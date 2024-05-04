#include "pch.h"
#include "xNyuHook.h"
#include "Overclocker.h"
#include "Threadhooker.h"



// --- Variables ---
std::unordered_set<DWORD> CurrentThreads;
std::unordered_set<DWORD> SafeThreads;
bool ThreadhookerEnabled = false;
THREADENTRY32 ThreadHookerThreadEntry = THREADENTRY32();
HANDLE ThreadhookerRoutineThread = nullptr;
HANDLE ThreadhookerEnabledMutex = CreateMutex(NULL, FALSE, NULL);
HANDLE ThreadhookerCurrentThreadsMutex = CreateMutex(NULL, FALSE, NULL);
HANDLE ThreadhookerSafeThreadsMutex = CreateMutex(NULL, FALSE, NULL);



// --- SuspendThread Hook ---
SuspendThreadHook<SuspendThreadT>* SuspendThreadHook<SuspendThreadT>::instance = nullptr;
EXTERN_DLL_EXPORT DWORD __stdcall SuspendThreadReal(HANDLE hThread, DWORD ignoreThread)
{
    if (SuspendThreadHook<SuspendThreadT>::instance && SuspendThreadHook<SuspendThreadT>::instance->isActive()) SuspendThreadHook<SuspendThreadT>::instance->setIgnoreThread(ignoreThread);
    return SuspendThread(hThread);
}

// --- ResumeThread Hook ---
ResumeThreadHook<ResumeThreadT>* ResumeThreadHook<ResumeThreadT>::instance = nullptr;
EXTERN_DLL_EXPORT DWORD __stdcall ResumeThreadReal(HANDLE hThread, DWORD ignoreThread)
{
    if (ResumeThreadHook<ResumeThreadT>::instance && ResumeThreadHook<ResumeThreadT>::instance->isActive()) ResumeThreadHook<ResumeThreadT>::instance->setIgnoreThread(ignoreThread);
    return ResumeThread(hThread);
}

// --- CreateThread Hook ---
CreateThreadHook<CreateThreadTT>* CreateThreadHook<CreateThreadTT>::instance = nullptr;
EXTERN_DLL_EXPORT HANDLE __stdcall CreateThreadReal(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId, bool safeThread)
{
    if (CreateThreadHook<CreateThreadTT>::instance && CreateThreadHook<CreateThreadTT>::instance->isActive()) CreateThreadHook<CreateThreadTT>::instance->setSafeThread(safeThread);
    return CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

// --- CreateRemoteThread Hook ---
CreateRemoteThreadHook<CreateRemoteThreadT>* CreateRemoteThreadHook<CreateRemoteThreadT>::instance = nullptr;
EXTERN_DLL_EXPORT HANDLE __stdcall CreateRemoteThreadReal(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId, bool safeThread)
{
    if (CreateRemoteThreadHook<CreateRemoteThreadT>::instance && CreateRemoteThreadHook<CreateRemoteThreadT>::instance->isActive()) CreateRemoteThreadHook<CreateRemoteThreadT>::instance->setSafeThread(safeThread);
    return CreateRemoteThread(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

// --- CreateRemoteThreadEx Hook ---
CreateRemoteThreadExHook<CreateRemoteThreadExT>* CreateRemoteThreadExHook<CreateRemoteThreadExT>::instance = nullptr;
EXTERN_DLL_EXPORT HANDLE __stdcall CreateRemoteThreadExReal(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList, LPDWORD lpThreadId, bool safeThread)
{
    if (CreateRemoteThreadExHook<CreateRemoteThreadExT>::instance && CreateRemoteThreadExHook<CreateRemoteThreadExT>::instance->isActive()) CreateRemoteThreadHook<CreateRemoteThreadExT>::instance->setSafeThread(safeThread);
    return CreateRemoteThreadEx(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpAttributeList, lpThreadId);
}

// --- ExitThread Hook ---
ExitThreadHook<ExitThreadT>* ExitThreadHook<ExitThreadT>::instance = nullptr;
EXTERN_DLL_EXPORT void __stdcall ExitThreadReal(DWORD dwExitCode)
{
    if (ExitThreadHook<ExitThreadT>::instance && ExitThreadHook<ExitThreadT>::instance->isActive()) return ExitThreadHook<ExitThreadT>::instance->callTrampoline(dwExitCode);
    else return ExitThread(dwExitCode);
}

// --- TerminateThread Hook ---
TerminateThreadHook<TerminateThreadT>* TerminateThreadHook<TerminateThreadT>::instance = nullptr;
EXTERN_DLL_EXPORT BOOL __stdcall TerminateThreadReal(HANDLE hThread, DWORD dwExitCode)
{
    if (TerminateThreadHook<TerminateThreadT>::instance && TerminateThreadHook<TerminateThreadT>::instance->isActive()) return TerminateThreadHook<TerminateThreadT>::instance->callTrampoline(hThread, dwExitCode);
    else return TerminateThread(hThread, dwExitCode);
}



// --- Functions ---
EXTERN_DLL_EXPORT int __stdcall ThreadHookerGetSafeThreadCount()
{
    WaitForSingleObject(ThreadhookerSafeThreadsMutex, INFINITE);
    int result = SafeThreads.size();
    ReleaseMutex(ThreadhookerSafeThreadsMutex);
    return result;
}

EXTERN_DLL_EXPORT int __stdcall ThreadHookerGetThreadCount()
{
    WaitForSingleObject(ThreadhookerCurrentThreadsMutex, INFINITE);
    int result = CurrentThreads.size();
    ReleaseMutex(ThreadhookerCurrentThreadsMutex);
    return result;
}

EXTERN_DLL_EXPORT std::unordered_set<DWORD> __stdcall ThreadHookerGetSafeThreads()
{
    WaitForSingleObject(ThreadhookerSafeThreadsMutex, INFINITE);
    std::unordered_set<DWORD> safeThreads = SafeThreads;
    ReleaseMutex(ThreadhookerSafeThreadsMutex);
    return safeThreads;
}

EXTERN_DLL_EXPORT std::unordered_set<DWORD> __stdcall ThreadHookerGetThreads()
{
    WaitForSingleObject(ThreadhookerCurrentThreadsMutex, INFINITE);
    std::unordered_set<DWORD> currentThreads = CurrentThreads;
    ReleaseMutex(ThreadhookerCurrentThreadsMutex);
    return currentThreads;
}

EXTERN_DLL_EXPORT bool __stdcall ThreadHookerSuspendThreads(int sleep = 0) {
    DWORD ignoreThread = GetCurrentThreadId();
    if (ThreadHookerGetThreadCount() > 0)
    {
        for (DWORD threadId : ThreadHookerGetThreads()) {
            HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadId);
            if (hThread != NULL) {
                SuspendThreadReal(hThread, ignoreThread);
                CloseHandle(hThread);
            }
        }
        if (sleep > 0) SleepExReal(sleep);
    }
    return true;
}

EXTERN_DLL_EXPORT bool __stdcall ThreadHookerResumeThreads(int sleep = 0) {
    DWORD ignoreThread = GetCurrentThreadId();
    if (ThreadHookerGetThreadCount() > 0)
    {
        for (DWORD threadId : ThreadHookerGetThreads()) {
            HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadId);
            if (hThread != NULL) {
                ResumeThreadReal(hThread, ignoreThread);
                CloseHandle(hThread);
            }
        }
        if (sleep > 0) SleepExReal(sleep);
    }
    return true;
}

void InitThreadhookerHooks()
{
    HMODULE Kernel32DLLHandle = GetModuleHandleA("Kernel32.dll");
    if (Kernel32DLLHandle != NULL)
    {
        if (!SuspendThreadHook<SuspendThreadT>::instance) SuspendThreadHook<SuspendThreadT>::instance = new SuspendThreadHook<SuspendThreadT>(GetProcAddress(Kernel32DLLHandle, "SuspendThread"));
        if (!ResumeThreadHook<ResumeThreadT>::instance) ResumeThreadHook<ResumeThreadT>::instance = new ResumeThreadHook<ResumeThreadT>(GetProcAddress(Kernel32DLLHandle, "ResumeThread"));
        if (!CreateThreadHook<CreateThreadTT>::instance) CreateThreadHook<CreateThreadTT>::instance = new CreateThreadHook<CreateThreadTT>(GetProcAddress(Kernel32DLLHandle, "CreateThread"));
        if (!CreateRemoteThreadHook<CreateRemoteThreadT>::instance) CreateRemoteThreadHook<CreateRemoteThreadT>::instance = new CreateRemoteThreadHook<CreateRemoteThreadT>(GetProcAddress(Kernel32DLLHandle, "CreateRemoteThread"));
        if (!CreateRemoteThreadExHook<CreateRemoteThreadExT>::instance) CreateRemoteThreadExHook<CreateRemoteThreadExT>::instance = new CreateRemoteThreadExHook<CreateRemoteThreadExT>(GetProcAddress(Kernel32DLLHandle, "CreateRemoteThreadEx"));
        if (!ExitThreadHook<ExitThreadT>::instance) ExitThreadHook<ExitThreadT>::instance = new ExitThreadHook<ExitThreadT>(GetProcAddress(Kernel32DLLHandle, "ExitThread"));
        if (!TerminateThreadHook<TerminateThreadT>::instance) TerminateThreadHook<TerminateThreadT>::instance = new TerminateThreadHook<TerminateThreadT>(GetProcAddress(Kernel32DLLHandle, "TerminateThread"));
    }
}

bool InitThreadhooker()
{
    InitThreadhookerHooks();

    if (SuspendThreadHook<SuspendThreadT>::instance) SuspendThreadHook<SuspendThreadT>::instance->install();
    if (ResumeThreadHook<ResumeThreadT>::instance) ResumeThreadHook<ResumeThreadT>::instance->install();
    if (CreateThreadHook<CreateThreadTT>::instance) CreateThreadHook<CreateThreadTT>::instance->install();
    if (CreateRemoteThreadHook<CreateRemoteThreadT>::instance) CreateRemoteThreadHook<CreateRemoteThreadT>::instance->install();
    if (CreateRemoteThreadExHook<CreateRemoteThreadExT>::instance) CreateRemoteThreadExHook<CreateRemoteThreadExT>::instance->install();
    if (ExitThreadHook<ExitThreadT>::instance) ExitThreadHook<ExitThreadT>::instance->install();
    if (TerminateThreadHook<TerminateThreadT>::instance) TerminateThreadHook<TerminateThreadT>::instance->install();

    // First thread search for initialization
    DWORD currentThreadId = GetCurrentThreadId();
    HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnapshot != INVALID_HANDLE_VALUE) {
        THREADENTRY32 threadEntry;
        threadEntry.dwSize = sizeof(THREADENTRY32);
        if (Thread32First(hThreadSnapshot, &threadEntry)) {
            do {
                if (threadEntry.th32OwnerProcessID == GetCurrentProcessId() &&
                    threadEntry.th32ThreadID != currentThreadId) {
                    CurrentThreads.insert(ThreadHookerThreadEntry.th32ThreadID);
                }
            } while (Thread32Next(hThreadSnapshot, &threadEntry));
        }
        CloseHandle(hThreadSnapshot);
    }

    setThreadhookerEnabled(true);
    CreateThreadReal(0, 0, (LPTHREAD_START_ROUTINE)ThreadhookerRoutine, 0, 0, 0, true);

    return true;
}

void UninitThreadhooker()
{
    setThreadhookerEnabled(false);

    if (SuspendThreadHook<SuspendThreadT>::instance && SuspendThreadHook<SuspendThreadT>::instance->isActive()) SuspendThreadHook<SuspendThreadT>::instance->remove();
    if (ResumeThreadHook<ResumeThreadT>::instance && ResumeThreadHook<ResumeThreadT>::instance->isActive()) ResumeThreadHook<ResumeThreadT>::instance->remove();
    if (CreateThreadHook<CreateThreadTT>::instance && CreateThreadHook<CreateThreadTT>::instance->isActive()) CreateThreadHook<CreateThreadTT>::instance->remove();
    if (CreateRemoteThreadHook<CreateRemoteThreadT>::instance && CreateRemoteThreadHook<CreateRemoteThreadT>::instance->isActive()) CreateRemoteThreadHook<CreateRemoteThreadT>::instance->remove();
    if (CreateRemoteThreadExHook<CreateRemoteThreadExT>::instance && CreateRemoteThreadExHook<CreateRemoteThreadExT>::instance->isActive()) CreateRemoteThreadExHook<CreateRemoteThreadExT>::instance->remove();
    if (ExitThreadHook<ExitThreadT>::instance && ExitThreadHook<ExitThreadT>::instance->isActive()) ExitThreadHook<ExitThreadT>::instance->remove();
    if (TerminateThreadHook<TerminateThreadT>::instance && TerminateThreadHook<TerminateThreadT>::instance->isActive()) TerminateThreadHook<TerminateThreadT>::instance->remove();
}

DWORD __stdcall ThreadhookerRoutine() {
    int ThreadHookerFrameSkipCurrent = 0;
    int ThreadHookerFrameSkipMax = 1;
    HANDLE ThreadHookerThreadSnapshot = 0;
    DWORD ThreadHookerCurrentThreadId = 0;
    bool ThreadHookerUpdateInit = false;
    DWORD ThreadHookerCurrentProccess = 0;
    int ThreadHookerUpdateBatch = 50;

    while (true)
    {
        if (!isThreadhookerEnabled()) break;
        ThreadHookerFrameSkipCurrent++;
        if (ThreadHookerFrameSkipCurrent < ThreadHookerFrameSkipMax) continue;

        if (ThreadHookerUpdateInit)
        {
            // Delete already closed normal threads
            if (ThreadHookerGetThreadCount() > 0)
            {
                std::vector<DWORD> threadsToErase;
                for (DWORD threadId : CurrentThreads)
                {
                    HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadId);
                    if (hThread == NULL) threadsToErase.push_back(threadId);
                    else CloseHandle(hThread);
                }
                for (DWORD threadId : threadsToErase) CurrentThreads.erase(threadId);
            }

            // Delete already closed safe threads
            if (ThreadHookerGetSafeThreadCount() > 0)
            {
                std::vector<DWORD> threadsToErase;
                for (DWORD threadId : SafeThreads)
                {
                    HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadId);
                    if (hThread == NULL) threadsToErase.push_back(threadId);
                    else CloseHandle(hThread);
                }
                for (DWORD threadId : threadsToErase) SafeThreads.erase(threadId);
            }

            // Init new thread search
            ThreadHookerCurrentThreadId = GetCurrentThreadId();
            ThreadHookerThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
            if (ThreadHookerThreadSnapshot == INVALID_HANDLE_VALUE) {
                return;
            }

            ThreadHookerThreadEntry.dwSize = sizeof(THREADENTRY32);

            if (!Thread32First(ThreadHookerThreadSnapshot, &ThreadHookerThreadEntry)) continue;
            ThreadHookerUpdateInit = false;
        }
        else
        {
            // Search a for batch of threads
            int safeThreadsCount = ThreadHookerGetSafeThreadCount();
            for (int b = 0; b < ThreadHookerUpdateBatch; b++)
            {
                if (Thread32Next(ThreadHookerThreadSnapshot, &ThreadHookerThreadEntry))
                {
                    if (ThreadHookerThreadEntry.th32OwnerProcessID == ThreadHookerCurrentProccess && ThreadHookerThreadEntry.th32ThreadID != ThreadHookerCurrentThreadId)
                    {
                        if (safeThreadsCount > 0) if (SafeThreads.find(ThreadHookerThreadEntry.th32ThreadID) != SafeThreads.end()) continue;
                        CurrentThreads.insert(ThreadHookerThreadEntry.th32ThreadID);
                    }
                }
                else
                {
                    CloseHandle(ThreadHookerThreadSnapshot);
                    ThreadHookerThreadSnapshot = 0;
                    ThreadHookerCurrentThreadId = 0;
                    ThreadHookerUpdateInit = true;
                    break;
                }
            }
        }

        ThreadHookerFrameSkipCurrent = 0;
    }

    return 0;
}

void setThreadhookerEnabled(bool value)
{
    WaitForSingleObject(ThreadhookerEnabledMutex, INFINITE);
    ThreadhookerEnabled = value;
    ReleaseMutex(ThreadhookerEnabledMutex);
}

bool isThreadhookerEnabled()
{
    WaitForSingleObject(ThreadhookerEnabledMutex, INFINITE);
    bool result =  ThreadhookerEnabled;
    ReleaseMutex(ThreadhookerEnabledMutex);
    return result;
}



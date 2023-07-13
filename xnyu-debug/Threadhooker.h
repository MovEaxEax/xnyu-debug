#pragma once

std::unordered_set<DWORD> CurrentThreads;
std::unordered_set<DWORD> SafeThreads;
bool ThreadHookerActive = false;
int ThreadHookerFrameSkipCurrent = 0;
int ThreadHookerFrameSkipMax = 1;
bool ThreadHookerSafeCreateThread = false;
bool ThreadHookerSafeCreateRemoteThread = false;
bool ThreadHookerSafeCreateRemoteThreadEx = false;
DWORD ThreadHookerOwnSuspensionMainThread = -1;
DWORD ThreadHookerOwnResumptionMainThread = -1;

typedef HANDLE(WINAPI* CreateThreadTT)(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
typedef VOID(WINAPI* ExitThreadTT)(DWORD dwExitCode);
typedef HANDLE(WINAPI* CreateRemoteThreadTT)(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
typedef HANDLE(WINAPI* CreateRemoteThreadExTT)(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList, LPDWORD lpThreadId);
typedef BOOL(WINAPI* TerminateThreadTT)(HANDLE hThread, DWORD dwExitCode);
typedef DWORD(WINAPI* SuspendThreadTT)(HANDLE hThread);
typedef DWORD(WINAPI* ResumeThreadTT)(HANDLE hThread);

HANDLE SuspendResumeThreadMutex = CreateMutex(NULL, FALSE, NULL);

template <typename FuncT>
class Hook_SuspendThread : public xNyuHook<SuspendThreadTT> {
public:
    static Hook_SuspendThread* instance;
    Hook_SuspendThread(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<SuspendThreadTT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static DWORD WINAPI CustomHook(HANDLE hThread)
    {
        WaitForSingleObject(SuspendResumeThreadMutex, INFINITE);
        instance->remove();
        bool canSuspend = true;
        if (ThreadHookerOwnSuspensionMainThread != -1)
        {
            DWORD currentMainThread = GetCurrentThreadId();
            if (currentMainThread == ThreadHookerOwnSuspensionMainThread) canSuspend = false;
        }
        DWORD result = canSuspend ? instance->pFunction(hThread) : 0;
        instance->install();
        ReleaseMutex(SuspendResumeThreadMutex);
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
Hook_SuspendThread<SuspendThreadTT>* Hook_SuspendThread<SuspendThreadTT>::instance = nullptr;

template <typename FuncT>
class Hook_ResumeThread : public xNyuHook<ResumeThreadTT> {
public:
    static Hook_ResumeThread* instance;
    Hook_ResumeThread(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<ResumeThreadTT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static DWORD WINAPI CustomHook(HANDLE hThread)
    {
        WaitForSingleObject(SuspendResumeThreadMutex, INFINITE);
        instance->remove();
        bool canResume = true;
        if (ThreadHookerOwnSuspensionMainThread != -1)
        {
            DWORD currentMainThread = GetCurrentThreadId();
            if (currentMainThread == ThreadHookerOwnResumptionMainThread) canResume = false;
        }
        DWORD result = canResume ? instance->pFunction(hThread) : 0;
        instance->install();
        ReleaseMutex(SuspendResumeThreadMutex);
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
Hook_ResumeThread<ResumeThreadTT>* Hook_ResumeThread<ResumeThreadTT>::instance = nullptr;

template <typename FuncT>
class Hook_CreateThread : public xNyuHook<CreateThreadTT> {
public:
    static Hook_CreateThread* instance;
    Hook_CreateThread(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<CreateThreadTT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HANDLE WINAPI CustomHook(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
    {
        instance->remove();
        HANDLE result = instance->pFunction(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
        if (ThreadHookerSafeCreateThread)
        {
            SafeThreads.insert(GetThreadId(result));
            ThreadHookerSafeCreateThread = false;
        }
        else CurrentThreads.insert(GetThreadId(result));
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
Hook_CreateThread<CreateThreadTT>* Hook_CreateThread<CreateThreadTT>::instance = nullptr;

template <typename FuncT>
class Hook_ExitThread : public xNyuHook<ExitThreadTT> {
public:
    static Hook_ExitThread* instance;
    Hook_ExitThread(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<ExitThreadTT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static VOID WINAPI CustomHook(DWORD dwExitCode)
    {
        instance->remove();
        DWORD targetThreadId = GetCurrentThreadId();
        CurrentThreads.erase(targetThreadId);
        SafeThreads.erase(targetThreadId);
        instance->pFunction(dwExitCode);
        instance->install();
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
Hook_ExitThread<ExitThreadTT>* Hook_ExitThread<ExitThreadTT>::instance = nullptr;

template <typename FuncT>
class Hook_CreateRemoteThread : public xNyuHook<CreateRemoteThreadTT> {
public:
    static Hook_CreateRemoteThread* instance;
    Hook_CreateRemoteThread(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<CreateRemoteThreadTT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HANDLE WINAPI CustomHook(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
    {
        instance->remove();
        HANDLE result = instance->pFunction(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
        if (ThreadHookerSafeCreateRemoteThread)
        {
            SafeThreads.insert(GetThreadId(result));
            ThreadHookerSafeCreateRemoteThread = false;
        }
        else CurrentThreads.insert(GetThreadId(result));
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
Hook_CreateRemoteThread<CreateRemoteThreadTT>* Hook_CreateRemoteThread<CreateRemoteThreadTT>::instance = nullptr;

template <typename FuncT>
class Hook_CreateRemoteThreadEx : public xNyuHook<CreateRemoteThreadExTT> {
public:
    static Hook_CreateRemoteThreadEx* instance;
    Hook_CreateRemoteThreadEx(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<CreateRemoteThreadExTT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HANDLE WINAPI CustomHook(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList, LPDWORD lpThreadId)
    {
        instance->remove();
        HANDLE result = instance->pFunction(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpAttributeList, lpThreadId);
        if (ThreadHookerSafeCreateRemoteThreadEx)
        {
            SafeThreads.insert(GetThreadId(result));
            ThreadHookerSafeCreateRemoteThreadEx = false;
        }
        else CurrentThreads.insert(GetThreadId(result));
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
Hook_CreateRemoteThreadEx<CreateRemoteThreadExTT>* Hook_CreateRemoteThreadEx<CreateRemoteThreadExTT>::instance = nullptr;

template <typename FuncT>
class Hook_TerminateThread : public xNyuHook<TerminateThreadTT> {
public:
    static Hook_TerminateThread* instance;
    Hook_TerminateThread(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<TerminateThreadTT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static BOOL WINAPI CustomHook(HANDLE hThread, DWORD dwExitCode)
    {
        instance->remove();
        DWORD targetThreadId = GetThreadId(hThread);
        CurrentThreads.erase(targetThreadId);
        SafeThreads.erase(targetThreadId);
        BOOL result = instance->pFunction(hThread, dwExitCode);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
Hook_TerminateThread<TerminateThreadTT>* Hook_TerminateThread<TerminateThreadTT>::instance = nullptr;



DWORD ThreadHookerCurrentThreadId = 0;
HANDLE ThreadHookerThreadSnapshot = 0;
THREADENTRY32 ThreadHookerThreadEntry;
bool ThreadHookerUpdateInit = false;
DWORD ThreadHookerCurrentProccess = 0;
int ThreadHookerUpdateBatch = 50;

int __stdcall ThreadHookerGetSafeThreadCount()
{
    return SafeThreads.size();
}

int __stdcall ThreadHookerGetThreadCount()
{
    return CurrentThreads.size();
}

std::unordered_set<DWORD> __stdcall ThreadHookerGetSafeThreads()
{
    return SafeThreads;
}

std::unordered_set<DWORD> __stdcall ThreadHookerGetThreads()
{
    return CurrentThreads;
}

HANDLE ResumeSuspendThreadFunctionMutex = CreateMutex(NULL, FALSE, NULL);

HANDLE SuspendThreadFunctionMutex = CreateMutex(NULL, FALSE, NULL);
bool __stdcall ThreadHookerSuspendThreads(int sleep = 0) {
    WaitForSingleObject(ResumeSuspendThreadFunctionMutex, INFINITE);
    WaitForSingleObject(SuspendThreadFunctionMutex, INFINITE);
    ThreadHookerOwnSuspensionMainThread = GetCurrentThreadId();
    if (ThreadHookerGetThreadCount() > 0)
    {
        for (DWORD threadId : CurrentThreads) {
            HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadId);
            if (threadId != ThreadHookerOwnSuspensionMainThread) {
                if (hThread != NULL) {
                    SuspendThread(hThread);
                    CloseHandle(hThread);
                }
            }
        }
        if (sleep > 0) Sleep(sleep);
    }
    ThreadHookerOwnSuspensionMainThread = -1;
    ReleaseMutex(SuspendThreadFunctionMutex);
    return true;
}

HANDLE ResumeThreadFunctionMutex = CreateMutex(NULL, FALSE, NULL);
bool __stdcall ThreadHookerResumeThreads(int sleep = 0) {
    WaitForSingleObject(ResumeThreadFunctionMutex, INFINITE);
    ThreadHookerOwnResumptionMainThread = GetCurrentThreadId();
    if (ThreadHookerGetThreadCount() > 0)
    {
        for (DWORD threadId : CurrentThreads) {
            HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadId);
            if (threadId != ThreadHookerOwnResumptionMainThread) {
                if (hThread != NULL) {
                    ResumeThread(hThread);
                    CloseHandle(hThread);
                }
            }
        }
        if (sleep > 0) Sleep(sleep);
    }
    ThreadHookerOwnSuspensionMainThread = -1;
    ReleaseMutex(ResumeThreadFunctionMutex);
    ReleaseMutex(ResumeSuspendThreadFunctionMutex);
    return true;
}

HANDLE WINAPI ThreadHookerCreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
{
    ThreadHookerSafeCreateThread = true;
    return CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

HANDLE WINAPI ThreadHookerCreateRemoteThread(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
{
    ThreadHookerSafeCreateRemoteThread = true;
    return CreateRemoteThread(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

HANDLE WINAPI ThreadHookerCreateRemoteThreadEx(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList, LPDWORD lpThreadId)
{
    ThreadHookerSafeCreateRemoteThreadEx = true;
    return CreateRemoteThreadEx(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpAttributeList, lpThreadId);
}

void InitThreadhooker()
{
    // Event driven thread detection
    HMODULE Kernel32DLLHandle = GetModuleHandleA("Kernel32.dll");
    if (Kernel32DLLHandle != NULL)
    {
        Hook_SuspendThread<SuspendThreadTT>::instance = new Hook_SuspendThread<SuspendThreadTT>(GetProcAddress(Kernel32DLLHandle, "SuspendThread"));
        Hook_SuspendThread<SuspendThreadTT>::instance->install();

        Hook_ResumeThread<ResumeThreadTT>::instance = new Hook_ResumeThread<ResumeThreadTT>(GetProcAddress(Kernel32DLLHandle, "ResumeThread"));
        Hook_ResumeThread<ResumeThreadTT>::instance->install();

        Hook_TerminateThread<TerminateThreadTT>::instance = new Hook_TerminateThread<TerminateThreadTT>(GetProcAddress(Kernel32DLLHandle, "TerminateThread"));
        Hook_TerminateThread<TerminateThreadTT>::instance->install();

        Hook_CreateRemoteThread<CreateRemoteThreadTT>::instance = new Hook_CreateRemoteThread<CreateRemoteThreadTT>(GetProcAddress(Kernel32DLLHandle, "CreateRemoteThread"));
        Hook_CreateRemoteThread<CreateRemoteThreadTT>::instance->install();

        Hook_CreateRemoteThreadEx<CreateRemoteThreadExTT>::instance = new Hook_CreateRemoteThreadEx<CreateRemoteThreadExTT>(GetProcAddress(Kernel32DLLHandle, "CreateRemoteThreadEx"));
        Hook_CreateRemoteThreadEx<CreateRemoteThreadExTT>::instance->install();

        Hook_ExitThread<ExitThreadTT>::instance = new Hook_ExitThread<ExitThreadTT>(GetProcAddress(Kernel32DLLHandle, "ExitThread"));
        Hook_ExitThread<ExitThreadTT>::instance->install();

        Hook_CreateThread<CreateThreadTT>::instance = new Hook_CreateThread<CreateThreadTT>(GetProcAddress(Kernel32DLLHandle, "CreateThread"));
        Hook_CreateThread<CreateThreadTT>::instance->install();

        ThreadHookerUpdateInit = true;
        ThreadHookerCurrentProccess = GetCurrentProcessId();
        ThreadHookerActive = true;
    }

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

    // Set references
    ThreadHookerReferences.ThreadHookerCreateRemoteThread = ThreadHookerCreateRemoteThread;
    ThreadHookerReferences.ThreadHookerCreateRemoteThreadEx = ThreadHookerCreateRemoteThreadEx;
    ThreadHookerReferences.ThreadHookerCreateThread = ThreadHookerCreateThread;
    ThreadHookerReferences.ThreadHookerGetSafeThreadCount = ThreadHookerGetSafeThreadCount;
    ThreadHookerReferences.ThreadHookerGetSafeThreads = ThreadHookerGetSafeThreads;
    ThreadHookerReferences.ThreadHookerGetThreadCount = ThreadHookerGetThreadCount;
    ThreadHookerReferences.ThreadHookerGetThreads = ThreadHookerGetThreads;
    ThreadHookerReferences.ThreadHookerResumeThreads = ThreadHookerResumeThreads;
    ThreadHookerReferences.ThreadHookerSuspendThreads = ThreadHookerSuspendThreads;
}

void UninitThreadhooker()
{
    if (ThreadHookerActive)
    {
        // Eject all used hooks
        while (true)
        {
            ThreadHookerSuspendThreads(5);

            bool deactivate = true;

            if (Hook_TerminateThread<TerminateThreadTT>::instance->isInstalled())
            {
                Hook_TerminateThread<TerminateThreadTT>::instance->remove();
                deactivate = false;
            }
            if (Hook_CreateRemoteThread<CreateRemoteThreadTT>::instance->isInstalled())
            {
                Hook_CreateRemoteThread<CreateRemoteThreadTT>::instance->remove();
                deactivate = false;
            }
            if (Hook_CreateRemoteThreadEx<CreateRemoteThreadExTT>::instance->isInstalled())
            {
                Hook_CreateRemoteThreadEx<CreateRemoteThreadExTT>::instance->remove();
                deactivate = false;
            }
            if (Hook_ExitThread<ExitThreadTT>::instance->isInstalled())
            {
                Hook_ExitThread<ExitThreadTT>::instance->remove();
                deactivate = false;
            }
            if (Hook_CreateThread<CreateThreadTT>::instance->isInstalled())
            {
                Hook_CreateThread<CreateThreadTT>::instance->remove();
                deactivate = false;
            }

            ThreadHookerResumeThreads(5);

            if (deactivate) break;
        }

        // Clear the lists
        if (CurrentThreads.size() > 0) CurrentThreads.clear();
        if (SafeThreads.size() > 0) SafeThreads.clear();
    }
}

void ThreadHookerUpdateThreads() {
    if (!ThreadHookerActive) return;
    ThreadHookerFrameSkipCurrent++;
    if (ThreadHookerFrameSkipCurrent < ThreadHookerFrameSkipMax) return;

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

        if (!Thread32First(ThreadHookerThreadSnapshot, &ThreadHookerThreadEntry)) return;
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



#pragma once

// --- Typedefs ---
typedef DWORD(__stdcall* SuspendThreadT)(HANDLE hThread);
typedef DWORD(__stdcall* ResumeThreadT)(HANDLE hThread);
typedef HANDLE(__stdcall* CreateThreadTT)(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
typedef HANDLE(__stdcall* CreateRemoteThreadT)(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
typedef HANDLE(__stdcall* CreateRemoteThreadExT)(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList, LPDWORD lpThreadId);
typedef void(__stdcall* ExitThreadT)(DWORD dwExitCode);
typedef BOOL(__stdcall* TerminateThreadT)(HANDLE hThread, DWORD dwExitCode);



// --- Variables ---
std::unordered_set<DWORD> CurrentThreads;
std::unordered_set<DWORD> SafeThreads;
bool ThreadhookerEnabled;
THREADENTRY32 ThreadHookerThreadEntry;
HANDLE ThreadhookerRoutineThread;
HANDLE ThreadhookerEnabledMutex;
HANDLE ThreadhookerCurrentThreadsMutex;
HANDLE ThreadhookerSafeThreadsMutex;



// --- SuspendThread ---
template <typename FuncT>
class SuspendThreadHook : public xNyuHook<SuspendThreadT> {
private:
    DWORD ignoreThread = -1;
public:
    static SuspendThreadHook* instance;
    SuspendThreadHook(void* originalAddress) : xNyuHook<SuspendThreadT>(originalAddress, CustomHook) { instance = this; }
    static DWORD __stdcall CustomHook(HANDLE hThread)
    {
        if (instance->HookInit)
        {
            DebugConsoleOutput("SuspendThread() Hook active...", true, "yellow");
            instance->HookInit = false;
        }
        if (instance->ignoreThread == -1 || GetCurrentThreadId() != instance->ignoreThread) return instance->callTrampoline(hThread);
        instance->ignoreThread = -1;
        return 0;
    }
    void setIgnoreThread(DWORD value) { instance->ignoreThread = value };
};
DWORD SuspendThreadReal(HANDLE hThread, DWORD ignoreThread = -1);

// --- ResumeThread Hook ---
template <typename FuncT>
class ResumeThreadHook : public xNyuHook<ResumeThreadT> {
private:
    DWORD ignoreThread = -1;
public:
    static ResumeThreadHook* instance;
    ResumeThreadHook(void* originalAddress) : xNyuHook<ResumeThreadT>(originalAddress, CustomHook) { instance = this; }
    static DWORD __stdcall CustomHook(HANDLE hThread)
    {
        if (instance->HookInit)
        {
            DebugConsoleOutput("ResumeThread() Hook active...", true, "yellow");
            instance->HookInit = false;
        }
        if (instance->ignoreThread == -1 || GetCurrentThreadId() != instance->ignoreThread) return instance->callTrampoline(hThread);
        instance->ignoreThread = -1;
        return 0;
    }
    void setIgnoreThread(DWORD value) { instance->ignoreThread = value };
};
DWORD ResumeThreadReal(HANDLE hThread, DWORD ignoreThread = -1);

// --- CreateThread Hook ---
template <typename FuncT>
class CreateThreadHook : public xNyuHook<CreateThreadTT> {
private:
    bool safeThread;
public:
    static CreateThreadHook* instance;
    CreateThreadHook(void* originalAddress) : xNyuHook<CreateThreadTT>(originalAddress, CustomHook) { instance = this; }
    static HANDLE __stdcall CustomHook(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
    {
        if (instance->HookInit)
        {
            DebugConsoleOutput("CreateThread() Hook active...", true, "yellow");
            instance->HookInit = false;
        }
        HANDLE result = instance->callTrampoline(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
        if (instance->safeThread)
        {
            SafeThreads.insert(GetThreadId(result));
            instance->safeThread = false;
        }
        else CurrentThreads.insert(GetThreadId(result));
        return result;
    }
    void setSafeThread(bool value) { instance->safeThread = value };
};
HANDLE CreateThreadReal(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId, bool safeThread = false);

// --- CreateRemoteThread Hook ---
template <typename FuncT>
class CreateRemoteThreadHook : public xNyuHook<CreateRemoteThreadT> {
private:
    bool safeThread;
public:
    static CreateRemoteThreadHook* instance;
    CreateRemoteThreadHook(void* originalAddress) : xNyuHook<CreateRemoteThreadT>(originalAddress, CustomHook) { instance = this; }
    static HANDLE __stdcall CustomHook(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
    {
        if (instance->HookInit)
        {
            DebugConsoleOutput("CreateRemoteThread() Hook active...", true, "yellow");
            instance->HookInit = false;
        }
        HANDLE result = instance->callTrampoline(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
        if (instance->safeThread)
        {
            SafeThreads.insert(GetThreadId(result));
            instance->safeThread = false;
        }
        else CurrentThreads.insert(GetThreadId(result));
        return result;
    }
    void setSafeThread(bool value) { instance->safeThread = value };
};
HANDLE CreateRemoteThreadReal(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId, bool safeThread = false);

// --- CreateRemoteThreadEx Hook ---
template <typename FuncT>
class CreateRemoteThreadExHook : public xNyuHook<CreateRemoteThreadExT> {
private:
    bool safeThread;
public:
    static CreateRemoteThreadExHook* instance;
    CreateRemoteThreadExHook(void* originalAddress) : xNyuHook<CreateRemoteThreadExT>(originalAddress, CustomHook) { instance = this; }
    static HANDLE __stdcall CustomHook(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList, LPDWORD lpThreadId)
    {
        if (instance->HookInit)
        {
            DebugConsoleOutput("CreateRemoteThreadEx() Hook active...", true, "yellow");
            instance->HookInit = false;
        }
        HANDLE result = instance->callTrampoline(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpAttributeList, lpThreadId);
        if (instance->safeThread)
        {
            SafeThreads.insert(GetThreadId(result));
            instance->safeThread = false;
        }
        else CurrentThreads.insert(GetThreadId(result));
        return result;
    }
    void setSafeThread(bool value) { instance->safeThread = value };
};
HANDLE CreateRemoteThreadExReal(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList, LPDWORD lpThreadId, bool safeThread = false);

// --- ExitThread Hook ---
template <typename FuncT>
class ExitThreadHook : public xNyuHook<ExitThreadT> {
public:
    static ExitThreadHook* instance;
    ExitThreadHook(void* originalAddress) : xNyuHook<ExitThreadT>(originalAddress, CustomHook) { instance = this; }
    static void __stdcall CustomHook(DWORD dwExitCode)
    {
        if (instance->HookInit)
        {
            DebugConsoleOutput("ExitThread() Hook active...", true, "yellow");
            instance->HookInit = false;
        }
        DWORD targetThreadId = GetCurrentThreadId();
        CurrentThreads.erase(targetThreadId);
        SafeThreads.erase(targetThreadId);
        instance->callTrampoline(dwExitCode);
    }
};
void ExitThreadReal(DWORD dwExitCode);

// --- TerminateThread Hook ---
template <typename FuncT>
class TerminateThreadHook : public xNyuHook<TerminateThreadT> {
public:
    static TerminateThreadHook* instance;
    TerminateThreadHook(void* originalAddress) : xNyuHook<TerminateThreadT>(originalAddress, CustomHook) { instance = this; }
    static BOOL __stdcall CustomHook(HANDLE hThread, DWORD dwExitCode)
    {
        if (instance->HookInit)
        {
            DebugConsoleOutput("TerminateThread() Hook active...", true, "yellow");
            instance->HookInit = false;
        }
        DWORD targetThreadId = GetCurrentThreadId();
        CurrentThreads.erase(targetThreadId);
        SafeThreads.erase(targetThreadId);
        return instance->callTrampoline(dwExitCode);
    }
};
BOOL TerminateThreadReal(HANDLE hThread, DWORD dwExitCode);



// --- Functions ---
int __stdcall ThreadHookerGetSafeThreadCount();
int __stdcall ThreadHookerGetThreadCount();
std::unordered_set<DWORD> __stdcall ThreadHookerGetSafeThreads();
std::unordered_set<DWORD> __stdcall ThreadHookerGetThreads();
bool __stdcall ThreadHookerSuspendThreads(int sleep = 0);
bool __stdcall ThreadHookerResumeThreads(int sleep = 0);
void InitThreadhookerHooks();
bool InitThreadhooker();
void UninitThreadhooker();
DWORD __stdcall ThreadhookerUpdate();
void setThreadhookerEnabled(bool value);
bool isThreadhookerEnabled();


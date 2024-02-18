#pragma once

// --- Typedefs ---
typedef DWORD(__stdcall* SleepExT)(DWORD dwMilliseconds, BOOL bAlertable);
typedef DWORD(__stdcall* GetTickCountT)();
typedef BOOL(__stdcall* QueryPerformanceCounterT)(LARGE_INTEGER* lpPerformanceCount);
typedef BOOL(__stdcall* QueryPerformanceFrequencyT)(LARGE_INTEGER* lpFrequency);
typedef DWORD(__stdcall* timeGetTimeT)();
typedef void(__stdcall* GetSystemTimeAsFileTimeT)(LPFILETIME lpSystemTimeAsFileTime);
typedef void(__stdcall* GetSystemTimePreciseAsFileTimeT)(LPFILETIME lpSystemTimeAsFileTime);
typedef BOOL(__stdcall* SetWaitableTimerT)(HANDLE hTimer, const LARGE_INTEGER* pDueTime, LONG lPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, LPVOID lpArgToCompletionRoutine, BOOL fResume);



// --- Variables ---
extern bool OverclockerEnabled;



// --- SleepEx Hook ---
template <typename FuncT>
class SleepExHook : public xNyuHook<SleepExT> {
public:
	static SleepExHook* instance;
	SleepExHook(void* originalAddress) : xNyuHook<SleepExT>(originalAddress, CustomHook) { instance = this; }
	static DWORD __stdcall CustomHook(DWORD dwMilliseconds, BOOL bAlertable)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("SleepEx() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		DWORD timeToSleep = (DWORD)ceil(round((float)dwMilliseconds / instance->Factor));
		return instance->callTrampoline(timeToSleep, bAlertable);
	}
};
DWORD SleepExReal(DWORD dwMilliseconds, BOOL bAlertable = false);



// --- GetTickCount Hook ---
template <typename FuncT>
class GetTickCountHook : public xNyuHook<GetTickCountT> {
private:
	DWORD OriginalClock = 0;
public:
	static GetTickCountHook* instance;
	GetTickCountHook(void* originalAddress) : xNyuHook<GetTickCountT>(originalAddress, CustomHook) { instance = this; }
	static DWORD __stdcall CustomHook()
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetTickCount() Hook active...", true, "yellow");
			instance->OriginalClock = instance->callTrampoline();
			instance->HookInit = false;
		}
		DWORD result = instance->callTrampoline();
		return result + ((result - instance->OriginalClock) * instance->Factor);
	}
};
DWORD GetTickCountReal();



// --- QueryPerformanceCounter Hook ---
template <typename FuncT>
class QueryPerformanceCounterHook : public xNyuHook<QueryPerformanceCounterT> {
private:
	LARGE_INTEGER OriginalPerformanceCount = LARGE_INTEGER();
public:
	static QueryPerformanceCounterHook* instance;
	QueryPerformanceCounterHook(void* originalAddress) : xNyuHook<QueryPerformanceCounterT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(LARGE_INTEGER* lpPerformanceCount)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("QueryPerformanceCounter() Hook active...", true, "yellow");
			instance->callTrampoline(reinterpret_cast<LARGE_INTEGER*>(&instance->OriginalPerformanceCount));
			instance->HookInit = false;
		}
		BOOL result = instance->callTrampoline(lpPerformanceCount);
		if (!result) return false;

		LONGLONG difference = lpPerformanceCount->QuadPart - instance->OriginalPerformanceCount.QuadPart;
		LONGLONG adjustment = static_cast<LONGLONG>(difference * (instance->Factor - 1.0f));
		lpPerformanceCount->QuadPart += adjustment;

		return true;
	}
};
BOOL QueryPerformanceCounterReal(LARGE_INTEGER* lpPerformanceCount);



// --- QueryPerformanceFrequency Hook ---
template <typename FuncT>
class QueryPerformanceFrequencyHook : public xNyuHook<QueryPerformanceFrequencyT> {
public:
	static QueryPerformanceFrequencyHook* instance;
	QueryPerformanceFrequencyHook(void* originalAddress) : xNyuHook<QueryPerformanceFrequencyT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(LARGE_INTEGER* lpFrequency)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("QueryPerformanceFrequency() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		BOOL result = instance->callTrampoline(lpFrequency);
		if (result) lpFrequency->QuadPart *= instance->Factor;
		return result;
	}
};
BOOL QueryPerformanceFrequencyReal(LARGE_INTEGER* lpFrequency);



// --- timeGetTime Hook ---
template <typename FuncT>
class timeGetTimeHook : public xNyuHook<timeGetTimeT> {
private:
	DWORD OriginalTime = 0;
public:
	static timeGetTimeHook* instance;
	timeGetTimeHook(void* originalAddress) : xNyuHook<timeGetTimeT>(originalAddress, CustomHook) { instance = this; }
	static DWORD __stdcall CustomHook()
	{
		instance->remove(true);
		if (instance->HookInit)
		{
			DebugConsoleOutput("timeGetTime() Hook active...", true, "yellow");
			instance->OriginalTime = instance->callOriginal();
			instance->HookInit = false;
		}
		DWORD result = instance->callOriginal();
		result = instance->OriginalTime + ((result - instance->OriginalTime) * instance->Factor);
		instance->install(false, true);
		return result;
	}
};
DWORD timeGetTimeReal();



// --- GetSystemTimeAsFileTime Hook ---
template <typename FuncT>
class GetSystemTimeAsFileTimeHook : public xNyuHook<GetSystemTimeAsFileTimeT> {
private:
	ULARGE_INTEGER OriginalFileTime = ULARGE_INTEGER();
public:
	static GetSystemTimeAsFileTimeHook* instance;
	GetSystemTimeAsFileTimeHook(void* originalAddress) : xNyuHook<GetSystemTimeAsFileTimeT>(originalAddress, CustomHook) { instance = this; }
	static void __stdcall CustomHook(LPFILETIME lpSystemTimeAsFileTime)
	{
		instance->remove(true);
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetSystemTimeAsFileTime() Hook active...", true, "yellow");
			instance->callOriginal((LPFILETIME)&instance->OriginalFileTime);
			instance->HookInit = false;
		}
		instance->callOriginal(lpSystemTimeAsFileTime);
		ULARGE_INTEGER FileTimer;
		FileTimer.LowPart = lpSystemTimeAsFileTime->dwLowDateTime;
		FileTimer.HighPart = lpSystemTimeAsFileTime->dwHighDateTime;
		FileTimer.QuadPart += (FileTimer.QuadPart - instance->OriginalFileTime.QuadPart) * instance->Factor;
		lpSystemTimeAsFileTime->dwLowDateTime = FileTimer.LowPart;
		lpSystemTimeAsFileTime->dwHighDateTime = FileTimer.HighPart;
		instance->install(false, true);
	}
};
void GetSystemTimeAsFileTimeReal(LPFILETIME lpSystemTimeAsFileTime);



// --- GetSystemTimePreciseAsFileTime Hook ---
template <typename FuncT>
class GetSystemTimePreciseAsFileTimeHook : public xNyuHook<GetSystemTimePreciseAsFileTimeT> {
private:
	ULARGE_INTEGER OriginalPreciseFileTime = ULARGE_INTEGER();
public:
	static GetSystemTimePreciseAsFileTimeHook* instance;
	GetSystemTimePreciseAsFileTimeHook(void* originalAddress) : xNyuHook<GetSystemTimePreciseAsFileTimeT>(originalAddress, CustomHook) { instance = this; }
	static void __stdcall CustomHook(LPFILETIME lpSystemTimeAsFileTime)
	{
		instance->remove(true);
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetSystemTimePreciseAsFileTime() Hook active...", true, "yellow");
			instance->callOriginal((LPFILETIME)&instance->OriginalPreciseFileTime);
			instance->HookInit = false;
		}
		instance->callOriginal(lpSystemTimeAsFileTime);
		ULARGE_INTEGER PreciseFileTimer;
		PreciseFileTimer.LowPart = lpSystemTimeAsFileTime->dwLowDateTime;
		PreciseFileTimer.HighPart = lpSystemTimeAsFileTime->dwHighDateTime;
		PreciseFileTimer.QuadPart += (PreciseFileTimer.QuadPart - instance->OriginalPreciseFileTime.QuadPart) * instance->Factor;
		lpSystemTimeAsFileTime->dwLowDateTime = PreciseFileTimer.LowPart;
		lpSystemTimeAsFileTime->dwHighDateTime = PreciseFileTimer.HighPart;
		instance->install(false, true);
	}
};
void GetSystemTimePreciseAsFileTimeReal(LPFILETIME lpSystemTimeAsFileTime);



// --- SetWaitableTimer Hook ---
template <typename FuncT>
class SetWaitableTimerHook : public xNyuHook<SetWaitableTimerT> {
public:
	static SetWaitableTimerHook* instance;
	SetWaitableTimerHook(void* originalAddress) : xNyuHook<SetWaitableTimerT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(HANDLE hTimer, const LARGE_INTEGER* pDueTime, LONG lPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, LPVOID lpArgToCompletionRoutine, BOOL fResume)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("SetWaitableTimer() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		LARGE_INTEGER ModifiedDueTime;
		ModifiedDueTime.QuadPart = pDueTime->QuadPart / instance->Factor;
		LONG ModifiedPeriod = lPeriod / instance->Factor;
		return instance->callTrampoline(hTimer, &ModifiedDueTime, ModifiedPeriod, pfnCompletionRoutine, lpArgToCompletionRoutine, fResume);
	}
};
BOOL SetWaitableTimerReal(HANDLE hTimer, const LARGE_INTEGER* pDueTime, LONG lPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, LPVOID lpArgToCompletionRoutine, BOOL fResume);



// --- Functions ---
void OverclockerSetSpeed(float value);
void InitOverclockerHooks();
bool InitOverclocker();
void UninitOverclocker();
bool isOverclockerEnabled();



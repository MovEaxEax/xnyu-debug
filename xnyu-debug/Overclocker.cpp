#include "pch.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "Threadhooker.h"
#include "xNyuHook.h"
#include "Overclocker.h"



// --- Variables ---
bool OverclockerEnabled = false;



// --- SleepEx Hook ---
SleepExHook<SleepExT>* SleepExHook<SleepExT>::instance = nullptr;
DWORD SleepExReal(DWORD dwMilliseconds, BOOL bAlertable)
{
	if (SleepExHook<SleepExT>::instance && SleepExHook<SleepExT>::instance->isActive()) return SleepExHook<SleepExT>::instance->callTrampoline(dwMilliseconds, bAlertable);
	else return SleepEx(dwMilliseconds, bAlertable);
}

// --- GetTickCount Hook ---
GetTickCountHook<GetTickCountT>* GetTickCountHook<GetTickCountT>::instance = nullptr;
DWORD GetTickCountReal()
{
	if (GetTickCountHook<GetTickCountT>::instance && GetTickCountHook<GetTickCountT>::instance->isActive()) return GetTickCountHook<GetTickCountT>::instance->callTrampoline();
	else return GetTickCount();
}

// --- QueryPerformanceCounter Hook ---
QueryPerformanceCounterHook<QueryPerformanceCounterT>* QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance = nullptr;
BOOL QueryPerformanceCounterReal(LARGE_INTEGER* lpPerformanceCount)
{
	if (QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance && QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance->isActive()) return QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance->callTrampoline(lpPerformanceCount);
	else return QueryPerformanceCounter(lpPerformanceCount);
}

// --- QueryPerformanceFrequency Hook ---
QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>* QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance = nullptr;
BOOL QueryPerformanceFrequencyReal(LARGE_INTEGER* lpFrequency)
{
	if (QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance && QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance->isActive()) return QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance->callTrampoline(lpFrequency);
	else return QueryPerformanceFrequency(lpFrequency);
}

// --- timeGetTime Hook ---
timeGetTimeHook<timeGetTimeT>* timeGetTimeHook<timeGetTimeT>::instance = nullptr;
DWORD timeGetTimeReal()
{
	if (timeGetTimeHook<timeGetTimeT>::instance && timeGetTimeHook<timeGetTimeT>::instance->isActive()) return timeGetTimeHook<timeGetTimeT>::instance->callOriginalSafeType();
	else return timeGetTime();
}

// --- GetSystemTimeAsFileTime Hook ---
GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>* GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance = nullptr;
void GetSystemTimeAsFileTimeReal(LPFILETIME lpSystemTimeAsFileTime)
{
	if (GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance && GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance->isActive()) GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance->callOriginalSafeVoid(lpSystemTimeAsFileTime);
	else GetSystemTimeAsFileTime(lpSystemTimeAsFileTime);
}

// --- GetSystemTimePreciseAsFileTime Hook ---
GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>* GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance = nullptr;
void GetSystemTimePreciseAsFileTimeReal(LPFILETIME lpSystemTimeAsFileTime)
{
	if (GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance && GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance->isActive()) GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance->callOriginalSafeVoid(lpSystemTimeAsFileTime);
	else GetSystemTimePreciseAsFileTime(lpSystemTimeAsFileTime);
}

// --- SetWaitableTimer Hook ---
SetWaitableTimerHook<SetWaitableTimerT>* SetWaitableTimerHook<SetWaitableTimerT>::instance = nullptr;
BOOL SetWaitableTimerReal(HANDLE hTimer, const LARGE_INTEGER* pDueTime, LONG lPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, LPVOID lpArgToCompletionRoutine, BOOL fResume)
{
	if (SetWaitableTimerHook<SetWaitableTimerT>::instance && SetWaitableTimerHook<SetWaitableTimerT>::instance->isInstalled()) return SetWaitableTimerHook<SetWaitableTimerT>::instance->callTrampoline(hTimer, pDueTime, lPeriod, pfnCompletionRoutine, lpArgToCompletionRoutine, fResume);
	else return SetWaitableTimer(hTimer, pDueTime, lPeriod, pfnCompletionRoutine, lpArgToCompletionRoutine, fResume);
}



// --- Functions ---
void OverclockerSetSpeed(float value)
{
	if (SleepExHook<SleepExT>::instance && SleepExHook<SleepExT>::instance->isInstalled()) SleepExHook<SleepExT>::instance->setFactor(value);
	if (GetTickCountHook<GetTickCountT>::instance && GetTickCountHook<GetTickCountT>::instance->isInstalled()) GetTickCountHook<GetTickCountT>::instance->setFactor(value);
	if (QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance && QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance->isInstalled()) QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance->setFactor(value);
	if (QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance && QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance->isInstalled()) QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance->setFactor(value);
	if (timeGetTimeHook<timeGetTimeT>::instance && timeGetTimeHook<timeGetTimeT>::instance->isInstalled()) timeGetTimeHook<timeGetTimeT>::instance->setFactor(value);
	if (GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance && GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance->isInstalled()) GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance->setFactor(value);
	if (GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance && GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance->isInstalled()) GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance->setFactor(value);
	if (SetWaitableTimerHook<SetWaitableTimerT>::instance && SetWaitableTimerHook<SetWaitableTimerT>::instance->isInstalled()) SetWaitableTimerHook<SetWaitableTimerT>::instance->setFactor(value);
}

void InitOverclockerHooks()
{
	std::string overclockerHooks = GetGlobalSetting("config_overclocker_hooks");

	HMODULE KernelbaseDLLHandle = GetModuleHandleA("Kernelbase.dll");
	if (KernelbaseDLLHandle != NULL)
	{
		if (overclockerHooks.find("sleepex") != std::string::npos || overclockerHooks.find("all") != std::string::npos)
		{
			if (!SleepExHook<SleepExT>::instance) SleepExHook<SleepExT>::instance = new SleepExHook<SleepExT>(GetProcAddress(KernelbaseDLLHandle, "SleepEx"));
		}
		if (overclockerHooks.find("getsystemtimeasfiletime") != std::string::npos || overclockerHooks.find("all") != std::string::npos)
		{
			if (!GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance) GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance = new GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>(GetProcAddress(KernelbaseDLLHandle, "GetSystemTimeAsFileTime"));
		}
		if (overclockerHooks.find("getsystemtimepreciseasfiletime") != std::string::npos || overclockerHooks.find("all") != std::string::npos)
		{
			if (!GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance) GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance = new GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>(GetProcAddress(KernelbaseDLLHandle, "GetSystemTimePreciseAsFileTime"));
		}
		if (overclockerHooks.find("setwaitabletimer") != std::string::npos || overclockerHooks.find("all") != std::string::npos)
		{
			if (!SetWaitableTimerHook<SetWaitableTimerT>::instance) SetWaitableTimerHook<SetWaitableTimerT>::instance = new SetWaitableTimerHook<SetWaitableTimerT>(GetProcAddress(KernelbaseDLLHandle, "SetWaitableTimer"));
		}
		if (overclockerHooks.find("queryperformancecounter") != std::string::npos || overclockerHooks.find("all") != std::string::npos)
		{
			if (!QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance) QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance = new QueryPerformanceCounterHook<QueryPerformanceCounterT>(GetProcAddress(KernelbaseDLLHandle, "QueryPerformanceCounter"));
		}
		if (overclockerHooks.find("queryperformancefrequency") != std::string::npos || overclockerHooks.find("all") != std::string::npos)
		{
			if (!QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance) QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance = new QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>(GetProcAddress(KernelbaseDLLHandle, "QueryPerformanceFrequency"));
		}
	}

	HMODULE Kernel32DLLHandle = GetModuleHandleA("Kernel32.dll");
	if (Kernel32DLLHandle != NULL)
	{
		if (overclockerHooks.find("gettickcount") != std::string::npos || overclockerHooks.find("all") != std::string::npos)
		{
			if (!GetTickCountHook<GetTickCountT>::instance) GetTickCountHook<GetTickCountT>::instance = new GetTickCountHook<GetTickCountT>(GetProcAddress(KernelbaseDLLHandle, "GetTickCount"));
		}
		if (overclockerHooks.find("timegettime") != std::string::npos || overclockerHooks.find("all") != std::string::npos)
		{
			if (!timeGetTimeHook<timeGetTimeT>::instance) timeGetTimeHook<timeGetTimeT>::instance = new timeGetTimeHook<timeGetTimeT>(GetProcAddress(Kernel32DLLHandle, "timeGetTime"));
		}
	}
}

bool InitOverclocker()
{
	InitOverclockerHooks();

	ThreadHookerSuspendThreads(0);

	if (SleepExHook<SleepExT>::instance) SleepExHook<SleepExT>::instance->install();
	if (GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance) GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance->install(false, false);
	if (GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance) GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance->install(false, false);
	if (SetWaitableTimerHook<SetWaitableTimerT>::instance) SetWaitableTimerHook<SetWaitableTimerT>::instance->install();
	if (QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance) QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance->install();
	if (QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance) QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance->install();
	if (GetTickCountHook<GetTickCountT>::instance) GetTickCountHook<GetTickCountT>::instance->install();
	if (timeGetTimeHook<timeGetTimeT>::instance) timeGetTimeHook<timeGetTimeT>::instance->install(false, false);

	OverclockerSetSpeed(2.0f);

	OverclockerEnabled = true;

	ThreadHookerResumeThreads(0);

	return true;
}

void UninitOverclocker()
{
	ThreadHookerSuspendThreads(0);

	if (SleepExHook<SleepExT>::instance && SleepExHook<SleepExT>::instance->isActive()) SleepExHook<SleepExT>::instance->remove();
	if (GetTickCountHook<GetTickCountT>::instance && GetTickCountHook<GetTickCountT>::instance->isActive()) GetTickCountHook<GetTickCountT>::instance->remove();
	if (QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance && QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance->isActive()) QueryPerformanceCounterHook<QueryPerformanceCounterT>::instance->remove();
	if (QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance && QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance->isActive()) QueryPerformanceFrequencyHook<QueryPerformanceFrequencyT>::instance->remove();
	if (timeGetTimeHook<timeGetTimeT>::instance && timeGetTimeHook<timeGetTimeT>::instance->isActive()) timeGetTimeHook<timeGetTimeT>::instance->remove();
	if (GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance && GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance->isActive()) GetSystemTimeAsFileTimeHook<GetSystemTimeAsFileTimeT>::instance->remove();
	if (GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance && GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance->isActive()) GetSystemTimePreciseAsFileTimeHook<GetSystemTimePreciseAsFileTimeT>::instance->remove();
	if (SetWaitableTimerHook<SetWaitableTimerT>::instance && SetWaitableTimerHook<SetWaitableTimerT>::instance->isActive()) SetWaitableTimerHook<SetWaitableTimerT>::instance->remove();

	OverclockerEnabled = false;

	ThreadHookerResumeThreads(0);
}

bool isOverclockerEnabled()
{
	return OverclockerEnabled;
}



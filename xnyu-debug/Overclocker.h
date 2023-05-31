#pragma once

// Global hook settings
typedef DWORD(__stdcall* GetTickCountT)();
GetTickCountT pGetTickCount = nullptr;
subhook::Hook GetTickCountSubHook;
void* GetTickCountOriginalAddress;
void* GetTickCountHookAddress;

typedef BOOL(__stdcall* QueryPerformanceCounterT)(LARGE_INTEGER* lpPerformanceCount);
QueryPerformanceCounterT pQueryPerformanceCounter = nullptr;
subhook::Hook QueryPerformanceCounterSubHook;
void* QueryPerformanceCounterOriginalAddress;
void* QueryPerformanceCounterHookAddress;

typedef BOOL(__stdcall* QueryPerformanceFrequencyT)(LARGE_INTEGER* lpFrequency);
QueryPerformanceFrequencyT pQueryPerformanceFrequency = nullptr;
subhook::Hook QueryPerformanceFrequencySubHook;
void* QueryPerformanceFrequencyOriginalAddress;
void* QueryPerformanceFrequencyHookAddress;

typedef DWORD(__stdcall* timeGetTimeT)();
timeGetTimeT pTimeGetTime = nullptr;
subhook::Hook TimeGetTimeSubHook;
void* TimeGetTimeOriginalAddress;
void* TimeGetTimeHookAddress;

typedef void(__stdcall* GetSystemTimeAsFileTimeT)(LPFILETIME lpSystemTimeAsFileTime);
GetSystemTimeAsFileTimeT pGetSystemTimeAsFileTime = nullptr;
subhook::Hook GetSystemTimeAsFileTimeSubHook;
void* GetSystemTimeAsFileTimeOriginalAddress;
void* GetSystemTimeAsFileTimeHookAddress;

typedef void(__stdcall* GetSystemTimePreciseAsFileTimeT)(LPFILETIME lpSystemTimeAsFileTime);
GetSystemTimePreciseAsFileTimeT pGetSystemTimePreciseAsFileTime = nullptr;
subhook::Hook GetSystemTimePreciseAsFileTimeSubHook;
void* GetSystemTimePreciseAsFileTimeOriginalAddress;
void* GetSystemTimePreciseAsFileTimeHookAddress;

/*
typedef HANDLE(__stdcall* CreateWaitableTimerAT)(LPSECURITY_ATTRIBUTES lpTimerAAttributes, BOOL bManualReset, LPCSTR lpTimerAName);
CreateWaitableTimerAT pCreateWaitableTimerA = nullptr;
subhook::Hook CreateWaitableTimerASubHook;
void* CreateWaitableTimerAOriginalAddress;
void* CreateWaitableTimerAHookAddress;

typedef HANDLE(__stdcall* CreateWaitableTimerWT)(LPSECURITY_ATTRIBUTES lpTimerWAttributes, BOOL bManualReset, LPCWSTR lpTimerWName);
CreateWaitableTimerWT pCreateWaitableTimerW = nullptr;
subhook::Hook CreateWaitableTimerWSubHook;
void* CreateWaitableTimerWOriginalAddress;
void* CreateWaitableTimerWHookAddress;
*/

typedef BOOL(__stdcall* SetWaitableTimerT)(HANDLE hTimer, const LARGE_INTEGER* pDueTime, LONG lPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, LPVOID lpArgToCompletionRoutine, BOOL fResume);
SetWaitableTimerT pSetWaitableTimer = nullptr;
subhook::Hook SetWaitableTimerSubHook;
void* SetWaitableTimerOriginalAddress;
void* SetWaitableTimerHookAddress;



bool OverclockerIsActive = false;
static std::mutex OverclockerMutex;
DWORD OriginalClock = 0;
DWORD OriginalTime = 0;
LONGLONG OriginalPerformanceCount = 0;
ULARGE_INTEGER OriginalFileTime = ULARGE_INTEGER();
ULARGE_INTEGER OriginalPreciseFileTime = ULARGE_INTEGER();

bool GetTickCountHookInfoTrigger = true;
DWORD __stdcall GetTickCountHook()
{
	std::lock_guard<std::mutex> lock(OverclockerMutex);

	GetTickCountSubHook.Remove();

	if (GetTickCountHookInfoTrigger)
	{
		DebugConsoleOutput("Using GetTickCount()", true, "yellow");
		GetTickCountHookInfoTrigger = false;
	}

	DWORD result = pGetTickCount();
	
	return result + ((result - OriginalClock) * 4);
}

bool QueryPerformanceCounterHookInfoTrigger = true;
BOOL __stdcall QueryPerformanceCounterHook(LARGE_INTEGER* lpPerformanceCount)
{
	std::lock_guard<std::mutex> lock(OverclockerMutex);

	QueryPerformanceCounterSubHook.Remove();

	if (QueryPerformanceCounterHookInfoTrigger)
	{
		DebugConsoleOutput("Using QueryPerformanceCounter()", true, "yellow");
		QueryPerformanceCounterHookInfoTrigger = false;
	}

	LONGLONG CurrentPerformanceCount;
	BOOL result = pQueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentPerformanceCount));
	if (!result) return FALSE;

	LONGLONG DeltaTime = CurrentPerformanceCount + ((CurrentPerformanceCount - OriginalPerformanceCount) * 4);
	*lpPerformanceCount = *reinterpret_cast<LARGE_INTEGER*>(&DeltaTime);

	return TRUE;
}

bool QueryPerformanceFrequencyHookInfoTrigger = true;
BOOL __stdcall QueryPerformanceFrequencyHook(LARGE_INTEGER* lpFrequency)
{
	std::lock_guard<std::mutex> lock(OverclockerMutex);

	QueryPerformanceFrequencySubHook.Remove();

	if (QueryPerformanceFrequencyHookInfoTrigger)
	{
		DebugConsoleOutput("Using QueryPerformanceFrequency()", true, "yellow");
		QueryPerformanceFrequencyHookInfoTrigger = false;
	}

	BOOL result = pQueryPerformanceFrequency(lpFrequency);

	if (result) lpFrequency->QuadPart *= 4;

	return result;
}

bool timeGetTimeHookInfoTrigger = true;
DWORD __stdcall timeGetTimeHook()
{
	std::lock_guard<std::mutex> lock(OverclockerMutex);

	TimeGetTimeSubHook.Remove();

	if (timeGetTimeHookInfoTrigger)
	{
		DebugConsoleOutput("Using timeGetTime()", true, "yellow");
		timeGetTimeHookInfoTrigger = false;
	}

	DWORD result = pTimeGetTime();

	return OriginalTime + ((result - OriginalTime) * 4);
}

bool GetSystemTimeAsFileTimeHookInfoTrigger = true;
void __stdcall GetSystemTimeAsFileTimeHook(LPFILETIME lpSystemTimeAsFileTime)
{
	std::lock_guard<std::mutex> lock(OverclockerMutex);

	GetSystemTimeAsFileTimeSubHook.Remove();

	if (GetSystemTimeAsFileTimeHookInfoTrigger)
	{
		DebugConsoleOutput("Using GetSystemTimeAsFileTime()", true, "yellow");
		GetSystemTimeAsFileTimeHookInfoTrigger = false;
	}

	pGetSystemTimeAsFileTime(lpSystemTimeAsFileTime);

	ULARGE_INTEGER FileTimer;
	FileTimer.LowPart = lpSystemTimeAsFileTime->dwLowDateTime;
	FileTimer.HighPart = lpSystemTimeAsFileTime->dwHighDateTime;
	FileTimer.QuadPart += (FileTimer.QuadPart - OriginalFileTime.QuadPart) * 4;
	lpSystemTimeAsFileTime->dwLowDateTime = FileTimer.LowPart;
	lpSystemTimeAsFileTime->dwHighDateTime = FileTimer.HighPart;

}

bool GetSystemTimePreciseAsFileTimeHookInfoTrigger = true;
void __stdcall GetSystemTimePreciseAsFileTimeHook(LPFILETIME lpSystemTimeAsFileTime)
{
	std::lock_guard<std::mutex> lock(OverclockerMutex);

	GetSystemTimePreciseAsFileTimeSubHook.Remove();

	if (GetSystemTimePreciseAsFileTimeHookInfoTrigger)
	{
		DebugConsoleOutput("Using GetSystemTimePreciseAsFileTime()", true, "yellow");
		GetSystemTimePreciseAsFileTimeHookInfoTrigger = false;
	}

	pGetSystemTimePreciseAsFileTime(lpSystemTimeAsFileTime);
	ULARGE_INTEGER PreciseFileTimer;
	PreciseFileTimer.LowPart = lpSystemTimeAsFileTime->dwLowDateTime;
	PreciseFileTimer.HighPart = lpSystemTimeAsFileTime->dwHighDateTime;
	PreciseFileTimer.QuadPart += (PreciseFileTimer.QuadPart - OriginalPreciseFileTime.QuadPart) * 4;
	lpSystemTimeAsFileTime->dwLowDateTime = PreciseFileTimer.LowPart;
	lpSystemTimeAsFileTime->dwHighDateTime = PreciseFileTimer.HighPart;
}

/*
bool CreateWaitableTimerAHookInfoTrigger = true;
HANDLE __stdcall CreateWaitableTimerAHook(LPSECURITY_ATTRIBUTES lpTimerAttributes, BOOL bManualReset, LPCSTR lpTimerName)
{
	std::lock_guard<std::mutex> lock(OverclockerMutex);

	CreateWaitableTimerASubHook.Remove();

	if (CreateWaitableTimerAHookInfoTrigger)
	{
		DebugConsoleOutput("Using CreateWaitableTimerA()", true, "yellow");
		CreateWaitableTimerAHookInfoTrigger = false;
	}

	HANDLE result = pCreateWaitableTimerA(lpTimerAttributes, bManualReset, lpTimerName);

	return result;
}

bool CreateWaitableTimerWHookInfoTrigger = true;
HANDLE __stdcall CreateWaitableTimerWHook(LPSECURITY_ATTRIBUTES lpTimerAttributes, BOOL bManualReset, LPCWSTR lpTimerName)
{
	std::lock_guard<std::mutex> lock(OverclockerMutex);

	CreateWaitableTimerWSubHook.Remove();

	if (CreateWaitableTimerWHookInfoTrigger)
	{
		DebugConsoleOutput("Using CreateWaitableTimerW()", true, "yellow");
		CreateWaitableTimerWHookInfoTrigger = false;
	}

	HANDLE result = pCreateWaitableTimerW(lpTimerAttributes, bManualReset, lpTimerName);

	return result;
}
*/

bool SetWaitableTimerHookInfoTrigger = true;
BOOL __stdcall SetWaitableTimerHook(HANDLE hTimer, const LARGE_INTEGER* pDueTime, LONG lPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, LPVOID lpArgToCompletionRoutine, BOOL fResume)
{
	std::lock_guard<std::mutex> lock(OverclockerMutex);

	SetWaitableTimerSubHook.Remove();

	if (SetWaitableTimerHookInfoTrigger)
	{
		DebugConsoleOutput("Using SetWaitableTimer()", true, "yellow");
		SetWaitableTimerHookInfoTrigger = false;
	}

	LARGE_INTEGER ModifiedDueTime;
	ModifiedDueTime.QuadPart = pDueTime->QuadPart / 4;
	LONG ModifiedPeriod = lPeriod / 4;

	BOOL result = pSetWaitableTimer(hTimer, pDueTime, lPeriod, pfnCompletionRoutine, lpArgToCompletionRoutine, fResume);

	return result;
}

bool InitOverclocker()
{
	// Init variables
	OriginalClock = GetTickCount();
	OriginalTime = timeGetTime();
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&OriginalPerformanceCount));
	GetSystemTimeAsFileTime((LPFILETIME)&OriginalFileTime);
	GetSystemTimePreciseAsFileTime((LPFILETIME)&OriginalPreciseFileTime);

	SuspendOtherThreads();
	Sleep(100);

	// Detect the module handles
	HMODULE Kernel32DLLHandle = GetModuleHandleA("Kernel32.dll");
	if (Kernel32DLLHandle != NULL)
	{
		// Set the hook addresses
		GetTickCountOriginalAddress = (void*)GetProcAddress(Kernel32DLLHandle, "GetTickCount");
		GetTickCountHookAddress = (void*)GetTickCountHook;
		pGetTickCount = (GetTickCountT)GetTickCountOriginalAddress;
		if (sizeof(void*) == 8) GetTickCountSubHook.Install(GetTickCountOriginalAddress, GetTickCountHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetTickCountSubHook.Install(GetTickCountOriginalAddress, GetTickCountHookAddress);

		QueryPerformanceCounterOriginalAddress = (void*)GetProcAddress(Kernel32DLLHandle, "QueryPerformanceCounter");
		QueryPerformanceCounterHookAddress = (void*)QueryPerformanceCounterHook;
		pQueryPerformanceCounter = (QueryPerformanceCounterT)QueryPerformanceCounterOriginalAddress;
		if (sizeof(void*) == 8) QueryPerformanceCounterSubHook.Install(QueryPerformanceCounterOriginalAddress, QueryPerformanceCounterHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) QueryPerformanceCounterSubHook.Install(QueryPerformanceCounterOriginalAddress, QueryPerformanceCounterHookAddress);

		QueryPerformanceFrequencyOriginalAddress = (void*)GetProcAddress(Kernel32DLLHandle, "QueryPerformanceFrequency");
		QueryPerformanceFrequencyHookAddress = (void*)QueryPerformanceFrequencyHook;
		pQueryPerformanceFrequency = (QueryPerformanceFrequencyT)QueryPerformanceFrequencyOriginalAddress;
		if (sizeof(void*) == 8) QueryPerformanceFrequencySubHook.Install(QueryPerformanceFrequencyOriginalAddress, QueryPerformanceFrequencyHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) QueryPerformanceFrequencySubHook.Install(QueryPerformanceFrequencyOriginalAddress, QueryPerformanceFrequencyHookAddress);

		GetSystemTimeAsFileTimeOriginalAddress = (void*)GetProcAddress(Kernel32DLLHandle, "GetSystemTimeAsFileTime");
		GetSystemTimeAsFileTimeHookAddress = (void*)GetSystemTimeAsFileTimeHook;
		pGetSystemTimeAsFileTime = (GetSystemTimeAsFileTimeT)GetSystemTimeAsFileTimeOriginalAddress;
		if (sizeof(void*) == 8) GetSystemTimeAsFileTimeSubHook.Install(GetSystemTimeAsFileTimeOriginalAddress, GetSystemTimeAsFileTimeHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetSystemTimeAsFileTimeSubHook.Install(GetSystemTimeAsFileTimeOriginalAddress, GetSystemTimeAsFileTimeHookAddress);

		GetSystemTimePreciseAsFileTimeOriginalAddress = (void*)GetProcAddress(Kernel32DLLHandle, "GetSystemTimePreciseAsFileTime");
		GetSystemTimePreciseAsFileTimeHookAddress = (void*)GetSystemTimePreciseAsFileTimeHook;
		pGetSystemTimePreciseAsFileTime = (GetSystemTimePreciseAsFileTimeT)GetSystemTimePreciseAsFileTimeOriginalAddress;
		if (sizeof(void*) == 8) GetSystemTimePreciseAsFileTimeSubHook.Install(GetSystemTimePreciseAsFileTimeOriginalAddress, GetSystemTimePreciseAsFileTimeHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetSystemTimePreciseAsFileTimeSubHook.Install(GetSystemTimePreciseAsFileTimeOriginalAddress, GetSystemTimePreciseAsFileTimeHookAddress);

		/*
		CreateWaitableTimerAOriginalAddress = (void*)GetProcAddress(Kernel32DLLHandle, "CreateWaitableTimerA");
		CreateWaitableTimerAHookAddress = (void*)CreateWaitableTimerAHook;
		pCreateWaitableTimerA = (CreateWaitableTimerAT)CreateWaitableTimerAOriginalAddress;
		if (sizeof(void*) == 8) CreateWaitableTimerASubHook.Install(CreateWaitableTimerAOriginalAddress, CreateWaitableTimerAHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) CreateWaitableTimerASubHook.Install(CreateWaitableTimerAOriginalAddress, CreateWaitableTimerAHookAddress);

		CreateWaitableTimerWOriginalAddress = (void*)GetProcAddress(Kernel32DLLHandle, "CreateWaitableTimerW");
		CreateWaitableTimerWHookAddress = (void*)CreateWaitableTimerWHook;
		pCreateWaitableTimerW = (CreateWaitableTimerWT)CreateWaitableTimerWOriginalAddress;
		if (sizeof(void*) == 8) CreateWaitableTimerWSubHook.Install(CreateWaitableTimerWOriginalAddress, CreateWaitableTimerWHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) CreateWaitableTimerWSubHook.Install(CreateWaitableTimerWOriginalAddress, CreateWaitableTimerWHookAddress);
		*/

		SetWaitableTimerOriginalAddress = (void*)GetProcAddress(Kernel32DLLHandle, "SetWaitableTimer");
		SetWaitableTimerHookAddress = (void*)SetWaitableTimerHook;
		pSetWaitableTimer = (SetWaitableTimerT)SetWaitableTimerOriginalAddress;
		if (sizeof(void*) == 8) SetWaitableTimerSubHook.Install(SetWaitableTimerOriginalAddress, SetWaitableTimerHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) SetWaitableTimerSubHook.Install(SetWaitableTimerOriginalAddress, SetWaitableTimerHookAddress);

	}

	HMODULE winmmDLLHandle = GetModuleHandleA("winmm.dll");
	if (winmmDLLHandle != NULL)
	{
		// Set the hook addresses
		TimeGetTimeOriginalAddress = (void*)GetProcAddress(winmmDLLHandle, "timeGetTime");
		TimeGetTimeHookAddress = (void*)timeGetTimeHook;
		pTimeGetTime = (timeGetTimeT)TimeGetTimeOriginalAddress;
		if (sizeof(void*) == 8) TimeGetTimeSubHook.Install(TimeGetTimeOriginalAddress, TimeGetTimeHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) TimeGetTimeSubHook.Install(TimeGetTimeOriginalAddress, TimeGetTimeHookAddress);

	}

	OverclockerIsActive = true;

	ResumeOtherThreads();

	return true;
}

void UninitOverclocker()
{
	while (true)
	{
		std::lock_guard<std::mutex> lock(OverclockerMutex);

		SuspendOtherThreads();
		Sleep(50);

		bool deactivate = true;

		if (GetTickCountSubHook.IsInstalled())
		{
			GetTickCountSubHook.Remove();
			deactivate = false;
		}
		if (QueryPerformanceCounterSubHook.IsInstalled())
		{
			QueryPerformanceCounterSubHook.Remove();
			deactivate = false;
		}
		if (QueryPerformanceFrequencySubHook.IsInstalled())
		{
			QueryPerformanceFrequencySubHook.Remove();
			deactivate = false;
		}
		if (GetSystemTimeAsFileTimeSubHook.IsInstalled())
		{
			GetSystemTimeAsFileTimeSubHook.Remove();
			deactivate = false;
		}
		if (GetSystemTimePreciseAsFileTimeSubHook.IsInstalled())
		{
			GetSystemTimePreciseAsFileTimeSubHook.Remove();
			deactivate = false;
		}
		/*
		if (CreateWaitableTimerASubHook.IsInstalled())
		{
			CreateWaitableTimerASubHook.Remove();
			deactivate = false;
		}
		if (CreateWaitableTimerWSubHook.IsInstalled())
		{
			CreateWaitableTimerWSubHook.Remove();
			deactivate = false;
		}
		*/
		if (SetWaitableTimerSubHook.IsInstalled())
		{
			SetWaitableTimerSubHook.Remove();
			deactivate = false;
		}
		if (TimeGetTimeSubHook.IsInstalled())
		{
			TimeGetTimeSubHook.Remove();
			deactivate = false;
		}

		ResumeOtherThreads();
		Sleep(50);

		if (deactivate) break;
	}

	OverclockerIsActive = false;
}
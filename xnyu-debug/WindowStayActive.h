#pragma once

bool WindowStayActiveMode = false;

// Global hook settings
typedef HWND(__stdcall* GetForegroundWindowT)();
GetForegroundWindowT pGetForegroundWindow = nullptr;
subhook::Hook GetForegroundWindowSubHook;
void* GetForegroundWindowOriginalAddress;
void* GetForegroundWindowHookAddress;
bool GetForegroundWindowReal = false;

typedef HWND(__stdcall* GetActiveWindowT)();
GetActiveWindowT pGetActiveWindow = nullptr;
subhook::Hook GetActiveWindowSubHook;
void* GetActiveWindowOriginalAddress;
void* GetActiveWindowHookAddress;
bool GetActiveWindowReal = false;

typedef HWND(__stdcall* GetFocusT)();
GetFocusT pGetFocus = nullptr;
subhook::Hook GetFocusSubHook;
void* GetFocusOriginalAddress;
void* GetFocusHookAddress;
bool GetFocusReal = false;

typedef BOOL(__stdcall* IsWindowEnabledT)(HWND hWnd);
IsWindowEnabledT pIsWindowEnabled = nullptr;
subhook::Hook IsWindowEnabledSubHook;
void* IsWindowEnabledOriginalAddress;
void* IsWindowEnabledHookAddress;
bool IsWindowEnabledReal = false;

typedef BOOL(__stdcall* IsWindowVisibleT)(HWND hWnd);
IsWindowVisibleT pIsWindowVisible = nullptr;
subhook::Hook IsWindowVisibleSubHook;
void* IsWindowVisibleOriginalAddress;
void* IsWindowVisibleHookAddress;
bool IsWindowVisibleReal = false;

typedef BOOL(__stdcall* IsIconicT)(HWND hWnd);
IsIconicT pIsIconic = nullptr;
subhook::Hook IsIconicSubHook;
void* IsIconicOriginalAddress;
void* IsIconicHookAddress;
bool IsIconicReal = false;

typedef BOOL(__stdcall* ShowWindowT)(HWND hWnd, int nCmdShow);
ShowWindowT pShowWindow = nullptr;
subhook::Hook ShowWindowSubHook;
void* ShowWindowOriginalAddress;
void* ShowWindowHookAddress;
bool ShowWindowReal = false;

typedef HWND(__stdcall* GetWindowT)(HWND hWnd, UINT uCmd);
GetWindowT pGetWindow = nullptr;
subhook::Hook GetWindowSubHook;
void* GetWindowOriginalAddress;
void* GetWindowHookAddress;
bool GetWindowReal = false;

typedef DWORD(__stdcall* GetWindowThreadProcessIdT)(HWND hWnd, LPDWORD lpdwProcessId);
GetWindowThreadProcessIdT pGetWindowThreadProcessId = nullptr;
subhook::Hook GetWindowThreadProcessIdSubHook;
void* GetWindowThreadProcessIdOriginalAddress;
void* GetWindowThreadProcessIdHookAddress;
bool GetWindowThreadProcessIdReal = false;
DWORD currentThreadId = 0;
DWORD currentProcessId = 0;

typedef BOOL(__stdcall* EnumWindowsT)(WNDENUMPROC lpEnumFunc, LPARAM lParam);
EnumWindowsT pEnumWindows = nullptr;
subhook::Hook EnumWindowsSubHook;
void* EnumWindowsOriginalAddress;
void* EnumWindowsHookAddress;
bool EnumWindowsReal = false;

HWND __stdcall GetForegroundWindowHook()
{
	if (GetForegroundWindowReal)
	{
		GetForegroundWindowSubHook.Remove();

		GetForegroundWindowReal = false;

		HWND result = pGetForegroundWindow();

		if (sizeof(void*) == 8) GetForegroundWindowSubHook.Install(GetForegroundWindowOriginalAddress, GetForegroundWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetForegroundWindowSubHook.Install(GetForegroundWindowOriginalAddress, GetForegroundWindowHookAddress);

		return result;
	}

	return MainWindowHandle;
}

HWND __stdcall GetActiveWindowHook()
{
	if (GetActiveWindowReal)
	{
		GetActiveWindowSubHook.Remove();

		GetActiveWindowReal = false;

		HWND result = pGetActiveWindow();

		if (sizeof(void*) == 8) GetActiveWindowSubHook.Install(GetActiveWindowOriginalAddress, GetActiveWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetActiveWindowSubHook.Install(GetActiveWindowOriginalAddress, GetActiveWindowHookAddress);

		return result;
	}

	return MainWindowHandle;
}

HWND __stdcall GetFocusHook()
{
	if (GetFocusReal)
	{
		GetFocusSubHook.Remove();

		GetFocusReal = false;

		HWND result = pGetFocus();

		if (sizeof(void*) == 8) GetFocusSubHook.Install(GetFocusOriginalAddress, GetFocusHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetFocusSubHook.Install(GetFocusOriginalAddress, GetFocusHookAddress);

		return result;
	}

	return MainWindowHandle;
}

BOOL __stdcall IsWindowEnabledHook(HWND hWnd)
{
	if (IsWindowEnabledReal)
	{
		IsWindowEnabledSubHook.Remove();

		IsWindowEnabledReal = false;

		BOOL result = pIsWindowEnabled(hWnd);

		if (sizeof(void*) == 8) IsWindowEnabledSubHook.Install(IsWindowEnabledOriginalAddress, IsWindowEnabledHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) IsWindowEnabledSubHook.Install(IsWindowEnabledOriginalAddress, IsWindowEnabledHookAddress);

		return result;
	}

	return true;
}

BOOL __stdcall IsWindowVisibleHook(HWND hWnd)
{
	if (IsWindowVisibleReal)
	{
		IsWindowVisibleSubHook.Remove();

		IsWindowVisibleReal = false;

		BOOL result = pIsWindowVisible(hWnd);

		if (sizeof(void*) == 8) IsWindowVisibleSubHook.Install(IsWindowVisibleOriginalAddress, IsWindowVisibleHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) IsWindowVisibleSubHook.Install(IsWindowVisibleOriginalAddress, IsWindowVisibleHookAddress);

		return result;
	}

	return true;
}

BOOL __stdcall IsIconicHook(HWND hWnd)
{
	if (IsIconicReal)
	{
		IsIconicSubHook.Remove();

		IsIconicReal = false;

		BOOL result = pIsIconic(hWnd);

		if (sizeof(void*) == 8) IsIconicSubHook.Install(IsIconicOriginalAddress, IsIconicHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) IsIconicSubHook.Install(IsIconicOriginalAddress, IsIconicHookAddress);

		return result;
	}

	return false;
}

BOOL __stdcall ShowWindowHook(HWND hWnd, int nCmdShow)
{
	ShowWindowSubHook.Remove();

	if (ShowWindowReal)
	{

		ShowWindowReal = false;

		BOOL result = pShowWindow(hWnd, SW_SHOW);

		if (sizeof(void*) == 8) ShowWindowSubHook.Install(ShowWindowOriginalAddress, ShowWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) ShowWindowSubHook.Install(ShowWindowOriginalAddress, ShowWindowHookAddress);

		return true;
	}

	BOOL result = pShowWindow(hWnd, SW_SHOW);

	if (sizeof(void*) == 8) ShowWindowSubHook.Install(ShowWindowOriginalAddress, ShowWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) ShowWindowSubHook.Install(ShowWindowOriginalAddress, ShowWindowHookAddress);

	return true;
}

HWND __stdcall GetWindowHook(HWND hWnd, UINT uCmd)
{
	if (GetWindowReal)
	{
		GetWindowSubHook.Remove();

		GetWindowReal = false;

		HWND result = pGetWindow(hWnd, uCmd);

		if (sizeof(void*) == 8) GetWindowSubHook.Install(GetWindowOriginalAddress, GetWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetWindowSubHook.Install(GetWindowOriginalAddress, GetWindowHookAddress);

		return result;
	}

	return MainWindowHandle;
}

DWORD __stdcall GetWindowThreadProcessIdHook(HWND hWnd, LPDWORD lpdwProcessId)
{
	if (GetWindowThreadProcessIdReal)
	{
		GetWindowThreadProcessIdSubHook.Remove();

		GetWindowThreadProcessIdReal = false;

		DWORD result = pGetWindowThreadProcessId(hWnd, lpdwProcessId);

		if (sizeof(void*) == 8) GetWindowThreadProcessIdSubHook.Install(GetWindowThreadProcessIdOriginalAddress, GetWindowThreadProcessIdHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetWindowThreadProcessIdSubHook.Install(GetWindowThreadProcessIdOriginalAddress, GetWindowThreadProcessIdHookAddress);

		return result;
	}

	return currentThreadId;
}

BOOL __stdcall EnumWindowsHook(WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
	if (EnumWindowsReal)
	{
		EnumWindowsSubHook.Remove();

		EnumWindowsReal = false;

		BOOL result = pEnumWindows(lpEnumFunc, lParam);

		if (sizeof(void*) == 8) EnumWindowsSubHook.Install(EnumWindowsOriginalAddress, EnumWindowsHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) EnumWindowsSubHook.Install(EnumWindowsOriginalAddress, GetForegroundWindowHookAddress);

		return result;
	}

	return false;
}

bool InitWindowStayActive()
{
	WindowStayActiveMode = true;
	currentThreadId = GetCurrentThreadId();
	currentProcessId = GetCurrentProcessId();

	// Detect the XInput module handle
	HMODULE User32DLLHandle = GetModuleHandleA("User32.dll");
	if (User32DLLHandle == NULL) return false;

	// Set the hook addresses
	GetForegroundWindowOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "GetForegroundWindow");
	GetForegroundWindowHookAddress = (void*)GetForegroundWindowHook;
	pGetForegroundWindow = (GetForegroundWindowT)GetForegroundWindowOriginalAddress;
	if (sizeof(void*) == 8) GetForegroundWindowSubHook.Install(GetForegroundWindowOriginalAddress, GetForegroundWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) GetForegroundWindowSubHook.Install(GetForegroundWindowOriginalAddress, GetForegroundWindowHookAddress);

	GetActiveWindowOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "GetActiveWindow");
	GetActiveWindowHookAddress = (void*)GetActiveWindowHook;
	pGetActiveWindow = (GetActiveWindowT)GetActiveWindowOriginalAddress;
	if (sizeof(void*) == 8) GetActiveWindowSubHook.Install(GetActiveWindowOriginalAddress, GetActiveWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) GetActiveWindowSubHook.Install(GetActiveWindowOriginalAddress, GetActiveWindowHookAddress);

	GetFocusOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "GetFocus");
	GetFocusHookAddress = (void*)GetFocusHook;
	pGetFocus = (GetFocusT)GetFocusOriginalAddress;
	if (sizeof(void*) == 8) GetFocusSubHook.Install(GetFocusOriginalAddress, GetFocusHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) GetFocusSubHook.Install(GetFocusOriginalAddress, GetFocusHookAddress);

	IsWindowEnabledOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "IsWindowEnabled");
	IsWindowEnabledHookAddress = (void*)IsWindowEnabledHook;
	pIsWindowEnabled = (IsWindowEnabledT)IsWindowEnabledOriginalAddress;
	if (sizeof(void*) == 8) IsWindowEnabledSubHook.Install(IsWindowEnabledOriginalAddress, IsWindowEnabledHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) IsWindowEnabledSubHook.Install(IsWindowEnabledOriginalAddress, IsWindowEnabledHookAddress);

	IsWindowVisibleOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "IsWindowVisible");
	IsWindowVisibleHookAddress = (void*)IsWindowVisibleHook;
	pIsWindowVisible = (IsWindowVisibleT)IsWindowVisibleOriginalAddress;
	if (sizeof(void*) == 8) IsWindowVisibleSubHook.Install(IsWindowVisibleOriginalAddress, IsWindowVisibleHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) IsWindowVisibleSubHook.Install(IsWindowVisibleOriginalAddress, IsWindowVisibleHookAddress);

	IsIconicOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "IsIconic");
	IsIconicHookAddress = (void*)IsIconicHook;
	pIsIconic = (IsIconicT)IsIconicOriginalAddress;
	if (sizeof(void*) == 8) IsIconicSubHook.Install(IsIconicOriginalAddress, IsIconicHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) IsIconicSubHook.Install(IsIconicOriginalAddress, IsIconicHookAddress);

	ShowWindowOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "ShowWindow");
	ShowWindowHookAddress = (void*)ShowWindowHook;
	pShowWindow = (ShowWindowT)ShowWindowOriginalAddress;
	if (sizeof(void*) == 8) ShowWindowSubHook.Install(ShowWindowOriginalAddress, ShowWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) ShowWindowSubHook.Install(ShowWindowOriginalAddress, ShowWindowHookAddress);

	GetWindowOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "GetWindow");
	GetWindowHookAddress = (void*)GetWindowHook;
	pGetWindow = (GetWindowT)GetWindowOriginalAddress;
	if (sizeof(void*) == 8) GetWindowSubHook.Install(GetWindowOriginalAddress, GetWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) GetWindowSubHook.Install(GetWindowOriginalAddress, GetWindowHookAddress);

	GetWindowThreadProcessIdOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "GetWindowThreadProcessId");
	GetWindowThreadProcessIdHookAddress = (void*)GetWindowThreadProcessIdHook;
	pGetWindowThreadProcessId = (GetWindowThreadProcessIdT)GetWindowThreadProcessIdOriginalAddress;
	if (sizeof(void*) == 8) GetWindowThreadProcessIdSubHook.Install(GetWindowThreadProcessIdOriginalAddress, GetWindowThreadProcessIdHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) GetWindowThreadProcessIdSubHook.Install(GetWindowThreadProcessIdOriginalAddress, GetWindowThreadProcessIdHookAddress);

	EnumWindowsOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "EnumWindows");
	EnumWindowsHookAddress = (void*)EnumWindowsHook;
	pEnumWindows = (EnumWindowsT)EnumWindowsOriginalAddress;
	if (sizeof(void*) == 8) EnumWindowsSubHook.Install(EnumWindowsOriginalAddress, EnumWindowsHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) EnumWindowsSubHook.Install(EnumWindowsOriginalAddress, EnumWindowsHookAddress);

}

void UninitWindowStayActive()
{
	WindowStayActiveMode = false;
	if (GetForegroundWindowSubHook.IsInstalled()) GetForegroundWindowSubHook.Remove();
	if (GetActiveWindowSubHook.IsInstalled()) GetActiveWindowSubHook.Remove();
	if (GetFocusSubHook.IsInstalled()) GetFocusSubHook.Remove();
	if (IsWindowEnabledSubHook.IsInstalled()) IsWindowEnabledSubHook.Remove();
	if (IsWindowVisibleSubHook.IsInstalled()) IsWindowVisibleSubHook.Remove();
	if (IsIconicSubHook.IsInstalled()) IsIconicSubHook.Remove();
	if (ShowWindowSubHook.IsInstalled()) ShowWindowSubHook.Remove();
	if (GetWindowSubHook.IsInstalled()) GetWindowSubHook.Remove();
	if (GetWindowThreadProcessIdSubHook.IsInstalled()) GetWindowThreadProcessIdSubHook.Remove();
	if (EnumWindowsSubHook.IsInstalled()) EnumWindowsSubHook.Remove();
}



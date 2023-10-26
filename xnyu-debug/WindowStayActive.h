#pragma once

bool WindowStayActiveMode = false;

// Global hook settings
typedef HWND(__stdcall* GetForegroundWindowT)();
GetForegroundWindowT pGetForegroundWindow = nullptr;
subhook::Hook GetForegroundWindowSubHook;
void* GetForegroundWindowOriginalAddress;
void* GetForegroundWindowHookAddress;
bool GetForegroundWindowReal = false;
HANDLE pGetForegroundWindowMutex = CreateMutex(NULL, FALSE, NULL);

typedef HWND(__stdcall* GetActiveWindowT)();
GetActiveWindowT pGetActiveWindow = nullptr;
subhook::Hook GetActiveWindowSubHook;
void* GetActiveWindowOriginalAddress;
void* GetActiveWindowHookAddress;
bool GetActiveWindowReal = false;
HANDLE pGetActiveWindowMutex = CreateMutex(NULL, FALSE, NULL);

typedef HWND(__stdcall* GetFocusT)();
GetFocusT pGetFocus = nullptr;
subhook::Hook GetFocusSubHook;
void* GetFocusOriginalAddress;
void* GetFocusHookAddress;
bool GetFocusReal = false;
HANDLE pGetFocusMutex = CreateMutex(NULL, FALSE, NULL);

typedef BOOL(__stdcall* IsWindowEnabledT)(HWND hWnd);
IsWindowEnabledT pIsWindowEnabled = nullptr;
subhook::Hook IsWindowEnabledSubHook;
void* IsWindowEnabledOriginalAddress;
void* IsWindowEnabledHookAddress;
bool IsWindowEnabledReal = false;
HANDLE pIsWindowEnabledMutex = CreateMutex(NULL, FALSE, NULL);

typedef BOOL(__stdcall* IsWindowVisibleT)(HWND hWnd);
IsWindowVisibleT pIsWindowVisible = nullptr;
subhook::Hook IsWindowVisibleSubHook;
void* IsWindowVisibleOriginalAddress;
void* IsWindowVisibleHookAddress;
bool IsWindowVisibleReal = false;
HANDLE pIsWindowVisibleMutex = CreateMutex(NULL, FALSE, NULL);

typedef BOOL(__stdcall* IsIconicT)(HWND hWnd);
IsIconicT pIsIconic = nullptr;
subhook::Hook IsIconicSubHook;
void* IsIconicOriginalAddress;
void* IsIconicHookAddress;
bool IsIconicReal = false;
HANDLE pIsIconicMutex = CreateMutex(NULL, FALSE, NULL);

typedef BOOL(__stdcall* ShowWindowT)(HWND hWnd, int nCmdShow);
ShowWindowT pShowWindow = nullptr;
subhook::Hook ShowWindowSubHook;
void* ShowWindowOriginalAddress;
void* ShowWindowHookAddress;
bool ShowWindowReal = false;
HANDLE pShowWindowMutex = CreateMutex(NULL, FALSE, NULL);

typedef HWND(__stdcall* GetWindowT)(HWND hWnd, UINT uCmd);
GetWindowT pGetWindow = nullptr;
subhook::Hook GetWindowSubHook;
void* GetWindowOriginalAddress;
void* GetWindowHookAddress;
bool GetWindowReal = false;
HANDLE pGetWindowMutex = CreateMutex(NULL, FALSE, NULL);

typedef DWORD(__stdcall* GetWindowThreadProcessIdT)(HWND hWnd, LPDWORD lpdwProcessId);
GetWindowThreadProcessIdT pGetWindowThreadProcessId = nullptr;
subhook::Hook GetWindowThreadProcessIdSubHook;
void* GetWindowThreadProcessIdOriginalAddress;
void* GetWindowThreadProcessIdHookAddress;
bool GetWindowThreadProcessIdReal = false;
DWORD currentThreadId = 0;
DWORD currentProcessId = 0;
HANDLE pGetWindowThreadProcessIdMutex = CreateMutex(NULL, FALSE, NULL);

typedef BOOL(__stdcall* EnumWindowsT)(WNDENUMPROC lpEnumFunc, LPARAM lParam);
EnumWindowsT pEnumWindows = nullptr;
subhook::Hook EnumWindowsSubHook;
void* EnumWindowsOriginalAddress;
void* EnumWindowsHookAddress;
bool EnumWindowsReal = false;
HANDLE pEnumWindowsMutex = CreateMutex(NULL, FALSE, NULL);

typedef LRESULT(__stdcall* DispatchMessageAT)(const MSG* lpMsg);
DispatchMessageAT pDispatchMessageA = nullptr;
subhook::Hook DispatchMessageASubhook;
void* DispatchMessageAOriginalAddress;
void* DispatchMessageAHookAddress;
HANDLE pDispatchMessageAMutex = CreateMutex(NULL, FALSE, NULL);

typedef LRESULT(__stdcall* DispatchMessageWT)(const MSG* lpMsg);
DispatchMessageWT pDispatchMessageW = nullptr;
subhook::Hook DispatchMessageWSubhook;
void* DispatchMessageWOriginalAddress;
void* DispatchMessageWHookAddress;
HANDLE pDispatchMessageWMutex = CreateMutex(NULL, FALSE, NULL);

typedef BOOL(__stdcall* PeekMessageAT)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
PeekMessageAT pPeekMessageA = nullptr;
subhook::Hook PeekMessageASubhook;
void* PeekMessageAOriginalAddress;
void* PeekMessageAHookAddress;
HANDLE pPeekMessageAMutex = CreateMutex(NULL, FALSE, NULL);

typedef BOOL(__stdcall* PeekMessageWT)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
PeekMessageWT pPeekMessageW = nullptr;
subhook::Hook PeekMessageWSubhook;
void* PeekMessageWOriginalAddress;
void* PeekMessageWHookAddress;
HANDLE pPeekMessageWMutex = CreateMutex(NULL, FALSE, NULL);

typedef BOOL(__stdcall* GetMessageAT)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
GetMessageAT pGetMessageA = nullptr;
subhook::Hook GetMessageASubhook;
void* GetMessageAOriginalAddress;
void* GetMessageAHookAddress;
HANDLE pGetMessageAMutex = CreateMutex(NULL, FALSE, NULL);

typedef BOOL(__stdcall* GetMessageWT)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
GetMessageWT pGetMessageW = nullptr;
subhook::Hook GetMessageWSubhook;
void* GetMessageWOriginalAddress;
void* GetMessageWHookAddress;
HANDLE pGetMessageWMutex = CreateMutex(NULL, FALSE, NULL);

typedef BOOL(__stdcall* ClipCursorT)(const RECT* lpRect);
ClipCursorT pClipCursor = nullptr;
subhook::Hook ClipCursorSubhook;
void* ClipCursorOriginalAddress = nullptr;
void* ClipCursorHookAddress = nullptr;
HANDLE pClipCursorMutex = CreateMutex(NULL, FALSE, NULL);

typedef SHORT(__stdcall* NtUserGetAsyncKeyStateT)(int vKey);
NtUserGetAsyncKeyStateT pNtUserGetAsyncKeyState = nullptr;
subhook::Hook NtUserGetAsyncKeyStateSubhook;
void* NtUserGetAsyncKeyStateOriginalAddress;
void* NtUserGetAsyncKeyStateHookAddress;
HANDLE pNtUserGetAsyncKeyStateMutex = CreateMutex(NULL, FALSE, NULL);

typedef SHORT(__stdcall* NtUserGetKeyStateT)(int nVirtKey);
NtUserGetKeyStateT pNtUserGetKeyState = nullptr;
subhook::Hook NtUserGetKeyStateSubhook;
void* NtUserGetKeyStateOriginalAddress;
void* NtUserGetKeyStateHookAddress;
HANDLE pNtUserGetKeyStateMutex = CreateMutex(NULL, FALSE, NULL);

typedef BOOL(__stdcall* GetLastInputInfoT)(PLASTINPUTINFO plii);
GetLastInputInfoT pGetLastInputInfo = nullptr;
subhook::Hook GetLastInputInfoSubhook;
void* GetLastInputInfoOriginalAddress;
void* GetLastInputInfoHookAddress;
HANDLE pGetLastInputInfoMutex = CreateMutex(NULL, FALSE, NULL);

HWND __stdcall GetForegroundWindowHook()
{
	WaitForSingleObject(pGetForegroundWindowMutex, INFINITE);

	if (GetForegroundWindowReal)
	{
		if (!GetForegroundWindowSubHook.IsInstalled()) return 0;
		GetForegroundWindowSubHook.Remove();

		GetForegroundWindowReal = false;

		HWND result = pGetForegroundWindow();

		if (sizeof(void*) == 8) GetForegroundWindowSubHook.Install(GetForegroundWindowOriginalAddress, GetForegroundWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetForegroundWindowSubHook.Install(GetForegroundWindowOriginalAddress, GetForegroundWindowHookAddress);

		ReleaseMutex(pGetForegroundWindowMutex);

		return result;
	}

	ReleaseMutex(pGetForegroundWindowMutex);

	return MainWindowHandle;
}

HWND __stdcall GetActiveWindowHook()
{
	WaitForSingleObject(pGetActiveWindowMutex, INFINITE);

	if (GetActiveWindowReal)
	{
		if (!GetActiveWindowSubHook.IsInstalled()) return 0;
		GetActiveWindowSubHook.Remove();

		GetActiveWindowReal = false;

		HWND result = pGetActiveWindow();

		if (sizeof(void*) == 8) GetActiveWindowSubHook.Install(GetActiveWindowOriginalAddress, GetActiveWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetActiveWindowSubHook.Install(GetActiveWindowOriginalAddress, GetActiveWindowHookAddress);

		ReleaseMutex(pGetActiveWindowMutex);

		return result;
	}

	ReleaseMutex(pGetActiveWindowMutex);

	return MainWindowHandle;
}

HWND __stdcall GetFocusHook()
{
	WaitForSingleObject(pGetFocusMutex, INFINITE);

	if (GetFocusReal)
	{
		if (!GetFocusSubHook.IsInstalled()) return 0;
		GetFocusSubHook.Remove();

		GetFocusReal = false;

		HWND result = pGetFocus();

		if (sizeof(void*) == 8) GetFocusSubHook.Install(GetFocusOriginalAddress, GetFocusHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetFocusSubHook.Install(GetFocusOriginalAddress, GetFocusHookAddress);

		ReleaseMutex(pGetFocusMutex);

		return result;
	}

	ReleaseMutex(pGetFocusMutex);

	return MainWindowHandle;
}

BOOL __stdcall IsWindowEnabledHook(HWND hWnd)
{
	WaitForSingleObject(pIsWindowEnabledMutex, INFINITE);

	if (IsWindowEnabledReal)
	{
		if (!IsWindowEnabledSubHook.IsInstalled()) return FALSE;
		IsWindowEnabledSubHook.Remove();

		IsWindowEnabledReal = false;

		BOOL result = pIsWindowEnabled(hWnd);

		if (sizeof(void*) == 8) IsWindowEnabledSubHook.Install(IsWindowEnabledOriginalAddress, IsWindowEnabledHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) IsWindowEnabledSubHook.Install(IsWindowEnabledOriginalAddress, IsWindowEnabledHookAddress);

		ReleaseMutex(pIsWindowEnabledMutex);

		return result;
	}

	ReleaseMutex(pIsWindowEnabledMutex);

	return true;
}

BOOL __stdcall IsWindowVisibleHook(HWND hWnd)
{
	WaitForSingleObject(pIsWindowVisibleMutex, INFINITE);

	if (IsWindowVisibleReal)
	{
		if (!IsWindowVisibleSubHook.IsInstalled()) return FALSE;
		IsWindowVisibleSubHook.Remove();

		IsWindowVisibleReal = false;

		BOOL result = pIsWindowVisible(hWnd);

		if (sizeof(void*) == 8) IsWindowVisibleSubHook.Install(IsWindowVisibleOriginalAddress, IsWindowVisibleHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) IsWindowVisibleSubHook.Install(IsWindowVisibleOriginalAddress, IsWindowVisibleHookAddress);

		ReleaseMutex(pIsWindowVisibleMutex);

		return result;
	}

	ReleaseMutex(pIsWindowVisibleMutex);

	return true;
}

BOOL __stdcall IsIconicHook(HWND hWnd)
{
	WaitForSingleObject(pIsIconicMutex, INFINITE);

	if (IsIconicReal)
	{
		if (!IsIconicSubHook.IsInstalled()) return FALSE;
		IsIconicSubHook.Remove();

		IsIconicReal = false;

		BOOL result = pIsIconic(hWnd);

		if (sizeof(void*) == 8) IsIconicSubHook.Install(IsIconicOriginalAddress, IsIconicHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) IsIconicSubHook.Install(IsIconicOriginalAddress, IsIconicHookAddress);

		ReleaseMutex(pIsIconicMutex);

		return result;
	}

	ReleaseMutex(pIsIconicMutex);

	return false;
}

BOOL __stdcall ShowWindowHook(HWND hWnd, int nCmdShow)
{
	WaitForSingleObject(pShowWindowMutex, INFINITE);

	if (!ShowWindowSubHook.IsInstalled()) return FALSE;
	ShowWindowSubHook.Remove();

	if (ShowWindowReal)
	{

		ShowWindowReal = false;

		BOOL result = pShowWindow(hWnd, SW_SHOW);

		if (sizeof(void*) == 8) ShowWindowSubHook.Install(ShowWindowOriginalAddress, ShowWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) ShowWindowSubHook.Install(ShowWindowOriginalAddress, ShowWindowHookAddress);

		ReleaseMutex(pShowWindowMutex);

		return true;
	}

	BOOL result = pShowWindow(hWnd, SW_SHOW);

	if (sizeof(void*) == 8) ShowWindowSubHook.Install(ShowWindowOriginalAddress, ShowWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) ShowWindowSubHook.Install(ShowWindowOriginalAddress, ShowWindowHookAddress);

	ReleaseMutex(pShowWindowMutex);

	return true;
}

HWND __stdcall GetWindowHook(HWND hWnd, UINT uCmd)
{
	WaitForSingleObject(pGetWindowMutex, INFINITE);

	if (GetWindowReal)
	{
		if (!GetWindowSubHook.IsInstalled()) return 0;
		GetWindowSubHook.Remove();

		GetWindowReal = false;

		HWND result = pGetWindow(hWnd, uCmd);

		if (sizeof(void*) == 8) GetWindowSubHook.Install(GetWindowOriginalAddress, GetWindowHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetWindowSubHook.Install(GetWindowOriginalAddress, GetWindowHookAddress);

		ReleaseMutex(pGetWindowMutex);

		return result;
	}

	ReleaseMutex(pGetWindowMutex);

	return MainWindowHandle;
}

DWORD __stdcall GetWindowThreadProcessIdHook(HWND hWnd, LPDWORD lpdwProcessId)
{
	WaitForSingleObject(pGetWindowThreadProcessIdMutex, INFINITE);

	if (GetWindowThreadProcessIdReal)
	{
		if (!GetWindowThreadProcessIdSubHook.IsInstalled()) return 0;
		GetWindowThreadProcessIdSubHook.Remove();

		GetWindowThreadProcessIdReal = false;

		DWORD result = pGetWindowThreadProcessId(hWnd, lpdwProcessId);

		if (sizeof(void*) == 8) GetWindowThreadProcessIdSubHook.Install(GetWindowThreadProcessIdOriginalAddress, GetWindowThreadProcessIdHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) GetWindowThreadProcessIdSubHook.Install(GetWindowThreadProcessIdOriginalAddress, GetWindowThreadProcessIdHookAddress);

		ReleaseMutex(pGetWindowThreadProcessIdMutex);

		return result;
	}

	ReleaseMutex(pGetWindowThreadProcessIdMutex);

	return currentThreadId;
}

BOOL __stdcall EnumWindowsHook(WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
	WaitForSingleObject(pEnumWindowsMutex, INFINITE);

	if (EnumWindowsReal)
	{
		if (!EnumWindowsSubHook.IsInstalled()) return FALSE;
		EnumWindowsSubHook.Remove();

		EnumWindowsReal = false;

		BOOL result = pEnumWindows(lpEnumFunc, lParam);

		if (sizeof(void*) == 8) EnumWindowsSubHook.Install(EnumWindowsOriginalAddress, EnumWindowsHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) EnumWindowsSubHook.Install(EnumWindowsOriginalAddress, GetForegroundWindowHookAddress);

		ReleaseMutex(pEnumWindowsMutex);

		return result;
	}

	ReleaseMutex(pEnumWindowsMutex);

	return false;
}

LRESULT __stdcall DispatchMessageAHook(const MSG* lpMsg)
{
	WaitForSingleObject(pDispatchMessageAMutex, INFINITE);

	// Remove hook to restore original function
	if (!DispatchMessageASubhook.IsInstalled()) return 0;
	DispatchMessageASubhook.Remove();

	bool blockMessage = false;
	LRESULT result = 0;

	if (lpMsg != NULL)
	{
		switch (lpMsg->message)
		{
		case WM_KILLFOCUS:
		case WM_ACTIVATEAPP:
		case WM_NCACTIVATE:
		case WM_SETFOCUS:
		case WM_ENABLE:
		case WM_SYSCOMMAND:
			blockMessage = true;
			break;
		}
	}

	if (!blockMessage) result = pDispatchMessageA(lpMsg);

	if (sizeof(void*) == 8) DispatchMessageASubhook.Install(DispatchMessageAOriginalAddress, DispatchMessageAHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) DispatchMessageASubhook.Install(DispatchMessageAOriginalAddress, DispatchMessageAHookAddress);

	ReleaseMutex(pDispatchMessageAMutex);

	return result;
}

LRESULT __stdcall DispatchMessageWHook(const MSG* lpMsg)
{
	WaitForSingleObject(pDispatchMessageWMutex, INFINITE);

	if (!DispatchMessageWSubhook.IsInstalled()) return 0;
	DispatchMessageWSubhook.Remove();

	bool blockMessage = false;
	LRESULT result = 0;

	if (lpMsg != NULL)
	{
		switch (lpMsg->message)
		{
		case WM_KILLFOCUS:
		case WM_ACTIVATEAPP:
		case WM_NCACTIVATE:
		case WM_SETFOCUS:
		case WM_ENABLE:
		case WM_SYSCOMMAND:
			blockMessage = true;
			break;
		}
	}

	if (!blockMessage) result = pDispatchMessageW(lpMsg);

	if (sizeof(void*) == 8) DispatchMessageWSubhook.Install(DispatchMessageWOriginalAddress, DispatchMessageWHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) DispatchMessageWSubhook.Install(DispatchMessageWOriginalAddress, DispatchMessageWHookAddress);

	ReleaseMutex(pDispatchMessageWMutex);

	return result;
}

BOOL __stdcall PeekMessageAHook(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
	WaitForSingleObject(pPeekMessageAMutex, INFINITE);

	if (!PeekMessageASubhook.IsInstalled()) return FALSE;
	PeekMessageASubhook.Remove();

	BOOL result = pPeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);

	if (result != FALSE)
	{
		switch (lpMsg->message)
		{
		case WM_KILLFOCUS:
		case WM_ACTIVATEAPP:
		case WM_NCACTIVATE:
		case WM_ENABLE:
			lpMsg->message = WM_NULL;
			break;
		case WM_SYSCOMMAND:
			if ((lpMsg->wParam & 0xFFF0) == SC_MINIMIZE || (lpMsg->wParam & 0xFFF0) == SC_RESTORE)
			{
				lpMsg->message = WM_NULL;
			}
			break;
		}
	}

	if (sizeof(void*) == 8) PeekMessageASubhook.Install(PeekMessageAOriginalAddress, PeekMessageAHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) PeekMessageASubhook.Install(PeekMessageAOriginalAddress, PeekMessageAHookAddress);

	ReleaseMutex(pPeekMessageAMutex);

	return result;
}

BOOL __stdcall PeekMessageWHook(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
	WaitForSingleObject(pPeekMessageWMutex, INFINITE);

	if (!PeekMessageWSubhook.IsInstalled()) return FALSE;
	PeekMessageWSubhook.Remove();

	BOOL result = pPeekMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);

	if (result != FALSE)
	{
		switch (lpMsg->message)
		{
		case WM_KILLFOCUS:
		case WM_ACTIVATEAPP:
		case WM_NCACTIVATE:
		case WM_ENABLE:
			lpMsg->message = WM_NULL;
			break;
		case WM_SYSCOMMAND:
			if ((lpMsg->wParam & 0xFFF0) == SC_MINIMIZE || (lpMsg->wParam & 0xFFF0) == SC_RESTORE)
			{
				lpMsg->message = WM_NULL;
			}
			break;
		}
	}

	if (sizeof(void*) == 8) PeekMessageWSubhook.Install(PeekMessageWOriginalAddress, PeekMessageWHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) PeekMessageWSubhook.Install(PeekMessageWOriginalAddress, PeekMessageWHookAddress);

	ReleaseMutex(pPeekMessageWMutex);

	return result;
}

BOOL __stdcall GetMessageAHook(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
	WaitForSingleObject(pGetMessageAMutex, INFINITE);

	// Remove hook to restore original function
	if (!GetMessageASubhook.IsInstalled()) return FALSE;
	GetMessageASubhook.Remove();

	// The return value of this function
	MSG message = MSG();
	LPMSG lpMessage = &message;

	BOOL result = pGetMessageA(lpMessage, hWnd, wMsgFilterMin, wMsgFilterMax);

	if (lpMessage != NULL)
	{
		switch (lpMessage->message)
		{
		case WM_KILLFOCUS:
			// Neutralize the message
			lpMessage->message = WM_NULL;
			break;

		case WM_ACTIVATE:
			if (LOWORD(lpMessage->wParam) == WA_INACTIVE)
			{
				lpMessage->wParam = MAKELONG(WA_ACTIVE, HIWORD(lpMessage->wParam));
			}
			break;

		case WM_ACTIVATEAPP:
			if (lpMessage->wParam == FALSE)
			{
				lpMessage->wParam = TRUE;
			}
			break;

		case WM_NCACTIVATE:
			// If this is a deactivation message, prevent deactivation
			if (lpMessage->wParam == FALSE)
			{
				lpMessage->wParam = TRUE; // Force it to stay active
			}
			break;

		case WM_SETFOCUS:
			lpMessage->message = WM_NULL;
			break;

		case WM_WINDOWPOSCHANGING:
		case WM_WINDOWPOSCHANGED:
			// Probably overkill
			break;

		case WM_ENABLE:
			lpMessage->wParam = TRUE;
			break;

		case WM_SYSCOMMAND:
			if ((lpMessage->wParam & 0xFFF0) == SC_MINIMIZE ||
				(lpMessage->wParam & 0xFFF0) == SC_RESTORE)
			{
				lpMessage->message = WM_NULL;
			}
			break;

		case WM_PARENTNOTIFY:
			// Probably overkill
			break;

		default:
			break;
		}
	}

	std::memcpy(lpMsg, lpMessage, sizeof(MSG));

	if (sizeof(void*) == 8) GetMessageASubhook.Install(GetMessageAOriginalAddress, GetMessageAHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) GetMessageASubhook.Install(GetMessageAOriginalAddress, GetMessageAHookAddress);

	ReleaseMutex(pGetMessageAMutex);

	return result;
}

BOOL __stdcall GetMessageWHook(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
	WaitForSingleObject(pGetMessageWMutex, INFINITE);

	// Remove hook to restore original function
	if (!GetMessageWSubhook.IsInstalled()) return FALSE;
	GetMessageWSubhook.Remove();

	// The return value of this function
	MSG message = MSG();
	LPMSG lpMessage = &message;

	BOOL result = pGetMessageW(lpMessage, hWnd, wMsgFilterMin, wMsgFilterMax);

	if (lpMessage != NULL)
	{
		switch (lpMessage->message)
		{
		case WM_KILLFOCUS:
			lpMessage->message = WM_NULL;
			break;

		case WM_ACTIVATE:
			if (LOWORD(lpMessage->wParam) == WA_INACTIVE)
			{
				lpMessage->wParam = MAKELONG(WA_ACTIVE, HIWORD(lpMessage->wParam));
			}
			break;

		case WM_ACTIVATEAPP:
			if (lpMessage->wParam == FALSE)
			{
				lpMessage->wParam = TRUE;
			}
			break;

		case WM_NCACTIVATE:
			if (lpMessage->wParam == FALSE)
			{
				lpMessage->wParam = TRUE;
			}
			break;

		case WM_SETFOCUS:
			lpMessage->message = WM_NULL;
			break;

		case WM_WINDOWPOSCHANGING:
		case WM_WINDOWPOSCHANGED:
			// Probably overkill
			break;

		case WM_ENABLE:
			lpMessage->wParam = TRUE;
			break;

		case WM_SYSCOMMAND:
			if ((lpMessage->wParam & 0xFFF0) == SC_MINIMIZE ||
				(lpMessage->wParam & 0xFFF0) == SC_RESTORE)
			{
				lpMessage->message = WM_NULL;
			}
			break;

		case WM_PARENTNOTIFY:
			// Probably overkill
			break;

		default:
			break;
		}
	}

	std::memcpy(lpMsg, lpMessage, sizeof(MSG));

	if (sizeof(void*) == 8) GetMessageWSubhook.Install(GetMessageWOriginalAddress, GetMessageWHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) GetMessageWSubhook.Install(GetMessageWOriginalAddress, GetMessageWHookAddress);

	ReleaseMutex(pGetMessageWMutex);

	return result;
}

BOOL __stdcall ClipCursorHook(const RECT* lpRect) {
	WaitForSingleObject(pClipCursorMutex, INFINITE);
	ReleaseMutex(pClipCursorMutex);
	return TRUE;
}

SHORT __stdcall GetAsyncKeyStateHook(int vKey) {
	WaitForSingleObject(pNtUserGetAsyncKeyStateMutex, INFINITE);

	if (!NtUserGetAsyncKeyStateSubhook.IsInstalled()) return 0;
	NtUserGetAsyncKeyStateSubhook.Remove();

	SHORT result = pNtUserGetAsyncKeyState(vKey);
	if (vKey == VK_MENU || vKey == VK_TAB || vKey == VK_LWIN || vKey == VK_RWIN) result = 0;

	if (sizeof(void*) == 8) NtUserGetAsyncKeyStateSubhook.Install(NtUserGetAsyncKeyStateOriginalAddress, NtUserGetAsyncKeyStateHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) NtUserGetAsyncKeyStateSubhook.Install(NtUserGetAsyncKeyStateOriginalAddress, NtUserGetAsyncKeyStateHookAddress);

	ReleaseMutex(pNtUserGetAsyncKeyStateMutex);
	return result;
}

SHORT __stdcall NtUserGetKeyStateHook(int nVirtKey) {
	WaitForSingleObject(pNtUserGetKeyStateMutex, INFINITE);

	if (!NtUserGetKeyStateSubhook.IsInstalled()) return 0;
	NtUserGetKeyStateSubhook.Remove();

	SHORT result = pNtUserGetKeyState(nVirtKey);
	if (nVirtKey == VK_MENU || nVirtKey == VK_TAB || nVirtKey == VK_LWIN || nVirtKey == VK_RWIN) result = 0;

	if (sizeof(void*) == 8) NtUserGetKeyStateSubhook.Install(NtUserGetKeyStateOriginalAddress, NtUserGetKeyStateHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) NtUserGetKeyStateSubhook.Install(NtUserGetKeyStateOriginalAddress, NtUserGetKeyStateHookAddress);

	ReleaseMutex(pNtUserGetKeyStateMutex);
	return result;
}

BOOL __stdcall GetLastInputInfoHook(PLASTINPUTINFO plii) {
	WaitForSingleObject(pNtUserGetKeyStateMutex, INFINITE);

	if (!NtUserGetKeyStateSubhook.IsInstalled()) return 0;
	NtUserGetKeyStateSubhook.Remove();

	SHORT result = pNtUserGetKeyState(nVirtKey);
	if (nVirtKey == VK_MENU || nVirtKey == VK_TAB || nVirtKey == VK_LWIN || nVirtKey == VK_RWIN) result = 0;

	if (sizeof(void*) == 8) NtUserGetKeyStateSubhook.Install(NtUserGetKeyStateOriginalAddress, NtUserGetKeyStateHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) NtUserGetKeyStateSubhook.Install(NtUserGetKeyStateOriginalAddress, NtUserGetKeyStateHookAddress);

	ReleaseMutex(pNtUserGetKeyStateMutex);
	return result;
}



bool InitWindowStayActive()
{
	ThreadHookerSuspendThreads(0);

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

	DispatchMessageAOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "DispatchMessageA");
	DispatchMessageAHookAddress = (void*)DispatchMessageAHook;
	pDispatchMessageA = (DispatchMessageAT)DispatchMessageAOriginalAddress;
	if (sizeof(void*) == 8) DispatchMessageASubhook.Install(DispatchMessageAOriginalAddress, DispatchMessageAHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) DispatchMessageASubhook.Install(DispatchMessageAOriginalAddress, DispatchMessageAHookAddress);

	DispatchMessageWOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "DispatchMessageW");
	DispatchMessageWHookAddress = (void*)DispatchMessageWHook;
	pDispatchMessageW = (DispatchMessageWT)DispatchMessageWOriginalAddress;
	if (sizeof(void*) == 8) DispatchMessageWSubhook.Install(DispatchMessageWOriginalAddress, DispatchMessageWHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) DispatchMessageWSubhook.Install(DispatchMessageWOriginalAddress, DispatchMessageWHookAddress);

	PeekMessageAOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "PeekMessageA");
	PeekMessageAHookAddress = (void*)PeekMessageAHook;
	pPeekMessageA = (PeekMessageAT)PeekMessageAOriginalAddress;
	if (sizeof(void*) == 8) PeekMessageASubhook.Install(PeekMessageAOriginalAddress, PeekMessageAHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) PeekMessageASubhook.Install(PeekMessageAOriginalAddress, PeekMessageAHookAddress);

	PeekMessageWOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "PeekMessageW");
	PeekMessageWHookAddress = (void*)PeekMessageWHook;
	pPeekMessageW = (PeekMessageWT)PeekMessageWOriginalAddress;
	if (sizeof(void*) == 8) PeekMessageWSubhook.Install(PeekMessageWOriginalAddress, PeekMessageWHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) PeekMessageWSubhook.Install(PeekMessageWOriginalAddress, PeekMessageWHookAddress);

	GetMessageAOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "GetMessageA");
	GetMessageAHookAddress = (void*)GetMessageAHook;
	pGetMessageA = (GetMessageAT)GetMessageAOriginalAddress;
	if (sizeof(void*) == 8) GetMessageASubhook.Install(GetMessageAOriginalAddress, GetMessageAHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) GetMessageASubhook.Install(GetMessageAOriginalAddress, GetMessageAHookAddress);

	GetMessageWOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "GetMessageW");
	GetMessageWHookAddress = (void*)GetMessageWHook;
	pGetMessageW = (GetMessageWT)GetMessageWOriginalAddress;
	if (sizeof(void*) == 8) GetMessageWSubhook.Install(GetMessageWOriginalAddress, GetMessageWHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) GetMessageWSubhook.Install(GetMessageWOriginalAddress, GetMessageWHookAddress);

	ClipCursorOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "ClipCursor");
	ClipCursorHookAddress = (void*)ClipCursorHook;
	pClipCursor = (ClipCursorT)ClipCursorOriginalAddress;
	if (sizeof(void*) == 8) ClipCursorSubhook.Install(ClipCursorOriginalAddress, ClipCursorHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) ClipCursorSubhook.Install(ClipCursorOriginalAddress, ClipCursorHookAddress);

	NtUserGetAsyncKeyStateOriginalAddress = GetProcAddressNt("NtUserGetAsyncKeyState");
	if (NtUserGetAsyncKeyStateOriginalAddress != nullptr)
	{
		NtUserGetAsyncKeyStateHookAddress = (void*)GetAsyncKeyStateHook;
		pNtUserGetAsyncKeyState = (NtUserGetAsyncKeyStateT)NtUserGetAsyncKeyStateOriginalAddress;
		if (sizeof(void*) == 8) NtUserGetAsyncKeyStateSubhook.Install(NtUserGetAsyncKeyStateOriginalAddress, NtUserGetAsyncKeyStateHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) NtUserGetAsyncKeyStateSubhook.Install(NtUserGetAsyncKeyStateOriginalAddress, NtUserGetAsyncKeyStateHookAddress);
	}

	NtUserGetKeyStateOriginalAddress = GetProcAddressNt("NtUserGetKeyState");
	if (NtUserGetKeyStateOriginalAddress != nullptr)
	{
		NtUserGetKeyStateHookAddress = (void*)NtUserGetKeyStateHook;
		pNtUserGetKeyState = (NtUserGetKeyStateT)NtUserGetKeyStateOriginalAddress;
		if (sizeof(void*) == 8) NtUserGetKeyStateSubhook.Install(NtUserGetKeyStateOriginalAddress, NtUserGetKeyStateHookAddress, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) NtUserGetKeyStateSubhook.Install(NtUserGetKeyStateOriginalAddress, NtUserGetKeyStateHookAddress);
	}
	
	GetLastInputInfoOriginalAddress = (void*)GetProcAddress(User32DLLHandle, "GetLastInputInfo");
	GetLastInputInfoHookAddress = (void*)GetLastInputInfoHook;
	pGetLastInputInfo = (GetLastInputInfoT)GetLastInputInfoOriginalAddress;
	if (sizeof(void*) == 8) GetLastInputInfoSubhook.Install(GetLastInputInfoOriginalAddress, GetLastInputInfoHookAddress, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) GetLastInputInfoSubhook.Install(GetLastInputInfoOriginalAddress, GetLastInputInfoHookAddress);

	ThreadHookerResumeThreads(0);
}

void UninitWindowStayActive()
{
	WaitForSingleObject(pGetForegroundWindowMutex, INFINITE);
	WaitForSingleObject(pGetActiveWindowMutex, INFINITE);
	WaitForSingleObject(pGetFocusMutex, INFINITE);
	WaitForSingleObject(pIsWindowEnabledMutex, INFINITE);
	WaitForSingleObject(pIsWindowVisibleMutex, INFINITE);
	WaitForSingleObject(pIsIconicMutex, INFINITE);
	WaitForSingleObject(pShowWindowMutex, INFINITE);
	WaitForSingleObject(pGetWindowMutex, INFINITE);
	WaitForSingleObject(pGetWindowThreadProcessIdMutex, INFINITE);
	WaitForSingleObject(pEnumWindowsMutex, INFINITE);
	WaitForSingleObject(pDispatchMessageAMutex, INFINITE);
	WaitForSingleObject(pDispatchMessageWMutex, INFINITE);
	WaitForSingleObject(pPeekMessageAMutex, INFINITE);
	WaitForSingleObject(pPeekMessageWMutex, INFINITE);
	WaitForSingleObject(pGetMessageAMutex, INFINITE);
	WaitForSingleObject(pGetMessageWMutex, INFINITE);
	WaitForSingleObject(pClipCursorMutex, INFINITE);
	WaitForSingleObject(pNtUserGetAsyncKeyStateMutex, INFINITE);
	WaitForSingleObject(pNtUserGetKeyStateMutex, INFINITE);
	WaitForSingleObject(pGetLastInputInfoMutex, INFINITE);

	ThreadHookerSuspendThreads(0);

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
	if (DispatchMessageASubhook.IsInstalled()) DispatchMessageASubhook.Remove();
	if (DispatchMessageWSubhook.IsInstalled()) DispatchMessageWSubhook.Remove();
	if (PeekMessageASubhook.IsInstalled()) PeekMessageASubhook.Remove();
	if (PeekMessageWSubhook.IsInstalled()) PeekMessageWSubhook.Remove();
	if (GetMessageASubhook.IsInstalled()) GetMessageASubhook.Remove();
	if (GetMessageWSubhook.IsInstalled()) GetMessageASubhook.Remove();
	if (ClipCursorSubhook.IsInstalled()) ClipCursorSubhook.Remove();
	if (NtUserGetAsyncKeyStateSubhook.IsInstalled()) NtUserGetAsyncKeyStateSubhook.Remove();
	if (NtUserGetKeyStateSubhook.IsInstalled()) NtUserGetKeyStateSubhook.Remove();
	if (GetLastInputInfoSubhook.IsInstalled()) GetLastInputInfoSubhook.Remove();

	ThreadHookerResumeThreads(0);

	ReleaseMutex(pGetForegroundWindowMutex);
	ReleaseMutex(pGetActiveWindowMutex);
	ReleaseMutex(pGetFocusMutex);
	ReleaseMutex(pIsWindowEnabledMutex);
	ReleaseMutex(pIsWindowVisibleMutex);
	ReleaseMutex(pIsIconicMutex);
	ReleaseMutex(pShowWindowMutex);
	ReleaseMutex(pGetWindowMutex);
	ReleaseMutex(pGetWindowThreadProcessIdMutex);
	ReleaseMutex(pEnumWindowsMutex);
	ReleaseMutex(pDispatchMessageAMutex);
	ReleaseMutex(pDispatchMessageWMutex);
	ReleaseMutex(pPeekMessageAMutex);
	ReleaseMutex(pPeekMessageWMutex);
	ReleaseMutex(pGetMessageAMutex);
	ReleaseMutex(pGetMessageWMutex);
	ReleaseMutex(pClipCursorMutex);
	ReleaseMutex(pNtUserGetAsyncKeyStateMutex);
	ReleaseMutex(pNtUserGetKeyStateMutex);
	ReleaseMutex(pGetLastInputInfoMutex);
}



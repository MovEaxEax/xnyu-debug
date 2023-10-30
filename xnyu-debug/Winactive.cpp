#include "pch.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "Threadhooker.h"
#include "xNyuHook.h"
#include "Winactive.h"



// Big thanks to Kula for the WndProc idea
WNDPROC OriginalWindowProcedure{};

bool WndProcInfoTrigger = false;
LRESULT CALLBACK WinActiveWndProc(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam) {
	if (WndProcInfoTrigger)
	{
		DebugConsoleOutput("WndProc() Hook active...", true, "yellow");
		WndProcInfoTrigger = false;
	}

	switch (Message)
	{
	case WM_ACTIVATE:
		if (LOWORD(WParam) == WA_INACTIVE) return 0;
	case WM_ACTIVATEAPP:
		if (WParam == FALSE) return 0;
	case WM_NCACTIVATE:
		if (WParam == FALSE) return 0;
	case WM_SYSCOMMAND:
		if ((WParam & 0xFFF0) == SC_MINIMIZE || (WParam & 0xFFF0) == SC_RESTORE) return 0;
	case WM_KILLFOCUS:
	case WM_ENABLE:
		return 0;
	}

	return CallWindowProc(OriginalWindowProcedure, WindowHandle, Message, WParam, LParam);
}

// --- GetActiveWindow Hook ---
GetActiveWindowHook<GetActiveWindowT>* GetActiveWindowHook<GetActiveWindowT>::instance = nullptr; HWND GetForegroundWindowReal();
HWND GetActiveWindowReal()
{
	if (GetActiveWindowHook<GetActiveWindowT>::instance && GetActiveWindowHook<GetActiveWindowT>::instance->isActive()) return GetActiveWindowHook<GetActiveWindowT>::instance->callTrampoline();
	else return GetActiveWindow();
}

// --- GetFocus Hook ---
GetFocusHook<GetFocusT>* GetFocusHook<GetFocusT>::instance = nullptr;
HWND GetFocusReal()
{
	if (GetFocusHook<GetFocusT>::instance && GetFocusHook<GetFocusT>::instance->isActive()) return GetFocusHook<GetFocusT>::instance->callTrampoline();
	else return GetFocus();
}

// --- IsWindowEnabled Hook ---
IsWindowEnabledHook<IsWindowEnabledT>* IsWindowEnabledHook<IsWindowEnabledT>::instance = nullptr;
BOOL IsWindowEnabledReal(HWND hWnd)
{
	if (IsWindowEnabledHook<IsWindowEnabledT>::instance && IsWindowEnabledHook<IsWindowEnabledT>::instance->isActive()) return IsWindowEnabledHook<IsWindowEnabledT>::instance->callTrampoline(hWnd);
	else return IsWindowEnabled(hWnd);
}

// --- IsWindowVisible Hook ---
IsWindowVisibleHook<IsWindowVisibleT>* IsWindowVisibleHook<IsWindowVisibleT>::instance = nullptr;
BOOL IsWindowVisibleReal(HWND hWnd)
{
	if (IsWindowVisibleHook<IsWindowVisibleT>::instance && IsWindowVisibleHook<IsWindowVisibleT>::instance->isActive()) return IsWindowVisibleHook<IsWindowVisibleT>::instance->callTrampoline(hWnd);
	else return IsWindowVisible(hWnd);
}

// --- IsIconic Hook ---
IsIconicHook<IsIconicT>* IsIconicHook<IsIconicT>::instance = nullptr;
BOOL IsIconicReal(HWND hWnd)
{
	if (IsIconicHook<IsIconicT>::instance && IsIconicHook<IsIconicT>::instance->isActive()) return IsIconicHook<IsIconicT>::instance->callTrampoline(hWnd);
	else return IsIconic(hWnd);
}

// --- ShowWindow Hook ---
ShowWindowHook<ShowWindowT>* ShowWindowHook<ShowWindowT>::instance = nullptr;
BOOL ShowWindowReal(HWND hWnd, int nCmdShow)
{
	if (ShowWindowHook<ShowWindowT>::instance && ShowWindowHook<ShowWindowT>::instance->isActive()) return ShowWindowHook<ShowWindowT>::instance->callTrampoline(hWnd, nCmdShow);
	else return ShowWindow(hWnd, nCmdShow);
}

// --- GetWindow Hook ---
GetWindowHook<GetWindowT>* GetWindowHook<GetWindowT>::instance = nullptr;
HWND GetWindowReal(HWND hWnd, UINT uCmd)
{
	if (GetWindowHook<GetWindowT>::instance && GetWindowHook<GetWindowT>::instance->isActive()) return GetWindowHook<GetWindowT>::instance->callTrampoline(hWnd, uCmd);
	else return GetWindow(hWnd, uCmd);
}

// --- GetWindowThreadProcessId Hook ---
GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>* GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>::instance = nullptr;
DWORD GetWindowThreadProcessIdReal(HWND hWnd, LPDWORD lpdwProcessId)
{
	if (GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>::instance && GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>::instance->isActive()) return GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>::instance->callTrampoline(hWnd, lpdwProcessId);
	else return GetWindowThreadProcessId(hWnd, lpdwProcessId);
}

// --- EnumWindows Hook ---
EnumWindowsHook<EnumWindowsT>* EnumWindowsHook<EnumWindowsT>::instance = nullptr;
BOOL EnumWindowsReal(WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
	if (EnumWindowsHook<EnumWindowsT>::instance && EnumWindowsHook<EnumWindowsT>::instance->isActive()) return EnumWindowsHook<EnumWindowsT>::instance->callTrampoline(lpEnumFunc, lParam);
	else return EnumWindows(lpEnumFunc, lParam);
}

// --- DispatchMessageA Hook ---
DispatchMessageAHook<DispatchMessageAT>* DispatchMessageAHook<DispatchMessageAT>::instance = nullptr;
LRESULT DispatchMessageAReal(const MSG* lpMsg)
{
	if (DispatchMessageAHook<DispatchMessageAT>::instance && DispatchMessageAHook<DispatchMessageAT>::instance->isActive()) return DispatchMessageAHook<DispatchMessageAT>::instance->callTrampoline(lpMsg);
	else return DispatchMessageA(lpMsg);
}

// --- DispatchMessageW Hook ---
DispatchMessageWHook<DispatchMessageWT>* DispatchMessageWHook<DispatchMessageWT>::instance = nullptr;
LRESULT DispatchMessageWReal(const MSG* lpMsg)
{
	if (DispatchMessageWHook<DispatchMessageWT>::instance && DispatchMessageWHook<DispatchMessageWT>::instance->isActive()) return DispatchMessageWHook<DispatchMessageWT>::instance->callTrampoline(lpMsg);
	else return DispatchMessageW(lpMsg);
}

// --- PeekMessageA Hook ---
PeekMessageAHook<PeekMessageAT>* PeekMessageAHook<PeekMessageAT>::instance = nullptr;
BOOL PeekMessageWReal(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
	if (PeekMessageAHook<PeekMessageAT>::instance && PeekMessageAHook<PeekMessageAT>::instance->isActive()) return PeekMessageAHook<PeekMessageAT>::instance->callTrampoline(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
	else return PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

// --- PeekMessageW Hook ---
PeekMessageWHook<PeekMessageWT>* PeekMessageWHook<PeekMessageWT>::instance = nullptr;
BOOL PeekMessageWReal(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
	if (PeekMessageWHook<PeekMessageWT>::instance && PeekMessageWHook<PeekMessageWT>::instance->isActive()) return PeekMessageWHook<PeekMessageWT>::instance->callTrampoline(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
	else return PeekMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

// --- GetMessageA Hook ---
GetMessageAHook<GetMessageAT>* GetMessageAHook<GetMessageAT>::instance = nullptr;
BOOL GetMessageAReal(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
	if (GetMessageAHook<GetMessageAT>::instance && GetMessageAHook<GetMessageAT>::instance->isActive()) return GetMessageAHook<GetMessageAT>::instance->callTrampoline(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
	else return GetMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}

// --- GetMessageW Hook ---
GetMessageWHook<GetMessageWT>* GetMessageWHook<GetMessageWT>::instance = nullptr;
BOOL GetMessageWReal(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
	if (GetMessageWHook<GetMessageWT>::instance && GetMessageWHook<GetMessageWT>::instance->isActive()) return GetMessageWHook<GetMessageWT>::instance->callTrampoline(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
	else return GetMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}

// --- ClipCursor Hook ---
ClipCursorHook<ClipCursorT>* ClipCursorHook<ClipCursorT>::instance = nullptr;
BOOL ClipCursorReal(const RECT* lpRect)
{
	if (ClipCursorHook<ClipCursorT>::instance && ClipCursorHook<ClipCursorT>::instance->isActive()) return ClipCursorHook<ClipCursorT>::instance->callTrampoline(lpRect);
	else return ClipCursor(lpRect);
}

// --- NtUserGetAsyncKeyState Hook ---
NtUserGetAsyncKeyStateHook<NtUserGetAsyncKeyStateT>* NtUserGetAsyncKeyStateHook<NtUserGetAsyncKeyStateT>::instance = nullptr;

// --- NtUserGetKeyState Hook ---
NtUserGetKeyStateHook<NtUserGetKeyStateT>* NtUserGetKeyStateHook<NtUserGetKeyStateT>::instance = nullptr;

// --- GetLastInputInfo Hook ---
GetLastInputInfoHook<GetLastInputInfoT>* GetLastInputInfoHook<GetLastInputInfoT>::instance = nullptr;
BOOL GetLastInputInfoReal(PLASTINPUTINFO plii)
{
	if (GetLastInputInfoHook<GetLastInputInfoT>::instance && GetLastInputInfoHook<GetLastInputInfoT>::instance->isActive()) return GetLastInputInfoHook<GetLastInputInfoT>::instance->callTrampoline(plii);
	else return GetLastInputInfo(plii);
}

// --- GetCursorPos Hook ---
GetCursorPosHook<GetCursorPosT>* GetCursorPosHook<GetCursorPosT>::instance = nullptr;
BOOL GetCursorPosReal(LPPOINT lpPoint)
{
	if (GetCursorPosHook<GetCursorPosT>::instance && GetCursorPosHook<GetCursorPosT>::instance->isActive()) return GetCursorPosHook<GetCursorPosT>::instance->callTrampoline(lpPoint);
	else return GetCursorPos(lpPoint);
}



// --- Variables ---
bool WinActiveEnabled = false;



// --- Functions ---
void InitWinactiveHooks()
{
	std::string winactiveHooks = GetGlobalSetting("config_winactive_hooks");

	HMODULE User32DLLHandle = GetModuleHandleA("User32.dll");
	if (User32DLLHandle != NULL)
	{
		if (winactiveHooks.find("getforegroundwindow") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!GetForegroundWindowHook<GetForegroundWindowT>::instance) GetForegroundWindowHook<GetForegroundWindowT>::instance = new GetForegroundWindowHook<GetForegroundWindowT>(GetProcAddress(User32DLLHandle, "GetForegroundWindow"));
		}
		if (winactiveHooks.find("getactivewindow") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!GetActiveWindowHook<GetActiveWindowT>::instance) GetActiveWindowHook<GetActiveWindowT>::instance = new GetActiveWindowHook<GetActiveWindowT>(GetProcAddress(User32DLLHandle, "GetActiveWindow"));
		}
		if (winactiveHooks.find("getfocus") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!GetFocusHook<GetFocusT>::instance) GetFocusHook<GetFocusT>::instance = new GetFocusHook<GetFocusT>(GetProcAddress(User32DLLHandle, "GetFocus"));
		}
		if (winactiveHooks.find("iswindowenabled") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!IsWindowEnabledHook<IsWindowEnabledT>::instance) IsWindowEnabledHook<IsWindowEnabledT>::instance = new IsWindowEnabledHook<IsWindowEnabledT>(GetProcAddress(User32DLLHandle, "IsWindowEnabled"));
		}
		if (winactiveHooks.find("iswindowvisible") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!IsWindowVisibleHook<IsWindowVisibleT>::instance) IsWindowVisibleHook<IsWindowVisibleT>::instance = new IsWindowVisibleHook<IsWindowVisibleT>(GetProcAddress(User32DLLHandle, "IsWindowVisible"));
		}
		if (winactiveHooks.find("isiconic") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!IsIconicHook<IsIconicT>::instance) IsIconicHook<IsIconicT>::instance = new IsIconicHook<IsIconicT>(GetProcAddress(User32DLLHandle, "IsIconic"));
		}
		if (winactiveHooks.find("showwindow") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!ShowWindowHook<ShowWindowT>::instance) ShowWindowHook<ShowWindowT>::instance = new ShowWindowHook<ShowWindowT>(GetProcAddress(User32DLLHandle, "ShowWindow"));
		}
		if (winactiveHooks.find("getwindow") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!GetWindowHook<GetWindowT>::instance) GetWindowHook<GetWindowT>::instance = new GetWindowHook<GetWindowT>(GetProcAddress(User32DLLHandle, "GetWindow"));
		}
		if (winactiveHooks.find("getwindowthreadprocessid") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>::instance) GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>::instance = new GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>(GetProcAddress(User32DLLHandle, "GetWindowThreadProcessId"));
		}
		if (winactiveHooks.find("enumwindows") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!EnumWindowsHook<EnumWindowsT>::instance) EnumWindowsHook<EnumWindowsT>::instance = new EnumWindowsHook<EnumWindowsT>(GetProcAddress(User32DLLHandle, "EnumWindows"));
		}
		if (winactiveHooks.find("dispatchmessagea") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!DispatchMessageAHook<DispatchMessageAT>::instance) DispatchMessageAHook<DispatchMessageAT>::instance = new DispatchMessageAHook<DispatchMessageAT>(GetProcAddress(User32DLLHandle, "DispatchMessageA"));
		}
		if (winactiveHooks.find("dispatchmessagew") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!DispatchMessageWHook<DispatchMessageWT>::instance) DispatchMessageWHook<DispatchMessageWT>::instance = new DispatchMessageWHook<DispatchMessageWT>(GetProcAddress(User32DLLHandle, "DispatchMessageW"));
		}
		if (winactiveHooks.find("peekmessagea") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!PeekMessageAHook<PeekMessageAT>::instance) PeekMessageAHook<PeekMessageAT>::instance = new PeekMessageAHook<PeekMessageAT>(GetProcAddress(User32DLLHandle, "PeekMessageA"));
		}
		if (winactiveHooks.find("peekmessagew") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!PeekMessageWHook<PeekMessageWT>::instance) PeekMessageWHook<PeekMessageWT>::instance = new PeekMessageWHook<PeekMessageWT>(GetProcAddress(User32DLLHandle, "PeekMessageW"));
		}
		if (winactiveHooks.find("getmessagea") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!GetMessageAHook<GetMessageAT>::instance) GetMessageAHook<GetMessageAT>::instance = new GetMessageAHook<GetMessageAT>(GetProcAddress(User32DLLHandle, "GetMessageA"));
		}
		if (winactiveHooks.find("getmessagew") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!GetMessageWHook<GetMessageWT>::instance) GetMessageWHook<GetMessageWT>::instance = new GetMessageWHook<GetMessageWT>(GetProcAddress(User32DLLHandle, "GetMessageW"));
		}
		if (winactiveHooks.find("clipcursor") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!ClipCursorHook<ClipCursorT>::instance) ClipCursorHook<ClipCursorT>::instance = new ClipCursorHook<ClipCursorT>(GetProcAddress(User32DLLHandle, "ClipCursor"));
		}
		if (winactiveHooks.find("ntusergetasynckeystate") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!NtUserGetAsyncKeyStateHook<NtUserGetAsyncKeyStateT>::instance) NtUserGetAsyncKeyStateHook<NtUserGetAsyncKeyStateT>::instance = new NtUserGetAsyncKeyStateHook<NtUserGetAsyncKeyStateT>(GetProcAddress(User32DLLHandle, "NtUserGetAsyncKeyState"));
		}
		if (winactiveHooks.find("ntusergetkeystate") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!NtUserGetKeyStateHook<NtUserGetKeyStateT>::instance) NtUserGetKeyStateHook<NtUserGetKeyStateT>::instance = new NtUserGetKeyStateHook<NtUserGetKeyStateT>(GetProcAddress(User32DLLHandle, "NtUserGetKeyState"));
		}
		if (winactiveHooks.find("getlastinputinfo") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!GetLastInputInfoHook<GetLastInputInfoT>::instance) GetLastInputInfoHook<GetLastInputInfoT>::instance = new GetLastInputInfoHook<GetLastInputInfoT>(GetProcAddress(User32DLLHandle, "GetLastInputInfo"));
		}
		if (winactiveHooks.find("getcursorpos") != std::string::npos || winactiveHooks.find("all") != std::string::npos)
		{
			if (!GetCursorPosHook<GetCursorPosT>::instance) GetCursorPosHook<GetCursorPosT>::instance = new GetCursorPosHook<GetCursorPosT>(GetProcAddress(User32DLLHandle, "GetCursorPos"));
		}
	}
}

bool InitWindowStayActive()
{
	// Init the hooks, if not already
	InitWinactiveHooks();

	ThreadHookerSuspendThreads(0);

	std::string winactiveHooks = GetGlobalSetting("config_overclocker_hooks");

	if (winactiveHooks.find("wndproc") != std::string::npos || winactiveHooks.find("all") != std::string::npos) OriginalWindowProcedure = (WNDPROC)SetWindowLongPtr(GetMainWindow(), GWLP_WNDPROC, (LONG_PTR)WinActiveWndProc);
	if (GetForegroundWindowHook<GetForegroundWindowT>::instance) GetForegroundWindowHook<GetForegroundWindowT>::instance->install();
	if (GetActiveWindowHook<GetActiveWindowT>::instance) GetActiveWindowHook<GetActiveWindowT>::instance->install();
	if (GetFocusHook<GetFocusT>::instance) GetFocusHook<GetFocusT>::instance->install();
	if (IsWindowEnabledHook<IsWindowEnabledT>::instance) IsWindowEnabledHook<IsWindowEnabledT>::instance->install();
	if (IsWindowVisibleHook<IsWindowVisibleT>::instance) IsWindowVisibleHook<IsWindowVisibleT>::instance->install();
	if (IsIconicHook<IsIconicT>::instance) IsIconicHook<IsIconicT>::instance->install();
	if (ShowWindowHook<ShowWindowT>::instance) ShowWindowHook<ShowWindowT>::instance->install();
	if (GetWindowHook<GetWindowT>::instance) GetWindowHook<GetWindowT>::instance->install();
	if (GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>::instance) GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>::instance->install();
	if (EnumWindowsHook<EnumWindowsT>::instance) EnumWindowsHook<EnumWindowsT>::instance->install();
	if (DispatchMessageAHook<DispatchMessageAT>::instance) DispatchMessageAHook<DispatchMessageAT>::instance->install();
	if (DispatchMessageWHook<DispatchMessageWT>::instance) DispatchMessageWHook<DispatchMessageWT>::instance->install();
	if (PeekMessageAHook<PeekMessageAT>::instance) PeekMessageAHook<PeekMessageAT>::instance->install();
	if (PeekMessageWHook<PeekMessageWT>::instance) PeekMessageWHook<PeekMessageWT>::instance->install();
	if (GetMessageAHook<GetMessageAT>::instance) GetMessageAHook<GetMessageAT>::instance->install();
	if (GetMessageWHook<GetMessageWT>::instance) GetMessageWHook<GetMessageWT>::instance->install();
	if (ClipCursorHook<ClipCursorT>::instance) ClipCursorHook<ClipCursorT>::instance->install();
	if (NtUserGetAsyncKeyStateHook<NtUserGetAsyncKeyStateT>::instance) NtUserGetAsyncKeyStateHook<NtUserGetAsyncKeyStateT>::instance->install();
	if (NtUserGetKeyStateHook<NtUserGetKeyStateT>::instance) NtUserGetKeyStateHook<NtUserGetKeyStateT>::instance->install();
	if (GetLastInputInfoHook<GetLastInputInfoT>::instance) GetLastInputInfoHook<GetLastInputInfoT>::instance->install();
	if (GetCursorPosHook<GetCursorPosT>::instance) GetCursorPosHook<GetCursorPosT>::instance->install();

	WinActiveEnabled = true;

	ThreadHookerResumeThreads(0);

	return true;
}

void UninitWindowStayActive()
{
	ThreadHookerSuspendThreads(0);

	if (OriginalWindowProcedure)
	{
		SetWindowLongPtr(GetMainWindow(), GWLP_WNDPROC, (LONG_PTR)OriginalWindowProcedure);
		OriginalWindowProcedure = NULL;
	}
	if (GetForegroundWindowHook<GetForegroundWindowT>::instance && GetForegroundWindowHook<GetForegroundWindowT>::instance->isActive()) GetForegroundWindowHook<GetForegroundWindowT>::instance->remove();
	if (GetActiveWindowHook<GetActiveWindowT>::instance && GetActiveWindowHook<GetActiveWindowT>::instance->isActive()) GetActiveWindowHook<GetActiveWindowT>::instance->remove();
	if (GetFocusHook<GetFocusT>::instance && GetFocusHook<GetFocusT>::instance->isActive()) GetFocusHook<GetFocusT>::instance->remove();
	if (IsWindowEnabledHook<IsWindowEnabledT>::instance && IsWindowEnabledHook<IsWindowEnabledT>::instance->isActive()) IsWindowEnabledHook<IsWindowEnabledT>::instance->remove();
	if (IsWindowVisibleHook<IsWindowVisibleT>::instance && IsWindowVisibleHook<IsWindowVisibleT>::instance->isActive()) IsWindowVisibleHook<IsWindowVisibleT>::instance->remove();
	if (IsIconicHook<IsIconicT>::instance && IsIconicHook<IsIconicT>::instance->isActive()) IsIconicHook<IsIconicT>::instance->remove();
	if (ShowWindowHook<ShowWindowT>::instance && ShowWindowHook<ShowWindowT>::instance->isActive()) ShowWindowHook<ShowWindowT>::instance->remove();
	if (GetWindowHook<GetWindowT>::instance && GetWindowHook<GetWindowT>::instance->isActive()) GetWindowHook<GetWindowT>::instance->remove();
	if (GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>::instance && GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>::instance->isActive()) GetWindowThreadProcessIdHook<GetWindowThreadProcessIdT>::instance->remove();
	if (EnumWindowsHook<EnumWindowsT>::instance && EnumWindowsHook<EnumWindowsT>::instance->isActive()) EnumWindowsHook<EnumWindowsT>::instance->remove();
	if (DispatchMessageAHook<DispatchMessageAT>::instance && DispatchMessageAHook<DispatchMessageAT>::instance->isActive()) DispatchMessageAHook<DispatchMessageAT>::instance->remove();
	if (DispatchMessageWHook<DispatchMessageWT>::instance && DispatchMessageWHook<DispatchMessageWT>::instance->isActive()) DispatchMessageWHook<DispatchMessageWT>::instance->remove();
	if (PeekMessageAHook<PeekMessageAT>::instance && PeekMessageAHook<PeekMessageAT>::instance->isActive()) PeekMessageAHook<PeekMessageAT>::instance->remove();
	if (PeekMessageWHook<PeekMessageWT>::instance && PeekMessageWHook<PeekMessageWT>::instance->isActive()) PeekMessageWHook<PeekMessageWT>::instance->remove();
	if (GetMessageAHook<GetMessageAT>::instance && GetMessageAHook<GetMessageAT>::instance->isActive()) GetMessageAHook<GetMessageAT>::instance->remove();
	if (GetMessageWHook<GetMessageWT>::instance && GetMessageWHook<GetMessageWT>::instance->isActive()) GetMessageWHook<GetMessageWT>::instance->remove();
	if (ClipCursorHook<ClipCursorT>::instance && ClipCursorHook<ClipCursorT>::instance->isActive()) ClipCursorHook<ClipCursorT>::instance->remove();
	if (NtUserGetAsyncKeyStateHook<NtUserGetAsyncKeyStateT>::instance && NtUserGetAsyncKeyStateHook<NtUserGetAsyncKeyStateT>::instance->isActive()) NtUserGetAsyncKeyStateHook<NtUserGetAsyncKeyStateT>::instance->remove();
	if (NtUserGetKeyStateHook<NtUserGetKeyStateT>::instance && NtUserGetKeyStateHook<NtUserGetKeyStateT>::instance->isActive()) NtUserGetKeyStateHook<NtUserGetKeyStateT>::instance->remove();
	if (GetLastInputInfoHook<GetLastInputInfoT>::instance && GetLastInputInfoHook<GetLastInputInfoT>::instance->isActive()) GetLastInputInfoHook<GetLastInputInfoT>::instance->remove();
	if (GetCursorPosHook<GetCursorPosT>::instance && GetCursorPosHook<GetCursorPosT>::instance->isActive()) GetCursorPosHook<GetCursorPosT>::instance->remove();

	WinActiveMode = false;

	ThreadHookerResumeThreads(0);
}

bool isWinActiveEnabled()
{
	return WinActiveEnabled;
}



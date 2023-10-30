#pragma once

// --- Typedefs ---
typedef HWND(__stdcall* GetForegroundWindowT)();
typedef HWND(__stdcall* GetActiveWindowT)();
typedef HWND(__stdcall* GetFocusT)();
typedef BOOL(__stdcall* IsWindowEnabledT)(HWND hWnd);
typedef BOOL(__stdcall* IsWindowVisibleT)(HWND hWnd);
typedef BOOL(__stdcall* IsIconicT)(HWND hWnd);
typedef BOOL(__stdcall* ShowWindowT)(HWND hWnd, int nCmdShow);
typedef HWND(__stdcall* GetWindowT)(HWND hWnd, UINT uCmd);
typedef DWORD(__stdcall* GetWindowThreadProcessIdT)(HWND hWnd, LPDWORD lpdwProcessId);
typedef BOOL(__stdcall* EnumWindowsT)(WNDENUMPROC lpEnumFunc, LPARAM lParam);
typedef LRESULT(__stdcall* DispatchMessageAT)(const MSG* lpMsg);
typedef LRESULT(__stdcall* DispatchMessageWT)(const MSG* lpMsg);
typedef BOOL(__stdcall* PeekMessageAT)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
typedef BOOL(__stdcall* PeekMessageWT)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
typedef BOOL(__stdcall* GetMessageAT)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
typedef BOOL(__stdcall* GetMessageWT)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
typedef BOOL(__stdcall* ClipCursorT)(const RECT* lpRect);
typedef SHORT(__stdcall* NtUserGetAsyncKeyStateT)(int vKey);
typedef SHORT(__stdcall* NtUserGetKeyStateT)(int vKey);
typedef BOOL(__stdcall* GetLastInputInfoT)(PLASTINPUTINFO plii);
typedef BOOL(__stdcall* GetCursorPosT)(LPPOINT lpPoint);



// --- Variables ---
extern bool WinActiveMode;



// Big thanks to Kula for the WndProc idea
extern WNDPROC OriginalWindowProcedure;
LRESULT CALLBACK WinActiveWndProc(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam);

// --- GetForegroundWindow Hook ---
template <typename FuncT>
class GetForegroundWindowHook : public xNyuHook<GetForegroundWindowT> {
private:
	HWND mainWindowHandle;
public:
	static GetForegroundWindowHook* instance;
	GetForegroundWindowHook(void* originalAddress) : xNyuHook<GetForegroundWindowT>(originalAddress, CustomHook) { instance = this; }
	static HWND __stdcall CustomHook()
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetForegroundWindow() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		return instance->mainWindowHandle;
	}
};
HWND GetForegroundWindowReal();

// --- GetActiveWindow Hook ---
template <typename FuncT>
class GetActiveWindowHook : public xNyuHook<GetActiveWindowT> {
private:
	HWND mainWindowHandle;
public:
	static GetActiveWindowHook* instance;
	GetActiveWindowHook(void* originalAddress) : xNyuHook<GetActiveWindowT>(originalAddress, CustomHook) { instance = this; }
	static HWND __stdcall CustomHook()
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetActiveWindow() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		return instance->mainWindowHandle
	}
};
HWND GetActiveWindowReal();

// --- GetFocus Hook ---
template <typename FuncT>
class GetFocusHook : public xNyuHook<GetFocusT> {
private:
	HWND mainWindowHandle;
public:
	static GetFocusHook* instance;
	GetFocusHook(void* originalAddress) : xNyuHook<GetFocusT>(originalAddress, CustomHook) { instance = this; }
	static HWND __stdcall CustomHook()
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetFocus() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		return instance->mainWindowHandle
	}
};
HWND GetFocusReal();

// --- IsWindowEnabled Hook ---
template <typename FuncT>
class IsWindowEnabledHook : public xNyuHook<IsWindowEnabledT> {
public:
	static IsWindowEnabledHook* instance;
	IsWindowEnabledHook(void* originalAddress) : xNyuHook<IsWindowEnabledT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(HWND hWnd)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("IsWindowEnabled() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		return true;
	}
};
BOOL IsWindowEnabledReal(HWND hWnd);

// --- IsWindowVisible Hook ---
template <typename FuncT>
class IsWindowVisibleHook : public xNyuHook<IsWindowVisibleT> {
public:
	static IsWindowVisibleHook* instance;
	IsWindowVisibleHook(void* originalAddress) : xNyuHook<IsWindowVisibleT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(HWND hWnd)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("IsWindowVisible() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		return true;
	}
};
BOOL IsWindowVisibleReal(HWND hWnd);

// --- IsIconic Hook ---
template <typename FuncT>
class IsIconicHook : public xNyuHook<IsIconicT> {
public:
	static IsIconicHook* instance;
	IsIconicHook(void* originalAddress) : xNyuHook<IsIconicT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(HWND hWnd)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetActiveWindow() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		return false;
	}
};
BOOL IsIconicReal(HWND hWnd);

// --- ShowWindow Hook ---
template <typename FuncT>
class ShowWindowHook : public xNyuHook<ShowWindowT> {
public:
	static ShowWindowHook* instance;
	ShowWindowHook(void* originalAddress) : xNyuHook<ShowWindowT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(HWND hWnd, int nCmdShow)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("ShowWindow() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		return true;
	}
};
BOOL ShowWindowReal(HWND hWnd, int nCmdShow);

// --- GetWindow Hook ---
template <typename FuncT>
class GetWindowHook : public xNyuHook<GetWindowT> {
private:
	HWND mainWindowHandle;
public:
	static GetWindowHook* instance;
	GetWindowHook(void* originalAddress) : xNyuHook<GetWindowT>(originalAddress, CustomHook) { instance = this; }
	static HWND __stdcall CustomHook(HWND hWnd, UINT uCmd)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetWindow() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		return instance->mainWindowHandle;
	}
};
HWND GetWindowReal(HWND hWnd, UINT uCmd);

// --- GetWindowThreadProcessId Hook ---
template <typename FuncT>
class GetWindowThreadProcessIdHook : public xNyuHook<GetWindowThreadProcessIdT> {
private:
	int mainThreadId;
public:
	static GetWindowThreadProcessIdHook* instance;
	GetWindowThreadProcessIdHook(void* originalAddress) : xNyuHook<GetWindowThreadProcessIdT>(originalAddress, CustomHook) { instance = this; }
	static DWORD __stdcall CustomHook(HWND hWnd, LPDWORD lpdwProcessId)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetWindowThreadProcessId() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		return instance->mainThreadId;
	}
};
DWORD GetWindowThreadProcessIdReal(HWND hWnd, LPDWORD lpdwProcessId);

// --- EnumWindows Hook ---
template <typename FuncT>
class EnumWindowsHook : public xNyuHook<EnumWindowsT> {
public:
	static EnumWindowsHook* instance;
	EnumWindowsHook(void* originalAddress) : xNyuHook<EnumWindowsT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(WNDENUMPROC lpEnumFunc, LPARAM lParam)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("EnumWindows() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		return false;
	}
};
BOOL EnumWindowsReal(WNDENUMPROC lpEnumFunc, LPARAM lParam);

// --- DispatchMessageA Hook ---
template <typename FuncT>
class DispatchMessageAHook : public xNyuHook<DispatchMessageAT> {
public:
	static DispatchMessageAHook* instance;
	DispatchMessageAHook(void* originalAddress) : xNyuHook<DispatchMessageAT>(originalAddress, CustomHook) { instance = this; }
	static LRESULT __stdcall CustomHook(const MSG* lpMsg)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("DispatchMessageA() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		if (lpMsg != NULL)
		{
			switch (lpMsg->message)
			{
			case WM_ACTIVATE:
				if (LOWORD(lpMsg->wParam) == WA_INACTIVE) return 0;
				break;
			case WM_ACTIVATEAPP:
				if (lpMsg->wParam == FALSE) return 0;
				break;
			case WM_NCACTIVATE:
				if (lpMsg->wParam == FALSE) return 0;
				break;
			case WM_SYSCOMMAND:
				if ((lpMsg->wParam & 0xFFF0) == SC_MINIMIZE || (lpMsg->wParam & 0xFFF0) == SC_RESTORE) return 0;
				break;
			case WM_KILLFOCUS:
			case WM_ENABLE:
				return 0;
			}
		}
		return instance->callTrampoline(lpMsg);
	}
};
LRESULT DispatchMessageAReal(const MSG* lpMsg);

// --- DispatchMessageW Hook ---
template <typename FuncT>
class DispatchMessageWHook : public xNyuHook<DispatchMessageWT> {
public:
	static DispatchMessageWHook* instance;
	DispatchMessageWHook(void* originalAddress) : xNyuHook<DispatchMessageWT>(originalAddress, CustomHook) { instance = this; }
	static LRESULT __stdcall CustomHook(const MSG* lpMsg)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("DispatchMessageW() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		if (lpMsg != NULL)
		{
			switch (lpMsg->message)
			{
			case WM_ACTIVATE:
				if (LOWORD(lpMsg->wParam) == WA_INACTIVE) return 0;
				break;
			case WM_ACTIVATEAPP:
				if (lpMsg->wParam == FALSE) return 0;
				break;
			case WM_NCACTIVATE:
				if (lpMsg->wParam == FALSE) return 0;
				break;
			case WM_SYSCOMMAND:
				if ((lpMsg->wParam & 0xFFF0) == SC_MINIMIZE || (lpMsg->wParam & 0xFFF0) == SC_RESTORE) return 0;
				break;
			case WM_KILLFOCUS:
			case WM_ENABLE:
				return 0;
			}
		}
		return instance->callTrampoline(lpMsg);
	}
};
LRESULT DispatchMessageWReal(const MSG* lpMsg);

// --- PeekMessageA Hook ---
template <typename FuncT>
class PeekMessageAHook : public xNyuHook<PeekMessageAT> {
public:
	static PeekMessageAHook* instance;
	PeekMessageAHook(void* originalAddress) : xNyuHook<PeekMessageAT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("PeekMessageA() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		BOOL result = instance->callTrampoline(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
		if (lpMsg != NULL)
		{
			switch (lpMsg->message)
			{
			case WM_ACTIVATE:
				if (LOWORD(lpMsg->wParam) == WA_INACTIVE) lpMsg->message = WM_NULL;
				break;
			case WM_ACTIVATEAPP:
				if (lpMsg->wParam == FALSE) lpMsg->message = WM_NULL;
				break;
			case WM_NCACTIVATE:
				if (lpMsg->wParam == FALSE) lpMsg->message = WM_NULL;
				break;
			case WM_SYSCOMMAND:
				if ((lpMsg->wParam & 0xFFF0) == SC_MINIMIZE || (lpMsg->wParam & 0xFFF0) == SC_RESTORE) lpMsg->message = WM_NULL;
				break;
			case WM_KILLFOCUS:
			case WM_ENABLE:
				lpMsg->message = WM_NULL;
				break;
			}
		}
		return result;
	}
};
BOOL PeekMessageAReal(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

// --- PeekMessageW Hook ---
template <typename FuncT>
class PeekMessageWHook : public xNyuHook<PeekMessageWT> {
public:
	static PeekMessageWHook* instance;
	PeekMessageWHook(void* originalAddress) : xNyuHook<PeekMessageWT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("PeekMessageW() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		BOOL result = instance->callTrampoline(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
		if (lpMsg != NULL)
		{
			switch (lpMsg->message)
			{
			case WM_ACTIVATE:
				if (LOWORD(lpMsg->wParam) == WA_INACTIVE) lpMsg->message = WM_NULL;
				break;
			case WM_ACTIVATEAPP:
				if (lpMsg->wParam == FALSE) lpMsg->message = WM_NULL;
				break;
			case WM_NCACTIVATE:
				if (lpMsg->wParam == FALSE) lpMsg->message = WM_NULL;
				break;
			case WM_SYSCOMMAND:
				if ((lpMsg->wParam & 0xFFF0) == SC_MINIMIZE || (lpMsg->wParam & 0xFFF0) == SC_RESTORE) lpMsg->message = WM_NULL;
				break;
			case WM_KILLFOCUS:
			case WM_ENABLE:
				lpMsg->message = WM_NULL;
				break;
			}
		}
		return result;
	}
};
BOOL PeekMessageWReal(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

// --- GetMessageA Hook ---
template <typename FuncT>
class GetMessageAHook : public xNyuHook<GetMessageAT> {
public:
	static GetMessageAHook* instance;
	GetMessageAHook(void* originalAddress) : xNyuHook<GetMessageAT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetMessageA() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		BOOL result = instance->callTrampoline(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
		if (lpMsg != NULL)
		{
			switch (lpMsg->message)
			{
			case WM_ACTIVATE:
				if (LOWORD(lpMsg->wParam) == WA_INACTIVE) lpMsg->message = WM_NULL;
				break;
			case WM_ACTIVATEAPP:
				if (lpMsg->wParam == FALSE) lpMsg->message = WM_NULL;
				break;
			case WM_NCACTIVATE:
				if (lpMsg->wParam == FALSE) lpMsg->message = WM_NULL;
				break;
			case WM_SYSCOMMAND:
				if ((lpMsg->wParam & 0xFFF0) == SC_MINIMIZE || (lpMsg->wParam & 0xFFF0) == SC_RESTORE) lpMsg->message = WM_NULL;
				break;
			case WM_KILLFOCUS:
			case WM_ENABLE:
				lpMsg->message = WM_NULL;
				break;
			}
		}
		return result;
	}
};
BOOL GetMessageAReal(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);

// --- GetMessageW Hook ---
template <typename FuncT>
class GetMessageWHook : public xNyuHook<GetMessageWT> {
public:
	static GetMessageWHook* instance;
	GetMessageWHook(void* originalAddress) : xNyuHook<GetMessageWT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetMessageW() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		BOOL result = instance->callTrampoline(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
		if (lpMsg != NULL)
		{
			switch (lpMsg->message)
			{
			case WM_ACTIVATE:
				if (LOWORD(lpMsg->wParam) == WA_INACTIVE) lpMsg->message = WM_NULL;
				break;
			case WM_ACTIVATEAPP:
				if (lpMsg->wParam == FALSE) lpMsg->message = WM_NULL;
				break;
			case WM_NCACTIVATE:
				if (lpMsg->wParam == FALSE) lpMsg->message = WM_NULL;
				break;
			case WM_SYSCOMMAND:
				if ((lpMsg->wParam & 0xFFF0) == SC_MINIMIZE || (lpMsg->wParam & 0xFFF0) == SC_RESTORE) lpMsg->message = WM_NULL;
				break;
			case WM_KILLFOCUS:
			case WM_ENABLE:
				lpMsg->message = WM_NULL;
				break;
			}
		}
		return result;
	}
};
BOOL GetMessageWReal(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);

// --- ClipCursor Hook ---
template <typename FuncT>
class ClipCursorHook : public xNyuHook<ClipCursorT> {
public:
	static ClipCursorHook* instance;
	ClipCursorHook(void* originalAddress) : xNyuHook<ClipCursorT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(const RECT* lpRect)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("ClipCursor() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		return true;
	}
};
BOOL ClipCursorReal(const RECT* lpRect);

// --- NtUserGetAsyncKeyState Hook ---
template <typename FuncT>
class NtUserGetAsyncKeyStateHook : public xNyuHook<NtUserGetAsyncKeyStateT> {
public:
	static NtUserGetAsyncKeyStateHook* instance;
	NtUserGetAsyncKeyStateHook(void* originalAddress) : xNyuHook<NtUserGetAsyncKeyStateT>(originalAddress, CustomHook) { instance = this; }
	static SHORT __stdcall CustomHook(int vKey)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("NtUserGetAsyncKeyState() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		SHORT result = instance->callTrampoline(vKey);
		if (vKey == VK_MENU || vKey == VK_TAB || vKey == VK_LWIN || vKey == VK_RWIN) result = 0;
		return result;
	}
};
SHORT NtUserGetAsyncKeyStateReal(int vKey);

// --- NtUserGetKeyState Hook ---
template <typename FuncT>
class NtUserGetKeyStateHook : public xNyuHook<NtUserGetKeyStateT> {
public:
	static NtUserGetKeyStateHook* instance;
	NtUserGetKeyStateHook(void* originalAddress) : xNyuHook<NtUserGetKeyStateT>(originalAddress, CustomHook) { instance = this; }
	static SHORT __stdcall CustomHook(int vKey)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("NtUserGetKeyState() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		SHORT result = instance->callTrampoline(vKey);
		if (vKey == VK_MENU || vKey == VK_TAB || vKey == VK_LWIN || vKey == VK_RWIN) result = 0;
		return result;
	}
};
SHORT NtUserGetKeyStateReal(int vKey);

// --- GetLastInputInfo Hook ---
template <typename FuncT>
class GetLastInputInfoHook : public xNyuHook<GetLastInputInfoT> {
private:
	LASTINPUTINFO originalPlii = LASTINPUTINFO();
public:
	static GetLastInputInfoHook* instance;
	GetLastInputInfoHook(void* originalAddress) : xNyuHook<GetLastInputInfoT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(PLASTINPUTINFO plii)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetLastInputInfo() Hook active...", true, "yellow");
			instance->callTrampoline(&instance->originalPlii);
			instance->HookInit = false;
		}
		std::memcpy(plii, &instance->originalPlii, sizeof(LASTINPUTINFO));
		return true;
	}
};
BOOL GetLastInputInfoReal(PLASTINPUTINFO plii);

// --- GetCursorPos Hook ---
template <typename FuncT>
class GetCursorPosHook : public xNyuHook<GetCursorPosT> {
private:
	HWND mainWindowHandle = nullptr;
public:
	static GetCursorPosHook* instance;
	GetCursorPosHook(void* originalAddress) : xNyuHook<GetCursorPosT>(originalAddress, CustomHook) { instance = this; }
	static BOOL __stdcall CustomHook(LPPOINT lpPoint)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("GetCursorPos() Hook active...", true, "yellow");
			instance->HookInit = false;
		}
		BOOL result = instance->callTrampoline(lpPoint);
		if (mainWindowHandle != NULL) {
			RECT rect;
			if (GetClientRect(mainWindowHandle, &rect)) {
				POINT topLeft = { rect.left, rect.top };
				POINT bottomRight = { rect.right, rect.bottom };
				ClientToScreen(mainWindowHandle, &topLeft);
				ClientToScreen(mainWindowHandle, &bottomRight);
				lpPoint->x = max(topLeft.x + 10, min(lpPoint->x, bottomRight.x - 10));
				lpPoint->y = max(topLeft.y + 10, min(lpPoint->y, bottomRight.y - 10));
			}
		}
		return result;
	}
};
BOOL GetCursorPosReal(LPPOINT lpPoint);



// --- Functions ---
bool InitWindowStayActive();
void UninitWindowStayActive();
bool isWinActiveEnabled();

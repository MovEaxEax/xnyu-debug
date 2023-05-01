// Global settings
GameInput SendInputGameInputLast;

// Specific settings
INPUT inputDataFinal[84];
int SendInputAmount = 0;
bool SendInputActive = false;
bool SendInputThreadAlive = false;
bool SendInputSendSync = true;

HANDLE SendInputThreadHandle = nullptr;

DWORD __stdcall SendInputThread() {
    while (SendInputThreadAlive)
    {
        if (SendInputActive)
        {
            SendInput(SendInputAmount, inputDataFinal, sizeof(INPUT));
            SendInputAmount = 0;
            SendInputActive = false;
        }
        Sleep(1);
    }
    return 0;
}

void InitSendInputHook()
{
    SendInputAmount = 0;
    SendInputActive = false;
    SendInputThreadAlive = true;
    SendInputThreadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SendInputThread, 0, 0, 0);
}

void SendInputHookUninit()
{
    SendInputThreadAlive = false;
    TerminateThread(SendInputThreadHandle, 0);
}

void InitPlaySendInputTAS()
{
    std::memset(&SendInputGameInputLast, 0x00, sizeof(GameInput));
    std::memset(&SendInputGameInputLast, 0x00, sizeof(GameInput));
}

void UninitPlaySendInputTAS()
{
}

void InitRecordSendInputTAS()
{
    std::memset(&SendInputGameInputLast, 0x00, sizeof(GameInput));
}

void UninitRecordSendInputTAS()
{
}

void SetSendInput(GameInput SendInputGameInput, BOOL TAS)
{
    SendInputAmount = 0;

    INPUT inputDataKeyboard;
    inputDataKeyboard.type = INPUT_KEYBOARD;
    inputDataKeyboard.ki.time = 0;
    inputDataKeyboard.ki.dwExtraInfo = 0;

    INPUT inputDataMouse;
    inputDataMouse.type = INPUT_MOUSE;
    inputDataMouse.mi.time = 0;
    inputDataMouse.mi.dwExtraInfo = 0;

    if (InputDriverMouseSet == InputDriverz::S3ND1NPUT)
    {
        if (SendInputGameInput.LMB || SendInputGameInputLast.LMB)
        {
            inputDataMouse.mi.dwFlags = (SendInputGameInput.LMB ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP);
            inputDataFinal[SendInputAmount] = inputDataMouse;
            SendInputAmount++;
        }

        if (SendInputGameInput.RMB || SendInputGameInputLast.RMB)
        {
            inputDataMouse.mi.dwFlags = (SendInputGameInput.RMB ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP);
            inputDataFinal[SendInputAmount] = inputDataMouse;
            SendInputAmount++;
        }

        if (SendInputGameInput.MB || SendInputGameInputLast.MB)
        {
            inputDataMouse.mi.dwFlags = (SendInputGameInput.MB ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP);
            inputDataFinal[SendInputAmount] = inputDataMouse;
            SendInputAmount++;
        }

        if (SendInputGameInput.ME1 || SendInputGameInputLast.ME1)
        {
            inputDataMouse.mi.mouseData = XBUTTON1;
            inputDataMouse.mi.dwFlags = (SendInputGameInput.ME1 ? MOUSEEVENTF_XDOWN : MOUSEEVENTF_XUP);
            inputDataFinal[SendInputAmount] = inputDataMouse;
            SendInputAmount++;
            inputDataMouse.mi.mouseData = 0;
        }

        if (SendInputGameInput.ME2 || SendInputGameInputLast.ME2)
        {
            inputDataMouse.mi.mouseData = XBUTTON2;
            inputDataMouse.mi.dwFlags = (SendInputGameInput.ME2 ? MOUSEEVENTF_XDOWN : MOUSEEVENTF_XUP);
            inputDataFinal[SendInputAmount] = inputDataMouse;
            SendInputAmount++;
            inputDataMouse.mi.mouseData = 0;
        }

        if (SendInputGameInput.WHEEL != 0)
        {
            inputDataMouse.mi.dwFlags = MOUSEEVENTF_WHEEL;
            inputDataMouse.mi.mouseData = (DWORD)SendInputGameInput.WHEEL;
            inputDataFinal[SendInputAmount] = inputDataMouse;
            SendInputAmount++;
            inputDataMouse.mi.mouseData = 0;
        }

        if (SendInputGameInput.MOUSEX != 0 || SendInputGameInput.MOUSEY != 0)
        {
            inputDataMouse.mi.dwFlags = MOUSEEVENTF_MOVE;
            if (SendInputGameInput.SETMOUSE)
            {
                inputDataMouse.mi.dwFlags |= MOUSEEVENTF_ABSOLUTE;
                inputDataMouse.mi.dx = (LONG)((MainWindowRect.left + SendInputGameInput.MOUSEX) * (65536 / GetSystemMetrics(SM_CXSCREEN)));
                inputDataMouse.mi.dy = (LONG)((MainWindowRect.top + SendInputGameInput.MOUSEY) * (65536 / GetSystemMetrics(SM_CYSCREEN)));
            }
            else
            {
                inputDataMouse.mi.dx = (LONG)SendInputGameInput.MOUSEX;
                inputDataMouse.mi.dy = (LONG)SendInputGameInput.MOUSEY;
            }
            inputDataFinal[SendInputAmount] = inputDataMouse;
            SendInputAmount++;
            inputDataMouse.mi.dx = 0;
            inputDataMouse.mi.dy = 0;
        }

    }

    if (InputDriverKeyboardSet == InputDriverz::S3ND1NPUT)
    {
        if (SendInputGameInput.ESC || SendInputGameInputLast.ESC)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_ESCAPE, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.ESC ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.TAB || SendInputGameInputLast.TAB)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_TAB, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.TAB ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.LSHIFT || SendInputGameInputLast.LSHIFT)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.LSHIFT ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.RSHIFT || SendInputGameInputLast.RSHIFT)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_RSHIFT, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.RSHIFT ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.CTRL || SendInputGameInputLast.CTRL)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_CONTROL, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.CTRL ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.ALT || SendInputGameInputLast.ALT)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_MENU, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.ALT ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.BACK || SendInputGameInputLast.BACK)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_BACK, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.BACK ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.RETURN || SendInputGameInputLast.RETURN)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_RETURN, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.RETURN ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.SPACE || SendInputGameInputLast.SPACE)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_SPACE, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.SPACE ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.AUP || SendInputGameInputLast.AUP)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_UP, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.AUP ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.ARIGHT || SendInputGameInputLast.ARIGHT)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_RIGHT, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.ARIGHT ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.ADOWN || SendInputGameInputLast.ADOWN)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_DOWN, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.ADOWN ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.ALEFT || SendInputGameInputLast.ALEFT)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_LEFT, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.ALEFT ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.D0 || SendInputGameInputLast.D0)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x30, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.D0 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.D1 || SendInputGameInputLast.D1)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x31, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.D1 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.D2 || SendInputGameInputLast.D2)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x32, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.D2 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.D3 || SendInputGameInputLast.D3)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x33, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.D3 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.D4 || SendInputGameInputLast.D4)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x34, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.D4 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.D5 || SendInputGameInputLast.D5)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x35, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.D5 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.D6 || SendInputGameInputLast.D6)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x36, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.D6 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.D7 || SendInputGameInputLast.D7)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x37, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.D7 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.D8 || SendInputGameInputLast.D8)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x38, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.D8 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.D9 || SendInputGameInputLast.D9)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x39, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.D9 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.A || SendInputGameInputLast.A)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x41, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.A ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.B || SendInputGameInputLast.B)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x42, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.B ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.C || SendInputGameInputLast.C)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x43, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.C ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.D || SendInputGameInputLast.D)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x44, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.D ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.E || SendInputGameInputLast.E)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x45, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.E ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F || SendInputGameInputLast.F)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x46, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.G || SendInputGameInputLast.G)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x47, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.G ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.H || SendInputGameInputLast.H)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x48, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.H ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.I || SendInputGameInputLast.I)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x49, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.I ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.J || SendInputGameInputLast.J)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x4A, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.J ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.K || SendInputGameInputLast.K)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x4B, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.K ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.L || SendInputGameInputLast.L)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x4C, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.L ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.M || SendInputGameInputLast.M)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x4D, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.M ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.N || SendInputGameInputLast.N)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x4E, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.N ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.O || SendInputGameInputLast.O)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x4F, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.O ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.P || SendInputGameInputLast.P)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x50, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.P ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.Q || SendInputGameInputLast.Q)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x51, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.Q ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.R || SendInputGameInputLast.R)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x52, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.R ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.S || SendInputGameInputLast.S)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x53, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.S ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.T || SendInputGameInputLast.T)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x54, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.T ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.U || SendInputGameInputLast.U)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x55, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.U ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.V || SendInputGameInputLast.V)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x56, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.V ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.W || SendInputGameInputLast.W)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x57, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.W ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.X || SendInputGameInputLast.X)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x58, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.X ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.Y || SendInputGameInputLast.Y)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x59, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.Y ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.Z || SendInputGameInputLast.Z)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(0x5A, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.Z ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUM0 || SendInputGameInputLast.NUM0)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD0, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUM0 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUM1 || SendInputGameInputLast.NUM1)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD1, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUM1 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUM2 || SendInputGameInputLast.NUM2)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD2, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUM2 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUM3 || SendInputGameInputLast.NUM3)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD3, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUM3 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUM4 || SendInputGameInputLast.NUM4)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD4, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUM4 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUM5 || SendInputGameInputLast.NUM5)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD5, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUM5 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUM6 || SendInputGameInputLast.NUM6)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD6, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUM6 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUM7 || SendInputGameInputLast.NUM7)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD7, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUM7 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUM8 || SendInputGameInputLast.NUM8)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD8, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUM8 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUM9 || SendInputGameInputLast.NUM9)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD9, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUM9 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUMDIV || SendInputGameInputLast.NUMDIV)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_DIVIDE, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUMDIV ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUMMUL || SendInputGameInputLast.NUMMUL)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_MULTIPLY, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUMMUL ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUMMIN || SendInputGameInputLast.NUMMIN)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_SUBTRACT, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUMMIN ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUMPLU || SendInputGameInputLast.NUMPLU)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_ADD, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUMPLU ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUMRET || SendInputGameInputLast.NUMRET)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_RETURN, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUMRET ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.NUMDEL || SendInputGameInputLast.NUMDEL)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_DELETE, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.NUMDEL ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F1 || SendInputGameInputLast.F1)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F1, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F1 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F2 || SendInputGameInputLast.F2)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F2, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F2 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F3 || SendInputGameInputLast.F3)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F3, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F3 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F4 || SendInputGameInputLast.F4)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F4, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F4 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F5 || SendInputGameInputLast.F5)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F5, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F5 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F6 || SendInputGameInputLast.F6)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F6, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F6 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F7 || SendInputGameInputLast.F7)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F7, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F7 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F8 || SendInputGameInputLast.F8)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F8, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F8 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F9 || SendInputGameInputLast.F9)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F9, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F9 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F10 || SendInputGameInputLast.F10)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F10, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F10 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F11 || SendInputGameInputLast.F11)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F11, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F11 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

        if (SendInputGameInput.F12 || SendInputGameInputLast.F12)
        {
            inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F12, MAPVK_VK_TO_VSC);
            inputDataKeyboard.ki.dwFlags = (SendInputGameInput.F12 ? 0x00 : KEYEVENTF_KEYUP);
            inputDataFinal[SendInputAmount] = inputDataKeyboard;
            SendInputAmount++;
        }

    }

    std::memcpy(&SendInputGameInputLast, &SendInputGameInput, sizeof(GameInput));

    if (SendInputAmount > 0)
    {
        std::cout << "SendInputAmount: " << std::dec << SendInputAmount << std::endl;
        SendInputActive = true;
        while (SendInputActive) Sleep(1);
    }

    if (InputDriverMouseSet == InputDriverz::S3ND1NPUT) TASSynchronizer.SendInputMouseSend = false;
    if (InputDriverKeyboardSet == InputDriverz::S3ND1NPUT) TASSynchronizer.SendInputKeyboardSend = false;
}



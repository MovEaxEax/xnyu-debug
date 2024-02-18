#include "pch.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "InputLayout.h"
#include "Overclocker.h"
#include "Threadhooker.h"
#include "xNyuHook.h"
#include "SendInputHook.h"



// --- Variable ---
HANDLE SendInputAllMutex = CreateMutex(NULL, FALSE, NULL);

INPUT SendInputstateMouseSet[84];
int SendInputstateMouseSetAmount = 0;
bool SendInputstateMouseSetDone = false;

INPUT SendInputstateKeyboardSet[84];
int SendInputstateKeyboardSetAmount = 0;
bool SendInputstateKeyboardSetDone = false;

HANDLE SendInputThreadHandle = nullptr;

bool SendInputThreadAlive = false;
HANDLE SendInputAliveMutex = CreateMutex(NULL, FALSE, NULL);



// -- Functions ---
void SetSendInputThreadAlive(bool value)
{
    WaitForSingleObject(SendInputAliveMutex, INFINITE);
    SendInputThreadAlive = value;
    ReleaseMutex(SendInputAliveMutex);
}

bool IsSendInputThreadAlive()
{
    WaitForSingleObject(SendInputAliveMutex, INFINITE);
    bool result = SendInputThreadAlive;
    ReleaseMutex(SendInputAliveMutex);
    return result;
}

DWORD __stdcall SendInputThread() {
    while (true)
    {
        if (IsSendInputThreadAlive()) break;

        WaitForSingleObject(SendInputAllMutex, INFINITE);

        if (SendInputstateMouseSetDone)
        {
            SendInput(SendInputstateMouseSetAmount, SendInputstateMouseSet, sizeof(INPUT));
            SendInputstateMouseSetAmount = 0;
            SendInputstateMouseSetDone = false;
        }

        if (SendInputstateKeyboardSetDone)
        {
            SendInput(SendInputstateKeyboardSetAmount, SendInputstateKeyboardSet, sizeof(INPUT));
            SendInputstateKeyboardSetAmount = 0;
            SendInputstateKeyboardSetDone = false;
        }

        ReleaseMutex(SendInputAllMutex);
        SleepExReal(1);
    }
    return 0;
}

bool SendInputIsSetMouseDone()
{
    WaitForSingleObject(SendInputAllMutex, INFINITE);
    bool result = !SendInputstateMouseSetDone;
    ReleaseMutex(SendInputAllMutex);
    return result;
}

bool SendInputIsSetKeyboardDone()
{
    WaitForSingleObject(SendInputAllMutex, INFINITE);
    bool result = !SendInputstateKeyboardSetDone;
    ReleaseMutex(SendInputAllMutex);
    return result;
}

void SendInputSetMouse(GameInput input, GameInput inputLast)
{
    WaitForSingleObject(SendInputAllMutex, INFINITE);

    SendInputstateMouseSetAmount = 0;

    INPUT inputDataMouse;
    inputDataMouse.type = INPUT_MOUSE;
    inputDataMouse.mi.time = 0;
    inputDataMouse.mi.dwExtraInfo = 0;

    if (input.LMB || inputLast.LMB)
    {
        inputDataMouse.mi.dwFlags = (input.LMB ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP);
        SendInputstateMouseSet[SendInputstateMouseSetAmount] = inputDataMouse;
        SendInputstateMouseSetAmount++;
    }

    if (input.RMB || inputLast.RMB)
    {
        inputDataMouse.mi.dwFlags = (input.RMB ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP);
        SendInputstateMouseSet[SendInputstateMouseSetAmount] = inputDataMouse;
        SendInputstateMouseSetAmount++;
    }

    if (input.MB || inputLast.MB)
    {
        inputDataMouse.mi.dwFlags = (input.MB ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP);
        SendInputstateMouseSet[SendInputstateMouseSetAmount] = inputDataMouse;
        SendInputstateMouseSetAmount++;
    }

    if (input.ME1 || inputLast.ME1)
    {
        inputDataMouse.mi.mouseData = XBUTTON1;
        inputDataMouse.mi.dwFlags = (input.ME1 ? MOUSEEVENTF_XDOWN : MOUSEEVENTF_XUP);
        SendInputstateMouseSet[SendInputstateMouseSetAmount] = inputDataMouse;
        SendInputstateMouseSetAmount++;
        inputDataMouse.mi.mouseData = 0;
    }

    if (input.ME2 || inputLast.ME2)
    {
        inputDataMouse.mi.mouseData = XBUTTON2;
        inputDataMouse.mi.dwFlags = (input.ME2 ? MOUSEEVENTF_XDOWN : MOUSEEVENTF_XUP);
        SendInputstateMouseSet[SendInputstateMouseSetAmount] = inputDataMouse;
        SendInputstateMouseSetAmount++;
        inputDataMouse.mi.mouseData = 0;
    }

    if (input.WHEEL != 0)
    {
        inputDataMouse.mi.dwFlags = MOUSEEVENTF_WHEEL;
        inputDataMouse.mi.mouseData = (DWORD)input.WHEEL;
        SendInputstateMouseSet[SendInputstateMouseSetAmount] = inputDataMouse;
        SendInputstateMouseSetAmount++;
        inputDataMouse.mi.mouseData = 0;
    }

    if (input.MOUSEX != 0 || input.MOUSEY != 0)
    {
        inputDataMouse.mi.dwFlags = MOUSEEVENTF_MOVE;
        if (input.SETMOUSE)
        {
            RECT windowRect = GetMainWindowRect();
            inputDataMouse.mi.dwFlags |= MOUSEEVENTF_ABSOLUTE;
            inputDataMouse.mi.dx = (LONG)((windowRect.left + input.MOUSEX) * (65536 / GetSystemMetrics(SM_CXSCREEN)));
            inputDataMouse.mi.dy = (LONG)((windowRect.top + input.MOUSEY) * (65536 / GetSystemMetrics(SM_CYSCREEN)));
        }
        else
        {
            inputDataMouse.mi.dx = (LONG)input.MOUSEX;
            inputDataMouse.mi.dy = (LONG)input.MOUSEY;
        }
        SendInputstateMouseSet[SendInputstateMouseSetAmount] = inputDataMouse;
        SendInputstateMouseSetAmount++;
        inputDataMouse.mi.dx = 0;
        inputDataMouse.mi.dy = 0;
    }

    if (SendInputstateMouseSetAmount > 0) SendInputstateMouseSetDone = true;
    ReleaseMutex(SendInputAllMutex);
}

void SendInputSetKeyboard(GameInput input, GameInput inputLast)
{
    WaitForSingleObject(SendInputAllMutex, INFINITE);

    INPUT inputDataKeyboard;
    inputDataKeyboard.type = INPUT_KEYBOARD;
    inputDataKeyboard.ki.time = 0;
    inputDataKeyboard.ki.dwExtraInfo = 0;

    SendInputstateKeyboardSetAmount = 0;

    if (input.ESC || inputLast.ESC)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_ESCAPE, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.ESC ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.TAB || inputLast.TAB)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_TAB, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.TAB ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.LSHIFT || inputLast.LSHIFT)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.LSHIFT ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.RSHIFT || inputLast.RSHIFT)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_RSHIFT, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.RSHIFT ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.CTRL || inputLast.CTRL)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_CONTROL, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.CTRL ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.ALT || inputLast.ALT)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_MENU, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.ALT ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.BACK || inputLast.BACK)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_BACK, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.BACK ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.RETURN || inputLast.RETURN)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_RETURN, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.RETURN ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.SPACE || inputLast.SPACE)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_SPACE, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.SPACE ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.AUP || inputLast.AUP)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_UP, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.AUP ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.ARIGHT || inputLast.ARIGHT)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_RIGHT, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.ARIGHT ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.ADOWN || inputLast.ADOWN)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_DOWN, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.ADOWN ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.ALEFT || inputLast.ALEFT)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_LEFT, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.ALEFT ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.D0 || inputLast.D0)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x30, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.D0 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.D1 || inputLast.D1)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x31, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.D1 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.D2 || inputLast.D2)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x32, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.D2 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.D3 || inputLast.D3)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x33, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.D3 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.D4 || inputLast.D4)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x34, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.D4 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.D5 || inputLast.D5)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x35, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.D5 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.D6 || inputLast.D6)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x36, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.D6 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.D7 || inputLast.D7)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x37, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.D7 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.D8 || inputLast.D8)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x38, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.D8 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.D9 || inputLast.D9)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x39, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.D9 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.A || inputLast.A)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x41, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.A ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.B || inputLast.B)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x42, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.B ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.C || inputLast.C)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x43, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.C ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.D || inputLast.D)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x44, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.D ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.E || inputLast.E)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x45, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.E ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F || inputLast.F)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x46, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.G || inputLast.G)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x47, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.G ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.H || inputLast.H)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x48, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.H ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.I || inputLast.I)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x49, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.I ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.J || inputLast.J)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x4A, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.J ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.K || inputLast.K)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x4B, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.K ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.L || inputLast.L)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x4C, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.L ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.M || inputLast.M)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x4D, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.M ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.N || inputLast.N)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x4E, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.N ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.O || inputLast.O)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x4F, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.O ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.P || inputLast.P)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x50, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.P ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.Q || inputLast.Q)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x51, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.Q ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.R || inputLast.R)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x52, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.R ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.S || inputLast.S)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x53, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.S ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.T || inputLast.T)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x54, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.T ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.U || inputLast.U)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x55, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.U ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.V || inputLast.V)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x56, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.V ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.W || inputLast.W)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x57, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.W ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.X || inputLast.X)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x58, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.X ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.Y || inputLast.Y)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x59, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.Y ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.Z || inputLast.Z)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(0x5A, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.Z ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUM0 || inputLast.NUM0)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD0, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUM0 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUM1 || inputLast.NUM1)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD1, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUM1 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUM2 || inputLast.NUM2)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD2, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUM2 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUM3 || inputLast.NUM3)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD3, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUM3 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUM4 || inputLast.NUM4)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD4, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUM4 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUM5 || inputLast.NUM5)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD5, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUM5 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUM6 || inputLast.NUM6)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD6, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUM6 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUM7 || inputLast.NUM7)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD7, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUM7 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUM8 || inputLast.NUM8)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD8, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUM8 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUM9 || inputLast.NUM9)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_NUMPAD9, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUM9 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUMDIV || inputLast.NUMDIV)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_DIVIDE, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUMDIV ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUMMUL || inputLast.NUMMUL)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_MULTIPLY, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUMMUL ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUMMIN || inputLast.NUMMIN)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_SUBTRACT, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUMMIN ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUMPLU || inputLast.NUMPLU)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_ADD, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUMPLU ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUMRET || inputLast.NUMRET)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_RETURN, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUMRET ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.NUMDEL || inputLast.NUMDEL)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_DELETE, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.NUMDEL ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F1 || inputLast.F1)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F1, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F1 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F2 || inputLast.F2)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F2, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F2 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F3 || inputLast.F3)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F3, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F3 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F4 || inputLast.F4)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F4, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F4 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F5 || inputLast.F5)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F5, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F5 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F6 || inputLast.F6)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F6, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F6 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F7 || inputLast.F7)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F7, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F7 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F8 || inputLast.F8)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F8, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F8 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F9 || inputLast.F9)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F9, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F9 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F10 || inputLast.F10)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F10, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F10 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F11 || inputLast.F11)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F11, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F11 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (input.F12 || inputLast.F12)
    {
        inputDataKeyboard.ki.wScan = MapVirtualKey(VK_F12, MAPVK_VK_TO_VSC);
        inputDataKeyboard.ki.dwFlags = (input.F12 ? 0x00 : KEYEVENTF_KEYUP);
        SendInputstateKeyboardSet[SendInputstateKeyboardSetAmount] = inputDataKeyboard;
        SendInputstateKeyboardSetAmount++;
    }

    if (SendInputstateKeyboardSetAmount > 0) SendInputstateKeyboardSetDone = true;
    ReleaseMutex(SendInputAllMutex);
}

bool SendInputHookInit()
{
    try
    {
        SetSendInputThreadAlive(true);
        SleepExReal(100);
        SendInputThreadHandle = CreateThreadReal(0, 0, (LPTHREAD_START_ROUTINE)SendInputThread, 0, 0, 0);
    }
    catch (...)
    {
        DebugConsoleOutput("Error: InitSendInputHook()", false, "red");
        return false;
    }
    return true;
}

bool SendInputHookUninit()
{
    try
    {
        SetSendInputThreadAlive(true);
        SleepExReal(100);
        TerminateThreadReal(SendInputThreadHandle, 0);
    }
    catch (...)
    {
        DebugConsoleOutput("Error: SendInputHookUninit()", false, "red");
        return false;
    }
    return true;
}

bool IsSendInputHookActive()
{
    return IsSendInputThreadAlive();
}



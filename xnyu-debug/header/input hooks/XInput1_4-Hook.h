#pragma once
#include <XInput.h>
#pragma comment(lib,"XInput.lib")

// Global hook settings
typedef DWORD(__stdcall* XInput1_4GetStateT)(DWORD dwUserIndex, XINPUT_STATE* pState);
XInput1_4GetStateT pXInput1_4GetState = nullptr;
typedef void(__stdcall* GetXInput1_4T)(BOOL TAS, GameInput* DST, std::string device);
GetXInput1_4T pGetXInput1_4 = nullptr;

subhook::Hook XInput1_4SubHook;

void* XInput1_4OriginalAddress;
void* XInput1_4HookAddress;

bool GetXInput1_4RetrieveInformation = false;
bool GetXInput1_4SendInformation = false;
bool XInput1_4GetInformation = false;
bool XInput1_4DisableForGame = false;
bool GetXInput1_4TASMode = false;
bool XInput1_4SendSync = true;

GameInput XInput1_4GameInputCurrent;
GameInput XInput1_4GameInputLast;
GameInput* GetXInput1_4DST = nullptr;

// Specific settings
XINPUT_STATE XInput1_4SendState;
XINPUT_STATE XInput1_4InputState;

int XInput1_4PacketNumber = 0;


HANDLE XInput1_4ThreadMutex = CreateMutex(NULL, FALSE, NULL);

bool XInput1_4TASSyncStateJoystickSet()
{
    WaitForSingleObject(XInput1_4ThreadMutex, INFINITE);
    bool finished = TASSynchronizer.XInput1_4JoystickSend || GetXInput1_4SendInformation;
    ReleaseMutex(XInput1_4ThreadMutex);
    return finished;
}

bool XInput1_4TASSyncStateJoystickGet()
{
    WaitForSingleObject(XInput1_4ThreadMutex, INFINITE);
    bool finished = TASSynchronizer.XInput1_4JoystickGet || XInput1_4GetInformation;
    ReleaseMutex(XInput1_4ThreadMutex);
    return finished;
}

void XInput1_4TLockMutex()
{
    WaitForSingleObject(XInput1_4ThreadMutex, INFINITE);
}

void XInput1_4TReleaseMutex()
{
    ReleaseMutex(XInput1_4ThreadMutex);
}

DWORD __stdcall XInput1_4Hook(DWORD dwUserIndex, XINPUT_STATE* pState)
{
    // Remove hook to restore original function
    WaitForSingleObject(XInput1_4ThreadMutex, INFINITE);

    XInput1_4SubHook.Remove();

    // The return value of this function
    std::memset(&XInput1_4InputState, 0x00, sizeof(XINPUT_STATE));

    DWORD result = pXInput1_4GetState(dwUserIndex, pState);
    std::memcpy(&XInput1_4InputState, pState, sizeof(XINPUT_STATE));

    // Packet index handling
    XInput1_4PacketNumber++;
    if (XInput1_4PacketNumber > 0xDEADBEEF) XInput1_4PacketNumber = 0;
    pState->dwPacketNumber = XInput1_4PacketNumber;

    if (GlobalSettings.config_tashook == "xinput1_4" || GlobalSettings.config_tashook == "xinput1_3")
    {
        ReleaseMutex(XInput1_4ThreadMutex);
        pTASRoutine();
        WaitForSingleObject(XInput1_4ThreadMutex, INFINITE);
    }

    if (GetXInput1_4SendInformation)
    {

        if (dwUserIndex == 0)
        {
            result = ERROR_SUCCESS;
            XInput1_4SendState.dwPacketNumber = pState->dwPacketNumber;
            std::memset(pState, 0x00, sizeof(XINPUT_STATE));
            std::memcpy(pState, &XInput1_4SendState, sizeof(XINPUT_STATE));

            TASSynchronizer.XInput1_4JoystickSend = false;
        }
        else
        {
            result = pXInput1_4GetState(dwUserIndex, pState);
        }

        GetXInput1_4SendInformation = TASSynchronizer.XInput1_4JoystickSend;
    }
    else
    {
        if (XInput1_4GetInformation)
        {
            pGetXInput1_4(false, GetXInput1_4DST, "joystick");
            TASSynchronizer.XInput1_4JoystickGet = false;
            XInput1_4GetInformation = false;
        }
        else if (XInput1_4DisableForGame)
        {
            std::memset(pState, 0x00, sizeof(XINPUT_STATE));
            result = ERROR_SUCCESS;
        }
    }
    // Init Hook again
    while (!XInput1_4SubHook.IsInstalled())
    {
        if (sizeof(void*) == 8) XInput1_4SubHook.Install(XInput1_4OriginalAddress, XInput1_4HookAddress, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) XInput1_4SubHook.Install(XInput1_4OriginalAddress, XInput1_4HookAddress);
    }

    ReleaseMutex(XInput1_4ThreadMutex);

    return result;
}



BOOL XInput1_4HookUninit()
{
    WaitForSingleObject(XInput1_4ThreadMutex, INFINITE);
    XInput1_4SubHook.Remove();
    ReleaseMutex(XInput1_4ThreadMutex);
    return true;
}

void InitPlayXInput1_4TAS()
{
    WaitForSingleObject(XInput1_4ThreadMutex, INFINITE);
    XInput1_4DisableForGame = true;
    GetXInput1_4SendInformation = true;
    std::memset(&XInput1_4GameInputCurrent, 0x00, sizeof(GameInput));
    std::memset(&XInput1_4GameInputLast, 0x00, sizeof(GameInput));
    ReleaseMutex(XInput1_4ThreadMutex);
}

void UninitPlayXInput1_4TAS()
{
    WaitForSingleObject(XInput1_4ThreadMutex, INFINITE);
    XInput1_4DisableForGame = false;
    GetXInput1_4SendInformation = false;
    std::memset(&XInput1_4GameInputCurrent, 0x00, sizeof(GameInput));
    std::memset(&XInput1_4GameInputLast, 0x00, sizeof(GameInput));
    ReleaseMutex(XInput1_4ThreadMutex);
}

void InitRecordXInput1_4TAS()
{
    WaitForSingleObject(XInput1_4ThreadMutex, INFINITE);
    if (TASRecordFrameByFrameInputTrigger)
    {
        XInput1_4DisableForGame = true;
        GetXInput1_4SendInformation = true;
    }
    std::memset(&XInput1_4GameInputCurrent, 0x00, sizeof(GameInput));
    std::memset(&XInput1_4GameInputLast, 0x00, sizeof(GameInput));
    ReleaseMutex(XInput1_4ThreadMutex);
}

void UninitRecordXInput1_4TAS()
{
    WaitForSingleObject(XInput1_4ThreadMutex, INFINITE);
    if (TASRecordFrameByFrameInputTrigger)
    {
        XInput1_4DisableForGame = false;
        GetXInput1_4SendInformation = false;
    }
    std::memset(&XInput1_4GameInputCurrent, 0x00, sizeof(GameInput));
    std::memset(&XInput1_4GameInputLast, 0x00, sizeof(GameInput));
    ReleaseMutex(XInput1_4ThreadMutex);
}



void __stdcall GetXInput1_4(BOOL TAS, GameInput* DST, std::string device)
{
    WaitForSingleObject(XInput1_4ThreadMutex, INFINITE);
    GetXInput1_4DST = DST;

    if (TAS)
    {
        XInput1_4GetInformation = true;
        ReleaseMutex(XInput1_4ThreadMutex);
        return;
    }

    std::memset(&XInput1_4GameInputCurrent, 0x00, sizeof(GameInput));

    if (InputDriverJoystickGet == InputDriverz::X1NPUT1_4)
    {
        // Joystick input
        int RAXISX = static_cast<int>((static_cast<float>(XInput1_4InputState.Gamepad.sThumbRX) / 32767.0f) * 1000.0f);
        int RAXISY = static_cast<int>((static_cast<float>(XInput1_4InputState.Gamepad.sThumbRY) / 32767.0f) * 1000.0f);
        int LAXISX = static_cast<int>((static_cast<float>(XInput1_4InputState.Gamepad.sThumbLX) / 32767.0f) * 1000.0f);
        int LAXISY = static_cast<int>((static_cast<float>(XInput1_4InputState.Gamepad.sThumbLY) / 32767.0f) * 1000.0f);

        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_A) XInput1_4GameInputCurrent.JOYA = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_B) XInput1_4GameInputCurrent.JOYB = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_X) XInput1_4GameInputCurrent.JOYX = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) XInput1_4GameInputCurrent.JOYY = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) XInput1_4GameInputCurrent.JOYRB = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) XInput1_4GameInputCurrent.JOYLB = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_START) XInput1_4GameInputCurrent.JOYSTART = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) XInput1_4GameInputCurrent.JOYSELECT = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) XInput1_4GameInputCurrent.JOYUP = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) XInput1_4GameInputCurrent.JOYDOWN = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) XInput1_4GameInputCurrent.JOYLEFT = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) XInput1_4GameInputCurrent.JOYRIGHT = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) XInput1_4GameInputCurrent.JOYRS = true;
        if (XInput1_4InputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) XInput1_4GameInputCurrent.JOYLS = true;
        if (XInput1_4InputState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) XInput1_4GameInputCurrent.JOYRT = XInput1_4InputState.Gamepad.bRightTrigger;
        if (XInput1_4InputState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) XInput1_4GameInputCurrent.JOYLT = XInput1_4InputState.Gamepad.bLeftTrigger;
        if (RAXISX > 99 || RAXISX < -99) XInput1_4GameInputCurrent.JOYRAXISX = RAXISX;
        if (RAXISY > 99 || RAXISY < -99) XInput1_4GameInputCurrent.JOYRAXISY = RAXISY;
        if (LAXISX > 99 || LAXISX < -99) XInput1_4GameInputCurrent.JOYLAXISX = LAXISX;
        if (LAXISY > 99 || LAXISY < -99) XInput1_4GameInputCurrent.JOYLAXISY = LAXISY;
    }

    std::memcpy(GetXInput1_4DST, &XInput1_4GameInputCurrent, sizeof(GameInput));
    ReleaseMutex(XInput1_4ThreadMutex);
}

void SetXInput1_4(GameInput XInput1_4GameInput, BOOL TAS)
{
    WaitForSingleObject(XInput1_4ThreadMutex, INFINITE);
    GetXInput1_4TASMode = TAS;
    GetXInput1_4SendInformation = true;

    if (InputDriverJoystickSet == InputDriverz::X1NPUT1_4)
    {
        std::memset(&XInput1_4SendState, 0x00, sizeof(XINPUT_STATE));

        SHORT RAXISX = static_cast<SHORT>((static_cast<float>(XInput1_4GameInput.JOYRAXISX) / 1000.0f) * 32767.0f);
        SHORT RAXISY = static_cast<SHORT>((static_cast<float>(XInput1_4GameInput.JOYRAXISY) / 1000.0f) * 32767.0f);
        SHORT LAXISX = static_cast<SHORT>((static_cast<float>(XInput1_4GameInput.JOYLAXISX) / 1000.0f) * 32767.0f);
        SHORT LAXISY = static_cast<SHORT>((static_cast<float>(XInput1_4GameInput.JOYLAXISY) / 1000.0f) * 32767.0f);

        if (XInput1_4GameInput.JOYA) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_A;
        if (XInput1_4GameInput.JOYB) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_B;
        if (XInput1_4GameInput.JOYX) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_X;
        if (XInput1_4GameInput.JOYY) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_Y;
        if (XInput1_4GameInput.JOYRB) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;
        if (XInput1_4GameInput.JOYLB) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_SHOULDER;
        if (XInput1_4GameInput.JOYSTART) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_START;
        if (XInput1_4GameInput.JOYSELECT) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_BACK;
        if (XInput1_4GameInput.JOYUP) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_UP;
        if (XInput1_4GameInput.JOYDOWN) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
        if (XInput1_4GameInput.JOYLEFT) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
        if (XInput1_4GameInput.JOYRIGHT) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
        if (XInput1_4GameInput.JOYRS) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_THUMB;
        if (XInput1_4GameInput.JOYLS) XInput1_4SendState.Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_THUMB;
        XInput1_4SendState.Gamepad.bRightTrigger = (BYTE)XInput1_4GameInput.JOYRT;
        XInput1_4SendState.Gamepad.bLeftTrigger = (BYTE)XInput1_4GameInput.JOYLT;
        XInput1_4SendState.Gamepad.sThumbRX = RAXISX;
        XInput1_4SendState.Gamepad.sThumbRY = RAXISY;
        XInput1_4SendState.Gamepad.sThumbLX = LAXISX;
        XInput1_4SendState.Gamepad.sThumbLY = LAXISY;
    }
    ReleaseMutex(XInput1_4ThreadMutex);
}

BOOL XInput1_4HookInit()
{
    // Detect the XInput module handle
    HMODULE XInputDllHandle = GetModuleHandleA("xinput1_4.dll");
    if (XInputDllHandle == NULL)
    {
        XInputDllHandle = GetModuleHandleA("xinput1_3.dll");
        if (XInputDllHandle == NULL) return false;
    }

    pGetXInput1_4 = (GetXInput1_4T)GetXInput1_4;

    // Set the hook addresses
    XInput1_4OriginalAddress = (void*)GetProcAddress(XInputDllHandle, "XInputGetState");
    XInput1_4HookAddress = (void*)XInput1_4Hook;
    pXInput1_4GetState = (XInput1_4GetStateT)XInput1_4OriginalAddress;

    if (sizeof(void*) == 8) XInput1_4SubHook.Install(XInput1_4OriginalAddress, XInput1_4HookAddress, subhook::HookFlags::HookFlag64BitOffset);
    if (sizeof(void*) == 4) XInput1_4SubHook.Install(XInput1_4OriginalAddress, XInput1_4HookAddress);

    return true;
}






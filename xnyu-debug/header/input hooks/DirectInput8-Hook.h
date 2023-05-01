#pragma once
#include <dinput.h>
#include <Xinput.h>
#pragma comment(lib, "Dinput8.lib")
#pragma comment(lib, "Dxguid.lib")

// Global hook settings
typedef HRESULT(__stdcall* DirectInput8GetDeviceStateT)(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);
DirectInput8GetDeviceStateT pDirectInput8DevicGetState = nullptr;
typedef void(__stdcall* GetDirectInput8T)(BOOL TAS, GameInput* DST, std::string device);
GetDirectInput8T pGetDirectInput8 = nullptr;

subhook::Hook DirectInput8SubHook;

void* DirectInput8OriginalAddress;
void* DirectInput8HookAddress;

bool DirectInput8RetrieveInformation = false;
bool DirectInput8SendInformation = false;
bool DirectInput8GetInformation = false;
bool DirectInput8DisableForGame = false;
bool DirectInput8TASMode = false;

GameInput DirectInput8GameInputCurrent;
GameInput DirectInput8GameInputLast;
GameInput* GetDirectInput8DSTAll;
GameInput* GetDirectInput8DSTMouse;
GameInput* GetDirectInput8DSTKeyboard;
GameInput* GetDirectInput8DSTJoystick;

// Specific settings
IDirectInput8* pDirectInput_DI8 = nullptr;
IDirectInputDevice8* pDirectInput8_Device = nullptr;
LPDIRECTINPUTDEVICE8 DirectInput8DeviceJoystick;
LPDIRECTINPUTDEVICE8 DirectInput8DeviceKeyboard;
LPDIRECTINPUTDEVICE8 DirectInput8DeviceMouse;

DIJOYSTATE DirectInput8JoystickSendState;
DIJOYSTATE DirectInput8JoystickInputState;
DIMOUSESTATE DirectInput8MouseSendState;
DIMOUSESTATE DirectInput8MouseInputState;
BYTE DirectInput8KeyboardSendState[256];
BYTE DirectInput8KeyboardInputState[256];

HRESULT __stdcall DirectInput8Hook(IDirectInputDevice8* pDevice, DWORD cbData, LPVOID lpvData)
{
    if(pDirectInput8_Device != pDevice) pDirectInput8_Device = pDevice;

    // Remove hook to restore original function
    DirectInput8SubHook.Remove();

    // The return value of this function
    HRESULT result = pDirectInput8DevicGetState(pDevice, cbData, lpvData);

    std::memset(&DirectInput8JoystickInputState, 0x00, sizeof(DIJOYSTATE));
    std::memset(&DirectInput8MouseInputState, 0x00, sizeof(DIMOUSESTATE));
    std::memset(&DirectInput8KeyboardInputState, 0x00, 256);
    if (cbData == sizeof(DIJOYSTATE) || cbData == sizeof(DIJOYSTATE2)) std::memcpy(&DirectInput8JoystickInputState, lpvData, sizeof(DIJOYSTATE));
    if (cbData == sizeof(DIMOUSESTATE) || cbData == sizeof(DIMOUSESTATE2)) std::memcpy(&DirectInput8MouseInputState, lpvData, sizeof(DIMOUSESTATE));
    if (cbData == 256) std::memcpy(&DirectInput8KeyboardInputState, lpvData, 256);

    // TAS routine
    if (GlobalSettings.config_tashook == "directinput8")
    {
        pTASRoutine();
    }

    if (DirectInput8SendInformation)
    {
        bool sent = false;

        if (InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8 && TASSynchronizer.DirectInput8JoystickSend)
        {
            if (cbData == sizeof(DIJOYSTATE))
            {
                result = ERROR_SUCCESS;
                std::memcpy(lpvData, &DirectInput8JoystickSendState, sizeof(DIJOYSTATE));
                sent = true;
                TASSynchronizer.DirectInput8JoystickSend = false;
            }

            if (cbData == sizeof(DIJOYSTATE2))
            {
                result = ERROR_SUCCESS;
                DIJOYSTATE2 converted = DIJOYSTATE2();
                std::memset(&converted, 0x00, sizeof(DIJOYSTATE2));
                converted.rgdwPOV[0] = -1;
                std::memcpy(&converted, &DirectInput8JoystickSendState, sizeof(DIJOYSTATE));
                std::memcpy(lpvData, &converted, sizeof(DIJOYSTATE2));
                sent = true;
                TASSynchronizer.DirectInput8JoystickSend = false;
            }
        }

        if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 && TASSynchronizer.DirectInput8MouseSend)
        {
            if (cbData == sizeof(DIMOUSESTATE))
            {
                result = ERROR_SUCCESS;
                std::memcpy(lpvData, &DirectInput8MouseSendState, sizeof(DIJOYSTATE));
                sent = true;
                TASSynchronizer.DirectInput8MouseSend = false;
            }

            if (cbData == sizeof(DIMOUSESTATE2))
            {
                result = ERROR_SUCCESS;
                DIMOUSESTATE2 converted = DIMOUSESTATE2();
                std::memcpy(&converted, &DirectInput8MouseSendState, sizeof(DIMOUSESTATE));
                std::memcpy(lpvData, &converted, sizeof(DIMOUSESTATE2));
                sent = true;
                TASSynchronizer.DirectInput8MouseSend = false;
            }
        }

        if (InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 && TASSynchronizer.DirectInput8KeyboardSend)
        {
            if (cbData == 256)
            {
                result = ERROR_SUCCESS;
                std::memcpy(lpvData, &DirectInput8KeyboardSendState, 256);
                sent = true;
                TASSynchronizer.DirectInput8KeyboardSend = false;
            }
        }

        bool canDeactivate = true;
        if (InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 && TASSynchronizer.DirectInput8KeyboardSend) canDeactivate = false;
        if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 && TASSynchronizer.DirectInput8MouseSend) canDeactivate = false;
        if (InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8 && TASSynchronizer.DirectInput8JoystickSend) canDeactivate = false;

        if (canDeactivate)
        {
            DirectInput8SendInformation = false;
        }

        if (!sent)
        {
            if (cbData == sizeof(DIJOYSTATE) || cbData == sizeof(DIJOYSTATE2))
            {
                std::memset(lpvData, 0x00, cbData);
                ((DIJOYSTATE*)lpvData)->rgdwPOV[0] = -1;
            }
            if (cbData == sizeof(DIMOUSESTATE) || cbData == sizeof(DIMOUSESTATE2)) std::memset(lpvData, 0x00, cbData);
            if (cbData == 256) std::memset(lpvData, 0x00, cbData);
        }

    }
    else
    {
        if (DirectInput8GetInformation)
        {
            if (InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8 && TASSynchronizer.DirectInput8JoystickGet)
            {
                if (cbData == sizeof(DIJOYSTATE) || cbData == sizeof(DIJOYSTATE2))
                {
                    pGetDirectInput8(false, GetDirectInput8DSTJoystick, "joystick");
                    TASSynchronizer.DirectInput8JoystickGet = false;
                }
            }

            if (InputDriverMouseGet == InputDriverz::DIRECT1NPUT8 && TASSynchronizer.DirectInput8MouseGet)
            {
                if (cbData == sizeof(DIMOUSESTATE) || cbData == sizeof(DIMOUSESTATE2))
                {
                    pGetDirectInput8(false, GetDirectInput8DSTMouse, "keyboard");
                    TASSynchronizer.DirectInput8MouseGet = false;
                }
            }

            if (InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8 && TASSynchronizer.DirectInput8KeyboardGet)
            {
                if (cbData == 256)
                {
                    pGetDirectInput8(false, GetDirectInput8DSTKeyboard, "mouse");
                    TASSynchronizer.DirectInput8KeyboardGet = false;
                }
            }

            bool canDeactivate = true;
            if (InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8 && TASSynchronizer.DirectInput8KeyboardGet) canDeactivate = false;
            if (InputDriverMouseGet == InputDriverz::DIRECT1NPUT8 && TASSynchronizer.DirectInput8MouseGet) canDeactivate = false;
            if (InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8 && TASSynchronizer.DirectInput8JoystickGet) canDeactivate = false;

            if (canDeactivate)
            {
                DirectInput8GetInformation = false;
            }

        }
        else if (DirectInput8DisableForGame)
        {
            if (cbData == sizeof(DIJOYSTATE) || cbData == sizeof(DIJOYSTATE2))
            {
                std::memset(lpvData, 0x00, cbData);
                ((DIJOYSTATE*)lpvData)->rgdwPOV[0] = -1;
            }
            if (cbData == sizeof(DIMOUSESTATE) || cbData == sizeof(DIMOUSESTATE2)) std::memset(lpvData, 0x00, cbData);
            if (cbData == 256) std::memset(lpvData, 0x00, cbData);
            result = DIERR_INVALIDPARAM;
        }
    }

    // Init Hook again
    if (sizeof(void*) == 8) DirectInput8SubHook.Install(DirectInput8OriginalAddress, DirectInput8HookAddress, subhook::HookFlags::HookFlag64BitOffset);
    if (sizeof(void*) == 4) DirectInput8SubHook.Install(DirectInput8OriginalAddress, DirectInput8HookAddress);

    return result;
}

BOOL DirectInput8HookUninit()
{
    DirectInput8DeviceJoystick->Release();
    pDirectInput_DI8->Release();
    DirectInput8SubHook.Remove();
    return true;
}

void InitPlayDirectInput8TAS()
{
    DirectInput8DisableForGame = true;
    DirectInput8SendInformation = true;
}

void UninitPlayDirectInput8TAS()
{
    DirectInput8DisableForGame = false;
    DirectInput8SendInformation = false;
}

void InitRecordDirectInput8TAS()
{
    if (TASRecordFrameByFrameInputTrigger)
    {
        DirectInput8DisableForGame = true;
        DirectInput8SendInformation = true;
    }
}

void UninitRecordDirectInput8TAS()
{
    if (TASRecordFrameByFrameInputTrigger)
    {
        DirectInput8DisableForGame = false;
        DirectInput8SendInformation = false;
    }
}



void __stdcall GetDirectInput8(BOOL TAS, GameInput* DST, std::string device)
{
    if (device == "all") GetDirectInput8DSTAll = DST;
    else if (device == "mouse") GetDirectInput8DSTMouse = DST;
    else if (device == "keyboard") GetDirectInput8DSTKeyboard = DST;
    else if (device == "joystick") GetDirectInput8DSTJoystick = DST;

    if (TAS)
    {
        DirectInput8GetInformation = true;
        return;
    }

    std::memset(&DirectInput8GameInputCurrent, 0x00, sizeof(GameInput));

    if (InputDriverMouseGet == InputDriverz::DIRECT1NPUT8 && (device == "all" || device == "mouse"))
    {
        // Mouse input
        int mouseDX = static_cast<int>(DirectInput8MouseInputState.lX);
        int mouseDY = static_cast<int>(DirectInput8MouseInputState.lY);
        int mouseDZ = static_cast<int>(DirectInput8MouseInputState.lZ);

        if (DirectInput8MouseInputState.rgbButtons[0] & 0x80) DirectInput8GameInputCurrent.LMB = true;
        if (DirectInput8MouseInputState.rgbButtons[1] & 0x80) DirectInput8GameInputCurrent.RMB = true;
        if (DirectInput8MouseInputState.rgbButtons[2] & 0x80) DirectInput8GameInputCurrent.MB = true;
        if (DirectInput8MouseInputState.rgbButtons[3] & 0x80) DirectInput8GameInputCurrent.ME1 = true;
        if (DirectInput8MouseInputState.rgbButtons[4] & 0x80) DirectInput8GameInputCurrent.ME2 = true;

        DirectInput8GameInputCurrent.MOUSEX = mouseDX;
        DirectInput8GameInputCurrent.MOUSEY = mouseDY;
        DirectInput8GameInputCurrent.WHEEL = mouseDZ;
    }

    if (InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8 && (device == "all" || device == "keyboard"))
    {
        // Keyboard input
        for (int i = 0; i < 256; i++) {
            if (DirectInput8KeyboardInputState[i] & 0x80) {
                if (i == DIK_ESCAPE) DirectInput8GameInputCurrent.ESC = true;
                if (i == DIK_TAB) DirectInput8GameInputCurrent.TAB = true;
                if (i == DIK_LSHIFT) DirectInput8GameInputCurrent.LSHIFT = true;
                if (i == DIK_RSHIFT) DirectInput8GameInputCurrent.RSHIFT = true;
                if (i == DIK_LCONTROL) DirectInput8GameInputCurrent.CTRL = true;
                if (i == DIK_BACK) DirectInput8GameInputCurrent.BACK = true;
                if (i == DIK_RETURN) DirectInput8GameInputCurrent.RETURN = true;
                if (i == DIK_SPACE) DirectInput8GameInputCurrent.SPACE = true;
                if (i == DIK_UP) DirectInput8GameInputCurrent.AUP = true;
                if (i == DIK_RIGHT) DirectInput8GameInputCurrent.ARIGHT = true;
                if (i == DIK_DOWN) DirectInput8GameInputCurrent.ADOWN = true;
                if (i == DIK_LEFT) DirectInput8GameInputCurrent.ALEFT = true;
                if (i == DIK_0) DirectInput8GameInputCurrent.D0 = true;
                if (i == DIK_1) DirectInput8GameInputCurrent.D1 = true;
                if (i == DIK_2) DirectInput8GameInputCurrent.D2 = true;
                if (i == DIK_3) DirectInput8GameInputCurrent.D3 = true;
                if (i == DIK_4) DirectInput8GameInputCurrent.D4 = true;
                if (i == DIK_5) DirectInput8GameInputCurrent.D5 = true;
                if (i == DIK_6) DirectInput8GameInputCurrent.D6 = true;
                if (i == DIK_7) DirectInput8GameInputCurrent.D7 = true;
                if (i == DIK_8) DirectInput8GameInputCurrent.D8 = true;
                if (i == DIK_9) DirectInput8GameInputCurrent.D9 = true;
                if (i == DIK_A) DirectInput8GameInputCurrent.A = true;
                if (i == DIK_B) DirectInput8GameInputCurrent.B = true;
                if (i == DIK_C) DirectInput8GameInputCurrent.C = true;
                if (i == DIK_D) DirectInput8GameInputCurrent.D = true;
                if (i == DIK_E) DirectInput8GameInputCurrent.E = true;
                if (i == DIK_F) DirectInput8GameInputCurrent.F = true;
                if (i == DIK_G) DirectInput8GameInputCurrent.G = true;
                if (i == DIK_H) DirectInput8GameInputCurrent.H = true;
                if (i == DIK_I) DirectInput8GameInputCurrent.I = true;
                if (i == DIK_J) DirectInput8GameInputCurrent.J = true;
                if (i == DIK_K) DirectInput8GameInputCurrent.K = true;
                if (i == DIK_L) DirectInput8GameInputCurrent.L = true;
                if (i == DIK_M) DirectInput8GameInputCurrent.M = true;
                if (i == DIK_N) DirectInput8GameInputCurrent.N = true;
                if (i == DIK_O) DirectInput8GameInputCurrent.O = true;
                if (i == DIK_P) DirectInput8GameInputCurrent.P = true;
                if (i == DIK_Q) DirectInput8GameInputCurrent.Q = true;
                if (i == DIK_R) DirectInput8GameInputCurrent.R = true;
                if (i == DIK_S) DirectInput8GameInputCurrent.S = true;
                if (i == DIK_T) DirectInput8GameInputCurrent.T = true;
                if (i == DIK_U) DirectInput8GameInputCurrent.U = true;
                if (i == DIK_V) DirectInput8GameInputCurrent.V = true;
                if (i == DIK_W) DirectInput8GameInputCurrent.W = true;
                if (i == DIK_X) DirectInput8GameInputCurrent.X = true;
                if (i == DIK_Y) DirectInput8GameInputCurrent.Y = true;
                if (i == DIK_Z) DirectInput8GameInputCurrent.Z = true;
                if (i == DIK_NUMPAD0) DirectInput8GameInputCurrent.NUM0 = true;
                if (i == DIK_NUMPAD1) DirectInput8GameInputCurrent.NUM1 = true;
                if (i == DIK_NUMPAD2) DirectInput8GameInputCurrent.NUM2 = true;
                if (i == DIK_NUMPAD3) DirectInput8GameInputCurrent.NUM3 = true;
                if (i == DIK_NUMPAD4) DirectInput8GameInputCurrent.NUM4 = true;
                if (i == DIK_NUMPAD5) DirectInput8GameInputCurrent.NUM5 = true;
                if (i == DIK_NUMPAD6) DirectInput8GameInputCurrent.NUM6 = true;
                if (i == DIK_NUMPAD7) DirectInput8GameInputCurrent.NUM7 = true;
                if (i == DIK_NUMPAD8) DirectInput8GameInputCurrent.NUM8 = true;
                if (i == DIK_NUMPAD9) DirectInput8GameInputCurrent.NUM9 = true;
                if (i == DIK_DIVIDE) DirectInput8GameInputCurrent.NUMDIV = true;
                if (i == DIK_MULTIPLY) DirectInput8GameInputCurrent.NUMMUL = true;
                if (i == DIK_SUBTRACT) DirectInput8GameInputCurrent.NUMMIN = true;
                if (i == DIK_ADD) DirectInput8GameInputCurrent.NUMPLU = true;
                if (i == DIK_NUMPADENTER) DirectInput8GameInputCurrent.NUMRET = true;
                if (i == DIK_NUMPADCOMMA) DirectInput8GameInputCurrent.NUMDEL = true;
                if (i == DIK_F1) DirectInput8GameInputCurrent.F1 = true;
                if (i == DIK_F2) DirectInput8GameInputCurrent.F2 = true;
                if (i == DIK_F3) DirectInput8GameInputCurrent.F3 = true;
                if (i == DIK_F4) DirectInput8GameInputCurrent.F4 = true;
                if (i == DIK_F5) DirectInput8GameInputCurrent.F5 = true;
                if (i == DIK_F6) DirectInput8GameInputCurrent.F6 = true;
                if (i == DIK_F7) DirectInput8GameInputCurrent.F7 = true;
                if (i == DIK_F8) DirectInput8GameInputCurrent.F8 = true;
                if (i == DIK_F9) DirectInput8GameInputCurrent.F9 = true;
                if (i == DIK_F10) DirectInput8GameInputCurrent.F10 = true;
                if (i == DIK_F11) DirectInput8GameInputCurrent.F11 = true;
                if (i == DIK_F12) DirectInput8GameInputCurrent.F12 = true;
                if (i == DIK_COMMA) DirectInput8GameInputCurrent.COMMA = true;
                if (i == DIK_PERIOD) DirectInput8GameInputCurrent.DOT = true;
                if (i == DIK_MINUS) DirectInput8GameInputCurrent.F12 = true;
                if (i == VK_OEM_PLUS) DirectInput8GameInputCurrent.MINUS = true;
            }
        }
    }

    if (InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8 && (device == "all" || device == "joystick"))
    {
        // Joystick input
        int LT = static_cast<int>(DirectInput8JoystickInputState.rglSlider[0]);
        int RT = static_cast<int>(DirectInput8JoystickInputState.rglSlider[1]);
        int LAXISX = static_cast<int>(DirectInput8JoystickInputState.lX);
        int LAXISY = static_cast<int>(DirectInput8JoystickInputState.lY);
        int RAXISX = static_cast<int>(DirectInput8JoystickInputState.lRx);
        int RAXISY = static_cast<int>(DirectInput8JoystickInputState.lRy);

        if (DirectInput8JoystickInputState.rgbButtons[0] == 0x80) DirectInput8GameInputCurrent.JOYA = true;
        if (DirectInput8JoystickInputState.rgbButtons[1] == 0x80) DirectInput8GameInputCurrent.JOYB = true;
        if (DirectInput8JoystickInputState.rgbButtons[2] == 0x80) DirectInput8GameInputCurrent.JOYX = true;
        if (DirectInput8JoystickInputState.rgbButtons[3] == 0x80) DirectInput8GameInputCurrent.JOYY = true;
        if (DirectInput8JoystickInputState.rgbButtons[4] == 0x80) DirectInput8GameInputCurrent.JOYLB = true;
        if (DirectInput8JoystickInputState.rgbButtons[5] == 0x80) DirectInput8GameInputCurrent.JOYRB = true;
        if (DirectInput8JoystickInputState.rgbButtons[6] == 0x80) DirectInput8GameInputCurrent.JOYSELECT = true;
        if (DirectInput8JoystickInputState.rgbButtons[7] == 0x80) DirectInput8GameInputCurrent.JOYSTART = true;
        if (DirectInput8JoystickInputState.rgbButtons[8] == 0x80) DirectInput8GameInputCurrent.JOYLS = true;
        if (DirectInput8JoystickInputState.rgbButtons[9] == 0x80) DirectInput8GameInputCurrent.JOYRS = true;
        if (DirectInput8JoystickInputState.rgdwPOV[0] == 0 || DirectInput8JoystickInputState.rgdwPOV[0] == 4500 || DirectInput8JoystickInputState.rgdwPOV[0] == 31500) DirectInput8GameInputCurrent.JOYUP = true;
        if (DirectInput8JoystickInputState.rgdwPOV[0] == 4500 || DirectInput8JoystickInputState.rgdwPOV[0] == 9000 || DirectInput8JoystickInputState.rgdwPOV[0] == 13500) DirectInput8GameInputCurrent.JOYRIGHT = true;
        if (DirectInput8JoystickInputState.rgdwPOV[0] == 13500 || DirectInput8JoystickInputState.rgdwPOV[0] == 18000 || DirectInput8JoystickInputState.rgdwPOV[0] == 22500) DirectInput8GameInputCurrent.JOYDOWN = true;
        if (DirectInput8JoystickInputState.rgdwPOV[0] == 22500 || DirectInput8JoystickInputState.rgdwPOV[0] == 27000 || DirectInput8JoystickInputState.rgdwPOV[0] == 31500) DirectInput8GameInputCurrent.JOYLEFT = true;
        if (LT > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) DirectInput8GameInputCurrent.JOYLT = LT;
        if (RT > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) DirectInput8GameInputCurrent.JOYRT = RT;
        if (LAXISX > 99 || LAXISX < -99) DirectInput8GameInputCurrent.JOYLAXISX = LAXISX;
        if (LAXISY > 99 || LAXISY < -99) DirectInput8GameInputCurrent.JOYLAXISY = LAXISY;
        if (RAXISX > 99 || RAXISX < -99) DirectInput8GameInputCurrent.JOYRAXISX = RAXISX;
        if (RAXISY > 99 || RAXISY < -99) DirectInput8GameInputCurrent.JOYRAXISY = RAXISY;
    }

    if (device == "all") std::memcpy(GetDirectInput8DSTAll, &DirectInput8GameInputCurrent, sizeof(GameInput));
    else if (device == "mouse") std::memcpy(GetDirectInput8DSTMouse, &DirectInput8GameInputCurrent, sizeof(GameInput));
    else if (device == "keyboard") std::memcpy(GetDirectInput8DSTKeyboard, &DirectInput8GameInputCurrent, sizeof(GameInput));
    else if (device == "joystick") std::memcpy(GetDirectInput8DSTJoystick, &DirectInput8GameInputCurrent, sizeof(GameInput));
}

void SetDirectInput8(GameInput DirectInput8GameInput, BOOL TAS)
{
    std::memset(&DirectInput8MouseSendState, 0x00, sizeof(DIMOUSESTATE));
    std::memset(&DirectInput8KeyboardSendState, 0x00, 256);
    std::memset(&DirectInput8JoystickSendState, 0x00, sizeof(DIJOYSTATE));
    DirectInput8JoystickSendState.rgdwPOV[0] = -1;

    if (InputDriverMouseGet == InputDriverz::DIRECT1NPUT8)
    {
        // Mouse input
        int mouseDX = static_cast<int>(DirectInput8GameInput.MOUSEX);
        int mouseDY = static_cast<int>(DirectInput8GameInput.MOUSEY);
        int mouseDZ = static_cast<int>(DirectInput8GameInput.WHEEL);

        if (DirectInput8GameInput.LMB) DirectInput8MouseSendState.rgbButtons[0] = 0x80;
        if (DirectInput8GameInput.RMB) DirectInput8MouseSendState.rgbButtons[1] = 0x80;
        if (DirectInput8GameInput.MB) DirectInput8MouseSendState.rgbButtons[2] = 0x80;
        if (DirectInput8GameInput.ME1) DirectInput8MouseSendState.rgbButtons[3] = 0x80;
        if (DirectInput8GameInput.ME2) DirectInput8MouseSendState.rgbButtons[4] = 0x80;

        DirectInput8MouseInputState.lX = mouseDX;
        DirectInput8MouseInputState.lY = mouseDY;
        DirectInput8MouseInputState.lZ = mouseDZ;
    }

    if (InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8)
    {
        // Keyboard input
        for (int i = 0; i < 256; i++) {
            if (i == DIK_ESCAPE) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.ESC ? 0x80 : 0x00;
            if (i == DIK_TAB) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.TAB ? 0x80 : 0x00;
            if (i == DIK_LSHIFT) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.LSHIFT ? 0x80 : 0x00;
            if (i == DIK_RSHIFT) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.RSHIFT ? 0x80 : 0x00;
            if (i == DIK_LCONTROL) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.CTRL ? 0x80 : 0x00;
            if (i == DIK_BACK) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.BACK ? 0x80 : 0x00;
            if (i == DIK_RETURN) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.RETURN ? 0x80 : 0x00;
            if (i == DIK_SPACE) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.SPACE ? 0x80 : 0x00;
            if (i == DIK_UP) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.AUP ? 0x80 : 0x00;
            if (i == DIK_RIGHT) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.ARIGHT ? 0x80 : 0x00;
            if (i == DIK_DOWN) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.ADOWN ? 0x80 : 0x00;
            if (i == DIK_LEFT) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.ALEFT ? 0x80 : 0x00;
            if (i == DIK_0) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.D0 ? 0x80 : 0x00;
            if (i == DIK_1) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.D1 ? 0x80 : 0x00;
            if (i == DIK_2) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.D2 ? 0x80 : 0x00;
            if (i == DIK_3) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.D3 ? 0x80 : 0x00;
            if (i == DIK_4) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.D4 ? 0x80 : 0x00;
            if (i == DIK_5) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.D5 ? 0x80 : 0x00;
            if (i == DIK_6) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.D6 ? 0x80 : 0x00;
            if (i == DIK_7) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.D7 ? 0x80 : 0x00;
            if (i == DIK_8) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.D8 ? 0x80 : 0x00;
            if (i == DIK_9) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.D9 ? 0x80 : 0x00;
            if (i == DIK_A) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.A ? 0x80 : 0x00;
            if (i == DIK_B) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.B ? 0x80 : 0x00;
            if (i == DIK_C) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.C ? 0x80 : 0x00;
            if (i == DIK_D) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.D ? 0x80 : 0x00;
            if (i == DIK_E) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.E ? 0x80 : 0x00;
            if (i == DIK_F) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F ? 0x80 : 0x00;
            if (i == DIK_G) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.G ? 0x80 : 0x00;
            if (i == DIK_H) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.H ? 0x80 : 0x00;
            if (i == DIK_I) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.I ? 0x80 : 0x00;
            if (i == DIK_J) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.J ? 0x80 : 0x00;
            if (i == DIK_K) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.K ? 0x80 : 0x00;
            if (i == DIK_L) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.L ? 0x80 : 0x00;
            if (i == DIK_M) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.M ? 0x80 : 0x00;
            if (i == DIK_N) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.N ? 0x80 : 0x00;
            if (i == DIK_O) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.O ? 0x80 : 0x00;
            if (i == DIK_P) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.P ? 0x80 : 0x00;
            if (i == DIK_Q) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.Q ? 0x80 : 0x00;
            if (i == DIK_R) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.R ? 0x80 : 0x00;
            if (i == DIK_S) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.S ? 0x80 : 0x00;
            if (i == DIK_T) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.T ? 0x80 : 0x00;
            if (i == DIK_U) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.U ? 0x80 : 0x00;
            if (i == DIK_V) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.V ? 0x80 : 0x00;
            if (i == DIK_W) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.W ? 0x80 : 0x00;
            if (i == DIK_X) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.X ? 0x80 : 0x00;
            if (i == DIK_Y) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.Y ? 0x80 : 0x00;
            if (i == DIK_Z) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.Z ? 0x80 : 0x00;
            if (i == DIK_NUMPAD0) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUM0 ? 0x80 : 0x00;
            if (i == DIK_NUMPAD1) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUM1 ? 0x80 : 0x00;
            if (i == DIK_NUMPAD2) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUM2 ? 0x80 : 0x00;
            if (i == DIK_NUMPAD3) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUM3 ? 0x80 : 0x00;
            if (i == DIK_NUMPAD4) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUM4 ? 0x80 : 0x00;
            if (i == DIK_NUMPAD5) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUM5 ? 0x80 : 0x00;
            if (i == DIK_NUMPAD6) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUM6 ? 0x80 : 0x00;
            if (i == DIK_NUMPAD7) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUM7 ? 0x80 : 0x00;
            if (i == DIK_NUMPAD8) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUM8 ? 0x80 : 0x00;
            if (i == DIK_NUMPAD9) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUM9 ? 0x80 : 0x00;
            if (i == DIK_DIVIDE) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUMDIV ? 0x80 : 0x00;
            if (i == DIK_MULTIPLY) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUMMUL ? 0x80 : 0x00;
            if (i == DIK_SUBTRACT) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUMMIN ? 0x80 : 0x00;
            if (i == DIK_ADD) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUMPLU ? 0x80 : 0x00;
            if (i == DIK_NUMPADENTER) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUMRET ? 0x80 : 0x00;
            if (i == DIK_NUMPADCOMMA) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.NUMDEL ? 0x80 : 0x00;
            if (i == DIK_F1) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F1 ? 0x80 : 0x00;
            if (i == DIK_F2) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F2 ? 0x80 : 0x00;
            if (i == DIK_F3) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F3 ? 0x80 : 0x00;
            if (i == DIK_F4) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F4 ? 0x80 : 0x00;
            if (i == DIK_F5) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F5 ? 0x80 : 0x00;
            if (i == DIK_F6) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F6 ? 0x80 : 0x00;
            if (i == DIK_F7) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F7 ? 0x80 : 0x00;
            if (i == DIK_F8) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F8 ? 0x80 : 0x00;
            if (i == DIK_F9) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F9 ? 0x80 : 0x00;
            if (i == DIK_F10) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F10 ? 0x80 : 0x00;
            if (i == DIK_F11) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F11 ? 0x80 : 0x00;
            if (i == DIK_F12) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F12 ? 0x80 : 0x00;
            if (i == DIK_COMMA) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.COMMA ? 0x80 : 0x00;
            if (i == DIK_PERIOD) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.DOT ? 0x80 : 0x00;
            if (i == DIK_MINUS) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.F12 ? 0x80 : 0x00;
            if (i == VK_OEM_PLUS) DirectInput8KeyboardSendState[i] = DirectInput8GameInput.MINUS ? 0x80 : 0x00;
        }
    }

    if (InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8)
    {
        LONG LT = static_cast<LONG>(DirectInput8GameInput.JOYLT);
        LONG RT = static_cast<LONG>(DirectInput8GameInput.JOYRT);
        LONG LAXISX = static_cast<float>(DirectInput8GameInput.JOYLAXISX);
        LONG LAXISY = static_cast<float>(DirectInput8GameInput.JOYLAXISY);
        LONG RAXISX = static_cast<float>(DirectInput8GameInput.JOYRAXISX);
        LONG RAXISY = static_cast<float>(DirectInput8GameInput.JOYRAXISY);
        if (DirectInput8GameInput.JOYA) DirectInput8JoystickSendState.rgbButtons[0] = 0x80;
        if (DirectInput8GameInput.JOYB) DirectInput8JoystickSendState.rgbButtons[1] = 0x80;
        if (DirectInput8GameInput.JOYX) DirectInput8JoystickSendState.rgbButtons[2] = 0x80;
        if (DirectInput8GameInput.JOYY) DirectInput8JoystickSendState.rgbButtons[3] = 0x80;
        if (DirectInput8GameInput.JOYLB) DirectInput8JoystickSendState.rgbButtons[4] = 0x80;
        if (DirectInput8GameInput.JOYRB) DirectInput8JoystickSendState.rgbButtons[5] = 0x80;
        if (DirectInput8GameInput.JOYSELECT) DirectInput8JoystickSendState.rgbButtons[6] = 0x80;
        if (DirectInput8GameInput.JOYSTART) DirectInput8JoystickSendState.rgbButtons[7] = 0x80;
        if (DirectInput8GameInput.JOYLS) DirectInput8JoystickSendState.rgbButtons[8] = 0x80;
        if (DirectInput8GameInput.JOYRS) DirectInput8JoystickSendState.rgbButtons[9] = 0x80;
        if (!DirectInput8GameInput.JOYUP && !DirectInput8GameInput.JOYRIGHT && !DirectInput8GameInput.JOYDOWN && !DirectInput8GameInput.JOYLEFT) DirectInput8JoystickSendState.rgdwPOV[0] = -1;
        if (DirectInput8GameInput.JOYUP && !DirectInput8GameInput.JOYRIGHT && !DirectInput8GameInput.JOYDOWN && !DirectInput8GameInput.JOYLEFT) DirectInput8JoystickSendState.rgdwPOV[0] = 0;
        if (DirectInput8GameInput.JOYUP && DirectInput8GameInput.JOYRIGHT && !DirectInput8GameInput.JOYDOWN && !DirectInput8GameInput.JOYLEFT) DirectInput8JoystickSendState.rgdwPOV[0] = 4500;
        if (!DirectInput8GameInput.JOYUP && DirectInput8GameInput.JOYRIGHT && !DirectInput8GameInput.JOYDOWN && !DirectInput8GameInput.JOYLEFT) DirectInput8JoystickSendState.rgdwPOV[0] = 9000;
        if (!DirectInput8GameInput.JOYUP && DirectInput8GameInput.JOYRIGHT && DirectInput8GameInput.JOYDOWN && !DirectInput8GameInput.JOYLEFT) DirectInput8JoystickSendState.rgdwPOV[0] = 13500;
        if (!DirectInput8GameInput.JOYUP && !DirectInput8GameInput.JOYRIGHT && DirectInput8GameInput.JOYDOWN && !DirectInput8GameInput.JOYLEFT) DirectInput8JoystickSendState.rgdwPOV[0] = 18000;
        if (!DirectInput8GameInput.JOYUP && !DirectInput8GameInput.JOYRIGHT && DirectInput8GameInput.JOYDOWN && DirectInput8GameInput.JOYLEFT) DirectInput8JoystickSendState.rgdwPOV[0] = 22500;
        if (!DirectInput8GameInput.JOYUP && !DirectInput8GameInput.JOYRIGHT && !DirectInput8GameInput.JOYDOWN && DirectInput8GameInput.JOYLEFT) DirectInput8JoystickSendState.rgdwPOV[0] = 27000;
        if (DirectInput8GameInput.JOYUP && !DirectInput8GameInput.JOYRIGHT && !DirectInput8GameInput.JOYDOWN && DirectInput8GameInput.JOYLEFT) DirectInput8JoystickSendState.rgdwPOV[0] = 31500;

        DirectInput8JoystickSendState.rglSlider[0] = LT;
        DirectInput8JoystickSendState.rglSlider[1] = RT;
        DirectInput8JoystickSendState.lX = LAXISX;
        DirectInput8JoystickSendState.lY = LAXISY;
        DirectInput8JoystickSendState.lRx = RAXISX;
        DirectInput8JoystickSendState.lRy = RAXISY;
    }

    DirectInput8SendInformation = true;
}

BOOL DirectInput8HookInit()
{
    // Detect the XInput module handle
    HMODULE XInputDllHandle = GetModuleHandleA("dinput8.dll");
    if (XInputDllHandle == NULL) return false;

    if (DirectInput8Create(dllHandle, 0x0800, IID_IDirectInput8, (LPVOID*)&pDirectInput_DI8, NULL) != DI_OK) {
        DebugConsoleOutput("Error: DirectInput8Create() failed!", false, "red");
        return false;
    }

    if (pDirectInput_DI8->CreateDevice(GUID_SysMouse, &DirectInput8DeviceJoystick, NULL) != DI_OK) {
        DebugConsoleOutput("Error: CreateDeviceDirectInput8() failed!", false, "red");
        pDirectInput_DI8->Release();
        return false;
    }

    pGetDirectInput8 = (GetDirectInput8T)GetDirectInput8;

    uintptr_t avTable = Internal::Memory::read<uintptr_t>(DirectInput8DeviceJoystick);
    uintptr_t pFunction = avTable + 9 * sizeof(uintptr_t);

    // Set the hook addresses
    DirectInput8OriginalAddress = Internal::Memory::read<void*>(pFunction);
    DirectInput8HookAddress = (void*)DirectInput8Hook;
    pDirectInput8DevicGetState = (DirectInput8GetDeviceStateT)DirectInput8OriginalAddress;

    if (sizeof(void*) == 8) DirectInput8SubHook.Install(DirectInput8OriginalAddress, DirectInput8HookAddress, subhook::HookFlags::HookFlag64BitOffset);
    if (sizeof(void*) == 4) DirectInput8SubHook.Install(DirectInput8OriginalAddress, DirectInput8HookAddress);

    return true;
}

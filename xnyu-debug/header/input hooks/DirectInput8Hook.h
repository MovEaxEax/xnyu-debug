#pragma once

// --- Structs ---
struct DIKEYBOARDSTATE
{
    BYTE keys[256];
};



// --- Typedefs ---
typedef HRESULT(__stdcall* DirectInput8GetDeviceStateT)(IDirectInputDevice8* pDevice, DWORD cbData, LPVOID lpvData);



// --- Variables ---
extern DirectInput8GetDeviceStateT pDirectInput8GetDeviceState;



// --- DirectInput8GetDeviceState ---
template <typename FuncT>
class DirectInput8GetDeviceStateHook : public xNyuHook<DirectInput8GetDeviceStateT> {
private:
    HANDLE inputAllMutex = CreateMutex(NULL, FALSE, NULL);
    
    IDirectInputDevice8* pDeviceCopy = nullptr;
    DIJOYSTATE inputstateJoystickGet = DIJOYSTATE();
    DIJOYSTATE inputstateJoystickSet = DIJOYSTATE();
    auto inputJoystickCounterTimer = std::chrono::high_resolution_clock::now();
    float inputJoystickFramesEstimated = 0;
    float inputJoystickTimeFrames = 0;
    float inputJoystickTotalFrames = 0;
    bool inputDeviceUsed = false;
    std::vector<int> inputDeviceThreadIDs;
    bool inputJoystickDeactivate = false;
    bool inputJoystickSet = false;

    DIMOUSESTATE inputstateMouseGet = DIMOUSESTATE();
    DIMOUSESTATE inputstateMouseSet = DIMOUSESTATE();
    auto inputMouseCounterTimer = std::chrono::high_resolution_clock::now();
    float inputMouseFramesEstimated = 0;
    float inputMouseTimeFrames = 0;
    float inputMouseTotalFrames = 0;
    bool inputMouseUsed = false;
    std::vector<int> inputMouseThreadIDs;
    bool inputMouseDeactivate = false;
    bool inputMouseSet = false;

    DIKEYBOARDSTATE inputstateKeyboardGet = DIKEYBOARDSTATE();
    DIKEYBOARDSTATE inputstateKeyboardSet = DIKEYBOARDSTATE();
    auto inputKeyboardCounterTimer = std::chrono::high_resolution_clock::now();
    float inputKeyboardFramesEstimated = 0;
    float inputKeyboardTimeFrames = 0;
    float inputKeyboardTotalFrames = 0;
    bool inputKeyboardUsed = false;
    std::vector<int> inputKeyboardThreadIDs;
    bool inputKeyboardDeactivate = false;
    bool inputKeyboardSet = false;

public:
    static DirectInput8GetDeviceStateHook* instance;
    DirectInput8GetDeviceStateHook(void* originalAddress) : xNyuHook<DirectInput8GetDeviceStateT>(originalAddress, CustomHook) { instance = this; }
    static HRESULT __stdcall CustomHook(IDirectInputDevice8* pDevice, DWORD cbData, LPVOID lpvData)
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);

        if (instance->HookInit)
        {
            DebugConsoleOutput("DirectInput8GetDeviceState() Hook active...", true, "yellow");
            instance->pDeviceCopy = pDevice;
            instance->HookInit = false;
        }

        HRESULT result = instance->callTrampoline(pDevice, cbData, lpvData);

        if (cbData == sizeof(DIJOYSTATE) || cbData == sizeof(DIJOYSTATE2))
        {
            // Joystick monitoring data
            instance->inputDeviceUsed = true;
            int threadId = (int)GetCurrentThreadId();
            if (std::find(instance->inputDeviceThreadIDs.begin(), instance->inputDeviceThreadIDs.end(), threadId) == instance->inputDeviceThreadIDs.end()) instance->inputDeviceThreadIDs.push_back(threadId);

            instance->inputJoystickTimeFrames += (float)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - instance->inputJoystickCounterTimer)).count();
            instance->inputJoystickTotalFrames += 1.0f;
            instance->inputJoystickCounterTimer = std::chrono::high_resolution_clock::now();

            if (instance->inputJoystickTotalFrames >= 15)
            {
                instance->inputJoystickFramesEstimated = (float)round(1000.0f / (instance->inputJoystickTimeFrames / instance->inputJoystickTotalFrames));
                instance->inputJoystickTimeFrames = 0;
                instance->inputJoystickTotalFrames = 0;
            }

            std::memcpy(&instance->inputstateJoystickGet, lpvData, sizeof(DIJOYSTATE));
            if (instance->inputJoystickDeactivate || instance->inputJoystickSet) std::memset(lpvData, 0x00, cbData);
            if (instance->inputJoystickSet)
            {
                std::memcpy(lpvData, &instance->inputstateJoystickSet, sizeof(DIJOYSTATE));
                instance->inputJoystickSet = false;
            }
        }

        if (cbData == sizeof(DIMOUSESTATE) || cbData == sizeof(DIMOUSESTATE2))
        {
            // Mouse monitoring data
            instance->inputMouseUsed = true;
            int threadId = (int)GetCurrentThreadId();
            if (std::find(instance->inputMouseThreadIDs.begin(), instance->inputMouseThreadIDs.end(), threadId) == instance->inputMouseThreadIDs.end()) instance->inputMouseThreadIDs.push_back(threadId);

            instance->inputMouseTimeFrames += (float)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - instance->inputMouseCounterTimer)).count();
            instance->inputMouseTotalFrames += 1.0f;
            instance->inputMouseCounterTimer = std::chrono::high_resolution_clock::now();

            if (instance->inputMouseTotalFrames >= 15)
            {
                instance->inputMouseFramesEstimated = (float)round(1000.0f / (instance->inputMouseTimeFrames / instance->inputMouseTotalFrames));
                instance->inputMouseTimeFrames = 0;
                instance->inputMouseTotalFrames = 0;
            }

            std::memcpy(&instance->inputstateMouseGet, lpvData, sizeof(DIMOUSESTATE));
            if (instance->inputMouseDeactivate || instance->inputMouseSet) std::memset(lpvData, 0x00, cbData);
            if (instance->inputMouseSet)
            {
                std::memcpy(lpvData, &instance->inputstateMouseSet, sizeof(DIMOUSESTATE));
                instance->inputMouseSet = false;
            }
        }

        if (cbData == sizeof(DIKEYBOARDSTATE))
        {
            // Keyboard monitoring data
            instance->inputKeyboardUsed = true;
            int threadId = (int)GetCurrentThreadId();
            if (std::find(instance->inputKeyboardThreadIDs.begin(), instance->inputKeyboardThreadIDs.end(), threadId) == instance->inputKeyboardThreadIDs.end()) instance->inputKeyboardThreadIDs.push_back(threadId);

            instance->inputKeyboardTimeFrames += (float)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - instance->inputKeyboardCounterTimer)).count();
            instance->inputKeyboardTotalFrames += 1.0f;
            instance->inputKeyboardCounterTimer = std::chrono::high_resolution_clock::now();

            if (instance->inputKeyboardTotalFrames >= 15)
            {
                instance->inputKeyboardFramesEstimated = (float)round(1000.0f / (instance->inputKeyboardTimeFrames / instance->inputKeyboardTotalFrames));
                instance->inputKeyboardTimeFrames = 0;
                instance->inputKeyboardTotalFrames = 0;
            }

            std::memcpy(&instance->inputstateKeyboardGet, lpvData, sizeof(DIKEYBOARDSTATE));
            if (instance->inputKeyboardDeactivate || instance->inputKeyboardSet) std::memset(lpvData, 0x00, cbData);
            if (instance->inputKeyboardSet)
            {
                std::memcpy(lpvData, &instance->inputstateKeyboardSet, sizeof(DIKEYBOARDSTATE));
                instance->inputKeyboardSet = false;
            }
        }

        ReleaseMutex(instance->inputAllMutex);
        return result;
    }

    bool GetJoystickUsed()
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        bool result = instance->inputDeviceUsed;
        ReleaseMutex(instance->inputAllMutex);
        return result;
    }
    float GetJoystickFrames()
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        float result = instance->inputJoystickFramesEstimated;
        ReleaseMutex(instance->inputAllMutex);
        return result;
    }
    void SetJoystickDeactivated(bool value)
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        instance->inputJoystickDeactivate = value;
        ReleaseMutex(instance->inputAllMutex);
    }
    bool GetMouseUsed()
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        bool result = instance->inputMouseUsed;
        ReleaseMutex(instance->inputAllMutex);
        return result;
    }
    float GetMouseFrames()
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        float result = instance->inputMouseFramesEstimated;
        ReleaseMutex(instance->inputAllMutex);
        return result;
    }
    void SetMouseDeactivated(bool value)
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        instance->inputMouseDeactivate = value;
        ReleaseMutex(instance->inputAllMutex);
    }
    bool GetKeyboardUsed()
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        bool result = instance->inputKeyboardUsed;
        ReleaseMutex(instance->inputAllMutex);
        return result;
    }
    float GetKeyboardFrames()
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        float result = instance->inputKeyboardFramesEstimated;
        ReleaseMutex(instance->inputAllMutex);
        return result;
    }
    void SetKeyboardDeactivated(bool value)
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        instance->inputKeyboardDeactivate = value;
        ReleaseMutex(instance->inputAllMutex);
    }

    bool IsSetJoystickDone()
    {
        WaitForSingleObject(instance->inputJoystickMutex, INFINITE);
        bool result = !instance->inputJoystickSet;
        ReleaseMutex(instance->inputJoystickMutex);
        return result;
    }
    bool IsSetMouseDone()
    {
        WaitForSingleObject(instance->inputMouseMutex, INFINITE);
        bool result = !instance->inputMouseSet;
        ReleaseMutex(instance->inputMouseMutex);
        return result;
    }
    bool IsSetKeyboardDone()
    {
        WaitForSingleObject(instance->inputKeyboardMutex, INFINITE);
        bool result = !instance->inputKeyboardSet;
        ReleaseMutex(instance->inputKeyboardMutex);
        return result;
    }

    void SetJoystick(GameInput input, GameInput inputLast)
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        std::memset(&instance->inputstateJoystickSet, 0x00, sizeof(DIJOYSTATE));
        instance->inputJoystickSet = true;

        instance->inputstateJoystickSet.rglSlider[0] = static_cast<LONG>(input.JOYLT);
        instance->inputstateJoystickSet.rglSlider[1] = static_cast<LONG>(input.JOYRT);
        instance->inputstateJoystickSet.lX = static_cast<LONG>(input.JOYLAXISX);
        instance->inputstateJoystickSet.lY = static_cast<LONG>(input.JOYLAXISY);
        instance->inputstateJoystickSet.lRx = static_cast<LONG>(input.JOYRAXISX);
        instance->inputstateJoystickSet.lRy = static_cast<LONG>(input.JOYRAXISY);
        if (input.JOYA) instance->inputstateJoystickSet.rgbButtons[0] = 0x80;
        if (input.JOYB) instance->inputstateJoystickSet.rgbButtons[1] = 0x80;
        if (input.JOYX) instance->inputstateJoystickSet.rgbButtons[2] = 0x80;
        if (input.JOYY) instance->inputstateJoystickSet.rgbButtons[3] = 0x80;
        if (input.JOYLB) instance->inputstateJoystickSet.rgbButtons[4] = 0x80;
        if (input.JOYRB) instance->inputstateJoystickSet.rgbButtons[5] = 0x80;
        if (input.JOYSELECT) instance->inputstateJoystickSet.rgbButtons[6] = 0x80;
        if (input.JOYSTART) instance->inputstateJoystickSet.rgbButtons[7] = 0x80;
        if (input.JOYLS) instance->inputstateJoystickSet.rgbButtons[8] = 0x80;
        if (input.JOYRS) instance->inputstateJoystickSet.rgbButtons[9] = 0x80;
        if (!input.JOYUP && !input.JOYRIGHT && !input.JOYDOWN && !input.JOYLEFT) instance->inputstateJoystickSet.rgdwPOV[0] = -1;
        if (input.JOYUP && !input.JOYRIGHT && !input.JOYDOWN && !input.JOYLEFT) instance->inputstateJoystickSet.rgdwPOV[0] = 0;
        if (input.JOYUP && input.JOYRIGHT && !input.JOYDOWN && !input.JOYLEFT) instance->inputstateJoystickSet.rgdwPOV[0] = 4500;
        if (!input.JOYUP && input.JOYRIGHT && !input.JOYDOWN && !input.JOYLEFT) instance->inputstateJoystickSet.rgdwPOV[0] = 9000;
        if (!input.JOYUP && input.JOYRIGHT && input.JOYDOWN && !input.JOYLEFT) instance->inputstateJoystickSet.rgdwPOV[0] = 13500;
        if (!input.JOYUP && !input.JOYRIGHT && input.JOYDOWN && !input.JOYLEFT) instance->inputstateJoystickSet.rgdwPOV[0] = 18000;
        if (!input.JOYUP && !input.JOYRIGHT && input.JOYDOWN && input.JOYLEFT) instance->inputstateJoystickSet.rgdwPOV[0] = 22500;
        if (!input.JOYUP && !input.JOYRIGHT && !input.JOYDOWN && input.JOYLEFT) instance->inputstateJoystickSet.rgdwPOV[0] = 27000;
        if (input.JOYUP && !input.JOYRIGHT && !input.JOYDOWN && input.JOYLEFT) instance->inputstateJoystickSet.rgdwPOV[0] = 31500;

        ReleaseMutex(instance->inputAllMutex);
    }
    void SetMouse(GameInput input, GameInput inputLast)
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        std::memset(&instance->inputstateMouseSet, 0x00, sizeof(DIMOUSESTATE));
        instance->inputMouseSet = true;

        instance->inputstateMouseSet.lX = static_cast<int>(input.MOUSEX);
        instance->inputstateMouseSet.lY = static_cast<int>(input.MOUSEY);
        instance->inputstateMouseSet.lZ = static_cast<int>(input.WHEEL);
        if (input.LMB) instance->inputstateMouseSet.rgbButtons[0] = 0x80;
        if (input.RMB) instance->inputstateMouseSet.rgbButtons[1] = 0x80;
        if (input.MB) instance->inputstateMouseSet.rgbButtons[2] = 0x80;
        if (input.ME1) instance->inputstateMouseSet.rgbButtons[3] = 0x80;
        if (input.ME2) instance->inputstateMouseSet.rgbButtons[4] = 0x80;

        ReleaseMutex(instance->inputAllMutex);
    }
    void SetKeyboard(GameInput input, GameInput inputLast)
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        std::memset(&instance->inputstateKeyboardSet, 0x00, sizeof(DIKEYBAORDSTATE));
        instance->inputKeyboardSet = true;

        for (int i = 0; i < 256; i++)
        {
            if (i == DIK_ESCAPE) instance->inputstateKeyboardSet[i] = input.ESC ? 0x80 : 0x00;
            else if (i == DIK_TAB) instance->inputstateKeyboardSet[i] = input.TAB ? 0x80 : 0x00;
            else if (i == DIK_LSHIFT) instance->inputstateKeyboardSet[i] = input.LSHIFT ? 0x80 : 0x00;
            else if (i == DIK_RSHIFT) instance->inputstateKeyboardSet[i] = input.RSHIFT ? 0x80 : 0x00;
            else if (i == DIK_LCONTROL) instance->inputstateKeyboardSet[i] = input.CTRL ? 0x80 : 0x00;
            else if (i == DIK_BACK) instance->inputstateKeyboardSet[i] = input.BACK ? 0x80 : 0x00;
            else if (i == DIK_RETURN) instance->inputstateKeyboardSet[i] = input.RETURN ? 0x80 : 0x00;
            else if (i == DIK_SPACE) instance->inputstateKeyboardSet[i] = input.SPACE ? 0x80 : 0x00;
            else if (i == DIK_UP) instance->inputstateKeyboardSet[i] = input.AUP ? 0x80 : 0x00;
            else if (i == DIK_RIGHT) instance->inputstateKeyboardSet[i] = input.ARIGHT ? 0x80 : 0x00;
            else if (i == DIK_DOWN) instance->inputstateKeyboardSet[i] = input.ADOWN ? 0x80 : 0x00;
            else if (i == DIK_LEFT) instance->inputstateKeyboardSet[i] = input.ALEFT ? 0x80 : 0x00;
            else if (i == DIK_0) instance->inputstateKeyboardSet[i] = input.D0 ? 0x80 : 0x00;
            else if (i == DIK_1) instance->inputstateKeyboardSet[i] = input.D1 ? 0x80 : 0x00;
            else if (i == DIK_2) instance->inputstateKeyboardSet[i] = input.D2 ? 0x80 : 0x00;
            else if (i == DIK_3) instance->inputstateKeyboardSet[i] = input.D3 ? 0x80 : 0x00;
            else if (i == DIK_4) instance->inputstateKeyboardSet[i] = input.D4 ? 0x80 : 0x00;
            else if (i == DIK_5) instance->inputstateKeyboardSet[i] = input.D5 ? 0x80 : 0x00;
            else if (i == DIK_6) instance->inputstateKeyboardSet[i] = input.D6 ? 0x80 : 0x00;
            else if (i == DIK_7) instance->inputstateKeyboardSet[i] = input.D7 ? 0x80 : 0x00;
            else if (i == DIK_8) instance->inputstateKeyboardSet[i] = input.D8 ? 0x80 : 0x00;
            else if (i == DIK_9) instance->inputstateKeyboardSet[i] = input.D9 ? 0x80 : 0x00;
            else if (i == DIK_A) instance->inputstateKeyboardSet[i] = input.A ? 0x80 : 0x00;
            else if (i == DIK_B) instance->inputstateKeyboardSet[i] = input.B ? 0x80 : 0x00;
            else if (i == DIK_C) instance->inputstateKeyboardSet[i] = input.C ? 0x80 : 0x00;
            else if (i == DIK_D) instance->inputstateKeyboardSet[i] = input.D ? 0x80 : 0x00;
            else if (i == DIK_E) instance->inputstateKeyboardSet[i] = input.E ? 0x80 : 0x00;
            else if (i == DIK_F) instance->inputstateKeyboardSet[i] = input.F ? 0x80 : 0x00;
            else if (i == DIK_G) instance->inputstateKeyboardSet[i] = input.G ? 0x80 : 0x00;
            else if (i == DIK_H) instance->inputstateKeyboardSet[i] = input.H ? 0x80 : 0x00;
            else if (i == DIK_I) instance->inputstateKeyboardSet[i] = input.I ? 0x80 : 0x00;
            else if (i == DIK_J) instance->inputstateKeyboardSet[i] = input.J ? 0x80 : 0x00;
            else if (i == DIK_K) instance->inputstateKeyboardSet[i] = input.K ? 0x80 : 0x00;
            else if (i == DIK_L) instance->inputstateKeyboardSet[i] = input.L ? 0x80 : 0x00;
            else if (i == DIK_M) instance->inputstateKeyboardSet[i] = input.M ? 0x80 : 0x00;
            else if (i == DIK_N) instance->inputstateKeyboardSet[i] = input.N ? 0x80 : 0x00;
            else if (i == DIK_O) instance->inputstateKeyboardSet[i] = input.O ? 0x80 : 0x00;
            else if (i == DIK_P) instance->inputstateKeyboardSet[i] = input.P ? 0x80 : 0x00;
            else if (i == DIK_Q) instance->inputstateKeyboardSet[i] = input.Q ? 0x80 : 0x00;
            else if (i == DIK_R) instance->inputstateKeyboardSet[i] = input.R ? 0x80 : 0x00;
            else if (i == DIK_S) instance->inputstateKeyboardSet[i] = input.S ? 0x80 : 0x00;
            else if (i == DIK_T) instance->inputstateKeyboardSet[i] = input.T ? 0x80 : 0x00;
            else if (i == DIK_U) instance->inputstateKeyboardSet[i] = input.U ? 0x80 : 0x00;
            else if (i == DIK_V) instance->inputstateKeyboardSet[i] = input.V ? 0x80 : 0x00;
            else if (i == DIK_W) instance->inputstateKeyboardSet[i] = input.W ? 0x80 : 0x00;
            else if (i == DIK_X) instance->inputstateKeyboardSet[i] = input.X ? 0x80 : 0x00;
            else if (i == DIK_Y) instance->inputstateKeyboardSet[i] = input.Y ? 0x80 : 0x00;
            else if (i == DIK_Z) instance->inputstateKeyboardSet[i] = input.Z ? 0x80 : 0x00;
            else if (i == DIK_NUMPAD0) instance->inputstateKeyboardSet[i] = input.NUM0 ? 0x80 : 0x00;
            else if (i == DIK_NUMPAD1) instance->inputstateKeyboardSet[i] = input.NUM1 ? 0x80 : 0x00;
            else if (i == DIK_NUMPAD2) instance->inputstateKeyboardSet[i] = input.NUM2 ? 0x80 : 0x00;
            else if (i == DIK_NUMPAD3) instance->inputstateKeyboardSet[i] = input.NUM3 ? 0x80 : 0x00;
            else if (i == DIK_NUMPAD4) instance->inputstateKeyboardSet[i] = input.NUM4 ? 0x80 : 0x00;
            else if (i == DIK_NUMPAD5) instance->inputstateKeyboardSet[i] = input.NUM5 ? 0x80 : 0x00;
            else if (i == DIK_NUMPAD6) instance->inputstateKeyboardSet[i] = input.NUM6 ? 0x80 : 0x00;
            else if (i == DIK_NUMPAD7) instance->inputstateKeyboardSet[i] = input.NUM7 ? 0x80 : 0x00;
            else if (i == DIK_NUMPAD8) instance->inputstateKeyboardSet[i] = input.NUM8 ? 0x80 : 0x00;
            else if (i == DIK_NUMPAD9) instance->inputstateKeyboardSet[i] = input.NUM9 ? 0x80 : 0x00;
            else if (i == DIK_DIVIDE) instance->inputstateKeyboardSet[i] = input.NUMDIV ? 0x80 : 0x00;
            else if (i == DIK_MULTIPLY) instance->inputstateKeyboardSet[i] = input.NUMMUL ? 0x80 : 0x00;
            else if (i == DIK_SUBTRACT) instance->inputstateKeyboardSet[i] = input.NUMMIN ? 0x80 : 0x00;
            else if (i == DIK_ADD) instance->inputstateKeyboardSet[i] = input.NUMPLU ? 0x80 : 0x00;
            else if (i == DIK_NUMPADENTER) instance->inputstateKeyboardSet[i] = input.NUMRET ? 0x80 : 0x00;
            else if (i == DIK_NUMPADCOMMA) instance->inputstateKeyboardSet[i] = input.NUMDEL ? 0x80 : 0x00;
            else if (i == DIK_F1) instance->inputstateKeyboardSet[i] = input.F1 ? 0x80 : 0x00;
            else if (i == DIK_F2) instance->inputstateKeyboardSet[i] = input.F2 ? 0x80 : 0x00;
            else if (i == DIK_F3) instance->inputstateKeyboardSet[i] = input.F3 ? 0x80 : 0x00;
            else if (i == DIK_F4) instance->inputstateKeyboardSet[i] = input.F4 ? 0x80 : 0x00;
            else if (i == DIK_F5) instance->inputstateKeyboardSet[i] = input.F5 ? 0x80 : 0x00;
            else if (i == DIK_F6) instance->inputstateKeyboardSet[i] = input.F6 ? 0x80 : 0x00;
            else if (i == DIK_F7) instance->inputstateKeyboardSet[i] = input.F7 ? 0x80 : 0x00;
            else if (i == DIK_F8) instance->inputstateKeyboardSet[i] = input.F8 ? 0x80 : 0x00;
            else if (i == DIK_F9) instance->inputstateKeyboardSet[i] = input.F9 ? 0x80 : 0x00;
            else if (i == DIK_F10) instance->inputstateKeyboardSet[i] = input.F10 ? 0x80 : 0x00;
            else if (i == DIK_F11) instance->inputstateKeyboardSet[i] = input.F11 ? 0x80 : 0x00;
            else if (i == DIK_F12) instance->inputstateKeyboardSet[i] = input.F12 ? 0x80 : 0x00;
            else if (i == DIK_COMMA) instance->inputstateKeyboardSet[i] = input.COMMA ? 0x80 : 0x00;
            else if (i == DIK_PERIOD) instance->inputstateKeyboardSet[i] = input.DOT ? 0x80 : 0x00;
            else if (i == DIK_MINUS) instance->inputstateKeyboardSet[i] = input.F12 ? 0x80 : 0x00;
            else if (i == VK_OEM_PLUS) instance->inputstateKeyboardSet[i] = input.MINUS ? 0x80 : 0x00;
        }

        ReleaseMutex(instance->inputAllMutex);
    }
    void GetJoystick(GameInput* input)
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);
        
        int LT = static_cast<int>(instance->inputstateJoystickGet.rglSlider[0]);
        int RT = static_cast<int>(instance->inputstateJoystickGet.rglSlider[1]);
        int LAXISX = static_cast<int>(instance->inputstateJoystickGet.lX);
        int LAXISY = static_cast<int>(instance->inputstateJoystickGet.lY);
        int RAXISX = static_cast<int>(instance->inputstateJoystickGet.lRx);
        int RAXISY = static_cast<int>(instance->inputstateJoystickGet.lRy);

        if (instance->inputstateJoystickGet.rgbButtons[0] == 0x80) input->JOYA = true;
        if (instance->inputstateJoystickGet.rgbButtons[1] == 0x80) input->JOYB = true;
        if (instance->inputstateJoystickGet.rgbButtons[2] == 0x80) input->JOYX = true;
        if (instance->inputstateJoystickGet.rgbButtons[3] == 0x80) input->JOYY = true;
        if (instance->inputstateJoystickGet.rgbButtons[4] == 0x80) input->JOYLB = true;
        if (instance->inputstateJoystickGet.rgbButtons[5] == 0x80) input->JOYRB = true;
        if (instance->inputstateJoystickGet.rgbButtons[6] == 0x80) input->JOYSELECT = true;
        if (instance->inputstateJoystickGet.rgbButtons[7] == 0x80) input->JOYSTART = true;
        if (instance->inputstateJoystickGet.rgbButtons[8] == 0x80) input->JOYLS = true;
        if (instance->inputstateJoystickGet.rgbButtons[9] == 0x80) input->JOYRS = true;
        if (instance->inputstateJoystickGet.rgdwPOV[0] == 0 || instance->inputstateJoystickGet.rgdwPOV[0] == 4500 || instance->inputstateJoystickGet.rgdwPOV[0] == 31500) input->JOYUP = true;
        if (instance->inputstateJoystickGet.rgdwPOV[0] == 4500 || instance->inputstateJoystickGet.rgdwPOV[0] == 9000 || instance->inputstateJoystickGet.rgdwPOV[0] == 13500) input->JOYRIGHT = true;
        if (instance->inputstateJoystickGet.rgdwPOV[0] == 13500 || instance->inputstateJoystickGet.rgdwPOV[0] == 18000 || instance->inputstateJoystickGet.rgdwPOV[0] == 22500) input->JOYDOWN = true;
        if (instance->inputstateJoystickGet.rgdwPOV[0] == 22500 || instance->inputstateJoystickGet.rgdwPOV[0] == 27000 || instance->inputstateJoystickGet.rgdwPOV[0] == 31500) input->JOYLEFT = true;
        if (LT > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) input->JOYLT = LT;
        if (RT > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) input->JOYRT = RT;
        if (LAXISX > 99 || LAXISX < -99) input->JOYLAXISX = LAXISX;
        if (LAXISY > 99 || LAXISY < -99) input->JOYLAXISY = LAXISY;
        if (RAXISX > 99 || RAXISX < -99) input->JOYRAXISX = RAXISX;
        if (RAXISY > 99 || RAXISY < -99) input->JOYRAXISY = RAXISY;

        ReleaseMutex(instance->inputAllMutex);
    }
    void GetMouse(GameInput* input)
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);

        input->MOUSEX = static_cast<int>(instance->inputstateMouseGet.lX);
        input->MOUSEY = static_cast<int>(instance->inputstateMouseGet.lY);
        input->WHEEL = static_cast<int>(instance->inputstateMouseGet.lZ);
        if (instance->inputstateMouseGet.rgbButtons[0] & 0x80) input->LMB = true;
        if (instance->inputstateMouseGet.rgbButtons[1] & 0x80) input->RMB = true;
        if (instance->inputstateMouseGet.rgbButtons[2] & 0x80) input->MB = true;
        if (instance->inputstateMouseGet.rgbButtons[3] & 0x80) input->ME1 = true;
        if (instance->inputstateMouseGet.rgbButtons[4] & 0x80) input->ME2 = true;

        ReleaseMutex(instance->inputAllMutex);
    }
    void GetKeyboard(GameInput* input)
    {
        WaitForSingleObject(instance->inputAllMutex, INFINITE);

        for (int i = 0; i < 256; i++) {
            if (instance->inputstateKeyboardGet[i] & 0x80) {
                if (i == DIK_ESCAPE) input->ESC = true;
                if (i == DIK_TAB) input->TAB = true;
                if (i == DIK_LSHIFT) input->LSHIFT = true;
                if (i == DIK_RSHIFT) input->RSHIFT = true;
                if (i == DIK_LCONTROL) input->CTRL = true;
                if (i == DIK_BACK) input->BACK = true;
                if (i == DIK_RETURN) input->RETURN = true;
                if (i == DIK_SPACE) input->SPACE = true;
                if (i == DIK_UP) input->AUP = true;
                if (i == DIK_RIGHT) input->ARIGHT = true;
                if (i == DIK_DOWN) input->ADOWN = true;
                if (i == DIK_LEFT) input->ALEFT = true;
                if (i == DIK_0) input->D0 = true;
                if (i == DIK_1) input->D1 = true;
                if (i == DIK_2) input->D2 = true;
                if (i == DIK_3) input->D3 = true;
                if (i == DIK_4) input->D4 = true;
                if (i == DIK_5) input->D5 = true;
                if (i == DIK_6) input->D6 = true;
                if (i == DIK_7) input->D7 = true;
                if (i == DIK_8) input->D8 = true;
                if (i == DIK_9) input->D9 = true;
                if (i == DIK_A) input->A = true;
                if (i == DIK_B) input->B = true;
                if (i == DIK_C) input->C = true;
                if (i == DIK_D) input->D = true;
                if (i == DIK_E) input->E = true;
                if (i == DIK_F) input->F = true;
                if (i == DIK_G) input->G = true;
                if (i == DIK_H) input->H = true;
                if (i == DIK_I) input->I = true;
                if (i == DIK_J) input->J = true;
                if (i == DIK_K) input->K = true;
                if (i == DIK_L) input->L = true;
                if (i == DIK_M) input->M = true;
                if (i == DIK_N) input->N = true;
                if (i == DIK_O) input->O = true;
                if (i == DIK_P) input->P = true;
                if (i == DIK_Q) input->Q = true;
                if (i == DIK_R) input->R = true;
                if (i == DIK_S) input->S = true;
                if (i == DIK_T) input->T = true;
                if (i == DIK_U) input->U = true;
                if (i == DIK_V) input->V = true;
                if (i == DIK_W) input->W = true;
                if (i == DIK_X) input->X = true;
                if (i == DIK_Y) input->Y = true;
                if (i == DIK_Z) input->Z = true;
                if (i == DIK_NUMPAD0) input->NUM0 = true;
                if (i == DIK_NUMPAD1) input->NUM1 = true;
                if (i == DIK_NUMPAD2) input->NUM2 = true;
                if (i == DIK_NUMPAD3) input->NUM3 = true;
                if (i == DIK_NUMPAD4) input->NUM4 = true;
                if (i == DIK_NUMPAD5) input->NUM5 = true;
                if (i == DIK_NUMPAD6) input->NUM6 = true;
                if (i == DIK_NUMPAD7) input->NUM7 = true;
                if (i == DIK_NUMPAD8) input->NUM8 = true;
                if (i == DIK_NUMPAD9) input->NUM9 = true;
                if (i == DIK_DIVIDE) input->NUMDIV = true;
                if (i == DIK_MULTIPLY) input->NUMMUL = true;
                if (i == DIK_SUBTRACT) input->NUMMIN = true;
                if (i == DIK_ADD) input->NUMPLU = true;
                if (i == DIK_NUMPADENTER) input->NUMRET = true;
                if (i == DIK_NUMPADCOMMA) input->NUMDEL = true;
                if (i == DIK_F1) input->F1 = true;
                if (i == DIK_F2) input->F2 = true;
                if (i == DIK_F3) input->F3 = true;
                if (i == DIK_F4) input->F4 = true;
                if (i == DIK_F5) input->F5 = true;
                if (i == DIK_F6) input->F6 = true;
                if (i == DIK_F7) input->F7 = true;
                if (i == DIK_F8) input->F8 = true;
                if (i == DIK_F9) input->F9 = true;
                if (i == DIK_F10) input->F10 = true;
                if (i == DIK_F11) input->F11 = true;
                if (i == DIK_F12) input->F12 = true;
                if (i == DIK_COMMA) input->COMMA = true;
                if (i == DIK_PERIOD) input->DOT = true;
                if (i == DIK_MINUS) input->F12 = true;
                if (i == VK_OEM_PLUS) input->MINUS = true;
            }
        }

        ReleaseMutex(instance->inputAllMutex);
    }
};
HRESULT DirectInput8GetDeviceStateReal(IDirectInputDevice8* pDevice, DWORD cbData, LPVOID lpvData);



// --- Functions ---
bool DirectInput8HookInit();
bool DirectInput8HookUninit();
bool IsDirectInput8HookActive();



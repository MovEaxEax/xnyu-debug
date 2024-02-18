#pragma once

// --- Typedefs ---
typedef DWORD(__stdcall* XInputGetStateT)(DWORD dwUserIndex, XINPUT_STATE* pState);



// --- Variables ---
extern XInputGetStateT pXInputGetState;



// --- XInputGetStateT ---
template <typename FuncT>
class XInputGetStateHook : public xNyuHook<XInputGetStateT> {
private:
    XINPUT_STATE inputstateJoystickGet = XINPUT_STATE();
    XINPUT_STATE inputstateJoystickSet = XINPUT_STATE();
    DWORD packetNumber = -1;
    auto inputJoystickCounterTimer = std::chrono::high_resolution_clock::now();
    float inputJoystickFramesEstimated = 0;
    float inputJoystickTimeFrames = 0;
    float inputJoystickTotalFrames = 0;
    bool inputJoystickUsed = false;
    std::vector<int> inputJoystickThreadIDs;
    bool inputJoystickDeactivate = false;
    bool inputJoystickSet = false;
    HANDLE inputJoystickMutex = CreateMutex(NULL, FALSE, NULL);

public:
    static XInputGetStateHook* instance;
    XInputGetStateHook(void* originalAddress) : xNyuHook<XInputGetStateT>(originalAddress, CustomHook) { instance = this; }
    static DWORD __stdcall CustomHook(DWORD dwUserIndex, XINPUT_STATE* pState)
    {
        WaitForSingleObject(instance->inputJoystickMutex, INFINITE);

        if (instance->HookInit)
        {
            DebugConsoleOutput("XInput1_4GetState() Hook active...", true, "yellow");
            instance->HookInit = false;
        }

        DWORD result = instance->callTrampoline(dwUserIndex, pState);

        if (dwUserIndex == 0)
        {
            instance->inputJoystickUsed = true;
            int threadId = (int)GetCurrentThreadId();
            if (std::find(instance->inputJoystickThreadIDs.begin(), instance->inputJoystickThreadIDs.end(), threadId) == instance->inputJoystickThreadIDs.end()) instance->inputJoystickThreadIDs.push_back(threadId);

            instance->inputJoystickTimeFrames += (float)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - instance->inputJoystickCounterTimer)).count();
            instance->inputJoystickTotalFrames += 1.0f;
            instance->inputJoystickCounterTimer = std::chrono::high_resolution_clock::now();

            if (instance->inputJoystickTotalFrames >= 15)
            {
                instance->inputJoystickFramesEstimated = (float)round(1000.0f / (instance->inputJoystickTimeFrames / instance->inputJoystickTotalFrames));
                instance->inputJoystickTimeFrames = 0;
                instance->inputJoystickTotalFrames = 0;
            }

            if (instance->packetNumber == -1) instance->packetNumber = pState->dwPacketNumber;
            else
            {
                instance->packetNumber++;
                if (instance->packetNumber > 0xDEADBEEF) instance->packetNumber = 1;
                pState->dwPacketNumber = instance->packetNumber
            }

            std::memcpy(&instance->inputstateJoystickGet, pState, sizeof(XINPUT_STATE));
            if (instance->inputJoystickDeactivate || instance->inputJoystickSet) std::memset(pState, 0x00, sizeof(XINPUT_STATE)));
            if (instance->inputJoystickSet)
            {
                std::memcpy(pState, &instance->inputstateJoystickSet, sizeof(XINPUT_STATE));
                instance->inputJoystickSet = false;
            }
        }

        ReleaseMutex(instance->inputJoystickMutex);
        return result;
    }

    bool GetJoystickUsed()
    {
        WaitForSingleObject(instance->inputJoystickMutex, INFINITE);
        bool result = instance->inputJoystickUsed;
        ReleaseMutex(instance->inputJoystickMutex);
        return result;
    }
    float GetJoystickFrames()
    {
        WaitForSingleObject(instance->inputJoystickMutex, INFINITE);
        float result = instance->inputJoystickFramesEstimated;
        ReleaseMutex(instance->inputJoystickMutex);
        return result;
    }
    void SetJoystickDeactivated(bool value)
    {
        WaitForSingleObject(instance->inputJoystickMutex, INFINITE);
        instance->inputJoystickDeactivate = value;
        ReleaseMutex(instance->inputJoystickMutex);
    }

    bool IsSetJoystickDone()
    {
        WaitForSingleObject(instance->inputJoystickMutex, INFINITE);
        bool result = !instance->inputJoystickSet;
        ReleaseMutex(instance->inputJoystickMutex);
        return result;
    }

    void SetJoystick(GameInput input, GameInput inputLast)
    {
        WaitForSingleObject(instance->inputJoystickMutex, INFINITE);
        std::memset(&instance->inputstateJoystickSet, 0x00, sizeof(DIJOYSTATE));
        instance->inputJoystickSet = true;

        short RAXISX = static_cast<short>((static_cast<float>(input.JOYRAXISX) / 1000.0f) * 32767.0f);
        short RAXISY = static_cast<short>((static_cast<float>(input.JOYRAXISY) / 1000.0f) * 32767.0f);
        short LAXISX = static_cast<short>((static_cast<float>(input.JOYLAXISX) / 1000.0f) * 32767.0f);
        short LAXISY = static_cast<short>((static_cast<float>(input.JOYLAXISY) / 1000.0f) * 32767.0f);

        if (input.JOYA) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_A;
        if (input.JOYB) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_B;
        if (input.JOYX) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_X;
        if (input.JOYY) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_Y;
        if (input.JOYRB) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;
        if (input.JOYLB) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_SHOULDER;
        if (input.JOYSTART) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_START;
        if (input.JOYSELECT) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_BACK;
        if (input.JOYUP) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_UP;
        if (input.JOYDOWN) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
        if (input.JOYLEFT) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
        if (input.JOYRIGHT) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
        if (input.JOYRS) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_THUMB;
        if (input.JOYLS) inputstateJoystickSet.Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_THUMB;
        inputstateJoystickSet.Gamepad.bRightTrigger = (BYTE)input.JOYRT;
        inputstateJoystickSet.Gamepad.bLeftTrigger = (BYTE)input.JOYLT;
        inputstateJoystickSet.Gamepad.sThumbRX = RAXISX;
        inputstateJoystickSet.Gamepad.sThumbRY = RAXISY;
        inputstateJoystickSet.Gamepad.sThumbLX = LAXISX;
        inputstateJoystickSet.Gamepad.sThumbLY = LAXISY;

        ReleaseMutex(instance->inputJoystickMutex);
    }
    void GetJoystick(GameInput* input)
    {
        WaitForSingleObject(instance->inputJoystickMutex, INFINITE);

        // Joystick input
        int RAXISX = static_cast<int>((static_cast<float>(inputstateJoystickGet.Gamepad.sThumbRX) / 32767.0f) * 1000.0f);
        int RAXISY = static_cast<int>((static_cast<float>(inputstateJoystickGet.Gamepad.sThumbRY) / 32767.0f) * 1000.0f);
        int LAXISX = static_cast<int>((static_cast<float>(inputstateJoystickGet.Gamepad.sThumbLX) / 32767.0f) * 1000.0f);
        int LAXISY = static_cast<int>((static_cast<float>(inputstateJoystickGet.Gamepad.sThumbLY) / 32767.0f) * 1000.0f);

        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_A) input->JOYA = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_B) input->JOYB = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_X) input->JOYX = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_Y) input->JOYY = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) input->JOYRB = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) input->JOYLB = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_START) input->JOYSTART = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) input->JOYSELECT = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) input->JOYUP = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) input->JOYDOWN = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) input->JOYLEFT = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) input->JOYRIGHT = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) input->JOYRS = true;
        if (inputstateJoystickGet.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) input->JOYLS = true;
        if (inputstateJoystickGet.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) input->JOYRT = inputstateJoystickGet.Gamepad.bRightTrigger;
        if (inputstateJoystickGet.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) input->JOYLT = inputstateJoystickGet.Gamepad.bLeftTrigger;
        if (RAXISX > 99 || RAXISX < -99) input->JOYRAXISX = RAXISX;
        if (RAXISY > 99 || RAXISY < -99) input->JOYRAXISY = RAXISY;
        if (LAXISX > 99 || LAXISX < -99) input->JOYLAXISX = LAXISX;
        if (LAXISY > 99 || LAXISY < -99) input->JOYLAXISY = LAXISY;

        ReleaseMutex(instance->inputJoystickMutex);
    }
};
DWORD XInputGetStateReal(DWORD dwUserIndex, XINPUT_STATE* pState);



// --- Functions ---
bool XInputHookInit();
bool XInputHookUninit();
bool IsXInputHookActive();



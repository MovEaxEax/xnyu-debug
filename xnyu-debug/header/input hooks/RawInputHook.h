#pragma once

// --- Typedefs ---
typedef UINT(__stdcall* GetRawInputDataT)(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader);



// --- Variables ---
extern GetRawInputDataT pGetRawInputData;



// --- GetRawInputData ---
template <typename FuncT>
class GetRawInputDataHook : public xNyuHook<GetRawInputDataT> {
private:
    GameInput inputstateDeviceCurrent = GameInput();
    BYTE inputGetBuffer[65000];
    int inputGetBufferSize = 0;
    BYTE inputSetBuffer[65000];
    int inputSetBufferSize = 0;
    auto inputDeviceCounterTimer = std::chrono::high_resolution_clock::now();
    float inputDeviceFramesEstimated = 0;
    float inputDeviceTimeFrames = 0;
    float inputDeviceTotalFrames = 0;
    bool inputDeviceUsed = false;
    std::vector<int> inputDeviceThreadIDs;
    bool inputDeviceDeactivate = false;
    bool inputDeviceSet = false;
    HANDLE inputDeviceMutex = CreateMutex(NULL, FALSE, NULL);

public:
    static GetRawInputDataHook* instance;
    GetRawInputDataHook(void* originalAddress) : xNyuHook<GetRawInputDataT>(originalAddress, CustomHook) { instance = this; }
    static UINT __stdcall CustomHook(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
    {
        WaitForSingleObject(instance->inputDeviceMutex, INFINITE);

        if (instance->HookInit)
        {
            DebugConsoleOutput("GetRawInputData() Hook active...", true, "yellow");
            instance->HookInit = false;
        }

        UINT result = instance->callTrampoline(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);

        instance->inputDeviceUsed = true;
        int threadId = (int)GetCurrentThreadId();
        if (std::find(instance->inputDeviceThreadIDs.begin(), instance->inputDeviceThreadIDs.end(), threadId) == instance->inputDeviceThreadIDs.end()) instance->inputDeviceThreadIDs.push_back(threadId);

        instance->inputDeviceTimeFrames += (float)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - instance->inputDeviceCounterTimer)).count();
        instance->inputDeviceTotalFrames += 1.0f;
        instance->inputDeviceCounterTimer = std::chrono::high_resolution_clock::now();

        if (instance->inputDeviceTotalFrames >= 15)
        {
            instance->inputDeviceFramesEstimated = (float)round(1000.0f / (instance->inputDeviceTimeFrames / instance->inputDeviceTotalFrames));
            instance->inputDeviceTimeFrames = 0;
            instance->inputDeviceTotalFrames = 0;
        }

        int resultBytesWritten = static_cast<int>(result);
        if (uiCommand == RID_INPUT)
        {
            if (pData != nullptr)
            {
                if (resultBytesWritten > 0)
                {
                    std::memcpy(instance->inputGetBuffer + instance->inputGetBufferSize, pData, resultBytesWritten);
                    instance->inputGetBufferSize += resultBytesWritten;
                    instance->ParseInputStateGet();
                }
            }
        }

        if (instance->inputDeviceSet)
        {
            if (uiCommand == RID_HEADER)
            {
                if (pData != nullptr)
                {
                    *pcbSize = instance->instance->inputSetBufferSize;
                    result = 0;
                }
            }
            else if (uiCommand == RID_INPUT)
            {
                if (pData == nullptr)
                {
                    *pcbSize = instance->inputSetBufferSize;
                    result = 0;
                }
                else
                {
                    UINT targetBufferSize = min(*pcbSize, instance->inputSetBufferSize);

                    std::memcpy(pData, instance->inputSetBuffer, targetBufferSize);

                    if (targetBufferSize < instance->inputSetBufferSize)
                    {
                        std::memmove(instance->inputSetBuffer, instance->inputSetBuffer + targetBufferSize, instance->inputSetBufferSize - targetBufferSize);
                        instance->inputSetBufferSize -= targetBufferSize;
                    }
                    else
                    {
                        instance->inputSetBufferSize = 0;
                    }

                    *pcbSize = targetBufferSize;
                    result = targetBufferSize;
                }
            }

            if (instance->inputSetBufferSize == 0) instance->inputDeviceSet = false;
        }
        else if (instance->inputDeviceDeactivate)
        {
            if (uiCommand == RID_HEADER)
            {
                if (pData != nullptr)
                {
                    *pcbSize = 0;
                    result = 0;
                }
            }
            else if (uiCommand == RID_INPUT)
            {
                if (pData == nullptr)
                {
                    *pcbSize = 0;
                    result = 0;
                }
                else
                {
                    UINT targetBufferSize = min(*pcbSize, inputGetBufferSize);
                    std::memset(pData, 0x00, targetBufferSize);

                    *pcbSize = 0;
                    result = 0;
                }
            }
        }

        ReleaseMutex(instance->inputDeviceMutex);
        return result;
    }

    bool GetDeviceUsed()
    {
        WaitForSingleObject(instance->inputDeviceMutex, INFINITE);
        bool result = instance->inputDeviceUsed;
        ReleaseMutex(instance->inputDeviceMutex);
        return result;
    }
    float GetDeviceFrames()
    {
        WaitForSingleObject(instance->inputDeviceMutex, INFINITE);
        float result = instance->inputDeviceFramesEstimated;
        ReleaseMutex(instance->inputDeviceMutex);
        return result;
    }
    void SetMouseDeactivated(bool value)
    {
        WaitForSingleObject(instance->inputDeviceMutex, INFINITE);
        instance->inputDeviceDeactivate = value;
        ReleaseMutex(instance->inputDeviceMutex);
    }
    void SetKeyboardDeactivated(bool value)
    {
        WaitForSingleObject(instance->inputDeviceMutex, INFINITE);
        instance->inputDeviceDeactivate = value;
        ReleaseMutex(instance->inputDeviceMutex);
    }

    void SetMousePacketToBuffer(USHORT flags, USHORT wheel = 0, LONG x = 0, LONG y = 0, bool relative = true)
    {
        RAWINPUT packet = RAWINPUT();
        packet.header.dwType = RIM_TYPEMOUSE;
        packet.data.mouse.usButtonFlags |= flags;
        packet.data.mouse.usButtonData = wheel;
        packet.data.mouse.usFlags = relative ? MOUSE_MOVE_RELATIVE : MOUSE_MOVE_ABSOLUTE;
        packet.data.mouse.lLastX = x;
        packet.data.mouse.lLastY = y;
        packet.header.dwSize = sizeof(packet); std::memcpy(instance->inputSetBuffer + instance->inputSetBufferSize, &packet, packet.header.dwSize);
        instance->inputSetBufferSize += packet.header.dwSize;
    }

    void SetMouse(GameInput input, GameInput inputLast)
    {
        WaitForSingleObject(instance->inputDeviceMutex, INFINITE);

        if (input.LMB != inputLast.LMB) SetMousePacketToBuffer(input.LMB ? RI_MOUSE_LEFT_BUTTON_DOWN : RI_MOUSE_LEFT_BUTTON_UP);
        if (input.RMB != inputLast.RMB) SetMousePacketToBuffer(input.RMB ? RI_MOUSE_RIGHT_BUTTON_DOWN : RI_MOUSE_RIGHT_BUTTON_UP);
        if (input.MB != inputLast.MB) SetMousePacketToBuffer(input.MB ? RI_MOUSE_MIDDLE_BUTTON_DOWN : RI_MOUSE_MIDDLE_BUTTON_UP);
        if (input.ME1 != inputLast.ME1) SetMousePacketToBuffer(input.ME1 ? RI_MOUSE_BUTTON_4_DOWN : RI_MOUSE_BUTTON_4_UP);
        if (input.ME2 != inputLast.ME2) SetMousePacketToBuffer(input.LMB ? RI_MOUSE_BUTTON_5_DOWN : RI_MOUSE_BUTTON_5_UP);
        if (input.WHEEL != 0) SetMousePacketToBuffer(RI_MOUSE_WHEEL, (USHORT)(input.WHEEL > 0 ? input.WHEEL : USHRT_MAX - input.WHEEL));

        instance->inputDeviceSet = true;
        ReleaseMutex(instance->inputDeviceMutex);
    }

    void SetKeyboardPacketToBuffer(USHORT vKey, USHORT flags)
    {
        RAWINPUT packet = RAWINPUT();
        packet.header.dwType = RIM_TYPEKEYBOARD;
        packet.data.keyboard.Flags |= flags;
        packet.data.keyboard.VKey = vKey;
        packet.header.dwSize = sizeof(packet); std::memcpy(instance->inputSetBuffer + instance->inputSetBufferSize, &packet, packet.header.dwSize);
        instance->inputSetBufferSize += packet.header.dwSize;
    }

    void SetKeyboard(GameInput input, GameInput inputLast)
    {
        WaitForSingleObject(instance->inputDeviceMutex, INFINITE);

        if (input.ESC != inputLast.ESC) instance->SetKeyboardPacketToBuffer(VK_ESCAPE, input.ESC ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.TAB != inputLast.TAB) instance->SetKeyboardPacketToBuffer(VK_TAB, input.TAB ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.LSHIFT != inputLast.LSHIFT) instance->SetKeyboardPacketToBuffer(VK_LSHIFT, input.LSHIFT ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.RSHIFT != inputLast.RSHIFT) instance->SetKeyboardPacketToBuffer(VK_RSHIFT, input.RSHIFT ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.CTRL != inputLast.CTRL) instance->SetKeyboardPacketToBuffer(VK_CONTROL, input.CTRL ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.ALT != inputLast.ALT) instance->SetKeyboardPacketToBuffer(VK_MENU, input.ALT ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.BACK != inputLast.BACK) instance->SetKeyboardPacketToBuffer(VK_BACK, input.BACK ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.RETURN != inputLast.RETURN) instance->SetKeyboardPacketToBuffer(VK_RETURN, input.RETURN ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.SPACE != inputLast.SPACE) instance->SetKeyboardPacketToBuffer(VK_SPACE, input.SPACE ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.AUP != inputLast.AUP) instance->SetKeyboardPacketToBuffer(VK_UP, input.AUP ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.ARIGHT != inputLast.ARIGHT) instance->SetKeyboardPacketToBuffer(VK_RIGHT, input.ARIGHT ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.ADOWN != inputLast.ADOWN) instance->SetKeyboardPacketToBuffer(VK_DOWN, input.ADOWN ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.ALEFT != inputLast.ALEFT) instance->SetKeyboardPacketToBuffer(VK_LEFT, input.ALEFT ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.D0 != inputLast.D0) instance->SetKeyboardPacketToBuffer(0x30, input.D0 ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.D1 != inputLast.D1) instance->SetKeyboardPacketToBuffer(0x31, input.D1 ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.D2 != inputLast.D2) instance->SetKeyboardPacketToBuffer(0x32, input.D2 ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.D3 != inputLast.D3) instance->SetKeyboardPacketToBuffer(0x33, input.D3 ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.D4 != inputLast.D4) instance->SetKeyboardPacketToBuffer(0x34, input.D4 ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.D5 != inputLast.D5) instance->SetKeyboardPacketToBuffer(0x35, input.D5 ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.D6 != inputLast.D6) instance->SetKeyboardPacketToBuffer(0x36, input.D6 ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.D7 != inputLast.D7) instance->SetKeyboardPacketToBuffer(0x37, input.D7 ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.D8 != inputLast.D8) instance->SetKeyboardPacketToBuffer(0x38, input.D8 ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.D9 != inputLast.D9) instance->SetKeyboardPacketToBuffer(0x39, input.D9 ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.A != inputLast.A) instance->SetKeyboardPacketToBuffer(0x41, input.A ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.B != inputLast.B) instance->SetKeyboardPacketToBuffer(0x42, input.B ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.C != inputLast.C) instance->SetKeyboardPacketToBuffer(0x43, input.C ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.D != inputLast.D) instance->SetKeyboardPacketToBuffer(0x44, input.D ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.E != inputLast.E) instance->SetKeyboardPacketToBuffer(0x45, input.E ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.F != inputLast.F) instance->SetKeyboardPacketToBuffer(0x46, input.F ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.G != inputLast.G) instance->SetKeyboardPacketToBuffer(0x47, input.G ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.H != inputLast.H) instance->SetKeyboardPacketToBuffer(0x48, input.H ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.I != inputLast.I) instance->SetKeyboardPacketToBuffer(0x49, input.I ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.J != inputLast.J) instance->SetKeyboardPacketToBuffer(0x4A, input.J ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.K != inputLast.K) instance->SetKeyboardPacketToBuffer(0x4B, input.K ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.L != inputLast.L) instance->SetKeyboardPacketToBuffer(0x4C, input.L ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.M != inputLast.M) instance->SetKeyboardPacketToBuffer(0x4D, input.M ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.N != inputLast.N) instance->SetKeyboardPacketToBuffer(0x4E, input.N ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.O != inputLast.O) instance->SetKeyboardPacketToBuffer(0x4F, input.O ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.P != inputLast.P) instance->SetKeyboardPacketToBuffer(0x50, input.P ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.Q != inputLast.Q) instance->SetKeyboardPacketToBuffer(0x51, input.Q ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.R != inputLast.R) instance->SetKeyboardPacketToBuffer(0x52, input.R ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.S != inputLast.S) instance->SetKeyboardPacketToBuffer(0x53, input.S ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.T != inputLast.T) instance->SetKeyboardPacketToBuffer(0x54, input.T ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.U != inputLast.U) instance->SetKeyboardPacketToBuffer(0x55, input.U ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.V != inputLast.V) instance->SetKeyboardPacketToBuffer(0x56, input.V ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.W != inputLast.W) instance->SetKeyboardPacketToBuffer(0x57, input.W ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.X != inputLast.X) instance->SetKeyboardPacketToBuffer(0x58, input.X ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.Y != inputLast.Y) instance->SetKeyboardPacketToBuffer(0x59, input.Y ? RI_KEY_MAKE : RI_KEY_BREAK);
        if (input.Z != inputLast.Z) instance->SetKeyboardPacketToBuffer(0x5A, input.Z ? RI_KEY_MAKE : RI_KEY_BREAK);

        instance->inputDeviceSet = true;
        ReleaseMutex(instance->inputDeviceMutex);
    }

    bool IsSetMouseDone()
    {
        WaitForSingleObject(instance->inputDeviceMutex, INFINITE);
        bool result = !instance->inputDeviceSet;
        ReleaseMutex(instance->inputDeviceMutex);
        return result;
    }
    bool IsSetKeyboardDone()
    {
        WaitForSingleObject(instance->inputDeviceMutex, INFINITE);
        bool result = !instance->inputDeviceSet;
        ReleaseMutex(instance->inputDeviceMutex);
        return result;
    }

    void GetMouse(GameInput* input)
    {
        WaitForSingleObject(instance->inputDeviceMutex, INFINITE);

        input->LMB = instance->inputstateDeviceCurrent.LMB;
        input->RMB = instance->inputstateDeviceCurrent.RMB;
        input->MB = instance->inputstateDeviceCurrent.MB;
        input->ME1 = instance->inputstateDeviceCurrent.ME1;
        input->ME2 = instance->inputstateDeviceCurrent.ME2;
        input->WHEEL = instance->inputstateDeviceCurrent.WHEEL;
        input->MOUSEX = instance->inputstateDeviceCurrent.MOUSEX;
        input->MOUSEY = instance->inputstateDeviceCurrent.MOUSEY;
        input->SETMOUSE = instance->inputstateDeviceCurrent.SETMOUSE;

        ReleaseMutex(instance->inputDeviceMutex);
    }
    void GetKeyboard(GameInput* input)
    {
        WaitForSingleObject(instance->inputDeviceMutex, INFINITE);

        input->ESC = instance->inputstateDeviceCurrent.ESC;
        input->TAB = instance->inputstateDeviceCurrent.TAB;
        input->LSHIFT = instance->inputstateDeviceCurrent.LSHIFT;
        input->RSHIFT = instance->inputstateDeviceCurrent.RSHIFT;
        input->CTRL = instance->inputstateDeviceCurrent.CTRL;
        input->ALT = instance->inputstateDeviceCurrent.ALT;
        input->BACK = instance->inputstateDeviceCurrent.BACK;
        input->RETURN = instance->inputstateDeviceCurrent.RETURN;
        input->SPACE = instance->inputstateDeviceCurrent.SPACE;
        input->AUP = instance->inputstateDeviceCurrent.AUP;
        input->ARIGHT = instance->inputstateDeviceCurrent.ARIGHT;
        input->ADOWN = instance->inputstateDeviceCurrent.ADOWN;
        input->ALEFT = instance->inputstateDeviceCurrent.ALEFT;
        input->D0 = instance->inputstateDeviceCurrent.D0;
        input->D1 = instance->inputstateDeviceCurrent.D1;
        input->D2 = instance->inputstateDeviceCurrent.D2;
        input->D3 = instance->inputstateDeviceCurrent.D3;
        input->D4 = instance->inputstateDeviceCurrent.D4;
        input->D5 = instance->inputstateDeviceCurrent.D5;
        input->D6 = instance->inputstateDeviceCurrent.D6;
        input->D7 = instance->inputstateDeviceCurrent.D7;
        input->D8 = instance->inputstateDeviceCurrent.D8;
        input->D9 = instance->inputstateDeviceCurrent.D9;
        input->A = instance->inputstateDeviceCurrent.A;
        input->B = instance->inputstateDeviceCurrent.B;
        input->C = instance->inputstateDeviceCurrent.C;
        input->D = instance->inputstateDeviceCurrent.D;
        input->E = instance->inputstateDeviceCurrent.E;
        input->F = instance->inputstateDeviceCurrent.F;
        input->G = instance->inputstateDeviceCurrent.G;
        input->H = instance->inputstateDeviceCurrent.H;
        input->I = instance->inputstateDeviceCurrent.I;
        input->J = instance->inputstateDeviceCurrent.J;
        input->K = instance->inputstateDeviceCurrent.K;
        input->L = instance->inputstateDeviceCurrent.L;
        input->M = instance->inputstateDeviceCurrent.M;
        input->N = instance->inputstateDeviceCurrent.N;
        input->O = instance->inputstateDeviceCurrent.O;
        input->P = instance->inputstateDeviceCurrent.P;
        input->Q = instance->inputstateDeviceCurrent.Q;
        input->R = instance->inputstateDeviceCurrent.R;
        input->S = instance->inputstateDeviceCurrent.S;
        input->T = instance->inputstateDeviceCurrent.T;
        input->U = instance->inputstateDeviceCurrent.U;
        input->V = instance->inputstateDeviceCurrent.V;
        input->W = instance->inputstateDeviceCurrent.W;
        input->X = instance->inputstateDeviceCurrent.X;
        input->Y = instance->inputstateDeviceCurrent.Y;
        input->Z = instance->inputstateDeviceCurrent.Z;

        ReleaseMutex(instance->inputDeviceMutex);
    }

    void ParseInputStateGet()
    {
        while (instance->inputGetBufferSize > 0)
        {
            RAWINPUT* packet = (RAWINPUT*)instance->inputGetBuffer;
            UINT packetSize = packet->header.dwSize;

            if (packet->header.dwType == RIM_TYPEMOUSE)
            {
                USHORT buttonFlag = packet->data.mouse.usButtonFlags;
                RAWMOUSE mouse = packet->data.mouse;
                if (buttonFlag & RI_MOUSE_LEFT_BUTTON_DOWN) instance->inputstateDeviceCurrent.LMB = true;
                if (buttonFlag & RI_MOUSE_LEFT_BUTTON_UP) instance->inputstateDeviceCurrent.LMB = false;
                if (buttonFlag & RI_MOUSE_RIGHT_BUTTON_DOWN) instance->inputstateDeviceCurrent.RMB = true;
                if (buttonFlag & RI_MOUSE_RIGHT_BUTTON_UP) instance->inputstateDeviceCurrent.RMB = false;
                if (buttonFlag & RI_MOUSE_MIDDLE_BUTTON_DOWN) instance->inputstateDeviceCurrent.MB = true;
                if (buttonFlag & RI_MOUSE_MIDDLE_BUTTON_UP) instance->inputstateDeviceCurrent.MB = false;
                if (buttonFlag & RI_MOUSE_BUTTON_4_DOWN)  instance->inputstateDeviceCurrent.ME1 = true;
                if (buttonFlag & RI_MOUSE_BUTTON_4_UP)  instance->inputstateDeviceCurrent.ME1 = false;
                if (buttonFlag & RI_MOUSE_BUTTON_5_DOWN) instance->inputstateDeviceCurrent.ME2 = true;
                if (buttonFlag & RI_MOUSE_BUTTON_5_UP) instance->inputstateDeviceCurrent.ME2 = false;
                if (buttonFlag & RI_MOUSE_WHEEL)
                {
                    if (mouse.usButtonData > (USHRT_MAX / 2)) instance->inputstateDeviceCurrent.WHEEL += -(int)(USHRT_MAX - mouse.usButtonData);
                    else if (mouse.usButtonData > 0 && mouse.usButtonData < (USHRT_MAX / 2)) instance->inputstateDeviceCurrent.WHEEL += (int)mouse.usButtonData;
                }
                else
                {
                    instance->inputstateDeviceCurrent.WHEEL = 0;
                }
                if (mouse.lLastX != 0 || mouse.lLastY != 0)
                {
                    if (data.mouse.usFlags == MOUSE_MOVE_RELATIVE)
                    {
                        instance->inputstateDeviceCurrent.SETMOUSE = false;
                        instance->inputstateDeviceCurrent.MOUSEX += (int)mouse.lLastX;
                        instance->inputstateDeviceCurrent.MOUSEY += (int)mouse.lLastY;
                    }
                    else
                    {
                        instance->inputstateDeviceCurrent.SETMOUSE = true;
                        instance->inputstateDeviceCurrent.MOUSEX = (int)mouse.lLastX;
                        instance->inputstateDeviceCurrent.MOUSEY = (int)mouse.lLastY;
                    }
                }
                else
                {
                    instance->inputstateDeviceCurrent.SETMOUSE = false;
                    instance->inputstateDeviceCurrent.MOUSEY 0;
                    instance->inputstateDeviceCurrent.MOUSEY 0;
                }
            }
            else if (packet->header.dwType == RIM_TYPEKEYBOARD)
            {
                bool pressed = !(packet->data.keyboard.Flags & RI_KEY_BREAK);
                USHORT virtualKey = packet->data.keyboard.VKey;
                bool isExtendedShift = (packet->data.keyboard.Flags & RI_KEY_E0) || (packet->data.keyboard.Flags & RI_KEY_E1);

                if (virtualKey == VK_ESCAPE) RawInputGameInputCurrent.ESC = pressed;
                else if (virtualKey == VK_TAB) RawInputGameInputCurrent.TAB = pressed;
                else if (virtualKey == VK_LSHIFT && isExtendedShift) RawInputGameInputCurrent.LSHIFT = pressed;
                else if (virtualKey == VK_RSHIFT && isExtendedShift) RawInputGameInputCurrent.RSHIFT = pressed;
                else if (virtualKey == VK_CONTROL) RawInputGameInputCurrent.CTRL = pressed;
                else if (virtualKey == VK_MENU) RawInputGameInputCurrent.ALT = pressed;
                else if (virtualKey == VK_BACK) RawInputGameInputCurrent.BACK = pressed;
                else if (virtualKey == VK_RETURN) RawInputGameInputCurrent.RETURN = pressed;
                else if (virtualKey == VK_SPACE) RawInputGameInputCurrent.SPACE = pressed;
                else if (virtualKey == VK_UP) RawInputGameInputCurrent.AUP = pressed;
                else if (virtualKey == VK_RIGHT) RawInputGameInputCurrent.ARIGHT = pressed;
                else if (virtualKey == VK_DOWN) RawInputGameInputCurrent.ADOWN = pressed;
                else if (virtualKey == VK_LEFT) RawInputGameInputCurrent.ALEFT = pressed;
                else if (virtualKey == 0x30) RawInputGameInputCurrent.D0 = pressed;
                else if (virtualKey == 0x31) RawInputGameInputCurrent.D1 = pressed;
                else if (virtualKey == 0x32) RawInputGameInputCurrent.D2 = pressed;
                else if (virtualKey == 0x33) RawInputGameInputCurrent.D3 = pressed;
                else if (virtualKey == 0x34) RawInputGameInputCurrent.D4 = pressed;
                else if (virtualKey == 0x35) RawInputGameInputCurrent.D5 = pressed;
                else if (virtualKey == 0x36) RawInputGameInputCurrent.D6 = pressed;
                else if (virtualKey == 0x37) RawInputGameInputCurrent.D7 = pressed;
                else if (virtualKey == 0x38) RawInputGameInputCurrent.D8 = pressed;
                else if (virtualKey == 0x39) RawInputGameInputCurrent.D9 = pressed;
                else if (virtualKey == 0x41) RawInputGameInputCurrent.A = pressed;
                else if (virtualKey == 0x42) RawInputGameInputCurrent.B = pressed;
                else if (virtualKey == 0x43) RawInputGameInputCurrent.C = pressed;
                else if (virtualKey == 0x44) RawInputGameInputCurrent.D = pressed;
                else if (virtualKey == 0x45) RawInputGameInputCurrent.E = pressed;
                else if (virtualKey == 0x46) RawInputGameInputCurrent.F = pressed;
                else if (virtualKey == 0x47) RawInputGameInputCurrent.G = pressed;
                else if (virtualKey == 0x48) RawInputGameInputCurrent.H = pressed;
                else if (virtualKey == 0x49) RawInputGameInputCurrent.I = pressed;
                else if (virtualKey == 0x4A) RawInputGameInputCurrent.J = pressed;
                else if (virtualKey == 0x4B) RawInputGameInputCurrent.K = pressed;
                else if (virtualKey == 0x4C) RawInputGameInputCurrent.L = pressed;
                else if (virtualKey == 0x4D) RawInputGameInputCurrent.M = pressed;
                else if (virtualKey == 0x4E) RawInputGameInputCurrent.N = pressed;
                else if (virtualKey == 0x4F) RawInputGameInputCurrent.O = pressed;
                else if (virtualKey == 0x50) RawInputGameInputCurrent.P = pressed;
                else if (virtualKey == 0x51) RawInputGameInputCurrent.Q = pressed;
                else if (virtualKey == 0x52) RawInputGameInputCurrent.R = pressed;
                else if (virtualKey == 0x53) RawInputGameInputCurrent.S = pressed;
                else if (virtualKey == 0x54) RawInputGameInputCurrent.T = pressed;
                else if (virtualKey == 0x55) RawInputGameInputCurrent.U = pressed;
                else if (virtualKey == 0x56) RawInputGameInputCurrent.V = pressed;
                else if (virtualKey == 0x57) RawInputGameInputCurrent.W = pressed;
                else if (virtualKey == 0x58) RawInputGameInputCurrent.X = pressed;
                else if (virtualKey == 0x59) RawInputGameInputCurrent.Y = pressed;
                else if (virtualKey == 0x5A) RawInputGameInputCurrent.Z = pressed;
                else if (virtualKey == VK_NUMPAD0)RawInputGameInputCurrent.NUM0 = pressed;
                else if (virtualKey == VK_NUMPAD1) RawInputGameInputCurrent.NUM1 = pressed;
                else if (virtualKey == VK_NUMPAD2) RawInputGameInputCurrent.NUM2 = pressed;
                else if (virtualKey == VK_NUMPAD3) RawInputGameInputCurrent.NUM3 = pressed;
                else if (virtualKey == VK_NUMPAD4) RawInputGameInputCurrent.NUM4 = pressed;
                else if (virtualKey == VK_NUMPAD5) RawInputGameInputCurrent.NUM5 = pressed;
                else if (virtualKey == VK_NUMPAD6) RawInputGameInputCurrent.NUM6 = pressed;
                else if (virtualKey == VK_NUMPAD7) RawInputGameInputCurrent.NUM7 = pressed;
                else if (virtualKey == VK_NUMPAD8) RawInputGameInputCurrent.NUM8 = pressed;
                else if (virtualKey == VK_NUMPAD9) RawInputGameInputCurrent.NUM9 = pressed;
                else if (virtualKey == VK_DIVIDE) RawInputGameInputCurrent.NUMDIV = pressed;
                else if (virtualKey == VK_MULTIPLY) RawInputGameInputCurrent.NUMMUL = pressed;
                else if (virtualKey == VK_SUBTRACT) RawInputGameInputCurrent.NUMMIN = pressed;
                else if (virtualKey == VK_ADD) RawInputGameInputCurrent.NUMPLU = pressed;
                else if (virtualKey == VK_RETURN) RawInputGameInputCurrent.NUMRET = pressed;
                else if (virtualKey == VK_DELETE) RawInputGameInputCurrent.NUMDEL = pressed;
                else if (virtualKey == VK_F1) RawInputGameInputCurrent.F1 = pressed;
                else if (virtualKey == VK_F2) RawInputGameInputCurrent.F2 = pressed;
                else if (virtualKey == VK_F3) RawInputGameInputCurrent.F3 = pressed;
                else if (virtualKey == VK_F4) RawInputGameInputCurrent.F4 = pressed;
                else if (virtualKey == VK_F5) RawInputGameInputCurrent.F5 = pressed;
                else if (virtualKey == VK_F6) RawInputGameInputCurrent.F6 = pressed;
                else if (virtualKey == VK_F7) RawInputGameInputCurrent.F7 = pressed;
                else if (virtualKey == VK_F8) RawInputGameInputCurrent.F8 = pressed;
                else if (virtualKey == VK_F9) RawInputGameInputCurrent.F9 = pressed;
                else if (virtualKey == VK_F10) RawInputGameInputCurrent.F10 = pressed;
                else if (virtualKey == VK_F11) RawInputGameInputCurrent.F11 = pressed;
                else if (virtualKey == VK_F12) RawInputGameInputCurrent.F12 = pressed;
                else if (virtualKey == VK_OEM_COMMA) RawInputGameInputCurrent.COMMA = pressed;
                else if (virtualKey == VK_OEM_PERIOD) RawInputGameInputCurrent.DOT = pressed;
                else if (virtualKey == VK_OEM_PLUS) RawInputGameInputCurrent.PLUS = pressed;
                else if (virtualKey == VK_OEM_MINUS) RawInputGameInputCurrent.MINUS = pressed;
            }

            std::memmove(instance->inputGetBuffer, instance->inputGetBuffer + packetSize, instance->inputGetBufferSize - packetSize);
            instance->inputGetBufferSize -= packetSize;
        }
    }

};
UINT GetRawInputDataReal(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader);



// --- Functions ---
bool GetRawInputDataHookInit();
bool GetRawInputDataHookUninit();
bool IsRawInputDataHookActive();



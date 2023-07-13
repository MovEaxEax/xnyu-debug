#pragma once

// Global hook settings
typedef UINT(__stdcall* GetRawInputDataT)(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader);
GetRawInputDataT pGetRawInputData = nullptr;
typedef void(__stdcall* GetRawInputT)(BOOL TAS, GameInput* DST, std::string device);
GetRawInputT pGetRawInput = nullptr;

subhook::Hook RawInputSubhook;

void* RawInputOriginalAddress;
void* RawInputHookAddress;

bool GetRawInputRetrieveInformation = false;
bool GetRawInputSendInformation = false;
bool GetRawInputGetInformation = false;
bool RawInputDisableForGame = false;
bool GetRawInputTASMode = false;

GameInput RawInputGameInputCurrent;
GameInput RawInputGameInputLast;
GameInput* GetRawInputDSTAll = nullptr;
GameInput* GetRawInputDSTMouse = nullptr;
GameInput* GetRawInputDSTKeyboard = nullptr;
GameInput* GetRawInputDSTJoystick = nullptr;

// Specific settings
BYTE* RawInputBuffer = (BYTE*)malloc(65000);
UINT RawInputCommand = 0;
int RawInputBytesNeededBuffer = 0;
int RawInputBytesNeededHeader;

BYTE* RawInputSendBuffer = (BYTE*)malloc(65000);
UINT RawInputSendBufferBytesNeeded = 0;
UINT RawInputSendHeaderBytesNeeded = 0;
UINT RawInputSendDataBytesNeeded = 0;
UINT RawInputSendPacketAmount = 0;

HANDLE RawInputThreadMutex = CreateMutex(NULL, FALSE, NULL);

bool RawInputTASSyncStateMouseSet()
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    bool finished = TASSynchronizer.RawInputMouseSend || GetRawInputSendInformation;
    ReleaseMutex(RawInputThreadMutex);
    return finished;
}

bool RawInputTASSyncStateMouseGet()
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    bool finished = TASSynchronizer.RawInputMouseGet || GetRawInputGetInformation;
    ReleaseMutex(RawInputThreadMutex);
    return finished;
}

bool RawInputTASSyncStateKeyboardSet()
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    bool finished = TASSynchronizer.RawInputKeyboardSend || GetRawInputSendInformation;
    ReleaseMutex(RawInputThreadMutex);
    return finished;
}

bool RawInputTASSyncStateKeyboardGet()
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    bool finished = TASSynchronizer.RawInputKeyboardGet || GetRawInputGetInformation;
    ReleaseMutex(RawInputThreadMutex);
    return finished;
}

bool RawInputTASSyncStateJoystickSet()
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    bool finished = TASSynchronizer.RawInputJoystickSend || GetRawInputSendInformation;
    ReleaseMutex(RawInputThreadMutex);
    return finished;
}

bool RawInputTASSyncStateJoystickGet()
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    bool finished = TASSynchronizer.RawInputJoystickGet || GetRawInputGetInformation;
    ReleaseMutex(RawInputThreadMutex);
    return finished;
}

void RawInputTLockMutex()
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
}

void RawInputTReleaseMutex()
{
    ReleaseMutex(RawInputThreadMutex);
}

UINT __stdcall GetRawInputData_Hook(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    RawInputSubhook.Remove();
    
    UINT result = 0;

    if (GetRawInputSendInformation)
    {

        if (pData != NULL)
        {
            RawInputSendHeaderBytesNeeded = sizeof(RAWINPUTHEADER) * RawInputSendPacketAmount;
            
            if (uiCommand == RID_HEADER)
            {
                result = 0;
                std::memcpy(pcbSize, &RawInputSendHeaderBytesNeeded, sizeof(UINT));
            }
            if (uiCommand == RID_INPUT)
            {
                RAWINPUT* packet;
                UINT offset = 0;
                UINT cpSize = 0;
                std::memcpy(&pcbSize, pcbSize, sizeof(UINT));
                while (RawInputSendBufferBytesNeeded > 20 && cpSize > 20)
                {
                    packet = (RAWINPUT*)(RawInputSendBuffer + offset);
                    UINT packetSize = packet->header.dwSize;
                    if (packetSize <= 0 || packetSize >= 4096) break;
                    std::memcpy((BYTE*)pData + offset, packet, packetSize);
                    offset += packetSize;
                    cpSize -= packetSize;
                    RawInputSendBufferBytesNeeded -= packetSize;
                }
                if (offset > 0) std::memset(RawInputSendBuffer, 0x00, offset);
                if (RawInputSendBufferBytesNeeded > 0 && offset > 0) std::memcpy(RawInputSendBuffer, RawInputSendBuffer + offset, RawInputSendBufferBytesNeeded);
                result = offset;

                GetRawInputSendInformation = false;
                TASSynchronizer.RawInputKeyboardSend = false;
                TASSynchronizer.RawInputMouseSend = false;
                TASSynchronizer.RawInputJoystickSend = false;
            }
        }
        else
        {
            result = RawInputSendBufferBytesNeeded;
        }

    }
    else
    {
        result = pGetRawInputData(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);
        if (pData != NULL && result > 0 && result < 65000)
        {
            // Set and copy old states
            std::memcpy(&RawInputGameInputLast, &RawInputGameInputCurrent, sizeof(GameInput));

            // Get data
            if (uiCommand == RID_INPUT)
            {
                int BytesNeededRelative = static_cast<int>(result);
                if (BytesNeededRelative > 0)
                {
                    UINT packetSize = ((RAWINPUT*)pData)->header.dwSize;
                    std::memcpy(RawInputBuffer + RawInputBytesNeededBuffer, pData, packetSize);
                    RawInputBytesNeededBuffer += packetSize;
                }
            }
        }

        bool demand = false;
        if (!GlobalSettings.config_rawinput_demand)
        {
            if (GetRawInputGetInformation)
            {
                demand = true;
                if (InputDriverMouseGet == InputDriverz::RAW1NPUT)
                {
                    pGetRawInput(false, GetRawInputDSTMouse, "mouse");
                }
                if (InputDriverKeyboardGet == InputDriverz::RAW1NPUT)
                {
                    pGetRawInput(false, GetRawInputDSTKeyboard, "keyboard");
                }
                if (InputDriverJoystickGet == InputDriverz::RAW1NPUT)
                {
                    pGetRawInput(false, GetRawInputDSTJoystick, "joystick");
                }

                GetRawInputGetInformation = false;
            }
        }

        if (RawInputDisableForGame && !demand)
        {
            result = 0;
            UINT fakeSize = 0;
            if (!pData == NULL)
            {
                // Probably handling for valid buffer?
            }
            //std::memcpy(pcbSize, &fakeSize, sizeof(UINT));
        }
    }

    if (sizeof(void*) == 8) RawInputSubhook.Install(RawInputOriginalAddress, RawInputHookAddress, subhook::HookFlags::HookFlag64BitOffset);
    if (sizeof(void*) == 4) RawInputSubhook.Install(RawInputOriginalAddress, RawInputHookAddress);

    ReleaseMutex(RawInputThreadMutex);
    return result;
}

BOOL RawInputHookUninit()
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    RawInputSubhook.Remove();
    ReleaseMutex(RawInputThreadMutex);
    return true;
}

void InitPlayRawInputTAS()
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    GetRawInputSendInformation = true;
    RawInputDisableForGame = true;
    RawInputBytesNeededBuffer = 0;
    RawInputSendBufferBytesNeeded = 0;
    std::memset(&RawInputGameInputCurrent, 0x00, sizeof(GameInput));
    std::memset(&RawInputGameInputLast, 0x00, sizeof(GameInput));
    std::memset(RawInputBuffer, 0x00, 65000);
    std::memset(RawInputSendBuffer, 0x00, 65000);
    ReleaseMutex(RawInputThreadMutex);
}

void UninitPlayRawInputTAS()
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    GetRawInputSendInformation = false;
    RawInputDisableForGame = false;
    RawInputBytesNeededBuffer = 0;
    RawInputSendBufferBytesNeeded = 0;
    std::memset(&RawInputGameInputCurrent, 0x00, sizeof(GameInput));
    std::memset(&RawInputGameInputLast, 0x00, sizeof(GameInput));
    std::memset(RawInputBuffer, 0x00, 65000);
    std::memset(RawInputSendBuffer, 0x00, 65000);
    ReleaseMutex(RawInputThreadMutex);
}

void InitRecordRawInputTAS()
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    if (TASRecordFrameByFrameInputTrigger)
    {
        GetRawInputSendInformation = true;
        RawInputDisableForGame = true;
    }
    RawInputBytesNeededBuffer = 0;
    RawInputSendBufferBytesNeeded = 0;
    std::memset(&RawInputGameInputCurrent, 0x00, sizeof(GameInput));
    std::memset(&RawInputGameInputLast, 0x00, sizeof(GameInput));
    std::memset(RawInputBuffer, 0x00, 65000);
    std::memset(RawInputSendBuffer, 0x00, 65000);
    ReleaseMutex(RawInputThreadMutex);
}

void UninitRecordRawInputTAS()
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    if (TASRecordFrameByFrameInputTrigger)
    {
        GetRawInputSendInformation = false;
        RawInputDisableForGame = false;
    }
    RawInputBytesNeededBuffer = 0;
    RawInputSendBufferBytesNeeded = 0;
    std::memset(&RawInputGameInputCurrent, 0x00, sizeof(GameInput));
    std::memset(&RawInputGameInputLast, 0x00, sizeof(GameInput));
    std::memset(RawInputBuffer, 0x00, 65000);
    std::memset(RawInputSendBuffer, 0x00, 65000);
    ReleaseMutex(RawInputThreadMutex);
}

void __stdcall GetRawInput(BOOL TAS, GameInput* DST, std::string device)
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    if (!GlobalSettings.config_rawinput_demand)
    {
        if (TAS)
        {
            if (device == "all") GetRawInputDSTAll = DST;
            else if (device == "mouse") GetRawInputDSTMouse = DST;
            else if (device == "keyboard") GetRawInputDSTKeyboard = DST;
            else if (device == "joystick") GetRawInputDSTJoystick = DST;

            GetRawInputGetInformation = true;
            ReleaseMutex(RawInputThreadMutex);
            return;
        }
    }

    if (InputDriverMouseGet == InputDriverz::RAW1NPUT)
    {
        RawInputGameInputCurrent.MOUSEX = 0;
        RawInputGameInputCurrent.MOUSEY = 0;
        RawInputGameInputCurrent.WHEEL = 0;
    }
    if (RawInputBytesNeededBuffer > 0)
    {
        BYTE* restPackets = (BYTE*)malloc(3000);
        int restpacketsOffsets = 0;
        RAWINPUT* packet = (RAWINPUT*)RawInputBuffer;
        UINT offset = 0;
        int index = 0;

        while (RawInputBytesNeededBuffer > 20)
        {
            UINT packetSize = packet->header.dwSize;
            index++;
            if (packetSize <= 0 || packetSize >= 4096) break;
            offset += packetSize;
            RawInputBytesNeededBuffer -= packetSize;
            // Mouse input
            if (packet->header.dwType == RIM_TYPEMOUSE)
            {
                if (InputDriverMouseGet == InputDriverz::RAW1NPUT)
                {
                    if (device == "all" || device == "mouse")
                    {
                        USHORT buttonFlag = packet->data.mouse.usButtonFlags;
                        RAWMOUSE mouse = packet->data.mouse;
                        if (buttonFlag & RI_MOUSE_LEFT_BUTTON_DOWN) RawInputGameInputCurrent.LMB = true;
                        if (buttonFlag & RI_MOUSE_LEFT_BUTTON_UP) RawInputGameInputCurrent.LMB = false;
                        if (buttonFlag & RI_MOUSE_RIGHT_BUTTON_DOWN) RawInputGameInputCurrent.RMB = true;
                        if (buttonFlag & RI_MOUSE_RIGHT_BUTTON_UP) RawInputGameInputCurrent.RMB = false;
                        if (buttonFlag & RI_MOUSE_MIDDLE_BUTTON_DOWN) RawInputGameInputCurrent.MB = true;
                        if (buttonFlag & RI_MOUSE_MIDDLE_BUTTON_UP) RawInputGameInputCurrent.MB = false;
                        if (buttonFlag & RI_MOUSE_BUTTON_4_DOWN)  RawInputGameInputCurrent.ME1 = true;
                        if (buttonFlag & RI_MOUSE_BUTTON_4_UP)  RawInputGameInputCurrent.ME1 = false;
                        if (buttonFlag & RI_MOUSE_BUTTON_5_DOWN) RawInputGameInputCurrent.ME2 = true;
                        if (buttonFlag & RI_MOUSE_BUTTON_5_UP) RawInputGameInputCurrent.ME2 = false;
                        if (buttonFlag & RI_MOUSE_WHEEL)
                        {
                            if (mouse.usButtonData > (USHRT_MAX / 2)) RawInputGameInputCurrent.WHEEL += -(int)(USHRT_MAX - mouse.usButtonData);
                            if (mouse.usButtonData > 0 && mouse.usButtonData < (USHRT_MAX / 2)) RawInputGameInputCurrent.WHEEL += (int)mouse.usButtonData;
                        }
                        RawInputGameInputCurrent.MOUSEX += mouse.lLastX;
                        RawInputGameInputCurrent.MOUSEY += mouse.lLastY;
                    }
                    else
                    {
                        std::memcpy(restPackets + restpacketsOffsets, packet, packetSize);
                        restpacketsOffsets += packetSize;
                    }
                }
            }

            // Keyboard input
            if (packet->header.dwType == RIM_TYPEKEYBOARD)
            {
                if (InputDriverKeyboardGet == InputDriverz::RAW1NPUT)
                {
                    if (device == "all" || device == "keyboard")
                    {
                        if (!(packet->data.keyboard.Flags & RI_KEY_BREAK))
                        {
                            USHORT virtualKey = packet->data.keyboard.VKey;
                            bool isExtendedShift = (packet->data.keyboard.Flags & RI_KEY_E0) || (packet->data.keyboard.Flags & RI_KEY_E1);

                            if (virtualKey == VK_ESCAPE) RawInputGameInputCurrent.ESC = true;
                            if (virtualKey == VK_TAB) RawInputGameInputCurrent.TAB = true;
                            if (virtualKey == VK_LSHIFT && isExtendedShift) RawInputGameInputCurrent.LSHIFT = true;
                            if (virtualKey == VK_RSHIFT && isExtendedShift) RawInputGameInputCurrent.RSHIFT = true;
                            if (virtualKey == VK_CONTROL) RawInputGameInputCurrent.CTRL = true;
                            if (virtualKey == VK_MENU) RawInputGameInputCurrent.ALT = true;
                            if (virtualKey == VK_BACK) RawInputGameInputCurrent.BACK = true;
                            if (virtualKey == VK_RETURN) RawInputGameInputCurrent.RETURN = true;
                            if (virtualKey == VK_SPACE) RawInputGameInputCurrent.SPACE = true;
                            if (virtualKey == VK_UP) RawInputGameInputCurrent.AUP = true;
                            if (virtualKey == VK_RIGHT) RawInputGameInputCurrent.ARIGHT = true;
                            if (virtualKey == VK_DOWN) RawInputGameInputCurrent.ADOWN = true;
                            if (virtualKey == VK_LEFT) RawInputGameInputCurrent.ALEFT = true;
                            if (virtualKey == 0x30) RawInputGameInputCurrent.D0 = true;
                            if (virtualKey == 0x31) RawInputGameInputCurrent.D1 = true;
                            if (virtualKey == 0x32) RawInputGameInputCurrent.D2 = true;
                            if (virtualKey == 0x33) RawInputGameInputCurrent.D3 = true;
                            if (virtualKey == 0x34) RawInputGameInputCurrent.D4 = true;
                            if (virtualKey == 0x35) RawInputGameInputCurrent.D5 = true;
                            if (virtualKey == 0x36) RawInputGameInputCurrent.D6 = true;
                            if (virtualKey == 0x37) RawInputGameInputCurrent.D7 = true;
                            if (virtualKey == 0x38) RawInputGameInputCurrent.D8 = true;
                            if (virtualKey == 0x39) RawInputGameInputCurrent.D9 = true;
                            if (virtualKey == 0x41) RawInputGameInputCurrent.A = true;
                            if (virtualKey == 0x42) RawInputGameInputCurrent.B = true;
                            if (virtualKey == 0x43) RawInputGameInputCurrent.C = true;
                            if (virtualKey == 0x44) RawInputGameInputCurrent.D = true;
                            if (virtualKey == 0x45) RawInputGameInputCurrent.E = true;
                            if (virtualKey == 0x46) RawInputGameInputCurrent.F = true;
                            if (virtualKey == 0x47) RawInputGameInputCurrent.G = true;
                            if (virtualKey == 0x48) RawInputGameInputCurrent.H = true;
                            if (virtualKey == 0x49) RawInputGameInputCurrent.I = true;
                            if (virtualKey == 0x4A) RawInputGameInputCurrent.J = true;
                            if (virtualKey == 0x4B) RawInputGameInputCurrent.K = true;
                            if (virtualKey == 0x4C) RawInputGameInputCurrent.L = true;
                            if (virtualKey == 0x4D) RawInputGameInputCurrent.M = true;
                            if (virtualKey == 0x4E) RawInputGameInputCurrent.N = true;
                            if (virtualKey == 0x4F) RawInputGameInputCurrent.O = true;
                            if (virtualKey == 0x50) RawInputGameInputCurrent.P = true;
                            if (virtualKey == 0x51) RawInputGameInputCurrent.Q = true;
                            if (virtualKey == 0x52) RawInputGameInputCurrent.R = true;
                            if (virtualKey == 0x53) RawInputGameInputCurrent.S = true;
                            if (virtualKey == 0x54) RawInputGameInputCurrent.T = true;
                            if (virtualKey == 0x55) RawInputGameInputCurrent.U = true;
                            if (virtualKey == 0x56) RawInputGameInputCurrent.V = true;
                            if (virtualKey == 0x57) RawInputGameInputCurrent.W = true;
                            if (virtualKey == 0x58) RawInputGameInputCurrent.X = true;
                            if (virtualKey == 0x59) RawInputGameInputCurrent.Y = true;
                            if (virtualKey == 0x5A) RawInputGameInputCurrent.Z = true;
                            if (virtualKey == VK_NUMPAD0)RawInputGameInputCurrent.NUM0 = true;
                            if (virtualKey == VK_NUMPAD1) RawInputGameInputCurrent.NUM1 = true;
                            if (virtualKey == VK_NUMPAD2) RawInputGameInputCurrent.NUM2 = true;
                            if (virtualKey == VK_NUMPAD3) RawInputGameInputCurrent.NUM3 = true;
                            if (virtualKey == VK_NUMPAD4) RawInputGameInputCurrent.NUM4 = true;
                            if (virtualKey == VK_NUMPAD5) RawInputGameInputCurrent.NUM5 = true;
                            if (virtualKey == VK_NUMPAD6) RawInputGameInputCurrent.NUM6 = true;
                            if (virtualKey == VK_NUMPAD7) RawInputGameInputCurrent.NUM7 = true;
                            if (virtualKey == VK_NUMPAD8) RawInputGameInputCurrent.NUM8 = true;
                            if (virtualKey == VK_NUMPAD9) RawInputGameInputCurrent.NUM9 = true;
                            if (virtualKey == VK_DIVIDE) RawInputGameInputCurrent.NUMDIV = true;
                            if (virtualKey == VK_MULTIPLY) RawInputGameInputCurrent.NUMMUL = true;
                            if (virtualKey == VK_SUBTRACT) RawInputGameInputCurrent.NUMMIN = true;
                            if (virtualKey == VK_ADD) RawInputGameInputCurrent.NUMPLU = true;
                            if (virtualKey == VK_RETURN) RawInputGameInputCurrent.NUMRET = true;
                            if (virtualKey == VK_DELETE) RawInputGameInputCurrent.NUMDEL = true;
                            if (virtualKey == VK_F1) RawInputGameInputCurrent.F1 = true;
                            if (virtualKey == VK_F2) RawInputGameInputCurrent.F2 = true;
                            if (virtualKey == VK_F3) RawInputGameInputCurrent.F3 = true;
                            if (virtualKey == VK_F4) RawInputGameInputCurrent.F4 = true;
                            if (virtualKey == VK_F5) RawInputGameInputCurrent.F5 = true;
                            if (virtualKey == VK_F6) RawInputGameInputCurrent.F6 = true;
                            if (virtualKey == VK_F7) RawInputGameInputCurrent.F7 = true;
                            if (virtualKey == VK_F8) RawInputGameInputCurrent.F8 = true;
                            if (virtualKey == VK_F9) RawInputGameInputCurrent.F9 = true;
                            if (virtualKey == VK_F10) RawInputGameInputCurrent.F10 = true;
                            if (virtualKey == VK_F11) RawInputGameInputCurrent.F11 = true;
                            if (virtualKey == VK_F12) RawInputGameInputCurrent.F12 = true;
                            if (virtualKey == VK_OEM_COMMA) RawInputGameInputCurrent.COMMA = true;
                            if (virtualKey == VK_OEM_PERIOD) RawInputGameInputCurrent.DOT = true;
                            if (virtualKey == VK_OEM_PLUS) RawInputGameInputCurrent.PLUS = true;
                            if (virtualKey == VK_OEM_MINUS) RawInputGameInputCurrent.MINUS = true;
                        }

                        if (packet->data.keyboard.Flags & RI_KEY_BREAK)
                        {
                            USHORT virtualKey = packet->data.keyboard.VKey;
                            bool isExtendedShift = (packet->data.keyboard.Flags & RI_KEY_E0) || (packet->data.keyboard.Flags & RI_KEY_E1);

                            if (virtualKey == VK_ESCAPE) RawInputGameInputCurrent.ESC = false;
                            if (virtualKey == VK_TAB) RawInputGameInputCurrent.TAB = false;
                            if (virtualKey == VK_LSHIFT && isExtendedShift) RawInputGameInputCurrent.LSHIFT = false;
                            if (virtualKey == VK_RSHIFT && isExtendedShift) RawInputGameInputCurrent.RSHIFT = false;
                            if (virtualKey == VK_CONTROL) RawInputGameInputCurrent.CTRL = false;
                            if (virtualKey == VK_MENU) RawInputGameInputCurrent.ALT = false;
                            if (virtualKey == VK_BACK) RawInputGameInputCurrent.BACK = false;
                            if (virtualKey == VK_RETURN) RawInputGameInputCurrent.RETURN = false;
                            if (virtualKey == VK_SPACE) RawInputGameInputCurrent.SPACE = false;
                            if (virtualKey == VK_UP) RawInputGameInputCurrent.AUP = false;
                            if (virtualKey == VK_RIGHT) RawInputGameInputCurrent.ARIGHT = false;
                            if (virtualKey == VK_DOWN) RawInputGameInputCurrent.ADOWN = false;
                            if (virtualKey == VK_LEFT) RawInputGameInputCurrent.ALEFT = false;
                            if (virtualKey == 0x30) RawInputGameInputCurrent.D0 = false;
                            if (virtualKey == 0x31) RawInputGameInputCurrent.D1 = false;
                            if (virtualKey == 0x32) RawInputGameInputCurrent.D2 = false;
                            if (virtualKey == 0x33) RawInputGameInputCurrent.D3 = false;
                            if (virtualKey == 0x34) RawInputGameInputCurrent.D4 = false;
                            if (virtualKey == 0x35) RawInputGameInputCurrent.D5 = false;
                            if (virtualKey == 0x36) RawInputGameInputCurrent.D6 = false;
                            if (virtualKey == 0x37) RawInputGameInputCurrent.D7 = false;
                            if (virtualKey == 0x38) RawInputGameInputCurrent.D8 = false;
                            if (virtualKey == 0x39) RawInputGameInputCurrent.D9 = false;
                            if (virtualKey == 0x41) RawInputGameInputCurrent.A = false;
                            if (virtualKey == 0x42) RawInputGameInputCurrent.B = false;
                            if (virtualKey == 0x43) RawInputGameInputCurrent.C = false;
                            if (virtualKey == 0x44) RawInputGameInputCurrent.D = false;
                            if (virtualKey == 0x45) RawInputGameInputCurrent.E = false;
                            if (virtualKey == 0x46) RawInputGameInputCurrent.F = false;
                            if (virtualKey == 0x47) RawInputGameInputCurrent.G = false;
                            if (virtualKey == 0x48) RawInputGameInputCurrent.H = false;
                            if (virtualKey == 0x49) RawInputGameInputCurrent.I = false;
                            if (virtualKey == 0x4A) RawInputGameInputCurrent.J = false;
                            if (virtualKey == 0x4B) RawInputGameInputCurrent.K = false;
                            if (virtualKey == 0x4C) RawInputGameInputCurrent.L = false;
                            if (virtualKey == 0x4D) RawInputGameInputCurrent.M = false;
                            if (virtualKey == 0x4E) RawInputGameInputCurrent.N = false;
                            if (virtualKey == 0x4F) RawInputGameInputCurrent.O = false;
                            if (virtualKey == 0x50) RawInputGameInputCurrent.P = false;
                            if (virtualKey == 0x51) RawInputGameInputCurrent.Q = false;
                            if (virtualKey == 0x52) RawInputGameInputCurrent.R = false;
                            if (virtualKey == 0x53) RawInputGameInputCurrent.S = false;
                            if (virtualKey == 0x54) RawInputGameInputCurrent.T = false;
                            if (virtualKey == 0x55) RawInputGameInputCurrent.U = false;
                            if (virtualKey == 0x56) RawInputGameInputCurrent.V = false;
                            if (virtualKey == 0x57) RawInputGameInputCurrent.W = false;
                            if (virtualKey == 0x58) RawInputGameInputCurrent.X = false;
                            if (virtualKey == 0x59) RawInputGameInputCurrent.Y = false;
                            if (virtualKey == 0x5A) RawInputGameInputCurrent.Z = false;
                            if (virtualKey == VK_NUMPAD0) RawInputGameInputCurrent.NUM0 = false;
                            if (virtualKey == VK_NUMPAD1) RawInputGameInputCurrent.NUM1 = false;
                            if (virtualKey == VK_NUMPAD2) RawInputGameInputCurrent.NUM2 = false;
                            if (virtualKey == VK_NUMPAD3) RawInputGameInputCurrent.NUM3 = false;
                            if (virtualKey == VK_NUMPAD4) RawInputGameInputCurrent.NUM4 = false;
                            if (virtualKey == VK_NUMPAD5) RawInputGameInputCurrent.NUM5 = false;
                            if (virtualKey == VK_NUMPAD6) RawInputGameInputCurrent.NUM6 = false;
                            if (virtualKey == VK_NUMPAD7) RawInputGameInputCurrent.NUM7 = false;
                            if (virtualKey == VK_NUMPAD8) RawInputGameInputCurrent.NUM8 = false;
                            if (virtualKey == VK_NUMPAD9) RawInputGameInputCurrent.NUM9 = false;
                            if (virtualKey == VK_DIVIDE) RawInputGameInputCurrent.NUMDIV = false;
                            if (virtualKey == VK_MULTIPLY) RawInputGameInputCurrent.NUMMUL = false;
                            if (virtualKey == VK_SUBTRACT) RawInputGameInputCurrent.NUMMIN = false;
                            if (virtualKey == VK_ADD) RawInputGameInputCurrent.NUMPLU = false;
                            if (virtualKey == VK_RETURN) RawInputGameInputCurrent.NUMRET = false;
                            if (virtualKey == VK_DELETE) RawInputGameInputCurrent.NUMDEL = false;
                            if (virtualKey == VK_F1) RawInputGameInputCurrent.F1 = false;
                            if (virtualKey == VK_F2) RawInputGameInputCurrent.F2 = false;
                            if (virtualKey == VK_F3) RawInputGameInputCurrent.F3 = false;
                            if (virtualKey == VK_F4) RawInputGameInputCurrent.F4 = false;
                            if (virtualKey == VK_F5) RawInputGameInputCurrent.F5 = false;
                            if (virtualKey == VK_F6) RawInputGameInputCurrent.F6 = false;
                            if (virtualKey == VK_F7) RawInputGameInputCurrent.F7 = false;
                            if (virtualKey == VK_F8) RawInputGameInputCurrent.F8 = false;
                            if (virtualKey == VK_F9) RawInputGameInputCurrent.F9 = false;
                            if (virtualKey == VK_F10) RawInputGameInputCurrent.F10 = false;
                            if (virtualKey == VK_F11) RawInputGameInputCurrent.F11 = false;
                            if (virtualKey == VK_F12) RawInputGameInputCurrent.F12 = false;
                            if (virtualKey == VK_OEM_COMMA) RawInputGameInputCurrent.COMMA = false;
                            if (virtualKey == VK_OEM_PERIOD) RawInputGameInputCurrent.DOT = false;
                            if (virtualKey == VK_OEM_PLUS) RawInputGameInputCurrent.PLUS = false;
                            if (virtualKey == VK_OEM_MINUS) RawInputGameInputCurrent.MINUS = false;
                        }
                    }
                    else
                    {
                        std::memcpy(restPackets + restpacketsOffsets, packet, packetSize);
                        restpacketsOffsets += packetSize;
                    }
                }

            }

            packet = (RAWINPUT*)(RawInputBuffer + offset);
        }

        std::memset(RawInputBuffer, 0x00, offset);
        RawInputBytesNeededBuffer = 0;

        if (restpacketsOffsets > 0)
        {
            RawInputBytesNeededBuffer = restpacketsOffsets;
            std::memcpy(RawInputBuffer, restPackets, restpacketsOffsets);
        }
    }

    if (!GlobalSettings.config_rawinput_demand)
    {
        if (device == "all") std::memcpy(GetRawInputDSTAll, &RawInputGameInputCurrent, sizeof(GameInput));
        else if (device == "mouse") std::memcpy(GetRawInputDSTMouse, &RawInputGameInputCurrent, sizeof(GameInput));
        else if (device == "keyboard") std::memcpy(GetRawInputDSTKeyboard, &RawInputGameInputCurrent, sizeof(GameInput));
        else if (device == "joystick") std::memcpy(GetRawInputDSTJoystick, &RawInputGameInputCurrent, sizeof(GameInput));
    }
    else
    {
        std::memcpy(DST, &RawInputGameInputCurrent, sizeof(GameInput));
        GetRawInputGetInformation = false;
    }

    if (device == "all")
    {
        TASSynchronizer.RawInputMouseGet = false;
        TASSynchronizer.RawInputKeyboardGet = false;
        TASSynchronizer.RawInputJoystickGet = false;
    }
    else if (device == "mouse") TASSynchronizer.RawInputMouseGet = false;
    else if (device == "keyboard") TASSynchronizer.RawInputKeyboardGet = false;
    else if (device == "joystick") TASSynchronizer.RawInputJoystickGet = false;
    ReleaseMutex(RawInputThreadMutex);
}

void SetRawInput(GameInput RawInputGameInput, BOOL TAS)
{
    WaitForSingleObject(RawInputThreadMutex, INFINITE);
    GetRawInputSendInformation = true;

    if (RawInputSendBufferBytesNeeded > 60000)
    {
        std::memset(RawInputSendBuffer, 0x00, 65000);
        RawInputSendBufferBytesNeeded = 0;
    }
    std::memcpy(&RawInputGameInputCurrent, &RawInputGameInput, sizeof(GameInput));

    RAWINPUT packet;

    if (InputDriverMouseSet == InputDriverz::RAW1NPUT)
    {
        packet = RAWINPUT();
        if (RawInputGameInput.LMB || RawInputGameInputLast.LMB)
        {
            packet.header.dwType = RIM_TYPEMOUSE;
            packet.data.mouse.usButtonFlags |= (RawInputGameInput.LMB ? RI_MOUSE_LEFT_BUTTON_DOWN : RI_MOUSE_LEFT_BUTTON_UP);
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.RMB || RawInputGameInputLast.RMB)
        {
            packet.header.dwType = RIM_TYPEMOUSE;
            packet.data.mouse.usButtonFlags |= (RawInputGameInput.RMB ? RI_MOUSE_RIGHT_BUTTON_DOWN : RI_MOUSE_RIGHT_BUTTON_UP);
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.MB || RawInputGameInputLast.MB)
        {
            packet.header.dwType = RIM_TYPEMOUSE;
            packet.data.mouse.usButtonFlags |= (RawInputGameInput.MB ? RI_MOUSE_MIDDLE_BUTTON_DOWN : RI_MOUSE_MIDDLE_BUTTON_UP);
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.ME1 || RawInputGameInputLast.ME1)
        {
            packet.header.dwType = RIM_TYPEMOUSE;
            packet.data.mouse.usButtonFlags |= (RawInputGameInput.ME1 ? RI_MOUSE_BUTTON_4_DOWN : RI_MOUSE_BUTTON_4_UP);
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.ME2 || RawInputGameInputLast.ME2)
        {
            packet.header.dwType = RIM_TYPEMOUSE;
            packet.data.mouse.usButtonFlags |= (RawInputGameInput.ME2 ? RI_MOUSE_BUTTON_5_DOWN : RI_MOUSE_BUTTON_5_UP);
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.WHEEL != 0)
        {
            packet.header.dwType = RIM_TYPEMOUSE;
            packet.data.mouse.usButtonFlags |= RI_MOUSE_WHEEL;
            if (RawInputGameInput.WHEEL > 0) packet.data.mouse.usButtonData = (USHORT)RawInputGameInput.WHEEL;
            if (RawInputGameInput.WHEEL < 0) packet.data.mouse.usButtonData = (USHORT)(USHRT_MAX - RawInputGameInput.WHEEL);
            packet.data.mouse.usButtonData = static_cast<USHORT>(RawInputGameInput.WHEEL);
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.MOUSEX != 0)
        {
            packet.header.dwType = RIM_TYPEMOUSE;
            packet.data.mouse.lLastX = (LONG)RawInputGameInput.MOUSEX;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.MOUSEY != 0)
        {
            packet.header.dwType = RIM_TYPEMOUSE;
            packet.data.mouse.lLastY = (LONG)RawInputGameInput.MOUSEY;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }
    }

    if (InputDriverKeyboardSet == InputDriverz::RAW1NPUT)
    {
        packet = RAWINPUT();
        if (RawInputGameInput.ESC || RawInputGameInputLast.ESC)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.ESC ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_ESCAPE;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.TAB || RawInputGameInputLast.TAB)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.TAB ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_TAB;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.LSHIFT || RawInputGameInputLast.LSHIFT)
        {
            packet.data.keyboard.Flags |= RI_KEY_E0;
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.LSHIFT ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_LSHIFT;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.RSHIFT || RawInputGameInputLast.RSHIFT)
        {
            packet.data.keyboard.Flags |= RI_KEY_E1;
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.RSHIFT ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_RSHIFT;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.CTRL || RawInputGameInputLast.CTRL)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.CTRL ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_CONTROL;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.ALT || RawInputGameInputLast.ALT)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.ALT ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_MENU;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.BACK || RawInputGameInputLast.BACK)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.BACK ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_BACK;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.RETURN || RawInputGameInputLast.RETURN)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.RETURN ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_RETURN;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.SPACE || RawInputGameInputLast.SPACE)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.SPACE ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_SPACE;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.AUP || RawInputGameInputLast.AUP)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.AUP ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_UP;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.ARIGHT || RawInputGameInputLast.ARIGHT)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.ARIGHT ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_RIGHT;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.ADOWN || RawInputGameInputLast.ADOWN)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.ADOWN ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_DOWN;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.ALEFT || RawInputGameInputLast.ALEFT)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.ALEFT ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = VK_LEFT;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.D0 || RawInputGameInputLast.D0)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.D0 ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x30;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }


        packet = RAWINPUT();
        if (RawInputGameInput.D1 || RawInputGameInputLast.D1)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.D1 ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x31;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.D2 || RawInputGameInputLast.D2)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.D2 ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x32;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.D3 || RawInputGameInputLast.D3)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.D3 ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x33;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.D4 || RawInputGameInputLast.D4)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.D4 ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x34;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.D5 || RawInputGameInputLast.D5)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.D5 ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x35;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.D6 || RawInputGameInputLast.D6)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.D6 ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x36;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.D7 || RawInputGameInputLast.D7)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.D7 ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x37;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.D8 || RawInputGameInputLast.D8)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.D8 ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x38;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.D9 || RawInputGameInputLast.D9)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.D9 ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x39;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.A || RawInputGameInputLast.A)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.A ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x41;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.B || RawInputGameInputLast.B)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.B ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x42;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.C || RawInputGameInputLast.C)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.C ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x43;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.D || RawInputGameInputLast.D)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.D ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x44;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.E || RawInputGameInputLast.E)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.E ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x45;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.F || RawInputGameInputLast.F)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.F ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x46;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.G || RawInputGameInputLast.G)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.G ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x47;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.H || RawInputGameInputLast.H)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.H ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x48;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.I || RawInputGameInputLast.I)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.I ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x49;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.J || RawInputGameInputLast.J)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.J ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x4A;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.K || RawInputGameInputLast.K)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.K ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x4B;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.L || RawInputGameInputLast.L)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.L ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x4C;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.M || RawInputGameInputLast.M)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.M ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x4D;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.N || RawInputGameInputLast.N)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.N ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x4E;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.O || RawInputGameInputLast.O)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.O ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x4F;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.P || RawInputGameInputLast.P)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.P ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x50;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.Q || RawInputGameInputLast.Q)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.Q ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x51;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.R || RawInputGameInputLast.R)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.R ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x52;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.S || RawInputGameInputLast.S)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.S ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x53;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
        }

        packet = RAWINPUT();
        if (RawInputGameInput.T || RawInputGameInputLast.T)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.T ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x54;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.U || RawInputGameInputLast.U)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.U ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x55;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.V || RawInputGameInputLast.V)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.V ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x56;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.W || RawInputGameInputLast.W)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.W ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x57;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
        }

        packet = RAWINPUT();
        if (RawInputGameInput.X || RawInputGameInputLast.X)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.X ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x58;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.Y || RawInputGameInputLast.Y)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.Y ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x59;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }

        packet = RAWINPUT();
        if (RawInputGameInput.Z || RawInputGameInputLast.Z)
        {
            packet.header.dwType = RIM_TYPEKEYBOARD;
            packet.data.keyboard.Flags |= (RawInputGameInput.Z ? RI_KEY_MAKE : RI_KEY_BREAK);
            packet.data.keyboard.VKey = 0x5A;
            packet.header.dwSize = sizeof(packet); std::memcpy(RawInputSendBuffer + RawInputSendBufferBytesNeeded, &packet, sizeof(packet)); RawInputSendBufferBytesNeeded += sizeof(packet);
            RawInputSendPacketAmount++;
        }
    }

    RawInputSendHeaderBytesNeeded = sizeof(RAWINPUTHEADER) * RawInputSendPacketAmount;

    std::memcpy(&RawInputGameInputLast, &RawInputGameInput, sizeof(GameInput));
    ReleaseMutex(RawInputThreadMutex);
}


BOOL RawInputHookInit()
{
    HMODULE RawInputDllHandle = GetModuleHandleA("User32.dll");
    if (RawInputDllHandle == NULL) return false;

    pGetRawInput = (GetRawInputT)GetRawInput;

    RawInputOriginalAddress = (void*)GetProcAddress(RawInputDllHandle, "GetRawInputData");
    RawInputHookAddress = (void*)GetRawInputData_Hook;
    pGetRawInputData = (GetRawInputDataT)RawInputOriginalAddress;

    std::memset(RawInputBuffer, 0x00, 65000);

    if (sizeof(void*) == 8) RawInputSubhook.Install(RawInputOriginalAddress, RawInputHookAddress, subhook::HookFlags::HookFlag64BitOffset);
    if (sizeof(void*) == 4) RawInputSubhook.Install(RawInputOriginalAddress, RawInputHookAddress);

    return true;
}

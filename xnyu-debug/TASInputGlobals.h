#pragma once
GameInput TASInputMouse;
GameInput TASInputKeyboard;
GameInput TASInputJoystick;

bool TASIgnoreMouseInput = false;

bool InitTASPlayers()
{
    try
    {
        if (InputDriverMouseSet == InputDriverz::RAW1NPUT || InputDriverKeyboardSet == InputDriverz::RAW1NPUT || InputDriverJoystickSet == InputDriverz::RAW1NPUT) InitPlayRawInputTAS();
        if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8) InitPlayDirectInput8TAS();
        if (InputDriverJoystickSet == InputDriverz::X1NPUT1_4) InitPlayXInput1_4TAS();
        if (InputDriverMouseSet == InputDriverz::S3ND1NPUT || InputDriverKeyboardSet == InputDriverz::S3ND1NPUT) InitPlaySendInputTAS();
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: InitTASPlayers()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        ThreadHookerResumeThreads();
        return false;
    }
    return true;
}

bool UninitTASPlayers()
{
    try
    {
        if (InputDriverMouseSet == InputDriverz::RAW1NPUT || InputDriverKeyboardSet == InputDriverz::RAW1NPUT || InputDriverJoystickSet == InputDriverz::RAW1NPUT) UninitPlayRawInputTAS();
        if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8) UninitPlayDirectInput8TAS();
        if (InputDriverJoystickSet == InputDriverz::X1NPUT1_4) UninitPlayXInput1_4TAS();
        if (InputDriverMouseSet == InputDriverz::S3ND1NPUT || InputDriverKeyboardSet == InputDriverz::S3ND1NPUT) UninitPlaySendInputTAS();
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: UninitTASPlayers()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        ThreadHookerResumeThreads();
        return false;
    }
    return true;
}

bool InitTASRecorders()
{
    try
    {
        if (InputDriverMouseGet == InputDriverz::RAW1NPUT || InputDriverKeyboardGet == InputDriverz::RAW1NPUT || InputDriverJoystickGet == InputDriverz::RAW1NPUT) InitRecordRawInputTAS();
        if (InputDriverMouseGet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8) InitRecordDirectInput8TAS();
        if (InputDriverJoystickGet == InputDriverz::X1NPUT1_4) InitRecordXInput1_4TAS();
        if (InputDriverMouseGet == InputDriverz::S3ND1NPUT || InputDriverKeyboardGet == InputDriverz::S3ND1NPUT) InitRecordSendInputTAS();
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: InitTASRecorders()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        ThreadHookerResumeThreads();
        return false;
    }
    return true;
}

bool UninitTASRecorders()
{
    try
    {
        if (InputDriverMouseGet == InputDriverz::RAW1NPUT || InputDriverKeyboardGet == InputDriverz::RAW1NPUT || InputDriverJoystickGet == InputDriverz::RAW1NPUT) UninitRecordRawInputTAS();
        if (InputDriverMouseGet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8) UninitRecordDirectInput8TAS();
        if (InputDriverJoystickGet == InputDriverz::X1NPUT1_4) UninitRecordXInput1_4TAS();
        if (InputDriverMouseGet == InputDriverz::S3ND1NPUT || InputDriverKeyboardGet == InputDriverz::S3ND1NPUT) UninitRecordSendInputTAS();
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: UninitTASRecorders()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        ThreadHookerResumeThreads();
        return false;
    }
    return true;
}

bool GetTASInput()
{
    try
    {
        std::memset(&TASInputMouse, 0x00, sizeof(GameInput));
        std::memset(&TASInputKeyboard, 0x00, sizeof(GameInput));
        std::memset(&TASInputJoystick, 0x00, sizeof(GameInput));

        if (!TASIgnoreMouseInput && InputDriverMouseGet == InputDriverz::RAW1NPUT) GetRawInput(true, &TASInputMouse, "mouse");
        if (InputDriverKeyboardGet == InputDriverz::RAW1NPUT) GetRawInput(true, &TASInputKeyboard, "keyboard");
        if (InputDriverJoystickGet == InputDriverz::RAW1NPUT) GetRawInput(true, &TASInputJoystick, "joystick");

        if (!TASIgnoreMouseInput && InputDriverMouseGet == InputDriverz::DIRECT1NPUT8) GetDirectInput8(true, &TASInputMouse, "mouse");
        if (InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8) GetDirectInput8(true, &TASInputKeyboard, "keyboard");
        if (InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8) GetDirectInput8(true, &TASInputJoystick, "joystick");

        if (InputDriverJoystickGet == InputDriverz::X1NPUT1_4) GetXInput1_4(true, &TASInputJoystick, "joystick");
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: GetTASInput()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }
    return true;
}

bool SetTASInput(GameInput FinalTASInput)
{
    try
    {
        if (InputDriverMouseSet == InputDriverz::RAW1NPUT || InputDriverKeyboardSet == InputDriverz::RAW1NPUT || InputDriverJoystickSet == InputDriverz::RAW1NPUT) SetRawInput(FinalTASInput, true);
        if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8) SetDirectInput8(FinalTASInput, true);
        if (InputDriverJoystickSet == InputDriverz::X1NPUT1_4) SetXInput1_4(FinalTASInput, true);
        if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEA || InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEA) SetMessageAInput(FinalTASInput, true);
        if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEW || InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEW) SetMessageWInput(FinalTASInput, true);
        if (InputDriverMouseSet == InputDriverz::S3ND1NPUT || InputDriverKeyboardSet == InputDriverz::S3ND1NPUT) SetSendInput(FinalTASInput, true);
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: SetTASInput()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }
    return true;
}

bool InitInputHooks()
{
    try
    {
        if (InputDriverMouseSet == InputDriverz::RAW1NPUT || InputDriverKeyboardSet == InputDriverz::RAW1NPUT || InputDriverJoystickSet == InputDriverz::RAW1NPUT || InputDriverMouseGet == InputDriverz::RAW1NPUT || InputDriverKeyboardGet == InputDriverz::RAW1NPUT || InputDriverJoystickGet == InputDriverz::RAW1NPUT)
        {
            RawInputHookInit();
        }
        if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8 || InputDriverMouseGet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8)
        {
            DirectInput8HookInit();
        }
        if (InputDriverJoystickSet == InputDriverz::X1NPUT1_4 || InputDriverJoystickGet == InputDriverz::X1NPUT1_4)
        {
            XInput1_4HookInit();
        }
        if (InputDriverMouseSet == InputDriverz::S3ND1NPUT || InputDriverKeyboardSet == InputDriverz::S3ND1NPUT)
        {
            InitSendInputHook();
        }

    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: InitInputHooks()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        ThreadHookerResumeThreads();
        return false;
    }
    return true;
}

bool UninitInputHooks()
{
    bool ejected = false;
    while (true)
    {
        try
        {
            ejected = true;
            if (InputDriverMouseSet == InputDriverz::RAW1NPUT || InputDriverKeyboardSet == InputDriverz::RAW1NPUT || InputDriverJoystickSet == InputDriverz::RAW1NPUT || InputDriverMouseGet == InputDriverz::RAW1NPUT || InputDriverKeyboardGet == InputDriverz::RAW1NPUT || InputDriverJoystickGet == InputDriverz::RAW1NPUT)
            {
                if (RawInputSubhook.IsInstalled())
                {
                    RawInputHookUninit();
                    ejected = false;
                }
            }
            if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8 || InputDriverMouseGet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8)
            {
                if (DirectInput8SubHook.IsInstalled())
                {
                    DirectInput8HookUninit();
                    ejected = false;
                }
            }
            if (InputDriverJoystickSet == InputDriverz::X1NPUT1_4 || InputDriverJoystickGet == InputDriverz::X1NPUT1_4)
            {
                if (XInput1_4SubHook.IsInstalled())
                {
                    XInput1_4HookUninit();
                    ejected = false;
                }
            }
            if (InputDriverMouseSet == InputDriverz::S3ND1NPUT || InputDriverKeyboardSet == InputDriverz::S3ND1NPUT)
            {
                SendInputHookUninit();
            }
        }
        catch (std::exception e)
        {
            DebugConsoleOutput("Error: UnInputHooks()", false, "red");
            DebugConsoleOutput(e.what(), false, "red");
            ThreadHookerResumeThreads(10);
            return false;
        }

        if (ejected) break;
    }
    return true;
}

#pragma once

bool InitTASPlayers()
{
    try
    {
        if (RawInputSubhook.IsInstalled())
        {
            if (InputDriverMouseSet == InputDriverz::RAW1NPUT || InputDriverKeyboardSet == InputDriverz::RAW1NPUT || InputDriverJoystickSet == InputDriverz::RAW1NPUT) InitPlayRawInputTAS();
        }
        if (DirectInput8SubHook.IsInstalled())
        {
            if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8) InitPlayDirectInput8TAS();
        }
        if (XInput1_4SubHook.IsInstalled())
        {
            if (InputDriverJoystickSet == InputDriverz::X1NPUT1_4) InitPlayXInput1_4TAS();
        }
        if (GetMessageASubhook.IsInstalled())
        {
            if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEA || InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEA) InitPlayGetMessageATAS();
        }
        if (GetMessageWSubhook.IsInstalled())
        {
            if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEW || InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEW) InitPlayGetMessageWTAS();
        }
        if (InputDriverMouseSet == InputDriverz::S3ND1NPUT || InputDriverKeyboardSet == InputDriverz::S3ND1NPUT) InitPlaySendInputTAS();
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: InitTASPlayers()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }
    return true;
}

bool UninitTASPlayers()
{
    try
    {
        if (RawInputSubhook.IsInstalled())
        {
            if (InputDriverMouseSet == InputDriverz::RAW1NPUT || InputDriverKeyboardSet == InputDriverz::RAW1NPUT || InputDriverJoystickSet == InputDriverz::RAW1NPUT) UninitPlayRawInputTAS();
        }
        if (DirectInput8SubHook.IsInstalled())
        {
            if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8) UninitPlayDirectInput8TAS();
        }
        if (XInput1_4SubHook.IsInstalled())
        {
            if (InputDriverJoystickSet == InputDriverz::X1NPUT1_4) UninitPlayXInput1_4TAS();
        }
        if (GetMessageASubhook.IsInstalled())
        {
            if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEA || InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEA) UninitPlayGetMessageATAS();
        }
        if (GetMessageWSubhook.IsInstalled())
        {
            if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEW || InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEW) UninitPlayGetMessageWTAS();
        }
        if (InputDriverMouseSet == InputDriverz::S3ND1NPUT || InputDriverKeyboardSet == InputDriverz::S3ND1NPUT) UninitPlaySendInputTAS();
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: UninitTASPlayers()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }
    return true;
}

bool InitTASRecorders()
{
    try
    {
        if (RawInputSubhook.IsInstalled())
        {
            if (InputDriverMouseGet == InputDriverz::RAW1NPUT || InputDriverKeyboardGet == InputDriverz::RAW1NPUT || InputDriverJoystickGet == InputDriverz::RAW1NPUT) InitRecordRawInputTAS();
        }
        if (DirectInput8SubHook.IsInstalled())
        {
            if (InputDriverMouseGet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8) InitRecordDirectInput8TAS();
        }
        if (XInput1_4SubHook.IsInstalled())
        {
            if (InputDriverJoystickGet == InputDriverz::X1NPUT1_4) InitRecordXInput1_4TAS();
        }
        if (GetMessageASubhook.IsInstalled())
        {
            if (InputDriverMouseGet == InputDriverz::G3TM3SSAGEA || InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEA) InitRecordGetMessageATAS();
        }
        if (GetMessageWSubhook.IsInstalled())
        {
            if (InputDriverMouseGet == InputDriverz::G3TM3SSAGEW || InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEW) InitRecordGetMessageWTAS();
        }
        if (InputDriverMouseGet == InputDriverz::S3ND1NPUT || InputDriverKeyboardGet == InputDriverz::S3ND1NPUT) InitRecordSendInputTAS();
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: InitTASRecorders()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }
    return true;
}

bool UninitTASRecorders()
{
    try
    {
        if (RawInputSubhook.IsInstalled())
        {
            if (InputDriverMouseGet == InputDriverz::RAW1NPUT || InputDriverKeyboardGet == InputDriverz::RAW1NPUT || InputDriverJoystickGet == InputDriverz::RAW1NPUT) UninitRecordRawInputTAS();
        }
        if (DirectInput8SubHook.IsInstalled())
        {
            if (InputDriverMouseGet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8) UninitRecordDirectInput8TAS();
        }
        if (XInput1_4SubHook.IsInstalled())
        {
            if (InputDriverJoystickGet == InputDriverz::X1NPUT1_4) UninitRecordXInput1_4TAS();
        }
        if (GetMessageASubhook.IsInstalled())
        {
            if (InputDriverMouseGet == InputDriverz::G3TM3SSAGEA || InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEA) UninitRecordGetMessageATAS();
        }
        if (GetMessageWSubhook.IsInstalled())
        {
            if (InputDriverMouseGet == InputDriverz::G3TM3SSAGEW || InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEW) UninitRecordGetMessageWTAS();
        }
        if (InputDriverMouseGet == InputDriverz::S3ND1NPUT || InputDriverKeyboardGet == InputDriverz::S3ND1NPUT) UninitRecordSendInputTAS();
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: UninitTASRecorders()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }
    return true;
}

bool GetTASInput(GameInput* FinalTASInput)
{
    try
    {
        GameInput TASInputMouse; GameInput TASInputKeyboard; GameInput TASInputJoystick;
        if (RawInputSubhook.IsInstalled())
        {
            if (InputDriverMouseGet == InputDriverz::RAW1NPUT) TASInputMouse = GetRawInput(true);
            if (InputDriverKeyboardGet == InputDriverz::RAW1NPUT) TASInputKeyboard = GetRawInput(true);
            if (InputDriverJoystickGet == InputDriverz::RAW1NPUT) TASInputJoystick = GetRawInput(true);
        }
        if (DirectInput8SubHook.IsInstalled())
        {
            if (InputDriverMouseGet == InputDriverz::DIRECT1NPUT8) TASInputMouse = GetDirectInput8(true);
            if (InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8) TASInputKeyboard = GetDirectInput8(true);
            if (InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8) TASInputJoystick = GetDirectInput8(true);
        }
        if (XInput1_4SubHook.IsInstalled())
        {
            if (InputDriverJoystickGet == InputDriverz::X1NPUT1_4) TASInputJoystick = GetXInput1_4(true);
        }
        if (GetMessageASubhook.IsInstalled())
        {
            if (InputDriverMouseGet == InputDriverz::G3TM3SSAGEA) TASInputMouse = GetMessageAInput(true);
            if (InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEA) TASInputKeyboard = GetMessageAInput(true);
        }
        if (GetMessageWSubhook.IsInstalled())
        {
            if (InputDriverMouseGet == InputDriverz::G3TM3SSAGEW) TASInputMouse = GetMessageWInput(true);
            if (InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEW) TASInputKeyboard = GetMessageWInput(true);
        }
        MergeGameInputs(FinalTASInput, &TASInputMouse, &TASInputKeyboard, &TASInputJoystick);
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
        if (RawInputSubhook.IsInstalled())
        {
            if (InputDriverMouseSet == InputDriverz::RAW1NPUT || InputDriverKeyboardSet == InputDriverz::RAW1NPUT || InputDriverJoystickSet == InputDriverz::RAW1NPUT) SetRawInput(FinalTASInput, true);
        }
        if (DirectInput8SubHook.IsInstalled())
        {
            if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8) SetDirectInput8(FinalTASInput, true);
        }
        if (XInput1_4SubHook.IsInstalled())
        {
            if (InputDriverJoystickSet == InputDriverz::X1NPUT1_4) SetXInput1_4(FinalTASInput, true);
        }
        if (GetMessageASubhook.IsInstalled())
        {
            if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEA || InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEA) SetMessageAInput(FinalTASInput, true);
        }
        if (GetMessageWSubhook.IsInstalled())
        {
            if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEW || InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEW) SetMessageWInput(FinalTASInput, true);
        }
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
        if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEA || InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEA || InputDriverMouseGet == InputDriverz::G3TM3SSAGEA || InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEA)
        {
            // They are now active all the time
        }
        if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEW || InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEW || InputDriverMouseGet == InputDriverz::G3TM3SSAGEW || InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEW)
        {
            // They are now active all the time
        }
        if (InputDriverMouseSet == InputDriverz::S3ND1NPUT || InputDriverKeyboardSet == InputDriverz::S3ND1NPUT)
        {
            InitSendInputHook();
        }

        GetMessageWHookInit();
        GetMessageAHookInit();
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: InitInputHooks()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }
    return true;
}

bool UninitInputHooks()
{
    try
    {
        if (InputDriverMouseSet == InputDriverz::RAW1NPUT || InputDriverKeyboardSet == InputDriverz::RAW1NPUT || InputDriverJoystickSet == InputDriverz::RAW1NPUT || InputDriverMouseGet == InputDriverz::RAW1NPUT || InputDriverKeyboardGet == InputDriverz::RAW1NPUT || InputDriverJoystickGet == InputDriverz::RAW1NPUT)
        {
            if (RawInputSubhook.IsInstalled())
            {
                RawInputHookUninit();
            }
        }
        if (InputDriverMouseSet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardSet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickSet == InputDriverz::DIRECT1NPUT8 || InputDriverMouseGet == InputDriverz::DIRECT1NPUT8 || InputDriverKeyboardGet == InputDriverz::DIRECT1NPUT8 || InputDriverJoystickGet == InputDriverz::DIRECT1NPUT8)
        {
            if (DirectInput8SubHook.IsInstalled())
            {
                DirectInput8HookUninit();
            }
        }
        if (InputDriverJoystickSet == InputDriverz::X1NPUT1_4 || InputDriverJoystickGet == InputDriverz::X1NPUT1_4)
        {
            if (XInput1_4SubHook.IsInstalled())
            {
                XInput1_4HookUninit();
            }
        }
        if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEA || InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEA || InputDriverMouseGet == InputDriverz::G3TM3SSAGEA || InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEA)
        {
            // They are now active all the time
        }
        if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEW || InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEW || InputDriverMouseGet == InputDriverz::G3TM3SSAGEW || InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEW)
        {
            // They are now active all the time
        }
        if (InputDriverMouseSet == InputDriverz::S3ND1NPUT || InputDriverKeyboardSet == InputDriverz::S3ND1NPUT)
        {
            SendInputHookUninit();
        }
        if (GetMessageWSubhook.IsInstalled())
        {
            GetMessageWHookUninit();
        }
        if (GetMessageASubhook.IsInstalled())
        {
            GetMessageAHookUninit();
        }
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: UnInputHooks()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }
    return true;
}

#include "pch.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "InputLayout.h"
#include "DirectInput8Hook.h"
#include "XInputHook.h"
#include "RawInputHook.h"
#include "SendInputHook.h"
#include "TASInputHooks.h"



// --- Variables ---
bool TASIgnoreMouseInput = false;



// --- Functions ---
bool SetTASInputEnabled(bool value)
{
    try
    {
        std::string mouseGet = GetGlobalSetting("config_mousedriver_get");
        std::string keyboardGet = GetGlobalSetting("config_keyboarddriver_get");
        std::string joystickGet = GetGlobalSetting("config_joystickdriver_get");

        if (mouseGet == "rawinput") { if (IsRawInputDataHookActive()) GetRawInputDataHook<GetRawInputDataT>::instance->SetMouseDeactivated(value); }
        else if (mouseGet == "directinput8") { if (IsDirectInput8HookActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->SetMouseDeactivated(value); }

        if (keyboardGet == "rawinput") { if (IsRawInputDataHookActive()) GetRawInputDataHook<GetRawInputDataT>::instance->SetKeyboardDeactivated(value); }
        else if (keyboardGet == "directinput8") { if (IsDirectInput8HookActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->SetKeyboardDeactivated(value); }

        if (joystickGet == "directinput8") { if (IsRawInputDataHookActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->SetJoystickDeactivated(value); }
        else if (joystickGet == "xinput") { if (IsXInputHookActive()) XInputGetStateHook<XInputGetStateT>::instance->SetJoystickDeactivated(value); }
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: GetTASInput()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }
    return true;
}

bool GetTASInput(GameInput* input)
{
    try
    {
        std::string mouseGet = GetGlobalSetting("config_mousedriver_get");
        std::string keyboardGet = GetGlobalSetting("config_keyboarddriver_get");
        std::string joystickGet = GetGlobalSetting("config_joystickdriver_get");

        if (mouseGet == "rawinput") { if (IsRawInputDataHookActive()) GetRawInputDataHook<GetRawInputDataT>::instance->GetMouse(input); }
        else if (mouseGet == "directinput8") { if (IsDirectInput8HookActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->GetMouse(input); }

        if (keyboardGet == "rawinput") { if (IsRawInputDataHookActive()) GetRawInputDataHook<GetRawInputDataT>::instance->GetKeyboard(input); }
        else if (keyboardGet == "directinput8") { if (IsDirectInput8HookActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->GetKeyboard(input); }

        if (joystickGet == "directinput8") { if (IsRawInputDataHookActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->GetJoystick(input); }
        else if (joystickGet == "xinput") { if (IsXInputHookActive()) XInputGetStateHook<XInputGetStateT>::instance->GetJoystick(input); }
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: GetTASInput()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }
    return true;
}

bool SetTASInput(GameInput input, GameInput inputLast)
{
    try
    {
        std::string mouseSet = GetGlobalSetting("config_mousedriver_set");
        std::string keyboardSet = GetGlobalSetting("config_keyboarddriver_set");
        std::string joystickSet = GetGlobalSetting("config_joystickdriver_set");

        if (mouseSet == "rawinput") { if (IsRawInputDataHookActive()) GetRawInputDataHook<GetRawInputDataT>::instance->SetMouse(input, inputLast); }
        else if (mouseSet == "directinput8") { if (IsDirectInput8HookActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->SetMouse(input, inputLast); }
        else if (mouseSet == "sendinput") { if (IsSendInputHookActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->SetMouse(input, inputLast); }

        if (keyboardSet == "rawinput") { if (IsRawInputDataHookActive()) GetRawInputDataHook<GetRawInputDataT>::instance->SetKeyboard(input, inputLast); }
        else if (keyboardSet == "directinput8") { if (IsDirectInput8HookActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->SetKeyboard(input, inputLast); }
        else if (keyboardSet == "sendinput") { if (IsSendInputHookActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->SetKeyboard(input, inputLast); }

        if (joystickSet == "directinput8") { if (IsDirectInput8HookActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->SetJoystick(input, inputLast); }
        else if (joystickSet == "xinput") { if (IsXInputHookActive()) XInputGetStateHook<XInputGetStateT>::instance->SetJoystick(input, inputLast); }
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: SetTASInput()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }
    return true;
}

bool InitTASInputHooks()
{
    try
    {
        std::string mouseSet = GetGlobalSetting("config_mousedriver_set");
        std::string keyboardSet = GetGlobalSetting("config_keyboarddriver_set");
        std::string joystickSet = GetGlobalSetting("config_joystickdriver_set");
        std::string mouseGet = GetGlobalSetting("config_mousedriver_get");
        std::string keyboardGet = GetGlobalSetting("config_keyboarddriver_get");
        std::string joystickGet = GetGlobalSetting("config_joystickdriver_get");

        if (mouseSet == "rawinput" || keyboardSet == "rawinput" || mouseGet == "rawinput" || keyboardGet == "rawinput") GetRawInputDataHookInit();
        if (mouseSet == "directinput8" || keyboardSet == "directinput8" || joystickSet == "directinput8" || mouseGet == "directinput8" || keyboardGet == "directinput8" || joystickGet == "directinput8") DirectInput8HookInit();
        if (mouseSet == "sendinput" || keyboardSet == "sendinput") SendInputHookInit();
        if (joystickSet == "xinput" || joystickGet == "xinput") XInputHookInit();

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
        std::string mouseSet = GetGlobalSetting("config_mousedriver_set");
        std::string keyboardSet = GetGlobalSetting("config_keyboarddriver_set");
        std::string joystickSet = GetGlobalSetting("config_joystickdriver_set");
        std::string mouseGet = GetGlobalSetting("config_mousedriver_get");
        std::string keyboardGet = GetGlobalSetting("config_keyboarddriver_get");
        std::string joystickGet = GetGlobalSetting("config_joystickdriver_get");

        if (mouseSet == "rawinput" || keyboardSet == "rawinput" || mouseGet == "rawinput" || keyboardGet == "rawinput") GetRawInputDataHookUninit();
        if (mouseSet == "directinput8" || keyboardSet == "directinput8" || joystickSet == "directinput8" || mouseGet == "directinput8" || keyboardGet == "directinput8" || joystickGet == "directinput8") DirectInput8HookUninit();
        if (mouseSet == "sendinput" || keyboardSet == "sendinput") SendInputHookUninit();
        if (joystickSet == "xinput" || joystickGet == "xinput") XInputHookUninit();
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: UninitInputHooks()", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }

    return true;
}



//Basic includes
#include "pch.h"

//Other includes
#include "xNyuLibrary.h"



DWORD __stdcall EjectDebug(LPVOID lpParameter) {
    Sleep(100);
    DebugConsoleOutput("Eject debug!", false, "red");
    if (!ConsoleEnabled)
    {
        FreeConsole();
        fclose(fp);
    }
    Sleep(100);
    FreeLibraryAndExitThread(dllHandle, 0);
    return 0;
}

EXTERN_DLL_EXPORT int ejectDebugger(char* parameterRaw)
{
    try
    {
        // Remove graphics hook
        if (D3D9_Subhook.IsInstalled())
        {
            D3D9_Subhook.Remove();
        }
        if (D3D10_Subhook.IsInstalled())
        {
            D3D10_Subhook.Remove();
        }
        if (D3D11_Subhook.IsInstalled())
        {
            D3D11_Subhook.Remove();
        }
        if (D3D12_Subhook.IsInstalled())
        {
            D3D12_Subhook.Remove();
        }

        // Remove the input hooks
        UninitInputHooks();

        // Disable the freezing settings
        SetThreadExecutionState(ES_CONTINUOUS);

        // Eject the DLL
        CreateThread(0, 0, EjectDebug, 0, 0, 0);
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in ejectDebugger()", false, "red");
        return 0;
    }
    return 1;
}

EXTERN_DLL_EXPORT int initDebugger(char* parameterRaw)
{
    try
    {
        std::string parameterString(parameterRaw);

        // Split the message
        std::vector<std::string> params;
        splitStringVector(params, parameterString, ";");

        // Get main window handle
        MainWindowHandle = find_main_window(GetCurrentProcessId());

        GlobalSettings.config_root_directory = params[0];
        GlobalSettings.config_settings_directory = params[1];
        GlobalSettings.config_script_directory = params[2];
        GlobalSettings.config_working_directory = params[3];
        GlobalSettings.config_log_directory = params[4];
        GlobalSettings.config_debugmod_directory = params[5];
        GlobalSettings.config_debugfunction_directory = params[6];
        GlobalSettings.config_debugaddress_directory = params[7];
        GlobalSettings.config_inputmapping_directory = params[8];
        GlobalSettings.config_savefile_directory = params[9];
        GlobalSettings.config_debugconfig_directory = params[10];

        GlobalSettings.config_mousedriver_set = params[11];
        GlobalSettings.config_mousedriver_get = params[12];
        GlobalSettings.config_keyboarddriver_set = params[13];
        GlobalSettings.config_keyboarddriver_get = params[14];
        GlobalSettings.config_joystickdriver_set = params[15];
        GlobalSettings.config_joystickdriver_get = params[16];
        GlobalSettings.config_graphicdriver = params[17];

        GlobalSettings.config_modname = params[18];
        GlobalSettings.config_processname = params[19];
        GlobalSettings.config_version = params[20];

        GlobalSettings.config_frame_skip = std::stoi(params[21]);
        GlobalSettings.config_tas_delay = std::stoi(params[22]);

        if (GlobalSettings.config_mousedriver_set == "rawinput") InputDriverMouseSet = InputDriverz::RAW1NPUT;
        if (GlobalSettings.config_mousedriver_set == "directinput8") InputDriverMouseSet = InputDriverz::DIRECT1NPUT8;
        if (GlobalSettings.config_mousedriver_set == "getmessagea") InputDriverMouseSet = InputDriverz::G3TM3SSAGEA;
        if (GlobalSettings.config_mousedriver_set == "getmessagew") InputDriverMouseSet = InputDriverz::G3TM3SSAGEW;
        if (GlobalSettings.config_mousedriver_set == "sendinput") InputDriverMouseSet = InputDriverz::S3ND1NPUT;

        if (GlobalSettings.config_mousedriver_get == "rawinput") InputDriverMouseGet = InputDriverz::RAW1NPUT;
        if (GlobalSettings.config_mousedriver_get == "directinput8") InputDriverMouseGet = InputDriverz::DIRECT1NPUT8;
        if (GlobalSettings.config_mousedriver_get == "getmessagea") InputDriverMouseGet = InputDriverz::G3TM3SSAGEA;
        if (GlobalSettings.config_mousedriver_get == "getmessagew") InputDriverMouseGet = InputDriverz::G3TM3SSAGEW;

        if (GlobalSettings.config_keyboarddriver_set == "rawinput") InputDriverKeyboardSet = InputDriverz::RAW1NPUT;
        if (GlobalSettings.config_keyboarddriver_set == "directinput8") InputDriverKeyboardSet = InputDriverz::DIRECT1NPUT8;
        if (GlobalSettings.config_keyboarddriver_set == "getmessagea") InputDriverKeyboardSet = InputDriverz::G3TM3SSAGEA;
        if (GlobalSettings.config_keyboarddriver_set == "getmessagew") InputDriverKeyboardSet = InputDriverz::G3TM3SSAGEW;
        if (GlobalSettings.config_keyboarddriver_set == "sendinput") InputDriverKeyboardSet = InputDriverz::S3ND1NPUT;

        if (GlobalSettings.config_keyboarddriver_get == "rawinput") InputDriverKeyboardGet = InputDriverz::RAW1NPUT;
        if (GlobalSettings.config_keyboarddriver_get == "directinput8") InputDriverKeyboardGet = InputDriverz::DIRECT1NPUT8;
        if (GlobalSettings.config_keyboarddriver_get == "getmessagea") InputDriverKeyboardGet = InputDriverz::G3TM3SSAGEA;
        if (GlobalSettings.config_keyboarddriver_get == "getmessagew") InputDriverKeyboardGet = InputDriverz::G3TM3SSAGEW;

        if (GlobalSettings.config_joystickdriver_set == "rawinput") InputDriverJoystickSet = InputDriverz::RAW1NPUT;
        if (GlobalSettings.config_joystickdriver_set == "directinput8") InputDriverJoystickSet = InputDriverz::DIRECT1NPUT8;
        if (GlobalSettings.config_joystickdriver_set == "xinput1_4") InputDriverJoystickSet = InputDriverz::X1NPUT1_4;

        if (GlobalSettings.config_joystickdriver_get == "rawinput") InputDriverJoystickGet = InputDriverz::RAW1NPUT;
        if (GlobalSettings.config_joystickdriver_get == "directinput8") InputDriverJoystickGet = InputDriverz::DIRECT1NPUT8;
        if (GlobalSettings.config_joystickdriver_get == "xinput1_4") InputDriverJoystickGet = InputDriverz::X1NPUT1_4;

        // Init the debug mod
        InitDebugMod(_DebugDrawRectangle, _DebugDrawText);

        // Init the debug menu variables
        DebugMenuInitValues();

        // Load texture files
        LoadFormTextures();

        BOOL already_hooked = false;

        if (GlobalSettings.config_graphicdriver == "directx12")
        {
            already_hooked = D3D12HookInit();
        }
        else if (GlobalSettings.config_graphicdriver == "directx11")
        {
            already_hooked = D3D11HookInit();
        }
        else if (GlobalSettings.config_graphicdriver == "directx10")
        {
            already_hooked = D3D10HookInit();
        }
        else if (GlobalSettings.config_graphicdriver == "directx9")
        {
            already_hooked = D3D9HookInit();
        }
        else
        {
            if (!already_hooked)
            {
                already_hooked = D3D12HookInit();
            }

            if (!already_hooked)
            {
                already_hooked = D3D11HookInit();
            }

            if (!already_hooked)
            {
                already_hooked = D3D10HookInit();
            }

            if (!already_hooked)
            {
                already_hooked = D3D9HookInit();
            }
        }

        if (!already_hooked)
        {
            // Graphics hook failed
            ejectDebugger(nullptr);
            return 2;
        }

        // Set input mapping paths
        LoadGameInputLayout(&TASInputLayout, GlobalSettings.config_inputmapping_directory + "InputMapping.ini");

        // Hook all the desired input functions
        InitInputHooks();

        // Set thread fitting for freezing
        SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED);
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in initDebugger()", false, "red");

        // Unknown hook failed
        ejectDebugger(nullptr);
        return 1;
    }
    return 0;
}

EXTERN_DLL_EXPORT int playScriptTAS(char* parameterRaw)
{
    try
    {
        if (!DebugMenuOpened)
        {
            std::string parameterString(parameterRaw);

            // Split the message
            std::vector<std::string> params;
            splitStringVector(params, parameterString, ";");

            if (!TASPlayScript)
            {
                // Path to the script
                TASScript = GlobalSettings.config_script_directory + params[0];

                // Start playing the script
                TASPlayScriptInit = true;
                TASPlayScript = true;
                TASPlayScriptUninit = false;
                TASPlayScriptDone = false;
            }
            else
            {
                // Stop playing the script
                TASPlayScriptInit = false;
                TASPlayScript = false;
                TASPlayScriptUninit = true;
            }
        }
        else
        {
            DebugConsoleOutput("You have to close the debug menu first!", false, "red");
        }
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in playScriptTAS()", false, "red");
        return 0;
    }
    return 1;
}

EXTERN_DLL_EXPORT int recordScriptTAS(char* parameterRaw)
{
    try
    {
        if (!DebugMenuOpened)
        {
            std::string parameterString(parameterRaw);

            // Split the message
            std::vector<std::string> params;
            splitStringVector(params, parameterString, ";");

            if (!TASRecordScript)
            {
                // Path to the script
                TASScript = GlobalSettings.config_script_directory + params[0];

                // Start recording the script
                TASRecordScriptInit = true;
                TASRecordScript = true;
                TASRecordScriptUninit = false;
                TASRecordScriptDone = false;
            }
            else
            {
                // Stop recording the script
                TASRecordScriptInit = false;
                TASRecordScript = false;
                TASRecordScriptUninit = true;
            }
        }
        else
        {
            DebugConsoleOutput("You have to close the debug menu first!", false, "red");
        }
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in recordScriptTAS()", false, "red");
        return 0;
    }
    return 1;
}

EXTERN_DLL_EXPORT int checkIfPlayScriptIsDoneTAS(char* parameterRaw)
{
    try
    {
        if (TASPlayScriptDone)
        {
            TASPlayScriptDone = false;
            return 666;
        }
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in checkIfPlayScriptIsDoneTAS()", false, "red");
        return 0;
    }
    return 1;
}

EXTERN_DLL_EXPORT int checkIfRecordScriptIsDoneTAS(char* parameterRaw)
{
    try
    {
        if (TASRecordScriptDone)
        {
            TASRecordScriptDone = false;
            return 666;
        }
        else if (TASRecordStartedSignal)
        {
            TASRecordStartedSignal = false;
            return 13;
        }
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in checkIfRecordScriptIsDoneTAS()", false, "red");
        return 0;
    }
    return 1;
}

EXTERN_DLL_EXPORT int enableFrameByFrameTAS(char* parameterRaw)
{
    try
    {
        std::string parameterString(parameterRaw);

        // Split the message
        std::vector<std::string> params;
        splitStringVector(params, parameterString, ";");

        TASRecordFrameByFrame = params[0] == "1" ? true : false;
        TASRecordFrameByFrameInputTrigger = TASRecordFrameByFrame;
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in enableFrameByFrameTAS()", false, "red");
        return 0;
    }
    return 1;
}

EXTERN_DLL_EXPORT int playToRecordTAS(char* parameterRaw)
{
    try
    {
        std::string parameterString(parameterRaw);

        // Split the message
        std::vector<std::string> params;
        splitStringVector(params, parameterString, ";");

        TASPlayScriptThenRecord = params[0] == "1" ? true : false;
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in playToRecordTAS()", false, "red");
        return 0;
    }
    return 1;
}

EXTERN_DLL_EXPORT int windowStayActive(char* parameterRaw)
{
    try
    {
        std::string parameterString(parameterRaw);

        // Split the message
        std::vector<std::string> params;
        splitStringVector(params, parameterString, ";");

        if (params[0] == "1")
        {
            if (!GetForegroundWindowSubHook.IsInstalled()) InitWindowStayActive();
        }
        else
        {
            if (GetForegroundWindowSubHook.IsInstalled()) UninitWindowStayActive();
        }
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in playToRecordTAS()", false, "red");
        return 0;
    }
    return 1;
}

EXTERN_DLL_EXPORT int receiveFrameTAS(char* parameterRaw)
{
    try
    {
        std::string parameterString(parameterRaw);

        // Split the message
        std::vector<std::string> params;
        splitStringVector(params, parameterString, ";END;");

        TASRecordFrameReceived = params[0];
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in receiveFrameTAS()", false, "red");
        return 0;
    }
    return 1;
}

EXTERN_DLL_EXPORT int toggleDevConsole(char* parameterRaw)
{
    try
    {
        if (!ConsoleEnabled)
        {
            AllocConsole();
            freopen_s(&fp, "CONOUT$", "w", stdout);
            DebugConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
            ConsoleEnabled = true;
        }
        else
        {
            fclose(fp);
            Sleep(10);
            FreeConsole();
            ConsoleEnabled = false;
        }
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in openDevConsole()", false, "red");
        return 0;
    }
    return 1;
}

EXTERN_DLL_EXPORT int toggleDevMode(char* parameterRaw)
{
    try
    {
        DevMode = !DevMode;
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in openDevConsole()", false, "red");
        return 0;
    }
    return 1;
}

DWORD MainThread()
{
    if (GetProcessName().find("xNyu") == std::string::npos)
    {
        // Probably needed...
        std::string tmp = ";";
        toggleDevConsole((char*)tmp.c_str());
    }
    return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        dllHandle = hModule;
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, nullptr, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:

        break;
    }
    return TRUE;
}

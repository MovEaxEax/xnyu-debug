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

EXTERN_DLL_EXPORT int EjectDebugger(char* parameterRaw)
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

        // Remove Threadhooker
        UninitThreadhooker();

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

                if (std::filesystem::exists(TASScript) && !params[0].empty() && params[0].find(".nts") != std::string::npos) {
                    // File exists
                    TASSynchronizerCanSend = false;
                    TASSynchronizerFinishedCurrent = 0;

                    // Start playing the script
                    TASPlayScriptInit = true;
                    TASPlayScript = true;
                    TASPlayScriptUninit = false;
                    TASPlayScriptDone = false;

                    TASPlayStartedSignal = true;
                }
                else {
                    DebugConsoleOutput("A script named \"" + TASScript + "\" doesn't exist!", false, "red");
                }
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
                if (params[0].empty())
                {
                    params[0] = "Script_" + GetCurrentDateTime() + ".nts";
                }
                else if (params[0].length() > 3) {
                    if (params[0].substr(params[0].length() - 4, 4) != ".nts") {
                        params[0] += ".nts";
                    }
                }
                else
                {
                    params[0] += ".nts";
                }

                // Path to the script
                TASScript = GlobalSettings.config_script_directory + params[0];

                // Start recording the script
                TASRecordScriptInit = true;
                TASRecordScript = true;
                TASRecordScriptUninit = false;
                TASRecordScriptDone = false;
                if (!TASPlayScriptThenRecord) TASRecordStartedSignal = true;
                else TASPlayStartedSignal = true;
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

EXTERN_DLL_EXPORT int initDebugger(char* parameterRaw)
{
    try
    {
        std::string parameterString(parameterRaw);

        // Split the message
        std::vector<std::string> params;
        splitStringVector(params, parameterString, ";");

        // Hook Thread creation process
        InitThreadhooker();

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
        GlobalSettings.config_editormode_settings_directory = params[8];
        GlobalSettings.config_editormode_actions_directory = params[9];
        GlobalSettings.config_supervision_directory = params[10];
        GlobalSettings.config_inputmapping_directory = params[11];
        GlobalSettings.config_savefile_directory = params[12];
        GlobalSettings.config_debugconfig_directory = params[13];

        GlobalSettings.config_mousedriver_set = params[14];
        GlobalSettings.config_mousedriver_get = params[15];
        GlobalSettings.config_keyboarddriver_set = params[16];
        GlobalSettings.config_keyboarddriver_get = params[17];
        GlobalSettings.config_joystickdriver_set = params[18];
        GlobalSettings.config_joystickdriver_get = params[19];
        GlobalSettings.config_graphicdriver = params[20];
        GlobalSettings.config_d3d9_hook = params[21];
        GlobalSettings.config_rawinput_demand = params[22] == "true";
        
        GlobalSettings.config_modname = params[23];
        GlobalSettings.config_processname = params[24];
        GlobalSettings.config_version = params[25];

        GlobalSettings.config_tashook = params[26];

        GlobalSettings.config_frame_skip = std::stoi(params[27]);
        GlobalSettings.config_tas_delay = std::stoi(params[28]);

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
        if (GlobalSettings.config_joystickdriver_set == "xinput1_4" || GlobalSettings.config_joystickdriver_set == "xinput1_3") InputDriverJoystickSet = InputDriverz::X1NPUT1_4;

        if (GlobalSettings.config_joystickdriver_get == "rawinput") InputDriverJoystickGet = InputDriverz::RAW1NPUT;
        if (GlobalSettings.config_joystickdriver_get == "directinput8") InputDriverJoystickGet = InputDriverz::DIRECT1NPUT8;
        if (GlobalSettings.config_joystickdriver_get == "xinput1_4" || GlobalSettings.config_joystickdriver_get == "xinput1_3") InputDriverJoystickGet = InputDriverz::X1NPUT1_4;

        // Detect the maximum hooks
        std::vector<std::string> _allHooks;
        _allHooks.push_back(GlobalSettings.config_mousedriver_set);
        _allHooks.push_back(GlobalSettings.config_keyboarddriver_set);
        _allHooks.push_back(GlobalSettings.config_joystickdriver_set);
        bool increase = true;
        if (GlobalSettings.config_mousedriver_set != "")
        {
            for (int i = 0; i < _allHooks.size(); i++) if (GlobalSettings.config_mousedriver_set == _allHooks[i]) increase = false;
            if (increase)
            {
                _allHooks.push_back(GlobalSettings.config_mousedriver_set);
                TASSynchronizerFinishedMax++;
            }
        }
        if (GlobalSettings.config_keyboarddriver_set != "")
        {
            increase = true;
            for (int i = 0; i < _allHooks.size(); i++) if (GlobalSettings.config_keyboarddriver_set == _allHooks[i]) increase = false;
            if (increase)
            {
                _allHooks.push_back(GlobalSettings.config_keyboarddriver_set);
                TASSynchronizerFinishedMax++;
            }
        }
        if (GlobalSettings.config_joystickdriver_set != "")
        {
            increase = true;
            for (int i = 0; i < _allHooks.size(); i++) if (GlobalSettings.config_joystickdriver_set == _allHooks[i]) increase = false;
            if (increase)
            {
                _allHooks.push_back(GlobalSettings.config_joystickdriver_set);
                TASSynchronizerFinishedMax++;
            }
        }

        // TAS functions for routine hooks
        pTASRoutine = (TASRoutineT)TASRoutine;
        pTASPlayScript = (TASCommandT)playScriptTAS;
        pTASRecordScript = (TASCommandT)recordScriptTAS;

        // Set the debug references
        GlobalReferences.drawRectangle = _DebugDrawRectangle;
        GlobalReferences.drawText = _DebugDrawText;
        GlobalReferences.logger = DebugConsoleOutput;
        GlobalReferences.TASRoutine = pTASRoutine;
        GlobalReferences.installGraphicsHook = InstallGraphicHook;
        GlobalReferences.removeGraphicsHook = RemoveGraphicHook;

        // Init the debug mod
        InitDebugMod();

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
            EjectDebugger(nullptr);
            return 2;
        }

        // Set input mapping paths
        LoadGameInputLayout(&TASInputLayout, GlobalSettings.config_inputmapping_directory + "InputMapping.ini");

        // Hook all the desired input functions
        // InitInputHooks();

        // Get memory regions
        GetMemoryRegions(memoryRegionsStart, memoryRegionsEnd, &memoryRegionsCounter);

        // Set thread fitting for freezing
        SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED);
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in initDebugger()", false, "red");

        // Unknown hook failed
        EjectDebugger(nullptr);
        return 1;
    }
    return 0;
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
        else if (TASPlayStartedSignal)
        {
            TASPlayStartedSignal = false;
            return 13;
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
        WaitForSingleObject(DebugConsoleOutputMutex, INFINITE);
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
        ReleaseMutex(DebugConsoleOutputMutex);
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in openDevConsole()", false, "red");
        ReleaseMutex(DebugConsoleOutputMutex);
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

EXTERN_DLL_EXPORT int toggleOverclocker(char* parameterRaw)
{
    try
    {
        if (!OverclockerIsActive) InitOverclocker();
        else UninitOverclocker();
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in enableOverclocker()", false, "red");
        return 0;
    }
    return 1;
}

EXTERN_DLL_EXPORT int toggleTASIgnoreMouse(char* parameterRaw)
{
    try
    {
        std::string parameterString(parameterRaw);

        // Split the message
        std::vector<std::string> params;
        splitStringVector(params, parameterString, ";");

        TASIgnoreMouseInput = !TASIgnoreMouseInput;
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error in toggleTASIgnoreMouse()", false, "red");
        return 0;
    }
    return 1;
}

DWORD MainThread()
{
    if (GetProcessName().find("xnyu") == std::string::npos)
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

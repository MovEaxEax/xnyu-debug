#include "pch.h"
#include "TAS.h"
#include "Conversions.h"
#include "InputLayout.h"
#include "DebugFunctions.h"
#include "DebugAddresses.h"
#include "Variable.h"
#include "Logging.h"
#include "Threadhooker.h"
#include "PythonTASConnecter.h"
#include "TASInputHooks.h"


// --- Variables ---
std::string TASTargetScript = "";

bool TASPlayingActive = false;
bool TASPlayingInit = false;
bool TASPlayingUnInit = false;

bool TASRecordingActive = false;
bool TASRecordingInit = false;
bool TASRecordingUnInit = false;

GameInputLayout TASInputLayout = GameInputLayout();
GameInput TASGameInputCurrent = GameInput();
GameInput TASGameInputLast = GameInput();

long long TASFramesPassed = 0;

HANDLE PythonInterpreterThread = nullptr;
HANDLE PythonInterpreterThreadMutex = CreateMutex(NULL, FALSE, NULL);
FILE* PythonInterpreterScript = nullptr;
bool PythonInterpreterThreadAlive = true;
std::string PythonInterpreterLineToExecute;

// --- Functions ---
DWORD __stdcall PythonInterpreterScriptRoutine(LPVOID lpParam)
{
    WaitForSingleObject(PythonInterpreterThreadMutex, INFINITE);

    // Init python interpreter
    Py_Initialize();

    // Export tas module
    PyImport_AppendInittab("xnyutas", PyInit_xnyutas);

    // Open and run script
    PythonInterpreterScript = fopen(TASTargetScript.c_str(), "r");
    ReleaseMutex(PythonInterpreterThreadMutex);
    PyRun_SimpleFile(PythonInterpreterScript, TASTargetScript.c_str());

    // Clean up
    WaitForSingleObject(PythonInterpreterThreadMutex, INFINITE);
    Py_Finalize();
    fclose(PythonInterpreterScript);
    TASPlayingUnInit = true;
    ReleaseMutex(PythonInterpreterThreadMutex);

    return 0;
}

DWORD __stdcall PythonInterpreterStringRoutine(LPVOID lpParam)
{
    WaitForSingleObject(PythonInterpreterThreadMutex, INFINITE);

    // Init python interpreter
    Py_Initialize();

    // Export tas module
    PyImport_AppendInittab("xnyutas", PyInit_xnyutas);
    ReleaseMutex(PythonInterpreterThreadMutex);

    // Loop to execute the next instruction
    while (true)
    {
        WaitForSingleObject(PythonInterpreterThreadMutex, INFINITE);
        if (!PythonInterpreterThreadAlive) break;
        if (PythonInterpreterLineToExecute != "") PyRun_SimpleString(PythonInterpreterLineToExecute.c_str());
        PythonInterpreterLineToExecute = "";
        ReleaseMutex(PythonInterpreterThreadMutex);
    }

    // Clean up
    Py_Finalize();
    ReleaseMutex(PythonInterpreterThreadMutex);

    return 0;
}

EXTERN_DLL_EXPORT bool PlayScriptRoutine() {
    try
    {
        if (TASPlayingInit)
        {
            TASGameInputCurrent = GameInput();
            TASGameInputLast = GameInput();

            SetTASInputEnabled(false);

            PythonShutdownInterpreter = false;
            PythonInterpreterThread = CreateThreadReal(NULL, 0, PythonInterpreterScriptRoutine, NULL, 0, NULL, true);

            TASPlayingActive = true;
            TASPlayingInit = false;
        }
        if (TASPlayingActive)
        {
            while (true)
            {
                WaitForSingleObject(PythonFrameTriggeredMutex, INFINITE);
                if (!PythonFrameTriggered)
                {
                    ReleaseMutex(PythonFrameTriggeredMutex);
                    break;
                }
                if (TASPlayingUnInit)
                {
                    ReleaseMutex(PythonFrameTriggeredMutex);
                    break;
                }
            }

            // Set frame input
            GameInputSetFrame(TASGameInputCurrent, TASInputLayout, PythonFrameTriggeredParameter);
            SetTASInput(TASGameInputCurrent, TASGameInputLast);
            TASGameInputLast = TASGameInputCurrent;

            return;
        }
        if (TASPlayingUnInit)
        {
            SetTASInputEnabled(false);
            WaitForSingleObject(PythonFrameTriggeredMutex, INFINITE);
            PythonShutdownInterpreter = true;
            ReleaseMutex(PythonFrameTriggeredMutex);
            TASPlayingActive = false;
            TASPlayingUnInit = false;
        }
    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: PlayScriptRoutine()", false, "red");



    }
    return true;
}

EXTERN_DLL_EXPORT bool RecordScriptRoutine() {
    try
    {

    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: RecordScriptRoutine()", false, "red");



    }
    return true;
}

EXTERN_DLL_EXPORT bool RecordScriptFrameByFrameRoutine() {
    try
    {

    }
    catch (std::exception e)
    {
        DebugConsoleOutput("Error: RecordScriptRoutine()", false, "red");



    }
    return true;
}

EXTERN_DLL_EXPORT void TASRoutine()
{
    if (TASPlayingActive) PlayScriptRoutine();
    if (TASRecordingActive) RecordScriptRoutine();
}



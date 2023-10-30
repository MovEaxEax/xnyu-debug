#pragma once

// Essentials



//
// --- STRUCTURE IMPORTS ---
//

// Utility
#include "Technical.h"
#include "Conversions.h"
#include "Logging.h"

// Input
#include "InputLayout.h"

// Variables
#include "Variable.h"

// Debug mod settings
#include "DebugSettings.h"

// Global
#include "SharedTypedefs.h"
#include "SharedVariables.h"

// Debug mod features
#include "DebugAddresses.h"
#include "DebugFunctions.h"
#include "DebugSupervisionSettings.h"
#include "DebugEditorSettings.h"
#include "DebugAddresses.h"
#include "SavefileEditor.h"
#include "DebugModGlobals.h"

// Memory
#include "Regions.h"
#include "BasePointer.h"
#include "ReadMemory.h"
#include "SigScan.h"
#include "WriteMemory.h"

// HackZ
#include "NtUser.h"

// Special
#include "xNyuHook.h"
#include "Threadhooker.h"
#include "Winactive.h"
#include "Overclocker.h"


// Input hooks
#include "InputHookGlobals.h"
#include "DirectInput8-Hook.h"
#include "XInput1_4-Hook.h"
#include "RawInput-Hook.h"
#include "SendInput-Hook.h"
#include "TASInputGlobals.h"
#include "TAS.h"

// After includes
#include "DrawingEssentials.h"
#include "DebugMenu.h"
#include <utility>
#include "Exceptions.hpp"
#include "Window.h"
#include <dxgi.h>
#include "DXGI.h"
#include "Direct3DBase.h"
#include "D3D9-Extra-Hooks.h"
#include "GraphicsHookGlobals.h"
#include "D3D9-Hook.h"
#include "D3D10-Hook.h"
#include "D3D11-Hook.h"
#include "D3D12-Hook.h"



DWORD __stdcall EjectDebug(LPVOID lpParameter);
EXTERN_DLL_EXPORT int EjectDebugger(char* parameterRaw);
EXTERN_DLL_EXPORT int playScriptTAS(char* parameterRaw);
EXTERN_DLL_EXPORT int recordScriptTAS(char* parameterRaw);
EXTERN_DLL_EXPORT int initDebugger(char* parameterRaw);
EXTERN_DLL_EXPORT int checkIfPlayScriptIsDoneTAS(char* parameterRaw);
EXTERN_DLL_EXPORT int checkIfRecordScriptIsDoneTAS(char* parameterRaw);
EXTERN_DLL_EXPORT int enableFrameByFrameTAS(char* parameterRaw);
EXTERN_DLL_EXPORT int playToRecordTAS(char* parameterRaw);
EXTERN_DLL_EXPORT int windowStayActive(char* parameterRaw);
EXTERN_DLL_EXPORT int receiveFrameTAS(char* parameterRaw);
EXTERN_DLL_EXPORT int toggleDevConsole(char* parameterRaw);
EXTERN_DLL_EXPORT int toggleDevMode(char* parameterRaw);
EXTERN_DLL_EXPORT int toggleOverclocker(char* parameterRaw);
EXTERN_DLL_EXPORT int toggleTASIgnoreMouse(char* parameterRaw);
DWORD MainThread();
BOOL WINAPI DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved);



#pragma once
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <math.h>
#include <psapi.h>
#include <stdio.h>
#include <iomanip>
#include <xnamath.h>
#include <filesystem>
#include <tlhelp32.h>
#include <ctime> 
#include <memory>
#include <memorys.h>
#include <atlimage.h>
#include <thread>
#include <mutex>
#include <functional>
#include <unordered_set>
#include <regex>
#include <optional>

#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")

#include <Processthreadsapi.h>
#pragma comment(lib, "Kernel32.lib")

#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

#define SUBHOOK_STATIC
#include <subhook.h>
#include "subhook.c"





//
// Definements ---------------------------------------------------------------------
//

#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

struct DebugSettings {
    std::string config_modname;
    std::string config_processname;
    std::string config_version;
    std::string config_tashook;
    std::string config_mousedriver_set;
    std::string config_mousedriver_get;
    std::string config_keyboarddriver_set;
    std::string config_keyboarddriver_get;
    std::string config_joystickdriver_set;
    std::string config_joystickdriver_get;
    std::string config_graphicdriver;
    std::string config_d3d9_hook;
    bool config_rawinput_demand;
    std::string config_root_directory;
    std::string config_settings_directory;
    std::string config_script_directory;
    std::string config_working_directory;
    std::string config_log_directory;
    std::string config_debugmod_directory;
    std::string config_debugfunction_directory;
    std::string config_debugaddress_directory;
    std::string config_editormode_settings_directory;
    std::string config_editormode_actions_directory;
    std::string config_supervision_directory;
    std::string config_inputmapping_directory;
    std::string config_savefile_directory;
    std::string config_debugconfig_directory;
    int config_frame_skip;
    int config_tas_delay;
};

struct DebugFeatures
{
    bool debugAddress;
    bool debugFunction;
    bool savefileEditor;
    bool supervision;
    bool editorMode;
};

struct DebugReferences
{
    void* logger;
    void* drawRectangle;
    void* drawText;
    void* TASRoutine;
    void* installGraphicsHook;
    void* removeGraphicsHook;
};

struct ThreadReferences
{
    void* ThreadHookerGetThreadCount;
    void* ThreadHookerGetThreads;
    void* ThreadHookerGetSafeThreadCount;
    void* ThreadHookerGetSafeThreads;
    void* ThreadHookerSuspendThreads;
    void* ThreadHookerResumeThreads;
    void* ThreadHookerCreateThread;
    void* ThreadHookerCreateRemoteThread;
    void* ThreadHookerCreateRemoteThreadEx;
};

struct Point
{
    float x;
    float y;
};

Point PointConversion(POINT point)
{
    Point newPoint = Point();
    newPoint.x = (float)point.x;
    newPoint.y = (float)point.y;
    return newPoint;
}

Point PointCreate(float x, float y)
{
    Point newPoint = Point();
    newPoint.x = x;
    newPoint.y = y;
    return newPoint;
}

//
// Globals -------------------------------------------------------------------------
//

// Debug Console
bool ConsoleEnabled = false;
bool DevMode = false;
HANDLE DebugConsoleHandle;
FILE* fp;

// Injected DLL Information
HMODULE dllHandle;
std::string dll_dir = "";

// Settings
std::string PipeServername = "";
std::string GraphicDriver = "";
std::string InputHookAdresse = "";

// Main window handle
HWND MainWindowHandle = NULL;
RECT MainWindowRect;

BOOL MainWindowActive = false;

DebugSettings GlobalSettings;
DebugReferences GlobalReferences;
ThreadReferences ThreadHookerReferences;
int GlobalFrameSkipCurrent = 0;

HANDLE DebugConsoleOutputMutex = CreateMutex(NULL, FALSE, NULL);

void __cdecl DebugConsoleOutput(std::string text, bool dev, std::string color = "white")
{
    WaitForSingleObject(DebugConsoleOutputMutex, INFINITE);
    if (!ConsoleEnabled)
    {
        ReleaseMutex(DebugConsoleOutputMutex);
        return;
    }
    if (dev && !DevMode)
    {
        ReleaseMutex(DebugConsoleOutputMutex);
        return;
    }
    WORD ForegroundColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    if (color == "red") ForegroundColor = FOREGROUND_RED | FOREGROUND_INTENSITY;
    if (color == "green") ForegroundColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    if (color == "blue") ForegroundColor = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    if (color == "purple") ForegroundColor = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    if (color == "yellow") ForegroundColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(DebugConsoleHandle, ForegroundColor);
    std::cout << text << std::endl;
    ReleaseMutex(DebugConsoleOutputMutex);
}

//
// Structs -------------------------------------------------------------------------
//

struct handle_data {
    unsigned long process_id;
    HWND window_handle;
};



//
// Technical / WinAPI Functions ----------------------------------------------------
//

BOOL is_main_window(HWND handle)
{
    return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
{
    handle_data& data = *(handle_data*)lParam;
    unsigned long process_id = 0;
    GetWindowThreadProcessId(handle, &process_id);
    if (data.process_id != process_id || !is_main_window(handle) || handle == GetConsoleWindow())
        return TRUE;
    data.window_handle = handle;
    return FALSE;
}

HWND find_main_window(unsigned long process_id)
{
    handle_data data;
    data.process_id = process_id;
    data.window_handle = 0;
    EnumWindows(enum_windows_callback, (LPARAM)&data);
    return data.window_handle;
}

HWND window;
LPARAM param = NULL;

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
    DWORD wndProcId;
    GetWindowThreadProcessId(handle, &wndProcId);

    if (GetCurrentProcessId() != wndProcId)
        return TRUE;

    window = handle;
    param = lParam;
    return FALSE;
}

BOOL CALLBACK EnumWindowsMessage(HWND handle, LPARAM lParam)
{
    SendMessage(handle, WM_INPUT, (LPARAM)handle, 0x49);
    PostMessage(handle, WM_INPUT, (LPARAM)handle, 0x49);
    return TRUE;
}

HWND GetProcessWindow()
{
    window = NULL;
    EnumWindows(EnumWindowsCallback, NULL);
    return window;
}

LPARAM GetProcessParam()
{
    window = NULL;
    EnumWindows(EnumWindowsCallback, NULL);
    return param;
}

DWORD GetProcId(const wchar_t* procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!_wcsicmp((wchar_t*)procEntry.szExeFile, procName))
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));

        }
    }
    CloseHandle(hSnap);
    return procId;
}

std::string GetProcessName()
{
    char buf[MAX_PATH];
    if (GetModuleBaseNameA(GetCurrentProcess(), NULL, buf, MAX_PATH)) {
        std::string processName(buf);
        return processName;
    }
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                
                wchar_t* target_module = _wcslwr((wchar_t*)modEntry.szModule);
                if (!_wcsicmp(target_module, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}



//
// Input handling ------------------------------------------------
//

struct GameInput
{
    bool ESC;
    bool TAB;
    bool LSHIFT;
    bool RSHIFT;
    bool CTRL;
    bool ALT;
    bool BACK;
    bool RETURN;
    bool SPACE;
    bool AUP;
    bool ARIGHT;
    bool ADOWN;
    bool ALEFT;
    bool D0;
    bool D1;
    bool D2;
    bool D3;
    bool D4;
    bool D5;
    bool D6;
    bool D7;
    bool D8;
    bool D9;
    bool A;
    bool B;
    bool C;
    bool D;
    bool E;
    bool F;
    bool G;
    bool H;
    bool I;
    bool J;
    bool K;
    bool L;
    bool M;
    bool N;
    bool O;
    bool P;
    bool Q;
    bool R;
    bool S;
    bool T;
    bool U;
    bool V;
    bool W;
    bool X;
    bool Y;
    bool Z;
    bool NUM0;
    bool NUM1;
    bool NUM2;
    bool NUM3;
    bool NUM4;
    bool NUM5;
    bool NUM6;
    bool NUM7;
    bool NUM8;
    bool NUM9;
    bool NUMDIV;
    bool NUMMUL;
    bool NUMMIN;
    bool NUMPLU;
    bool NUMRET;
    bool NUMDEL;
    bool F1;
    bool F2;
    bool F3;
    bool F4;
    bool F5;
    bool F6;
    bool F7;
    bool F8;
    bool F9;
    bool F10;
    bool F11;
    bool F12;
    bool COMMA;
    bool DOT;
    bool PLUS;
    bool MINUS;
    bool LMB;
    bool RMB;
    bool MB;
    bool ME1;
    bool ME2;
    int WHEEL;
    int MOUSEX;
    int MOUSEY;
    bool JOYA;
    bool JOYB;
    bool JOYX;
    bool JOYY;
    bool JOYSTART;
    bool JOYSELECT;
    bool JOYRB;
    bool JOYLB;
    bool JOYUP;
    bool JOYDOWN;
    bool JOYRIGHT;
    bool JOYLEFT;
    int JOYRT;
    int JOYLT;
    int JOYRAXISX;
    int JOYRAXISY;
    int JOYLAXISX;
    int JOYLAXISY;
    bool JOYRS;
    bool JOYLS;
    bool SETMOUSE;
};

struct GameInputLayout
{
    std::string ESC;
    std::string TAB;
    std::string LSHIFT;
    std::string RSHIFT;
    std::string CTRL;
    std::string ALT;
    std::string BACK;
    std::string RETURN;
    std::string SPACE;
    std::string AUP;
    std::string ARIGHT;
    std::string ADOWN;
    std::string ALEFT;
    std::string D0;
    std::string D1;
    std::string D2;
    std::string D3;
    std::string D4;
    std::string D5;
    std::string D6;
    std::string D7;
    std::string D8;
    std::string D9;
    std::string A;
    std::string B;
    std::string C;
    std::string D;
    std::string E;
    std::string F;
    std::string G;
    std::string H;
    std::string I;
    std::string J;
    std::string K;
    std::string L;
    std::string M;
    std::string N;
    std::string O;
    std::string P;
    std::string Q;
    std::string R;
    std::string S;
    std::string T;
    std::string U;
    std::string V;
    std::string W;
    std::string X;
    std::string Y;
    std::string Z;
    std::string NUM0;
    std::string NUM1;
    std::string NUM2;
    std::string NUM3;
    std::string NUM4;
    std::string NUM5;
    std::string NUM6;
    std::string NUM7;
    std::string NUM8;
    std::string NUM9;
    std::string NUMDIV;
    std::string NUMMUL;
    std::string NUMMIN;
    std::string NUMPLU;
    std::string NUMRET;
    std::string NUMDEL;
    std::string F1;
    std::string F2;
    std::string F3;
    std::string F4;
    std::string F5;
    std::string F6;
    std::string F7;
    std::string F8;
    std::string F9;
    std::string F10;
    std::string F11;
    std::string F12;
    std::string COMMA;
    std::string DOT;
    std::string PLUS;
    std::string MINUS;
    std::string LMB;
    std::string RMB;
    std::string MB;
    std::string ME1;
    std::string ME2;
    std::string WHEEL;
    std::string MOUSEX;
    std::string MOUSEY;
    std::string JOYA;
    std::string JOYB;
    std::string JOYX;
    std::string JOYY;
    std::string JOYSTART;
    std::string JOYSELECT;
    std::string JOYRB;
    std::string JOYLB;
    std::string JOYUP;
    std::string JOYDOWN;
    std::string JOYRIGHT;
    std::string JOYLEFT;
    std::string JOYRT;
    std::string JOYLT;
    std::string JOYRAXISX;
    std::string JOYRAXISY;
    std::string JOYLAXISX;
    std::string JOYLAXISY;
    std::string JOYRS;
    std::string JOYLS;
};

void MergeGameInputs(GameInput* DST, GameInput* MOUSE, GameInput* KEYBOARD, GameInput* JOYSTICK)
{
    DST->ESC = KEYBOARD->ESC;
    DST->TAB = KEYBOARD->TAB;
    DST->LSHIFT = KEYBOARD->LSHIFT;
    DST->RSHIFT = KEYBOARD->RSHIFT;
    DST->CTRL = KEYBOARD->CTRL;
    DST->ALT = KEYBOARD->ALT;
    DST->BACK = KEYBOARD->BACK;
    DST->RETURN = KEYBOARD->RETURN;
    DST->SPACE = KEYBOARD->SPACE;
    DST->AUP = KEYBOARD->SPACE;
    DST->ARIGHT = KEYBOARD->ARIGHT;
    DST->ADOWN = KEYBOARD->ADOWN;
    DST->ALEFT = KEYBOARD->ALEFT;
    DST->D0 = KEYBOARD->D0;
    DST->D1 = KEYBOARD->D1;
    DST->D2 = KEYBOARD->D2;
    DST->D3 = KEYBOARD->D3;
    DST->D4 = KEYBOARD->D4;
    DST->D5 = KEYBOARD->D5;
    DST->D6 = KEYBOARD->D6;
    DST->D7 = KEYBOARD->D7;
    DST->D8 = KEYBOARD->D8;
    DST->D9 = KEYBOARD->D9;
    DST->A = KEYBOARD->A;
    DST->B = KEYBOARD->B;
    DST->C = KEYBOARD->C;
    DST->D = KEYBOARD->D;
    DST->E = KEYBOARD->E;
    DST->F = KEYBOARD->F;
    DST->G = KEYBOARD->G;
    DST->H = KEYBOARD->H;
    DST->I = KEYBOARD->I;
    DST->J = KEYBOARD->J;
    DST->K = KEYBOARD->K;
    DST->L = KEYBOARD->L;
    DST->M = KEYBOARD->M;
    DST->N = KEYBOARD->N;
    DST->O = KEYBOARD->O;
    DST->P = KEYBOARD->P;
    DST->Q = KEYBOARD->Q;
    DST->R = KEYBOARD->R;
    DST->S = KEYBOARD->S;
    DST->T = KEYBOARD->T;
    DST->U = KEYBOARD->U;
    DST->V = KEYBOARD->V;
    DST->W = KEYBOARD->W;
    DST->X = KEYBOARD->X;
    DST->Y = KEYBOARD->Y;
    DST->Z = KEYBOARD->Z;
    DST->NUM0 = KEYBOARD->NUM0;
    DST->NUM1 = KEYBOARD->NUM1;
    DST->NUM2 = KEYBOARD->NUM2;
    DST->NUM3 = KEYBOARD->NUM3;
    DST->NUM4 = KEYBOARD->NUM4;
    DST->NUM5 = KEYBOARD->NUM5;
    DST->NUM6 = KEYBOARD->NUM6;
    DST->NUM7 = KEYBOARD->NUM7;
    DST->NUM8 = KEYBOARD->NUM8;
    DST->NUM9 = KEYBOARD->NUM9;
    DST->NUMDIV = KEYBOARD->NUMDIV;
    DST->NUMMUL = KEYBOARD->NUMMUL;
    DST->NUMMIN = KEYBOARD->NUMMIN;
    DST->NUMPLU = KEYBOARD->NUMPLU;
    DST->NUMRET = KEYBOARD->NUMRET;
    DST->NUMDEL = KEYBOARD->NUMDEL;
    DST->F1 = KEYBOARD->F1;
    DST->F2 = KEYBOARD->F2;
    DST->F3 = KEYBOARD->F3;
    DST->F4 = KEYBOARD->F4;
    DST->F5 = KEYBOARD->F5;
    DST->F6 = KEYBOARD->F6;
    DST->F7 = KEYBOARD->F7;
    DST->F8 = KEYBOARD->F8;
    DST->F9 = KEYBOARD->F9;
    DST->F10 = KEYBOARD->F10;
    DST->F11 = KEYBOARD->F11;
    DST->F12 = KEYBOARD->F12;
    DST->COMMA = KEYBOARD->COMMA;
    DST->DOT = KEYBOARD->DOT;
    DST->PLUS = KEYBOARD->PLUS;
    DST->MINUS = KEYBOARD->MINUS;
    DST->LMB = MOUSE->LMB;
    DST->RMB = MOUSE->RMB;
    DST->MB = MOUSE->MB;
    DST->ME1 = MOUSE->ME1;
    DST->ME2 = MOUSE->ME2;
    DST->WHEEL = MOUSE->WHEEL;
    DST->MOUSEX = MOUSE->MOUSEX;
    DST->MOUSEY = MOUSE->MOUSEY;
    DST->JOYA = JOYSTICK->JOYA;
    DST->JOYB = JOYSTICK->JOYB;
    DST->JOYX = JOYSTICK->JOYX;
    DST->JOYY = JOYSTICK->JOYY;
    DST->JOYSTART = JOYSTICK->JOYSTART;
    DST->JOYSELECT = JOYSTICK->JOYSELECT;
    DST->JOYRB = JOYSTICK->JOYRB;
    DST->JOYLB = JOYSTICK->JOYLB;
    DST->JOYUP = JOYSTICK->JOYUP;
    DST->JOYDOWN = JOYSTICK->JOYDOWN;
    DST->JOYRIGHT = JOYSTICK->JOYRIGHT;
    DST->JOYLEFT = JOYSTICK->JOYLEFT;
    DST->JOYRT = JOYSTICK->JOYRT;
    DST->JOYLT = JOYSTICK->JOYLT;
    DST->JOYRAXISX = JOYSTICK->JOYRAXISX;
    DST->JOYRAXISY = JOYSTICK->JOYRAXISY;
    DST->JOYLAXISX = JOYSTICK->JOYLAXISX;
    DST->JOYLAXISY = JOYSTICK->JOYLAXISY;
    DST->JOYRS = JOYSTICK->JOYRS;
    DST->JOYLS = JOYSTICK->JOYLS;
}

void LoadGameInputLayout(GameInputLayout* DST, std::string fileName)
{
    std::ifstream file(fileName);

    while (!file.eof()) {
        std::string line = "";
        std::getline(file, line);

        std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::tolower(c); });
        while (line.find(" ") != std::string::npos) line.replace(line.find(" "), 1, "");
        while (line.find(";") != std::string::npos) line.replace(line.find(";"), 1, "");

        if (line.length() > 0) {
            if (line.find("=") != std::string::npos) {
                size_t delimiter = line.find("=");
                std::string id = line.substr(0, delimiter);
                std::string map = line.substr(delimiter + 1, line.length() - delimiter - 1);

                if (id == "esc") DST->ESC = map;
                if (id == "tab") DST->TAB = map;
                if (id == "lshift") DST->LSHIFT = map;
                if (id == "rshift") DST->RSHIFT = map;
                if (id == "ctrl") DST->CTRL = map;
                if (id == "alt") DST->ALT = map;
                if (id == "back") DST->BACK = map;
                if (id == "return") DST->RETURN = map;
                if (id == "space") DST->SPACE = map;
                if (id == "aup") DST->AUP = map;
                if (id == "aright") DST->ARIGHT = map;
                if (id == "adown") DST->ADOWN = map;
                if (id == "aleft") DST->ALEFT = map;
                if (id == "d0") DST->D0 = map;
                if (id == "d1") DST->D1 = map;
                if (id == "d2") DST->D2 = map;
                if (id == "d3") DST->D3 = map;
                if (id == "d4") DST->D4 = map;
                if (id == "d5") DST->D5 = map;
                if (id == "d6") DST->D6 = map;
                if (id == "d7") DST->D7 = map;
                if (id == "d8") DST->D8 = map;
                if (id == "d9") DST->D9 = map;
                if (id == "a") DST->A = map;
                if (id == "b") DST->B = map;
                if (id == "c") DST->C = map;
                if (id == "d") DST->D = map;
                if (id == "e") DST->E = map;
                if (id == "f") DST->F = map;
                if (id == "g") DST->G = map;
                if (id == "h") DST->H = map;
                if (id == "i") DST->I = map;
                if (id == "j") DST->J = map;
                if (id == "k") DST->K = map;
                if (id == "l") DST->L = map;
                if (id == "m") DST->M = map;
                if (id == "n") DST->N = map;
                if (id == "o") DST->O = map;
                if (id == "p") DST->P = map;
                if (id == "q") DST->Q = map;
                if (id == "r") DST->R = map;
                if (id == "s") DST->S = map;
                if (id == "t") DST->T = map;
                if (id == "u") DST->U = map;
                if (id == "v") DST->V = map;
                if (id == "w") DST->W = map;
                if (id == "x") DST->X = map;
                if (id == "y") DST->Y = map;
                if (id == "z") DST->Z = map;
                if (id == "num0") DST->NUM0 = map;
                if (id == "num1") DST->NUM1 = map;
                if (id == "num2") DST->NUM2 = map;
                if (id == "num3") DST->NUM3 = map;
                if (id == "num4") DST->NUM4 = map;
                if (id == "num5") DST->NUM5 = map;
                if (id == "num6") DST->NUM6 = map;
                if (id == "num7") DST->NUM7 = map;
                if (id == "num8") DST->NUM8 = map;
                if (id == "num9") DST->NUM9 = map;
                if (id == "numdiv") DST->NUMDIV = map;
                if (id == "nummul") DST->NUMMUL = map;
                if (id == "nummin") DST->NUMMIN = map;
                if (id == "numplu") DST->NUMPLU = map;
                if (id == "numret") DST->NUMRET = map;
                if (id == "numdel") DST->NUMDEL = map;
                if (id == "f1") DST->F1 = map;
                if (id == "f2") DST->F2 = map;
                if (id == "f3") DST->F3 = map;
                if (id == "f4") DST->F4 = map;
                if (id == "f5") DST->F5 = map;
                if (id == "f6") DST->F6 = map;
                if (id == "f7") DST->F7 = map;
                if (id == "f8") DST->F8 = map;
                if (id == "f9") DST->F9 = map;
                if (id == "f10") DST->F10 = map;
                if (id == "f11") DST->F11 = map;
                if (id == "f12") DST->F12 = map;
                if (id == "comma") DST->COMMA = map;
                if (id == "dot") DST->DOT = map;
                if (id == "plus") DST->PLUS = map;
                if (id == "minus") DST->MINUS = map;
                if (id == "lmb") DST->LMB = map;
                if (id == "rmb") DST->RMB = map;
                if (id == "mb") DST->MB = map;
                if (id == "me1") DST->ME1 = map;
                if (id == "me2") DST->ME2 = map;
                if (id == "wheel") DST->WHEEL = map;
                if (id == "mousex") DST->MOUSEX = map;
                if (id == "mousey") DST->MOUSEY = map;
                if (id == "joya") DST->JOYA = map;
                if (id == "joyb") DST->JOYB = map;
                if (id == "joyx") DST->JOYX = map;
                if (id == "joyy") DST->JOYY = map;
                if (id == "joystart") DST->JOYSTART = map;
                if (id == "joyselect") DST->JOYSELECT = map;
                if (id == "joyrb") DST->JOYRB = map;
                if (id == "joylb") DST->JOYLB = map;
                if (id == "joyup") DST->JOYUP = map;
                if (id == "joydown") DST->JOYDOWN = map;
                if (id == "joyright") DST->JOYRIGHT = map;
                if (id == "joyleft") DST->JOYLEFT = map;
                if (id == "joyrt") DST->JOYRT = map;
                if (id == "joylt") DST->JOYLT = map;
                if (id == "joyraxisx") DST->JOYRAXISX = map;
                if (id == "joyraxisy") DST->JOYRAXISY = map;
                if (id == "joylaxisx") DST->JOYLAXISX = map;
                if (id == "joylaxisy") DST->JOYLAXISY = map;
                if (id == "joyrs") DST->JOYRS = map;
                if (id == "joyls") DST->JOYLS = map;
            }
        }
    }
}



//
// Conversion / Condition Functions ------------------------------------------------
//

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

template <size_t N>
int splitStringArray(std::string(&arr)[N], std::string str)
{
    int n = 0;
    std::istringstream iss(str);
    for (auto it = std::istream_iterator<std::string>(iss); it != std::istream_iterator<std::string>() && n < N; ++it, ++n) arr[n] = *it;
    return 1;
}

int splitStringVector(std::vector<std::string> &vector, std::string str, std::string del)
{
    while (str.find(del) != std::string::npos)
    {
        int index = str.find(del);
        vector.push_back(str.substr(0, index));
        str = str.substr(index + 1, str.length() - 1);
    }

    vector.push_back(str);

    return 1;
}

int SubstringsInString(std::string str, std::string sub)
{
    int count = 0;
    int nPos = str.find(sub, 0);
    while (nPos != std::string::npos)
    {
        count++;
        nPos = str.find(sub, nPos + sub.size());
    }
    return count;
}

std::string getNumberType(std::string str)
{
    try {
        size_t pos = 0;
        std::stoi(str, &pos);
        if (pos == str.length()) {
            return "int";
        }
    }
    catch (const std::invalid_argument&) {}
    catch (const std::out_of_range&) {}

    try {
        size_t pos = 0;
        std::stof(str, &pos);
        if (pos == str.length()) {
            return "float";
        }
    }
    catch (const std::invalid_argument&) {}
    catch (const std::out_of_range&) {}

    try {
        size_t pos = 0;
        std::stod(str, &pos);
        if (pos == str.length()) {
            return "double";
        }
    }
    catch (const std::invalid_argument&) {}
    catch (const std::out_of_range&) {}

    return "nan";
}

uintptr_t HexStringToAddress(std::string hex_string) {
    return (uintptr_t)std::stoll(hex_string, 0, 16);;
}

int HexStringToInt(std::string hex_string) {
    return (uintptr_t)std::stoi(hex_string, 0, 16);;
}

float HexStringToFloat(std::string hex_string) {
    float x;
    std::stringstream ss;
    ss << std::hex << hex_string;
    ss >> x;
    return x;
}

bool contains_double_or_string(const std::string& str)
{
    std::regex double_or_string_regex(R"([-+]?\d*\.\d+|\D+)"); // regular expression to match double or string
    return std::regex_match(str, double_or_string_regex);
}

bool is_digits(const std::string& str, std::string extra = "")
{
    return str.find_first_not_of("0123456789" + extra) == std::string::npos;
}

bool contains_double(const std::string& str)
{
    std::regex double_regex(R"([-+]?[0-9]*\.?[0-9]+)");
    return std::regex_match(str, double_regex);
}

bool contains_dot(const std::string& str)
{
    return str.find(".") != std::string::npos;
}

bool isHexString(std::string const& s)
{
    return s.compare(0, 2, "0x") == 0
        && s.size() > 2
        && s.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
}

int XInput2Axis(double value)
{
    return (int)round(value * 32.76);
}

int Axis2XInput(double value)
{
    if (value > 32760) value = 32760;
    return (int)floor((value + 1) / 32.76);
}

std::string GetCurrentDateTime() {
    std::stringstream ss;
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H-%M-%S");
    return ss.str();
}

// Special
#include "xNyuHooks.h"
#include "Threadhooker.h"
#include "WindowStayActive.h"
#include "Overclocker.h"

// Debug mod
#include "xNyuVariables.h"
#include "DebugSettings.h"
#include "DebugAddresses.h"
#include "DebugFunctions.h"
#include "DebugSupervisionSettings.h"
#include "DebugEditorSettings.h"
#include "DebugAddresses.h"
#include "SavefileEditor.h"
#include "DebugModGlobals.h"

// Input hooks
#include "InputHookGlobals.h"
#include "DirectInput8-Hook.h"
#include "XInput1_4-Hook.h"
#include "RawInput-Hook.h"
#include "GetMessageA-Hook.h"
#include "GetMessageW-Hook.h"
#include "SendInput-Hook.h"
#include "TASInputGlobals.h"
#include "TAS.h"

// After includes
#include "xNyuDrawingEssentials.h"
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





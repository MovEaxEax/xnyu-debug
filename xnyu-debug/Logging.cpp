#include "pch.h"
#include "GlobalSettings.h"
#include "Logging.h"



// --- Variables ---
bool DebugConsoleEnabled = false;
HANDLE DebugConsoleHandle = nullptr;
FILE* DebugConsoleFilePointer = nullptr;
HANDLE DebugConsoleOutputMutex = CreateMutex(NULL, FALSE, NULL);



// --- Functions ---
void SetDebugConsoleHandle(HANDLE handle)
{
    WaitForSingleObject(DebugConsoleOutputMutex, INFINITE);
    DebugConsoleHandle = handle;
    ReleaseMutex(DebugConsoleOutputMutex);
}

void SetDebugConsoleEnabled(bool enabled)
{
    WaitForSingleObject(DebugConsoleOutputMutex, INFINITE);
    DebugConsoleEnabled = enabled;
    ReleaseMutex(DebugConsoleOutputMutex);
}

void SetDebugConsoleFilePointer(FILE* fp)
{
    WaitForSingleObject(DebugConsoleOutputMutex, INFINITE);
    DebugConsoleFilePointer = fp;
    ReleaseMutex(DebugConsoleOutputMutex);
}

EXTERN_DLL_EXPORT void __cdecl DebugConsoleOutput(std::string text, bool dev, std::string color = "white")
{
    WaitForSingleObject(DebugConsoleOutputMutex, INFINITE);
    if (!DebugConsoleEnabled)
    {
        ReleaseMutex(DebugConsoleOutputMutex);
        return;
    }
    if (dev && !IsDevMode())
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



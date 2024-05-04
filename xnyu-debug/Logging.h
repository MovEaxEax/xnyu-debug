#pragma once

// --- Structs ---
enum DEBUG_CONSOLE_COLOR : int
{
	WHITE = 0,
	RED = 1,
	GREEN = 2,
	BLUE = 3,
	PURPLE = 4,
	YELLOW = 5
};

// --- Variables ---
extern bool DebugConsoleEnabled;
extern HANDLE DebugConsoleHandle;
extern FILE* DebugConsoleFilePointer;
extern HANDLE DebugConsoleOutputMutex;

// --- Functions ---
void SetDebugConsoleHandle(HANDLE handle);
void SetDebugConsoleEnabled(bool enabled);
void SetDebugConsoleFilePointer(FILE* fp);
EXTERN_DLL_EXPORT void __stdcall DebugConsoleOutput(std::string text, bool dev = false, DEBUG_CONSOLE_COLOR color = DEBUG_CONSOLE_COLOR::WHITE);



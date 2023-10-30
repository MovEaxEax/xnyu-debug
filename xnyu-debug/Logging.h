#pragma once

// --- Variables ---
extern bool DebugConsoleEnabled;
extern HANDLE DebugConsoleHandle;
extern FILE* DebugConsoleFilePointer;
extern HANDLE DebugConsoleOutputMutex;

// --- Functions ---
void SetDebugConsoleHandle(HANDLE handle);
void SetDebugConsoleEnabled(bool enabled);
void SetDebugConsoleFilePointer(FILE* fp);
void __cdecl DebugConsoleOutput(std::string text, bool dev, std::string color);



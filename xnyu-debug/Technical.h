#pragma once

// --- Structs ---
struct CallbackHandleData {
    unsigned long pid;
    HWND windowHandle;
};

struct Point
{
    float x;
    float y;
};



// --- Functions ---
BOOL CALLBACK FindMainWindowHandleCallback(HWND handle, LPARAM lParam);
HWND FindMainWindowHandle(unsigned long pid);
int FindMainThreadID(unsigned long pid);
std::string GetProcessName();
Point PointConversion(POINT point);
Point PointCreate(float x, float y);



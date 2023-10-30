#include "pch.h"
#include "Technical.h"
#include "Winactive.h"



// --- Functions ---
BOOL CALLBACK FindMainWindowHandleCallback(HWND handle, LPARAM lParam)
{
    CallbackHandleData& data = *(CallbackHandleData*)lParam;
    unsigned long pid = 0;
    GetWindowThreadProcessId(handle, &pid);
    if (data.pid != pid || !(GetWindowReal(handle, GW_OWNER) == (HWND)0 && IsWindowVisibleReal(handle)) || handle == GetConsoleWindow()) return true;
    data.windowHandle = handle;
    return false;
}

HWND FindMainWindowHandle(unsigned long pid)
{
    CallbackHandleData data;
    data.pid = pid;
    data.windowHandle = 0;
    EnumWindows(FindMainWindowHandleCallback, (LPARAM)&data);
    return data.windowHandle;
}

int FindMainThreadID(unsigned long pid) {
    DWORD mainThreadID = 0;
    DWORD lowestThreadID = MAXDWORD;

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        THREADENTRY32 te;
        te.dwSize = sizeof(THREADENTRY32);
        if (Thread32First(hSnapshot, &te)) {
            do {
                if (te.th32OwnerProcessID == (DWORD)pid) {
                    if (te.th32ThreadID < lowestThreadID) {
                        lowestThreadID = te.th32ThreadID;
                        mainThreadID = te.th32ThreadID;
                    }
                }
                te.dwSize = sizeof(THREADENTRY32);
            } while (Thread32Next(hSnapshot, &te));
        }
        CloseHandle(hSnapshot);
    }

    return (int)mainThreadID;
}

std::string GetProcessName()
{
    char buf[MAX_PATH];
    if (GetModuleBaseNameA(GetCurrentProcess(), NULL, buf, MAX_PATH)) {
        std::string processName(buf);
        return processName;
    }
}

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



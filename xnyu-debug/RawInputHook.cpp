#include "pch.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "InputLayout.h"
#include "xNyuHook.h"
#include "RawInputHook.h"



// --- Variables ---
GetRawInputDataT pGetRawInputData = nullptr;



// --- GetRawInputData Hook ---
GetRawInputDataHook<GetRawInputDataT>* GetRawInputDataHook<GetRawInputDataT>::instance = nullptr;
UINT GetRawInputDataReal(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
{
    if (GetRawInputDataHook<GetRawInputDataT>::instance && GetRawInputDataHook<GetRawInputDataT>::instance->isActive()) return GetRawInputDataHook<GetRawInputDataT>::instance->callTrampoline(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);
    return pGetRawInputData(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);
}



// --- Functions ---
bool GetRawInputDataHookInit()
{
    HMODULE RawInputDllHandle = GetModuleHandleA("User32.dll");
    if (RawInputDllHandle == NULL) return false;

    pGetRawInputData = (GetRawInputDataT)GetProcAddress(RawInputDllHandle, "GetRawInputData");
    if (!GetRawInputDataHook<GetRawInputDataT>::instance) GetRawInputDataHook<GetRawInputDataT>::instance = new GetRawInputDataHook<GetRawInputDataT>((void*)pGetRawInputData);
    else return false;

    return true;
}

bool GetRawInputDataHookUninit()
{
    if (GetRawInputDataHook<GetRawInputDataT>::instance && GetRawInputDataHook<GetRawInputDataT>::instance->isActive()) GetRawInputDataHook<GetRawInputDataT>::instance->remove();
    else return false;

    return true;
}

bool IsRawInputDataHookActive()
{
    return GetRawInputDataHook<GetRawInputDataT>::instance && GetRawInputDataHook<GetRawInputDataT>::instance->isActive();
}



#include "pch.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "InputLayout.h"
#include "xNyuHook.h"
#include "XInputHook.h"



// --- Variables ---
XInputGetStateT pXInputGetState;



// --- XInputGetState Hook ---
XInputGetStateHook<XInputGetStateT>* XInputGetStateHook<XInputGetStateT>::instance = nullptr;
DWORD XInputGetStateReal(DWORD dwUserIndex, XINPUT_STATE* pState)
{
	if (XInputGetStateHook<XInputGetStateT>::instance && XInputGetStateHook<XInputGetStateT>::instance->isActive()) return XInputGetStateHook<XInputGetStateT>::instance->callTrampoline(dwUserIndex, pState);
	return pXInputGetState(dwUserIndex, pState);
}



// --- Functions ---
bool XInputHookInit()
{
    HMODULE XInputDllHandle = GetModuleHandleA("xinput1_4.dll");
    if (XInputDllHandle == NULL)
    {
        XInputDllHandle = GetModuleHandleA("xinput1_3.dll");
        if (XInputDllHandle == NULL) return false;
    }

    pXInputGetState = (XInputGetStateT)GetProcAddress(XInputDllHandle, "XInputGetState");
    if (!XInputGetStateHook<XInputGetStateT>::instance) XInputGetStateHook<XInputGetStateT>::instance = new XInputGetStateHook<XInputGetStateT>((void*)pXInputGetState);
    else return false;

    return true;
}

bool XInputHookUninit()
{
    if (XInputGetStateHook<XInputGetStateT>::instance && XInputGetStateHook<XInputGetStateT>::instance->isActive()) XInputGetStateHook<XInputGetStateT>::instance->remove();
    else return false;

    return true;
}

bool IsXInputHookActive()
{
    return XInputGetStateHook<XInputGetStateT>::instance && XInputGetStateHook<XInputGetStateT>::instance->isActive();
}



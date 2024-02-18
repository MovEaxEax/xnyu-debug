#include "pch.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "InputLayout.h"
#include "xNyuHook.h"
#include "DirectInput8Hook.h"



// --- Variables ---
DirectInput8GetDeviceStateT pDirectInput8GetDeviceState = nullptr;



// --- DirectInput8GetDeviceState Hook ---
DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>* DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance = nullptr;
HRESULT DirectInput8GetDeviceStateReal(IDirectInputDevice8* pDevice, DWORD cbData, LPVOID lpvData)
{
    if (DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance && DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->isActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->callTrampoline(pDevice, cbData, lpvData);
    return pDirectInput8GetDeviceState(pDevice, cbData, lpvData);
}



// --- Functions ---
bool DirectInput8HookInit()
{
    HMODULE DInput8DllHandle = GetModuleHandleA("dinput8.dll");
    if (DInput8DllHandle == NULL) return false;

    IDirectInput8* DirectInputDummyInterface = nullptr;
    LPDIRECTINPUTDEVICE8 DirectInput8DummyDevice = nullptr;

    if (DirectInput8Create(GetMainDllHandle(), 0x0800, IID_IDirectInput8, (LPVOID*)&DirectInputDummyInterface, NULL) != DI_OK) {
        DebugConsoleOutput("Error: DirectInput8Create() failed!", false, "red");
        return false;
    }

    if (DirectInputDummyInterface->CreateDevice(GUID_SysMouse, &DirectInput8DummyDevice, NULL) != DI_OK) {
        DebugConsoleOutput("Error: CreateDeviceDirectInput8() failed!", false, "red");
        DirectInputDummyInterface->Release();
        return false;
    }

    uintptr_t avTable = Internal::Memory::read<uintptr_t>(DirectInputDummyInterface);
    uintptr_t pFunction = avTable + 9 * sizeof(uintptr_t);
    void* address = Internal::Memory::read<void*>(pFunction);
    pDirectInput8GetDeviceState = (DirectInput8GetDeviceStateT)address;
    if (!DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance = new DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>(address);
    else return false;

    DirectInputDummyInterface->Release();
    DirectInput8DummyDevice->Release();

    return true;
}

bool DirectInput8HookUninit()
{
    if (DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance && DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->isActive()) DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->remove();
    else return false;

    return true;
}

bool IsDirectInput8HookActive()
{
    return DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance && DirectInput8GetDeviceStateHook<DirectInput8GetDeviceStateT>::instance->isActive();
}



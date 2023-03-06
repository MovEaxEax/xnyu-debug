#pragma once

// Global hook settings
typedef BOOL(__stdcall* GetMessageWT)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
GetMessageWT pGetMessageW = nullptr;

subhook::Hook GetMessageWSubhook;

void* GetMessageWOriginalAddress;
void* GetMessageWHookAddress;

bool GetMessageWSendInformation = false;
bool GetMessageWDisableForGame = false;

GameInput GetMessageWGameInputCurrent;
GameInput GetMessageWGameInputLast;

// Specific settings



BOOL __stdcall GetMessageWHook(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
    // Remove hook to restore original function
    GetMessageWSubhook.Remove();

    // The return value of this function
    BOOL result = pGetMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
    
    if (WindowStayActiveMode)
    {
    }

    if (GetMessageWSendInformation)
    {

    }
    else
    {
        if (GetMessageWDisableForGame)
        {

        }
    }

    // Init Hook again
    if (sizeof(void*) == 8) GetMessageWSubhook.Install(GetMessageWOriginalAddress, GetMessageWHookAddress, subhook::HookFlags::HookFlag64BitOffset);
    if (sizeof(void*) == 4) GetMessageWSubhook.Install(GetMessageWOriginalAddress, GetMessageWHookAddress);

    return result;
}



BOOL GetMessageWHookInit()
{
    // Detect the XInput module handle
    HMODULE GetMessageWDllHandle = GetModuleHandleA("User32.dll");
    if (GetMessageWDllHandle == NULL) return false;

    // Set the hook addresses
    GetMessageWOriginalAddress = (void*)GetProcAddress(GetMessageWDllHandle, "GetMessageW");
    GetMessageWHookAddress = (void*)GetMessageWHook;
    pGetMessageW = (GetMessageWT)GetMessageWOriginalAddress;

    if (sizeof(void*) == 8) GetMessageWSubhook.Install(GetMessageWOriginalAddress, GetMessageWHookAddress, subhook::HookFlags::HookFlag64BitOffset);
    if (sizeof(void*) == 4) GetMessageWSubhook.Install(GetMessageWOriginalAddress, GetMessageWHookAddress);

    return true;
}

BOOL GetMessageWHookUninit()
{
    GetMessageWSubhook.Remove();
    return true;
}

void InitPlayGetMessageWTAS()
{
    GetMessageWSendInformation = true;

}

void UninitPlayGetMessageWTAS()
{
    GetMessageWSendInformation = false;

}

void InitRecordGetMessageWTAS()
{
}

void UninitRecordGetMessageWTAS()
{
}

GameInput GetMessageWInput(BOOL TAS)
{
    if (InputDriverMouseGet == InputDriverz::G3TM3SSAGEW)
    {

    }

    if (InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEW)
    {

    }

    return GetMessageWGameInputCurrent;
}

void SetMessageWInput(GameInput GetMessageWGameInput, BOOL TAS)
{
    if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEW)
    {

    }

    if (InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEW)
    {

    }
}



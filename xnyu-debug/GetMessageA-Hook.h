#pragma once

// Global hook settings
typedef BOOL(__stdcall* GetMessageAT)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
GetMessageAT pGetMessageA = nullptr;

subhook::Hook GetMessageASubhook;

void* GetMessageAOriginalAddress;
void* GetMessageAHookAddress;

bool GetMessageASendInformation = false;
bool GetMessageADisableForGame = false;

GameInput GetMessageAGameInputCurrent;
GameInput GetMessageAGameInputLast;

// Specific settings



BOOL __stdcall GetMessageAHook(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
    // Remove hook to restore original function
    GetMessageASubhook.Remove();

    // The return value of this function
    BOOL result = pGetMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);

    if (WindowStayActiveMode)
    {
    }

    if (GetMessageASendInformation)
    {

    }
    else
    {
        if (GetMessageADisableForGame)
        {

        }
    }

    // Init Hook again
    if (sizeof(void*) == 8) GetMessageASubhook.Install(GetMessageAOriginalAddress, GetMessageAHookAddress, subhook::HookFlags::HookFlag64BitOffset);
    if (sizeof(void*) == 4) GetMessageASubhook.Install(GetMessageAOriginalAddress, GetMessageAHookAddress);

    return result;
}



BOOL GetMessageAHookInit()
{
    // Detect the XInput module handle
    HMODULE GetMessageADllHandle = GetModuleHandleA("User32.dll");
    if (GetMessageADllHandle == NULL) return false;

    // Set the hook addresses
    GetMessageAOriginalAddress = (void*)GetProcAddress(GetMessageADllHandle, "GetMessageA");
    GetMessageAHookAddress = (void*)GetMessageAHook;
    pGetMessageA = (GetMessageAT)GetMessageAOriginalAddress;

    if (sizeof(void*) == 8) GetMessageASubhook.Install(GetMessageAOriginalAddress, GetMessageAHookAddress, subhook::HookFlags::HookFlag64BitOffset);
    if (sizeof(void*) == 4) GetMessageASubhook.Install(GetMessageAOriginalAddress, GetMessageAHookAddress);

    return true;
}

BOOL GetMessageAHookUninit()
{
    GetMessageASubhook.Remove();
    return true;
}

void InitPlayGetMessageATAS()
{
    GetMessageASendInformation = true;

}

void UninitPlayGetMessageATAS()
{
    GetMessageASendInformation = false;

}

void InitRecordGetMessageATAS()
{
}

void UninitRecordGetMessageATAS()
{
}

GameInput GetMessageAInput(BOOL TAS)
{
    if (InputDriverMouseGet == InputDriverz::G3TM3SSAGEA)
    {

    }

    if (InputDriverKeyboardGet == InputDriverz::G3TM3SSAGEA)
    {

    }

    return GetMessageAGameInputCurrent;
}

void SetMessageAInput(GameInput GetMessageAGameInput, BOOL TAS)
{
    if (InputDriverMouseSet == InputDriverz::G3TM3SSAGEA)
    {

    }

    if (InputDriverKeyboardSet == InputDriverz::G3TM3SSAGEA)
    {

    }
}



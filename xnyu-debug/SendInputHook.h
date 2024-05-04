#pragma once

// --- Variable ---
extern INPUT SendInputstateMouseSet[];
extern int SendInputstateMouseSetAmount;
extern bool SendInputstateMouseSetDone;

extern INPUT SendInputstateKeyboardSet[];
extern int SendInputstateKeyboardSetAmount;
extern bool SendInputstateKeyboardSetDone;

extern HANDLE SendInputThreadHandle;

extern bool SendInputThreadAlive;
extern HANDLE SendInputAliveMutex;



// -- Functions ---
void SetSendInputThreadAlive(bool value);
bool IsSendInputThreadAlive();
void SendInputSetKeyboard(GameInput& input, GameInput& inputLast);
void SendInputSetMouse(GameInput& input, GameInput& inputLast);
bool SendInputHookInit();
bool SendInputHookUninit();
bool IsSendInputHookActive();
DWORD __stdcall SendInputThread();



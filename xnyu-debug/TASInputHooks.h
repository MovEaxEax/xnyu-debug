#pragma once

// --- Variables ---
extern bool TASIgnoreMouseInput;

// --- Functions ---
bool SetTASInputEnabled(bool value);
bool GetTASInput(GameInput& input);
bool SetTASInput(GameInput& input, GameInput& inputLast);
bool InitTASInputHooks();
bool UninitInputHooks();



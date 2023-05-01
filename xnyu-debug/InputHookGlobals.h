#pragma once

enum InputDriverz {
	N0NE = -1,
	RAW1NPUT = 0,
	DIRECT1NPUT8 = 1,
	X1NPUT1_4 = 2,
	G3TM3SSAGEA = 3,
	G3TM3SSAGEW = 4,
	S3ND1NPUT = 5,
};

InputDriverz InputDriverKeyboardGet = InputDriverz::N0NE;
InputDriverz InputDriverMouseGet = InputDriverz::N0NE;
InputDriverz InputDriverJoystickGet = InputDriverz::N0NE;

InputDriverz InputDriverKeyboardSet = InputDriverz::N0NE;
InputDriverz InputDriverMouseSet = InputDriverz::N0NE;
InputDriverz InputDriverJoystickSet = InputDriverz::N0NE;

bool TASRecordFrameByFrameInputTrigger = false;

bool TASSynchronizerCanSend = false;
int TASSynchronizerFinishedCurrent = 0;
int TASSynchronizerFinishedMax = 0;

struct TASSync {
	bool RawInputKeyboardGet;
	bool RawInputMouseGet;
	bool RawInputJoystickGet;
	bool RawInputKeyboardSend;
	bool RawInputMouseSend;
	bool RawInputJoystickSend;

	bool DirectInput8KeyboardGet;
	bool DirectInput8MouseGet;
	bool DirectInput8JoystickGet;
	bool DirectInput8KeyboardSend;
	bool DirectInput8MouseSend;
	bool DirectInput8JoystickSend;

	bool XInput1_4JoystickGet;
	bool XInput1_4JoystickSend;

	bool GetMessageAKeyboardGet;
	bool GetMessageAMouseGet;
	bool GetMessageAKeyboardSend;
	bool GetMessageAMouseSend;

	bool GetMessageWKeyboardGet;
	bool GetMessageWMouseGet;
	bool GetMessageWKeyboardSend;
	bool GetMessageWMouseSend;

	bool SendInputKeyboardGet;
	bool SendInputMouseGet;
	bool SendInputKeyboardSend;
	bool SendInputMouseSend;
};

TASSync TASSynchronizer;

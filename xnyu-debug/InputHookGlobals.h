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
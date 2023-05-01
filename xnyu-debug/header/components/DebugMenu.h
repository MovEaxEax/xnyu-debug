#pragma once

std::string DebugMenuVersion = "v1.0";

struct DebugFontStyle {
	std::string fontsize;
	std::string color;
	int alpha;
};

struct DebugRawInput {
	int device;
	int key;
	int x;
	int y;
};

// Typedefs
typedef void(__stdcall* DebugDrawT)();
DebugDrawT DebugDraw = nullptr;

// Essential data
DebugRawInput DebugRawInputData;
float DebugWidthFactor = 1;
float DebugHeightFactor = 1;
bool DebugMenuOpened = false;

// Triggers
bool DebugMenuInit = false;

// Input toggle
bool RawInputCanAttach = false;
bool RawInputIsAttached = false;

// Modes
bool DebugMenuShowValuesMode = false;
bool DebugMenuSuperVisionMode = false;
bool DebugMenuSettingsPerformanceMode = false;


int DebugMenuShowValuesModeUpdateIntervall = 200;
std::vector<std::string> DebugMenuShowValuesModeData;

bool DebugMenuInitSwitch = true;
bool DebugMenuCanDraw = true;
int DebugMenuGeneralFrameskip = 2;
int DebugMenuGeneralFrameskipFactor = 2;
int DebugMenuSettingsPerformanceModeFrameskipFactor = 0;
int DebugMenuNotImportantSettingsFrameSkip = 0;

// Cursor
POINT DebugMenuCursorPosition;

// Menu Selector

std::vector<DebugFunction> DebugMenuHotkeys;
std::vector<std::string> DebugMenuParameter;
int DebugMenuParameterFocus = -1;
int DebugMenuFunctionFocus = -1;

std::vector<RECT> DebugMenuEmptyHoverBoxes;
std::vector<RECT> DebugMenuOverviewHoverBoxes;
std::vector<RECT> DebugMenuDebugAddressesParentsHoverBoxes;
std::vector<std::vector<RECT>> DebugMenuDebugAddressesChildsHoverBoxes;
std::vector<RECT> DebugMenuDebugFunctionsParentsHoverBoxes;
std::vector<std::vector<RECT>> DebugMenuDebugFunctionsChildsHoverBoxes;
std::vector<RECT> DebugMenuSavefileEditorFilesHoverBoxes;
std::vector<RECT> DebugMenuSavefileEditorParentsHoverBoxes;
std::vector<std::vector<RECT>> DebugMenuSavefileEditorChildsHoverBoxes;


int DebugMenuDebugAddressesParentFocus = 0;
int DebugMenuDebugFunctionsParentFocus = 0;
std::vector<DebugAddress> DebugMenuDebugAddressShowValues;
bool DebugMenuDebugAddressShowValuesInit = false;
int DebugMenuDebugAddressShowValuesBackWidth = 0;
int DebugMenuDebugAddressShowValuesBackHeight = 0;
int DebugMenuDebugAddressShowValuesMaxCol = 25;
int DebugMenuDebugAddressShowValuesMaxRow = 5;
int* DebugMenuDebugAddressShowValuesRowWidth = new int[DebugMenuDebugAddressShowValuesMaxRow];
int DebugMenuDebugAddressShowValuesRowHeight = 0;

// Forms
DEBUGMENUFORM DebugMenuMainForm = DEBUGMENUFORM::FORM_NONE;
int DebugMenuSubForm = 0;
DEBUGMENUFORM DebugMenuMainFormLast = DEBUGMENUFORM::FORM_NONE;
int DebugMenuSubFormLast = 0;

GameInput DebugInputCurrent = GameInput();
GameInput DebugInputLast = GameInput();

void DebugMenuInitForms()
{
	if (DebugMenuMainForm == DEBUGMENUFORM::FORM_OVERVIEW)
	{
		DebugMenuParameterFocus = -1;
		DebugMenuFunctionFocus = -1;
		SavefileParentFocus = -1;
		SavefileParentFocus = -1;
	}

	if (DebugMenuMainForm == DEBUGMENUFORM::FORM_DEBUGVALUES)
	{

	}

	if (DebugMenuMainForm == DEBUGMENUFORM::FORM_DEBUGFUNCTIONS)
	{

	}

	if (DebugMenuMainForm == DEBUGMENUFORM::FORM_SAVEFILEEDITOR)
	{

	}

}

void DebugMenuMockData()
{

	DebugMenuOpened = false;
}

void DebugMenuInitHoverBoxes()
{
	int col = 0;
	int row = 0;

	// Overview
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 58, 252, 274, 292 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 282, 252, 499, 292 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 58, 364, 274, 404 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 58, 487, 274, 527 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 58, 977, 274, 1018 });
	for (int i = 0; i < 13; i++)
	{
		DebugMenuOverviewHoverBoxes.push_back(RECT{ 1065, 195 + (65 * i), 1435, 195 + (65 * i) + 29});
		DebugMenuOverviewHoverBoxes.push_back(RECT{ 1065, 195 + (65 * i) + 29, 1435, 195 + (65 * i) + 29 + 28});
	}
	for (int i = 0; i < 12; i++)
	{
		DebugMenuOverviewHoverBoxes.push_back(RECT{ 1505, 195 + (65 * i), 1875, 195 + (65 * i) + 29 });
		DebugMenuOverviewHoverBoxes.push_back(RECT{ 1505, 195 + (65 * i) + 29, 1875, 195 + (65 * i) + 29 + 28 });
	}

	// Debug addresses
	DebugMenuDebugAddressesParentsHoverBoxes.push_back(RECT{ 63, 975, 279, 1016 });

	col = 0;
	row = 0;
	for (int i = 0; i < DebugAddresses.size(); i++)
	{
		DebugMenuDebugAddressesParentsHoverBoxes.push_back(RECT{ 60 + (360 * row), 165 + (30 * col), 60 + (360 * row) + 360, 165 + (30 * col) + 30 });
		col++;
		if (col == 25)
		{
			col = 0;
			row++;
		}

		int ccol = 0;
		int crow = 0;
		std::vector<RECT> childrenRects;
		childrenRects.push_back(RECT{ 63, 975, 279, 1016 });
		for (int k = 0; k < DebugAddresses[i].addresses.size(); k++)
		{
			childrenRects.push_back(RECT{ 60 + (360 * crow), 165 + (30 * ccol), 60 + (360 * crow) + 360, 165 + (30 * ccol) + 30 });
			ccol++;
			if (ccol == 25)
			{
				ccol = 0;
				crow++;
			}
		}
		DebugMenuDebugAddressesChildsHoverBoxes.push_back(childrenRects);
	}

	// Debug functions
	DebugMenuDebugFunctionsParentsHoverBoxes.push_back(RECT{ 63, 975, 279, 1016 });

	col = 0;
	row = 0;
	for (int i = 0; i < DebugFunctions.size(); i++)
	{
		DebugMenuDebugFunctionsParentsHoverBoxes.push_back(RECT{ 60 + (360 * row), 165 + (30 * col), 60 + (360 * row) + 360, 165 + (30 * col) + 30 });
		col++;
		if (col == 25)
		{
			col = 0;
			row++;
		}

		int ccol = 0;
		int crow = 0;
		std::vector<RECT> childrenRects;
		childrenRects.push_back(RECT{ 63, 975, 279, 1016 });
		for (int k = 0; k < DebugFunctions[i].functions.size(); k++)
		{
			childrenRects.push_back(RECT{ 60 + (360 * crow), 165 + (30 * ccol), 60 + (360 * crow) + 360, 165 + (30 * ccol) + 30 });
			ccol++;
			if (ccol == 25)
			{
				ccol = 0;
				crow++;
			}
		}
		DebugMenuDebugFunctionsChildsHoverBoxes.push_back(childrenRects);
	}

	// Savefile editor
	DebugMenuSavefileEditorParentsHoverBoxes.push_back(RECT{ 63, 975, 279, 1016 });

	col = 0;
	row = 0;
	for (int i = 0; i < SavefileParents.size(); i++)
	{
		DebugMenuSavefileEditorParentsHoverBoxes.push_back(RECT{ 60 + (360 * row), 165 + (30 * col), 60 + (360 * row) + 360, 165 + (30 * col) + 30 });
		col++;
		if (col == 25)
		{
			col = 0;
			row++;
		}

		int ccol = 0;
		int crow = 0;
		std::vector<RECT> childrenRects;
		childrenRects.push_back(RECT{ 63, 975, 279, 1016 });
		childrenRects.push_back(RECT{ 710, 975, 926, 1016 });
		childrenRects.push_back(RECT{ 988, 975, 1024, 1016 });
		for (int k = 0; k < SavefileParents[i].fields.size(); k++)
		{
			childrenRects.push_back(RECT{ 60 + (360 * crow), 165 + (60 * ccol), 60 + (360 * crow) + 360, 165 + (60 * ccol) + 30 });
			childrenRects.push_back(RECT{ 60 + (360 * crow), 165 + (60 * ccol) + 30, 60 + (360 * crow) + 360, 165 + (60 * ccol) + 60 });
			ccol++;
			if (ccol == 12)
			{
				ccol = 0;
				crow++;
			}
		}
		DebugMenuSavefileEditorChildsHoverBoxes.push_back(childrenRects);
	}





}

void DebugMenuInitHotkeys()
{
	DebugFunction tmp;
	tmp.nameFull = "- EMPTY -";
	for (int i = 0; i < 25; i++) DebugMenuHotkeys.push_back(tmp);
	for (int i = 0; i < 25; i++) DebugMenuParameter.push_back("");
}

void DebugMenuInitSaveEditor()
{

}


void DebugMenuInitSettings()
{
	std::ifstream file(GlobalSettings.config_debugconfig_directory + "hotkeys.txt");

	if (file.good())
	{
		std::string script = "";

		while (!file.eof()) {

			// Read line
			std::string line = "";
			std::getline(file, line);

			//Declare Substrings
			std::string substring_instruction = "";
			std::string substring_iterations = "";

			// Check if line contains content
			if (line.length() > 0) {
				std::string key = line.substr(0, line.find("="));
				std::string func = line.substr(line.find("=") + 1, line.find(";") - (line.find("=") + 1));
				if (func != "")
				{
					int index = 0;
					if (key == "NUM_1") index = 0;
					if (key == "NUM_2") index = 1;
					if (key == "NUM_3") index = 2;
					if (key == "NUM_4") index = 3;
					if (key == "NUM_5") index = 4;
					if (key == "NUM_6") index = 5;
					if (key == "NUM_7") index = 6;
					if (key == "NUM_8") index = 7;
					if (key == "NUM_9") index = 8;
					if (key == "NUM_/") index = 9;
					if (key == "NUM_*") index = 10;
					if (key == "NUM_-") index = 11;
					if (key == "NUM_+") index = 12;
					if (key == "F1") index = 13;
					if (key == "F2") index = 14;
					if (key == "F3") index = 15;
					if (key == "F4") index = 16;
					if (key == "F5") index = 17;
					if (key == "F6") index = 18;
					if (key == "F7") index = 19;
					if (key == "F8") index = 20;
					if (key == "F9") index = 21;
					if (key == "F10") index = 22;
					if (key == "F11") index = 23;
					if (key == "F12") index = 24;

					std::string parentName = func.substr(0, func.find("."));
					std::string childName = func.substr(func.find(".") + 1, func.find("(") - (func.find(".") + 1));
					std::string paramsAll = func.substr(func.find("(") + 1, func.find(")") - (func.find("(") + 1));

					for (int i = 0; i < DebugFunctions.size(); i++)
					{
						if (DebugFunctions[i].nameParent == parentName)
						{
							for (int k = 0; k < DebugFunctions[i].functions.size(); k++)
							{
								if (DebugFunctions[i].functions[k].nameChild == childName)
								{
									DebugMenuHotkeys[index] = DebugFunctions[i].functions[k];
									DebugMenuParameter[index] = paramsAll;
									break;
								}
							}
						}
					}
				}
			}

		}

		file.close();
	}

	// Update debug function parameter
	for (int i = 0; i < DebugMenuHotkeys.size(); i++)
	{
		if (DebugMenuHotkeys[i].nameFull != "- EMPTY -")
		{
			if (DebugMenuParameter[i] != "")
			{
				if (DebugMenuHotkeys[i].parameter.size() > 0)
				{
					std::string paramCopy = DebugMenuParameter[i];
					int index = 0;
					bool quote = false;
					while (index < paramCopy.length())
					{
						if (paramCopy[index] == '\"' || paramCopy[index] == '\'')
						{
							quote = !quote;
							paramCopy.replace(index, 1, "");
						}
						if (paramCopy[index] == ' ' && !quote)
						{
							paramCopy.replace(index, 1, "");
						}
						else
						{
							index++;
						}
					}

					if (paramCopy == "")
					{
						for (int k = 0; k < DebugMenuHotkeys[i].parameter.size(); k++) SetVariable(&DebugMenuHotkeys[i].parameter[k], "none");
					}
					else
					{
						std::vector<std::string> params;
						splitStringVector(params, paramCopy, ",");
						for (int k = 0; k < params.size(); k++)
						{
							if (params[k] == "")
							{
								SetVariable(&DebugMenuHotkeys[i].parameter[k], "none");
							}
							else
							{
								if (DebugMenuHotkeys[i].parameter[k].type.find("float") != std::string::npos && params[k].find(".") == std::string::npos) params[k] = params[k] + ".0";
								SetVariable(&DebugMenuHotkeys[i].parameter[k], params[k]);
							}
							if (k + 1 > DebugMenuHotkeys[i].parameter.size()) break;
						}
					}
				}
			}
		}
	}

}

void DebugMenuInitValues()
{
	DebugMenuMockData();
	DebugMenuInitHotkeys();
	DebugMenuInitSaveEditor();
	DebugMenuInitSettings();
	DebugMenuInitHoverBoxes();

	DebugConsoleOutput("Debug menu init successfull!", false, "green");
	DebugMenuInit = true;
}

BOOLEAN CheckWindowActive()
{
	GetForegroundWindowReal = true;
	return GetForegroundWindow() == MainWindowHandle;
}

// Wrapper function
void __cdecl _DebugDrawText(std::string text, int x, int y, HFONT font, unsigned char* color, float alpha, std::string align = "left")
{
	unsigned char alphaC = (unsigned char)(alpha * 255);
	DrawTextToTexture(x, y, text, font, color, alphaC, align);
}

void __cdecl _DebugDrawRectangle(int x, int y, int w, int h, unsigned char* color, float alpha)
{
	unsigned char alphaC = (unsigned char)(alpha * 255);
	DrawRectangleToTexture(x, y, w, h, color, alphaC);
}

void _DrawMenu()
{
	// Draw the surface
	DebugDraw();
}

BOOL DebugKeyPressed(std::string id, bool rapid = false)
{
	if (id == "esc") return DebugInputCurrent.ESC && (rapid ? true : !DebugInputLast.ESC);
	if (id == "tab") return DebugInputCurrent.TAB && (rapid ? true : !DebugInputLast.TAB);
	if (id == "lshift") return DebugInputCurrent.LSHIFT && (rapid ? true : !DebugInputLast.LSHIFT);
	if (id == "rshift") return DebugInputCurrent.RSHIFT && (rapid ? true : !DebugInputLast.RSHIFT);
	if (id == "ctrl") return DebugInputCurrent.CTRL && (rapid ? true : !DebugInputLast.CTRL);
	if (id == "alt") return DebugInputCurrent.ALT && (rapid ? true : !DebugInputLast.ALT);
	if (id == "back") return DebugInputCurrent.BACK && (rapid ? true : !DebugInputLast.BACK);
	if (id == "return") return DebugInputCurrent.RETURN && (rapid ? true : !DebugInputLast.RETURN);
	if (id == "space") return DebugInputCurrent.SPACE && (rapid ? true : !DebugInputLast.SPACE);
	if (id == "aup") return DebugInputCurrent.AUP && (rapid ? true : !DebugInputLast.AUP);
	if (id == "aright") return DebugInputCurrent.ARIGHT && (rapid ? true : !DebugInputLast.ARIGHT);
	if (id == "adown") return DebugInputCurrent.ADOWN && (rapid ? true : !DebugInputLast.ADOWN);
	if (id == "aleft") return DebugInputCurrent.ALEFT && (rapid ? true : !DebugInputLast.ALEFT);
	if (id == "d0") return DebugInputCurrent.D0 && (rapid ? true : !DebugInputLast.D0);
	if (id == "d1") return DebugInputCurrent.D1 && (rapid ? true : !DebugInputLast.D1);
	if (id == "d2") return DebugInputCurrent.D2 && (rapid ? true : !DebugInputLast.D2);
	if (id == "d3") return DebugInputCurrent.D3 && (rapid ? true : !DebugInputLast.D3);
	if (id == "d4") return DebugInputCurrent.D4 && (rapid ? true : !DebugInputLast.D4);
	if (id == "d5") return DebugInputCurrent.D5 && (rapid ? true : !DebugInputLast.D5);
	if (id == "d6") return DebugInputCurrent.D6 && (rapid ? true : !DebugInputLast.D6);
	if (id == "d7") return DebugInputCurrent.D7 && (rapid ? true : !DebugInputLast.D7);
	if (id == "d8") return DebugInputCurrent.D8 && (rapid ? true : !DebugInputLast.D8);
	if (id == "d9") return DebugInputCurrent.D9 && (rapid ? true : !DebugInputLast.D9);
	if (id == "a") return DebugInputCurrent.A && (rapid ? true : !DebugInputLast.A);
	if (id == "b") return DebugInputCurrent.B && (rapid ? true : !DebugInputLast.B);
	if (id == "c") return DebugInputCurrent.C && (rapid ? true : !DebugInputLast.C);
	if (id == "d") return DebugInputCurrent.D && (rapid ? true : !DebugInputLast.D);
	if (id == "e") return DebugInputCurrent.E && (rapid ? true : !DebugInputLast.E);
	if (id == "f") return DebugInputCurrent.F && (rapid ? true : !DebugInputLast.F);
	if (id == "g") return DebugInputCurrent.G && (rapid ? true : !DebugInputLast.G);
	if (id == "h") return DebugInputCurrent.H && (rapid ? true : !DebugInputLast.H);
	if (id == "i") return DebugInputCurrent.I && (rapid ? true : !DebugInputLast.I);
	if (id == "j") return DebugInputCurrent.J && (rapid ? true : !DebugInputLast.J);
	if (id == "k") return DebugInputCurrent.K && (rapid ? true : !DebugInputLast.K);
	if (id == "l") return DebugInputCurrent.L && (rapid ? true : !DebugInputLast.L);
	if (id == "m") return DebugInputCurrent.M && (rapid ? true : !DebugInputLast.M);
	if (id == "n") return DebugInputCurrent.N && (rapid ? true : !DebugInputLast.N);
	if (id == "o") return DebugInputCurrent.O && (rapid ? true : !DebugInputLast.O);
	if (id == "p") return DebugInputCurrent.P && (rapid ? true : !DebugInputLast.P);
	if (id == "q") return DebugInputCurrent.Q && (rapid ? true : !DebugInputLast.Q);
	if (id == "r") return DebugInputCurrent.R && (rapid ? true : !DebugInputLast.R);
	if (id == "s") return DebugInputCurrent.S && (rapid ? true : !DebugInputLast.S);
	if (id == "t") return DebugInputCurrent.T && (rapid ? true : !DebugInputLast.T);
	if (id == "u") return DebugInputCurrent.U && (rapid ? true : !DebugInputLast.U);
	if (id == "v") return DebugInputCurrent.V && (rapid ? true : !DebugInputLast.V);
	if (id == "w") return DebugInputCurrent.W && (rapid ? true : !DebugInputLast.W);
	if (id == "x") return DebugInputCurrent.X && (rapid ? true : !DebugInputLast.X);
	if (id == "y") return DebugInputCurrent.Y && (rapid ? true : !DebugInputLast.Y);
	if (id == "z") return DebugInputCurrent.Z && (rapid ? true : !DebugInputLast.Z);
	if (id == "num0") return DebugInputCurrent.NUM0 && (rapid ? true : !DebugInputLast.NUM0);
	if (id == "num1") return DebugInputCurrent.NUM1 && (rapid ? true : !DebugInputLast.NUM1);
	if (id == "num2") return DebugInputCurrent.NUM2 && (rapid ? true : !DebugInputLast.NUM2);
	if (id == "num3") return DebugInputCurrent.NUM3 && (rapid ? true : !DebugInputLast.NUM3);
	if (id == "num4") return DebugInputCurrent.NUM4 && (rapid ? true : !DebugInputLast.NUM4);
	if (id == "num5") return DebugInputCurrent.NUM5 && (rapid ? true : !DebugInputLast.NUM5);
	if (id == "num6") return DebugInputCurrent.NUM6 && (rapid ? true : !DebugInputLast.NUM6);
	if (id == "num7") return DebugInputCurrent.NUM7 && (rapid ? true : !DebugInputLast.NUM7);
	if (id == "num8") return DebugInputCurrent.NUM8 && (rapid ? true : !DebugInputLast.NUM8);
	if (id == "num9") return DebugInputCurrent.NUM9 && (rapid ? true : !DebugInputLast.NUM9);
	if (id == "numdiv") return DebugInputCurrent.NUMDIV && (rapid ? true : !DebugInputLast.NUMDIV);
	if (id == "nummul") return DebugInputCurrent.NUMMUL && (rapid ? true : !DebugInputLast.NUMMUL);
	if (id == "nummin") return DebugInputCurrent.NUMMIN && (rapid ? true : !DebugInputLast.NUMMIN);
	if (id == "numplu") return DebugInputCurrent.NUMPLU && (rapid ? true : !DebugInputLast.NUMPLU);
	if (id == "numret") return DebugInputCurrent.NUMRET && (rapid ? true : !DebugInputLast.NUMRET);
	if (id == "numdel") return DebugInputCurrent.NUMDEL && (rapid ? true : !DebugInputLast.NUMDEL);
	if (id == "f1") return DebugInputCurrent.F1 && (rapid ? true : !DebugInputLast.F1);
	if (id == "f2") return DebugInputCurrent.F2 && (rapid ? true : !DebugInputLast.F2);
	if (id == "f3") return DebugInputCurrent.F3 && (rapid ? true : !DebugInputLast.F3);
	if (id == "f4") return DebugInputCurrent.F4 && (rapid ? true : !DebugInputLast.F4);
	if (id == "f5") return DebugInputCurrent.F5 && (rapid ? true : !DebugInputLast.F5);
	if (id == "f6") return DebugInputCurrent.F6 && (rapid ? true : !DebugInputLast.F6);
	if (id == "f7") return DebugInputCurrent.F7 && (rapid ? true : !DebugInputLast.F7);
	if (id == "f8") return DebugInputCurrent.F8 && (rapid ? true : !DebugInputLast.F8);
	if (id == "f9") return DebugInputCurrent.F9 && (rapid ? true : !DebugInputLast.F9);
	if (id == "f10") return DebugInputCurrent.F10 && (rapid ? true : !DebugInputLast.F10);
	if (id == "f11") return DebugInputCurrent.F11 && (rapid ? true : !DebugInputLast.F11);
	if (id == "f12") return DebugInputCurrent.F12 && (rapid ? true : !DebugInputLast.F12);
	if (id == "comma") return DebugInputCurrent.COMMA && (rapid ? true : !DebugInputLast.COMMA);
	if (id == "dot") return DebugInputCurrent.DOT && (rapid ? true : !DebugInputLast.DOT);
	if (id == "plus") return DebugInputCurrent.PLUS && (rapid ? true : !DebugInputLast.PLUS);
	if (id == "minus") return DebugInputCurrent.MINUS && (rapid ? true : !DebugInputLast.MINUS);
	if (id == "lmb") return DebugInputCurrent.LMB && (rapid ? true : !DebugInputLast.LMB);
	if (id == "rmb") return DebugInputCurrent.RMB && (rapid ? true : !DebugInputLast.RMB);
	if (id == "mb") return DebugInputCurrent.MB && (rapid ? true : !DebugInputLast.MB);

	return false;
}

void DebugMenuHandleClick(int id, bool left)
{
	if (left)
	{
		// Left click
		if (DebugMenuMainForm == DEBUGMENUFORM::FORM_OVERVIEW)
		{
			DebugMenuParameterFocus = -1;
			if (id == 0) DebugMenuShowValuesMode = !DebugMenuShowValuesMode;
			if (id == 1)
			{
				DebugMenuMainForm = DEBUGMENUFORM::FORM_DEBUGVALUES;
				DebugMenuSubForm = 0;
				DebugMenuDebugAddressesParentFocus = -1;
			}
			if (id == 2) if (GlobalDebugFeatures.savefileEditor)
			{
				DebugMenuMainForm = DEBUGMENUFORM::FORM_SAVEFILEEDITOR;
				DebugMenuSubForm = 0;
			}
			if (id == 3) if (GlobalDebugFeatures.supervision) DebugMenuSuperVisionMode = !DebugMenuSuperVisionMode;
			if (id == 4) DebugMenuSettingsPerformanceMode = !DebugMenuSettingsPerformanceMode;

			if (id - 5 >= 0 && (id - 5) % 2 == 0)
			{
				DebugMenuFunctionFocus = (id - 5) / 2; // Debug function focus
				DebugMenuMainForm = DEBUGMENUFORM::FORM_DEBUGFUNCTIONS;
				DebugMenuSubForm = 0;
				DebugMenuDebugFunctionsParentFocus = -1;
			}
			if (id - 6 >= 0 && (id - 6) % 2 == 0) DebugMenuParameterFocus = (id - 6) / 2; // Debug function parameter focus
		}
		else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_DEBUGVALUES)
		{
			if (DebugMenuSubForm == 0)
			{
				if (id == 0)
				{
					DebugMenuMainForm = DEBUGMENUFORM::FORM_OVERVIEW;
				}

				if (id > 0)
				{
					DebugMenuDebugAddressesParentFocus = id - 1;
					DebugMenuSubForm = 1;
				}
			}
			else if (DebugMenuSubForm == 1)
			{
				if (id == 0)
				{
					DebugMenuSubForm = 0;
				}

				if (id > 0)
				{
					bool add = true;
					DebugAddress focusAddress = DebugAddresses[DebugMenuDebugAddressesParentFocus].addresses[id - 1];
					for (int i = 0; i < DebugMenuDebugAddressShowValues.size(); i++)
					{
						if (focusAddress.nameFull == DebugMenuDebugAddressShowValues[i].nameFull)
						{
							add = false;
							DebugMenuDebugAddressShowValues.erase(DebugMenuDebugAddressShowValues.begin() + i);
							break;
						}
					}
					if (add) DebugMenuDebugAddressShowValues.push_back(DebugAddresses[DebugMenuDebugAddressesParentFocus].addresses[id - 1]);
				}
			}
		}
		else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_DEBUGFUNCTIONS)
		{
			if (DebugMenuSubForm == 0)
			{
				if (id == 0)
				{
					DebugMenuMainForm = DEBUGMENUFORM::FORM_OVERVIEW;
				}

				if (id > 0)
				{
					DebugMenuDebugFunctionsParentFocus = id - 1;
					DebugMenuSubForm = 1;
				}
			}
			else if (DebugMenuSubForm == 1)
			{
				if (id == 0)
				{
					DebugMenuSubForm = 0;
				}

				if (id > 0)
				{
					bool select = true;
					DebugFunction focusAddress = DebugFunctions[DebugMenuDebugFunctionsParentFocus].functions[id - 1];
					if (focusAddress.nameFull == DebugMenuHotkeys[DebugMenuFunctionFocus].nameFull)
					{
						DebugFunction tmp;
						tmp.nameFull = "- EMPTY -";
						DebugMenuHotkeys[DebugMenuFunctionFocus] = tmp;
					}
					else
					{
						DebugMenuHotkeys[DebugMenuFunctionFocus] = focusAddress;
					}
				}
			}
		}
		else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_SAVEFILEEDITOR)
		{
			if (DebugMenuSubForm == 0)
			{
				if (id == 0)
				{
					DebugMenuMainForm = DEBUGMENUFORM::FORM_OVERVIEW;
				}

				if (id > 0)
				{
					SavefileCurrentFile = SavefileFiles[id - 1];
					pScopeSavefile(SavefileCurrentFile);
					DebugMenuSubForm = 1;
				}
			}
			else if (DebugMenuSubForm == 1)
			{
				if (id == 0)
				{
					DebugMenuSubForm = 0;
				}

				if (id > 0)
				{
					SavefileParentFocus = id - 1;
					DebugMenuSubForm = 2;
					pLoadSavefile(&SavefileParents[SavefileParentFocus]);
				}
			}
			else if (DebugMenuSubForm == 2)
			{
				if (id == 0)
				{
					// Done
					DebugMenuSubForm = 1;
				}

				if (id == 1)
				{
					// Save
					pSaveSavefile(&SavefileParents[SavefileParentFocus]);
				}

				if (id == 2)
				{
					// Reload
					pLoadSavefile(&SavefileParents[SavefileParentFocus]);
				}

				if (id > 2)
				{
					if (id - 3 >= 0 && (id - 3) % 2 == 1) SavefileFielFocus = (id - 4) / 2;
				}
			}

		}
	}
	else
	{
		// Right Click
		if (DebugMenuMainForm == DEBUGMENUFORM::FORM_OVERVIEW)
		{
			DebugMenuParameterFocus = -1;
			if (id == 0) DebugMenuShowValuesMode = !DebugMenuShowValuesMode;
			if (id == 1)
			{
				DebugMenuMainForm = DEBUGMENUFORM::FORM_DEBUGVALUES;
				DebugMenuSubForm = 0;
				DebugMenuDebugAddressesParentFocus = -1;
			}
			if (id == 2) if (GlobalDebugFeatures.savefileEditor)
			{
				DebugMenuMainForm = DEBUGMENUFORM::FORM_SAVEFILEEDITOR;
				DebugMenuSubForm = 0;
			}
			if (id == 3) if (GlobalDebugFeatures.supervision) DebugMenuSuperVisionMode = !DebugMenuSuperVisionMode;
			if (id == 4) DebugMenuSettingsPerformanceMode = !DebugMenuSettingsPerformanceMode;

			if (id - 5 >= 0 && (id - 5) % 2 == 0)
			{
				DebugFunction tmp;
				tmp.nameFull = "- EMPTY -";
				DebugMenuHotkeys[(id - 5) / 2] = tmp;
			}
			if (id - 6 >= 0 && (id - 6) % 2 == 0) DebugMenuParameter[(id - 6) / 2] = "";
		}
	}

	int DebugMenuDebugAddressesParentFocus = 0;
	int DebugMenuDebugFunctionsParentFocus = 0;
	std::vector<DebugAddress> DebugMenuDebugAddressShowValues;
}

void _DrawHoverBoxes()
{
	std::vector<RECT> boxesTarget;
	if (DebugMenuMainForm == DEBUGMENUFORM::FORM_OVERVIEW) boxesTarget = DebugMenuOverviewHoverBoxes;
	else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_DEBUGVALUES)
	{
		if (DebugMenuSubForm == 0)
		{
			boxesTarget = DebugMenuDebugAddressesParentsHoverBoxes;
		}
		if (DebugMenuSubForm == 1)
		{
			boxesTarget = DebugMenuDebugAddressesChildsHoverBoxes[DebugMenuDebugAddressesParentFocus];
		}
	}
	else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_DEBUGFUNCTIONS)
	{
		if (DebugMenuSubForm == 0)
		{
			boxesTarget = DebugMenuDebugFunctionsParentsHoverBoxes;
		}
		if (DebugMenuSubForm == 1)
		{
			boxesTarget = DebugMenuDebugFunctionsChildsHoverBoxes[DebugMenuDebugFunctionsParentFocus];
		}
	}
	else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_SAVEFILEEDITOR)
	{
		if (DebugMenuSubForm == 0)
		{
			boxesTarget = DebugMenuSavefileEditorFilesHoverBoxes;
		}
		if (DebugMenuSubForm == 1)
		{
			boxesTarget = DebugMenuSavefileEditorParentsHoverBoxes;
		}
		if (DebugMenuSubForm == 2)
		{
			boxesTarget = DebugMenuSavefileEditorChildsHoverBoxes[SavefileParentFocus];
		}
	}

	for (int i = 0; i < boxesTarget.size(); i++)
	{
		if (DebugMenuCursorPosition.x > boxesTarget[i].left && DebugMenuCursorPosition.x < boxesTarget[i].right && DebugMenuCursorPosition.y > boxesTarget[i].top && DebugMenuCursorPosition.y < boxesTarget[i].bottom)
		{
			if (DebugKeyPressed("lmb") || DebugKeyPressed("mb")) DebugMenuHandleClick(i, true);
			if (DebugKeyPressed("rmb")) DebugMenuHandleClick(i, false);
			_DebugDrawRectangle(boxesTarget[i].left, boxesTarget[i].top, boxesTarget[i].right - boxesTarget[i].left, boxesTarget[i].bottom - boxesTarget[i].top, ColorYellow, 0.7f);
			break;
		}
	}
}

int DebugMenuShowValuesModeRowWidths[10];
int DebugMenuShowValuesModeMaxRows = 0;
int DebugMenuShowValuesModeFinalRowWidth = 0;
int DebugMenuShowValuesModeFinalRowHeight = 0;

void DebugMenuShowValuesModeCalculateSize()
{

}

void DebugMenuExecuteHotkey(int id)
{
	if (DebugMenuHotkeys[id].nameFull == "TAS.PlayScript")
	{
		std::string _script = "";
		if (DebugMenuHotkeys[id].parameter[0].value != "none" && !DebugMenuHotkeys[id].parameter[0].value.empty()) _script = GetVariableString(&DebugMenuHotkeys[id].parameter[0]);
		_script = _script + ";";
		pTASPlayScript((char*)_script.c_str());
	}
	else if (DebugMenuHotkeys[id].nameFull == "TAS.RecordScript")
	{
		std::string _script = "";
		if (DebugMenuHotkeys[id].parameter[0].value != "none" && !DebugMenuHotkeys[id].parameter[0].value.empty()) _script = GetVariableString(&DebugMenuHotkeys[id].parameter[0]);
		_script = _script + ";";
		pTASRecordScript((char*)_script.c_str());
	}
	else
	{
		pExecuteDebugFunction(&DebugMenuHotkeys[id]);
	}
}

std::string DebugMenuHotkeyDisplayName(int id)
{
	return DebugMenuHotkeys[id].nameFull;
}

std::string DebugMenuHotkeyDisplayParameter(int id)
{
	return "Parameter: " + DebugMenuParameter[id];
}

void DebugMenuCheckParameterInput(int id)
{
	if (DebugKeyPressed("a")) DebugMenuParameter[id] += "a";
	if (DebugKeyPressed("b")) DebugMenuParameter[id] += "b";
	if (DebugKeyPressed("c")) DebugMenuParameter[id] += "c";
	if (DebugKeyPressed("d")) DebugMenuParameter[id] += "d";
	if (DebugKeyPressed("e")) DebugMenuParameter[id] += "e";
	if (DebugKeyPressed("f")) DebugMenuParameter[id] += "f";
	if (DebugKeyPressed("g")) DebugMenuParameter[id] += "g";
	if (DebugKeyPressed("h")) DebugMenuParameter[id] += "h";
	if (DebugKeyPressed("i")) DebugMenuParameter[id] += "i";
	if (DebugKeyPressed("j")) DebugMenuParameter[id] += "j";
	if (DebugKeyPressed("k")) DebugMenuParameter[id] += "k";
	if (DebugKeyPressed("l")) DebugMenuParameter[id] += "l";
	if (DebugKeyPressed("m")) DebugMenuParameter[id] += "m";
	if (DebugKeyPressed("n")) DebugMenuParameter[id] += "n";
	if (DebugKeyPressed("o")) DebugMenuParameter[id] += "o";
	if (DebugKeyPressed("p")) DebugMenuParameter[id] += "p";
	if (DebugKeyPressed("q")) DebugMenuParameter[id] += "q";
	if (DebugKeyPressed("r")) DebugMenuParameter[id] += "r";
	if (DebugKeyPressed("s")) DebugMenuParameter[id] += "s";
	if (DebugKeyPressed("t")) DebugMenuParameter[id] += "t";
	if (DebugKeyPressed("u")) DebugMenuParameter[id] += "u";
	if (DebugKeyPressed("v")) DebugMenuParameter[id] += "v";
	if (DebugKeyPressed("w")) DebugMenuParameter[id] += "w";
	if (DebugKeyPressed("x")) DebugMenuParameter[id] += "x";
	if (DebugKeyPressed("y")) DebugMenuParameter[id] += "y";
	if (DebugKeyPressed("z")) DebugMenuParameter[id] += "z";
	if (DebugKeyPressed("d0")) DebugMenuParameter[id] += "0";
	if (DebugKeyPressed("d1")) DebugMenuParameter[id] += "1";
	if (DebugKeyPressed("d2"))
	{
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000 || GetAsyncKeyState(VK_RSHIFT) & 0x8000) DebugMenuParameter[id] += "\"";
		else DebugMenuParameter[id] += "2";
	}
	if (DebugKeyPressed("d3")) DebugMenuParameter[id] += "3";
	if (DebugKeyPressed("d4")) DebugMenuParameter[id] += "4";
	if (DebugKeyPressed("d5")) DebugMenuParameter[id] += "5";
	if (DebugKeyPressed("d6")) DebugMenuParameter[id] += "6";
	if (DebugKeyPressed("d7")) DebugMenuParameter[id] += "7";
	if (DebugKeyPressed("d8")) DebugMenuParameter[id] += "8";
	if (DebugKeyPressed("d9")) DebugMenuParameter[id] += "9";
	if (DebugKeyPressed("comma")) DebugMenuParameter[id] += ",";
	if (DebugKeyPressed("dot")) DebugMenuParameter[id] += ".";
	if (DebugKeyPressed("plus")) DebugMenuParameter[id] += "+";
	if (DebugKeyPressed("minus")) DebugMenuParameter[id] += "-";
	if (DebugKeyPressed("space")) DebugMenuParameter[id] += " ";
	if (DebugKeyPressed("back")) if (DebugMenuParameter[id].length() > 0) DebugMenuParameter[id] = DebugMenuParameter[id].substr(0, DebugMenuParameter[id].length() - 1);
}

void DebugMenuCheckSavefileFieldInput()
{
	if (SavefileParentFocus == -1 || SavefileFielFocus == -1) return;
	if (DebugKeyPressed("a")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "a";
	if (DebugKeyPressed("b")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "b";
	if (DebugKeyPressed("c")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "c";
	if (DebugKeyPressed("d")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "d";
	if (DebugKeyPressed("e")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "e";
	if (DebugKeyPressed("f")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "f";
	if (DebugKeyPressed("g")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "g";
	if (DebugKeyPressed("h")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "h";
	if (DebugKeyPressed("i")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "i";
	if (DebugKeyPressed("j")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "j";
	if (DebugKeyPressed("k")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "k";
	if (DebugKeyPressed("l")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "l";
	if (DebugKeyPressed("m")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "m";
	if (DebugKeyPressed("n")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "n";
	if (DebugKeyPressed("o")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "o";
	if (DebugKeyPressed("p")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "p";
	if (DebugKeyPressed("q")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "q";
	if (DebugKeyPressed("r")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "r";
	if (DebugKeyPressed("s")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "s";
	if (DebugKeyPressed("t")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "t";
	if (DebugKeyPressed("u")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "u";
	if (DebugKeyPressed("v")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "v";
	if (DebugKeyPressed("w")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "w";
	if (DebugKeyPressed("x")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "x";
	if (DebugKeyPressed("y")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "y";
	if (DebugKeyPressed("z")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "z";
	if (DebugKeyPressed("d0")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "0";
	if (DebugKeyPressed("d1")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "1";
	if (DebugKeyPressed("d2"))
	{
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000 || GetAsyncKeyState(VK_RSHIFT) & 0x8000) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "\"";
		else SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "2";
	}

	if (DebugKeyPressed("d3")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "3";
	if (DebugKeyPressed("d4")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "4";
	if (DebugKeyPressed("d5")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "5";
	if (DebugKeyPressed("d6")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "6";
	if (DebugKeyPressed("d7")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "7";
	if (DebugKeyPressed("d8")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "8";
	if (DebugKeyPressed("d9")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "9";
	if (DebugKeyPressed("comma")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += ",";
	if (DebugKeyPressed("dot")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += ".";
	if (DebugKeyPressed("plus")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "+";
	if (DebugKeyPressed("minus")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += "-";
	if (DebugKeyPressed("space")) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value += " ";
	if (DebugKeyPressed("back")) if (SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value.length() > 0) SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value = SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value.substr(0, SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value.length() - 1);
}

RECT OriginalCursorClip;
RECT CustomCursorClip;
POINT OriginalCursorPos;
POINT CustomCursorPos;

void CalcNewCursorPos()
{
	CustomCursorPos.x += DebugInputCurrent.MOUSEX;
	CustomCursorPos.y += DebugInputCurrent.MOUSEY;
}

void __cdecl DebugMenuOpen()
{
	std::cout << "Opened!" << std::endl;
	DebugMenuOpened = true;
	DebugMenuInitSwitch = true;
	DebugMenuMainForm = DEBUGMENUFORM::FORM_OVERVIEW;
	DebugMenuSubForm = 0;
	DebugMenuMainFormLast = DEBUGMENUFORM::FORM_OVERVIEW;
	DebugMenuSubFormLast = 0;
	RawInputDisableForGame = true;

	std::ifstream file(GlobalSettings.config_debugconfig_directory + "hotkeys.txt");

	DebugFunction tmp;
	tmp.nameFull = "- EMPTY -";
	for (int i = 0; i < 25; i++) DebugMenuHotkeys[i] = tmp;
	for (int i = 0; i < 25; i++) DebugMenuParameter[i] = "";
	 
	if (file.good())
	{
		std::string script = "";

		while (!file.eof()) {
			// Read line
			std::string line = "";
			std::getline(file, line);

			//Declare Substrings
			std::string substring_instruction = "";
			std::string substring_iterations = "";

			// Check if line contains content
			if (line.length() > 0) {
				std::string key = line.substr(0, line.find("="));
				std::string func = line.substr(line.find("=") + 1, line.find(";") - (line.find("=") + 1));
				if (func != "")
				{
					int index = 0;

					if (key == "NUM_1") index = 0;
					if (key == "NUM_2") index = 1;
					if (key == "NUM_3") index = 2;
					if (key == "NUM_4") index = 3;
					if (key == "NUM_5") index = 4;
					if (key == "NUM_6") index = 5;
					if (key == "NUM_7") index = 6;
					if (key == "NUM_8") index = 7;
					if (key == "NUM_9") index = 8;
					if (key == "NUM_/") index = 9;
					if (key == "NUM_*") index = 10;
					if (key == "NUM_-") index = 11;
					if (key == "NUM_+") index = 12;
					if (key == "F1") index = 13;
					if (key == "F2") index = 14;
					if (key == "F3") index = 15;
					if (key == "F4") index = 16;
					if (key == "F5") index = 17;
					if (key == "F6") index = 18;
					if (key == "F7") index = 19;
					if (key == "F8") index = 20;
					if (key == "F9") index = 21;
					if (key == "F10") index = 22;
					if (key == "F11") index = 23;
					if (key == "F12") index = 24;

					std::string parentName = func.substr(0, func.find("."));
					std::string childName = func.substr(func.find(".") + 1, func.find("(") - (func.find(".") + 1));
					std::string paramsAll = func.substr(func.find("(") + 1, func.find(")") - (func.find("(") + 1));

					for (int i = 0; i < DebugFunctions.size(); i++)
					{
						if (DebugFunctions[i].nameParent == parentName)
						{
							for (int k = 0; k < DebugFunctions[i].functions.size(); k++)
							{
								if (DebugFunctions[i].functions[k].nameChild == childName)
								{
									DebugMenuHotkeys[index] = DebugFunctions[i].functions[k];
									DebugMenuParameter[index] = paramsAll;
									break;
								}
							}
						}
					}

				}
			}
		}

		file.close();
	}

	if (GlobalDebugFeatures.savefileEditor)
	{
		pGetSavefiles(SavefileFilesBuffer);
		std::string allFiles(SavefileFilesBuffer);
		if (SavefileFiles.size() > 0) SavefileFiles.clear();
		splitStringVector(SavefileFiles, allFiles, ";");

		if (DebugMenuSavefileEditorFilesHoverBoxes.size() > 0) DebugMenuSavefileEditorFilesHoverBoxes.clear();

		// Savefile editor
		DebugMenuSavefileEditorFilesHoverBoxes.push_back(RECT{ 63, 975, 279, 1016 });

		int col = 0;
		int row = 0;
		for (int i = 0; i < SavefileFiles.size(); i++)
		{
			DebugMenuSavefileEditorFilesHoverBoxes.push_back(RECT{ 60 + (360 * row), 165 + (30 * col), 60 + (360 * row) + 360, 165 + (30 * col) + 30 });
			col++;
			if (col == 25)
			{
				col = 0;
				row++;
			}
		}
	}

}

void DebugMenuClose()
{
	if (DebugMenuShowValuesMode)
	{
		DebugMenuShowValuesModeCalculateSize();
	}

	DebugMenuDebugAddressShowValuesInit = true;
	DebugMenuDebugAddressShowValuesBackWidth = 0;
	DebugMenuDebugAddressShowValuesBackHeight = 0;

	// Close the menu
	DebugMenuOpened = false;
	DebugMenuInitSwitch = true;
	DebugMenuMainForm = DEBUGMENUFORM::FORM_NONE;
	DebugMenuSubForm = 0;
	RawInputDisableForGame = false;

	std::ofstream file(GlobalSettings.config_debugconfig_directory + "hotkeys.txt");

	for (int i = 0; i < DebugMenuHotkeys.size(); i++)
	{
		std::string line = "";
		if (i == 0) line = "NUM_1=";
		if (i == 1) line = "NUM_2=";
		if (i == 2) line = "NUM_3=";
		if (i == 3) line = "NUM_4=";
		if (i == 4) line = "NUM_5=";
		if (i == 5) line = "NUM_6=";
		if (i == 6) line = "NUM_7=";
		if (i == 7) line = "NUM_8=";
		if (i == 8) line = "NUM_9=";
		if (i == 9) line = "NUM_/=";
		if (i == 10) line = "NUM_*=";
		if (i == 11) line = "NUM_-=";
		if (i == 12) line = "NUM_+=";
		if (i == 13) line = "F1=";
		if (i == 14) line = "F2=";
		if (i == 15) line = "F3=";
		if (i == 16) line = "F4=";
		if (i == 17) line = "F5=";
		if (i == 18) line = "F6=";
		if (i == 19) line = "F7=";
		if (i == 20) line = "F8=";
		if (i == 21) line = "F9=";
		if (i == 22) line = "F10=";
		if (i == 23) line = "F11=";
		if (i == 24) line = "F12=";

		if (DebugMenuHotkeys[i].nameFull != "- EMPTY -") line = line + DebugMenuHotkeys[i].nameFull + "(" + DebugMenuParameter[i] + ");";
		else line = line + ";";

		file << line << std::endl;
	}

	file.close();

	// Update debug function parameter
	for (int i = 0; i < DebugMenuHotkeys.size(); i++)
	{
		if (DebugMenuHotkeys[i].nameFull != "- EMPTY -")
		{
			if (DebugMenuParameter[i] != "")
			{
				if (DebugMenuHotkeys[i].parameter.size() > 0)
				{
					std::string paramCopy = DebugMenuParameter[i];
					int index = 0;
					bool quote = false;
					while (index < paramCopy.length())
					{
						if (paramCopy[index] == ' ' && !quote)
						{
							paramCopy.replace(index, 1, "");
						}
						else
						{
							index++;
						}
					}

					if (paramCopy.empty())
					{
						for (int k = 0; k < DebugMenuHotkeys[i].parameter.size(); k++) SetVariable(&DebugMenuHotkeys[i].parameter[k], "none");
					}
					else
					{
						std::vector<std::string> params;
						splitStringVector(params, paramCopy, ",");
						for (int k = 0; k < params.size(); k++)
						{
							if (params[k].empty())
							{
								SetVariable(&DebugMenuHotkeys[i].parameter[k], "none");
							}
							else
							{
								if (DebugMenuHotkeys[i].parameter[k].type.find("float") != std::string::npos && params[k].find(".") == std::string::npos) params[k] = params[k] + ".0";
								SetVariable(&DebugMenuHotkeys[i].parameter[k], params[k]);
							}
							if (k + 1 > DebugMenuHotkeys[i].parameter.size()) break;
						}
					}
				}
			}
			else
			{
				for (int k = 0; k < DebugMenuHotkeys[i].parameter.size(); k++) SetVariable(&DebugMenuHotkeys[i].parameter[k], "none");
			}
		}
	}


}

void DebugDrawDebugAddresses()
{
	if (DebugMenuDebugAddressShowValuesInit)
	{
		HGDIOBJ oldFont = SelectObject(hdc, FontSmall);

		int col = 0;
		int row = 0;
		int highestWidth = 0;
		DebugMenuDebugAddressShowValuesBackHeight = 10;
		DebugMenuDebugAddressShowValuesBackWidth = 10;
		DebugMenuDebugAddressShowValuesRowHeight = 0;
		std::sort(DebugMenuDebugAddressShowValues.begin(), DebugMenuDebugAddressShowValues.end(), DebugAddressSortNameFull);
		std::string lastParent = "";
		int parentOff = 0;
		for (int i = 0; i < DebugMenuDebugAddressShowValues.size(); i++)
		{
			std::string text = "";
			if (DebugMenuDebugAddressShowValues[i].nameParent != lastParent)
			{
				lastParent = DebugMenuDebugAddressShowValues[i].nameParent;
				text = lastParent;
				parentOff++;
				i--;
			}
			else
			{
				pGetDebugAddressValue(&DebugMenuDebugAddressShowValues[i]);
				text = DebugMenuDebugAddressShowValues[i].nameFull + ": " + DebugMenuDebugAddressShowValues[i].value.value;
			}
			SIZE textSize;
			GetTextExtentPoint32A(hdc, text.c_str(), (int)text.length(), &textSize);
			textSize.cx += 10;
			textSize.cy += 5;

			if (DebugMenuDebugAddressShowValuesRowHeight == 0) DebugMenuDebugAddressShowValuesRowHeight = textSize.cy;

			if (textSize.cx > highestWidth) highestWidth = textSize.cx;
			if (row == 0) DebugMenuDebugAddressShowValuesBackHeight += DebugMenuDebugAddressShowValuesRowHeight;
			if (i + 1 == DebugMenuDebugAddressShowValues.size() || col + 1 == DebugMenuDebugAddressShowValuesMaxCol)
			{
				DebugMenuDebugAddressShowValuesRowWidth[row] = highestWidth;
				DebugMenuDebugAddressShowValuesBackWidth += highestWidth;
			}

			if (col + 1 == DebugMenuDebugAddressShowValuesMaxCol)
			{
				highestWidth = 0;
				col = 0;
				row++;
			}
			else
			{
				col++;
			}
		}

		SelectObject(hdc, oldFont);
		DebugMenuDebugAddressShowValuesInit = false;
	}
	else
	{
		_DebugDrawRectangle(0, 0, DebugMenuDebugAddressShowValuesBackWidth, DebugMenuDebugAddressShowValuesBackHeight, ColorBlack, 0.8f);

		int col = 0;
		int row = 0;
		std::string lastParent = "";
		for (int i = 0; i < DebugMenuDebugAddressShowValues.size(); i++)
		{
			if (DebugMenuDebugAddressShowValues[i].nameParent != lastParent)
			{
				lastParent = DebugMenuDebugAddressShowValues[i].nameParent;
				_DebugDrawText("- " + DebugMenuDebugAddressShowValues[i].nameParent + " -", 5 + (row > 0 ? DebugMenuDebugAddressShowValuesRowWidth[row - 1] : 0), 5 + (col * DebugMenuDebugAddressShowValuesRowHeight), FontSmall, ColorWhite, 1.0f, "left");
				i--;
			}
			else
			{
				pGetDebugAddressValue(&DebugMenuDebugAddressShowValues[i]);
				std::string text = DebugMenuDebugAddressShowValues[i].nameFull + ": " + DebugMenuDebugAddressShowValues[i].value.value;
				_DebugDrawText(text, 5 + (row > 0 ? DebugMenuDebugAddressShowValuesRowWidth[row - 1] : 0), 5 + (col * DebugMenuDebugAddressShowValuesRowHeight), FontSmall, ColorWhite, 1.0f, "left");
			}

			if (col + 1 == DebugMenuDebugAddressShowValuesMaxCol)
			{
				col = 0;
				row++;
			}
			else
			{
				col++;
			}
		}
	}
}



int DebugMenuHotkeyDelegationIndex = 0;

void DebugMenuMainRoutine()
{
	// Check for input
	//if (!TASPlayScript && !TASRecordScript)
	//{
	std::memcpy(&DebugInputLast, &DebugInputCurrent, sizeof(GameInput));
	GetRawInput(false, &DebugInputCurrent, "all");
	//}

	GetWindowRect(MainWindowHandle, &MainWindowRect);
	
	MainWindowActive = CheckWindowActive();

	if (DebugMenuOpened)
	{
		// Customize the cursor
		GetCursorPos(&DebugMenuCursorPosition);
		ScreenToClient(MainWindowHandle, &DebugMenuCursorPosition);

		//std::cout << "X: " << std::dec << DebugMenuCursorPosition.x << " | Y: " << DebugMenuCursorPosition.y << std::endl;

		if (DebugMenuCanDraw)
		{
			ClearSurface(DebugMenuMainForm, DebugMenuSubForm);

			// Input handling
			if (MainWindowActive)
			{

				if (DebugKeyPressed("num0"))
				{
					DebugMenuClose();
				}

				if (DebugKeyPressed("esc"))
				{
					if (DebugMenuSubForm > 0)
					{
						DebugMenuSubForm--;
					}
					else
					{
						if (DebugMenuMainForm == DEBUGMENUFORM::FORM_OVERVIEW)
						{
							DebugMenuClose();
						}
						else
						{
							DebugMenuMainForm = DEBUGMENUFORM::FORM_OVERVIEW;
						}
					}
				}

				if (DebugMenuParameterFocus > -1) DebugMenuCheckParameterInput(DebugMenuParameterFocus);
			}

			// Draw Hoverboxes
			_DrawHoverBoxes();
			
			// Draw overview
			if (DebugMenuMainForm == DEBUGMENUFORM::FORM_OVERVIEW)
			{
				_DebugDrawText(DebugMenuShowValuesMode ? "Enabled" : "Disabled", 160, 260, FontBigMedium, DebugMenuShowValuesMode ? ColorDarkGreen : ColorRed, 1.0f, "center");
				_DebugDrawText("Edit", 390, 260, FontBigMedium, ColorBlack, 1.0f, "center");
				_DebugDrawText(GlobalDebugFeatures.savefileEditor ? "Edit" : "Not Available", 160, 370, FontBigMedium, GlobalDebugFeatures.savefileEditor ? ColorBlack : ColorGray, 1.0f, "center");
				_DebugDrawText(GlobalDebugFeatures.supervision ? (DebugMenuSuperVisionMode ? "Enabled" : "Disabled") : "Not Available", 160, 493, FontBigMedium, GlobalDebugFeatures.supervision ? (DebugMenuSuperVisionMode ? ColorDarkGreen : ColorRed) : ColorGray, 1.0f, "center");
				_DebugDrawText(DebugMenuSettingsPerformanceMode ? "Enabled" : "Disabled", 160, 983, FontBigMedium, DebugMenuSettingsPerformanceMode ? ColorDarkGreen : ColorRed, 1.0f, "center");

				for (int i = 0; i < 13; i++)
				{
					_DebugDrawText(DebugMenuHotkeys[i].nameFull, 1245, 200 + (65 * i), FontMedium, ColorBlack, 1.0f, "center");
					_DebugDrawText(DebugMenuParameter[i], 1245, 228 + (65 * i), FontMedium, ColorBlack, 1.0f, "center");
				}

				for (int i = 0; i < 12; i++)
				{
					_DebugDrawText(DebugMenuHotkeys[i + 13].nameFull, 1690, 200 + (65 * i), FontMedium, ColorBlack, 1.0f, "center");
					_DebugDrawText(DebugMenuParameter[i + 13], 1690, 228 + (65 * i), FontMedium, ColorBlack, 1.0f, "center");
				}

			}
			else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_DEBUGVALUES)
			{
				_DebugDrawText("Done", 163, 981, FontBigMedium, ColorBlack, 1.0f, "center");
				if (DebugMenuSubForm == 0)
				{
					int col = 0;
					int row = 0;
					for (int i = 0; i < DebugAddresses.size(); i++)
					{
						_DebugDrawText(DebugAddresses[i].nameParent, 60 + (360 * row), 165 + (30 * col), FontMedium, ColorBlack, 1.0f, "left");
						col++;
						if (col == 25)
						{
							col = 0;
							row++;
						}
					}
				}
				else
				{
					int col = 0;
					int row = 0;
					for (int i = 0; i < DebugAddresses[DebugMenuDebugAddressesParentFocus].addresses.size(); i++)
					{
						bool selected = false;
						DebugAddress focusAddress = DebugAddresses[DebugMenuDebugAddressesParentFocus].addresses[i];
						for (int i = 0; i < DebugMenuDebugAddressShowValues.size(); i++)
						{
							if (focusAddress.nameFull == DebugMenuDebugAddressShowValues[i].nameFull)
							{
								selected = true;
								break;
							}
						}

						_DebugDrawText(focusAddress.nameChild, 60 + (360 * row), 165 + (30 * col), FontMedium, selected ? ColorDarkGreen : ColorRed, 1.0f, "left");
						col++;
						if (col == 25)
						{
							col = 0;
							row++;
						}
					}
				}
			}
			else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_DEBUGFUNCTIONS)
			{
				_DebugDrawText("Done", 163, 981, FontBigMedium, ColorBlack, 1.0f, "center");
				if (DebugMenuSubForm == 0)
				{
					int col = 0;
					int row = 0;
					for (int i = 0; i < DebugFunctions.size(); i++)
					{
						_DebugDrawText(DebugFunctions[i].nameParent, 60 + (360 * row), 165 + (30 * col), FontMedium, ColorBlack, 1.0f, "left");
						col++;
						if (col == 25)
						{
							col = 0;
							row++;
						}
					}
				}
				else
				{
					int col = 0;
					int row = 0;
					for (int i = 0; i < DebugFunctions[DebugMenuDebugFunctionsParentFocus].functions.size(); i++)
					{
						bool selected = false;
						DebugFunction focusFunction = DebugFunctions[DebugMenuDebugFunctionsParentFocus].functions[i];
						if (focusFunction.nameFull == DebugMenuHotkeys[DebugMenuFunctionFocus].nameFull) selected = true;

						_DebugDrawText(focusFunction.nameChild, 60 + (360 * row), 165 + (30 * col), FontMedium, selected ? ColorDarkGreen : ColorRed, 1.0f, "left");
						col++;
						if (col == 25)
						{
							col = 0;
							row++;
						}
					}
				}
			}
			else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_SAVEFILEEDITOR)
			{
				
				_DebugDrawText("Done", 163, 981, FontBigMedium, ColorBlack, 1.0f, "center");
				if (DebugMenuSubForm == 0)
				{
					std::cout << "Form 1" << std::endl;
					int col = 0;
					int row = 0;
					for (int i = 0; i < SavefileFiles.size(); i++)
					{
						_DebugDrawText(SavefileFiles[i], 60 + (360 * row), 165 + (30 * col), FontMedium, ColorBlack, 1.0f, "left");
						col++;
						if (col == 25)
						{
							col = 0;
							row++;
						}
					}
				}
				else if (DebugMenuSubForm == 1)
				{
					std::cout << "Form 2" << std::endl;
					int col = 0;
					int row = 0;
					for (int i = 0; i < SavefileParents.size(); i++)
					{
						_DebugDrawText(SavefileParents[i].nameParent, 60 + (360 * row), 165 + (30 * col), FontMedium, ColorBlack, 1.0f, "left");
						col++;
						if (col == 25)
						{
							col = 0;
							row++;
						}
					}
				}
				else if(DebugMenuSubForm == 2)
				{
					DebugMenuCheckSavefileFieldInput();
					std::cout << "Form 3" << std::endl;
					int col = 0;
					int row = 0;
					for (int i = 0; i < SavefileParents[SavefileParentFocus].fields.size(); i++)
					{
						std::string title = SavefileParents[SavefileParentFocus].fields[i].nameChild + " (" + SavefileParents[SavefileParentFocus].fields[i].value.type +")";
						std::string value = SavefileParents[SavefileParentFocus].fields[i].value.value;
						_DebugDrawText(title, 60 + (360 * row), 165 + (60 * col), FontMedium, ColorBlack, 1.0f, "left");
						_DebugDrawRectangle(60 + (360 * row), 165 + (60 * col) + 30, 300, 26, ColorWhite, 1.0f);
						_DebugDrawText(value, 60 + (360 * row) + 5, 165 + (60 * col) + 32, FontMedium, ColorBlack, 1.0f, "left");
						col++;
						if (col == 12)
						{
							col = 0;
							row++;
						}
					}
				}

			
			}

			if (DebugMenuMainForm != DebugMenuMainFormLast || DebugMenuSubForm != DebugMenuSubFormLast)
			{
				DebugMenuInitForms();
				DebugMenuMainFormLast = DebugMenuMainForm;
				DebugMenuSubFormLast = DebugMenuSubForm;
			}
		}

		// Draw custom cursor
		DrawCursorToTexture(DebugMenuCursorPosition.x, DebugMenuCursorPosition.y);

		// Draw menu
		_DrawMenu();
	}
	else
	{
		if (DebugMenuInitSwitch)
		{
			DebugMenuGeneralFrameskip = 0;
			DebugMenuCanDraw = true;
			DebugMenuInitSwitch = false;
		}

		if (DebugMenuCanDraw)
		{
			ClearSurface(DEBUGMENUFORM::FORM_NONE, 0);

			if (CheckWindowActive())// && !TASPlayScript && !TASRecordScript)
			{
				if (DebugKeyPressed("num0"))
				{
					// Open the menu
					DebugMenuOpen();
				}

				// Hotkeys
				if (DebugKeyPressed("num1", DebugMenuHotkeys[0].rapid)) DebugMenuExecuteHotkey(0);
				if (DebugKeyPressed("num2", DebugMenuHotkeys[1].rapid)) DebugMenuExecuteHotkey(1);
				if (DebugKeyPressed("num3", DebugMenuHotkeys[2].rapid)) DebugMenuExecuteHotkey(2);
				if (DebugKeyPressed("num4", DebugMenuHotkeys[3].rapid)) DebugMenuExecuteHotkey(3);
				if (DebugKeyPressed("num5", DebugMenuHotkeys[4].rapid)) DebugMenuExecuteHotkey(4);
				if (DebugKeyPressed("num6", DebugMenuHotkeys[5].rapid)) DebugMenuExecuteHotkey(5);
				if (DebugKeyPressed("num7", DebugMenuHotkeys[6].rapid)) DebugMenuExecuteHotkey(6);
				if (DebugKeyPressed("num8", DebugMenuHotkeys[7].rapid)) DebugMenuExecuteHotkey(7);
				if (DebugKeyPressed("num9", DebugMenuHotkeys[8].rapid)) DebugMenuExecuteHotkey(8);
				if (DebugKeyPressed("num/", DebugMenuHotkeys[9].rapid)) DebugMenuExecuteHotkey(9);
				if (DebugKeyPressed("num*", DebugMenuHotkeys[10].rapid)) DebugMenuExecuteHotkey(10);
				if (DebugKeyPressed("num-", DebugMenuHotkeys[11].rapid)) DebugMenuExecuteHotkey(11);
				if (DebugKeyPressed("num+", DebugMenuHotkeys[12].rapid)) DebugMenuExecuteHotkey(12);
				if (DebugKeyPressed("f1", DebugMenuHotkeys[13].rapid)) DebugMenuExecuteHotkey(13);
				if (DebugKeyPressed("f2", DebugMenuHotkeys[14].rapid)) DebugMenuExecuteHotkey(14);
				if (DebugKeyPressed("f3", DebugMenuHotkeys[15].rapid)) DebugMenuExecuteHotkey(15);
				if (DebugKeyPressed("f4", DebugMenuHotkeys[16].rapid)) DebugMenuExecuteHotkey(16);
				if (DebugKeyPressed("f5", DebugMenuHotkeys[17].rapid)) DebugMenuExecuteHotkey(17);
				if (DebugKeyPressed("f6", DebugMenuHotkeys[18].rapid)) DebugMenuExecuteHotkey(18);
				if (DebugKeyPressed("f7", DebugMenuHotkeys[19].rapid)) DebugMenuExecuteHotkey(19);
				if (DebugKeyPressed("f8", DebugMenuHotkeys[20].rapid)) DebugMenuExecuteHotkey(20);
				if (DebugKeyPressed("f9", DebugMenuHotkeys[21].rapid)) DebugMenuExecuteHotkey(21);
				if (DebugKeyPressed("f10", DebugMenuHotkeys[22].rapid)) DebugMenuExecuteHotkey(22);
				if (DebugKeyPressed("f11", DebugMenuHotkeys[23].rapid)) DebugMenuExecuteHotkey(23);
				if (DebugKeyPressed("f12", DebugMenuHotkeys[24].rapid)) DebugMenuExecuteHotkey(24);
			}

			if (DebugMenuShowValuesMode)
			{
				if (DebugMenuDebugAddressShowValues.size() > 0)
				{
					DebugDrawDebugAddresses();
				}
			}

		}

		if (TASPlayScript)
		{
			_DebugDrawRectangle(1845, 5, 70, 26, ColorBlack, 0.8f);
			_DebugDrawRectangle(1850, 12, 12, 12, ColorGreen, 1.0f);
			_DebugDrawText("Play", 1865, 7, FontMedium, ColorWhite, 1.0f, "left");
		}
		else if (TASRecordScript)
		{
			_DebugDrawRectangle(1845, 5, 70, 26, ColorBlack, 0.8f);
			_DebugDrawRectangle(1850, 10, 12, 12, ColorRed, 1.0f);
			_DebugDrawText("Rec.", 1865, 7, FontMedium, ColorWhite, 1.0f, "left");
		}

		// Debugmod frame logic
		pOnFrameDebugMod();

		_DrawMenu();
	}

	DebugMenuGeneralFrameskip++;
	if (DebugMenuGeneralFrameskip == DebugMenuGeneralFrameskipFactor + DebugMenuSettingsPerformanceModeFrameskipFactor)
	{
		DebugMenuGeneralFrameskip = 0;
		DebugMenuCanDraw = true;
	}

	DebugMenuNotImportantSettingsFrameSkip++;
	if (DebugMenuNotImportantSettingsFrameSkip == 5) DebugMenuNotImportantSettingsFrameSkip = 0;
}





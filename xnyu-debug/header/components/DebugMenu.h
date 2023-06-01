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
bool DebugMenuShowCursorMode = false;
bool DebugMenuHotkeyOverlayMode = false;


int DebugMenuShowValuesModeUpdateIntervall = 200;
std::vector<std::string> DebugMenuShowValuesModeData;

bool DebugMenuInitSwitch = true;
bool DebugMenuCanDraw = true;
int DebugMenuGeneralFrameskip = 0;
int DebugMenuGeneralFrameskipFactor = 3;
int DebugMenuSettingsPerformanceModeFrameskipFactor = 7;
int DebugMenuNotImportantSettingsFrameSkip = 0;
int DebugHotkeysActiveSlot = 0;

int TextIndexPointerBlinkCounter = 0;
bool TextIndexPointerBlink = 0;
int TextIndexPointer = 0;

// Cursor
POINT DebugMenuCursorPosition;

// Menu Selector

std::vector<std::string> DebugMenuSlotName;
std::vector<std::vector<DebugFunction>> DebugMenuHotkeys;
std::vector<std::vector<std::string>> DebugMenuParameter;
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
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 58, 599, 274, 639 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 58, 713, 274, 753 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 58, 835, 274, 875 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 1584, 975, 1613, 1003 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 1621, 975, 1650, 1003 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 1658, 975, 1687, 1003 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 1695, 975, 1724, 1003 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 1732, 975, 1761, 1003 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 1769, 975, 1798, 1003 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 1806, 975, 1835, 1003 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 1843, 975, 1872, 1003 });
	DebugMenuOverviewHoverBoxes.push_back(RECT{ 1584, 1011, 1872, 1037 });

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
		childrenRects.push_back(RECT{ 712, 975, 928, 1016 });
		childrenRects.push_back(RECT{ 989, 975, 1205, 1016 });
		for (int k = 0; k < SavefileParents[i].fields.size(); k++)
		{
			//childrenRects.push_back(RECT{ 60 + (360 * crow), 165 + (60 * ccol), 60 + (360 * crow) + 360, 165 + (60 * ccol) + 30 });
			childrenRects.push_back(RECT{ 60 + (360 * crow) - 3, 165 + (60 * ccol) + 30 - 3, 60 + (360 * crow) - 3 + 306, 165 + (60 * ccol) + 60 - 1 });
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
	for (int k = 0; k < 8; k++)
	{
		std::vector<DebugFunction> subListFun;
		std::vector<std::string> subListStr;
		for (int i = 0; i < 25; i++) subListFun.push_back(tmp);
		for (int i = 0; i < 25; i++) subListStr.push_back("");
		DebugMenuHotkeys.push_back(subListFun);
		DebugMenuParameter.push_back(subListStr);
		DebugMenuSlotName.push_back("Slot " + std::to_string(k));
	}
}

void DebugMenuInitSaveEditor()
{

}


void DebugMenuInitSettings()
{
	for (int f = 0; f < 8; f++)
	{
		std::ifstream file(GlobalSettings.config_debugconfig_directory + "hotkeys" + std::to_string(f) + ".txt");

		if (file.good())
		{
			std::string script = "";

			bool firstSlotName = true;
			while (!file.eof()) {

				// Read line
				std::string line = "";
				std::getline(file, line);

				if (firstSlotName)
				{
					DebugMenuSlotName[f] = line;
					firstSlotName = false;
					continue;
				}

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
										DebugMenuHotkeys[f][index] = DebugFunctions[i].functions[k];
										DebugMenuParameter[f][index] = paramsAll;
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
		for (int i = 0; i < DebugMenuHotkeys[f].size(); i++)
		{
			if (DebugMenuHotkeys[f][i].nameFull != "- EMPTY -")
			{
				if (DebugMenuParameter[f][i] != "")
				{
					if (DebugMenuHotkeys[f][i].parameter.size() > 0)
					{
						std::string paramCopy = DebugMenuParameter[f][i];
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
							for (int k = 0; k < DebugMenuHotkeys[f][i].parameter.size(); k++) SetVariable(&DebugMenuHotkeys[f][i].parameter[k], "none");
						}
						else
						{
							std::vector<std::string> params;
							splitStringVector(params, paramCopy, ",");
							for (int k = 0; k < params.size(); k++)
							{
								if (params[k] == "")
								{
									SetVariable(&DebugMenuHotkeys[f][i].parameter[k], "none");
								}
								else
								{
									if (DebugMenuHotkeys[f][i].parameter[k].type.find("float") != std::string::npos && params[k].find(".") == std::string::npos) params[k] = params[k] + ".0";
									SetVariable(&DebugMenuHotkeys[f][i].parameter[k], params[k]);
								}
								if (k + 1 > DebugMenuHotkeys[f][i].parameter.size()) break;
							}
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
			TextIndexPointer = 0;

			if (id == 0 && GlobalDebugFeatures.debugAddress) DebugMenuShowValuesMode = !DebugMenuShowValuesMode;
			if (id == 1 && GlobalDebugFeatures.debugAddress)
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
			if (id == 3 && GlobalDebugFeatures.supervision)
			{
				DebugMenuSuperVisionMode = !DebugMenuSuperVisionMode;
				pToggleSupervisionRoutine(DebugMenuSuperVisionMode);
			}
			if (id == 4) DebugMenuShowCursorMode = !DebugMenuShowCursorMode;
			if (id == 5) DebugMenuSettingsPerformanceMode = !DebugMenuSettingsPerformanceMode;
			if (id == 6) DebugMenuHotkeyOverlayMode = !DebugMenuHotkeyOverlayMode;

			if (id > 6 && id < 15)
			{
				for (int i = 0; i < 8; i++)
				{
					if (id == 7 + i)
					{
						DebugHotkeysActiveSlot = i;
						if (DebugMenuParameterFocus == -2) TextIndexPointer = DebugMenuSlotName[DebugHotkeysActiveSlot].length();
					}
				}
			}

			if (id == 15)
			{
				DebugMenuParameterFocus = -2;
				TextIndexPointer = DebugMenuSlotName[DebugHotkeysActiveSlot].length();
			}

			if (id - 16 >= 0 && (id - 16) % 2 == 0)
			{
				DebugMenuFunctionFocus = (id - 16) / 2; // Debug function focus
				DebugMenuMainForm = DEBUGMENUFORM::FORM_DEBUGFUNCTIONS;
				DebugMenuSubForm = 0;
				DebugMenuDebugFunctionsParentFocus = -1;
			}
			if (id - 17 >= 0 && (id - 17) % 2 == 0)
			{
				DebugMenuParameterFocus = (id - 17) / 2; // Debug function parameter focus
				TextIndexPointer = DebugMenuParameter[DebugHotkeysActiveSlot][DebugMenuParameterFocus].length();
			}
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
					if (focusAddress.nameFull == DebugMenuHotkeys[DebugHotkeysActiveSlot][DebugMenuFunctionFocus].nameFull)
					{
						DebugFunction tmp;
						tmp.nameFull = "- EMPTY -";
						DebugMenuHotkeys[DebugHotkeysActiveSlot][DebugMenuFunctionFocus] = tmp;
					}
					else
					{
						DebugMenuHotkeys[DebugHotkeysActiveSlot][DebugMenuFunctionFocus] = focusAddress;
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
					pUpdateSavefile(&SavefileParents[SavefileParentFocus]);
				}

				if (id == 2)
				{
					// Reload
					pLoadSavefile(&SavefileParents[SavefileParentFocus]);
				}

				if (id > 2)
				{
					if (id - 3 >= 0)
					{
						SavefileFielFocus = id - 3;
						TextIndexPointer = SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value.length();
					}
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

			if (id - 16 >= 0 && (id - 16) % 2 == 0)
			{
				DebugFunction tmp;
				tmp.nameFull = "- EMPTY -";
				DebugMenuHotkeys[DebugHotkeysActiveSlot][(id - 16) / 2] = tmp;
			}
			if (id - 17 >= 0 && (id - 17) % 2 == 0) DebugMenuParameter[DebugHotkeysActiveSlot][(id - 17) / 2] = "";
		}
	}

	int DebugMenuDebugAddressesParentFocus = 0;
	int DebugMenuDebugFunctionsParentFocus = 0;
	std::vector<DebugAddress> DebugMenuDebugAddressShowValues;
}

std::vector<RECT> HoverBoxesTarget;
void _DetectHoverBoxesTarget()
{
	if (DebugMenuMainForm == DEBUGMENUFORM::FORM_OVERVIEW) HoverBoxesTarget = DebugMenuOverviewHoverBoxes;
	else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_DEBUGVALUES)
	{
		if (DebugMenuSubForm == 0)
		{
			HoverBoxesTarget = DebugMenuDebugAddressesParentsHoverBoxes;
		}
		if (DebugMenuSubForm == 1)
		{
			HoverBoxesTarget = DebugMenuDebugAddressesChildsHoverBoxes[DebugMenuDebugAddressesParentFocus];
		}
	}
	else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_DEBUGFUNCTIONS)
	{
		if (DebugMenuSubForm == 0)
		{
			HoverBoxesTarget = DebugMenuDebugFunctionsParentsHoverBoxes;
		}
		if (DebugMenuSubForm == 1)
		{
			HoverBoxesTarget = DebugMenuDebugFunctionsChildsHoverBoxes[DebugMenuDebugFunctionsParentFocus];
		}
	}
	else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_SAVEFILEEDITOR)
	{
		if (DebugMenuSubForm == 0)
		{
			HoverBoxesTarget = DebugMenuSavefileEditorFilesHoverBoxes;
		}
		if (DebugMenuSubForm == 1)
		{
			HoverBoxesTarget = DebugMenuSavefileEditorParentsHoverBoxes;
		}
		if (DebugMenuSubForm == 2)
		{
			HoverBoxesTarget = DebugMenuSavefileEditorChildsHoverBoxes[SavefileParentFocus];
		}
	}
}

void _DrawHoverBoxes()
{
	for (int i = 0; i < HoverBoxesTarget.size(); i++)
	{
		if (DebugMenuCursorPosition.x > HoverBoxesTarget[i].left && DebugMenuCursorPosition.x < HoverBoxesTarget[i].right && DebugMenuCursorPosition.y > HoverBoxesTarget[i].top && DebugMenuCursorPosition.y < HoverBoxesTarget[i].bottom)
		{
			_DebugDrawRectangle(HoverBoxesTarget[i].left, HoverBoxesTarget[i].top, HoverBoxesTarget[i].right - HoverBoxesTarget[i].left, HoverBoxesTarget[i].bottom - HoverBoxesTarget[i].top, ColorYellow, 0.7f);
			break;
		}
	}
}

void _CheckHoverBoxes()
{
	for (int i = 0; i < HoverBoxesTarget.size(); i++)
	{
		if (DebugMenuCursorPosition.x > HoverBoxesTarget[i].left && DebugMenuCursorPosition.x < HoverBoxesTarget[i].right && DebugMenuCursorPosition.y > HoverBoxesTarget[i].top && DebugMenuCursorPosition.y < HoverBoxesTarget[i].bottom)
		{
			if (DebugKeyPressed("lmb") || DebugKeyPressed("mb")) DebugMenuHandleClick(i, true);
			if (DebugKeyPressed("rmb")) DebugMenuHandleClick(i, false);
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
	if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].nameParent == "TAS")
	{
		if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].nameChild == "PlayScript")
		{
			std::string _script = "";
			if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value != "none" && !DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value.empty()) _script = GetVariableString(&DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0]);
			_script = _script + ";";
			pTASPlayScript((char*)_script.c_str());
		}
		else if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].nameChild == "RecordScript")
		{
			std::string _script = "";
			if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value != "none" && !DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value.empty()) _script = GetVariableString(&DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0]);
			_script = _script + ";";
			pTASRecordScript((char*)_script.c_str());
		}
	}
	else if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].nameParent == "DebugMenu")
	{
		if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].nameChild == "SetHotkeySlot")
		{
			if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value != "none" && !DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value.empty())
			{
				int index = GetVariableInt32(&DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0]);
				if (index > 0 && index < 9) DebugHotkeysActiveSlot = index - 1;
			}
		}
		else if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].nameChild == "ChangeHotkeySlot")
		{
			if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value != "none" && !DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value.empty())
			{
				int index = GetVariableInt32(&DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0]);
				DebugHotkeysActiveSlot += index;
				if (DebugHotkeysActiveSlot < 0) DebugHotkeysActiveSlot = 7;
				if (DebugHotkeysActiveSlot > 7) DebugHotkeysActiveSlot = 0;
			}
		}
		else if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].nameChild == "EnablePerformancemode")
		{
			if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value != "none" && !DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value.empty())
			{
				DebugMenuSettingsPerformanceMode = GetVariableBool(&DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0]);
			}
			else DebugMenuSettingsPerformanceMode = !DebugMenuSettingsPerformanceMode;
		}
		else if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].nameChild == "EnableDebugValues")
		{
			if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value != "none" && !DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value.empty())
			{
				DebugMenuShowValuesMode = GetVariableBool(&DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0]);
			}
			else DebugMenuShowValuesMode = !DebugMenuShowValuesMode;
		}
		else if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].nameChild == "EnableCursorPosition")
		{
			if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value != "none" && !DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value.empty())
			{
				DebugMenuShowCursorMode = GetVariableBool(&DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0]);
			}
			else DebugMenuShowCursorMode = !DebugMenuShowCursorMode;
		}
		else if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].nameChild == "EnableHotkeyOverlay")
		{
			if (DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value != "none" && !DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0].value.empty())
			{
				DebugMenuHotkeyOverlayMode = GetVariableBool(&DebugMenuHotkeys[DebugHotkeysActiveSlot][id].parameter[0]);
			}
			else DebugMenuHotkeyOverlayMode = !DebugMenuHotkeyOverlayMode;
		}
	}
	else
	{
		pExecuteDebugFunction(&DebugMenuHotkeys[DebugHotkeysActiveSlot][id]);
	}
}

std::string DebugMenuHotkeyDisplayName(int id)
{
	return DebugMenuHotkeys[DebugHotkeysActiveSlot][id].nameFull;
}

std::string DebugMenuHotkeyDisplayParameter(int id)
{
	return "Parameter: " + DebugMenuParameter[DebugHotkeysActiveSlot][id];
}

int DebugMenuCheckTextInput(std::string* text, int indexPointer)
{
	int oldLength = text->length();
	int indexPointerOld = indexPointer;

	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000 || GetAsyncKeyState(VK_RSHIFT) & 0x8000)
	{
		if (DebugKeyPressed("a")) text->insert(indexPointer, "A");
		else if (DebugKeyPressed("b")) text->insert(indexPointer, "B");
		else if (DebugKeyPressed("c")) text->insert(indexPointer, "C");
		else if (DebugKeyPressed("d")) text->insert(indexPointer, "D");
		else if (DebugKeyPressed("e")) text->insert(indexPointer, "E");
		else if (DebugKeyPressed("f")) text->insert(indexPointer, "F");
		else if (DebugKeyPressed("g")) text->insert(indexPointer, "G");
		else if (DebugKeyPressed("h")) text->insert(indexPointer, "H");
		else if (DebugKeyPressed("i")) text->insert(indexPointer, "I");
		else if (DebugKeyPressed("j")) text->insert(indexPointer, "J");
		else if (DebugKeyPressed("k")) text->insert(indexPointer, "K");
		else if (DebugKeyPressed("l")) text->insert(indexPointer, "L");
		else if (DebugKeyPressed("m")) text->insert(indexPointer, "M");
		else if (DebugKeyPressed("n")) text->insert(indexPointer, "N");
		else if (DebugKeyPressed("o")) text->insert(indexPointer, "O");
		else if (DebugKeyPressed("p")) text->insert(indexPointer, "P");
		else if (DebugKeyPressed("q")) text->insert(indexPointer, "Q");
		else if (DebugKeyPressed("r")) text->insert(indexPointer, "R");
		else if (DebugKeyPressed("s")) text->insert(indexPointer, "S");
		else if (DebugKeyPressed("t")) text->insert(indexPointer, "T");
		else if (DebugKeyPressed("u")) text->insert(indexPointer, "U");
		else if (DebugKeyPressed("v")) text->insert(indexPointer, "V");
		else if (DebugKeyPressed("w")) text->insert(indexPointer, "W");
		else if (DebugKeyPressed("x")) text->insert(indexPointer, "X");
		else if (DebugKeyPressed("y")) text->insert(indexPointer, "Y");
		else if (DebugKeyPressed("z")) text->insert(indexPointer, "Z");
		else if (DebugKeyPressed("d0")) text->insert(indexPointer, "=");
		else if (DebugKeyPressed("d1")) text->insert(indexPointer, "!");
		else if (DebugKeyPressed("d2")) text->insert(indexPointer, "\"");
		else if (DebugKeyPressed("d3")) text->insert(indexPointer, "§");
		else if (DebugKeyPressed("d4")) text->insert(indexPointer, "$");
		else if (DebugKeyPressed("d5")) text->insert(indexPointer, "%");
		else if (DebugKeyPressed("d6")) text->insert(indexPointer, "&");
		else if (DebugKeyPressed("d7")) text->insert(indexPointer, "/");
		else if (DebugKeyPressed("d8")) text->insert(indexPointer, "(");
		else if (DebugKeyPressed("d9")) text->insert(indexPointer, ")");
		else if (DebugKeyPressed("comma")) text->insert(indexPointer, ";");
		else if (DebugKeyPressed("dot")) text->insert(indexPointer, ":");
		else if (DebugKeyPressed("plus")) text->insert(indexPointer, "*");
		else if (DebugKeyPressed("minus")) text->insert(indexPointer, "_");
	}
	else
	{
		if (DebugKeyPressed("a")) text->insert(indexPointer, "a");
		else if (DebugKeyPressed("b")) text->insert(indexPointer, "b");
		else if (DebugKeyPressed("c")) text->insert(indexPointer, "c");
		else if (DebugKeyPressed("d")) text->insert(indexPointer, "d");
		else if (DebugKeyPressed("e")) text->insert(indexPointer, "e");
		else if (DebugKeyPressed("f")) text->insert(indexPointer, "f");
		else if (DebugKeyPressed("g")) text->insert(indexPointer, "g");
		else if (DebugKeyPressed("h")) text->insert(indexPointer, "h");
		else if (DebugKeyPressed("i")) text->insert(indexPointer, "i");
		else if (DebugKeyPressed("j")) text->insert(indexPointer, "j");
		else if (DebugKeyPressed("k")) text->insert(indexPointer, "k");
		else if (DebugKeyPressed("l")) text->insert(indexPointer, "l");
		else if (DebugKeyPressed("m")) text->insert(indexPointer, "m");
		else if (DebugKeyPressed("n")) text->insert(indexPointer, "n");
		else if (DebugKeyPressed("o")) text->insert(indexPointer, "o");
		else if (DebugKeyPressed("p")) text->insert(indexPointer, "p");
		else if (DebugKeyPressed("q")) text->insert(indexPointer, "q");
		else if (DebugKeyPressed("r")) text->insert(indexPointer, "r");
		else if (DebugKeyPressed("s")) text->insert(indexPointer, "s");
		else if (DebugKeyPressed("t")) text->insert(indexPointer, "t");
		else if (DebugKeyPressed("u")) text->insert(indexPointer, "u");
		else if (DebugKeyPressed("v")) text->insert(indexPointer, "v");
		else if (DebugKeyPressed("w")) text->insert(indexPointer, "w");
		else if (DebugKeyPressed("x")) text->insert(indexPointer, "x");
		else if (DebugKeyPressed("y")) text->insert(indexPointer, "y");
		else if (DebugKeyPressed("z")) text->insert(indexPointer, "z");
		else if (DebugKeyPressed("d0")) text->insert(indexPointer, "0");
		else if (DebugKeyPressed("d1")) text->insert(indexPointer, "1");
		else if (DebugKeyPressed("d2")) text->insert(indexPointer, "2");
		else if (DebugKeyPressed("d3")) text->insert(indexPointer, "3");
		else if (DebugKeyPressed("d4")) text->insert(indexPointer, "4");
		else if (DebugKeyPressed("d5")) text->insert(indexPointer, "5");
		else if (DebugKeyPressed("d6")) text->insert(indexPointer, "6");
		else if (DebugKeyPressed("d7")) text->insert(indexPointer, "7");
		else if (DebugKeyPressed("d8")) text->insert(indexPointer, "8");
		else if (DebugKeyPressed("d9")) text->insert(indexPointer, "9");
		else if (DebugKeyPressed("comma")) text->insert(indexPointer, ",");
		else if (DebugKeyPressed("dot")) text->insert(indexPointer, ".");
		else if (DebugKeyPressed("plus")) text->insert(indexPointer, "+");
		else if (DebugKeyPressed("minus")) text->insert(indexPointer, "-");
	}

	if (DebugKeyPressed("space")) text->insert(indexPointer, " ");
	if (DebugKeyPressed("back")) if (indexPointer > 0) text->erase(indexPointer - 1, 1);
	if (DebugKeyPressed("aleft")) if (indexPointer > 0) indexPointer--;
	if (DebugKeyPressed("aright")) if (indexPointer < text->length()) indexPointer++;

	int newLength = text->length();
	if (oldLength > newLength)
	{
		indexPointer -= oldLength - newLength;
		if (indexPointer < 0) indexPointer = 0;
	}
	if (oldLength < newLength)
	{
		indexPointer += newLength - oldLength;
	}
	if (indexPointer != indexPointerOld)
	{
		TextIndexPointerBlink = true;
		TextIndexPointerBlinkCounter = 0;
	}

	return indexPointer;
}



RECT OriginalCursorClip;
RECT CustomCursorClip;
POINT OriginalCursorPos;
POINT CustomCursorPos;

void __cdecl DebugMenuOpen()
{
	DebugMenuOpened = true;
	DebugMenuInitSwitch = true;
	DebugMenuMainForm = DEBUGMENUFORM::FORM_OVERVIEW;
	DebugMenuSubForm = 0;
	DebugMenuMainFormLast = DEBUGMENUFORM::FORM_OVERVIEW;
	DebugMenuSubFormLast = 0;
	RawInputDisableForGame = true;

	_DetectHoverBoxesTarget();

	DebugFunction tmp;
	tmp.nameFull = "- EMPTY -";
	for (int k = 0; k < 8; k++)
	{
		std::vector<DebugFunction> subListFun;
		std::vector<std::string> subListStr;
		for (int i = 0; i < 25; i++) subListFun.push_back(tmp);
		for (int i = 0; i < 25; i++) subListStr.push_back("");
		DebugMenuHotkeys.push_back(subListFun);
		DebugMenuParameter.push_back(subListStr);
		DebugMenuSlotName.push_back("Slot " + std::to_string(k));
	}
	
	for (int f = 0; f < 8; f++)
	{
		std::ifstream file(GlobalSettings.config_debugconfig_directory + "hotkeys" + std::to_string(f) + ".txt");

		if (file.good())
		{
			std::string script = "";

			bool firstSlotName = true;

			while (!file.eof()) {
				// Read line
				std::string line = "";
				std::getline(file, line);

				if (firstSlotName)
				{
					DebugMenuSlotName[f] = line;
					firstSlotName = false;
					continue;
				}

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
										DebugMenuHotkeys[f][index] = DebugFunctions[i].functions[k];
										DebugMenuParameter[f][index] = paramsAll;
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

	for (int f = 0; f < 8; f++)
	{
		std::ofstream file(GlobalSettings.config_debugconfig_directory + "hotkeys" + std::to_string(f) + ".txt");

		file << DebugMenuSlotName[f] << std::endl;
		for (int i = 0; i < DebugMenuHotkeys[f].size(); i++)
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

			if (DebugMenuHotkeys[f][i].nameFull != "- EMPTY -") line = line + DebugMenuHotkeys[f][i].nameFull + "(" + DebugMenuParameter[f][i] + ");";
			else line = line + ";";

			file << line << std::endl;
		}

		file.close();

		// Update debug function parameter
		for (int i = 0; i < DebugMenuHotkeys[f].size(); i++)
		{
			if (DebugMenuHotkeys[f][i].nameFull != "- EMPTY -")
			{
				if (DebugMenuParameter[f][i] != "")
				{
					if (DebugMenuHotkeys[f][i].parameter.size() > 0)
					{
						std::string paramCopy = DebugMenuParameter[f][i];
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
							for (int k = 0; k < DebugMenuHotkeys[f][i].parameter.size(); k++) SetVariable(&DebugMenuHotkeys[f][i].parameter[k], "none");
						}
						else
						{
							std::vector<std::string> params;
							splitStringVector(params, paramCopy, ",");
							for (int k = 0; k < params.size(); k++)
							{
								if (params[k].empty())
								{
									SetVariable(&DebugMenuHotkeys[f][i].parameter[k], "none");
								}
								else
								{
									if (DebugMenuHotkeys[f][i].parameter[k].type.find("float") != std::string::npos && params[k].find(".") == std::string::npos) params[k] = params[k] + ".0";
									SetVariable(&DebugMenuHotkeys[f][i].parameter[k], params[k]);
								}
								if (k + 1 > DebugMenuHotkeys[f][i].parameter.size()) break;
							}
						}
					}
				}
				else
				{
					for (int k = 0; k < DebugMenuHotkeys[f][i].parameter.size(); k++) SetVariable(&DebugMenuHotkeys[f][i].parameter[k], "none");
				}
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
				text = DebugMenuDebugAddressShowValues[i].nameChild + ": " + DebugMenuDebugAddressShowValues[i].value.value;
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
				_DebugDrawText("- " + DebugMenuDebugAddressShowValues[i].nameParent + " -", 5 + (row > 0 ? DebugMenuDebugAddressShowValuesRowWidth[row - 1] : 0), 5 + (col * DebugMenuDebugAddressShowValuesRowHeight), FontSmall, ColorCyan, 1.0f, "left");
				i--;
			}
			else
			{
				pGetDebugAddressValue(&DebugMenuDebugAddressShowValues[i]);
				std::string text = DebugMenuDebugAddressShowValues[i].nameChild + ": " + DebugMenuDebugAddressShowValues[i].value.value;
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



void DebugDrawHotkeyOverlay()
{
	// Width detection
	int widthSlots = 0;
	int widthNums = 0;
	int widthFs = 0;
	for (int i = 0; i < 25; i++)
	{
		if (i < 8)
		{
			SIZE textSize;
			GetTextExtentPoint32A(hdc, DebugMenuSlotName[i].c_str(), (int)DebugMenuSlotName[i].length(), &textSize);
			if (textSize.cx > widthSlots) widthSlots = textSize.cx;
		}
		SIZE textSize;
		std::string targetText = "F10: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][i].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][i].nameFull);
		GetTextExtentPoint32A(hdc, targetText.c_str(), (int)targetText.length(), &textSize);
		if (i < 13)
		{
			if (textSize.cx > widthNums) widthNums = textSize.cx;
		}
		else
		{
			if (textSize.cx > widthFs) widthFs = textSize.cx;
		}
	}

	//Drawing
	_DebugDrawRectangle(0, 850, widthSlots + widthNums + widthFs + 116, 230, ColorBlack, 0.8f);

	_DebugDrawText("Active Slot:", 3, 853, FontSmall, ColorWhite, 1.0f);
	for (int i = 0; i < 8; i++)
	{
		_DebugDrawText(DebugMenuSlotName[i], 3, 868 + (i * 15), FontSmall, DebugHotkeysActiveSlot == i ? ColorGreen : ColorRed, 1.0f);
	}

	_DebugDrawText("Functions:", 3 + widthSlots + 30, 853, FontSmall, ColorWhite, 1.0f);
	_DebugDrawText("N1: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][0].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][0].nameFull), 3 + widthSlots + 30, 868 + (0 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("N2: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][1].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][1].nameFull), 3 + widthSlots + 30, 868 + (1 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("N3: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][2].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][2].nameFull), 3 + widthSlots + 30, 868 + (2 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("N4: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][3].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][3].nameFull), 3 + widthSlots + 30, 868 + (3 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("N5: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][4].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][4].nameFull), 3 + widthSlots + 30, 868 + (4 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("N6: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][5].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][5].nameFull), 3 + widthSlots + 30, 868 + (5 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("N7: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][6].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][6].nameFull), 3 + widthSlots + 30, 868 + (6 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("N8: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][7].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][7].nameFull), 3 + widthSlots + 30, 868 + (7 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("N9: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][8].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][8].nameFull), 3 + widthSlots + 30, 868 + (8 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("N/: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][9].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][9].nameFull), 3 + widthSlots + 30, 868 + (9 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("N*: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][10].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][10].nameFull), 3 + widthSlots + 30, 868 + (10 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("N-: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][11].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][11].nameFull), 3 + widthSlots + 30, 868 + (11 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("N+: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][12].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][12].nameFull), 3 + widthSlots + 30, 868 + (12 * 15), FontSmall, ColorYellow, 1.0f);

	_DebugDrawText("F1:  " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][13].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][13].nameFull), 3 + widthSlots + widthNums + 60, 868 + (0 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("F2:  " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][14].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][14].nameFull), 3 + widthSlots + widthNums + 60, 868 + (1 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("F3:  " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][15].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][15].nameFull), 3 + widthSlots + widthNums + 60, 868 + (2 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("F4:  " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][16].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][16].nameFull), 3 + widthSlots + widthNums + 60, 868 + (3 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("F5:  " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][17].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][17].nameFull), 3 + widthSlots + widthNums + 60, 868 + (4 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("F6:  " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][18].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][18].nameFull), 3 + widthSlots + widthNums + 60, 868 + (5 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("F7:  " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][19].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][19].nameFull), 3 + widthSlots + widthNums + 60, 868 + (6 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("F8:  " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][20].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][20].nameFull), 3 + widthSlots + widthNums + 60, 868 + (7 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("F9:  " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][21].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][21].nameFull), 3 + widthSlots + widthNums + 60, 868 + (8 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("F10: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][22].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][22].nameFull), 3 + widthSlots + widthNums + 60, 868 + (9 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("F11: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][23].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][23].nameFull), 3 + widthSlots + widthNums + 60, 868 + (10 * 15), FontSmall, ColorYellow, 1.0f);
	_DebugDrawText("F12: " + (DebugMenuHotkeys[DebugHotkeysActiveSlot][24].nameFull == "- EMPTY -" ? "" : DebugMenuHotkeys[DebugHotkeysActiveSlot][24].nameFull), 3 + widthSlots + widthNums + 60, 868 + (11 * 15), FontSmall, ColorYellow, 1.0f);
}



int DebugMenuHotkeyDelegationIndex = 0;

void DebugMenuMainRoutine()
{
	// Check for input
	if (!TASPlayScript && !TASRecordScript)
	{
		// Customize the cursor
		GetCursorPos(&DebugMenuCursorPosition);
		ScreenToClient(MainWindowHandle, &DebugMenuCursorPosition);
	}
	std::memcpy(&DebugInputLast, &DebugInputCurrent, sizeof(GameInput));
	GetRawInput(false, &DebugInputCurrent, "all");

	GetWindowRect(MainWindowHandle, &MainWindowRect);
	
	MainWindowActive = CheckWindowActive();

	if (DebugMenuOpened)
	{
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

			if (DebugMenuMainForm == DEBUGMENUFORM::FORM_OVERVIEW)
			{
				if (DebugMenuParameterFocus > -1) TextIndexPointer = DebugMenuCheckTextInput(&DebugMenuParameter[DebugHotkeysActiveSlot][DebugMenuParameterFocus], TextIndexPointer);
				if (DebugMenuParameterFocus == -2) TextIndexPointer = DebugMenuCheckTextInput(&DebugMenuSlotName[DebugHotkeysActiveSlot], TextIndexPointer);
			}
			if (DebugMenuMainForm == DEBUGMENUFORM::FORM_SAVEFILEEDITOR && DebugMenuSubForm == 2)
			{
				if (SavefileFielFocus > -1) TextIndexPointer = DebugMenuCheckTextInput(&SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value, TextIndexPointer);
			}

		}

		_CheckHoverBoxes();

		if (DebugMenuCanDraw)
		{
			ClearSurface(DebugMenuMainForm, DebugMenuSubForm);
			
			// Draw Hoverboxes
			_DetectHoverBoxesTarget();
			_DrawHoverBoxes();

			// Draw overview
			if (DebugMenuMainForm == DEBUGMENUFORM::FORM_OVERVIEW)
			{
				_DebugDrawText(GlobalDebugFeatures.debugAddress ? (DebugMenuShowValuesMode ? "Enabled" : "Disabled") : "Not Available", 160, 260, FontBigMedium, DebugMenuShowValuesMode ? ColorDarkGreen : ColorRed, 1.0f, "center");
				_DebugDrawText(GlobalDebugFeatures.debugAddress ? "Edit" : "Not Available", 390, 260, FontBigMedium, ColorBlack, 1.0f, "center");
				_DebugDrawText(GlobalDebugFeatures.savefileEditor ? "Edit" : "Not Available", 160, 370, FontBigMedium, GlobalDebugFeatures.savefileEditor ? ColorBlack : ColorGray, 1.0f, "center");
				_DebugDrawText(GlobalDebugFeatures.supervision ? (DebugMenuSuperVisionMode ? "Enabled" : "Disabled") : "Not Available", 160, 493, FontBigMedium, GlobalDebugFeatures.supervision ? (DebugMenuSuperVisionMode ? ColorDarkGreen : ColorRed) : ColorGray, 1.0f, "center");
				_DebugDrawText(DebugMenuShowCursorMode ? "Enabled" : "Disabled", 160, 608, FontBigMedium, DebugMenuShowCursorMode ? ColorDarkGreen : ColorRed, 1.0f, "center");
				_DebugDrawText(DebugMenuSettingsPerformanceMode ? "Enabled" : "Disabled", 160, 721, FontBigMedium, DebugMenuSettingsPerformanceMode ? ColorDarkGreen : ColorRed, 1.0f, "center");
				_DebugDrawText(DebugMenuHotkeyOverlayMode ? "Enabled" : "Disabled", 160, 842, FontBigMedium, DebugMenuHotkeyOverlayMode ? ColorDarkGreen : ColorRed, 1.0f, "center");

				for (int i = 0; i < 13; i++)
				{
					_DebugDrawText(DebugMenuHotkeys[DebugHotkeysActiveSlot][i].nameFull, 1245, 200 + (65 * i), FontMedium, ColorBlack, 1.0f, "center");
					_DebugDrawText(DebugMenuParameter[DebugHotkeysActiveSlot][i], 1245, 228 + (65 * i), FontMedium, ColorBlack, 1.0f, "center");
				}

				for (int i = 0; i < 12; i++)
				{
					_DebugDrawText(DebugMenuHotkeys[DebugHotkeysActiveSlot][i + 13].nameFull, 1690, 200 + (65 * i), FontMedium, ColorBlack, 1.0f, "center");
					_DebugDrawText(DebugMenuParameter[DebugHotkeysActiveSlot][i + 13], 1690, 228 + (65 * i), FontMedium, ColorBlack, 1.0f, "center");
				}

				for (int i = 0; i < 8; i++)
				{
					if (DebugHotkeysActiveSlot == i)
					{
						_DebugDrawRectangle(1584 + (i * 37), 975, 29, 28, ColorGreen, 1.0f);
						_DebugDrawText(std::to_string(i + 1), 1599 + (i * 37), 980, FontMedium, ColorRed, 1.0f, "center");
					}
					else
					{
						_DebugDrawText(std::to_string(i + 1), 1599 + (i * 37), 980, FontMedium, ColorBlack, 1.0f, "center");
					}
				}

				// Draw slot name
				_DebugDrawText(DebugMenuSlotName[DebugHotkeysActiveSlot], 1728, 1015, FontMedium, ColorBlack, 1.0f, "center");
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
						if (focusFunction.nameFull == DebugMenuHotkeys[DebugHotkeysActiveSlot][DebugMenuFunctionFocus].nameFull) selected = true;

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
					_DebugDrawText("Save", 812, 981, FontBigMedium, ColorBlack, 1.0f, "center");
					_DebugDrawText("Reload", 1089, 981, FontBigMedium, ColorBlack, 1.0f, "center");

					int col = 0;
					int row = 0;
					for (int i = 0; i < SavefileParents[SavefileParentFocus].fields.size(); i++)
					{
						std::string title = SavefileParents[SavefileParentFocus].fields[i].nameChild + " (" + SavefileParents[SavefileParentFocus].fields[i].value.type +")";
						std::string value = SavefileParents[SavefileParentFocus].fields[i].value.value;
						_DebugDrawText(title, 60 + (360 * row), 165 + (60 * col), FontMedium, ColorBlack, 1.0f, "left");
						_DebugDrawRectangle(60 + (360 * row), 165 + (60 * col) + 30, 300, 26, ColorWhite, 1.0f);
						_DebugDrawText(value, 60 + (360 * row) + 150, 165 + (60 * col) + 32, FontMedium, ColorBlack, 1.0f, "center");
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

			// Draw text index pointer
			if (TextIndexPointerBlink)
			{
				SIZE originalSize;
				SIZE partSize;
				std::string targetText = "";
				int targetX = 0;
				int targetY = 0;
				bool canDrawPointerIndex = true;
				if (DebugMenuMainForm == DEBUGMENUFORM::FORM_OVERVIEW)
				{
					if (DebugMenuParameterFocus > -1)
					{
						targetText = DebugMenuParameter[DebugHotkeysActiveSlot][DebugMenuParameterFocus];
						if (DebugMenuParameterFocus < 13)
						{
							targetX = 1245;
							targetY = 228 + (65 * DebugMenuParameterFocus);
						}
						else
						{
							targetX = 1690;
							targetY = 228 + (65 * (DebugMenuParameterFocus - 13));
						}
					}
					else if (DebugMenuParameterFocus == -2)
					{
						targetText = DebugMenuSlotName[DebugHotkeysActiveSlot];
						targetX = 1728;
						targetY = 1015;
					}
					else
					{
						canDrawPointerIndex = false;
					}
				}
				else if (DebugMenuMainForm == DEBUGMENUFORM::FORM_SAVEFILEEDITOR && DebugMenuSubForm == 2)
				{
					if (SavefileFielFocus > -1)
					{
						targetText = SavefileParents[SavefileParentFocus].fields[SavefileFielFocus].value.value;
						targetX = 60 + (360 * (std::floor(SavefileFielFocus / 12))) + 150;
						targetY = 165 + (60 * SavefileFielFocus) + 32;
					}
					else
					{
						canDrawPointerIndex = false;
					}
				}
				else
				{
					canDrawPointerIndex = false;
				}

				if (canDrawPointerIndex)
				{
					GetTextExtentPoint32A(hdc, targetText.c_str(), (int)targetText.length(), &originalSize);
					GetTextExtentPoint32A(hdc, targetText.substr(0, TextIndexPointer).c_str(), (int)TextIndexPointer, &partSize);

					_DebugDrawText("l", (targetX - ((originalSize.cx * 1.5) / 2)) + (partSize.cx * 1.5), targetY, FontMedium, ColorRed, 1.0f, "left");
				}

			}

			// Handle blinker
			TextIndexPointerBlinkCounter++;
			if (TextIndexPointerBlinkCounter > 15)
			{
				TextIndexPointerBlinkCounter = 0;
				TextIndexPointerBlink = !TextIndexPointerBlink;
			}

			// Draw custom cursor
			DrawCursorToTexture(DebugMenuCursorPosition.x, DebugMenuCursorPosition.y);

			DebugMenuCanDraw = false;
		}

	}
	else
	{
		if (DebugMenuInitSwitch)
		{
			DebugMenuGeneralFrameskip = 0;
			DebugMenuCanDraw = true;
			DebugMenuInitSwitch = false;
		}

		if (MainWindowActive)// && !TASPlayScript && !TASRecordScript)
		{
			if (DebugKeyPressed("num0"))
			{
				// Open the menu
				DebugMenuOpen();
			}

			// Hotkeys
			if (DebugKeyPressed("num1", DebugMenuHotkeys[DebugHotkeysActiveSlot][0].rapid)) DebugMenuExecuteHotkey(0);
			if (DebugKeyPressed("num2", DebugMenuHotkeys[DebugHotkeysActiveSlot][1].rapid)) DebugMenuExecuteHotkey(1);
			if (DebugKeyPressed("num3", DebugMenuHotkeys[DebugHotkeysActiveSlot][2].rapid)) DebugMenuExecuteHotkey(2);
			if (DebugKeyPressed("num4", DebugMenuHotkeys[DebugHotkeysActiveSlot][3].rapid)) DebugMenuExecuteHotkey(3);
			if (DebugKeyPressed("num5", DebugMenuHotkeys[DebugHotkeysActiveSlot][4].rapid)) DebugMenuExecuteHotkey(4);
			if (DebugKeyPressed("num6", DebugMenuHotkeys[DebugHotkeysActiveSlot][5].rapid)) DebugMenuExecuteHotkey(5);
			if (DebugKeyPressed("num7", DebugMenuHotkeys[DebugHotkeysActiveSlot][6].rapid)) DebugMenuExecuteHotkey(6);
			if (DebugKeyPressed("num8", DebugMenuHotkeys[DebugHotkeysActiveSlot][7].rapid)) DebugMenuExecuteHotkey(7);
			if (DebugKeyPressed("num9", DebugMenuHotkeys[DebugHotkeysActiveSlot][8].rapid)) DebugMenuExecuteHotkey(8);
			if (DebugKeyPressed("numdiv", DebugMenuHotkeys[DebugHotkeysActiveSlot][9].rapid)) DebugMenuExecuteHotkey(9);
			if (DebugKeyPressed("nummul", DebugMenuHotkeys[DebugHotkeysActiveSlot][10].rapid)) DebugMenuExecuteHotkey(10);
			if (DebugKeyPressed("nummin", DebugMenuHotkeys[DebugHotkeysActiveSlot][11].rapid)) DebugMenuExecuteHotkey(11);
			if (DebugKeyPressed("numplu", DebugMenuHotkeys[DebugHotkeysActiveSlot][12].rapid)) DebugMenuExecuteHotkey(12);
			if (DebugKeyPressed("f1", DebugMenuHotkeys[DebugHotkeysActiveSlot][13].rapid)) DebugMenuExecuteHotkey(13);
			if (DebugKeyPressed("f2", DebugMenuHotkeys[DebugHotkeysActiveSlot][14].rapid)) DebugMenuExecuteHotkey(14);
			if (DebugKeyPressed("f3", DebugMenuHotkeys[DebugHotkeysActiveSlot][15].rapid)) DebugMenuExecuteHotkey(15);
			if (DebugKeyPressed("f4", DebugMenuHotkeys[DebugHotkeysActiveSlot][16].rapid)) DebugMenuExecuteHotkey(16);
			if (DebugKeyPressed("f5", DebugMenuHotkeys[DebugHotkeysActiveSlot][17].rapid)) DebugMenuExecuteHotkey(17);
			if (DebugKeyPressed("f6", DebugMenuHotkeys[DebugHotkeysActiveSlot][18].rapid)) DebugMenuExecuteHotkey(18);
			if (DebugKeyPressed("f7", DebugMenuHotkeys[DebugHotkeysActiveSlot][19].rapid)) DebugMenuExecuteHotkey(19);
			if (DebugKeyPressed("f8", DebugMenuHotkeys[DebugHotkeysActiveSlot][20].rapid)) DebugMenuExecuteHotkey(20);
			if (DebugKeyPressed("f9", DebugMenuHotkeys[DebugHotkeysActiveSlot][21].rapid)) DebugMenuExecuteHotkey(21);
			if (DebugKeyPressed("f10", DebugMenuHotkeys[DebugHotkeysActiveSlot][22].rapid)) DebugMenuExecuteHotkey(22);
			if (DebugKeyPressed("f11", DebugMenuHotkeys[DebugHotkeysActiveSlot][23].rapid)) DebugMenuExecuteHotkey(23);
			if (DebugKeyPressed("f12", DebugMenuHotkeys[DebugHotkeysActiveSlot][24].rapid)) DebugMenuExecuteHotkey(24);
		}

		if (DebugMenuCanDraw || (TASRecordScript && TASRecordFrameByFrame))
		{
			ClearSurface(DEBUGMENUFORM::FORM_NONE, 0);

			if (DebugMenuShowValuesMode)
			{
				if (DebugMenuDebugAddressShowValues.size() > 0)
				{
					DebugDrawDebugAddresses();
				}
			}

			if (DebugMenuHotkeyOverlayMode) DebugDrawHotkeyOverlay();

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

			DebugMenuCanDraw = false;
		}

		// Debugmod frame logic
		pOnFrameDebugMod();

		// Draw cursor position
		if (DebugMenuShowCursorMode)
		{
			std::string CursorPositionText = "X: " + std::to_string(DebugMenuCursorPosition.x) + "| Y: " + std::to_string(DebugMenuCursorPosition.y);
			SIZE CursorPositionTextSize;
			GetTextExtentPoint32A(hdc, CursorPositionText.c_str(), (int)CursorPositionText.length(), &CursorPositionTextSize);
			CursorPositionTextSize.cx += 21;
			CursorPositionTextSize.cy += 6;
			_DebugDrawRectangle(DebugMenuCursorPosition.x + 10, DebugMenuCursorPosition.y, CursorPositionTextSize.cx, CursorPositionTextSize.cy, ColorBlack, 0.8f);
			_DebugDrawText(CursorPositionText, DebugMenuCursorPosition.x + 13, DebugMenuCursorPosition.y + 3, FontSmallMedium, ColorYellow, 1.0f, "left");
		}

	}

	_DrawMenu();

	// Frameskips for performance
	DebugMenuGeneralFrameskip++;
	if (DebugMenuSettingsPerformanceMode)
	{
		if (DebugMenuGeneralFrameskip >= DebugMenuGeneralFrameskipFactor + DebugMenuSettingsPerformanceModeFrameskipFactor)
		{
			DebugMenuGeneralFrameskip = 0;
			DebugMenuCanDraw = true;
		}
	}
	else
	{
		if (DebugMenuGeneralFrameskip >= DebugMenuGeneralFrameskipFactor)
		{
			DebugMenuGeneralFrameskip = 0;
			DebugMenuCanDraw = true;
		}
	}


	DebugMenuNotImportantSettingsFrameSkip++;
	if (DebugMenuNotImportantSettingsFrameSkip >= 5) DebugMenuNotImportantSettingsFrameSkip = 0;
}





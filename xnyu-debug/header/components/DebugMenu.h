#pragma once



// --- Structs ---
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



// --- Typedefs ---
typedef void(__stdcall* DebugDrawT)();



// --- Variables ---
extern std::string DebugMenuVersion;
extern DebugDrawT DebugDraw;
extern DebugRawInput DebugRawInputData;
extern float DebugWidthFactor;
extern float DebugHeightFactor;
extern bool DebugMenuOpened;
extern bool DebugMenuInit;
extern bool RawInputCanAttach;
extern bool RawInputIsAttached;
extern bool DebugMenuShowValuesMode;
extern bool DebugMenuSuperVisionMode;
extern bool DebugMenuSettingsPerformanceMode;
extern bool DebugMenuShowCursorMode;
extern bool DebugMenuHotkeyOverlayMode;
extern bool DebugMenuEditorMode;
extern bool DebugMenuEditorModeInit;
extern int DebugMenuShowValuesModeUpdateIntervall;
extern std::vector<std::string> DebugMenuShowValuesModeData;
extern bool DebugMenuInitSwitch;
extern bool DebugMenuCanDraw;
extern int DebugMenuGeneralFrameskip;
extern int DebugMenuGeneralFrameskipFactor;
extern int DebugMenuSettingsPerformanceModeFrameskipFactor;
extern int DebugMenuNotImportantSettingsFrameSkip;
extern int DebugHotkeysActiveSlot;
extern int TextIndexPointerBlinkCounter;
extern bool TextIndexPointerBlink;
extern int TextIndexPointer;
extern POINT DebugMenuCursorPosition;
extern POINT DebugMenuCursorPositionLast;
extern POINT DebugMenuCursorPositionLastDelta;
extern POINT RealCursorPosition;
extern std::vector<std::string> DebugMenuSlotName;
extern std::vector<std::vector<DebugFunction>> DebugMenuHotkeys;
extern std::vector<std::vector<std::string>> DebugMenuParameter;
extern int DebugMenuParameterFocus;
extern int DebugMenuFunctionFocus;
extern std::vector<RECT> DebugMenuEmptyHoverBoxes;
extern std::vector<RECT> DebugMenuOverviewHoverBoxes;
extern std::vector<RECT> DebugMenuDebugAddressesParentsHoverBoxes;
extern std::vector<std::vector<RECT>> DebugMenuDebugAddressesChildsHoverBoxes;
extern std::vector<RECT> DebugMenuDebugFunctionsParentsHoverBoxes;
extern std::vector<std::vector<RECT>> DebugMenuDebugFunctionsChildsHoverBoxes;
extern std::vector<RECT> DebugMenuSavefileEditorFilesHoverBoxes;
extern std::vector<RECT> DebugMenuSavefileEditorParentsHoverBoxes;
extern std::vector<std::vector<RECT>> DebugMenuSavefileEditorChildsHoverBoxes;
extern int DebugMenuDebugAddressesParentFocus;
extern int DebugMenuDebugFunctionsParentFocus;
extern std::vector<DebugAddress> DebugMenuDebugAddressShowValues;
extern bool DebugMenuDebugAddressShowValuesInit;
extern int DebugMenuDebugAddressShowValuesBackWidth;
extern int DebugMenuDebugAddressShowValuesBackHeight;
extern int DebugMenuDebugAddressShowValuesMaxCol;
extern int DebugMenuDebugAddressShowValuesMaxRow;
extern int* DebugMenuDebugAddressShowValuesRowWidth;
extern int DebugMenuDebugAddressShowValuesRowHeight;
extern DEBUGMENUFORM DebugMenuMainForm;
extern int DebugMenuSubForm;
extern DEBUGMENUFORM DebugMenuMainFormLast;
extern int DebugMenuSubFormLast;
extern bool DebugMenuHoverDescriptionShow;
extern std::vector<std::string> DebugMenuHoverDescription;
extern GameInput DebugInputCurrent;
extern GameInput DebugInputLast;
extern Point DebugMenuEditorModeDraggingLMBPosition;
extern Point DebugMenuEditorModeDraggingRMBPosition;
extern Point DebugMenuEditorModeDraggingMBPosition;
extern Point DebugMenuEditorModeDraggingLMBPositionLast;
extern Point DebugMenuEditorModeDraggingRMBPositionLast;
extern Point DebugMenuEditorModeDraggingMBPositionLast;
extern Point DebugMenuEditorModeDraggingLMBPositionLastDelta;
extern Point DebugMenuEditorModeDraggingRMBPositionLastDelta;
extern Point DebugMenuEditorModeDraggingMBPositionLastDelta;
extern bool DebugMenuEditorModeDraggingLMBTrigger;
extern bool DebugMenuEditorModeDraggingRMBTrigger;
extern bool DebugMenuEditorModeDraggingMBTrigger;
extern bool DebugMenuEditorModeDraggingLMB;
extern bool DebugMenuEditorModeDraggingRMB;
extern bool DebugMenuEditorModeDraggingMB;
extern Point DebugMenuEditorModeContextMenuPosition;
extern bool DebugMenuEditorModeContextMenuShowTrigger;
extern bool DebugMenuEditorModeContextMenuShowOpen;
extern int DebugMenuEditorModeContextMenuEntryIdLayer1;
extern int DebugMenuEditorModeContextMenuEntryIdLayer2;
extern int DebugMenuEditorModeCurrentMode;
extern HCURSOR HiddenCursor;
extern HCURSOR OriginalCursor;
extern int DebugMenuEditorModeContextMenuMaxWidth;
extern int DebugMenuEditorModeContextMenuMaxHeight;
extern int DebugMenuEditorModeContextMenuLayer1Width;
extern std::vector<int> DebugMenuEditorModeContextMenuLayer2Width;
extern std::vector<RECT> HoverBoxesTarget;
extern int DebugMenuShowValuesModeRowWidths[10];
extern int DebugMenuShowValuesModeMaxRows;
extern int DebugMenuShowValuesModeFinalRowWidth;
extern int DebugMenuShowValuesModeFinalRowHeight;
extern RECT OriginalCursorClip;
extern RECT CustomCursorClip;
extern POINT OriginalCursorPos;
extern POINT CustomCursorPos;
extern int DebugMenuHotkeyDelegationIndex;



// --- Functions ---
void DebugMenuInitForms();
void DebugMenuMockData();
void DebugMenuInitHoverBoxes();
void DebugMenuInitHotkeys();
void DebugMenuInitSaveEditor();
void DebugMenuInitSettings();
void DebugMenuInitHiddenCursor();
void DebugMenuInitEditorMode();
void DebugMenuInitValues();
BOOLEAN CheckWindowActive();
void __cdecl _DebugDrawText(std::string text, int x, int y, HFONT font, unsigned char* color, float alpha, std::string align = "left");
void __cdecl _DebugDrawRectangle(int x, int y, int w, int h, unsigned char* color, float alpha);
void _DrawCursorToTexture(int x, int y);
void _DrawMenu();
BOOL DebugKeyPressed(std::string id, bool rapid = false);
void DebugMenuHandleHover(int id);
void DebugMenuHandleClick(int id, bool left);
void _DetectHoverBoxesTarget();
void _DrawHoverBoxes();
void _CheckHoverBoxes();
void DebugMenuShowValuesModeCalculateSize();
void DebugMenuExecuteHotkey(int id);
std::string DebugMenuHotkeyDisplayName(int id);
std::string DebugMenuHotkeyDisplayParameter(int id);
bool DebugMenuCheckShiftKeyAsync();
bool DebugMenuCheckCtrlKeyAsync();
int DebugMenuCheckTextInput(std::string* text, int indexPointer);
void __cdecl DebugMenuOpen();
void DebugMenuClose();
void DebugDrawDebugAddresses();
void DebugDrawHotkeyOverlay();
void DebugMenuMainRoutine();



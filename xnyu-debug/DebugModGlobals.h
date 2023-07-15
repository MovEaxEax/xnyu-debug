#pragma once

typedef void(__cdecl* OnInitDebugModT)(DebugSettings _globalSettings, DebugFeatures* _features, DebugReferences _references, ThreadReferences _threadReferences);
OnInitDebugModT pOnInitDebugMod = nullptr;

typedef void(__cdecl* OnDebugMenuT)(bool isEnabled);
OnDebugMenuT pOnDebugMenu = nullptr;

typedef void(__cdecl* OnFrameDebugModT)();
OnFrameDebugModT pOnFrameDebugMod = nullptr;

typedef void(__cdecl* OnExitDebugModT)();
OnExitDebugModT pOnExitDebugMod = nullptr;

typedef void(__cdecl* SetDebugAddressValueT)(DebugAddress* targetAddress);
SetDebugAddressValueT pSetDebugAddressValue = nullptr;

typedef void(__cdecl* GetDebugAddressValueT)(DebugAddress* targetAddress);
GetDebugAddressValueT pGetDebugAddressValue = nullptr;

typedef void(__cdecl* ExecuteDebugFunctionT)(DebugFunction* targetFunction);
ExecuteDebugFunctionT pExecuteDebugFunction = nullptr;

typedef void(__cdecl* GetSavefilesT)(char* saveFilesBuffer);
GetSavefilesT pGetSavefiles = nullptr;

typedef void(__cdecl* ScopeSavefileT)(std::string filename);
ScopeSavefileT pScopeSavefile = nullptr;

typedef void(__cdecl* LoadSavefileT)(SavefileParent* savefileParent);
LoadSavefileT pLoadSavefile = nullptr;

typedef void(__cdecl* UpdateSavefileT)(SavefileParent* savefileParent);
UpdateSavefileT pUpdateSavefile = nullptr;

typedef void(__cdecl* InitSupervisionSettingsT)(const std::vector<FeatureSettingParent>& settingParent);
InitSupervisionSettingsT pInitSupervisionSettings = nullptr;

typedef void(__cdecl* GetSupervisionSettingsT)(FeatureSettingParent* settingParent);
GetSupervisionSettingsT pGetSupervisionSettings = nullptr;

typedef void(__cdecl* UpdateSupervisionSettingsT)(FeatureSettingParent* settingParent);
UpdateSupervisionSettingsT pUpdateSupervisionSettings = nullptr;

typedef void(__cdecl* ToggleSupervisionRoutineT)(bool isEnabled);
ToggleSupervisionRoutineT pToggleSupervisionRoutine = nullptr;

typedef void(__cdecl* InitEditorModeSettingsT)(const std::vector<FeatureSettingParent>& settingParent);
InitEditorModeSettingsT pInitEditorModeSettings = nullptr;

typedef void(__cdecl* GetEditorModeSettingsT)(FeatureSettingParent* settingParent);
GetEditorModeSettingsT pGetEditorModeSettings = nullptr;

typedef void(__cdecl* UpdateEditorModeSettingsT)(FeatureSettingParent* settingParent);
UpdateEditorModeSettingsT pUpdateEditorModeSettings = nullptr;

typedef void(__cdecl* ToggleEditorModeRoutineT)(bool isEnabled);
ToggleEditorModeRoutineT pToggleEditorModeRoutine = nullptr;

// Editor control functions
typedef void(__cdecl* EditorModeMovementMoveForwardT)();
EditorModeMovementMoveForwardT pEditorModeMovementMoveForward = nullptr;

typedef void(__cdecl* EditorModeMovementMoveBackwardT)();
EditorModeMovementMoveBackwardT pEditorModeMovementMoveBackward = nullptr;

typedef void(__cdecl* EditorModeMovementStrifeLeftT)();
EditorModeMovementStrifeLeftT pEditorModeMovementStrifeLeft = nullptr;

typedef void(__cdecl* EditorModeMovementStrifeRightT)();
EditorModeMovementStrifeRightT pEditorModeMovementStrifeRight = nullptr;

typedef void(__cdecl* EditorModeMovementMoveUpwardsT)();
EditorModeMovementMoveUpwardsT pEditorModeMovementMoveUpwards = nullptr;

typedef void(__cdecl* EditorModeMovementMoveDownwardsT)();
EditorModeMovementMoveDownwardsT pEditorModeMovementMoveDownwards = nullptr;

typedef void(__cdecl* EditorModeMovementMouseXAxisT)(float);
EditorModeMovementMouseXAxisT pEditorModeMovementMouseXAxis = nullptr;

typedef void(__cdecl* EditorModeMovementMouseYAxisT)(float);
EditorModeMovementMouseYAxisT pEditorModeMovementMouseYAxis = nullptr;

typedef void(__cdecl* EditorModeMovementMouseWheelAxisT)(float);
EditorModeMovementMouseWheelAxisT pEditorModeMovementMouseWheelAxis = nullptr;

typedef void(__cdecl* EditorModeActionLeftClickT)(Point);
EditorModeActionLeftClickT pEditorModeActionLeftClick = nullptr;

typedef void(__cdecl* EditorModeActionLeftClickDraggingT)(Point, Point, Point);
EditorModeActionLeftClickDraggingT pEditorModeActionLeftClickDragging = nullptr;

typedef void(__cdecl* EditorModeActionRightClickT)(Point);
EditorModeActionRightClickT pEditorModeActionRightClick = nullptr;

typedef void(__cdecl* EditorModeActionRightClickDraggingT)(Point, Point, Point);
EditorModeActionRightClickDraggingT pEditorModeActionRightClickDragging = nullptr;

typedef void(__cdecl* EditorModeActionMiddleClickT)(Point);
EditorModeActionMiddleClickT pEditorModeActionMiddleClick = nullptr;

typedef void(__cdecl* EditorModeActionMiddleClickDraggingT)(Point, Point, Point);
EditorModeActionMiddleClickDraggingT pEditorModeActionMiddleClickDragging = nullptr;

typedef void(__cdecl* EditorModeActionEnterRotationModeT)();
EditorModeActionEnterRotationModeT pEditorModeActionEnterRotationMode = nullptr;

typedef void(__cdecl* EditorModeActionEnterScalingModeT)();
EditorModeActionEnterScalingModeT pEditorModeActionEnterScalingMode = nullptr;

typedef void(__cdecl* EditorModeActionEnterMovingModeT)();
EditorModeActionEnterMovingModeT pEditorModeActionEnterMovingMode = nullptr;

typedef void(__cdecl* EditorModeActionHoldingShiftT)();
EditorModeActionHoldingShiftT pEditorModeActionHoldingShift = nullptr;

typedef void(__cdecl* EditorModeActionContextActionT)(EditorModeAction*);
EditorModeActionContextActionT pEditorModeActionContextAction = nullptr;

typedef void(__cdecl* EditorModeActionUndoT)();
EditorModeActionUndoT pEditorModeActionUndo = nullptr;

typedef void(__cdecl* EditorModeActionRedoT)();
EditorModeActionRedoT pEditorModeActionRedo = nullptr;





HMODULE DebugModModuleHandle = nullptr;

DebugFeatures GlobalDebugFeatures = DebugFeatures();

typedef void(__stdcall* TASRoutineT)();
TASRoutineT pTASRoutine = nullptr;

typedef void(__cdecl* TASCommandT)(char* script);
TASCommandT pTASPlayScript = nullptr;
TASCommandT pTASRecordScript = nullptr;

bool DebugModIsLoaded = false;

void InitDebugMod()
{
	try
	{
		LoadDebugAddresses();
		LoadDebugFunctions();
		LoadEditorModeSettings();
		LoadSupervisionSettings();
		LoadSavefileLayouts();

		std::string modFilePath = "";
		for (const auto& _file : std::filesystem::directory_iterator(GlobalSettings.config_debugmod_directory)) if (_file.path().string().find(".dll") != std::string::npos) modFilePath = _file.path().string();
		if (modFilePath != "")
		{
			DebugModModuleHandle = LoadLibraryA(modFilePath.c_str());

			pOnInitDebugMod = (OnInitDebugModT)GetProcAddress(DebugModModuleHandle, "OnInitDebugMod");
			pOnDebugMenu = (OnDebugMenuT)GetProcAddress(DebugModModuleHandle, "OnDebugMenu");
			pOnFrameDebugMod = (OnFrameDebugModT)GetProcAddress(DebugModModuleHandle, "OnFrameDebugMod");
			pOnExitDebugMod = (OnExitDebugModT)GetProcAddress(DebugModModuleHandle, "OnExitDebugMod");
			pSetDebugAddressValue = (SetDebugAddressValueT)GetProcAddress(DebugModModuleHandle, "SetDebugAddressValue");
			pGetDebugAddressValue = (GetDebugAddressValueT)GetProcAddress(DebugModModuleHandle, "GetDebugAddressValue");
			pExecuteDebugFunction = (ExecuteDebugFunctionT)GetProcAddress(DebugModModuleHandle, "ExecuteDebugFunction");

			pInitSupervisionSettings = (InitSupervisionSettingsT)GetProcAddress(DebugModModuleHandle, "InitSupervisionSettings");
			pGetSupervisionSettings = (GetSupervisionSettingsT)GetProcAddress(DebugModModuleHandle, "GetSupervisionSettings");
			pUpdateSupervisionSettings = (UpdateSupervisionSettingsT)GetProcAddress(DebugModModuleHandle, "UpdateSupervisionSettings");
			pToggleSupervisionRoutine = (ToggleSupervisionRoutineT)GetProcAddress(DebugModModuleHandle, "ToggleSupervisionRoutine");

			pInitEditorModeSettings = (InitEditorModeSettingsT)GetProcAddress(DebugModModuleHandle, "InitEditorModeSettings");
			pGetEditorModeSettings = (GetEditorModeSettingsT)GetProcAddress(DebugModModuleHandle, "GetEditorModeSettings");
			pUpdateEditorModeSettings = (UpdateEditorModeSettingsT)GetProcAddress(DebugModModuleHandle, "UpdateEditorModeSettings");
			pToggleEditorModeRoutine = (ToggleEditorModeRoutineT)GetProcAddress(DebugModModuleHandle, "ToggleEditorModeRoutine");

			pEditorModeMovementMoveForward = (EditorModeMovementMoveForwardT)GetProcAddress(DebugModModuleHandle, "EditorModeMovementMoveForward");
			pEditorModeMovementMoveBackward = (EditorModeMovementMoveBackwardT)GetProcAddress(DebugModModuleHandle, "EditorModeMovementMoveBackward");
			pEditorModeMovementStrifeLeft = (EditorModeMovementStrifeLeftT)GetProcAddress(DebugModModuleHandle, "EditorModeMovementStrifeLeft");
			pEditorModeMovementStrifeRight = (EditorModeMovementStrifeRightT)GetProcAddress(DebugModModuleHandle, "EditorModeMovementStrifeRight");
			pEditorModeMovementMoveUpwards = (EditorModeMovementMoveUpwardsT)GetProcAddress(DebugModModuleHandle, "EditorModeMovementMoveUpwards");
			pEditorModeMovementMoveDownwards = (EditorModeMovementMoveDownwardsT)GetProcAddress(DebugModModuleHandle, "EditorModeMovementMoveDownwards");
			pEditorModeMovementMouseXAxis = (EditorModeMovementMouseXAxisT)GetProcAddress(DebugModModuleHandle, "EditorModeMovementMouseXAxis");
			pEditorModeMovementMouseYAxis = (EditorModeMovementMouseYAxisT)GetProcAddress(DebugModModuleHandle, "EditorModeMovementMouseYAxis");
			pEditorModeMovementMouseWheelAxis = (EditorModeMovementMouseWheelAxisT)GetProcAddress(DebugModModuleHandle, "EditorModeMovementMouseWheelAxis");
			pEditorModeActionLeftClick = (EditorModeActionLeftClickT)GetProcAddress(DebugModModuleHandle, "EditorModeActionLeftClick");
			pEditorModeActionLeftClickDragging = (EditorModeActionLeftClickDraggingT)GetProcAddress(DebugModModuleHandle, "EditorModeActionLeftClickDragging");
			pEditorModeActionRightClick = (EditorModeActionRightClickT)GetProcAddress(DebugModModuleHandle, "EditorModeActionRightClick");
			pEditorModeActionRightClickDragging = (EditorModeActionLeftClickDraggingT)GetProcAddress(DebugModModuleHandle, "EditorModeActionRightClickDragging");
			pEditorModeActionMiddleClick = (EditorModeActionMiddleClickT)GetProcAddress(DebugModModuleHandle, "EditorModeActionMiddleClick");
			pEditorModeActionMiddleClickDragging = (EditorModeActionMiddleClickDraggingT)GetProcAddress(DebugModModuleHandle, "EditorModeActionMiddleClickDragging");
			pEditorModeActionEnterRotationMode = (EditorModeActionEnterRotationModeT)GetProcAddress(DebugModModuleHandle, "EditorModeActionEnterRotationMode");
			pEditorModeActionEnterScalingMode = (EditorModeActionEnterScalingModeT)GetProcAddress(DebugModModuleHandle, "EditorModeActionEnterScalingMode");
			pEditorModeActionEnterMovingMode = (EditorModeActionEnterMovingModeT)GetProcAddress(DebugModModuleHandle, "EditorModeActionEnterMovingMode");
			pEditorModeActionHoldingShift = (EditorModeActionHoldingShiftT)GetProcAddress(DebugModModuleHandle, "EditorModeActionHoldingShift");
			pEditorModeActionContextAction = (EditorModeActionContextActionT)GetProcAddress(DebugModModuleHandle, "EditorModeActionContextAction");
			pEditorModeActionUndo = (EditorModeActionUndoT)GetProcAddress(DebugModModuleHandle, "EditorModeActionUndo");
			pEditorModeActionRedo = (EditorModeActionRedoT)GetProcAddress(DebugModModuleHandle, "EditorModeActionRedo");

			pGetSavefiles = (GetSavefilesT)GetProcAddress(DebugModModuleHandle, "GetSavefiles");
			pLoadSavefile = (LoadSavefileT)GetProcAddress(DebugModModuleHandle, "LoadSavefile");
			pUpdateSavefile = (UpdateSavefileT)GetProcAddress(DebugModModuleHandle, "SaveSavefile");
			pScopeSavefile = (ScopeSavefileT)GetProcAddress(DebugModModuleHandle, "ScopeSavefile");

			pOnInitDebugMod(GlobalSettings, &GlobalDebugFeatures, GlobalReferences, ThreadHookerReferences);
			pInitSupervisionSettings(DebugSupervisionSettings);
			pInitEditorModeSettings(DebugSupervisionSettings);

			DebugModIsLoaded = true;
		}
	}
	catch (std::exception e)
	{
		DebugConsoleOutput("Error occured in: InitDebugMod()", false, "red");
		DebugConsoleOutput(e.what(), false, "red");
	}
}

bool UninitDebugMod()
{
	try
	{
		pOnExitDebugMod();

		FreeLibrary(DebugModModuleHandle);

		return true;
	}
	catch (std::exception e)
	{
		DebugConsoleOutput("Error occured in: UninitDebugMod()", false, "red");
		DebugConsoleOutput(e.what(), false, "red");
		return false;
	}
}

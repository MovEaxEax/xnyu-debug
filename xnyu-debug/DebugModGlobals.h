#pragma once

typedef void(__stdcall* OnInitDebugModT)(DebugSettings _globalSettings, DebugFeatures* features, void* _logger, void* _drawRectangle, void* _drawText);
OnInitDebugModT pOnInitDebugMod = nullptr;

typedef void(__stdcall* OnFrameDebugModT)();
OnFrameDebugModT pOnFrameDebugMod = nullptr;

typedef void(__stdcall* OnExitDebugModT)();
OnExitDebugModT pOnExitDebugMod = nullptr;

typedef void(__stdcall* SetDebugAddressValueT)(DebugAddress* targetAddress);
SetDebugAddressValueT pSetDebugAddressValue = nullptr;

typedef void(__stdcall* GetDebugAddressValueT)(DebugAddress* targetAddress);
GetDebugAddressValueT pGetDebugAddressValue = nullptr;

typedef void(__stdcall* ExecuteDebugFunctionT)(DebugFunction* targetFunction);
ExecuteDebugFunctionT pExecuteDebugFunction = nullptr;

typedef void(__stdcall* GetSavefilesT)(char* savefiles);
GetSavefilesT pGetSavefiles = nullptr;

typedef void(__stdcall* ScopeSavefileT)(std::string filename);
ScopeSavefileT pScopeSavefile = nullptr;

typedef void(__stdcall* LoadSavefileT)(SavefileParent* savefileParent);
LoadSavefileT pLoadSavefile = nullptr;

typedef void(__stdcall* SaveSavefileT)(SavefileParent* savefileParent);
SaveSavefileT pSaveSavefile = nullptr;

typedef void(__stdcall* SupervisionRoutineT)();
SupervisionRoutineT pSupervisionRoutine = nullptr;

HMODULE DebugModModuleHandle = nullptr;

DebugFeatures GlobalDebugFeatures = DebugFeatures();

bool InitDebugMod(void* pDebugDrawRectangle, void* pDebugDrawText)
{
	try
	{
		LoadDebugAddresses();
		LoadDebugFunctions();
		LoadSavefileLayouts();

		std::string modFilePath = "";
		for (const auto& _file : std::filesystem::directory_iterator(GlobalSettings.config_debugmod_directory)) if (_file.path().string().find(".dll") != std::string::npos) modFilePath = _file.path().string();
		if (modFilePath == "") return false;

		DebugModModuleHandle = LoadLibraryA(modFilePath.c_str());

		pOnInitDebugMod = (OnInitDebugModT)GetProcAddress(DebugModModuleHandle, "OnInitDebugMod");
		pOnFrameDebugMod = (OnFrameDebugModT)GetProcAddress(DebugModModuleHandle, "OnFrameDebugMod");
		pOnExitDebugMod = (OnExitDebugModT)GetProcAddress(DebugModModuleHandle, "OnExitDebugMod");
		pSetDebugAddressValue = (SetDebugAddressValueT)GetProcAddress(DebugModModuleHandle, "SetDebugAddressValue");
		pGetDebugAddressValue = (GetDebugAddressValueT)GetProcAddress(DebugModModuleHandle, "GetDebugAddressValue");
		pExecuteDebugFunction = (ExecuteDebugFunctionT)GetProcAddress(DebugModModuleHandle, "ExecuteDebugFunction");

		pGetSavefiles = (GetSavefilesT)GetProcAddress(DebugModModuleHandle, "GetSavefiles");
		pLoadSavefile = (LoadSavefileT)GetProcAddress(DebugModModuleHandle, "LoadSavefile");
		pSaveSavefile = (SaveSavefileT)GetProcAddress(DebugModModuleHandle, "SaveSavefile");
		pScopeSavefile = (ScopeSavefileT)GetProcAddress(DebugModModuleHandle, "ScopeSavefile");

		pSupervisionRoutine = (SupervisionRoutineT)GetProcAddress(DebugModModuleHandle, "SupervisionRoutine");

		pOnInitDebugMod(GlobalSettings, &GlobalDebugFeatures, DebugConsoleOutput, pDebugDrawRectangle, pDebugDrawText);
		
		return true;
	}
	catch (std::exception e)
	{
		DebugConsoleOutput("Error occured in: InitDebugMod()", false, "red");
		DebugConsoleOutput(e.what(), false, "red");
		return false;
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

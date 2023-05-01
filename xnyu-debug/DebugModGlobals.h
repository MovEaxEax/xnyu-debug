#pragma once

typedef void(__cdecl* OnInitDebugModT)(DebugSettings _globalSettings, DebugFeatures* features, void* _logger, void* _drawRectangle, void* _drawText, void* _TASRoutine);
OnInitDebugModT pOnInitDebugMod = nullptr;

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

typedef void(__cdecl* SaveSavefileT)(SavefileParent* savefileParent);
SaveSavefileT pSaveSavefile = nullptr;

typedef void(__cdecl* SupervisionRoutineT)();
SupervisionRoutineT pSupervisionRoutine = nullptr;

HMODULE DebugModModuleHandle = nullptr;

DebugFeatures GlobalDebugFeatures = DebugFeatures();

typedef void(__stdcall* TASRoutineT)();
TASRoutineT pTASRoutine = nullptr;

typedef void(__cdecl* TASCommandT)(char* script);
TASCommandT pTASPlayScript = nullptr;
TASCommandT pTASRecordScript = nullptr;

void InitDebugMod(void* pDebugDrawRectangle, void* pDebugDrawText)
{
	try
	{
		LoadDebugAddresses();
		LoadDebugFunctions();
		LoadSavefileLayouts();

		std::string modFilePath = "";
		for (const auto& _file : std::filesystem::directory_iterator(GlobalSettings.config_debugmod_directory)) if (_file.path().string().find(".dll") != std::string::npos) modFilePath = _file.path().string();
		if (modFilePath != "")
		{

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

			pOnInitDebugMod(GlobalSettings, &GlobalDebugFeatures, DebugConsoleOutput, pDebugDrawRectangle, pDebugDrawText, pTASRoutine);
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

#include "pch.h"
#include "DebugSettings.h"
#include "GlobalSettings.h"
#include "Winactive.h"
#include "Technical.h"



// --- Variables ---
HMODULE MainDllHandle = nullptr;
HWND MainWindowHandle = nullptr;
RECT MainWindowRect = RECT();
RECT MainWindowClientRect = RECT();
bool MainWindowIsActive = false;
unsigned long MainWindowPID = -1;
int MainWindowThreadId = -1;
int GlobalSettingsUpdateFrameSkip = -1;
std::map<std::string, std::string> GlobalSettings;
std::map<std::string, std::string> DebugFeaturesSettings;
HANDLE GlobalSettingsMutex = CreateMutex(NULL, FALSE, NULL);



// --- Functions ---
EXTERN_DLL_EXPORT HWND __cdecl GetMainWindowHandle()
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);
	HWND result = MainWindowHandle;
	ReleaseMutex(GlobalSettingsMutex);
	return result;
}

EXTERN_DLL_EXPORT HMODULE __cdecl GetMainDllHandle()
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);
	HMODULE result = MainDllHandle;
	ReleaseMutex(GlobalSettingsMutex);
	return result;
}

EXTERN_DLL_EXPORT unsigned long __cdecl GetMainWindowPid()
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);
	unsigned long result = MainWindowPID;
	ReleaseMutex(GlobalSettingsMutex);
	return result;
}

EXTERN_DLL_EXPORT int __cdecl GetMainWindowThreadId()
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);
	int result = MainWindowThreadId;
	ReleaseMutex(GlobalSettingsMutex);
	return result;
}

EXTERN_DLL_EXPORT RECT __cdecl GetMainWindowRect()
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);
	RECT result = MainWindowRect;
	ReleaseMutex(GlobalSettingsMutex);
	return result;
}

EXTERN_DLL_EXPORT RECT __cdecl GetMainWindowClientRect()
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);
	RECT result = MainWindowClientRect;
	ReleaseMutex(GlobalSettingsMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl IsMainWindowActive()
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);
	bool result = MainWindowIsActive;
	ReleaseMutex(GlobalSettingsMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl IsDevMode()
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);
	bool result = DevMode;
	ReleaseMutex(GlobalSettingsMutex);
	return result;
}

EXTERN_DLL_EXPORT std::string __cdecl GetGlobalSetting(std::string key)
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);
	try
	{
		if (key.empty())
		{
			ReleaseMutex(GlobalSettingsMutex);
			return "none";
		}
		std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return std::tolower(c); });
		if (GlobalSettings.find(key) == GlobalSettings.end())
		{
			ReleaseMutex(GlobalSettingsMutex);
			return "none";
		}
		ReleaseMutex(GlobalSettingsMutex);
		return GlobalSettings[key];
	}
	catch (...)
	{
		ReleaseMutex(GlobalSettingsMutex);
		return "error";
	}
}

EXTERN_DLL_EXPORT bool __cdecl SetGlobalSetting(std::string key, std::string value)
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);
	try
	{
		if (key.empty() || value.empty())
		{
			ReleaseMutex(GlobalSettingsMutex);
			return false;
		}
		std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return std::tolower(c); });
		std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return std::tolower(c); });
		GlobalSettings[key] = value;
		ReleaseMutex(GlobalSettingsMutex);
		return true;
	}
	catch (...)
	{
		ReleaseMutex(GlobalSettingsMutex);
		return false;
	}
}

EXTERN_DLL_EXPORT std::string __cdecl GetDebugFeaturesSetting(std::string key)
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);
	try
	{
		if (key.empty())
		{
			ReleaseMutex(GlobalSettingsMutex);
			return "";
		}
		std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return std::tolower(c); });
		if (DebugFeaturesSettings.find(key) == DebugFeaturesSettings.end())
		{
			ReleaseMutex(GlobalSettingsMutex);
			return "none";
		}
		ReleaseMutex(GlobalSettingsMutex);
		return DebugFeaturesSettings[key];
	}
	catch (...)
	{
		ReleaseMutex(GlobalSettingsMutex);
		return "error";
	}
}

EXTERN_DLL_EXPORT bool __cdecl SetDebugFeaturesSetting(std::string key, std::string value)
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);
	try
	{
		if (key.empty() || value.empty())
		{
			ReleaseMutex(GlobalSettingsMutex);
			return false;
		}
		std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return std::tolower(c); });
		std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return std::tolower(c); });
		DebugFeaturesSettings[key] = value;
		ReleaseMutex(GlobalSettingsMutex);
		return true;
	}
	catch (...)
	{
		ReleaseMutex(GlobalSettingsMutex);
		return false;
	}
}

void GlobalSettingsUpdate()
{
	WaitForSingleObject(GlobalSettingsMutex, INFINITE);

	try
	{
		if (GlobalSettingsUpdateFrameSkip >= 10 || GlobalSettingsUpdateFrameSkip < 0)
		{
			MainWindowPID = GetCurrentProcessId();
			MainWindowHandle = FindMainWindowHandle(MainWindowPID);
			MainWindowThreadId = FindMainThreadID(MainWindowPID);
			GetWindowRect(MainWindowHandle, &MainWindowRect);
			GetClientRect(MainWindowHandle, &MainWindowClientRect);
			MainWindowIsActive = GetForegroundWindowReal() == MainWindowHandle;

			GlobalSettingsUpdateFrameSkip = 0;
		}
		else GlobalSettingsUpdateFrameSkip++;
	}
	catch (...)
	{
		GlobalSettingsUpdateFrameSkip = 0;
	}

	ReleaseMutex(GlobalSettingsMutex);
}



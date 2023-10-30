#pragma once

// --- Variables ---
extern HMODULE MainDllHandle;
extern HWND MainWindowHandle;
extern RECT MainWindowRect;
extern RECT MainWindowClientRect = RECT();
extern bool MainWindowIsActive;
extern int MainWindowThreadId;
extern unsigned long MainWindowPID;
extern int GlobalSettingsUpdateFrameSkip;
bool DevMode = false;
extern std::map<std::string, std::string> GlobalSettings;
extern std::map<std::string, std::string> DebugFeaturesSettings;
extern HANDLE GlobalSettingsMutex;

// --- Functions ---
EXTERN_DLL_EXPORT HWND __cdecl GetMainWindowHandle();
EXTERN_DLL_EXPORT HMODULE __cdecl GetMainDllHandle();
EXTERN_DLL_EXPORT unsigned long __cdecl GetMainWindowPid();
EXTERN_DLL_EXPORT int __cdecl GetMainWindowThreadId();
EXTERN_DLL_EXPORT RECT __cdecl GetMainWindowRect();
EXTERN_DLL_EXPORT RECT __cdecl GetMainWindowClientRect();
EXTERN_DLL_EXPORT bool __cdecl IsMainWindowActive();
EXTERN_DLL_EXPORT bool __cdecl IsDevMode();
EXTERN_DLL_EXPORT std::string __cdecl GetGlobalSetting(std::string key);
EXTERN_DLL_EXPORT bool __cdecl SetGlobalSetting(std::string key, std::string value);
EXTERN_DLL_EXPORT std::string __cdecl GetDebugFeaturesSetting(std::string key);
EXTERN_DLL_EXPORT bool __cdecl SetDebugFeaturesSetting(std::string key, std::string value);
void UpdateGlobalSettings();



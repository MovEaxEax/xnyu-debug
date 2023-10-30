#pragma once

// --- Structs ---
struct DebugEditorModeAction
{
    std::string nameFull;
    std::string nameChild;
    std::string nameParent;
};

struct DebugEditorModeActionParent
{
    std::string nameParent;
    std::vector<DebugEditorModeAction> actions;
};

struct DebugEditorFeatureSetting
{
    std::string nameFull;
    std::string nameChild;
    std::string nameParent;
    std::string type;
    std::vector<std::string> description;
    std::vector<Variable> comboboxValues;
    Variable checkboxChecked;
    Variable value;
};

struct DebugEditorFeatureSettingParent
{
    std::string nameParent;
    std::vector<DebugEditorFeatureSetting> settings;
    std::vector<std::string> description;
};



// --- Variables ---
extern std::vector<DebugEditorFeatureSettingParent> DebugEditorModeSettings;
extern std::vector<DebugEditorModeActionParent> DebugEditorModeActions;
extern HANDLE DebugEditorModeMutex;



// --- Functions ---
bool LoadEditorModeSettings();



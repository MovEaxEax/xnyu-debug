#pragma once

// --- Structs ---
struct DebugSupervisionFeatureSetting
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

struct DebugSupervisionFeatureSettingParent
{
    std::string nameParent;
    std::vector<DebugSupervisionFeatureSetting> settings;
    std::vector<std::string> description;
};



// --- Variables ---
extern std::vector<DebugSupervisionFeatureSettingParent> DebugSupervisionSettings;
extern HANDLE DebugSupervisionMutex;



// --- Functions ---
bool LoadSupervisionSettings();



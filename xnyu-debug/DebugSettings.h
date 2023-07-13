#pragma once

struct FeatureSetting
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

struct FeatureSettingParent
{
    std::string nameParent;
    std::vector<FeatureSetting> settings;
    std::vector<std::string> description;
};



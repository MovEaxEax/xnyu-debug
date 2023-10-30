#include "pch.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "Variable.h"
#include "Conversions.h"
#include "DebugSupervisionSettings.h"



// --- Variables ---
std::vector<DebugSupervisionFeatureSettingParent> DebugSupervisionSettings;
HANDLE DebugSupervisionMutex = CreateMutex(NULL, FALSE, NULL);;



// --- Functions ---
bool LoadSupervisionSettings()
{
    WaitForSingleObject(DebugSupervisionMutex, INFINITE);
    try
    {
        std::string debugSupervisionDirectorySetting = GetGlobalSetting("config_supervision_directory");

        for (const auto& _file : std::filesystem::directory_iterator(debugSupervisionDirectorySetting))
        {
            std::ifstream address_file = std::ifstream(_file.path());
            std::string fileText((std::istreambuf_iterator<char>(address_file)), std::istreambuf_iterator<char>());
            address_file.close();

            // Delete comments
            size_t commentStart;
            while ((commentStart = fileText.find("//")) != std::string::npos) {
                size_t lineEnd = fileText.find("\n", commentStart);
                fileText.erase(commentStart, lineEnd != std::string::npos ? lineEnd - commentStart + 1 : std::string::npos);
            }

            // Delete tabs, line breaks, and carriage returns
            fileText.erase(std::remove(fileText.begin(), fileText.end(), '\t'), fileText.end());
            fileText.erase(std::remove(fileText.begin(), fileText.end(), '\n'), fileText.end());
            fileText.erase(std::remove(fileText.begin(), fileText.end(), '\r'), fileText.end());

            DebugSupervisionFeatureSettingParent debugSettingParent;
            while (!fileText.empty())
            {
                size_t braceStart = fileText.find("{");
                size_t braceEnd = fileText.find("}");

                if (braceStart == std::string::npos || braceEnd == std::string::npos) break;
                if (fileText[0] != ' ' && fileText[0] != '{')
                {
                    debugSettingParent = DebugSupervisionFeatureSettingParent();

                    int descStart = fileText.find("[");
                    int descEnd = fileText.find("]");
                    if (descStart != std::string::npos && descEnd != std::string::npos && descStart == 0)
                    {
                        std::string descPayload = fileText.substr(descStart + 1, descEnd - (descStart + 1));
                        splitStringVector(debugSettingParent.description, descPayload, "#");
                        fileText.replace(descStart, (descEnd - descStart) + 1, "");
                    }

                    size_t nameStart = fileText.find_first_not_of(' ');
                    size_t nameEnd = fileText.find_first_of('{', nameStart) - 1;
                    debugSettingParent.nameParent = fileText.substr(nameStart, nameEnd - nameStart + 1);
                    fileText.erase(0, nameEnd + 2);

                    std::string children = fileText.substr(0, fileText.find("}"));
                    fileText.erase(0, children.size() + 1);
                    std::vector<std::string> childrenSplitted;
                    splitStringVector(childrenSplitted, children, ";");

                    for (int i = 0; i < childrenSplitted.size() - 1; i++)
                    {
                        std::string childrenTarget = childrenSplitted[i];
                        if (childrenTarget.find("(") == std::string::npos || childrenTarget.find(")") == std::string::npos) return false;

                        DebugSupervisionFeatureSetting featureSetting = DebugSupervisionFeatureSetting();
                        int descStart = childrenTarget.find("[");
                        int descEnd = childrenTarget.find("]");
                        if (descStart != std::string::npos && descEnd != std::string::npos)
                        {
                            std::string descPayload = childrenTarget.substr(descStart + 1, descEnd - (descStart + 1));
                            splitStringVector(featureSetting.description, descPayload, "#");
                            childrenTarget.replace(descStart, (descEnd - descStart) + 1, "");
                        }

                        nameStart = childrenTarget.find_first_not_of(' ');
                        nameEnd = childrenTarget.find_first_of('(', nameStart) - 1;
                        featureSetting.nameChild = childrenTarget.substr(nameStart, nameEnd - nameStart + 1);
                        featureSetting.nameParent = debugSettingParent.nameParent;
                        featureSetting.nameFull = debugSettingParent.nameParent + "." + featureSetting.nameChild;

                        std::string parameter = childrenTarget.substr(nameEnd + 2, childrenTarget.find(")") - (nameEnd + 2));

                        std::vector<std::string> parameterSplitted;
                        splitStringVector(parameterSplitted, parameter, ",");

                        bool typeFound = false;
                        bool widgetFound = false;

                        for (int h = 0; h < parameterSplitted.size(); h++)
                        {
                            std::string instruction = parameterSplitted[h];
                            if (!typeFound) if (instruction == "textbox" || instruction == "combobox" || instruction == "checkbox") typeFound = true;
                            else if (!widgetFound) if (instruction != "textbox" && instruction != "combobox" && instruction != "checkbox") widgetFound = true;

                            if (!typeFound)
                            {
                                featureSetting.value = Variable();
                                featureSetting.value.type = instruction;
                            }
                            if (typeFound && !widgetFound && h == 0)
                            {
                                featureSetting.type = "checkbox";
                                featureSetting.value = Variable();
                                featureSetting.value.type = "bool";
                            }
                            if (typeFound && !widgetFound)
                            {
                                featureSetting.type = instruction;
                            }
                            if (typeFound && widgetFound)
                            {
                                Variable comboboxElement = Variable();
                                comboboxElement.type = featureSetting.value.type;
                                comboboxElement.value = instruction;
                                featureSetting.comboboxValues.push_back(comboboxElement);
                            }
                        }

                        debugSettingParent.settings.push_back(featureSetting);
                    }
                    DebugSupervisionSettings.push_back(debugSettingParent);
                }
                if (fileText[0] == '{')
                {
                    ReleaseMutex(DebugSupervisionMutex);
                    return false;
                }
                fileText.erase(fileText.begin(), std::find_if(fileText.begin(), fileText.end(), [](unsigned char ch) { return !std::isspace(ch); }));
            }
        }

    }
    catch (const std::exception& e)
    {
        ReleaseMutex(DebugSupervisionMutex);
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }

    ReleaseMutex(DebugSupervisionMutex);
    return true;
}



#pragma once

struct DebugFunction {
    std::string nameParent;
    std::string nameChild;
    std::string nameFull;
    bool rapid;
    std::vector<Variable> parameter;
};

struct DebugFunctionParent {
    std::string nameParent;
    std::vector<DebugFunction> functions;
};

std::vector<DebugFunctionParent> DebugFunctions;

bool LoadDebugFunctions()
{
    try
    {
        for (const auto& _file : std::filesystem::directory_iterator(GlobalSettings.config_debugfunction_directory))
        {
            std::ifstream address_file = std::ifstream(_file.path());
            std::string fileText((std::istreambuf_iterator<char>(address_file)), std::istreambuf_iterator<char>());
            address_file.close();

            // Delete comments
            if (fileText.find("//") != std::string::npos) {
                while (fileText.find("//") != std::string::npos) {
                    int nIndex = fileText.find("\n", fileText.find("//"));
                    if (nIndex == std::string::npos) fileText.replace(fileText.find("//"), fileText.length() - fileText.find("//"), "");
                    else fileText.replace(fileText.find("//"), (nIndex + 1) - fileText.find("//"), "");
                }
            }

            // Delete hashtags
            if (fileText.find("#") != std::string::npos) {
                while (fileText.find("#") != std::string::npos) {
                    fileText.replace(fileText.find("#"), 1, "");
                }
            }

            // Delete tabulators
            if (fileText.find("\t") != std::string::npos) {
                while (fileText.find("\t") != std::string::npos) {
                    fileText.replace(fileText.find("\t"), 1, "");
                }
            }

            // Delete line breaks
            if (fileText.find("\n") != std::string::npos) {
                while (fileText.find("\n") != std::string::npos) {
                    fileText.replace(fileText.find("\n"), 1, "");
                }
            }

            // Delete line breaks
            if (fileText.find("\r") != std::string::npos) {
                while (fileText.find("\r") != std::string::npos) {
                    fileText.replace(fileText.find("\r"), 1, "");
                }
            }

            DebugFunctionParent debugAddressParent;
            while (fileText.length() > 0)
            {
                if (fileText.find("{") == std::string::npos || fileText.find("}") == std::string::npos) break;
                if (fileText[0] != ' ' && fileText[0] != '{')
                {
                    int index = 0;
                    int lastCharacterIndex = -1;
                    int startCharacterIndex = -1;
                    while (true)
                    {
                        if (fileText[index] != '{' && fileText[index] != ' ' && startCharacterIndex == -1) startCharacterIndex = index;
                        if (fileText[index] != '{' && fileText[index] != ' ') lastCharacterIndex = index;
                        if (fileText[index] == '{')
                        {
                            if (startCharacterIndex == -1 || lastCharacterIndex == -1) return false;
                            debugAddressParent = DebugFunctionParent();
                            debugAddressParent.nameParent = fileText.substr(startCharacterIndex, lastCharacterIndex - startCharacterIndex + 1);
                            fileText.replace(0, index + 1, "");
                            break;
                        }
                        index++;
                    }
                    std::string children = fileText.substr(0, fileText.find("}"));
                    if (children.find(";") == std::string::npos) return false;
                    fileText.replace(0, fileText.find("}") + 1, "");
                    std::vector<std::string> childrenSplitted;
                    splitStringVector(childrenSplitted, children, ";");
                    for (int i = 0; i < childrenSplitted.size() - 1; i++)
                    {
                        std::string childrenTarget = childrenSplitted[i];
                        if (childrenTarget.find("(") == std::string::npos || childrenTarget.find(")") == std::string::npos) return false;
                        DebugFunction debugAddress = DebugFunction();
                        index = 0;
                        lastCharacterIndex = -1;
                        startCharacterIndex = -1;
                        while (true)
                        {
                            if (childrenTarget[index] != '(' && childrenTarget[index] != ' ' && startCharacterIndex == -1) startCharacterIndex = index;
                            if (childrenTarget[index] != '(' && childrenTarget[index] != ' ') lastCharacterIndex = index;
                            if (childrenTarget[index] == '(')
                            {
                                if (startCharacterIndex == -1 || lastCharacterIndex == -1) return false;
                                debugAddress.nameChild = childrenTarget.substr(startCharacterIndex, lastCharacterIndex - startCharacterIndex + 1);
                                debugAddress.nameParent = debugAddressParent.nameParent;
                                debugAddress.nameFull = debugAddressParent.nameParent + "." + debugAddress.nameChild;
                                std::string types = childrenTarget.substr(index + 1, childrenTarget.find(")") - (index + 1));
                                std::vector<std::string> typesSplitted;
                                splitStringVector(typesSplitted, types, ",");
                                for (int k = 0; k < typesSplitted.size(); k++)
                                {
                                    if (typesSplitted[k] == "rapid")
                                    {
                                        debugAddress.rapid = true;
                                    }
                                    else
                                    {
                                        Variable para = Variable();
                                        para.type = typesSplitted[k];
                                        debugAddress.parameter.push_back(para);
                                    }
                                }
                                break;
                            }
                            index++;
                        }
                        debugAddressParent.functions.push_back(debugAddress);
                    }
                    DebugFunctions.push_back(debugAddressParent);
                }
                if (fileText[0] == '{') return false;
                if (fileText[0] == ' ') fileText.replace(0, 1, "");
            }

        }

        // Add TAS specific functions
        DebugFunction TASPlayScript = DebugFunction();
        TASPlayScript.nameChild = "PlayScript";
        TASPlayScript.nameFull = "TAS.PlayScript";
        TASPlayScript.nameParent = "TAS";
        TASPlayScript.parameter.push_back(Variable());
        TASPlayScript.parameter[0].type = "string";
        TASPlayScript.parameter[0].value = "none";
        TASPlayScript.rapid = false;

        DebugFunction TASRecordScript = DebugFunction();
        TASRecordScript.nameChild = "RecordScript";
        TASRecordScript.nameFull = "TAS.RecordScript";
        TASRecordScript.nameParent = "TAS";
        TASRecordScript.parameter.push_back(Variable());
        TASRecordScript.parameter[0].type = "string";
        TASRecordScript.parameter[0].value = "none";
        TASRecordScript.rapid = false;

        DebugFunctionParent TASParent = DebugFunctionParent();
        TASParent.nameParent = "TAS";
        TASParent.functions.push_back(TASPlayScript);
        TASParent.functions.push_back(TASRecordScript);
        DebugFunctions.push_back(TASParent);

        // Add DebugMenu specific functions
        DebugFunction DBGSetHotkeySlot = DebugFunction();
        DBGSetHotkeySlot.nameChild = "SetHotkeySlot";
        DBGSetHotkeySlot.nameFull = "DebugMenu.SetHotkeySlot";
        DBGSetHotkeySlot.nameParent = "DebugMenu";
        DBGSetHotkeySlot.parameter.push_back(Variable());
        DBGSetHotkeySlot.parameter[0].type = "int32";
        DBGSetHotkeySlot.parameter[0].value = "none";
        DBGSetHotkeySlot.rapid = false;

        DebugFunction DBGChangeHotkeySlot = DebugFunction();
        DBGChangeHotkeySlot.nameChild = "ChangeHotkeySlot";
        DBGChangeHotkeySlot.nameFull = "DebugMenu.ChangeHotkeySlot";
        DBGChangeHotkeySlot.nameParent = "DebugMenu";
        DBGChangeHotkeySlot.parameter.push_back(Variable());
        DBGChangeHotkeySlot.parameter[0].type = "int32";
        DBGChangeHotkeySlot.parameter[0].value = "none";
        DBGChangeHotkeySlot.rapid = false;

        DebugFunction DBGEnablePerformancemode = DebugFunction();
        DBGEnablePerformancemode.nameChild = "EnablePerformancemode";
        DBGEnablePerformancemode.nameFull = "DebugMenu.EnablePerformancemode";
        DBGEnablePerformancemode.nameParent = "DebugMenu";
        DBGEnablePerformancemode.parameter.push_back(Variable());
        DBGEnablePerformancemode.parameter[0].type = "bool";
        DBGEnablePerformancemode.parameter[0].value = "none";
        DBGEnablePerformancemode.rapid = false;

        DebugFunction DBGEnableDebugValues = DebugFunction();
        DBGEnableDebugValues.nameChild = "EnableDebugValues";
        DBGEnableDebugValues.nameFull = "DebugMenu.EnableDebugValues";
        DBGEnableDebugValues.nameParent = "DebugMenu";
        DBGEnableDebugValues.parameter.push_back(Variable());
        DBGEnableDebugValues.parameter[0].type = "bool";
        DBGEnableDebugValues.parameter[0].value = "none";
        DBGEnableDebugValues.rapid = false;

        DebugFunction DBGEnableCursorPosition = DebugFunction();
        DBGEnableCursorPosition.nameChild = "EnableCursorPosition";
        DBGEnableCursorPosition.nameFull = "DebugMenu.EnableCursorPosition";
        DBGEnableCursorPosition.nameParent = "DebugMenu";
        DBGEnableCursorPosition.parameter.push_back(Variable());
        DBGEnableCursorPosition.parameter[0].type = "bool";
        DBGEnableCursorPosition.parameter[0].value = "none";
        DBGEnableCursorPosition.rapid = false;

        DebugFunction DBGEnableHotkeyOverlay = DebugFunction();
        DBGEnableHotkeyOverlay.nameChild = "EnableHotkeyOverlay";
        DBGEnableHotkeyOverlay.nameFull = "DebugMenu.EnableHotkeyOverlay";
        DBGEnableHotkeyOverlay.nameParent = "DebugMenu";
        DBGEnableHotkeyOverlay.parameter.push_back(Variable());
        DBGEnableHotkeyOverlay.parameter[0].type = "bool";
        DBGEnableHotkeyOverlay.parameter[0].value = "none";
        DBGEnableHotkeyOverlay.rapid = false;

        DebugFunctionParent DBGParent = DebugFunctionParent();
        DBGParent.nameParent = "DebugMenu";
        DBGParent.functions.push_back(DBGSetHotkeySlot);
        DBGParent.functions.push_back(DBGChangeHotkeySlot);
        DBGParent.functions.push_back(DBGEnablePerformancemode);
        DBGParent.functions.push_back(DBGEnableDebugValues);
        DBGParent.functions.push_back(DBGEnableCursorPosition);
        DBGParent.functions.push_back(DBGEnableHotkeyOverlay);
        DebugFunctions.push_back(DBGParent);

   }
    catch (const std::exception& e)
    {
        DebugConsoleOutput(e.what(), false, "red");
    }

    return true;
}



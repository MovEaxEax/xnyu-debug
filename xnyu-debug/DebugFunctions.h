#pragma once

struct DebugFunction {
    std::string nameParent;
    std::string nameChild;
    std::string nameFull;
    std::vector<std::string> description;
    std::string placeholder;
    bool rapid;
    std::vector<Variable> parameter;
};

struct DebugFunctionParent {
    std::string nameParent;
    std::vector<std::string> description;
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
            size_t commentStart;
            while ((commentStart = fileText.find("//")) != std::string::npos) {
                size_t lineEnd = fileText.find("\n", commentStart);
                fileText.erase(commentStart, lineEnd != std::string::npos ? lineEnd - commentStart + 1 : std::string::npos);
            }

            // Delete tabs, line breaks, and carriage returns
            fileText.erase(std::remove(fileText.begin(), fileText.end(), '\t'), fileText.end());
            fileText.erase(std::remove(fileText.begin(), fileText.end(), '\n'), fileText.end());
            fileText.erase(std::remove(fileText.begin(), fileText.end(), '\r'), fileText.end());

            DebugFunctionParent debugAddressParent;
            while (!fileText.empty())
            {
                size_t braceStart = fileText.find("{");
                size_t braceEnd = fileText.find("}");

                if (braceStart == std::string::npos || braceEnd == std::string::npos) break;
                if (fileText[0] != ' ' && fileText[0] != '{')
                {
                    debugAddressParent = DebugFunctionParent();

                    int descStart = fileText.find("[");
                    int descEnd = fileText.find("]");
                    if (descStart != std::string::npos && descEnd != std::string::npos && descStart == 0)
                    {
                        std::string descPayload = fileText.substr(descStart + 1, descEnd - (descStart + 1));
                        splitStringVector(debugAddressParent.description, descPayload, "#");
                        fileText.replace(descStart, (descEnd - descStart) + 1, "");
                    }

                    size_t nameStart = fileText.find_first_not_of(' ');
                    size_t nameEnd = fileText.find_first_of('{', nameStart) - 1;
                    debugAddressParent.nameParent = fileText.substr(nameStart, nameEnd - nameStart + 1);
                    fileText.erase(0, nameEnd + 2);

                    std::string children = fileText.substr(0, fileText.find("}"));
                    fileText.erase(0, children.size() + 1);
                    std::vector<std::string> childrenSplitted;
                    splitStringVector(childrenSplitted, children, ";");

                    for (int i = 0; i < childrenSplitted.size() - 1; i++)
                    {
                        std::string childrenTarget = childrenSplitted[i];
                        if (childrenTarget.find("(") == std::string::npos || childrenTarget.find(")") == std::string::npos) return false;

                        DebugFunction debugAddress = DebugFunction();
                        int descStart = childrenTarget.find("[");
                        int descEnd = childrenTarget.find("]");
                        if (descStart != std::string::npos && descEnd != std::string::npos)
                        {
                            std::string descPayload = childrenTarget.substr(descStart + 1, descEnd - (descStart + 1));
                            splitStringVector(debugAddress.description, descPayload, "#");
                            childrenTarget.replace(descStart, (descEnd - descStart) + 1, "");
                        }

                        nameStart = childrenTarget.find_first_not_of(' ');
                        nameEnd = childrenTarget.find_first_of('(', nameStart) - 1;
                        debugAddress.nameChild = childrenTarget.substr(nameStart, nameEnd - nameStart + 1);
                        debugAddress.nameParent = debugAddressParent.nameParent;
                        debugAddress.nameFull = debugAddressParent.nameParent + "." + debugAddress.nameChild;

                        std::string types = childrenTarget.substr(nameEnd + 2, childrenTarget.find(")") - (nameEnd + 2));
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
                                debugAddress.placeholder += para.type + (k + 1 < typesSplitted.size() && typesSplitted[k + 1] != "rapid" ? "," : "");
                                debugAddress.parameter.push_back(para);
                            }
                        }
                        debugAddress.placeholder += "...";
                        debugAddressParent.functions.push_back(debugAddress);
                    }
                    DebugFunctions.push_back(debugAddressParent);
                }
                if (fileText[0] == '{') return false;
                fileText.erase(fileText.begin(), std::find_if(fileText.begin(), fileText.end(), [](unsigned char ch) { return !std::isspace(ch); }));
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
        TASPlayScript.description.push_back("TAS.PlayScript(string)");
        TASPlayScript.description.push_back("");
        TASPlayScript.description.push_back("Run an existing NTL script");
        TASPlayScript.description.push_back("The script has to be saved in the default script directory");
        TASPlayScript.description.push_back("Use the '/' to define a subdirectory");
        TASPlayScript.description.push_back("");
        TASPlayScript.description.push_back("  - string: Name of the script that get's played");
        TASPlayScript.placeholder = "string...";

        DebugFunction TASRecordScript = DebugFunction();
        TASRecordScript.nameChild = "RecordScript";
        TASRecordScript.nameFull = "TAS.RecordScript";
        TASRecordScript.nameParent = "TAS";
        TASRecordScript.parameter.push_back(Variable());
        TASRecordScript.parameter[0].type = "string";
        TASRecordScript.parameter[0].value = "none";
        TASRecordScript.rapid = false;
        TASRecordScript.description.push_back("TAS.RecordScript(string)");
        TASRecordScript.description.push_back("");
        TASRecordScript.description.push_back("Start a new recording of a NTL script");
        TASRecordScript.description.push_back("Scripts are saved in the default script directory");
        TASRecordScript.description.push_back("Use the '/' to define a subdirectory");
        TASRecordScript.description.push_back("If no name is defined, it uses the default name format (current time)");
        TASRecordScript.description.push_back("");
        TASRecordScript.description.push_back("  - string: Name of the script that get's recorded (Optional)");
        TASRecordScript.placeholder = "string...";

        DebugFunctionParent TASParent = DebugFunctionParent();
        TASParent.nameParent = "TAS";
        TASParent.functions.push_back(TASPlayScript);
        TASParent.functions.push_back(TASRecordScript);
        TASParent.description.push_back("- TAS -");
        TASParent.description.push_back("");
        TASParent.description.push_back("Communicate with the internal functions to control TAS");
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
        DBGSetHotkeySlot.description.push_back("DebugMenu.SetHotkeySlot(int32)");
        DBGSetHotkeySlot.description.push_back("");
        DBGSetHotkeySlot.description.push_back("Set the current selected Hotkey slot to an absolute value");
        DBGSetHotkeySlot.description.push_back("");
        DBGSetHotkeySlot.description.push_back("Value must be between 1 and 8");
        DBGSetHotkeySlot.description.push_back("");
        DBGSetHotkeySlot.description.push_back("  - int32: The new slot index");
        DBGSetHotkeySlot.placeholder = "int32...";

        DebugFunction DBGChangeHotkeySlot = DebugFunction();
        DBGChangeHotkeySlot.nameChild = "ChangeHotkeySlot";
        DBGChangeHotkeySlot.nameFull = "DebugMenu.ChangeHotkeySlot";
        DBGChangeHotkeySlot.nameParent = "DebugMenu";
        DBGChangeHotkeySlot.parameter.push_back(Variable());
        DBGChangeHotkeySlot.parameter[0].type = "int32";
        DBGChangeHotkeySlot.parameter[0].value = "none";
        DBGChangeHotkeySlot.rapid = false;
        DBGChangeHotkeySlot.description.push_back("DebugMenu.ChangeHotkeySlot(int32)");
        DBGChangeHotkeySlot.description.push_back("");
        DBGChangeHotkeySlot.description.push_back("Change the current selected Hotkey slot by a relative value");
        DBGChangeHotkeySlot.description.push_back("");
        DBGChangeHotkeySlot.description.push_back("  - int32: The amount of slots you want to jump");
        DBGChangeHotkeySlot.placeholder = "int32...";

        DebugFunction DBGEnablePerformancemode = DebugFunction();
        DBGEnablePerformancemode.nameChild = "EnablePerformancemode";
        DBGEnablePerformancemode.nameFull = "DebugMenu.EnablePerformancemode";
        DBGEnablePerformancemode.nameParent = "DebugMenu";
        DBGEnablePerformancemode.parameter.push_back(Variable());
        DBGEnablePerformancemode.parameter[0].type = "bool";
        DBGEnablePerformancemode.parameter[0].value = "none";
        DBGEnablePerformancemode.rapid = false;
        DBGEnablePerformancemode.description.push_back("DebugMenu.EnablePerformancemode(bool)");
        DBGEnablePerformancemode.description.push_back("");
        DBGEnablePerformancemode.description.push_back("Enable/Disable the Performance mode");
        DBGEnablePerformancemode.description.push_back("");
        DBGEnablePerformancemode.description.push_back("If the boolean is blank, this function can be used as a toggle");
        DBGEnablePerformancemode.description.push_back("");
        DBGEnablePerformancemode.description.push_back("  - bool: Enable/Disable (Optional)");
        DBGEnablePerformancemode.placeholder = "bool...";

        DebugFunction DBGEnableDebugValues = DebugFunction();
        DBGEnableDebugValues.nameChild = "EnableDebugValues";
        DBGEnableDebugValues.nameFull = "DebugMenu.EnableDebugValues";
        DBGEnableDebugValues.nameParent = "DebugMenu";
        DBGEnableDebugValues.parameter.push_back(Variable());
        DBGEnableDebugValues.parameter[0].type = "bool";
        DBGEnableDebugValues.parameter[0].value = "none";
        DBGEnableDebugValues.rapid = false;
        DBGEnableDebugValues.description.push_back("DebugMenu.EnableDebugValues(bool)");
        DBGEnableDebugValues.description.push_back("");
        DBGEnableDebugValues.description.push_back("Enable/Disable the Debug Values mode");
        DBGEnableDebugValues.description.push_back("");
        DBGEnableDebugValues.description.push_back("If the boolean is blank, this function can be used as a toggle");
        DBGEnableDebugValues.description.push_back("");
        DBGEnableDebugValues.description.push_back("  - bool: Enable/Disable (Optional)");
        DBGEnableDebugValues.placeholder = "bool...";

        DebugFunction DBGEnableCursorPosition = DebugFunction();
        DBGEnableCursorPosition.nameChild = "EnableCursorPosition";
        DBGEnableCursorPosition.nameFull = "DebugMenu.EnableCursorPosition";
        DBGEnableCursorPosition.nameParent = "DebugMenu";
        DBGEnableCursorPosition.parameter.push_back(Variable());
        DBGEnableCursorPosition.parameter[0].type = "bool";
        DBGEnableCursorPosition.parameter[0].value = "none";
        DBGEnableCursorPosition.rapid = false;
        DBGEnableCursorPosition.description.push_back("DebugMenu.CursorPosition(bool)");
        DBGEnableCursorPosition.description.push_back("");
        DBGEnableCursorPosition.description.push_back("Enable/Disable the Cursor Position mode");
        DBGEnableCursorPosition.description.push_back("");
        DBGEnableCursorPosition.description.push_back("If the boolean is blank, this function can be used as a toggle");
        DBGEnableCursorPosition.description.push_back("");
        DBGEnableCursorPosition.description.push_back("  - bool: Enable/Disable (Optional)");
        DBGEnableCursorPosition.placeholder = "bool...";

        DebugFunction DBGEnableHotkeyOverlay = DebugFunction();
        DBGEnableHotkeyOverlay.nameChild = "EnableHotkeyOverlay";
        DBGEnableHotkeyOverlay.nameFull = "DebugMenu.EnableHotkeyOverlay";
        DBGEnableHotkeyOverlay.nameParent = "DebugMenu";
        DBGEnableHotkeyOverlay.parameter.push_back(Variable());
        DBGEnableHotkeyOverlay.parameter[0].type = "bool";
        DBGEnableHotkeyOverlay.parameter[0].value = "none";
        DBGEnableHotkeyOverlay.rapid = false;
        DBGEnableHotkeyOverlay.description.push_back("DebugMenu.HotkeyOverlay(bool)");
        DBGEnableHotkeyOverlay.description.push_back("");
        DBGEnableHotkeyOverlay.description.push_back("Enable/Disable the Hotkey overlay");
        DBGEnableHotkeyOverlay.description.push_back("");
        DBGEnableHotkeyOverlay.description.push_back("If the boolean is blank, this function can be used as a toggle");
        DBGEnableHotkeyOverlay.description.push_back("");
        DBGEnableHotkeyOverlay.description.push_back("  - bool: Enable/Disable (Optional)");
        DBGEnableHotkeyOverlay.placeholder = "bool...";

        DebugFunction DBGEnableSupervision = DebugFunction();
        DBGEnableSupervision.nameChild = "EnableSupervision";
        DBGEnableSupervision.nameFull = "DebugMenu.EnableSupervision";
        DBGEnableSupervision.nameParent = "DebugMenu";
        DBGEnableSupervision.parameter.push_back(Variable());
        DBGEnableSupervision.parameter[0].type = "bool";
        DBGEnableSupervision.parameter[0].value = "none";
        DBGEnableSupervision.rapid = false;
        DBGEnableSupervision.description.push_back("DebugMenu.EnableSupervision(bool)");
        DBGEnableSupervision.description.push_back("");
        DBGEnableSupervision.description.push_back("Enable/Disable the Supervision mode");
        DBGEnableSupervision.description.push_back("");
        DBGEnableSupervision.description.push_back("If the boolean is blank, this function can be used as a toggle");
        DBGEnableSupervision.description.push_back("");
        DBGEnableSupervision.description.push_back("  - bool: Enable/Disable (Optional)");
        DBGEnableSupervision.placeholder = "bool...";

        DebugFunction DBGEnableEditorMode = DebugFunction();
        DBGEnableEditorMode.nameChild = "EnableEditorMode";
        DBGEnableEditorMode.nameFull = "DebugMenu.EnableEditorMode";
        DBGEnableEditorMode.nameParent = "DebugMenu";
        DBGEnableEditorMode.parameter.push_back(Variable());
        DBGEnableEditorMode.parameter[0].type = "bool";
        DBGEnableEditorMode.parameter[0].value = "none";
        DBGEnableEditorMode.rapid = false;
        DBGEnableEditorMode.description.push_back("DebugMenu.EnableEditorMode(bool)");
        DBGEnableEditorMode.description.push_back("");
        DBGEnableEditorMode.description.push_back("Enable/Disable the Editor mode");
        DBGEnableEditorMode.description.push_back("");
        DBGEnableEditorMode.description.push_back("If the boolean is blank, this function can be used as a toggle");
        DBGEnableEditorMode.description.push_back("");
        DBGEnableEditorMode.description.push_back("  - bool: Enable/Disable (Optional)");
        DBGEnableEditorMode.placeholder = "bool...";

        DebugFunctionParent DBGParent = DebugFunctionParent();
        DBGParent.nameParent = "DebugMenu";
        DBGParent.functions.push_back(DBGSetHotkeySlot);
        DBGParent.functions.push_back(DBGChangeHotkeySlot);
        DBGParent.functions.push_back(DBGEnablePerformancemode);
        DBGParent.functions.push_back(DBGEnableDebugValues);
        DBGParent.functions.push_back(DBGEnableCursorPosition);
        DBGParent.functions.push_back(DBGEnableHotkeyOverlay);
        DBGParent.functions.push_back(DBGEnableSupervision);
        DBGParent.functions.push_back(DBGEnableEditorMode);
        DBGParent.description.push_back("- DebugMenu -");
        DBGParent.description.push_back("");
        DBGParent.description.push_back("Communicate with the internal functions of the Debug Menu");
        DebugFunctions.push_back(DBGParent);
   }
    catch (const std::exception& e)
    {
        DebugConsoleOutput(e.what(), false, "red");
    }

    return true;
}



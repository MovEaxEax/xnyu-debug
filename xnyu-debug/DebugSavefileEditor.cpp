#include "pch.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "Variable.h"
#include "Conversions.h"
#include "DebugSavefileEditor.h"



// --- Variables ---
std::vector<SavefileParent> SavefileParents;
std::vector<std::string> SavefileFiles;
std::string SavefileCurrentFile = "";
int SavefileParentFocus = 0;
int SavefileFielFocus = 0;
char* SavefileFilesBuffer = new char[2048];
HANDLE DebugSavefileEditorMutex = CreateMutex(NULL, FALSE, NULL);



// --- Functions ---
bool LoadSavefileLayouts()
{
    WaitForSingleObject(DebugSavefileEditorMutex, INFINITE);
    try
    {
        std::string debugSavefileDirectorySetting = GetGlobalSetting("config_savefile_directory");

        for (const auto& _file : std::filesystem::directory_iterator(debugSavefileDirectorySetting))
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

            SavefileParent savefileParent = SavefileParent();
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
                            savefileParent = SavefileParent();
                            savefileParent.nameParent = fileText.substr(startCharacterIndex, lastCharacterIndex - startCharacterIndex + 1);
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

                        SavefileField savefileField = SavefileField();
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
                                savefileField.nameChild = childrenTarget.substr(startCharacterIndex, lastCharacterIndex - startCharacterIndex + 1);
                                savefileField.nameParent = savefileParent.nameParent;
                                savefileField.nameFull = savefileParent.nameParent + "." + savefileField.nameChild;
                                std::string parameter = childrenTarget.substr(index + 1, childrenTarget.find(")") - (index + 1));
                                savefileField.value.type = parameter;
                                break;
                            }
                            index++;
                        }
                        savefileParent.fields.push_back(savefileField);
                    }
                    SavefileParents.push_back(savefileParent);
                }
                if (fileText[0] == '{')
                {
                    ReleaseMutex(DebugSavefileEditorMutex);
                    return false;
                }
                if (fileText[0] == ' ') fileText.replace(0, 1, "");
            }
        }
    }
    catch (const std::exception& e)
    {
        ReleaseMutex(DebugSavefileEditorMutex);
        DebugConsoleOutput(e.what(), false, "red");
        return false;
    }

    ReleaseMutex(DebugSavefileEditorMutex);
    return true;
}



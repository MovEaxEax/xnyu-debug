#include "pch.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "Variable.h"
#include "Conversions.h"
#include "DebugAddresses.h"



// --- Variables ---
std::vector<DebugAddressParent> DebugAddresses;
HANDLE DebugAddressesMutex = CreateMutex(NULL, FALSE, NULL);



// --- Functions ---
bool DebugAddressSortNameParent(DebugAddress a, DebugAddress b) {
    return a.nameParent < b.nameParent;
}

bool DebugAddressSortNameChild(DebugAddress a, DebugAddress b) {
    return a.nameChild < b.nameChild;
}

bool DebugAddressSortNameFull(DebugAddress a, DebugAddress b) {
    return a.nameFull < b.nameFull;
}

std::vector<DebugAddressParent> GetDebugAddresses() {
    WaitForSingleObject(DebugAddressesMutex, INFINITE);
    std::vector<DebugAddressParent> result = DebugAddresses;
    ReleaseMutex(DebugAddressesMutex);
    return result;
}

void SetDebugAddresses(std::vector<DebugAddressParent> debugAddresses) {
    WaitForSingleObject(DebugAddressesMutex, INFINITE);
    DebugAddresses = debugAddresses;
    ReleaseMutex(DebugAddressesMutex);
}

bool LoadDebugAddresses()
{
    WaitForSingleObject(DebugAddressesMutex, INFINITE);
    try
    {
        std::string debugAddressDirectorySetting = GetGlobalSetting("config_debugaddress_directory");

        for (const auto& _file : std::filesystem::directory_iterator(debugAddressDirectorySetting))
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

            DebugAddressParent debugAddressParent;
            while (!fileText.empty())
            {
                size_t braceStart = fileText.find("{");
                size_t braceEnd = fileText.find("}");

                if (braceStart == std::string::npos || braceEnd == std::string::npos) break;
                if (fileText[0] != ' ' && fileText[0] != '{')
                {
                    debugAddressParent = DebugAddressParent();

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

                        DebugAddress debugAddress = DebugAddress();
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

                        std::string parameter = childrenTarget.substr(nameEnd + 2, childrenTarget.find(")") - (nameEnd + 2));
                        if (parameter.find(",") != std::string::npos)
                        {
                            std::vector<std::string> parameterSplitted;
                            splitStringVector(parameterSplitted, parameter, ",");
                            for (int h = 0; h < parameterSplitted.size(); h++)
                            {
                                if (parameterSplitted[h] == "hex") debugAddress.value.forceHex = true;
                                else debugAddress.value.type = parameterSplitted[h];
                            }
                        }
                        else
                        {
                            debugAddress.value.forceHex = false;
                            debugAddress.value.type = parameter;
                        }

                        debugAddressParent.addresses.push_back(debugAddress);
                    }
                    DebugAddresses.push_back(debugAddressParent);
                }
                if (fileText[0] == '{')
                {
                    ReleaseMutex(DebugAddressesMutex);
                    return false;
                }
                fileText.erase(fileText.begin(), std::find_if(fileText.begin(), fileText.end(), [](unsigned char ch) { return !std::isspace(ch); }));
            }
        }

    }
    catch (const std::exception& e)
    {
        DebugConsoleOutput(e.what(), false, "red");
        ReleaseMutex(DebugAddressesMutex);
        return false;
    }

    ReleaseMutex(DebugAddressesMutex);
    return true;
}



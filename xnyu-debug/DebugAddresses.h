#pragma once

struct DebugAddress {
    std::string nameParent;
    std::string nameChild;
    std::string nameFull;
    Variable value;
};

struct DebugAddressParent {
    std::string nameParent;
    std::vector<DebugAddress> addresses;
};

std::vector<DebugAddressParent> DebugAddresses;

bool DebugAddressSortNameParent(DebugAddress a, DebugAddress b) {
    return a.nameParent < b.nameParent;
}

bool DebugAddressSortNameChild(DebugAddress a, DebugAddress b) {
    return a.nameChild < b.nameChild;
}

bool DebugAddressSortNameFull(DebugAddress a, DebugAddress b) {
    return a.nameFull < b.nameFull;
}

bool LoadDebugAddresses()
{
    try
    {
        for (const auto& _file : std::filesystem::directory_iterator(GlobalSettings.config_debugaddress_directory))
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

            DebugAddressParent debugAddressParent;
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
                            debugAddressParent = DebugAddressParent();
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
                        DebugAddress debugAddress = DebugAddress();
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
                                std::string parameter = childrenTarget.substr(index + 1, childrenTarget.find(")") - (index + 1));
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
                                break;
                            }
                            index++;
                        }
                        debugAddressParent.addresses.push_back(debugAddress);
                    }
                    DebugAddresses.push_back(debugAddressParent);
                }
                if (fileText[0] == '{') return false;
                if (fileText[0] == ' ') fileText.replace(0, 1, "");
            }

        }
    }
    catch (const std::exception& e)
    {
        DebugConsoleOutput(e.what(), false, "red");
    }

    return true;
}



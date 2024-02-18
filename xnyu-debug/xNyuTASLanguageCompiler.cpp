#include "pch.h"
#include "Conversions.h"
#include "Logging.h"
#include "GlobalSettings.h"
#include "Variable.h"
#include "xNyuTASLanguageDatatypes.h"
#include "xNyuTASLanguageCreateInstructions.h"
#include "xNyuTASLanguageCompiler.h"



// --- Variables ---



// --- Functions ---
std::string NTLGenerateUUID() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 25);
    std::uniform_int_distribution<> disAlphaNum(0, 35);

    char firstChar = 'a' + dis(gen);

    std::string result = "";
    result += firstChar;

    for (int i = 1; i < 16; ++i) {
        int val = disAlphaNum(gen);
        if (val < 26) {
            result += 'a' + val;
        }
        else {
            result += '0' + (val - 26);
        }
    }

    return result;
}

std::pair<std::string, int> NTLFindNextType(std::string& content, int startIndex, std::string extra)
{
    std::pair<std::string, int> result;
    std::vector<std::pair<std::string, int>> dataTypes = {
        {"byte", content.find("byte" + extra, startIndex)},
        {"int32", content.find("int32" + extra, startIndex)},
        {"int64", content.find("int64" + extra, startIndex)},
        {"float", content.find("float" + extra, startIndex)},
        {"double", content.find("double" + extra, startIndex)},
        {"string", content.find("string" + extra, startIndex)},
        {"void", content.find("void" + extra, startIndex)}
    };

    result.first = "";
    result.second = -1;

    for (const auto& type : dataTypes) {
        if (type.second != std::string::npos)
        {
            if (result.second == -1)
            {
                result.first = type.first;
                result.second = type.second;
            }
            else if (type.second < result.second)
            {
                result.first = type.first;
                result.second = type.second;
            }
        }
    }

    return result;
}

std::pair<std::string, int> NTLFindNextFunctionalOperator(std::string& content, int startIndex, std::string extra)
{
    std::pair<std::string, int> result;
    std::vector<std::pair<std::string, int>> dataTypes = {
        {"(", content.find("(" + extra, startIndex)},
        {")", content.find(")" + extra, startIndex)},
        {"{", content.find("{" + extra, startIndex)},
        {"}", content.find("}" + extra, startIndex)},
        {";", content.find(";" + extra, startIndex)},
    };

    result.first = "";
    result.second = -1;

    for (const auto& type : dataTypes) {
        if (type.second != std::string::npos)
        {
            if (result.second == -1)
            {
                result.first = type.first;
                result.second = type.second;
            }
            else if (type.second < result.second)
            {
                result.first = type.first;
                result.second = type.second;
            }
        }
    }

    return result;
}

std::pair<std::string, int> NTLFindDelegationOperator(std::string& content, int startIndex, std::string extra)
{
    std::pair<std::string, int> result;
    std::vector<std::pair<std::string, int>> dataTypes = {
        {"++;", content.find("(" + extra, startIndex)},
        {"--;", content.find(")" + extra, startIndex)},
        {"+=", content.find("{" + extra, startIndex)},
        {"-=", content.find("}" + extra, startIndex)},
        {"*=", content.find(";" + extra, startIndex)},
        {"/=", content.find(";" + extra, startIndex)},
        {"=", content.find(";" + extra, startIndex)},
    };

    result.first = "";
    result.second = -1;

    for (const auto& type : dataTypes) {
        if (type.second != std::string::npos)
        {
            if (result.second == -1)
            {
                result.first = type.first;
                result.second = type.second;
            }
            else if (type.second < result.second)
            {
                result.first = type.first;
                result.second = type.second;
            }
        }
    }

    return result;
}

std::pair<std::string, std::string> NTLSplitTypeIdentifier(std::string& payload)
{
    std::pair<std::string, std::string> result;

    int seperatorIndex = payload.find("#");
    result.first = payload.substr(0, seperatorIndex);
    result.second = payload.substr(seperatorIndex + 1, payload.length() - (seperatorIndex + 1));

    return result;
}

int NTLFindParantheseCloseIndex(std::string& target, int startIndex) {
    int index = startIndex;
    int opens = 0;
    while (index < target.length())
    {
        int openIndex = target.find("{", index);
        int closeIndex = target.find("}", index);
        if (openIndex == -1 && closeIndex == -1) return -1;
        if (openIndex > closeIndex)
        {
            opens++;
            index = openIndex + 1;
        }
        else
        {
            if (opens == 0) return closeIndex;
            opens--;
            index = closeIndex + 1;
        }
    }
}

bool NTLReadAllFunctions(std::string& content, std::vector<FunctionSignature>* functions) {

    int index = 0;
    while (true)
    {
        if (index >= content.length()) break;
        std::pair<std::string, int> nextType = NTLFindNextType(content, index, "#");
        if (nextType.second == -1) break;
        std::pair<std::string, int> nextOperatorStart = NTLFindNextFunctionalOperator(content, nextType.second, "");
        if (nextOperatorStart.second == -1) break;

        if (nextOperatorStart.first == "(")
        {
            FunctionSignature functionTarget = FunctionSignature();
            int endParameter = content.find(")", nextType.second);
            std::string parameterPayload = subtringBetween(content, nextOperatorStart.second, endParameter);
            std::vector<std::string> parameterSplitted;
            splitStringVector(functionTarget.parameter, parameterPayload, ",");
            functionTarget.name = subtringBetween(content, nextType.second + nextType.first.length(), nextOperatorStart.second);
            functionTarget.returntype = nextType.first;
            int startParanthesis = content.find("{", endParameter);
            int endParanthesis = NTLFindParantheseCloseIndex(content, startParanthesis + 1);
            functionTarget.content = subtringBetween(content, startParanthesis, endParanthesis);
            functionTarget.uuid = NTLGenerateUUID();
            functions->push_back(functionTarget);
            index = endParanthesis + 1;
        }
        else
        {
            index = nextOperatorStart.second + 1;
        }
    }

    return true;
}

std::vector<std::string> NTLFindImports(std::string& str, std::vector<std::string>& ignoreList) {
    std::regex importRegex("import\\{\"(.*?)\"\\}");
    std::smatch match;
    std::vector<std::string> imports;

    while (std::regex_search(str, match, importRegex)) {
        std::string finding = match[1].str();
        if (!stringVectorContains(ignoreList, finding))
        {
            ignoreList.push_back(finding);
            imports.push_back(finding);
        }
        str.erase(match.position(), match.length());
    }

    return imports;
}

std::string NTLResolvePathTraversing(std::string base, std::string target) {
    std::string normalizedBase = base;
    if (normalizedBase.back() != '\\' && normalizedBase.back() != '/') normalizedBase += '\\';

    std::stringstream ss(target);
    std::string segment;
    std::vector<std::string> segments;

    while (std::getline(ss, segment, '\\')) {
        segments.push_back(segment);
    }

    for (const auto& seg : segments) {
        if (seg == "..") {
            size_t lastSeparator = normalizedBase.find_last_of("\\/", normalizedBase.size() - 2);
            if (lastSeparator != std::string::npos) normalizedBase.erase(lastSeparator + 1);
            else normalizedBase += seg + '\\';
        }
        else if (seg != ".") {
            normalizedBase += seg + '\\';
        }
    }

    if (!normalizedBase.empty() && (normalizedBase.back() == '\\' || normalizedBase.back() == '/')) normalizedBase.pop_back();

    return normalizedBase;
}

std::string NTLReadFileFormatted(std::string filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return "";

    std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

    int pos;
    while ((pos = content.find("//")) != std::string::npos) {
        int endOfLine = content.find("\n", pos);
        content.erase(pos, endOfLine != std::string::npos ? endOfLine - pos : std::string::npos);
    }
    while ((pos = content.find("/*")) != std::string::npos) {
        int endComment = content.find("*/", pos + 2);
        content.erase(pos, endComment != std::string::npos ? endComment + 2 - pos : std::string::npos);
    }

    bool insideString = false;
    for (auto& c : content) {
        if (c == '"' || c == '\'') {
            insideString = !insideString;
        }
        if (!insideString && c >= 'A' && c <= 'Z') {
            c = std::tolower(c);
        }
    }

    int contentIndex = 0;
    while (true)
    {
        if (contentIndex >= content.length()) break;

        std::pair<std::string, int> targetType = NTLFindNextType(content, contentIndex);

        if (targetType.second == -1) break;
        if (content[targetType.second + targetType.first.length()] == ' ') content.insert(targetType.second + targetType.first.length(), "#");
        contentIndex = targetType.second + targetType.first.length() + 1;
    }

    contentIndex = 0;
    while (true)
    {
        if (contentIndex >= content.length()) break;
        int finding = content.find("return ", contentIndex);
        if (finding == std::string::npos) break;
        content.replace(finding, 7, "return#");
        contentIndex = finding + 7;
    }

    insideString = false;
    content.erase(std::remove_if(content.begin(), content.end(),
        [&](char c) {
            if (c == '"' || c == '\'') {
                insideString = !insideString;
            }
            if (insideString) {
                return c == '\n' || c == '\r' || c == '\t';
            }
            else {
                return c == ' ' || c == '\n' || c == '\r' || c == '\t';
            }
        }), content.end());

    return content;
}

void NTLReadAllCodeFiles(std::string directory, std::string filename, std::string& code, std::vector<std::string>& ignoreList) {
    std::string targetFile = NTLResolvePathTraversing(directory, filename);
    code += NTLReadFileFormatted(directory + filename);
    std::vector<std::string> imports = NTLFindImports(code, ignoreList);
    for (int i = 0; i < imports.size(); i++) NTLReadAllCodeFiles(directory, filename, code, ignoreList);
}

bool NTLCompileNextInstruction(std::vector<Instruction>* targetInstructions, std::vector<FunctionSignature>* functions, FunctionSignature* currentFunction, std::vector<Variable>* usedVariables, std::string& content, int* tmpVariableIncrease)
{
    std::pair<std::string, int> nextFunctionalOperator = NTLFindNextFunctionalOperator(content, 0, "");

    if (nextFunctionalOperator.first == "(")
    {
        // No delegation
        std::string instructionName = subtringFromTo(content, 0, nextFunctionalOperator.second);
        std::string parameterPayload = subtringBetween(content, content.find("("), content.find(")"));
        int endInstructionIndex = 0;

        if (instructionName == "if")
        {
            int skipOffsetStart = targetInstructions->size();
            int startParantheseIndex = content.find("{");
            int endParantheseIndex = NTLFindParantheseCloseIndex(content, startParantheseIndex + 1);
            std::string contentInParanthese = subtringBetween(content, startParantheseIndex, endParantheseIndex);
            endInstructionIndex = endParantheseIndex;

            bool isOr = parameterPayload.find("||") != std::string::npos;
            bool isAnd = parameterPayload.find("&&") != std::string::npos;

            std::vector<std::string> conditionParameter;
            if (isOr || isAnd) splitStringVector(conditionParameter, parameterPayload, isOr ? "||" : "&&");
            else conditionParameter.push_back(parameterPayload);

            Instruction ifInstruction = Instruction();
            ifInstruction.opcode = OpCode::IF;

            for (int i = 0; i < conditionParameter.size(); i++)
            {
                std::string comparer = "";
                std::string compareA = "";
                std::string compareB = "";
                if (conditionParameter[i].find("==")) comparer = "==";
                else if (conditionParameter[i].find("!=")) comparer = "!=";
                else if (conditionParameter[i].find("<=")) comparer = "!=";
                else if (conditionParameter[i].find(">=")) comparer = "!=";
                else if (conditionParameter[i].find("<")) comparer = "!=";
                else if (conditionParameter[i].find(">")) comparer = "!=";
                if (comparer == "")
                {
                    ifInstruction.params.push_back("single");
                    bool isVariable = false;
                    bool isDebugVariable = false;
                    if (isLetter(conditionParameter[i][0])) isVariable = true;
                    if (isVariable) isDebugVariable = !variableVectorContainsName(usedVariables, conditionParameter[i]);
                    if (isVariable)
                    {
                        if (isDebugVariable) ifInstruction.params.push_back("var dbg");
                        else ifInstruction.params.push_back("var tas");
                    }
                    else ifInstruction.params.push_back("plain");
                    ifInstruction.params.push_back(conditionParameter[i]);
                }
                else
                {
                    compareA = subtringFromTo(conditionParameter[i], 0, conditionParameter[i].find(comparer));
                    conditionParameter[i] += "-";
                    compareB = subtringFromTo(conditionParameter[i], conditionParameter[i].find(comparer) + comparer.length(), conditionParameter[i].length() - 1);

                    ifInstruction.params.push_back("pair");
                    bool isVariableA = false;
                    bool isDebugVariableA = false;
                    if (isLetter(compareA[0])) isVariableA = true;
                    if (isVariableA) isDebugVariableA = !variableVectorContainsName(usedVariables, compareA);
                    if (isVariableA)
                    {
                        if (isDebugVariableA) ifInstruction.params.push_back("var dbg");
                        else ifInstruction.params.push_back("var tas");
                    }
                    else ifInstruction.params.push_back("plain");
                    ifInstruction.params.push_back(compareA);

                    ifInstruction.params.push_back(comparer);

                    ifInstruction.params.push_back("pair");
                    bool isVariableB = false;
                    bool isDebugVariableB = false;
                    if (isLetter(compareB[0])) isVariableA = true;
                    if (isVariableB) isDebugVariableB = !variableVectorContainsName(usedVariables, compareB);
                    if (isVariableB)
                    {
                        if (isDebugVariableB) ifInstruction.params.push_back("var dbg");
                        else ifInstruction.params.push_back("var tas");
                    }
                    else ifInstruction.params.push_back("plain");
                    ifInstruction.params.push_back(compareB);
                }

                if (i + 1 < conditionParameter.size()) ifInstruction.params.push_back(isOr ? "||" : "&&");
            }

            while (contentInParanthese.length() > 0) NTLCompileNextInstruction(targetInstructions, functions, currentFunction, usedVariables, contentInParanthese, tmpVariableIncrease);

            ifInstruction.address = (targetInstructions->size() - skipOffsetStart) + 1;
            targetInstructions->insert(targetInstructions->begin() + skipOffsetStart, ifInstruction);
        }
        else if (instructionName == "while")
        {
            int skipOffsetStart = targetInstructions->size();
            int startParantheseIndex = content.find("{");
            int endParantheseIndex = NTLFindParantheseCloseIndex(content, startParantheseIndex + 1);
            std::string contentInParanthese = subtringBetween(content, startParantheseIndex, endParantheseIndex);
            endInstructionIndex = endParantheseIndex;

            bool isOr = parameterPayload.find("||") != std::string::npos;
            bool isAnd = parameterPayload.find("&&") != std::string::npos;

            std::vector<std::string> conditionParameter;
            if (isOr || isAnd) splitStringVector(conditionParameter, parameterPayload, isOr ? "||" : "&&");
            else conditionParameter.push_back(parameterPayload);

            Instruction ifInstruction = Instruction();
            ifInstruction.opcode = OpCode::IF;

            for (int i = 0; i < conditionParameter.size(); i++)
            {
                std::string comparer = "";
                std::string compareA = "";
                std::string compareB = "";
                if (conditionParameter[i].find("==")) comparer = "==";
                else if (conditionParameter[i].find("!=")) comparer = "!=";
                else if (conditionParameter[i].find("<=")) comparer = "!=";
                else if (conditionParameter[i].find(">=")) comparer = "!=";
                else if (conditionParameter[i].find("<")) comparer = "!=";
                else if (conditionParameter[i].find(">")) comparer = "!=";
                if (comparer == "")
                {
                    ifInstruction.params.push_back("single");
                    bool isVariable = false;
                    bool isDebugVariable = false;
                    if (isLetter(conditionParameter[i][0])) isVariable = true;
                    if (isVariable) isDebugVariable = !variableVectorContainsName(usedVariables, conditionParameter[i]);
                    if (isVariable)
                    {
                        if (isDebugVariable) ifInstruction.params.push_back("var dbg");
                        else ifInstruction.params.push_back("var tas");
                    }
                    else ifInstruction.params.push_back("plain");
                    ifInstruction.params.push_back(conditionParameter[i]);
                }
                else
                {
                    compareA = subtringFromTo(conditionParameter[i], 0, conditionParameter[i].find(comparer));
                    conditionParameter[i] += "-";
                    compareB = subtringFromTo(conditionParameter[i], conditionParameter[i].find(comparer) + comparer.length(), conditionParameter[i].length() - 1);

                    ifInstruction.params.push_back("pair");
                    bool isVariableA = false;
                    bool isDebugVariableA = false;
                    if (isLetter(compareA[0])) isVariableA = true;
                    if (isVariableA) isDebugVariableA = !variableVectorContainsName(usedVariables, compareA);
                    if (isVariableA)
                    {
                        if (isDebugVariableA) ifInstruction.params.push_back("var dbg");
                        else ifInstruction.params.push_back("var tas");
                    }
                    else ifInstruction.params.push_back("plain");
                    ifInstruction.params.push_back(compareA);

                    ifInstruction.params.push_back(comparer);

                    ifInstruction.params.push_back("pair");
                    bool isVariableB = false;
                    bool isDebugVariableB = false;
                    if (isLetter(compareB[0])) isVariableA = true;
                    if (isVariableB) isDebugVariableB = !variableVectorContainsName(usedVariables, compareB);
                    if (isVariableB)
                    {
                        if (isDebugVariableB) ifInstruction.params.push_back("var dbg");
                        else ifInstruction.params.push_back("var tas");
                    }
                    else ifInstruction.params.push_back("plain");
                    ifInstruction.params.push_back(compareB);
                }

                if (i + 1 < conditionParameter.size()) ifInstruction.params.push_back(isOr ? "||" : "&&");
            }

            while (contentInParanthese.length() > 0) NTLCompileNextInstruction(targetInstructions, functions, currentFunction, usedVariables, contentInParanthese, tmpVariableIncrease);

            ifInstruction.address = (targetInstructions->size() - skipOffsetStart) + 2;
            targetInstructions->insert(targetInstructions->begin() + skipOffsetStart, ifInstruction);

            Instruction jmpBackInstruction = Instruction();
            jmpBackInstruction.opcode = OpCode::JMPOFF;
            jmpBackInstruction.address = -(ifInstruction.address - 1);
            targetInstructions->push_back(jmpBackInstruction);
        }
        else if (instructionName == "repeat")
        {
            int skipOffsetStart = targetInstructions->size();
            int startParantheseIndex = content.find("{");
            int endParantheseIndex = NTLFindParantheseCloseIndex(content, startParantheseIndex + 1);
            std::string contentInParanthese = subtringBetween(content, startParantheseIndex, endParantheseIndex);
            endInstructionIndex = endParantheseIndex;

            *tmpVariableIncrease++;
            std::string tmpVariRepeat = "repeatertmpvarindicies" + std::to_string(*tmpVariableIncrease);
            targetInstructions->push_back(Create_NTLI_CREATE_VAR(tmpVariRepeat, "int32"));
            targetInstructions->push_back(Create_NTLI_SET_VAR_PLAIN(tmpVariRepeat, "0"));

            Instruction ifInstruction = Instruction();
            ifInstruction.opcode = OpCode::IF;
            ifInstruction.params.push_back("pair");
            ifInstruction.params.push_back("var tas");
            ifInstruction.params.push_back(tmpVariRepeat);
            ifInstruction.params.push_back("<");
            ifInstruction.params.push_back("plain");
            ifInstruction.params.push_back(parameterPayload);

            while (contentInParanthese.length() > 0) NTLCompileNextInstruction(targetInstructions, functions, currentFunction, usedVariables, contentInParanthese, tmpVariableIncrease);

            ifInstruction.address = (targetInstructions->size() - skipOffsetStart) + 2;
            targetInstructions->insert(targetInstructions->begin() + skipOffsetStart, ifInstruction);

            Instruction jmpBackInstruction = Instruction();
            jmpBackInstruction.opcode = OpCode::JMPOFF;
            jmpBackInstruction.address = -(ifInstruction.address - 1);
            targetInstructions->push_back(jmpBackInstruction);

            targetInstructions->push_back(Create_NTLI_REMOVE_VAR(tmpVariRepeat));
        }
        else if (instructionName == "log")
        {
            Instruction logInstruction = Instruction();
            logInstruction.opcode = OpCode::LOG;

            std::vector<std::string> logParameter;
            splitStringVector(logParameter, parameterPayload, ",");
            for (int i = 0; i < logParameter.size(); i++)
            {
                bool isVariable = false;
                bool isDebugVariable = false;
                if (isLetter(logParameter[i][0])) isVariable = true;
                if (isVariable) isDebugVariable = !variableVectorContainsName(usedVariables, logParameter[i]);
                if (isVariable)
                {
                    if (isDebugVariable) logInstruction.params.push_back("var dbg");
                    else logInstruction.params.push_back("var tas");
                }
                else logInstruction.params.push_back("plain");
                logInstruction.params.push_back(logParameter[i]);
            }
        }
        else if (instructionName == "filewriteline")
        {

        }
        else
        {
            bool isTasFunction = false;
            for (int i = 0; i < functions->size(); i++)
            {
                if (functions->data()[i].name == instructionName)
                {
                    isTasFunction = true;
                    break;
                }
            }

            if (isTasFunction)
            {
                for (int i = 0; i < functions->size(); i++)
                {
                    if (functions->data()[i].name == instructionName)
                    {
                        std::vector<std::string> callParameterSplit;
                        splitStringVector(callParameterSplit, parameterPayload, ",");
                        for (int k = 0; k < callParameterSplit.size(); k++)
                        {
                            std::string argName = functions->data()[i].name + "_arg" + std::to_string(k);
                            targetInstructions->push_back(Create_NTLI_CREATE_VAR(functions->data()[i].name + "_arg" + std::to_string(k), subtringFromTo(functions->data()[i].parameter[k], 0, functions->data()[i].parameter[k].find("#"))));
                            if (isLetter(callParameterSplit[k][0]))
                            {
                                if (variableVectorContainsName(usedVariables, callParameterSplit[k]))
                                {
                                    // TAS variable
                                    targetInstructions->push_back(Create_NTLI_SET_VAR_FROM_VAR(argName, callParameterSplit[k]));
                                }
                                else
                                {
                                    // DBG variable
                                    targetInstructions->push_back(Create_NTLI_SET_VAR_FROM_VAR_DBG(argName, callParameterSplit[k]));
                                }
                            }
                            else
                            {
                                // Plain value
                                targetInstructions->push_back(Create_NTLI_SET_VAR_PLAIN(argName, callParameterSplit[k]));
                            }
                        }
                        if (functions->data()[i].returntype != "void")
                        {
                            std::string returnVar = functions->data()[i].name + "_ret";
                            targetInstructions->push_back(Create_NTLI_CREATE_VAR(returnVar, functions->data()[i].returntype));
                            targetInstructions->push_back(Create_NTLI_RETSET(targetInstructions->size() + 3));
                            targetInstructions->push_back(Create_NTLI_JMP(0, "FREP_" + functions->data()[i].name));
                            targetInstructions->push_back(Create_NTLI_REMOVE_VAR(returnVar));
                        }
                        else
                        {
                            targetInstructions->push_back(Create_NTLI_RETSET(targetInstructions->size() + 2));
                            targetInstructions->push_back(Create_NTLI_JMP(0, "FREP_" + functions->data()[i].name));
                        }

                    }
                }

            }
            else
            {
                Instruction logInstruction = Instruction();
                logInstruction.opcode = OpCode::CALLDBG;

                std::vector<std::string> callDbgParameter;
                splitStringVector(callDbgParameter, parameterPayload, ",");
                for (int i = 0; i < callDbgParameter.size(); i++)
                {
                    bool isVariable = false;
                    bool isDebugVariable = false;
                    if (isLetter(callDbgParameter[i][0])) isVariable = true;
                    if (isVariable) isDebugVariable = !variableVectorContainsName(usedVariables, callDbgParameter[i]);
                    if (isVariable)
                    {
                        if (isDebugVariable) logInstruction.params.push_back("var dbg");
                        else logInstruction.params.push_back("var tas");
                    }
                    else logInstruction.params.push_back("plain");
                    logInstruction.params.push_back(callDbgParameter[i]);
                }
            }
        }

        content.replace(0, endInstructionIndex + 1, "");
    }
    else if (nextFunctionalOperator.first == "{")
    {
        // Some kind of loop
        std::string instructionName = subtringFromTo(content, 0, nextFunctionalOperator.second);

        int closedParanthesis = NTLFindParantheseCloseIndex(content, nextFunctionalOperator.second + 1);
        std::string fullInstruction = subtringBetween(content, nextFunctionalOperator.second, closedParanthesis);
        content.replace(0, closedParanthesis + 1, "");

        if (instructionName == "frame")
        {
            Instruction frameInstruction = Instruction();
            frameInstruction.opcode = OpCode::FRAME;

            std::vector<std::string> frameInputs;
            splitStringVector(frameInputs, fullInstruction, ";");
            for (int i = 0; i < frameInputs.size(); i++)
            {
                if (frameInputs[i].length() > 0)
                {
                    std::string inputText = subtringFromTo(frameInputs[i], 0, frameInputs[i].find("("));
                    std::string parameterText = subtringBetween(frameInputs[i], frameInputs[i].find("("), frameInputs[i].find(")"));

                    if (parameterText.length() > 0)
                    {
                        std::vector<std::string> parameterValues;
                        splitStringVector(parameterValues, parameterText, ",");
                        for (int k = 0; k < parameterValues.size(); k++)
                        {
                            bool isVariable = false;
                            bool isDebugVariable = false;
                            if (isLetter(parameterValues[k][0])) isVariable = true;
                            if (isVariable) isDebugVariable = !variableVectorContainsName(usedVariables, parameterValues[k]);
                            if (isVariable)
                            {
                                if (isDebugVariable) inputText += ",var dbg";
                                else inputText += ",var tas";
                            }
                            else inputText += ",plain";
                            inputText += ",";
                            inputText += parameterValues[k];
                        }

                    }

                    frameInstruction.params.push_back(inputText);
                }
            }
        }
        else
        {
            return false;
        }
    }
    else if (nextFunctionalOperator.first == ";")
    {
        if (content.length() >= 6 && content.substr(0, 6) == "return")
        {
            Instruction retInstruction = Instruction();
            retInstruction.opcode = OpCode::RET;
            if (content.substr(0, 7) == "return#")
            {

                std::string returnValue = subtringBetween(content, content.find("#"), content.find(";"));
                std::string retVarName = currentFunction->name + "_ret";
                bool isVariable = false;
                bool isDebugVariable = false;
                if (isLetter(returnValue[0])) isVariable = true;
                if (isVariable) isDebugVariable = !variableVectorContainsName(usedVariables, returnValue);
                if (isVariable)
                {
                    if (isDebugVariable) targetInstructions->push_back(Create_NTLI_SET_VAR_FROM_VAR_DBG(retVarName, returnValue));
                    else targetInstructions->push_back(Create_NTLI_SET_VAR_FROM_VAR(retVarName, returnValue));
                }
                else targetInstructions->push_back(Create_NTLI_SET_VAR_PLAIN(retVarName, returnValue));
            }
            targetInstructions->push_back(retInstruction);
        }
        else
        {

            // Delegation
            std::pair<std::string, int> delegationOperator = NTLFindDelegationOperator(content, 0, "");
            std::string delegationTarget = subtringFromTo(content, 0, delegationOperator.second);
            std::string delegationValue = subtringFromTo(content, delegationOperator.second + delegationOperator.first.length(), nextFunctionalOperator.second);
            std::string delegationOperation = delegationOperator.first;

            std::string typeDescriptor = "";
            bool hasTypeDescriptor = delegationTarget.find("#") != std::string::npos;
            if (hasTypeDescriptor)
            {
                typeDescriptor = subtringFromTo(delegationTarget, 0, delegationTarget.find("#"));
                delegationTarget.replace(0, delegationTarget.find("#") + 1, "");
            }

            bool isValueFunction = delegationValue.find("(") != std::string::npos;
            bool isValueDebugFunction = true;
            bool isValueDebugVariable = true;
            bool isValueVariable = false;
            if (isValueFunction)
            {
                for (int i = 0; i < functions->size(); i++)
                {
                    if (delegationValue.find(functions->data()[i].name + "(") != std::string::npos)
                    {
                        isValueDebugFunction = false;
                        break;
                    }
                }
            }
            else
            {
                if (isLetter(delegationValue[0])) isValueVariable = true;
                if (isValueVariable) isValueDebugVariable = !variableVectorContainsName(usedVariables, delegationTarget);
            }
            bool isTargetDebugVariable = !variableVectorContainsName(usedVariables, delegationTarget);

            if (isTargetDebugVariable)
            {
                // Delegate to DBG Variable
                if (isValueFunction)
                {
                    // Delegate a function result
                    if (isValueDebugFunction)
                    {

                        // TODO

                    }
                    else
                    {
                        // Delegate a TAS function result
                        for (int i = 0; i < functions->size(); i++)
                        {
                            std::string funcName = subtringFromTo(delegationValue, 0, delegationValue.find("("));
                            if (funcName == functions->data()[i].name)
                            {
                                std::string callParameter = subtringBetween(delegationValue, delegationValue.find("("), delegationValue.find(")"));
                                std::vector<std::string> callParameterSplit;
                                splitStringVector(callParameterSplit, callParameter, ",");
                                for (int k = 0; k < callParameterSplit.size(); k++)
                                {
                                    std::string argName = functions->data()[i].name + "_arg" + std::to_string(k);
                                    targetInstructions->push_back(Create_NTLI_CREATE_VAR(functions->data()[i].name + "_arg" + std::to_string(k), subtringFromTo(functions->data()[i].parameter[k], 0, functions->data()[i].parameter[k].find("#"))));
                                    if (isLetter(callParameterSplit[k][0]))
                                    {
                                        if (variableVectorContainsName(usedVariables, callParameterSplit[k]))
                                        {
                                            // TAS variable
                                            targetInstructions->push_back(Create_NTLI_SET_VAR_FROM_VAR(argName, callParameterSplit[k]));
                                        }
                                        else
                                        {
                                            // DBG variable
                                            targetInstructions->push_back(Create_NTLI_SET_VAR_FROM_VAR_DBG(argName, callParameterSplit[k]));
                                        }
                                    }
                                    else
                                    {
                                        // Plain value
                                        targetInstructions->push_back(Create_NTLI_SET_VAR_PLAIN(argName, callParameterSplit[k]));
                                    }
                                }
                                std::string returnVar = functions->data()[i].name + "_ret";
                                targetInstructions->push_back(Create_NTLI_CREATE_VAR(returnVar, functions->data()[i].returntype));
                                targetInstructions->push_back(Create_NTLI_RETSET(targetInstructions->size() + 3));
                                targetInstructions->push_back(Create_NTLI_JMP(0, "FREP_" + functions->data()[i].name));
                                for (int k = 0; k < callParameterSplit.size(); k++)
                                {
                                    std::string argName = functions->data()[i].name + "_arg" + std::to_string(k);
                                    targetInstructions->push_back(Create_NTLI_REMOVE_VAR(argName));
                                }

                                if (delegationOperation == "=") targetInstructions->push_back(Create_NTLI_SET_VAR_DBG_FROM_VAR(delegationTarget, returnVar));
                                if (delegationOperation == "+=") targetInstructions->push_back(Create_NTLI_PLUS_VAR_DBG_FROM_VAR(delegationTarget, returnVar));
                                if (delegationOperation == "-=") targetInstructions->push_back(Create_NTLI_MINUS_VAR_DBG_FROM_VAR(delegationTarget, returnVar));
                                if (delegationOperation == "*=") targetInstructions->push_back(Create_NTLI_MULTI_VAR_DBG_FROM_VAR(delegationTarget, returnVar));
                                if (delegationOperation == "/=") targetInstructions->push_back(Create_NTLI_DIVIDE_VAR_DBG_FROM_VAR(delegationTarget, returnVar));

                                targetInstructions->push_back(Create_NTLI_REMOVE_VAR(returnVar));
                                break;
                            }
                        }
                    }
                }
                else if (isValueVariable)
                {
                    // Delegate a variable value
                    if (isValueDebugVariable)
                    {
                        // Delegate a DBG variable value
                        if (delegationOperation == "=") targetInstructions->push_back(Create_NTLI_SET_VAR_DBG_FROM_VAR_DBG(delegationTarget, delegationValue));
                        if (delegationOperation == "+=") targetInstructions->push_back(Create_NTLI_PLUS_VAR_DBG_FROM_VAR_DBG(delegationTarget, delegationValue));
                        if (delegationOperation == "-=") targetInstructions->push_back(Create_NTLI_MINUS_VAR_DBG_FROM_VAR_DBG(delegationTarget, delegationValue));
                        if (delegationOperation == "*=") targetInstructions->push_back(Create_NTLI_MULTI_VAR_DBG_FROM_VAR_DBG(delegationTarget, delegationValue));
                        if (delegationOperation == "/=") targetInstructions->push_back(Create_NTLI_DIVIDE_VAR_DBG_FROM_VAR_DBG(delegationTarget, delegationValue));
                    }
                    else
                    {
                        // Delegate a TAS variable value
                        if (delegationOperation == "=") targetInstructions->push_back(Create_NTLI_SET_VAR_DBG_FROM_VAR(delegationTarget, delegationValue));
                        if (delegationOperation == "+=") targetInstructions->push_back(Create_NTLI_PLUS_VAR_DBG_FROM_VAR(delegationTarget, delegationValue));
                        if (delegationOperation == "-=") targetInstructions->push_back(Create_NTLI_MINUS_VAR_DBG_FROM_VAR(delegationTarget, delegationValue));
                        if (delegationOperation == "*=") targetInstructions->push_back(Create_NTLI_MULTI_VAR_DBG_FROM_VAR(delegationTarget, delegationValue));
                        if (delegationOperation == "/=") targetInstructions->push_back(Create_NTLI_DIVIDE_VAR_DBG_FROM_VAR(delegationTarget, delegationValue));
                    }
                }
                else
                {
                    // Delegate a plain value
                    if (delegationOperation == "=") targetInstructions->push_back(Create_NTLI_SET_VAR_DBG_PLAIN(delegationTarget, delegationValue));
                    if (delegationOperation == "+=") targetInstructions->push_back(Create_NTLI_PLUS_VAR_DBG_PLAIN(delegationTarget, delegationValue));
                    if (delegationOperation == "-=") targetInstructions->push_back(Create_NTLI_MINUS_VAR_DBG_PLAIN(delegationTarget, delegationValue));
                    if (delegationOperation == "*=") targetInstructions->push_back(Create_NTLI_MULTI_VAR_DBG_PLAIN(delegationTarget, delegationValue));
                    if (delegationOperation == "/=") targetInstructions->push_back(Create_NTLI_DIVIDE_VAR_DBG_PLAIN(delegationTarget, delegationValue));
                }
            }
            else
            {
                // Delegate to TAS Variable
                if (isValueFunction)
                {
                    // Delegate a function result
                    if (isValueDebugFunction)
                    {

                        // TODO

                    }
                    else
                    {
                        // Delegate a TAS function result
                        for (int i = 0; i < functions->size(); i++)
                        {
                            std::string funcName = subtringFromTo(delegationValue, 0, delegationValue.find("("));
                            if (funcName == functions->data()[i].name)
                            {
                                std::string callParameter = subtringBetween(delegationValue, delegationValue.find("("), delegationValue.find(")"));
                                std::vector<std::string> callParameterSplit;
                                splitStringVector(callParameterSplit, callParameter, ",");
                                for (int k = 0; k < callParameterSplit.size(); k++)
                                {
                                    std::string argName = functions->data()[i].uuid + "_arg" + std::to_string(k);
                                    targetInstructions->push_back(Create_NTLI_CREATE_VAR(functions->data()[i].uuid + "_arg" + std::to_string(k), subtringFromTo(functions->data()[i].parameter[k], 0, functions->data()[i].parameter[k].find("#"))));
                                    if (isLetter(callParameterSplit[k][0]))
                                    {
                                        if (variableVectorContainsName(usedVariables, callParameterSplit[k]))
                                        {
                                            // TAS variable
                                            targetInstructions->push_back(Create_NTLI_SET_VAR_FROM_VAR(argName, callParameterSplit[k]));
                                        }
                                        else
                                        {
                                            // DBG variable
                                            targetInstructions->push_back(Create_NTLI_SET_VAR_FROM_VAR_DBG(argName, callParameterSplit[k]));
                                        }
                                    }
                                    else
                                    {
                                        // Plain value
                                        targetInstructions->push_back(Create_NTLI_SET_VAR_PLAIN(argName, callParameterSplit[k]));
                                    }
                                }
                                std::string returnVar = functions->data()[i].uuid + "_ret";
                                targetInstructions->push_back(Create_NTLI_CREATE_VAR(returnVar, functions->data()[i].returntype));
                                targetInstructions->push_back(Create_NTLI_RETSET(targetInstructions->size() + 3));
                                targetInstructions->push_back(Create_NTLI_JMP(0, "FREP_" + functions->data()[i].uuid));
                                for (int k = 0; k < callParameterSplit.size(); k++)
                                {
                                    std::string argName = functions->data()[i].uuid + "_arg" + std::to_string(k);
                                    targetInstructions->push_back(Create_NTLI_REMOVE_VAR(argName));
                                }

                                if (delegationOperation == "=")
                                {
                                    if (hasTypeDescriptor)
                                    {
                                        targetInstructions->push_back(Create_NTLI_CREATE_VAR(delegationTarget, typeDescriptor));
                                        Variable newVariable = Variable();
                                        newVariable.name = delegationTarget;
                                        newVariable.type = typeDescriptor;
                                        usedVariables->push_back(newVariable);
                                    }
                                    targetInstructions->push_back(Create_NTLI_SET_VAR_FROM_VAR(delegationTarget, returnVar));
                                }
                                if (delegationOperation == "+=") targetInstructions->push_back(Create_NTLI_PLUS_VAR_FROM_VAR(delegationTarget, returnVar));
                                if (delegationOperation == "-=") targetInstructions->push_back(Create_NTLI_MINUS_VAR_FROM_VAR(delegationTarget, returnVar));
                                if (delegationOperation == "*=") targetInstructions->push_back(Create_NTLI_MULTI_VAR_FROM_VAR(delegationTarget, returnVar));
                                if (delegationOperation == "/=") targetInstructions->push_back(Create_NTLI_DIVIDE_VAR_FROM_VAR(delegationTarget, returnVar));

                                targetInstructions->push_back(Create_NTLI_REMOVE_VAR(returnVar));
                                break;
                            }
                        }
                    }
                }
                else if (isValueVariable)
                {
                    // Delegate a variable value
                    if (isValueDebugVariable)
                    {
                        // Delegate a DBG variable value
                        if (delegationOperation == "=")
                        {
                            if (hasTypeDescriptor)
                            {
                                targetInstructions->push_back(Create_NTLI_CREATE_VAR(delegationTarget, typeDescriptor));
                                Variable newVariable = Variable();
                                newVariable.name = delegationTarget;
                                newVariable.type = typeDescriptor;
                                usedVariables->push_back(newVariable);
                            }
                            targetInstructions->push_back(Create_NTLI_SET_VAR_FROM_VAR_DBG(delegationTarget, delegationValue));
                        }
                        if (delegationOperation == "+=") targetInstructions->push_back(Create_NTLI_PLUS_VAR_FROM_VAR_DBG(delegationTarget, delegationValue));
                        if (delegationOperation == "-=") targetInstructions->push_back(Create_NTLI_MINUS_VAR_FROM_VAR_DBG(delegationTarget, delegationValue));
                        if (delegationOperation == "*=") targetInstructions->push_back(Create_NTLI_MULTI_VAR_FROM_VAR_DBG(delegationTarget, delegationValue));
                        if (delegationOperation == "/=") targetInstructions->push_back(Create_NTLI_DIVIDE_VAR_FROM_VAR_DBG(delegationTarget, delegationValue));
                    }
                    else
                    {
                        // Delegate a TAS variable value
                        if (delegationOperation == "=")
                        {
                            if (hasTypeDescriptor)
                            {
                                targetInstructions->push_back(Create_NTLI_CREATE_VAR(delegationTarget, typeDescriptor));
                                Variable newVariable = Variable();
                                newVariable.name = delegationTarget;
                                newVariable.type = typeDescriptor;
                                usedVariables->push_back(newVariable);
                            }
                            targetInstructions->push_back(Create_NTLI_SET_VAR_FROM_VAR(delegationTarget, delegationValue));
                        }
                        if (delegationOperation == "+=") targetInstructions->push_back(Create_NTLI_PLUS_VAR_FROM_VAR(delegationTarget, delegationValue));
                        if (delegationOperation == "-=") targetInstructions->push_back(Create_NTLI_MINUS_VAR_FROM_VAR(delegationTarget, delegationValue));
                        if (delegationOperation == "*=") targetInstructions->push_back(Create_NTLI_MULTI_VAR_FROM_VAR(delegationTarget, delegationValue));
                        if (delegationOperation == "/=") targetInstructions->push_back(Create_NTLI_DIVIDE_VAR_FROM_VAR(delegationTarget, delegationValue));
                    }
                }
                else
                {
                    // Delegate a plain value
                    if (delegationOperation == "=")
                    {
                        if (hasTypeDescriptor)
                        {
                            targetInstructions->push_back(Create_NTLI_CREATE_VAR(delegationTarget, typeDescriptor));
                            Variable newVariable = Variable();
                            newVariable.name = delegationTarget;
                            newVariable.type = typeDescriptor;
                            usedVariables->push_back(newVariable);
                        }
                        targetInstructions->push_back(Create_NTLI_SET_VAR_PLAIN(delegationTarget, delegationValue));
                    }
                    if (delegationOperation == "+=") targetInstructions->push_back(Create_NTLI_PLUS_VAR_PLAIN(delegationTarget, delegationValue));
                    if (delegationOperation == "-=") targetInstructions->push_back(Create_NTLI_MINUS_VAR_PLAIN(delegationTarget, delegationValue));
                    if (delegationOperation == "*=") targetInstructions->push_back(Create_NTLI_MULTI_VAR_PLAIN(delegationTarget, delegationValue));
                    if (delegationOperation == "/=") targetInstructions->push_back(Create_NTLI_DIVIDE_VAR_PLAIN(delegationTarget, delegationValue));
                }
            }
        }

        content.replace(0, nextFunctionalOperator.second + 1, "");
    }
    else
    {
        return false;
    }

    return true;
}

bool NTLCompileFunctions(NTLScript* script, std::vector<FunctionSignature>* functions) {
    std::vector<Variable> usedVariables;
    int tmpVariableIncrease = 0;
    int entryPoint = 0;
    for (int i = 0; i < functions->size(); i++)
    {
        FunctionSignature* targetFunction = &functions->data()[i];
        targetFunction->address = script->instructions.size();

        if (targetFunction->name == "main") entryPoint = targetFunction->address;

        for (int k = 0; k < targetFunction->parameter.size(); k++)
        {
            std::string targetPrameter = targetFunction->parameter[k];
            targetPrameter.replace(0, targetPrameter.find("#") + 1, "");
            int indexFinder = 0;
            while (true)
            {
                int foundIndex = targetFunction->content.find(targetPrameter, indexFinder);
                if (indexFinder == std::string::npos) break;
                if (!isDigit(targetFunction->content[foundIndex - 1]) && !isLetter(targetFunction->content[foundIndex - 1]))
                {
                    if (!isDigit(targetFunction->content[foundIndex + targetPrameter.length()]) && !isLetter(targetFunction->content[foundIndex + targetPrameter.length()]))
                    {
                        targetFunction->content.replace(foundIndex, targetPrameter.length(), targetFunction->name + "_arg" + std::to_string(k));
                    }
                }

                indexFinder = foundIndex + targetPrameter.length();
            }
        }

        while (true)
        {
            NTLCompileNextInstruction(&script->instructions, functions, targetFunction, &usedVariables, targetFunction->content, &tmpVariableIncrease);
            if (targetFunction->content.length() == 0) break;
        }

    }

    for (int i = 0; i < script->instructions.size(); i++)
    {
        if (script->instructions[i].opcode == OpCode::JMP)
        {
            if (script->instructions[i].params.size() > 0 && script->instructions[i].params[0].find("FREP_"))
            {
                script->instructions[i].params[0].replace(0, 5, "");
                std::string targetFunctionName = script->instructions[i].params[0];
                script->instructions[i].params.clear();
                for (int k = 0; k < functions->size(); k++)
                {
                    if (functions->data()[k].name == targetFunctionName)
                    {
                        script->instructions[i].address = functions->data()[k].address;
                        break;
                    }
                }
            }
        }
    }

    script->entrypoint = entryPoint;

    return true;
}

NTLScript NTLCompileScript(std::string directory, std::string filename)
{
    std::string rawCode = "";
    std::vector<std::string> ignoreImportsList;
    NTLReadAllCodeFiles(directory, filename, rawCode, ignoreImportsList);

    std::vector<FunctionSignature> allFunctions;
    NTLReadAllFunctions(rawCode, &allFunctions);

    NTLScript compiledScript = NTLScript();
    NTLCompileFunctions(&compiledScript, &allFunctions);

    return compiledScript;
}





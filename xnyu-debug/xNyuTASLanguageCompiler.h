#pragma once

// --- Variables ---



// --- Functions ---
std::string NTLGenerateUUID();
std::pair<std::string, int> NTLFindNextType(std::string& content, int startIndex, std::string extra = "");
std::pair<std::string, int> NTLFindNextFunctionalOperator(std::string& content, int startIndex, std::string extra = "");
std::pair<std::string, int> NTLFindDelegationOperator(std::string& content, int startIndex, std::string extra = "");
std::pair<std::string, std::string> NTLSplitTypeIdentifier(std::string& payload);
int NTLFindParantheseCloseIndex(std::string& target, int startIndex);
bool NTLReadAllFunctions(std::string& content, std::vector<FunctionSignature>* functions);
std::vector<std::string> NTLFindImports(std::string& str, std::vector<std::string>& ignoreList);
std::string NTLResolvePathTraversing(std::string base, std::string target);
std::string NTLReadFileFormatted(std::string filePath);
void NTLReadAllCodeFiles(std::string directory, std::string filename, std::string& code, std::vector<std::string>& ignoreList);
bool NTLCompileNextInstruction(std::vector<Instruction>* targetInstructions, std::vector<FunctionSignature>* functions, FunctionSignature* currentFunction, std::vector<Variable>* usedVariables, std::string& content, int* tmpVariableIncrease);
bool NTLCompileFunctions(NTLScript* script, std::vector<FunctionSignature>* functions);
NTLScript NTLCompileScript(std::string directory, std::string filename);



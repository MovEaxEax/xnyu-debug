#pragma once



// --- Structs ---
struct Instruction {
    std::string type;
    std::vector<std::string> parameter;
};

struct Function {
    std::string name;
    std::vector<Instruction> instructions;
    int id;
};

struct Stack {
    int id;
    int line;
};



// --- Variables ---
extern std::string TASScript;
extern bool TASPlayScript;
extern bool TASPlayScriptDone;
extern bool TASPlayScriptInit;
extern bool TASPlayScriptUninit;
extern bool TASPlayScriptThenRecord;
extern bool TASPlayStartedSignal;
extern bool TASPlaySkipFirstSync;
extern std::ifstream TASPlayScriptStream;
extern bool TASRecordScript;
extern bool TASRecordScriptDone;
extern bool TASRecordScriptInit;
extern bool TASRecordScriptUninit;
extern bool TASRecordFrameByFrame;
extern bool TASRecordStartedSignal;
extern bool TASRecordSkipFirstSync;
extern std::string TASRecordFrameReceived;
extern std::ofstream TASRecordScriptStream;
extern GameInput TASInputCurrent;
extern GameInput TASInputLast;
extern std::string TASLastError;
extern GameInputLayout TASInputLayout;
extern std::vector<Function> TASScriptFunctions;
extern std::vector<Variable> TASScriptVariables;
extern std::vector<Stack> TASStack;
extern Stack TASCurrentStack;
extern int TASFunctionId;
extern int TASRepeatNamer;
extern long long TASFramesPassed;



// --- Functions ---
std::string ReadScript(std::string file_path);
int ParseInstructions(std::vector<Instruction>& functions, std::string content);
int ParseFunction(std::vector<Function>& functions, std::string script);
void AddFunctionLifecycles(std::vector<Function>& functions, std::vector<Stack>& stack, Stack* currentStack);
void AddFunctionReturn(std::vector<Function>& functions);
std::string GameInputToFrame(GameInput* SRC);
void GameInputSetFrame(GameInput* SRC, std::string key, std::vector<std::string> parameter);
bool FindDebugFunction(std::string parentName, std::string childName, DebugFunction* debugFunction);
bool FindDebugAddress(std::string parentName, std::string childName, DebugAddress* debugAddress);
bool VariableCondition(std::string condition);
int PlayInstruction(Instruction instruction);
bool __stdcall PlayScriptRoutine();
bool __stdcall RecordScriptRoutine();
void __stdcall TASRoutine();



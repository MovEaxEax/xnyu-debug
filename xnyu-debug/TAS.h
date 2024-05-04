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

extern bool TASPlayingActive;
extern bool TASPlayingInit;
extern bool TASPlayingUnInit;

extern bool TASRecordingActive;
extern bool TASRecordingInit;
extern bool TASRecordingUnInit;

extern std::string TASRecordFrameReceived;
extern std::ofstream TASRecordScriptStream;

extern GameInputLayout TASInputLayout;
extern GameInput TASInputCurrent;
extern GameInput TASInputLast;
extern long long TASFramesPassed;

extern HANDLE PythonInterpreterThread = nullptr;
extern HANDLE PythonInterpreterThreadMutex = CreateMutex(NULL, FALSE, NULL);
extern FILE* PythonInterpreterScript = nullptr;
extern bool PythonInterpreterThreadAlive = true;
extern std::string PythonInterpreterLineToExecute;



// --- Functions ---
bool __stdcall PlayScriptRoutine();
bool __stdcall RecordScriptRoutine();
void __stdcall TASRoutine();



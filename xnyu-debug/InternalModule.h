#pragma once



// --- Typedefs ---
typedef void(__stdcall* GetInternalVariableT)(InternalVariable& variable);
typedef void(__stdcall* SetInternalVariableT)(InternalVariable& variable);
typedef void(__stdcall* CallInternalFunctionT)(InternalFunction& function);



// --- Structs ---
struct InternalModuleConfig
{
	bool isModuleAvailable = false;
	bool isInternalFunctionsAvailable = false;
	bool isInternalVariablesAvailable = false;
	bool isInternalSavefileEditorAvailable = false;
	bool isInternalEditorModeAvailable = false;
	bool isInternalSupervisionAvailable = false;
	std::string moduleName = "";
	std::string moduleVersion = "";
	std::string moduleAuthor = "";
};

struct InternalFunction
{
	std::string name = "";
	std::string nameParent = "";
	std::string nameChild = "";
	std::string description = "";
	Variable returnValue = nullptr;
	std::vector<Variable> parameter;
	bool rapid = false;
	bool cooldown = false;
};

enum INTERNAL_FUNCTION_HOTKEY_IDENTIFIER : int
{
	A = 0,
	B = 1,
	C = 2,
	D = 3,
	E = 4,
	F = 5,
	G = 6,
	H = 7,
	I = 8,
	J = 9,
	K = 10,
	L = 11,
	M = 12,
	N = 13,
	O = 14,
	P = 15,
	Q = 16,
	R = 17,
	S = 18,
	T = 19,
	U = 20,
	V = 21,
	W = 22,
	X = 23,
	Y = 24,
	Z = 25,
	D0 = 26,
	D1 = 27,
	D2 = 28,
	D3 = 29,
	D4 = 30,
	D5 = 31,
	D6 = 32,
	D7 = 33,
	D8 = 34,
	D9 = 35,
	NUM1 = 36,
	NUM2 = 37,
	NUM3 = 38,
	NUM4 = 39,
	NUM5 = 40,
	NUM6 = 41,
	NUM7 = 42,
	NUM8 = 43,
	NUM9 = 44,
	F1 = 45,
	F2 = 46,
	F3 = 47,
	F4 = 48,
	F5 = 49,
	F6 = 50,
	F7 = 51,
	F8 = 52,
	F9 = 53,
	F10 = 54,
	F11 = 55,
	F12 = 56,
	NONEKEY = 57
};

struct InternalFunctionHotkey
{
	INTERNAL_FUNCTION_HOTKEY_IDENTIFIER hotkey = INTERNAL_FUNCTION_HOTKEY_IDENTIFIER::NONEKEY;
	InternalFunction* internalFunction = nullptr;
	bool pressed = false;
};

struct InternalFunctionSettings
{
	std::vector<InternalFunction> functions;
	std::vector<InternalFunctionHotkey> hotkeys;
};

struct InternalVariable
{
	std::string name = "";
	std::string nameParent = "";
	std::string nameChild = "";
	std::string description = "";
	Variable variable = nullptr;
	bool hex = false;
};

struct InternalVariableSettings
{
	int refresh = 200;
	ALIGN align = ALIGN::TOP_LEFT;
	std::vector<InternalVariable> variables;
};

struct InternalSavefileStaticField
{
	std::vector<FormElement> fields;
};

struct InternalSavefileDynamicField
{
	std::string pattern = "";
	std::vector<InternalSavefileStaticField> fields;
};

struct InternalSavefileGroup
{
	std::vector<InternalSavefileStaticField> statics;
	std::vector<InternalSavefileDynamicField> dynamics;
};

struct InternalSavefile
{
	std::string name = "";
	std::vector<InternalSavefileGroup> groups;
};

struct InternalEditorModeContextMenuField
{
	std::string name = "";
	std::string nameParent = "";
	std::string nameChild = "";
	std::string label = "";
	std::string dataString = "";
	int dataInteger = 0;
	bool disabled = false;
};

struct InternalEditorModeSettings
{
	std::vector<InternalEditorModeContextMenuField> contextmenu;
	std::vector<FormElement> toolbar;
};

struct InternalSupervisionSettings
{
	std::vector<FormElement> configuration;
};



// --- Variables ---
EXTERN_DLL_EXPORT extern InternalModuleConfig internalModuleConfig;
EXTERN_DLL_EXPORT extern InternalFunctionSettings internalFunctions;
EXTERN_DLL_EXPORT extern InternalVariableSettings internalVariables;
EXTERN_DLL_EXPORT extern std::vector<InternalSavefile> internalSavefiles;
EXTERN_DLL_EXPORT extern InternalEditorModeSettings internalEditorModeSettings;
EXTERN_DLL_EXPORT extern InternalSupervisionSettings internalSupervisionSetings;

extern GetInternalVariableT pGetInternalVariable = nullptr;
extern SetInternalVariableT pSetInternalVariable = nullptr;
extern CallInternalFunctionT pCallInternalFunction = nullptr;



// --- Functions ---
InternalVariable* _stdcall FindInternalVariableByName(std::string& name);
void _stdcall GetInternalVariable(std::string& name, Variable& output);
void _stdcall SetInternalVariable(std::string& name, Variable& input);

InternalFunction* _stdcall FindInternalFunctionByName(std::string& name);
void _stdcall CallInternalFunction(std::string& name, Variable& returnValue, std::vector<VariableType>& parameter);

void _stdcall GetSavefilesAvailable(std::vector<std::string> files);
void _stdcall CreateNewSavefile();
void _stdcall DeleteSavefile(std::string name);
void _stdcall ReadSavefile(InternalSavefile& internalSavefile);
void _stdcall WriteSavefile(InternalSavefile& internalSavefile);

void _stdcall UpdateEditorModeContextMenu(InternalEditorModeContextMenu& menu);
void _stdcall InvokeEditorModeContextMenuFunction(InternalEditorModeContextMenuField& field);



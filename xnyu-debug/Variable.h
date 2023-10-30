#pragma once

// --- Structs ---
struct Variable {
    std::string name;
    std::string type;
    std::string value;
    bool forceHex;
};



// --- Functions ---
EXTERN_DLL_EXPORT bool __cdecl CheckVariableType(std::string type, std::string value);
EXTERN_DLL_EXPORT std::string __cdecl GetValueType(std::string value);

EXTERN_DLL_EXPORT void __cdecl SetVariable(Variable* variable, std::string value);

EXTERN_DLL_EXPORT std::string __cdecl GetVariableString(Variable* variable);
EXTERN_DLL_EXPORT bool __cdecl GetVariableBool(Variable* variable);
EXTERN_DLL_EXPORT BYTE __cdecl GetVariableByte(Variable* variable);
EXTERN_DLL_EXPORT int __cdecl GetVariableInt32(Variable* variable);
EXTERN_DLL_EXPORT long long __cdecl GetVariableInt64(Variable* variable);
EXTERN_DLL_EXPORT float __cdecl GetVariableFloat(Variable* variable);
EXTERN_DLL_EXPORT double __cdecl GetVariableDouble(Variable* variable);

EXTERN_DLL_EXPORT std::string __cdecl GetVariableString(std::string value);
EXTERN_DLL_EXPORT bool __cdecl GetVariableBool(std::string value);
EXTERN_DLL_EXPORT BYTE __cdecl GetVariableByte(std::string value);
EXTERN_DLL_EXPORT int __cdecl GetVariableInt32(std::string value);
EXTERN_DLL_EXPORT long long __cdecl GetVariableInt64(std::string value);
EXTERN_DLL_EXPORT float __cdecl GetVariableFloat(std::string value);
EXTERN_DLL_EXPORT double __cdecl GetVariableDouble(std::string value);

EXTERN_DLL_EXPORT void __cdecl VariableAdd(Variable* variable, std::string value);
EXTERN_DLL_EXPORT void __cdecl VariableAdd(Variable* variableDST, Variable* variableSRC);
EXTERN_DLL_EXPORT void __cdecl VariableSubtract(Variable* variable, std::string value);
EXTERN_DLL_EXPORT void __cdecl VariableSubtract(Variable* variableDST, Variable* variableSRC);
EXTERN_DLL_EXPORT void __cdecl VariableMultiply(Variable* variable, std::string value);
EXTERN_DLL_EXPORT void __cdecl VariableMultiply(Variable* variableDST, Variable* variableSRC);
EXTERN_DLL_EXPORT void __cdecl VariableDivide(Variable* variable, std::string value);
EXTERN_DLL_EXPORT void __cdecl VariableDivide(Variable* variableDST, Variable* variableSRC);



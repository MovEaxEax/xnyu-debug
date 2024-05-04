#pragma once

// --- Functions ---

// POINTER
void _DbgReadPointerBD();
void _DbgReadPointerB();
EXTERN_DLL_EXPORT bool __stdcall MemoryReadPointerT1(BasePointer address, void** dst, bool safe);
EXTERN_DLL_EXPORT void* __stdcall MemoryReadPointerT2(BasePointer address, bool safe);
bool __stdcall MemoryReadPointer(BasePointer address, void** dst, bool safe = true);
void* __stdcall MemoryReadPointer(BasePointer address, bool safe = true);

// FLOAT
void _DbgReadFloatBD();
void _DbgReadFloatAD();
void _DbgReadFloatB();
void _DbgReadFloatA();
EXTERN_DLL_EXPORT bool __stdcall MemoryReadFloatT3(BasePointer address, void* dst, bool safe);
EXTERN_DLL_EXPORT bool __stdcall MemoryReadFloatT4(void* address, void* dst);
EXTERN_DLL_EXPORT float __stdcall MemoryReadFloatT5(BasePointer address, bool safe);
EXTERN_DLL_EXPORT float __stdcall MemoryReadFloatT6(void* address);
bool __stdcall MemoryReadFloat(BasePointer address, void* dst, bool safe = true);
bool __stdcall MemoryReadFloat(void* address, void* dst);
float __stdcall MemoryReadFloat(BasePointer address, bool safe = true);
float __stdcall MemoryReadFloat(void* address);

// DOUBLE
void _DbgReadDoubleBD();
void _DbgReadDoubleAD();
void _DbgReadDoubleB();
void _DbgReadDoubleA();
EXTERN_DLL_EXPORT bool __stdcall MemoryReadDoubleT7(BasePointer address, void* dst, bool safe);
EXTERN_DLL_EXPORT bool __stdcall MemoryReadDoubleT8(void* address, void* dst);
EXTERN_DLL_EXPORT double __stdcall MemoryReadDoubleT9(BasePointer address, bool safe);
EXTERN_DLL_EXPORT double __stdcall MemoryReadDoubleT10(void* address);
bool __stdcall MemoryReadDouble(BasePointer address, void* dst, bool safe = true);
bool __stdcall MemoryReadDouble(void* address, void* dst);
double __stdcall MemoryReadDouble(BasePointer address, bool safe = true);
double __stdcall MemoryReadDouble(void* address);

// INT32
void _DbgReadInt32BD();
void _DbgReadInt32AD();
void _DbgReadInt32B();
void _DbgReadInt32A();
EXTERN_DLL_EXPORT bool __stdcall MemoryReadInt32T11(BasePointer address, void* dst, bool safe);
EXTERN_DLL_EXPORT bool __stdcall MemoryReadInt32T12(void* address, void* dst);
EXTERN_DLL_EXPORT int __stdcall MemoryReadInt32T13(BasePointer address, bool safe);
EXTERN_DLL_EXPORT int __stdcall MemoryReadInt32T14(void* address);
bool __stdcall MemoryReadInt32(BasePointer address, void* dst, bool safe = true);
bool __stdcall MemoryReadInt32(void* address, void* dst);
int __stdcall MemoryReadInt32(BasePointer address, bool safe = true);
int __stdcall MemoryReadInt32(void* address);

// INT64
void _DbgReadInt64BD();
void _DbgReadInt64AD();
void _DbgReadInt64B();
void _DbgReadInt64A();
EXTERN_DLL_EXPORT bool __stdcall MemoryReadInt64T15(BasePointer address, void* dst, bool safe);
EXTERN_DLL_EXPORT bool __stdcall MemoryReadInt64T16(void* address, void* dst);
EXTERN_DLL_EXPORT long long __stdcall MemoryReadInt64T17(BasePointer address, bool safe);
EXTERN_DLL_EXPORT long long __stdcall MemoryReadInt64T18(void* address);
bool __stdcall MemoryReadInt64(BasePointer address, void* dst, bool safe = true);
bool __stdcall MemoryReadInt64(void* address, void* dst);
long long __stdcall MemoryReadInt64(BasePointer address, bool safe = true);
long long __stdcall MemoryReadInt64(void* address);

// STRING
void _DbgReadStringBD();
void _DbgReadStringAD();
void _DbgReadStringB();
void _DbgReadStringA();
EXTERN_DLL_EXPORT bool __stdcall MemoryReadStringT19(BasePointer address, void* dst, bool safe);
EXTERN_DLL_EXPORT bool __stdcall MemoryReadStringT20(void* address, void* dst);
EXTERN_DLL_EXPORT std::string __stdcall MemoryReadStringT21(BasePointer address, bool safe);
EXTERN_DLL_EXPORT std::string __stdcall MemoryReadStringT22(void* address);
bool __stdcall MemoryReadString(BasePointer address, void* dst, bool safe = true);
bool __stdcall MemoryReadString(void* address, void* dst);
std::string __stdcall MemoryReadString(BasePointer address, bool safe = true);
std::string __stdcall MemoryReadString(void* address);

// BOOL
void _DbgReadBoolBD();
void _DbgReadBoolAD();
void _DbgReadBoolB();
void _DbgReadBoolA();
EXTERN_DLL_EXPORT bool __stdcall MemoryReadBoolT23(BasePointer address, void* dst, bool safe);
EXTERN_DLL_EXPORT bool __stdcall MemoryReadBoolT24(void* address, void* dst);
EXTERN_DLL_EXPORT bool __stdcall MemoryReadBoolT25(BasePointer address, bool safe);
EXTERN_DLL_EXPORT bool __stdcall MemoryReadBoolT26(void* address);
bool __stdcall MemoryReadBool(BasePointer address, void* dst, bool safe = true);
bool __stdcall MemoryReadBool(void* address, void* dst);
bool __stdcall MemoryReadBool(BasePointer address, bool safe = true);
bool __stdcall MemoryReadBool(void* address);

// BYTE
void _DbgReadByteBD();
void _DbgReadByteAD();
void _DbgReadByteB();
void _DbgReadByteA();
EXTERN_DLL_EXPORT bool __stdcall MemoryReadByteT27(BasePointer address, void* dst, bool safe);
EXTERN_DLL_EXPORT bool __stdcall MemoryReadByteT28(void* address, void* dst);
EXTERN_DLL_EXPORT BYTE __stdcall MemoryReadByteT29(BasePointer address, bool safe);
EXTERN_DLL_EXPORT BYTE __stdcall MemoryReadByteT30(void* address);
bool __stdcall MemoryReadByte(BasePointer address, void* dst, bool safe = true);
bool __stdcall MemoryReadByte(void* address, void* dst);
BYTE __stdcall MemoryReadByte(BasePointer address, bool safe = true);
BYTE __stdcall MemoryReadByte(void* address);

// BYTES
void _DbgReadBytesBD();
void _DbgReadBytesAD();
void _DbgReadBytesB();
void _DbgReadBytesA();
EXTERN_DLL_EXPORT bool __stdcall MemoryReadBytesT31(BasePointer address, void* dst, int amount, bool safe);
EXTERN_DLL_EXPORT bool __stdcall MemoryReadBytesT32(void* address, void* dst, int amount);
EXTERN_DLL_EXPORT BYTE* __stdcall MemoryReadBytesT33(BasePointer address, int amount, bool safe);
EXTERN_DLL_EXPORT BYTE* __stdcall MemoryReadBytesT34(void* address, int amount);
bool __stdcall MemoryReadBytes(BasePointer address, void* dst, int amount, bool safe = true);
bool __stdcall MemoryReadBytes(void* address, void* dst, int amount);
BYTE* __stdcall MemoryReadBytes(BasePointer address, int amount, bool safe = true);
BYTE* __stdcall MemoryReadBytes(void* address, int amount);

// VARIABLE
EXTERN_DLL_EXPORT void __stdcall MemoryReadVariableT35(BasePointer address, Variable& src, bool safe);
EXTERN_DLL_EXPORT void __stdcall MemoryReadVariableT36(void* address, Variable& src);
void __stdcall MemoryReadVariable(BasePointer address, Variable& src, bool safe = true);
void __stdcall MemoryReadVariable(void* address, Variable& src);



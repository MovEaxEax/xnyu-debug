#pragma once

// --- Functions ---

// POINTER
void _DbgReadPointerBD();
void _DbgReadPointerB();
EXTERN_DLL_EXPORT bool __cdecl DbgReadPointer(BasePointer address, void** dst, bool safe = true);
EXTERN_DLL_EXPORT void* __cdecl DbgReadPointer(BasePointer address, bool safe = true);

// FLOAT
void _DbgReadFloatBD();
void _DbgReadFloatAD();
void _DbgReadFloatB();
void _DbgReadFloatA();
EXTERN_DLL_EXPORT bool __cdecl DbgReadFloat(BasePointer address, void* dst, bool safe = true);
EXTERN_DLL_EXPORT bool __cdecl DbgReadFloat(void* address, void* dst);
EXTERN_DLL_EXPORT float __cdecl DbgReadFloat(BasePointer address, bool safe = true);
EXTERN_DLL_EXPORT float __cdecl DbgReadFloat(void* address);

// DOUBLE
void _DbgReadDoubleBD();
void _DbgReadDoubleAD();
void _DbgReadDoubleB();
void _DbgReadDoubleA();
EXTERN_DLL_EXPORT bool __cdecl DbgReadDouble(BasePointer address, void* dst, bool safe = true);
EXTERN_DLL_EXPORT bool __cdecl DbgReadDouble(void* address, void* dst);
EXTERN_DLL_EXPORT double __cdecl DbgReadDouble(BasePointer address, bool safe = true);
EXTERN_DLL_EXPORT double __cdecl DbgReadDouble(void* address);

// INT32
void _DbgReadInt32BD();
void _DbgReadInt32AD();
void _DbgReadInt32B();
void _DbgReadInt32A();
EXTERN_DLL_EXPORT bool __cdecl DbgReadInt32(BasePointer address, void* dst, bool safe = true);
EXTERN_DLL_EXPORT bool __cdecl DbgReadInt32(void* address, void* dst);
EXTERN_DLL_EXPORT int __cdecl DbgReadInt32(BasePointer address, bool safe = true);
EXTERN_DLL_EXPORT int __cdecl DbgReadInt32(void* address);

// INT64
void _DbgReadInt64BD();
void _DbgReadInt64AD();
void _DbgReadInt64B();
void _DbgReadInt64A();
EXTERN_DLL_EXPORT bool __cdecl DbgReadInt64(BasePointer address, void* dst, bool safe = true);
EXTERN_DLL_EXPORT bool __cdecl DbgReadInt64(void* address, void* dst);
EXTERN_DLL_EXPORT long long __cdecl DbgReadInt64(BasePointer address, bool safe = true);
EXTERN_DLL_EXPORT long long __cdecl DbgReadInt64(void* address);

// STRING
void _DbgReadStringBD();
void _DbgReadStringAD();
void _DbgReadStringB();
void _DbgReadStringA();
EXTERN_DLL_EXPORT bool __cdecl DbgReadString(BasePointer address, void* dst, bool safe = true);
EXTERN_DLL_EXPORT bool __cdecl DbgReadString(void* address, void* dst);
EXTERN_DLL_EXPORT std::string __cdecl DbgReadString(BasePointer address, bool safe = true);
EXTERN_DLL_EXPORT std::string __cdecl DbgReadString(void* address);

// BOOL
void _DbgReadBoolBD();
void _DbgReadBoolAD();
void _DbgReadBoolB();
void _DbgReadBoolA();
EXTERN_DLL_EXPORT bool __cdecl DbgReadBool(BasePointer address, void* dst, bool safe = true);
EXTERN_DLL_EXPORT bool __cdecl DbgReadBool(void* address, void* dst);
EXTERN_DLL_EXPORT bool __cdecl DbgReadBool(BasePointer address, bool safe = true);
EXTERN_DLL_EXPORT bool __cdecl DbgReadBool(void* address);

// BYTE
void _DbgReadByteBD();
void _DbgReadByteAD();
void _DbgReadByteB();
void _DbgReadByteA();
EXTERN_DLL_EXPORT bool __cdecl DbgReadByte(BasePointer address, void* dst, bool safe = true);
EXTERN_DLL_EXPORT bool __cdecl DbgReadByte(void* address, void* dst);
EXTERN_DLL_EXPORT BYTE __cdecl DbgReadByte(BasePointer address, bool safe = true);
EXTERN_DLL_EXPORT BYTE __cdecl DbgReadByte(void* address);

// BYTES
void _DbgReadBytesBD();
void _DbgReadBytesAD();
void _DbgReadBytesB();
void _DbgReadBytesA();
EXTERN_DLL_EXPORT bool __cdecl DbgReadBytes(BasePointer address, void* dst, int amount, bool safe = true);
EXTERN_DLL_EXPORT bool __cdecl DbgReadBytes(void* address, void* dst, int amount);
EXTERN_DLL_EXPORT BYTE* __cdecl DbgReadBytes(BasePointer address, int amount, bool safe = true);
EXTERN_DLL_EXPORT BYTE* __cdecl DbgReadBytes(void* address, int amount);



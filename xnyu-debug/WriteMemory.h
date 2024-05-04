#pragma once

// --- Functions ---

// FLOAT
void _DbgWriteFloatBS();
void _DbgWriteFloatAS();
void _DbgWriteFloatBV();
void _DbgWriteFloatAV();
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteFloat(BasePointer address, void* src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteFloat(void* address, void* src);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteFloat(BasePointer address, float src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteFloat(void* address, float src);

// DOUBLE
void _DbgWriteDoubleBS();
void _DbgWriteDoubleAS();
void _DbgWriteDoubleBV();
void _DbgWriteDoubleAV();
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteDouble(BasePointer address, void* src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteDouble(void* address, void* src);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteDouble(BasePointer address, double src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteDouble(void* address, double src);

// INT32
void _DbgWriteInt32BS();
void _DbgWriteInt32AS();
void _DbgWriteInt32BV();
void _DbgWriteInt32AV();
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteInt32(BasePointer address, void* src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteInt32(void* address, void* src);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteInt32(BasePointer address, int src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteInt32(void* address, int src);

// INT64
void _DbgWriteInt64BS();
void _DbgWriteInt64AS();
void _DbgWriteInt64BV();
void _DbgWriteInt64AV();
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteInt64(BasePointer address, void* src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteInt64(void* address, void* src);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteInt64(BasePointer address, long long src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteInt64(void* address, long long src);

// STRING
void _DbgWriteStringBS();
void _DbgWriteStringAS();
void _DbgWriteStringBV();
void _DbgWriteStringAV();
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteString(BasePointer address, void* src, int size, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteString(void* address, void* src, int size);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteString(BasePointer address, std::string src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteString(void* address, std::string src);

// BOOL
void _DbgWriteBoolBS();
void _DbgWriteBoolAS();
void _DbgWriteBoolBV();
void _DbgWriteBoolAV();
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteBool(BasePointer address, void* src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteBool(void* address, void* src);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteBool(BasePointer address, bool src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteBool(void* address, bool src);

// BYTE
void _DbgWriteByteBS();
void _DbgWriteByteAS();
void _DbgWriteByteBV();
void _DbgWriteByteAV();
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteByte(BasePointer address, void* src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteByte(void* address, void* src);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteByte(BasePointer address, BYTE src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteByte(void* address, BYTE src);

// BYTES
void _DbgWriteBytesBS();
void _DbgWriteBytesAS();
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteBytes(BasePointer address, void* src, int amount, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteBytes(void* address, void* src, int amount);


// VARIABLE
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteVariable(BasePointer address, Variable& src, bool safe = true);
EXTERN_DLL_EXPORT bool __stdcall MemoryWriteBytes(void* address, Variable& src);



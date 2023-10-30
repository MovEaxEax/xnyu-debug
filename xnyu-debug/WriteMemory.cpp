#include "pch.h"
#include "BasePointer.h"
#include "WriteMemory.h"



// --- Functions ---

// FLOAT
void _DbgWriteFloatBS()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, par._src, sizeof(float));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteFloatAS()
{
	__try
	{
		std::memcpy(par._address, par._src, sizeof(float));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteFloatBV()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, &par._float_value, sizeof(float));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteFloatAV()
{
	__try
	{
		std::memcpy(par._address, &par._float_value, sizeof(float));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteFloat(BasePointer address, void* src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	_DbgWriteFloatBS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteFloat(void* address, void* src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._src = src;
	_DbgWriteFloatAS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteFloat(BasePointer address, float src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._float_value = src;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgWriteFloatBV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteFloat(void* address, float src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._float_value = src;
	par._address = address;
	_DbgWriteFloatAV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

// DOUBLE
void _DbgWriteDoubleBS()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, par._src, sizeof(double));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteDoubleAS()
{
	__try
	{
		std::memcpy(par._address, par._src, sizeof(double));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteDoubleBV()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, &par._double_value, sizeof(double));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteDoubleAV()
{
	__try
	{
		std::memcpy(par._address, &par._double_value, sizeof(double));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteDouble(BasePointer address, void* src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._src = src;
	_DbgWriteDoubleBS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteDouble(void* address, void* src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._src = src;
	_DbgWriteDoubleAS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteDouble(BasePointer address, double src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._double_value = src;
	_DbgWriteDoubleBV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteDouble(void* address, double src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._double_value = src;
	_DbgWriteDoubleAV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

// INT32
void _DbgWriteInt32BS()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, par._src, sizeof(int));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteInt32AS()
{
	__try
	{
		std::memcpy(par._address, par._src, sizeof(int));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteInt32BV()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, &par._int32_value, sizeof(int));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteInt32AV()
{
	__try
	{
		std::memcpy(par._address, &par._int32_value, sizeof(int));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteInt32(BasePointer address, void* src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	_DbgWriteInt32BS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteInt32(void* address, void* src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._src = src;
	_DbgWriteInt32AS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteInt32(BasePointer address, int src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._int32_value = src;
	_DbgWriteInt32BV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteInt32(void* address, int src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._int32_value = src;
	_DbgWriteInt32AV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

// INT64
void _DbgWriteInt64BS()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, par._src, sizeof(long long));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteInt64AS()
{
	__try
	{
		std::memcpy(par._address, par._src, sizeof(long long));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteInt64BV()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, &par._int64_value, sizeof(long long));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteInt64AV()
{
	__try
	{
		std::memcpy(par._address, &par._int64_value, sizeof(long long));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteInt64(BasePointer address, void* src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	_DbgWriteInt64BS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteInt64(void* address, void* src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._src = src;
	_DbgWriteInt64AS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteInt64(BasePointer address, long long src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._int64_value = src;
	_DbgWriteInt64BV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteInt64(void* address, long long src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._int64_value = src;
	_DbgWriteInt64AV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

// STRING
void _DbgWriteStringBS()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, par._src, par._size);
			char terminator = 0x00;
			std::memcpy((void*)((long long)finalAddress + (long long)par._size), &terminator, 1);
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteStringAS()
{
	__try
	{
		std::memcpy(par._address, par._src, par._size);
		char terminator = 0x00;
		std::memcpy((void*)((long long)par._address + (long long)par._size), &terminator, 1);
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteStringBV()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, par._string_value.c_str(), par._string_value.size());
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteStringAV()
{
	__try
	{
		std::memcpy(par._address, par._string_value.c_str(), par._string_value.size());
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteString(BasePointer address, void* src, int size, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	par._size = size;
	_DbgWriteStringBS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteString(void* address, void* src, int size)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._src = src;
	par._size = size;
	_DbgWriteStringAS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteString(BasePointer address, std::string src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._string_value = src;
	_DbgWriteStringBV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteString(void* address, std::string src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._string_value = src;
	_DbgWriteStringAV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

// BOOL
void _DbgWriteBoolBS()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, par._src, sizeof(bool));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteBoolAS()
{
	__try
	{
		std::memcpy(par._address, par._src, sizeof(bool));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteBoolBV()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, &par._bool_value, sizeof(bool));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteBoolAV()
{
	__try
	{
		std::memcpy(par._address, &par._bool_value, sizeof(bool));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteBool(BasePointer address, void* src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	_DbgWriteBoolBS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteBool(void* address, void* src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._src = src;
	_DbgWriteBoolAS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteBool(BasePointer address, bool src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._bool_value = src;
	_DbgWriteBoolBV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteBool(void* address, bool src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._bool_value = src;
	_DbgWriteBoolAV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

// BYTE
void _DbgWriteByteBS()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, par._src, 1);
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteByteAS()
{
	__try
	{
		std::memcpy(par._address, par._src, 1);
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteByteBV()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, &par._byte_value, 1);
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteByteAV()
{
	__try
	{
		std::memcpy(par._address, &par._byte_value, 1);
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteByte(BasePointer address, void* src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	_DbgWriteByteBS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteByte(void* address, void* src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._src = src;
	_DbgWriteByteAS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteByte(BasePointer address, BYTE src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._byte_value = src;
	_DbgWriteByteBV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteByte(void* address, BYTE src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._byte_value = src;
	_DbgWriteByteAV();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

// BYTES
void _DbgWriteBytesBS()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(finalAddress, par._src, par._amount);
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgWriteBytesAS()
{
	__try
	{
		std::memcpy(par._address, par._src, par._amount);
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteBytes(BasePointer address, void* src, int amount, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	par._amount = amount;
	_DbgWriteBytesBS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgWriteBytes(void* address, void* src, int amount)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._src = src;
	par._amount = amount;
	_DbgWriteBytesAS();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}



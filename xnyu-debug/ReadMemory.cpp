#include "pch.h"
#include "BasePointer.h"
#include "ReadMemory.h"



// --- Functions ---

// POINTER
void _DbgReadPointerBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		void* finalAddress = ret._void_ptr;
		if (ret._void_ptr != nullptr)
		{
			std::memcpy(par._dst, &finalAddress, sizeof(void*));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadPointerB()
{
	__try
	{
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._void_ptr = nullptr;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadPointer(BasePointer address, void** dst, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadPointerBD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT void* __cdecl DbgReadPointer(BasePointer address, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadPointerB();
	void* result = ret._void_ptr;
	ReleaseMutex(MemoryMutex);
	return result;
}

// FLOAT
void _DbgReadFloatBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		void* finalAddress = ret._void_ptr;
		if (finalAddress != nullptr)
		{
			std::memcpy(par._dst, finalAddress, sizeof(float));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadFloatAD()
{
	__try
	{
		std::memcpy(par._dst, par._address, sizeof(float));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadFloatB()
{
	__try
	{
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		void* finalAddress = ret._void_ptr;
		if (ret._void_ptr != nullptr)
		{
			float dst;
			std::memcpy(&dst, finalAddress, sizeof(float));
			ret._float_value = dst;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._float_value = 0;
	}
}

void _DbgReadFloatA()
{
	__try
	{
		float dst;
		std::memcpy(&dst, par._address, sizeof(float));
		ret._float_value = dst;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._float_value = 0;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadFloat(BasePointer address, void* dst, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadFloatBD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadFloat(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadFloatAD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT float __cdecl DbgReadFloat(BasePointer address, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadFloatB();
	float result = ret._float_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT float __cdecl DbgReadFloat(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadFloatA();
	float result = ret._float_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

// DOUBLE
void _DbgReadDoubleBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		void* finalAddress = ret._void_ptr;
		if (ret._void_ptr != nullptr)
		{
			std::memcpy(par._dst, finalAddress, sizeof(double));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadDoubleAD()
{
	__try
	{
		std::memcpy(par._dst, par._address, sizeof(double));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadDoubleB()
{
	__try
	{
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		void* finalAddress = ret._void_ptr;
		if (ret._void_ptr != nullptr)
		{
			double dst;
			std::memcpy(&dst, finalAddress, sizeof(double));
			ret._double_value = dst;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._double_value = 0;
	}
}

void _DbgReadDoubleA()
{
	__try
	{
		double dst;
		std::memcpy(&dst, par._address, sizeof(double));
		ret._double_value = dst;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._double_value = 0;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadDouble(BasePointer address, void* dst, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadDoubleBD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadDouble(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadDoubleAD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT double __cdecl DbgReadDouble(BasePointer address, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadDoubleB();
	double result = ret._double_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT double __cdecl DbgReadDouble(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadDoubleA();
	double result = ret._double_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

// INT32
void _DbgReadInt32BD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(par._dst, finalAddress, sizeof(int));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadInt32AD()
{
	__try
	{
		std::memcpy(par._dst, par._address, sizeof(int));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadInt32B()
{
	__try
	{
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			int dst;
			std::memcpy(&dst, finalAddress, sizeof(int));
			ret._int32_value = dst;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._int32_value = 0;
	}
}

void _DbgReadInt32A()
{
	__try
	{
		int dst;
		std::memcpy(&dst, par._address, sizeof(int));
		ret._int32_value = dst;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._int32_value = 0;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadInt32(BasePointer address, void* dst, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadInt32BD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadInt32(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadInt32AD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT int __cdecl DbgReadInt32(BasePointer address, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadInt32B();
	int result = ret._int32_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT int __cdecl DbgReadInt32(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadInt32A();
	int result = ret._int32_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

// INT64
void _DbgReadInt64BD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(par._dst, finalAddress, sizeof(long long));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadInt64AD()
{
	__try
	{
		std::memcpy(par._dst, par._address, sizeof(long long));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadInt64B()
{
	__try
	{
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			long long dst = 0;
			std::memcpy(&dst, finalAddress, sizeof(long long));
			ret._int64_value = dst;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._int64_value = 0;
	}
}

void _DbgReadInt64A()
{
	__try
	{
		long long dst = 0;
		std::memcpy(&dst, par._address, sizeof(long long));
		ret._int64_value = dst;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._int64_value = 0;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadInt64(BasePointer address, void* dst, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadInt64BD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadInt64(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadInt64AD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT long long __cdecl DbgReadInt64(BasePointer address, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadInt64B();
	long long result = ret._int64_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT long long __cdecl DbgReadInt64(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadInt64A();
	long long result = ret._int64_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

// STRING
void _DbgReadStringBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			int index = 0;
			while (true)
			{
				std::memcpy((void*)((long long)par._dst + (long long)index), (void*)((long long)finalAddress + (long long)index), 1);
				if (((char*)par._dst)[index] == 0x00) break;
				index++;
			}
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadStringAD()
{
	__try
	{
		int index = 0;
		while (true)
		{
			std::memcpy((void*)((long long)par._dst + (long long)index), (void*)((long long)par._address + (long long)index), 1);
			if (((char*)par._dst)[index] == 0x00) break;
			index++;
		}
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadStringB()
{
	__try
	{
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			int index = 0;
			char* buffer = new char[2048];
			while (true)
			{
				std::memcpy((void*)((long long)buffer + (long long)index), (void*)((long long)finalAddress + (long long)index), 1);
				if (buffer[index] == 0x00) break;
				index++;
			}
			ret._string_value.assign(buffer, sizeof(buffer));
			free(buffer);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._string_value = "";
	}
}

void _DbgReadStringA()
{
	__try
	{
		int index = 0;
		char* buffer = new char[2048];
		while (true)
		{
			std::memcpy((void*)((long long)buffer + (long long)index), (void*)((long long)par._address + (long long)index), 1);
			if (buffer[index] == 0x00) break;
			index++;
		}
		ret._string_value.assign(buffer, sizeof(buffer));
		free(buffer);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._string_value = "";
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadString(BasePointer address, void* dst, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadStringBD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadString(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadStringAD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT std::string __cdecl DbgReadString(BasePointer address, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadStringB();
	std::string result = ret._string_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT std::string __cdecl DbgReadString(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadStringA();
	std::string result = ret._string_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

// BOOL
void _DbgReadBoolBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(par._dst, finalAddress, sizeof(bool));
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadBoolAD()
{
	__try
	{
		std::memcpy(par._dst, par._address, sizeof(bool));
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadBoolB()
{
	__try
	{
		ret._bool_value = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			bool dst;
			std::memcpy(&dst, finalAddress, sizeof(bool));
			ret._bool_value = dst;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._bool_value = false;
	}
}

void _DbgReadBoolA()
{
	__try
	{
		bool dst;
		std::memcpy(&dst, par._address, sizeof(bool));
		ret._bool_value = dst;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._bool_value = false;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadBool(BasePointer address, void* dst, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadBoolBD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadBool(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadBoolAD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadBool(BasePointer address, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadBoolB();
	bool result = ret._bool_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadBool(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadBoolA();
	bool result = ret._bool_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

// BYTE
void _DbgReadByteBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(par._dst, finalAddress, 1);
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadByteAD()
{
	__try
	{
		std::memcpy(par._dst, par._address, 1);
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadByteB()
{
	__try
	{
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			BYTE dst;
			std::memcpy(&dst, finalAddress, 1);
			ret._byte_value = dst;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._byte_value = 0x00;
	}
}

void _DbgReadByteA()
{
	__try
	{
		BYTE dst;
		std::memcpy(&dst, par._address, 1);
		ret._byte_value = dst;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._byte_value = 0x00;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadByte(BasePointer address, void* dst, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadByteBD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadByte(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadByteAD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT BYTE __cdecl DbgReadByte(BasePointer address, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadByteB();
	BYTE result = ret._byte_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT BYTE __cdecl DbgReadByte(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadByteA();
	BYTE result = ret._byte_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

// BYTES
void _DbgReadBytesBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			std::memcpy(par._dst, finalAddress, par._amount);
			ret._success = true;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadBytesAD()
{
	__try
	{
		std::memcpy(par._dst, par._address, par._amount);
		ret._success = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._success = false;
	}
}

void _DbgReadBytesB()
{
	__try
	{
		if (par._use_safe) DbgResolveBasePointerSafe(); else DbgResolveBasePointerUnsafe();
		if (ret._void_ptr != nullptr)
		{
			void* finalAddress = ret._void_ptr;
			BYTE* dst = new BYTE[par._amount];
			std::memcpy(&dst, finalAddress, par._amount);
			ret._byte_ptr = dst;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._byte_ptr = nullptr;
	}
}

void _DbgReadBytesA()
{
	__try
	{
		BYTE* dst = new BYTE[par._amount];
		std::memcpy(&dst, par._address, par._amount);
		ret._byte_ptr = dst;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._byte_ptr = nullptr;
	}
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadBytes(BasePointer address, void* dst, int amount, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	par._amount = amount;
	_DbgReadBytesBD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT bool __cdecl DbgReadBytes(void* address, void* dst, int amount)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	par._amount = amount;
	_DbgReadBytesAD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT BYTE* __cdecl DbgReadBytes(BasePointer address, int amount, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._use_safe = safe;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._amount = amount;
	_DbgReadBytesB();
	BYTE* result = ret._byte_ptr;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT BYTE* __cdecl DbgReadBytes(void* address, int amount)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._amount = amount;
	_DbgReadBytesA();
	BYTE* result = ret._byte_ptr;
	ReleaseMutex(MemoryMutex);
	return result;
}



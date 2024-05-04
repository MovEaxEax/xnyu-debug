#include "pch.h"
#include "BasePointer.h"
#include "Variable.h"
#include "ReadMemory.h"



// --- Functions ---

// POINTER
void _DbgReadPointerBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._void_ptr = nullptr;
	}
}

EXTERN_DLL_EXPORT bool __stdcall MemoryReadPointerT1(BasePointer address, void** dst, bool safe)
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

bool __stdcall MemoryReadPointer(BasePointer address, void** dst, bool safe)
{
	return MemoryReadPointerT1(address, dst, safe);
}

EXTERN_DLL_EXPORT void* __stdcall MemoryReadPointerT2(BasePointer address, bool safe)
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

void* __stdcall MemoryReadPointer(BasePointer address, bool safe)
{
	return MemoryReadPointerT2(address, safe);
}

// FLOAT
void _DbgReadFloatBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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

EXTERN_DLL_EXPORT bool __stdcall MemoryReadFloatT3(BasePointer address, void* dst, bool safe)
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

bool __stdcall MemoryReadFloat(BasePointer address, void* dst, bool safe)
{
	return MemoryReadFloatT3(address, dst, safe);
}

EXTERN_DLL_EXPORT bool __stdcall MemoryReadFloatT4(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadFloatAD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

bool __stdcall MemoryReadFloat(void* address, void* dst)
{
	return MemoryReadFloatT4(address, dst);
}

EXTERN_DLL_EXPORT float __stdcall MemoryReadFloatT5(BasePointer address, bool safe)
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

float __stdcall MemoryReadFloat(BasePointer address, bool safe)
{
	return MemoryReadFloatT5(address, safe);
}

EXTERN_DLL_EXPORT float __stdcall MemoryReadFloatT6(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadFloatA();
	float result = ret._float_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

float __stdcall MemoryReadFloat(void* address)
{
	return MemoryReadFloatT6(address);
}

// DOUBLE
void _DbgReadDoubleBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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

EXTERN_DLL_EXPORT bool __stdcall MemoryReadDoubleT7(BasePointer address, void* dst, bool safe)
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

bool __stdcall MemoryReadDouble(BasePointer address, void* dst, bool safe)
{
	return MemoryReadDoubleT7(address, dst, safe);
}

EXTERN_DLL_EXPORT bool __stdcall MemoryReadDoubleT8(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadDoubleAD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

bool __stdcall MemoryReadDouble(void* address, void* dst)
{
	return MemoryReadDoubleT8(address, dst);
}

EXTERN_DLL_EXPORT double __stdcall MemoryReadDoubleT9(BasePointer address, bool safe)
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

double __stdcall MemoryReadDouble(BasePointer address, bool safe)
{
	return MemoryReadDoubleT9(address, safe);
}

EXTERN_DLL_EXPORT double __stdcall MemoryReadDoubleT10(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadDoubleA();
	double result = ret._double_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

double __stdcall MemoryReadDouble(void* address)
{
	return MemoryReadDoubleT10(address);
}

// INT32
void _DbgReadInt32BD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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

EXTERN_DLL_EXPORT bool __stdcall MemoryReadInt32T11(BasePointer address, void* dst, bool safe)
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

bool __stdcall MemoryReadInt32(BasePointer address, void* dst, bool safe)
{
	return MemoryReadInt32T11(address, dst, safe);
}

EXTERN_DLL_EXPORT bool __stdcall MemoryReadInt32T12(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadInt32AD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

bool __stdcall MemoryReadInt32(void* address, void* dst)
{
	return MemoryReadInt32T12(address, dst);
}

EXTERN_DLL_EXPORT int __stdcall MemoryReadInt32T13(BasePointer address, bool safe)
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

int __stdcall MemoryReadInt32(BasePointer address, bool safe)
{
	return MemoryReadInt32T13(address, safe);
}

EXTERN_DLL_EXPORT int __stdcall MemoryReadInt32T14(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadInt32A();
	int result = ret._int32_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

int __stdcall MemoryReadInt32(void* address)
{
	return MemoryReadInt32T14(address);
}

// INT64
void _DbgReadInt64BD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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

EXTERN_DLL_EXPORT bool __stdcall MemoryReadInt64T15(BasePointer address, void* dst, bool safe)
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

bool __stdcall MemoryReadInt64(BasePointer address, void* dst, bool safe)
{
	return MemoryReadInt64T15(address, dst, safe);
}

EXTERN_DLL_EXPORT bool __stdcall MemoryReadInt64T16(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadInt64AD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

bool __stdcall MemoryReadInt64(void* address, void* dst)
{
	return MemoryReadInt64T16(address, dst);
}

EXTERN_DLL_EXPORT long long __stdcall MemoryReadInt64T17(BasePointer address, bool safe)
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

long long __stdcall MemoryReadInt64(BasePointer address, bool safe)
{
	return MemoryReadInt64T17(address, safe);
}

EXTERN_DLL_EXPORT long long __stdcall MemoryReadInt64T18(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadInt64A();
	long long result = ret._int64_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

long long __stdcall MemoryReadInt64(void* address)
{
	return MemoryReadInt64T18(address);
}

// STRING
void _DbgReadStringBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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

EXTERN_DLL_EXPORT bool __stdcall MemoryReadStringT19(BasePointer address, void* dst, bool safe)
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

bool __stdcall MemoryReadString(BasePointer address, void* dst, bool safe)
{
	return MemoryReadStringT19(address, dst, safe);
}

EXTERN_DLL_EXPORT bool __stdcall MemoryReadStringT20(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadStringAD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

bool __stdcall MemoryReadString(void* address, void* dst)
{
	return MemoryReadStringT20(address, dst);
}

EXTERN_DLL_EXPORT std::string __stdcall MemoryReadStringT21(BasePointer address, bool safe)
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

std::string __stdcall MemoryReadString(BasePointer address, bool safe)
{
	return MemoryReadStringT21(address, safe);
}

EXTERN_DLL_EXPORT std::string __stdcall MemoryReadStringT22(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadStringA();
	std::string result = ret._string_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

std::string __stdcall MemoryReadString(void* address)
{
	return MemoryReadStringT22(address);
}

// BOOL
void _DbgReadBoolBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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

EXTERN_DLL_EXPORT bool __stdcall MemoryReadBoolT23(BasePointer address, void* dst, bool safe)
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

bool __stdcall MemoryReadBool(BasePointer address, void* dst, bool safe)
{
	return MemoryReadBoolT23(address, dst, safe);
}

EXTERN_DLL_EXPORT bool __stdcall MemoryReadBoolT24(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadBoolAD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

bool __stdcall MemoryReadBool(void* address, void* dst)
{
	return MemoryReadBoolT24(address, dst);
}

EXTERN_DLL_EXPORT bool __stdcall MemoryReadBoolT25(BasePointer address, bool safe)
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

bool __stdcall MemoryReadBool(BasePointer address, bool safe)
{
	return MemoryReadBoolT25(address, safe);
}

EXTERN_DLL_EXPORT bool __stdcall MemoryReadBoolT26(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadBoolA();
	bool result = ret._bool_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

bool __stdcall MemoryReadBool(void* address)
{
	return MemoryReadBoolT26(address);
}

// BYTE
void _DbgReadByteBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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

EXTERN_DLL_EXPORT bool __stdcall MemoryReadByteT27(BasePointer address, void* dst, bool safe)
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

bool __stdcall MemoryReadByte(BasePointer address, void* dst, bool safe)
{
	return MemoryReadByteT27(address, dst, safe);
}

EXTERN_DLL_EXPORT bool __stdcall MemoryReadByteT28(void* address, void* dst)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._dst = dst;
	_DbgReadByteAD();
	bool result = ret._success;
	ReleaseMutex(MemoryMutex);
	return result;
}

bool __stdcall MemoryReadByte(void* address, void* dst)
{
	return MemoryReadByteT28(address, dst);
}

EXTERN_DLL_EXPORT BYTE __stdcall MemoryReadByteT29(BasePointer address, bool safe)
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

BYTE __stdcall MemoryReadByte(BasePointer address, bool safe)
{
	return MemoryReadByteT29(address, safe);
}

EXTERN_DLL_EXPORT BYTE __stdcall MemoryReadByteT30(void* address)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	_DbgReadByteA();
	BYTE result = ret._byte_value;
	ReleaseMutex(MemoryMutex);
	return result;
}

BYTE __stdcall MemoryReadByte(void* address)
{
	return MemoryReadByteT30(address);
}

// BYTES
void _DbgReadBytesBD()
{
	__try
	{
		ret._success = false;
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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
		if (par._use_safe) MemoryResolveBasePointerSafe(); else MemoryResolveBasePointerUnsafe();
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

EXTERN_DLL_EXPORT bool __stdcall MemoryReadBytesT31(BasePointer address, void* dst, int amount, bool safe)
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

bool __stdcall MemoryReadBytes(BasePointer address, void* dst, int amount, bool safe)
{
	return MemoryReadBytesT31(address, dst, amount, safe);
}

EXTERN_DLL_EXPORT bool __stdcall MemoryReadBytesT32(void* address, void* dst, int amount)
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

bool __stdcall MemoryReadBytes(void* address, void* dst, int amount)
{
	return MemoryReadBytesT32(address, dst, amount);
}

EXTERN_DLL_EXPORT BYTE* __stdcall MemoryReadBytesT33(BasePointer address, int amount, bool safe)
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

BYTE* __stdcall MemoryReadBytes(BasePointer address, int amount, bool safe)
{
	return MemoryReadBytesT33(address, amount, safe);
}

EXTERN_DLL_EXPORT BYTE* __stdcall MemoryReadBytesT34(void* address, int amount)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	par._address = address;
	par._amount = amount;
	_DbgReadBytesA();
	BYTE* result = ret._byte_ptr;
	ReleaseMutex(MemoryMutex);
	return result;
}

BYTE* __stdcall MemoryReadBytes(void* address, int amount)
{
	return MemoryReadBytesT34(address, amount);
}

EXTERN_DLL_EXPORT void __stdcall MemoryReadVariableT35(BasePointer address, Variable& src, bool safe)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	switch (src.getType())
	{
	case VariableType::BOOL:
		src.setValue(MemoryReadBool(address));
		break;
	case VariableType::BYTE:
		src.setValue(MemoryReadByte(address));
		break;
	case VariableType::INT32:
		src.setValue(MemoryReadInt32(address));
		break;
	case VariableType::INT64:
		src.setValue(MemoryReadInt64(address));
		break;
	case VariableType::FLOAT:
		src.setValue(MemoryReadFloat(address));
		break;
	case VariableType::DOUBLE:
		src.setValue(MemoryReadDouble(address));
		break;
	case VariableType::STRING:
		src.setValue(MemoryReadString(address));
		break;
	default:
		break;
	}
	ReleaseMutex(MemoryMutex);
}

void __stdcall MemoryReadVariable(BasePointer address, Variable& src, bool safe)
{
	MemoryReadVariableT35(address, src, safe);
}

EXTERN_DLL_EXPORT void __stdcall MemoryReadVariableT36(void* address, Variable& src)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	switch (src.getType())
	{
	case VariableType::BOOL:
		src.setValue(MemoryReadBool(address));
		break;
	case VariableType::BYTE:
		src.setValue(MemoryReadByte(address));
		break;
	case VariableType::INT32:
		src.setValue(MemoryReadInt32(address));
		break;
	case VariableType::INT64:
		src.setValue(MemoryReadInt64(address));
		break;
	case VariableType::FLOAT:
		src.setValue(MemoryReadFloat(address));
		break;
	case VariableType::DOUBLE:
		src.setValue(MemoryReadDouble(address));
		break;
	case VariableType::STRING:
		src.setValue(MemoryReadString(address));
		break;
	default:
		break;
	}
	ReleaseMutex(MemoryMutex);
}

void __stdcall MemoryReadVariable(void* address, Variable& src)
{
	MemoryReadVariableT36(address, src);
}



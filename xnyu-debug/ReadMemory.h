#pragma once

// POINTER
void _DbgReadPointerBD()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._void_ptr = nullptr;
	}
}

bool DbgReadPointer(BasePointer address, void** dst)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadPointerBD();
	return ret._success;
}

void* DbgReadPointer(BasePointer address)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadPointerB();
	return ret._void_ptr;
}

// FLOAT
void _DbgReadFloatBD()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgReadFloat(BasePointer address, void* dst)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadFloatBD();
	return ret._success;
}

bool DbgReadFloat(void* address, void* dst)
{
	par._address = address;
	par._dst = dst;
	_DbgReadFloatAD();
	return ret._success;
}

float DbgReadFloat(BasePointer address)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadFloatB();
	return ret._float_value;
}

float DbgReadFloat(void* address)
{
	par._address = address;
	_DbgReadFloatA();
	return ret._float_value;
}

// DOUBLE
void _DbgReadDoubleBD()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgReadDouble(BasePointer address, void* dst)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadDoubleBD();
	return ret._success;
}

bool DbgReadDouble(void* address, void* dst)
{
	par._address = address;
	par._dst = dst;
	_DbgReadDoubleAD();
	return ret._success;
}

double DbgReadDouble(BasePointer address)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadDoubleB();
	return ret._double_value;
}

double DbgReadDouble(void* address)
{
	par._address = address;
	_DbgReadDoubleA();
	return ret._double_value;
}

// INT32
void _DbgReadInt32BD()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgReadInt32(BasePointer address, void* dst)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadInt32BD();
	return ret._success;
}

bool DbgReadInt32(void* address, void* dst)
{
	par._address = address;
	par._dst = dst;
	_DbgReadInt32AD();
	return ret._success;
}

int DbgReadInt32(BasePointer address)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadInt32B();
	return ret._int32_value;
}

int DbgReadInt32(void* address)
{
	par._address = address;
	_DbgReadInt32A();
	return ret._int32_value;
}

// INT64
void _DbgReadInt64BD()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgReadInt64(BasePointer address, void* dst)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadInt64BD();
	return ret._success;
}

bool DbgReadInt64(void* address, void* dst)
{
	par._address = address;
	par._dst = dst;
	_DbgReadInt64AD();
	return ret._success;
}

long long DbgReadInt64(BasePointer address)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadInt64B();
	return ret._int64_value;
}

long long DbgReadInt64(void* address)
{
	par._address = address;
	_DbgReadInt64A();
	return ret._int64_value;
}

// STRING
void _DbgReadStringBD()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgReadString(BasePointer address, void* dst)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadStringBD();
	return ret._success;
}

bool DbgReadString(void* address, void* dst)
{
	par._address = address;
	par._dst = dst;
	_DbgReadStringAD();
	return ret._success;
}

std::string DbgReadString(BasePointer address)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadStringB();
	return ret._string_value;
}

std::string DbgReadString(void* address)
{
	par._address = address;
	_DbgReadStringA();
	return ret._string_value;
}

// BOOL
void _DbgReadBoolBD()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgReadBool(BasePointer address, void* dst)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadBoolBD();
	return ret._success;
}

bool DbgReadBool(void* address, void* dst)
{
	par._address = address;
	par._dst = dst;
	_DbgReadBoolAD();
	return ret._success;
}

bool DbgReadBool(BasePointer address)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadBoolB();
	return ret._bool_value;
}

bool DbgReadBool(void* address)
{
	par._address = address;
	_DbgReadBoolA();
	return ret._bool_value;
}

// BYTE
void _DbgReadByteBD()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgReadByte(BasePointer address, void* dst)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	_DbgReadByteBD();
	return ret._success;
}

bool DbgReadByte(void* address, void* dst)
{
	par._address = address;
	par._dst = dst;
	_DbgReadByteAD();
	return ret._success;
}

BYTE DbgReadByte(BasePointer address)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgReadByteB();
	return ret._byte_value;
}

BYTE DbgReadByte(void* address)
{
	par._address = address;
	_DbgReadByteA();
	return ret._byte_value;
}

// BYTES
void _DbgReadBytesBD()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgReadBytes(BasePointer address, void* dst, int amount)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._dst = dst;
	par._amount = amount;
	_DbgReadBytesBD();
	return ret._success;
}

bool DbgReadBytes(void* address, void* dst, int amount)
{
	par._address = address;
	par._dst = dst;
	par._amount = amount;
	_DbgReadBytesAD();
	return ret._success;
}

BYTE* DbgReadBytes(BasePointer address, int amount)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._amount = amount;
	_DbgReadBytesB();
	return ret._byte_ptr;
}

BYTE* DbgReadBytes(void* address, int amount)
{
	par._address = address;
	par._amount = amount;
	_DbgReadBytesA();
	return ret._byte_ptr;
}



#pragma once

// FLOAT
void _DbgWriteFloatBS()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgWriteFloat(BasePointer address, void* src)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	_DbgWriteFloatBS();
	return ret._success;
}

bool DbgWriteFloat(void* address, void* src)
{
	par._address = address;
	par._src = src;
	_DbgWriteFloatAS();
	return ret._success;
}

bool DbgWriteFloat(BasePointer address, float src)
{
	par._float_value = src;
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	_DbgWriteFloatBV();
	return ret._success;
}

bool DbgWriteFloat(void* address, float src)
{
	par._float_value = src;
	par._address = address;
	_DbgWriteFloatAV();
	return ret._success;
}

// DOUBLE
void _DbgWriteDoubleBS()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgWriteDouble(BasePointer address, void* src)
{
	par._basepointer = address;
	par._src = src;
	_DbgWriteDoubleBS();
	return ret._success;
}

bool DbgWriteDouble(void* address, void* src)
{
	par._address = address;
	par._src = src;
	_DbgWriteDoubleAS();
	return ret._success;
}

bool DbgWriteDouble(BasePointer address, double src)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._double_value = src;
	_DbgWriteDoubleBV();
	return ret._success;
}

bool DbgWriteDouble(void* address, double src)
{
	par._address = address;
	par._double_value = src;
	_DbgWriteDoubleAV();
	return ret._success;
}

// INT32
void _DbgWriteInt32BS()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgWriteInt32(BasePointer address, void* src)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	_DbgWriteInt32BS();
	return ret._success;
}

bool DbgWriteInt32(void* address, void* src)
{
	par._address = address;
	par._src = src;
	_DbgWriteInt32AS();
	return ret._success;
}

bool DbgWriteInt32(BasePointer address, int src)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._int32_value = src;
	_DbgWriteInt32BV();
	return ret._success;
}

bool DbgWriteInt32(void* address, int src)
{
	par._address = address;
	par._int32_value = src;
	_DbgWriteInt32AV();
	return ret._success;
}

// INT64
void _DbgWriteInt64BS()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgWriteInt64(BasePointer address, void* src)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	_DbgWriteInt64BS();
	return ret._success;
}

bool DbgWriteInt64(void* address, void* src)
{
	par._address = address;
	par._src = src;
	_DbgWriteInt64AS();
	return ret._success;
}

bool DbgWriteInt64(BasePointer address, long long src)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._int64_value = src;
	_DbgWriteInt64BV();
	return ret._success;
}

bool DbgWriteInt64(void* address, long long src)
{
	par._address = address;
	par._int64_value = src;
	_DbgWriteInt64AV();
	return ret._success;
}

// STRING
void _DbgWriteStringBS()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgWriteString(BasePointer address, void* src, int size)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	par._size = size;
	_DbgWriteStringBS();
	return ret._success;
}

bool DbgWriteString(void* address, void* src, int size)
{
	par._address = address;
	par._src = src;
	par._size = size;
	_DbgWriteStringAS();
	return ret._success;
}

bool DbgWriteString(BasePointer address, std::string src)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._string_value = src;
	_DbgWriteStringBV();
	return ret._success;
}

bool DbgWriteString(void* address, std::string src)
{
	par._address = address;
	par._string_value = src;
	_DbgWriteStringAV();
	return ret._success;
}

// BOOL
void _DbgWriteBoolBS()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgWriteBool(BasePointer address, void* src)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	_DbgWriteBoolBS();
	return ret._success;
}

bool DbgWriteBool(void* address, void* src)
{
	par._address = address;
	par._src = src;
	_DbgWriteBoolAS();
	return ret._success;
}

bool DbgWriteBool(BasePointer address, bool src)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._bool_value = src;
	_DbgWriteBoolBV();
	return ret._success;
}

bool DbgWriteBool(void* address, bool src)
{
	par._address = address;
	par._bool_value = src;
	_DbgWriteBoolAV();
	return ret._success;
}

// BYTE
void _DbgWriteByteBS()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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
		DbgResolveBasePointerSafe();
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

bool DbgWriteByte(BasePointer address, void* src)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	_DbgWriteByteBS();
	return ret._success;
}

bool DbgWriteByte(void* address, void* src)
{
	par._address = address;
	par._src = src;
	_DbgWriteByteAS();
	return ret._success;
}

bool DbgWriteByte(BasePointer address, BYTE src)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._byte_value = src;
	_DbgWriteByteBV();
	return ret._success;
}

bool DbgWriteByte(void* address, BYTE src)
{
	par._address = address;
	par._byte_value = src;
	_DbgWriteByteAV();
	return ret._success;
}

// BYTES
void _DbgWriteBytesBS()
{
	__try
	{
		ret._success = false;
		DbgResolveBasePointerSafe();
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

bool DbgWriteBytes(BasePointer address, void* src, int amount)
{
	par._basepointer = address;
	par._basepointerOffsetSize = address.offsets.size();
	par._src = src;
	par._amount = amount;
	_DbgWriteBytesBS();
	return ret._success;
}

bool DbgWriteBytes(void* address, void* src, int amount)
{
	par._address = address;
	par._src = src;
	par._amount = amount;
	_DbgWriteBytesAS();
	return ret._success;
}



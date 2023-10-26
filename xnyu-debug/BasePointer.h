#pragma once

struct BasePointer
{
	void* baseAddress;
	std::vector<void*> offsets;
};

struct ReturnValue
{
	void* _void_ptr;
	bool _success;
	float _float_value;
	double _double_value;
	int _int32_value;
	long long _int64_value;
	std::string _string_value;
	BYTE _byte_value;
	bool _bool_value;
	BYTE* _byte_ptr;
};

struct ParameterValue
{
	BasePointer _basepointer;
	int _basepointerOffsetSize;
	void* _address;
	void* _dst;
	void* _src;
	int _amount;
	int _size;
	float _float_value;
	double _double_value;
	int _int32_value;
	long long _int64_value;
	std::string _string_value;
	BYTE _byte_value;
	bool _bool_value;
	BYTE* _byte_ptr;
};

// Struct to handle the return values
ReturnValue ret;
ParameterValue par;



bool IsValidMemoryAddress(uintptr_t address, uintptr_t* srcMemory, uintptr_t* dstMemory, int memoryCounter)
{
	for (int i = 0; i < memoryCounter; i++)
	{
		if (address >= srcMemory[i] && address <= (dstMemory[i] - sizeof(uintptr_t)))
		{
			return true;
		}
	}
	return false;
}

void DbgResolveBasePointerUnsafe()
{
	__try
	{
		uintptr_t finalAddress = reinterpret_cast<uintptr_t>(par._basepointer.baseAddress);
		finalAddress = *reinterpret_cast<uintptr_t*>(finalAddress);
		for (int i = 0; i < par._basepointerOffsetSize; i++)
		{
			finalAddress += reinterpret_cast<uintptr_t>(par._basepointer.offsets[i]);
			if (i + 1 < par._basepointerOffsetSize)
			{
				finalAddress = *reinterpret_cast<uintptr_t*>(finalAddress);
			}
		}
		ret._void_ptr = reinterpret_cast<void*>(finalAddress);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._void_ptr = nullptr;
	}
}

void DbgResolveBasePointerSafe()
{
	__try
	{
		uintptr_t finalAddress = reinterpret_cast<uintptr_t>(par._basepointer.baseAddress);
		if (!IsValidMemoryAddress(finalAddress, memoryRegionsStart, memoryRegionsEnd, memoryRegionsCounter))
		{
			ret._void_ptr = nullptr;
			return;
		}
		finalAddress = *reinterpret_cast<uintptr_t*>(finalAddress);
		for (int i = 0; i < par._basepointerOffsetSize; i++)
		{
			finalAddress += reinterpret_cast<uintptr_t>(par._basepointer.offsets[i]);
			if (i + 1 < par._basepointerOffsetSize)
			{
				if (!IsValidMemoryAddress(finalAddress, memoryRegionsStart, memoryRegionsEnd, memoryRegionsCounter))
				{
					ret._void_ptr = nullptr;
					return;
				}
				finalAddress = *reinterpret_cast<uintptr_t*>(finalAddress);
			}
		}
		ret._void_ptr = reinterpret_cast<void*>(finalAddress);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		ret._void_ptr = nullptr;
	}
}



#include "pch.h"
#include "MemoryRegions.h"
#include "BasePointer.h"



// --- Variables ---
ReturnValue ret = ReturnValue();
ParameterValue par = ParameterValue();
HANDLE MemoryMutex = CreateMutex(NULL, FALSE, NULL);



// --- Functions ---
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
		if (!IsValidMemoryAddress(finalAddress, MemoryRegionsStart, MemoryRegionsEnd, MemoryRegionsCounter))
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
				if (!IsValidMemoryAddress(finalAddress, MemoryRegionsStart, MemoryRegionsEnd, MemoryRegionsCounter))
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



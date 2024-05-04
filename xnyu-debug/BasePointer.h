#pragma once

// --- Structs ---

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
	bool _use_safe;
};



// --- Variables ---
extern ReturnValue ret;
extern ParameterValue par;
extern HANDLE MemoryMutex;



// --- Functions ---
bool MemoryIsValidAddress(uintptr_t address, uintptr_t* srcMemory, uintptr_t* dstMemory, int memoryCounter);
void MemoryResolveBasePointerUnsafe();
void MemoryResolveBasePointerSafe();



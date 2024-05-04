#pragma once

// --- Structs ---
struct SigScanParameter
{
	int _pattern_size;
	BYTE* _pattern_mask;
	BYTE* _bytes_scan;
	BYTE* _bytes_check;
	long long _dst_offset;
	void* _start;
	void* _end;
	long long _amount;
	void* _finding;
	bool _success;
};



// --- Variables ---
extern SigScanParameter ssp;



// --- Functions ---
void _MemorySigScanFromTo();
bool MemorySigScanPatternConversion(std::string pattern);
EXTERN_DLL_EXPORT void* __stdcall MemorySigScanT1(void* src, std::string pattern);
EXTERN_DLL_EXPORT void* __stdcall MemorySigScanT2(void* src, void* dst, std::string pattern);
EXTERN_DLL_EXPORT void* __stdcall MemorySigScanT3(void* src, int amount, std::string pattern);
EXTERN_DLL_EXPORT void* __stdcall MemorySigScanT4(void* src, long long amount, std::string pattern);
EXTERN_DLL_EXPORT void* __stdcall MemorySigScanT5(std::string pattern);
void* __stdcall MemorySigScan(void* src, std::string pattern);
void* __stdcall MemorySigScan(void* src, void* dst, std::string pattern);
void* __stdcall MemorySigScan(void* src, int amount, std::string pattern);
void* __stdcall MemorySigScan(void* src, long long amount, std::string pattern);
void* __stdcall MemorySigScan(std::string pattern);


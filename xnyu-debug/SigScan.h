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
void _DbgSigScanFromTo();
bool SigScanPatternConversion(std::string pattern);
EXTERN_DLL_EXPORT void* __cdecl DbgSigScan(void* src, std::string pattern);
EXTERN_DLL_EXPORT void* __cdecl DbgSigScan(void* src, void* dst, std::string pattern);
EXTERN_DLL_EXPORT void* __cdecl DbgSigScan(void* src, int amount, std::string pattern);
EXTERN_DLL_EXPORT void* __cdecl DbgSigScan(void* src, long long amount, std::string pattern);
EXTERN_DLL_EXPORT void* __cdecl DbgSigScan(std::string pattern);



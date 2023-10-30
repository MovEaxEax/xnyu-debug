#include "pch.h"
#include "MemoryRegions.h"
#include "BasePointer.h"
#include "SigScan.h"



// --- Variables ---
SigScanParameter ssp = SigScanParameter();



// --- Functions ---
void _DbgSigScanFromTo()
{
	__try
	{
		ssp._finding = nullptr;
		ssp._success = false;
		long long offset = 0;
		void* dstAddress = ssp._start;
		while ((long long)dstAddress + (long long)ssp._pattern_size < (long long)ssp._end)
		{
			bool found = true;
			int check_index = 0;
			dstAddress = (void*)((long long)ssp._start + offset);
			std::memcpy(ssp._bytes_scan, dstAddress, ssp._pattern_size);

			for (int i = 0; i < ssp._pattern_size; i++)
			{
				if (ssp._pattern_mask[i] != 1) continue;
				if (ssp._bytes_scan[i] != ssp._bytes_check[check_index])
				{
					found = false;
					break;
				}
				check_index++;
			}

			if (found)
			{
				ssp._finding = (void*)((long long)dstAddress + ssp._dst_offset);
				ssp._success = true;
				break;
			}
			else
			{
				offset++;
			}
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
	}
}

bool SigScanPatternConversion(std::string pattern)
{
	try
	{
		std::vector<BYTE> patternMask;
		std::vector<BYTE> bytesToCheck;
		bool offsetFound = false;

		pattern.erase(std::remove_if(pattern.begin(), pattern.end(), ::isspace), pattern.end());
		std::transform(pattern.begin(), pattern.end(), pattern.begin(),
			[](unsigned char c) { return std::tolower(c); });

		for (size_t i = 0; i < pattern.length();)
		{
			if (pattern[i] == 'x')
			{
				if (offsetFound)
				{
					return false;
				}
				ssp._dst_offset = i / 2;
				patternMask.push_back(0x00);
				offsetFound = true;
				++i;
			}
			else if (pattern[i] == '?')
			{
				patternMask.push_back(0);
				++i;
			}
			else if (i + 1 < pattern.length() && std::isxdigit(pattern[i]) && std::isxdigit(pattern[i + 1]))
			{
				// Convert two hex characters to a byte
				std::string byteString = pattern.substr(i, 2);
				BYTE byte = static_cast<BYTE>(std::stoul(byteString, nullptr, 16));
				bytesToCheck.push_back(byte);
				patternMask.push_back(0x01);
				i += 2;
			}
			else
			{
				return false;
			}
		}

		ssp._pattern_size = patternMask.size();

		std::copy(patternMask.begin(), patternMask.end(), ssp._pattern_mask);
		std::copy(bytesToCheck.begin(), bytesToCheck.end(), ssp._bytes_check);


		return true;
	}
	catch (...)
	{
		return false;
	}
}

EXTERN_DLL_EXPORT void* __cdecl DbgSigScan(void* src, std::string pattern)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	ssp._pattern_mask = (BYTE*)malloc(1024);
	ssp._bytes_scan = (BYTE*)malloc(1024);
	ssp._bytes_check = (BYTE*)malloc(1024);
	if (!SigScanPatternConversion(pattern))
	{
		ReleaseMutex(MemoryMutex);
		return nullptr;
	}
	ssp._start = src;
	ssp._end = (void*)0xFFFFFFFFFFFFFFFF;
	_DbgSigScanFromTo();
	free(ssp._pattern_mask);
	free(ssp._bytes_scan);
	free(ssp._bytes_check);
	void* result = ssp._finding;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT void* __cdecl DbgSigScan(void* src, void* dst, std::string pattern)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	ssp._pattern_mask = (BYTE*)malloc(1024);
	ssp._bytes_scan = (BYTE*)malloc(1024);
	ssp._bytes_check = (BYTE*)malloc(1024);
	if (!SigScanPatternConversion(pattern))
	{
		ReleaseMutex(MemoryMutex);
		return nullptr;
	}
	ssp._start = src;
	ssp._end = dst;
	_DbgSigScanFromTo();
	free(ssp._pattern_mask);
	free(ssp._bytes_scan);
	free(ssp._bytes_check);
	void* result = ssp._finding;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT void* __cdecl DbgSigScan(void* src, int amount, std::string pattern)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	ssp._pattern_mask = (BYTE*)malloc(1024);
	ssp._bytes_scan = (BYTE*)malloc(1024);
	ssp._bytes_check = (BYTE*)malloc(1024);
	if (!SigScanPatternConversion(pattern))
	{
		ReleaseMutex(MemoryMutex);
		return nullptr;
	}
	ssp._start = src;
	ssp._end = (void*)((long long)src + (long long)amount);
	_DbgSigScanFromTo();
	free(ssp._pattern_mask);
	free(ssp._bytes_scan);
	free(ssp._bytes_check);
	void* result = ssp._finding;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT void* __cdecl DbgSigScan(void* src, long long amount, std::string pattern)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	ssp._pattern_mask = (BYTE*)malloc(1024);
	ssp._bytes_scan = (BYTE*)malloc(1024);
	ssp._bytes_check = (BYTE*)malloc(1024);
	if (!SigScanPatternConversion(pattern))
	{
		ReleaseMutex(MemoryMutex);
		return nullptr;
	}
	ssp._start = src;
	ssp._end = (void*)((long long)src + amount);
	_DbgSigScanFromTo();
	free(ssp._pattern_mask);
	free(ssp._bytes_scan);
	free(ssp._bytes_check);
	void* result = ssp._finding;
	ReleaseMutex(MemoryMutex);
	return result;
}

EXTERN_DLL_EXPORT void* __cdecl DbgSigScan(std::string pattern)
{
	WaitForSingleObject(MemoryMutex, INFINITE);
	ssp._pattern_mask = (BYTE*)malloc(1024);
	ssp._bytes_scan = (BYTE*)malloc(1024);
	ssp._bytes_check = (BYTE*)malloc(1024);
	if (!SigScanPatternConversion(pattern))
	{
		ReleaseMutex(MemoryMutex);
		return nullptr;
	}
	for (int i = 0; i < MemoryRegionsCounter; i++)
	{
		ssp._start = (void*)MemoryRegionsStart[i];
		ssp._end = (void*)MemoryRegionsEnd[i];
		_DbgSigScanFromTo();
		if (ssp._success) break;
	}
	free(ssp._pattern_mask);
	free(ssp._bytes_scan);
	free(ssp._bytes_check);
	void* result = ssp._finding;
	ReleaseMutex(MemoryMutex);
	return result;
}



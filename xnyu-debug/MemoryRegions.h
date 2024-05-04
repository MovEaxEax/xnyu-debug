#pragma once

// --- Variables ---
extern uintptr_t MemoryRegionsStart[65000];
extern uintptr_t MemoryRegionsEnd[65000];
extern int MemoryRegionsCounter;

// --- Functions ---
EXTERN_DLL_EXPORT uintptr_t __stdcall MemoryGetSectionAddress(HMODULE moduleHandle, std::string sectionName);
long long __stdcall MemoryGetRegionsSize();
void __stdcall MemoryUpdateRegions();



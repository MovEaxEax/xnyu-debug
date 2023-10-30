#pragma once

// --- Variables ---
extern uintptr_t MemoryRegionsStart[65000];
extern uintptr_t MemoryRegionsEnd[65000];
extern int MemoryRegionsCounter;



// --- Functions ---
long long GetMemoryRegionsSize();
void UpdateMemoryRegions();



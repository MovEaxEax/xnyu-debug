#include "pch.h"
#include "BasePointer.h"
#include "MemoryRegions.h"


// --- Variables ---
uintptr_t MemoryRegionsStart[65000];
uintptr_t MemoryRegionsEnd[65000];
int MemoryRegionsCounter = 0;



// --- Functions ---
long long GetMemoryRegionsSize() {
    WaitForSingleObject(MemoryMutex, INFINITE);

    if (MemoryRegionsCounter <= 0) return -1;
    long long size = 0;
    for (int i = 0; i < MemoryRegionsCounter; i++) size += (long long)(MemoryRegionsEnd[i] - MemoryRegionsStart[i]);

    ReleaseMutex(MemoryMutex);

    return size;
}

void UpdateMemoryRegions() {
    WaitForSingleObject(MemoryMutex, INFINITE);
    HANDLE processHandle = GetCurrentProcess();
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);

    int Counter = 0;

    LPVOID lpAddress = systemInfo.lpMinimumApplicationAddress;
    while (lpAddress < systemInfo.lpMaximumApplicationAddress) {
        MEMORY_BASIC_INFORMATION memInfo;
        SIZE_T bytesReturned = VirtualQueryEx(processHandle, lpAddress, &memInfo, sizeof(memInfo));
        if (bytesReturned == 0) {
            break;
        }

        // Check if the memory region is readable and/or writable
        if (memInfo.Protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE)) {
            Counter++;
        }

        lpAddress = (LPVOID)((DWORD_PTR)memInfo.BaseAddress + memInfo.RegionSize);
    }

    Counter = 0;
    lpAddress = systemInfo.lpMinimumApplicationAddress;
    while (lpAddress < systemInfo.lpMaximumApplicationAddress) {
        MEMORY_BASIC_INFORMATION memInfo;
        SIZE_T bytesReturned = VirtualQueryEx(processHandle, lpAddress, &memInfo, sizeof(memInfo));
        if (bytesReturned == 0) {
            break;
        }

        if (memInfo.Protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE)) {
            uintptr_t start = (uintptr_t)memInfo.BaseAddress;
            uintptr_t end = (uintptr_t)memInfo.BaseAddress + memInfo.RegionSize;
            std::memcpy(MemoryRegionsStart + (Counter * sizeof(uintptr_t)), &start, sizeof(uintptr_t*));
            std::memcpy(MemoryRegionsEnd + (Counter * sizeof(uintptr_t)), &end, sizeof(uintptr_t*));
            Counter++;
        }

        lpAddress = (LPVOID)((DWORD_PTR)memInfo.BaseAddress + memInfo.RegionSize);
    }

    for (int i = 0; i < Counter; ++i)
    {
        for (int k = 0; k < Counter; k++)
        {
            if (i != k)
            {
                if ((MemoryRegionsStart[i] != 0 && MemoryRegionsEnd[i] != 0) && (MemoryRegionsStart[k] != 0 && MemoryRegionsEnd[k] != 0))
                {
                    if (MemoryRegionsStart[i] == MemoryRegionsStart[k] && MemoryRegionsEnd[i] == MemoryRegionsEnd[k])
                    {
                        MemoryRegionsStart[i] = 0;
                        MemoryRegionsEnd[i] = 0;
                        break;
                    }
                }
            }
        }
    }

    int writeIndex = 0;
    for (int readIndex = 0; readIndex < Counter; ++readIndex) {
        if (MemoryRegionsStart[readIndex] != 0 || MemoryRegionsEnd[readIndex] != 0) {
            MemoryRegionsStart[writeIndex] = MemoryRegionsStart[readIndex];
            MemoryRegionsEnd[writeIndex] = MemoryRegionsEnd[readIndex];
            writeIndex++;
        }
    }

    MemoryRegionsCounter = writeIndex;

    ReleaseMutex(MemoryMutex);
}



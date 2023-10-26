#pragma once

uintptr_t memoryRegionsStart[65000];
uintptr_t memoryRegionsEnd[65000];
int memoryRegionsCounter = 0;

long long GetMemoryRegionsSize() {
    if (memoryRegionsCounter <= 0) return -1;

    long long size = 0;
    for (int i = 0; i < memoryRegionsCounter; i++) size += (long long)(memoryRegionsEnd[i] - memoryRegionsStart[i]);
    return size;
}

void GetMemoryRegions(uintptr_t* srcRegions, uintptr_t* dstRegions, int* count) {
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
            std::memcpy(srcRegions + (Counter * sizeof(uintptr_t)), &start, sizeof(uintptr_t*));
            std::memcpy(dstRegions + (Counter * sizeof(uintptr_t)), &end, sizeof(uintptr_t*));
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
                if ((memoryRegionsStart[i] != 0 && memoryRegionsEnd[i] != 0) && (memoryRegionsStart[k] != 0 && memoryRegionsEnd[k] != 0))
                {
                    if (memoryRegionsStart[i] == memoryRegionsStart[k] && memoryRegionsEnd[i] == memoryRegionsEnd[k])
                    {
                        memoryRegionsStart[i] = 0;
                        memoryRegionsEnd[i] = 0;
                        break;
                    }
                }
            }
        }
    }

    int writeIndex = 0;
    for (int readIndex = 0; readIndex < Counter; ++readIndex) {
        if (memoryRegionsStart[readIndex] != 0 || memoryRegionsEnd[readIndex] != 0) {
            memoryRegionsStart[writeIndex] = memoryRegionsStart[readIndex];
            memoryRegionsEnd[writeIndex] = memoryRegionsEnd[readIndex];
            writeIndex++;
        }
    }
    Counter = writeIndex;

    std::memcpy(count, &Counter, sizeof(int));
}



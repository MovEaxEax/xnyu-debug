#include "pch.h"
#include "NtUser.h"



// --- Functions ---
void* GetProcAddressNt(std::string name)
{
	if (name.substr(0, 6) == "NtUser")
	{
		HMODULE Win32UDLLHandle = GetModuleHandleA("win32u.dll");
		if (Win32UDLLHandle == NULL) return nullptr;

		long long Win32UDLLHandleAddressStart = (long long)Win32UDLLHandle;

		if (name == "NtUserGetKeyState")
		{
			long long Win32UDLLHandleAddressEnd = Win32UDLLHandleAddressStart + 8000;
			return DbgSigScan((void*)Win32UDLLHandleAddressStart, (void*)Win32UDLLHandleAddressEnd, "X 8B D1 B8 03 10 00 00 F6 04 25 08 03 FE 7F 01");
		}
		if (name == "NtUserGetAsyncKeyState")
		{
			long long Win32UDLLHandleAddressEnd = Win32UDLLHandleAddressStart + 8000;
			return DbgSigScan((void*)Win32UDLLHandleAddressStart, (void*)Win32UDLLHandleAddressEnd, "X 8B D1 B8 44 10 00 00 F6 04 25 08 03 FE 7F 01");
		}
	}

	return nullptr;
}



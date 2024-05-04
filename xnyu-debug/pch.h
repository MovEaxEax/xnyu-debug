#ifndef PCH_H
#define PCH_H

#pragma once

#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <psapi.h>
#include <stdio.h>
#include <iomanip>
#include <xnamath.h>
#include <filesystem>
#include <tlhelp32.h>
#include <ctime> 
#include <memory>
#include <memorys.h>
#include <atlimage.h>
#include <thread>
#include <mutex>
#include <functional>
#include <unordered_set>
#include <regex>
#include <optional>
#include <chrono>
#include <random>
#include <variant>
#include <Python.h>

#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")

#include <Processthreadsapi.h>
#pragma comment(lib, "Kernel32.lib")

#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

#include <dinput.h>
#pragma comment(lib, "Dinput8.lib")

#include <Xinput.h>
#pragma comment(lib,"XInput.lib")

#pragma comment(lib, "Dxguid.lib")

#include <Shlobj.h>
#pragma comment(lib, "shell32.lib")

#define SUBHOOK_STATIC
#include <subhook.h>
#include "subhook.c"

#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)
#define EXTERN_DLL_IMPORT extern "C" __declspec(dllimport)
#define WIN32_LEAN_AND_MEAN 

#endif //PCH_H

#pragma once

template <typename FuncT>
class xNyuHook {
public:
    FuncT pFunction;
    FuncT pFunctionTrampoline = nullptr;
    FuncT pFunctionBefore;
    FuncT pFunctionAfter;

    subhook::Hook Subhook;
    void* hookAddress;

    HANDLE Mutex = CreateMutex(NULL, FALSE, NULL);

    bool HookInit = true;
    bool RealCall = true;
    bool RemoveBlockInstall = false;

    bool IsActive = false;

    float Factor = 1.0f;

    xNyuHook(void* originalAddress, void* hookAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : pFunction(reinterpret_cast<FuncT>(originalAddress)),
        hookAddress(reinterpret_cast<FuncT>(hookAddress)),
        pFunctionBefore(reinterpret_cast<FuncT>(hookExecuteBefore)),
        pFunctionAfter(reinterpret_cast<FuncT>(hookExecuteAfter)) { }

    virtual ~xNyuHook() = default;

    template <typename... Args>
    auto CustomHook(Args&&... args) -> decltype(pFunction(std::forward<Args>(args)...));

    void setHookBefore(void* hook)
    {
        pFunctionBefore = (FuncT)hook;
    }

    void setHookAfter(void* hook)
    {
        pFunctionAfter = (FuncT)hook;
    }

    void setFactor(float value)
    {
        Factor = value;
    }

    void setHookInit(bool value)
    {
        HookInit = value;
    }

    void setRealCall(bool value)
    {
        RealCall = value;
    }

    void mutexWait()
    {
        WaitForSingleObject(Mutex, INFINITE);
    }

    void mutexFree()
    {
        ReleaseMutex(Mutex);
    }

    bool isInstalled()
    {
        mutexWait();
        bool result = Subhook.IsInstalled();
        mutexFree();
        return result;
    }

    bool isActive()
    {
        return IsActive;
    }

    void install(bool trampoline = true, bool fromHook = false)
    {
        mutexWait();
        if (!Subhook.IsInstalled() && !RemoveBlockInstall)
        {
            Subhook.Install((void*)pFunction, hookAddress, sizeof(void*) == 8 ? subhook::HookFlags::HookFlag64BitOffset : subhook::HookFlags::HookNoFlags);
            if (trampoline)
            {
                pFunctionTrampoline = (FuncT)Subhook.GetTrampoline();
                HookInit = true;
                IsActive = true;
                RemoveBlockInstall = false;
            }
            else
            {
                if (!fromHook)
                {
                    HookInit = true;
                    IsActive = true;
                    RemoveBlockInstall = false;
                }
            }
        }
        if (RemoveBlockInstall)
        {
            IsActive = false;
            RemoveBlockInstall = false;
        }
        mutexFree();
    }

    void remove(bool fromHook = false)
    {
        mutexWait();
        if (Subhook.IsInstalled())
        {
            if (!fromHook) IsActive = false;
            Subhook.Remove();
        }
        else
        {
            RemoveBlockInstall = true;
            IsActive = false;
        }
        mutexFree();
    }

    template<typename... Args>
    auto callOriginal(Args&&... args) -> decltype(pFunction(std::forward<Args>(args)...))
    {
        return pFunction(std::forward<Args>(args)...);
    }

    template<typename... Args>
    auto callOriginalSafeType(Args&&... args) -> decltype(pFunction(std::forward<Args>(args)...))
    {
        mutexWait();
        bool _isInstalled = Subhook.IsInstalled();
        if (_isInstalled) remove(true);
        auto result = pFunction(std::forward<Args>(args)...);
        if (_isInstalled) install(false, true);
        mutexFree();
        return result;
    }

    template<typename... Args>
    auto callOriginalSafeVoid(Args&&... args) -> decltype(pFunction(std::forward<Args>(args)...))
    {
        mutexWait();
        bool _isInstalled = Subhook.IsInstalled();
        if (_isInstalled) remove(true);
        pFunction(std::forward<Args>(args)...);
        if (_isInstalled) install(false, true);
        mutexFree();
    }

    template<typename... Args>
    auto callTrampoline(Args&&... args) -> decltype(pFunction(std::forward<Args>(args)...))
    {
        return pFunctionTrampoline(std::forward<Args>(args)...);
    }
};



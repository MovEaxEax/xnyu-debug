#pragma once

template <typename FuncT>
class xNyuHook {
public:
    FuncT pFunction;
    FuncT pFunctionBefore;
    FuncT pFunctionAfter;
    subhook::Hook Subhook;
    void* hookAddress;
    xNyuHook(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : pFunction(reinterpret_cast<FuncT>(originalAddress)),
        pFunctionBefore(reinterpret_cast<FuncT>(hookExecuteBefore)),
        pFunctionAfter(reinterpret_cast<FuncT>(hookExecuteAfter)) {
    }

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

    bool isInstalled()
    {
        return Subhook.IsInstalled();
    }

    void remove() {
        Subhook.Remove();
    }
};



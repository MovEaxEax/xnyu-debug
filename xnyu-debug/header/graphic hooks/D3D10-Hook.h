#include <dxgiformat.h>
#include <d3d10_1.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <d3dcommon.h>
#include <D3Dcompiler.h>
#pragma comment (lib, "d3d10_1.lib")
#pragma comment (lib, "d3d10.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "D3Dcompiler.lib")

namespace Direct3D10Hooking
{
    class Direct3D10 : public Direct3DHooking::Direct3DBase
    {
        ID3D10Device* pDevice;
        IDXGISwapChain* pSwapChain;

    public:
        Direct3D10();
        ~Direct3D10();
        static const int VTableElements = 98;

        std::vector<size_t> vtable() const override;
    };
}

using namespace Indicium::Core::Exceptions;

Direct3D10Hooking::Direct3D10::Direct3D10() :
    pDevice(nullptr), pSwapChain(nullptr)
{
    temp_window = std::make_unique<Window>("TempDirect3D10OverlayWindow");

    HMODULE hModDXGI = GetModuleHandleA("DXGI.dll");
    HMODULE hModD3D10 = GetModuleHandleA("D3D10.dll");

    if (hModDXGI == nullptr)
    {
        throw ModuleNotFoundException("Could not get handle to DXGI.dll");
    }

    if (hModD3D10 == nullptr)
    {
        throw ModuleNotFoundException("Could not get handle to D3D10.dll");
    }

    const LPVOID hCreateDXGIFactory = static_cast<LPVOID>(GetProcAddress(hModDXGI, "CreateDXGIFactory"));
    if (hCreateDXGIFactory == nullptr)
    {
        throw ProcAddressNotFoundException("Could not get handle to CreateDXGIFactory");
    }

    IDXGIFactory* pFactory;
    const auto hr = static_cast<HRESULT(WINAPI*)(
        REFIID,
        void** ppFactory)>(hCreateDXGIFactory)(
            __uuidof(IDXGIFactory),
            reinterpret_cast<void**>(&pFactory));

    if (FAILED(hr))
    {
        throw DXAPIException("Could not create DXGI factory", hr);
    }

    const auto hD3D10CreateDeviceAndSwapChain = static_cast<LPVOID>(GetProcAddress(
        hModD3D10,
        "D3D10CreateDeviceAndSwapChain"));
    if (hD3D10CreateDeviceAndSwapChain == nullptr)
    {
        throw ProcAddressNotFoundException("Could not get handle to D3D10CreateDeviceAndSwapChain");
    }

    UINT i = 0;
    IDXGIAdapter* pAdapter;
    std::vector<IDXGIAdapter*> vAdapters;
    while (pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND)
    {
        vAdapters.push_back(pAdapter);
        ++i;
    }

    if (vAdapters.empty())
    {
        throw RuntimeException("No adapters found");
    }

    DXGI_RATIONAL rational = {};
    rational.Numerator = 60;
    rational.Denominator = 1;

    DXGI_MODE_DESC modeDesc = {};
    modeDesc.Height = 100;
    modeDesc.Width = 100;
    modeDesc.RefreshRate = rational;
    modeDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    DXGI_SAMPLE_DESC sampleDesc = {};
    sampleDesc.Count = 1;
    sampleDesc.Quality = 0;

    DXGI_SWAP_CHAIN_DESC scDesc = {};
    scDesc.BufferCount = 1;
    scDesc.Flags = 0;
    scDesc.Windowed = true;
    scDesc.OutputWindow = temp_window->windowHandle();
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.SampleDesc = sampleDesc;
    scDesc.BufferDesc = modeDesc;

    const auto hr10 = static_cast<HRESULT(WINAPI*)(
        IDXGIAdapter*,
        D3D10_DRIVER_TYPE,
        HMODULE,
        UINT,
        UINT,
        DXGI_SWAP_CHAIN_DESC*,
        IDXGISwapChain**,
        ID3D10Device**)>(hD3D10CreateDeviceAndSwapChain)(
            vAdapters[0],
            D3D10_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            D3D10_SDK_VERSION,
            &scDesc,
            &pSwapChain,
            &pDevice);

    if (FAILED(hr10))
    {
        throw DXAPIException("Could not create D3D10 device", hr10);
    }
}

// D3D10 Device
IDXGISwapChain* pD3D10_SwapChain;
ID3D10Device* pD3D10_Device;
void* pD3D10_SwapChain_vTable[18];

std::vector<size_t> Direct3D10Hooking::Direct3D10::vtable() const
{
    pD3D10_SwapChain = pSwapChain;
    return std::vector<size_t>(*reinterpret_cast<size_t**>(pSwapChain),
        *reinterpret_cast<size_t**>(pSwapChain) + DXGIHooking::DXGI::SwapChainVTableElements);
}

Direct3D10Hooking::Direct3D10::~Direct3D10()
{
    if (pSwapChain)
        pSwapChain->Release();

    if (pDevice)
        pDevice->Release();
}

// EndScene() Function Pointer
typedef HRESULT(__stdcall* Present10T)(UINT SyncInterval, UINT Flags);
Present10T pD3D10_Present = nullptr;

// Addresses
void* D3D10_Present_Original_Address = 0;
void* D3D10_Present_Hook_Address = 0;

// Subhooks
subhook::Hook D3D10_Subhook;

// Fonts
ID3DX10Font* Extra_Small_Font_D3D10 = nullptr;
ID3DX10Font* Small_Font_D3D10 = nullptr;
ID3DX10Font* Small_Medium_Font_D3D10 = nullptr;
ID3DX10Font* Medium_Font_D3D10 = nullptr;
ID3DX10Font* Big_Medium_Font_D3D10 = nullptr;
ID3DX10Font* Big_Font_D3D10 = nullptr;
ID3DX10Font* Extra_Big_Font_D3D10 = nullptr;

// Colors
D3DXCOLOR Red_D3D10(255, 255, 0, 0);
D3DXCOLOR Green_D3D10(255, 0, 255, 0);
D3DXCOLOR Blue_D3D10(255, 0, 0, 255);
D3DXCOLOR Black_D3D10(255, 0, 0, 0);
D3DXCOLOR White_D3D10(255, 255, 255, 255);
D3DXCOLOR Gray_D3D10(255, 150, 150, 150);
D3DXCOLOR Yellow_D3D10(255, 255, 247, 0);
D3DXCOLOR Purple_D3D10(255, 170, 0, 255);
D3DXCOLOR Pink_D3D10(255, 255, 0, 221);
D3DXCOLOR Orange_D3D10(255, 255, 157, 0);
D3DXCOLOR Cyan_D3D10(255, 0, 255, 242);

//
// Drawing -------------------------------------------------------------------------
//

void DrawRectangle_D3D10()
{

}



void DrawMessage_D3D10()
{


}

//
// Hook Routine ---------------------------------------------------------------------
//
HRESULT D3D10_Present_Hook(UINT SyncInterval, UINT Flags)
{
    if (DebugMenuInit == true)
    {
        // Set the device for the globals
        pD3D10_SwapChain->GetDevice(__uuidof(pD3D10_Device), (void**)&pD3D10_Device);

        // Set DebugMenu function
        DebugDraw = (DebugDrawT)DrawMessage_D3D10;

        // Init fonts
        ID3DX10Font* pFont = nullptr;
        D3DX10_FONT_DESC fontDesc = {};
        fontDesc.Width = 0;
        fontDesc.Weight = 0;
        fontDesc.MipLevels = 1;
        fontDesc.Italic = false;
        fontDesc.CharSet = DEFAULT_CHARSET;
        fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
        fontDesc.Quality = DEFAULT_QUALITY;
        fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
        wcscpy_s(fontDesc.FaceName, L"Arial");
        fontDesc.Height = 12;
        D3DX10CreateFontIndirect(pD3D10_Device, &fontDesc, &Extra_Small_Font_D3D10);
        fontDesc.Height = 16;
        D3DX10CreateFontIndirect(pD3D10_Device, &fontDesc, &Extra_Small_Font_D3D10);
        fontDesc.Height = 20;
        D3DX10CreateFontIndirect(pD3D10_Device, &fontDesc, &Extra_Small_Font_D3D10);
        fontDesc.Height = 24;
        D3DX10CreateFontIndirect(pD3D10_Device, &fontDesc, &Extra_Small_Font_D3D10);
        fontDesc.Height = 28;
        D3DX10CreateFontIndirect(pD3D10_Device, &fontDesc, &Extra_Small_Font_D3D10);
        fontDesc.Height = 36;
        D3DX10CreateFontIndirect(pD3D10_Device, &fontDesc, &Extra_Small_Font_D3D10);
        fontDesc.Height = 58;
        D3DX10CreateFontIndirect(pD3D10_Device, &fontDesc, &Extra_Small_Font_D3D10);

        // Deactivate DebugMenu
        DebugMenuInit = false;
    }

    // Debug Menu
    DebugMenuMainRoutine();

    // Remove hook
    D3D10_Subhook.Remove();

    // Trampoline
    HRESULT Trampoline = pD3D10_Present(SyncInterval, Flags);

    // Reinstall Hook
    if (sizeof(void*) == 8) D3D10_Subhook.Install(D3D10_Present_Original_Address, D3D10_Present_Hook_Address, subhook::HookFlags::HookFlag64BitOffset);
    if (sizeof(void*) == 4) D3D10_Subhook.Install(D3D10_Present_Original_Address, D3D10_Present_Hook_Address);

    return Trampoline;
}



//
// Init function --------------------------------------------------------------------
//
BOOL D3D10HookInit()
{
    if (GetModuleHandleA("d3d10.dll") == NULL) return false;

    try {
        // I love to comment comments
        std::cout << "DirectX 10 detected!" << std::endl;

        // Get vTable
        Direct3D10Hooking::Direct3D10 D3D10Hookah;
        std::vector<uintptr_t> vTable = D3D10Hookah.vtable();

        std::memcpy(pD3D10_SwapChain_vTable, pD3D10_SwapChain, sizeof(void*) * 18);
        pD3D10_SwapChain->GetDevice(__uuidof(pD3D10_Device), (void**)&pD3D10_Device);

        // Set addresses
        D3D10_Present_Original_Address = pD3D10_SwapChain_vTable[8];
        pD3D10_Present = (Present10T)D3D10_Present_Original_Address;
        D3D10_Present_Hook_Address = D3D10_Present_Hook;

        // Install the Hook
        if (sizeof(void*) == 8) return D3D10_Subhook.Install(D3D10_Present_Original_Address, D3D10_Present_Hook_Address, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) return D3D10_Subhook.Install(D3D10_Present_Original_Address, D3D10_Present_Hook_Address);

        return false;
    }
    catch (const std::exception e)
    {
        std::cout << "Error when init D3D10: \n" << e.what() << std::endl;
    }

    return false;
}



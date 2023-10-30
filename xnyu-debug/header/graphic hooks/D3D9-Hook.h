#pragma once
namespace Direct3D9Hooking
{
    class Direct3D9 : public Direct3DHooking::Direct3DBase
    {
        IDirect3D9* d3d9;
        IDirect3DDevice9* d3d9_device;
    public:
        Direct3D9();
        ~Direct3D9();
        static const int VTableElements = 119;

        std::vector<size_t> vtable() const override;
    };
}

using namespace Indicium::Core::Exceptions;

Direct3D9Hooking::Direct3D9::Direct3D9() :
    d3d9(nullptr), d3d9_device(nullptr)
{
    temp_window = std::make_unique<Window>("TempDirect3D9OverlayWindow");

    const auto hMod = GetModuleHandleA("d3d9.dll");

    if (hMod == nullptr)
    {
        throw ModuleNotFoundException("Could not get the handle to d3d9.dll");
    }

    const auto Direct3DCreate9 = static_cast<LPVOID>(GetProcAddress(hMod, "Direct3DCreate9"));
    if (Direct3DCreate9 == nullptr)
    {
        throw ProcAddressNotFoundException("Could not locate the Direct3DCreate9 procedure entry point");
    }

    d3d9 = static_cast<LPDIRECT3D9(WINAPI*)(UINT)>(Direct3DCreate9)(D3D_SDK_VERSION);
    if (d3d9 == nullptr)
    {
        throw RuntimeException("Could not create the DirectX 9 interface");
    }

    D3DDISPLAYMODE display_mode;
    const auto hr = d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display_mode);
    if (FAILED(hr))
    {
        throw DXAPIException("Could not determine the current display mode", hr);
    }

    D3DPRESENT_PARAMETERS present_parameters;
    ZeroMemory(&present_parameters, sizeof(D3DPRESENT_PARAMETERS));
    present_parameters.Windowed = TRUE;
    present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    present_parameters.BackBufferFormat = display_mode.Format;

    const auto error_code = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, temp_window->windowHandle(),
        D3DCREATE_SOFTWARE_VERTEXPROCESSING |
        D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &present_parameters, &d3d9_device);
    if (FAILED(error_code))
    {
        throw DXAPIException("Could not create the Direct3D 9 device", error_code);
    }
}

// D3D9 Device
IDirect3DDevice9* pD3D9_Device;

std::vector<size_t> Direct3D9Hooking::Direct3D9::vtable() const
{
    pD3D9_Device = d3d9_device;
    return std::vector<size_t>(*reinterpret_cast<size_t**>(d3d9_device),
        *reinterpret_cast<size_t**>(d3d9_device) + VTableElements);
}

Direct3D9Hooking::Direct3D9::~Direct3D9()
{
    if (d3d9_device)
        d3d9_device->Release();

    if (d3d9)
        d3d9->Release();
}



//
// Definitions ---------------------------------------------------------------------
//

// Hook Function Pointer
typedef HRESULT(__stdcall* EndSceneT)(IDirect3DDevice9* pDevice);
EndSceneT pD3D9_Endscene = nullptr;

// Addresses
void* D3D9_Graphics_Original_Address = 0;
void* D3D9_Graphics_Hook_Address = 0;

// Subhooks
subhook::Hook D3D9_Subhook;

// Fonts
LPD3DXFONT Extra_Small_Font_D3D9 = nullptr;
LPD3DXFONT Small_Font_D3D9 = nullptr;
LPD3DXFONT Small_Medium_Font_D3D9 = nullptr;
LPD3DXFONT Medium_Font_D3D9 = nullptr;
LPD3DXFONT Big_Medium_Font_D3D9 = nullptr;
LPD3DXFONT Big_Font_D3D9 = nullptr;
LPD3DXFONT Extra_Big_Font_D3D9 = nullptr;

// Colors
D3DCOLOR Red_D3D9 = D3DCOLOR_ARGB(255, 255, 0, 0);
D3DCOLOR Green_D3D9 = D3DCOLOR_ARGB(255, 0, 255, 0);
D3DCOLOR Blue_D3D9 = D3DCOLOR_ARGB(255, 0, 0, 255);
D3DCOLOR Black_D3D9 = D3DCOLOR_ARGB(255, 0, 0, 0);
D3DCOLOR White_D3D9 = D3DCOLOR_ARGB(255, 255, 255, 255);
D3DCOLOR Gray_D3D9 = D3DCOLOR_ARGB(255, 150, 150, 150);
D3DCOLOR Yellow_D3D9 = D3DCOLOR_ARGB(255, 255, 247, 0);
D3DCOLOR Purple_D3D9 = D3DCOLOR_ARGB(255, 170, 0, 255);
D3DCOLOR Pink_D3D9 = D3DCOLOR_ARGB(255, 255, 0, 221);
D3DCOLOR Orange_D3D9 = D3DCOLOR_ARGB(255, 255, 157, 0);
D3DCOLOR Cyan_D3D9 = D3DCOLOR_ARGB(255, 0, 255, 242);

struct VertexD3D9
{
    float x, y, z, rhw;
    float u, v;
};

//
// Drawing -------------------------------------------------------------------------
//

constexpr const char* pD3D9_TextureShader = R"(
float4 main(float2 texcoord : TEXCOORD0, sampler2D textureSampler : register(s0)) : COLOR
{
    float4 color = tex2D(textureSampler, texcoord);

    // Swap red and blue channels
    float temp = color.r;
    color.r = color.b;
    color.b = temp;
    return color;
}
)";

LPDIRECT3DVERTEXSHADER9 pD3D9_BackupVertexShader;
LPDIRECT3DPIXELSHADER9 pD3D9_BackupPixelShader;

LPDIRECT3DPIXELSHADER9 pD3D9_PixelShader;
LPDIRECT3DTEXTURE9 pD3D9_SurfaceTexture = nullptr;

/*
void BackUpOldStates_D3D9()
{
    pD3D9_Device->GetVertexShader(&pD3D9_BackupVertexShader);
    pD3D9_Device->GetPixelShader(&pD3D9_BackupPixelShader);
}

void RestoreOldStates_D3D9()
{
    pD3D9_Device->SetVertexShader(pD3D9_BackupVertexShader);
    pD3D9_Device->SetPixelShader(pD3D9_BackupPixelShader);
    if (pD3D9_BackupVertexShader != nullptr) pD3D9_BackupVertexShader->Release();
    if (pD3D9_BackupPixelShader != nullptr) pD3D9_BackupPixelShader->Release();
}

void ClearStates_D3D9()
{
    pD3D9_Device->SetVertexShader(nullptr);
    pD3D9_Device->SetPixelShader(nullptr);
}
*/

struct D3D9RenderStatesBackup
{
    IDirect3DVertexShader9* vertexShader;
    IDirect3DPixelShader9* pixelShader;
    DWORD renderStates[D3DRS_POINTSIZE_MAX];
    DWORD samplerStates[2][D3DSAMP_DMAPOFFSET + 1];
};

void BackUpOldStates_D3D9(D3D9RenderStatesBackup& backup)
{
    pD3D9_Device->GetVertexShader(&backup.vertexShader);
    pD3D9_Device->GetPixelShader(&backup.pixelShader);

    for (DWORD state = D3DRS_ZENABLE; state <= D3DRS_POINTSIZE_MAX; ++state)
    {
        pD3D9_Device->GetRenderState(static_cast<D3DRENDERSTATETYPE>(state), &backup.renderStates[state]);
    }

    for (DWORD state = D3DSAMP_ADDRESSU; state <= D3DSAMP_DMAPOFFSET; ++state)
    {
        pD3D9_Device->GetSamplerState(0, static_cast<D3DSAMPLERSTATETYPE>(state), &backup.samplerStates[0][state]);
        pD3D9_Device->GetSamplerState(1, static_cast<D3DSAMPLERSTATETYPE>(state), &backup.samplerStates[1][state]);
    }
}

void RestoreOldStates_D3D9(const D3D9RenderStatesBackup& backup)
{
    pD3D9_Device->SetVertexShader(backup.vertexShader);
    pD3D9_Device->SetPixelShader(backup.pixelShader);

    if (backup.vertexShader != nullptr) backup.vertexShader->Release();
    if (backup.pixelShader != nullptr) backup.pixelShader->Release();

    for (DWORD state = D3DRS_ZENABLE; state <= D3DRS_POINTSIZE_MAX; ++state)
    {
        pD3D9_Device->SetRenderState(static_cast<D3DRENDERSTATETYPE>(state), backup.renderStates[state]);
    }

    for (DWORD state = D3DSAMP_ADDRESSU; state <= D3DSAMP_DMAPOFFSET; ++state)
    {
        pD3D9_Device->SetSamplerState(0, static_cast<D3DSAMPLERSTATETYPE>(state), backup.samplerStates[0][state]);
        pD3D9_Device->SetSamplerState(1, static_cast<D3DSAMPLERSTATETYPE>(state), backup.samplerStates[1][state]);
    }
}

void ClearStates_D3D9()
{
    pD3D9_Device->SetVertexShader(nullptr);
    pD3D9_Device->SetPixelShader(nullptr);
    pD3D9_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pD3D9_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pD3D9_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    pD3D9_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
    pD3D9_Device->SetRenderState(D3DRS_ZENABLE, FALSE);
    pD3D9_Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    pD3D9_Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
    pD3D9_Device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
    pD3D9_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    pD3D9_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
    pD3D9_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    pD3D9_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    pD3D9_Device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
    pD3D9_Device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
    pD3D9_Device->SetRenderState(D3DRS_FOGENABLE, FALSE);
    pD3D9_Device->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
    pD3D9_Device->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
    pD3D9_Device->SetRenderState(D3DRS_CLIPPLANEENABLE, 0);
}

void Draw_D3D9()
{
    D3D9RenderStatesBackup RenderStatesBackup_D3D9 = D3D9RenderStatesBackup();
    BackUpOldStates_D3D9(RenderStatesBackup_D3D9);
    ClearStates_D3D9();

    HRESULT hr = 0;

    // Get resolution
    IDirect3DSurface9* backBuffer;
    pD3D9_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
    D3DSURFACE_DESC surfaceDesc;
    backBuffer->GetDesc(&surfaceDesc);
    backBuffer->Release();

    int x = 0;
    int y = 0;
    int w = surfaceDesc.Width;
    int h = surfaceDesc.Height;

    D3DLOCKED_RECT LockedRect;
    
    hr = pD3D9_SurfaceTexture->LockRect(0, &LockedRect, nullptr, D3DLOCK_DISCARD);

    unsigned char* pDest = reinterpret_cast<unsigned char*>(LockedRect.pBits);
    std::memcpy(pDest, SurfaceTextureRaw, SurfaceTextureDimension);
    pD3D9_SurfaceTexture->UnlockRect(0);

    pD3D9_Device->SetTexture(0, pD3D9_SurfaceTexture);

    VertexD3D9 vertices[4] = {
        {x, y, 0.0f, 1.0f, 0.0f, 1.0f},
        {x + w, y, 0.0f, 1.0f, 1.0f, 1.0f},
        {x, y + h, 0.0f, 1.0f, 0.0f, 0.0f},
        {x + w, y + h, 0.0f, 1.0f, 1.0f, 0.0f}
    };

    pD3D9_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
    pD3D9_Device->SetPixelShader(pD3D9_PixelShader);
    pD3D9_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(VertexD3D9));
    
    RestoreOldStates_D3D9(RenderStatesBackup_D3D9);
}

//
// Hook Routine ---------------------------------------------------------------------
//
typedef HRESULT(__stdcall* D3D9_PresentT)(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
template <typename FuncT>
class D3D9_PresentHook : public xNyuHook<D3D9_PresentT> {
public:
    static D3D9_PresentHook* instance;
    D3D9_PresentHook(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_PresentT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }

    static HRESULT APIENTRY CustomHook(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
    {
        if (DebugMenuInit)
        {
            pD3D9_Device = pDevice;

            HRESULT hr = 0;

            // Error buffer
            LPD3DXBUFFER pShaderBuffer = NULL;
            LPD3DXBUFFER pErrorBuffer = NULL;

            // Create Texture
            hr = D3DXCreateTexture(pD3D9_Device, SurfaceTextureWidth, SurfaceTextureHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &pD3D9_SurfaceTexture);
            if (FAILED(hr)) { DebugConsoleOutput("Error: D3DXCreateTexture()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }

            // Compile shader code
            hr = D3DXCompileShader(pD3D9_TextureShader, strlen(pD3D9_TextureShader), NULL, NULL, "main", "ps_2_0", 0, &pShaderBuffer, &pErrorBuffer, NULL);
            if (FAILED(hr)) { DebugConsoleOutput("Error: CompilePixelShader()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
            hr = pD3D9_Device->CreatePixelShader(reinterpret_cast<DWORD*>(pShaderBuffer->GetBufferPointer()), &pD3D9_PixelShader);
            if (FAILED(hr)) { DebugConsoleOutput("Error: CreatePixelShader()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }

            // Set DebugMenu function
            DebugDraw = (DebugDrawT)Draw_D3D9;

            // Deactivate DebugMenu
            DebugMenuInit = false;
            DebugConsoleOutput("DirectX 9 init success!", false, "green");
        }

        // Remove hook
        instance->remove();

        ThreadHookerUpdateThreads();

        // TAS routine
        if (GlobalSettings.config_tashook == "graphics")
        {
            pTASRoutine();
        }

        // Debug Menu
        DebugMenuMainRoutine();

        // Trampoline
        HRESULT Trampoline = instance->pFunction(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

        // Reinstall Hook
        instance->install();

        return Trampoline;
    }

    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};

D3D9_PresentHook<D3D9_PresentT>* D3D9_PresentHook<D3D9_PresentT>::instance = nullptr;

//
// Init function --------------------------------------------------------------------
//
BOOL D3D9HookInit()
{
    if (GetModuleHandleA("d3d9.dll") == NULL) return false;

    try {
        // I love to comments comments
        DebugConsoleOutput("DirectX 9 detected!", false, "green");

        // Get vTable
        Direct3D9Hooking::Direct3D9 D3D9Hookah;
        std::vector<uintptr_t> vTable = D3D9Hookah.vtable();

        // Set present hook
        D3D9_PresentHook<D3D9_PresentT>::instance = new D3D9_PresentHook<D3D9_PresentT>((void*)vTable[17]);
        D3D9_PresentHook<D3D9_PresentT>::instance->install();

        // Set other hooks
        D3D9_InitExtraHooks(vTable);

        return true;
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error when init D3D9:", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
    }

    return false;
}


bool D3D9HookUninit()
{
    return true;
}



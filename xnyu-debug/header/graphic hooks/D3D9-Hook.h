/*
MIT License
Copyright (c) 2018 Benjamin Höglinger
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#include <DXErr.h>
#pragma comment(lib, "DXErr.lib")



namespace Direct3D9Hooking
{
    enum Direct3DDevice9FunctionOrdinals : short
    {
        QueryInterface = 0,
        AddRef = 1,
        Release = 2,
        TestCooperativeLevel = 3,
        GetAvailableTextureMem = 4,
        EvictManagedResources = 5,
        GetDirect3D = 6,
        GetDeviceCaps = 7,
        GetDisplayMode = 8,
        GetCreationParameters = 9,
        SetCursorProperties = 10,
        SetCursorPosition = 11,
        ShowCursor = 12,
        CreateAdditionalSwapChain = 13,
        GetSwapChain = 14,
        GetNumberOfSwapChains = 15,
        Reset = 16,
        Present = 17,
        GetBackBuffer = 18,
        GetRasterStatus = 19,
        SetDialogBoxMode = 20,
        SetGammaRamp = 21,
        GetGammaRamp = 22,
        CreateTexture = 23,
        CreateVolumeTexture = 24,
        CreateCubeTexture = 25,
        CreateVertexBuffer = 26,
        CreateIndexBuffer = 27,
        CreateRenderTarget = 28,
        CreateDepthStencilSurface = 29,
        UpdateSurface = 30,
        UpdateTexture = 31,
        GetRenderTargetData = 32,
        GetFrontBufferData = 33,
        StretchRect = 34,
        ColorFill = 35,
        CreateOffscreenPlainSurface = 36,
        SetRenderTarget = 37,
        GetRenderTarget = 38,
        SetDepthStencilSurface = 39,
        GetDepthStencilSurface = 40,
        BeginScene = 41,
        EndScene = 42,
        Clear = 43,
        SetTransform = 44,
        GetTransform = 45,
        MultiplyTransform = 46,
        SetViewport = 47,
        GetViewport = 48,
        SetMaterial = 49,
        GetMaterial = 50,
        SetLight = 51,
        GetLight = 52,
        LightEnable = 53,
        GetLightEnable = 54,
        SetClipPlane = 55,
        GetClipPlane = 56,
        SetRenderState = 57,
        GetRenderState = 58,
        CreateStateBlock = 59,
        BeginStateBlock = 60,
        EndStateBlock = 61,
        SetClipStatus = 62,
        GetClipStatus = 63,
        GetTexture = 64,
        SetTexture = 65,
        GetTextureStageState = 66,
        SetTextureStageState = 67,
        GetSamplerState = 68,
        SetSamplerState = 69,
        ValidateDevice = 70,
        SetPaletteEntries = 71,
        GetPaletteEntries = 72,
        SetCurrentTexturePalette = 73,
        GetCurrentTexturePalette = 74,
        SetScissorRect = 75,
        GetScissorRect = 76,
        SetSoftwareVertexProcessing = 77,
        GetSoftwareVertexProcessing = 78,
        SetNPatchMode = 79,
        GetNPatchMode = 80,
        DrawPrimitive = 81,
        DrawIndexedPrimitive = 82,
        DrawPrimitiveUP = 83,
        DrawIndexedPrimitiveUP = 84,
        ProcessVertices = 85,
        CreateVertexDeclaration = 86,
        SetVertexDeclaration = 87,
        GetVertexDeclaration = 88,
        SetFVF = 89,
        GetFVF = 90,
        CreateVertexShader = 91,
        SetVertexShader = 92,
        GetVertexShader = 93,
        SetVertexShaderConstantF = 94,
        GetVertexShaderConstantF = 95,
        SetVertexShaderConstantI = 96,
        GetVertexShaderConstantI = 97,
        SetVertexShaderConstantB = 98,
        GetVertexShaderConstantB = 99,
        SetStreamSource = 100,
        GetStreamSource = 101,
        SetStreamSourceFreq = 102,
        GetStreamSourceFreq = 103,
        SetIndices = 104,
        GetIndices = 105,
        CreatePixelShader = 106,
        SetPixelShader = 107,
        GetPixelShader = 108,
        SetPixelShaderConstantF = 109,
        GetPixelShaderConstantF = 110,
        SetPixelShaderConstantI = 111,
        GetPixelShaderConstantI = 112,
        SetPixelShaderConstantB = 113,
        GetPixelShaderConstantB = 114,
        DrawRectPatch = 115,
        DrawTriPatch = 116,
        DeletePatch = 117,
        CreateQuery = 118,
    };

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

// EndScene() Function Pointer
typedef HRESULT(__stdcall* EndSceneT)(IDirect3DDevice9* pDevice);
EndSceneT pD3D9_Endscene = nullptr;

// Addresses
void* D3D9_Endscene_Original_Address = 0;
void* D3D9_Endscene_Hook_Address = 0;

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

void ClearOldStates_D3D9()
{
    pD3D9_Device->SetVertexShader(nullptr);
    pD3D9_Device->SetPixelShader(nullptr);
}

void Draw_D3D9()
{
    BackUpOldStates_D3D9();
    ClearOldStates_D3D9();

    HRESULT hr = 0;

    int x = 0;
    int y = 0;
    int w = SurfaceTextureWidth;
    int h = SurfaceTextureHeight;

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
    pD3D9_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    pD3D9_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pD3D9_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    pD3D9_Device->SetRenderState(D3DRS_ZENABLE, FALSE);
    pD3D9_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    pD3D9_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(VertexD3D9));
    pD3D9_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    pD3D9_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
    
    ClearOldStates_D3D9();
}



//
// Technical function --------------------------------------------------------------------
//






//
// Hook Routine ---------------------------------------------------------------------
//
HRESULT APIENTRY D3D9_Endscene_Hook(IDirect3DDevice9* pDevice)
{
    if (DebugMenuInit)
    {
        // Set the device for the globals
        pD3D9_Device = pDevice;

        HRESULT hr = 0;

        LPD3DXBUFFER pShaderBuffer = NULL;
        LPD3DXBUFFER pErrorBuffer = NULL;

        // Create Texture
        hr = D3DXCreateTexture(pD3D9_Device, SurfaceTextureWidth, SurfaceTextureHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &pD3D9_SurfaceTexture);
        if (FAILED(hr)) { DebugConsoleOutput("Error: D3DXCreateTexture()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }

        // Compile the shader code
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
    D3D9_Subhook.Remove();

    // Trampoline
    HRESULT Trampoline = pD3D9_Endscene(pDevice);

    // Reinstall Hook
    if (sizeof(void*) == 8) D3D9_Subhook.Install(D3D9_Endscene_Original_Address, D3D9_Endscene_Hook_Address, subhook::HookFlags::HookFlag64BitOffset);
    if (sizeof(void*) == 4) D3D9_Subhook.Install(D3D9_Endscene_Original_Address, D3D9_Endscene_Hook_Address);

    // Check frameskip
    GlobalFrameSkipCurrent++;
    if (GlobalFrameSkipCurrent >= GlobalSettings.config_frame_skip)
    {
        // TAS
        PlayScriptRoutine();
        RecordScriptRoutine();
        GlobalFrameSkipCurrent = 0;
    }

    // Debug Menu
    DebugMenuMainRoutine();

    return Trampoline;
}



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

        // Set addresses
        D3D9_Endscene_Original_Address = (void*)vTable[42];
        D3D9_Endscene_Hook_Address = D3D9_Endscene_Hook;
        pD3D9_Endscene = (EndSceneT)D3D9_Endscene_Original_Address;

        // Install the Hook
        if (sizeof(void*) == 8) return D3D9_Subhook.Install(D3D9_Endscene_Original_Address, D3D9_Endscene_Hook_Address, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) return D3D9_Subhook.Install(D3D9_Endscene_Original_Address, D3D9_Endscene_Hook_Address);

        return false;
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error when init D3D9:", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
    }

    return false;
}



#include "pch.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Conversions.h"
#include "D3D9-Extra-Hooks.h"
#include "Logging.h"
#include "xNyuHook.h"
#include "DrawingEssentials.h"
#include "D3D9-Hook.h"



// --- Variables ---
IDirect3DDevice9* D3D9_Device = nullptr;

const char* D3D9_TextureShader = R"(
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

LPDIRECT3DVERTEXSHADER9 D3D9_BackupVertexShader = nullptr;
LPDIRECT3DPIXELSHADER9 D3D9_BackupPixelShader = nullptr;
LPDIRECT3DPIXELSHADER9 D3D9_PixelShader = nullptr;
LPDIRECT3DTEXTURE9 D3D9_SurfaceTexture = nullptr;



// --- Hook ---
D3D9_PresentHook<D3D9_PresentT>* D3D9_PresentHook<D3D9_PresentT>::instance = nullptr;



// --- Functions ---
std::vector<uintptr_t> GetVTable_D3D9()
{
    // Create throw away window
    WNDCLASSEX tmpWindowClass{};
    HWND tmpWindow;
    ZeroMemory(&tmpWindowClass, sizeof(WNDCLASSEX));
    tmpWindowClass.cbSize = sizeof(WNDCLASSEX);
    tmpWindowClass.style = CS_HREDRAW | CS_VREDRAW;
    tmpWindowClass.lpfnWndProc = DefWindowProc;
    tmpWindowClass.lpszClassName = s2ws("ThrowAwayWindow").c_str();
    tmpWindowClass.hInstance = GetModuleHandle(nullptr);
    tmpWindow = CreateWindow(tmpWindowClass.lpszClassName, L"ThrowAwayWindow", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, tmpWindowClass.hInstance, NULL);

    // Create D3D9 device
    const auto hMod = GetModuleHandleA("d3d9.dll");
    const auto Direct3DCreate9 = static_cast<LPVOID>(GetProcAddress(hMod, "Direct3DCreate9"));
    IDirect3D9* d3d9 = static_cast<LPDIRECT3D9(WINAPI*)(UINT)>(Direct3DCreate9)(D3D_SDK_VERSION);
    D3DDISPLAYMODE display_mode;
    const auto hr = d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display_mode);
    D3DPRESENT_PARAMETERS present_parameters;
    ZeroMemory(&present_parameters, sizeof(D3DPRESENT_PARAMETERS));
    present_parameters.Windowed = TRUE;
    present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    present_parameters.BackBufferFormat = display_mode.Format;
    const auto error_code = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, tmpWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &present_parameters, &D3D9_Device);

    // Clean up window
    DestroyWindow(tmpWindow);
    UnregisterClass(tmpWindowClass.lpszClassName, tmpWindowClass.hInstance);

    // Return VTable
    return std::vector<uintptr_t>(*reinterpret_cast<uintptr_t**>(D3D9_Device), *reinterpret_cast<uintptr_t**>(D3D9_Device) + 119);
}

void BackUpOldStates_D3D9(D3D9RenderStatesBackup& backup)
{
    D3D9_Device->GetVertexShader(&backup.vertexShader);
    D3D9_Device->GetPixelShader(&backup.pixelShader);

    for (DWORD state = D3DRS_ZENABLE; state <= D3DRS_POINTSIZE_MAX; ++state)
    {
        D3D9_Device->GetRenderState(static_cast<D3DRENDERSTATETYPE>(state), &backup.renderStates[state]);
    }

    for (DWORD state = D3DSAMP_ADDRESSU; state <= D3DSAMP_DMAPOFFSET; ++state)
    {
        D3D9_Device->GetSamplerState(0, static_cast<D3DSAMPLERSTATETYPE>(state), &backup.samplerStates[0][state]);
        D3D9_Device->GetSamplerState(1, static_cast<D3DSAMPLERSTATETYPE>(state), &backup.samplerStates[1][state]);
    }
}

void RestoreOldStates_D3D9(const D3D9RenderStatesBackup& backup)
{
    D3D9_Device->SetVertexShader(backup.vertexShader);
    D3D9_Device->SetPixelShader(backup.pixelShader);

    if (backup.vertexShader != nullptr) backup.vertexShader->Release();
    if (backup.pixelShader != nullptr) backup.pixelShader->Release();

    for (DWORD state = D3DRS_ZENABLE; state <= D3DRS_POINTSIZE_MAX; ++state)
    {
        D3D9_Device->SetRenderState(static_cast<D3DRENDERSTATETYPE>(state), backup.renderStates[state]);
    }

    for (DWORD state = D3DSAMP_ADDRESSU; state <= D3DSAMP_DMAPOFFSET; ++state)
    {
        D3D9_Device->SetSamplerState(0, static_cast<D3DSAMPLERSTATETYPE>(state), backup.samplerStates[0][state]);
        D3D9_Device->SetSamplerState(1, static_cast<D3DSAMPLERSTATETYPE>(state), backup.samplerStates[1][state]);
    }
}

void ClearStates_D3D9()
{
    D3D9_Device->SetVertexShader(nullptr);
    D3D9_Device->SetPixelShader(nullptr);
    D3D9_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    D3D9_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    D3D9_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    D3D9_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
    D3D9_Device->SetRenderState(D3DRS_ZENABLE, FALSE);
    D3D9_Device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    D3D9_Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
    D3D9_Device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
    D3D9_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    D3D9_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
    D3D9_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    D3D9_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    D3D9_Device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
    D3D9_Device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
    D3D9_Device->SetRenderState(D3DRS_FOGENABLE, FALSE);
    D3D9_Device->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
    D3D9_Device->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
    D3D9_Device->SetRenderState(D3DRS_CLIPPLANEENABLE, 0);
}

void Draw_D3D9()
{
    D3D9RenderStatesBackup RenderStatesBackup_D3D9 = D3D9RenderStatesBackup();
    BackUpOldStates_D3D9(RenderStatesBackup_D3D9);
    ClearStates_D3D9();

    HRESULT hr = 0;

    // Get resolution
    IDirect3DSurface9* backBuffer;
    D3D9_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
    D3DSURFACE_DESC surfaceDesc;
    backBuffer->GetDesc(&surfaceDesc);
    backBuffer->Release();

    int x = 0;
    int y = 0;
    int w = surfaceDesc.Width;
    int h = surfaceDesc.Height;

    D3DLOCKED_RECT LockedRect;

    hr = D3D9_SurfaceTexture->LockRect(0, &LockedRect, nullptr, D3DLOCK_DISCARD);

    unsigned char* pDest = reinterpret_cast<unsigned char*>(LockedRect.pBits);
    std::memcpy(pDest, SurfaceTextureRaw, SurfaceTextureDimension);
    D3D9_SurfaceTexture->UnlockRect(0);

    D3D9_Device->SetTexture(0, D3D9_SurfaceTexture);

    VertexD3D9 vertices[4] = {
        {x, y, 0.0f, 1.0f, 0.0f, 1.0f},
        {x + w, y, 0.0f, 1.0f, 1.0f, 1.0f},
        {x, y + h, 0.0f, 1.0f, 0.0f, 0.0f},
        {x + w, y + h, 0.0f, 1.0f, 1.0f, 0.0f}
    };

    D3D9_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
    D3D9_Device->SetPixelShader(D3D9_PixelShader);
    D3D9_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(VertexD3D9));

    RestoreOldStates_D3D9(RenderStatesBackup_D3D9);
}

bool HookInit_D3D9()
{
    if (GetModuleHandleA("d3d9.dll") == NULL) return false;

    try
    {
        DebugConsoleOutput("DirectX 9 detected!", false, "green");

        // Get vTable
        std::vector<uintptr_t> vTable = GetVTable_D3D9();

        if (!D3D9_PresentHook<D3D9_PresentT>::instance) D3D9_PresentHook<D3D9_PresentT>::instance = new D3D9_PresentHook<D3D9_PresentT>((void*)vTable[17]);
        D3D9_PresentHook<D3D9_PresentT>::instance->install();

        // Set other hooks
        //D3D9_InitExtraHooks(vTable);

        return true;
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error when init D3D9:", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
    }

    return false;
}

bool HookUninit_D3D9()
{
    if (D3D9_PresentHook<D3D9_PresentT>::instance && D3D9_PresentHook<D3D9_PresentT>::instance->isActive()) D3D9_PresentHook<D3D9_PresentT>::instance->remove();
    return true;
}



#include "pch.h"

#include <d3d10.h>
///#include <d3d10_1.h>
//#include <d3dx10.h>
//#include <d3dcommon.h>
//#include <D3Dcompiler.h>
//#include <dxgiformat.h>
#pragma comment (lib, "d3d10.lib")
//#pragma comment (lib, "d3d10_1.lib")
//#pragma comment (lib, "d3dx10.lib")
//#pragma comment (lib, "D3Dcompiler.lib")

#include "Conversions.h"
#include "Logging.h"
#include "xNyuHook.h"
#include "DrawingEssentials.h"
#include "D3D10-Hook.h"



// --- Variables ---
ID3D10Device* D3D10_Device = nullptr;
IDXGISwapChain* D3D10_SwapChain = nullptr;

D3D10_INPUT_ELEMENT_DESC D3D10_TextureLayoutDesc[];
UINT D3D10_TextureLayoutElements = 0;
ID3D10InputLayout* D3D10_TextureLayout = nullptr;

D3D10_TEXTURE2D_DESC D3D10_TextureDesc;
ID3D10Texture2D* D3D10_Texture = nullptr;
ID3D10ShaderResourceView* D3D10_TextureSRV = nullptr;

D3D10_BUFFER_DESC D3D10_VertexBufferDesc;
ID3D10Buffer* D3D10_VertexBuffer = nullptr;

ID3D10PixelShader* D3D10_PixelShader = nullptr;
ID3D10VertexShader* D3D10_VertexShader = nullptr;

const char* D3D10_TextureShader = R"(
Texture2D textureSampler : register(t0);
SamplerState samplerState : register(s0);

struct VertexInputType
{
    float4 position : POSITION;
    float2 texcoord : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
};

PixelInputType VertexShader(VertexInputType input)
{
    PixelInputType output;
    output.position = input.position; // Assuming position is already in clip space
    output.texcoord = input.texcoord;
    return output;
}

float4 PixelShader(PixelInputType input) : SV_TARGET
{
    float4 color = textureSampler.Sample(samplerState, input.texcoord);
    // Swap red and blue channels
    float temp = color.r;
    color.r = color.b;
    color.b = temp;
    return color;
}
)";



// --- Hook ---
D3D10_PresentHook<D3D10_PresentT>* D3D10_PresentHook<D3D10_PresentT>::instance = nullptr;



// --- Functions ---
std::vector<uintptr_t> GetVTable_D3D10()
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

    // Create D3D10 device
    HMODULE hModDXGI = GetModuleHandleA("DXGI.dll");
    HMODULE hModD3D10 = GetModuleHandleA("D3D10.dll");
    const LPVOID hCreateDXGIFactory = static_cast<LPVOID>(GetProcAddress(hModDXGI, "CreateDXGIFactory"));
    IDXGIFactory* pFactory;
    const auto hr = static_cast<HRESULT(WINAPI*)(REFIID,void** ppFactory)>(hCreateDXGIFactory)(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory));
    const auto hD3D10CreateDeviceAndSwapChain = static_cast<LPVOID>(GetProcAddress( hModD3D10, "D3D10CreateDeviceAndSwapChain"));
    UINT i = 0;
    IDXGIAdapter* pAdapter;
    std::vector<IDXGIAdapter*> vAdapters;
    while (pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND)
    {
        vAdapters.push_back(pAdapter);
        i++;
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
    scDesc.OutputWindow = tmpWindow;
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.SampleDesc = sampleDesc;
    scDesc.BufferDesc = modeDesc;
    const auto hr10 = static_cast<HRESULT(WINAPI*)(IDXGIAdapter*, D3D10_DRIVER_TYPE, HMODULE, UINT, UINT, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**, ID3D10Device**)>(hD3D10CreateDeviceAndSwapChain)(vAdapters[0], D3D10_DRIVER_TYPE_HARDWARE, nullptr, 0, D3D10_SDK_VERSION, &scDesc, &D3D10_SwapChain, &D3D10_Device);

    // Clean up window
    DestroyWindow(tmpWindow);
    UnregisterClass(tmpWindowClass.lpszClassName, tmpWindowClass.hInstance);

    // Return VTable
    return std::vector<uintptr_t>(*reinterpret_cast<uintptr_t**>(D3D10_SwapChain), *reinterpret_cast<uintptr_t**>(D3D10_SwapChain) + 98);
}

void BackUpOldStates_D3D10(D3D10RenderStatesBackup& backup)
{
    D3D10_Device->OMGetBlendState(&backup.blendState, backup.blendFactor, &backup.sampleMask);
    D3D10_Device->OMGetDepthStencilState(&backup.depthStencilState, &backup.stencilRef);
    D3D10_Device->RSGetState(&backup.rasterizerState);
    D3D10_Device->VSGetShader(&backup.vertexShader);
    D3D10_Device->PSGetShader(&backup.pixelShader);
    D3D10_Device->PSGetSamplers(0, 1, backup.samplerState);
    D3D10_Device->GSGetShader(&backup.geometryShader);
    D3D10_Device->IAGetInputLayout(&backup.inputLayout);
    backup.numViewports = D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
    D3D10_Device->RSGetViewports(&backup.numViewports, backup.viewports);
    for (UINT i = 0; i < D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) D3D10_Device->OMGetRenderTargets(1, &backup.renderTargetViews[i], &backup.depthStencilView);
    D3D10_Device->PSGetSamplers(0, 4, backup.samplerState);
}

void RestoreOldStates_D3D10(const D3D10RenderStatesBackup& backup)
{
    D3D10_Device->OMSetBlendState(backup.blendState, backup.blendFactor, backup.sampleMask);
    if (backup.blendState) backup.blendState->Release();

    D3D10_Device->OMSetDepthStencilState(backup.depthStencilState, backup.stencilRef);
    if (backup.depthStencilState) backup.depthStencilState->Release();

    D3D10_Device->RSSetState(backup.rasterizerState);
    if (backup.rasterizerState) backup.rasterizerState->Release();

    D3D10_Device->VSSetShader(backup.vertexShader);
    if (backup.vertexShader) backup.vertexShader->Release();

    D3D10_Device->PSSetShader(backup.pixelShader);
    if (backup.pixelShader) backup.pixelShader->Release();

    D3D10_Device->PSSetSamplers(0, 1, backup.samplerState);
    for (int i = 0; i < 4; i++) if (backup.samplerState && backup.samplerState[i]) backup.samplerState[i]->Release();

    D3D10_Device->GSSetShader(backup.geometryShader);
    if (backup.geometryShader) backup.geometryShader->Release();

    D3D10_Device->IASetInputLayout(backup.inputLayout);
    if (backup.inputLayout) backup.inputLayout->Release();

    D3D10_Device->RSSetViewports(backup.numViewports, backup.viewports);

    for (UINT i = 0; i < D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
    {
        D3D10_Device->OMSetRenderTargets(1, &backup.renderTargetViews[i], backup.depthStencilView);
        if (backup.renderTargetViews[i]) backup.renderTargetViews[i]->Release();
    }
    if (backup.depthStencilView) backup.depthStencilView->Release();

    D3D10_Device->PSSetSamplers(0, 4, backup.samplerState);
}

void ClearStates_D3D10()
{
    D3D10_Device->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
    D3D10_Device->OMSetDepthStencilState(nullptr, 0);
    D3D10_Device->RSSetState(nullptr);
    D3D10_Device->VSSetShader(nullptr);
    D3D10_Device->GSSetShader(nullptr);
    D3D10_Device->PSSetShader(nullptr);
    D3D10_Device->IASetInputLayout(nullptr);
    D3D10_Device->RSSetViewports(0, nullptr);
    D3D10_Device->OMSetRenderTargets(0, nullptr, nullptr);
    D3D10_Device->PSSetSamplers(0, 4, nullptr); // Adjust the count as needed
}

void Draw_D3D10()
{
    D3D10RenderStatesBackup RenderStatesBackup_D3D10 = D3D10RenderStatesBackup();
    BackUpOldStates_D3D10(RenderStatesBackup_D3D10);
    ClearStates_D3D10();

    // Get resolution
    IDXGISurface1* backBuffer = nullptr;
    D3D10_SwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&backBuffer);
    DXGI_SURFACE_DESC surfaceDesc;
    backBuffer->GetDesc(&surfaceDesc);
    backBuffer->Release();

    int x = 0;
    int y = 0;
    int w = surfaceDesc.Width;
    int h = surfaceDesc.Height;

    // Image data to texture
    D3D10_MAPPED_TEXTURE2D mappedTex;
    D3D10_Texture->Map(0, D3D10_MAP_WRITE_DISCARD, 0, &mappedTex);
    unsigned char* pDest = reinterpret_cast<unsigned char*>(mappedTex.pData);
    for (UINT row = 0; row < D3D10_TextureDesc.Height; ++row) memcpy(pDest + row * mappedTex.RowPitch, SurfaceTextureRaw + row * SurfaceTextureWidth * 4, SurfaceTextureWidth * 4);
    D3D10_Texture->Unmap(0);

    // Create vertices
    VertexD3D10 vertices[4] =
    {
        {x, y, 0.0f, 1.0f, 0.0f, 1.0f},
        {x + w, y, 0.0f, 1.0f, 1.0f, 1.0f},
        {x, y + h, 0.0f, 1.0f, 0.0f, 0.0f},
        {x + w, y + h, 0.0f, 1.0f, 1.0f, 0.0f}
    };

    // Vertices to vertex buffer
    void* pData = nullptr;
    D3D10_VertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, &pData);
    memcpy(pData, vertices, sizeof(vertices));
    D3D10_VertexBuffer->Unmap();

    // Set input layout, shaders, and resources
    D3D10_Device->IASetInputLayout(D3D10_TextureLayout);
    D3D10_Device->VSSetShader(D3D10_VertexShader);
    D3D10_Device->PSSetShader(D3D10_PixelShader);
    D3D10_Device->PSSetShaderResources(0, 1, &D3D10_TextureSRV);

    // Draw
    UINT stride = sizeof(VertexD3D10);
    UINT offset = 0;
    D3D10_Device->IASetVertexBuffers(0, 1, &D3D10_VertexBuffer, &stride, &offset);
    D3D10_Device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    D3D10_Device->Draw(4, 0);

    RestoreOldStates_D3D10(RenderStatesBackup_D3D10);
}

bool HookInit_D3D10()
{
    if (GetModuleHandleA("d3d10.dll") == NULL) return false;

    try
    {
        DebugConsoleOutput("DirectX 10 detected!", false, "green");

        // Get vTable
        std::vector<uintptr_t> vTable = GetVTable_D3D10();

        if (!D3D10_PresentHook<D3D10_PresentT>::instance) D3D10_PresentHook<D3D10_PresentT>::instance = new D3D10_PresentHook<D3D10_PresentT>((void*)vTable[18]);
        D3D10_PresentHook<D3D10_PresentT>::instance->install();

        // Set other hooks
        //D3D10_InitExtraHooks(vTable);

        return true;
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error when init D3D10:", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
    }

    return false;
}


bool HookUninit_D3D10()
{
    if (D3D10_PresentHook<D3D10_PresentT>::instance && D3D10_PresentHook<D3D10_PresentT>::instance->isActive()) D3D10_PresentHook<D3D10_PresentT>::instance->remove();
    return true;
}



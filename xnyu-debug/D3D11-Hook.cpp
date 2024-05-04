#include "pch.h"

#include <d3d11.h>
// #include <D3DX11.h>
// #include <d2d1_1.h>
// #include <dxgi1_2.h>
// #include <d3dcompiler.h>
// #include <wchar.h>
#include <DXErr.h>
#pragma comment (lib, "d3d11.lib")
// #pragma comment (lib, "D3DX11.lib")
// #pragma comment(lib, "d2d1.lib")
// #pragma comment(lib, "dxgi.lib")
// #pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "DXErr.lib")
// #pragma comment(lib, "legacy_stdio_definitions.lib")

#include "Conversions.h"
#include "Logging.h"
#include "xNyuHook.h"
#include "DrawingEssentials.h"
#include "D3D11-Hook.h"



// --- Typedefs ---
D3D11_PresentHook<D3D11_PresentT>* D3D11_PresentHook<D3D11_PresentT>::instance = nullptr;



// --- Variables ---
extern IDXGISwapChain* D3D11_SwapChain = nullptr;
extern IDXGISurface* D3D11_Surface = nullptr;
extern ID3D11Device* D3D11_Device = nullptr;
extern ID3D11DeviceContext* D3D11_DeviceContext = nullptr;

extern ID3D11VertexShader* D3D11_VertexShader = nullptr;
extern ID3D11InputLayout* D3D11_VertexLayout = nullptr;
extern ID3D11PixelShader* D3D11_PixelShader = nullptr;
extern ID3D11Buffer* D3D11_VertexBuffer = nullptr;
extern ID3D11Buffer* D3D11_IndexBuffer = nullptr;
extern ID3D11Buffer* D3D11_ConstantBuffer = nullptr;
extern ID3D11SamplerState* D3D11_SamplerState = nullptr;
extern XMMATRIX D3D11_OrthographicProjectionMatrix;
extern VertexD3D11 D3D11_Verts[4];
extern D3D11_BUFFER_DESC D3D11_BufferVertexDesc;
extern D3D11_SUBRESOURCE_DATA D3D11_BufferVertexSubresourceLine;
extern UINT D3D11_StrideVertex = sizeof(VertexD3D11);
extern UINT D3D11_OffsetVertex = 0;
extern D3D11_SAMPLER_DESC D3D11_SamplerDesc;
extern D3D11_TEXTURE2D_DESC D3D11_TextureDesc;
extern D3D11_SUBRESOURCE_DATA D3D11_TextureData;
extern D3D11_SHADER_RESOURCE_VIEW_DESC D3D11_ViewDesc;
extern D3D11_INPUT_ELEMENT_DESC D3D11_Layout[2];

extern HWND D3D11_Window = nullptr;
extern ID3D11DeviceContext* D3D11_DeviceContext = nullptr;
extern ID3D11RenderTargetView* D3D11_RenderTargetView = nullptr;
extern ID3D11DepthStencilView* D3D11_DepthStencilView;
extern D3D11_VIEWPORT D3D11_Viewport;
extern D3D11_VIEWPORT D3D11_CustomViewport;
extern D3D11_BLEND_DESC D3D11_BlendDesc;
extern ID3D11BlendState* D3D11_BlendState = nullptr;
extern float D3D11_BlendFactor[4];
extern UINT D3D11_SampleMask = 0;
extern D3D11_DEPTH_STENCIL_DESC D3D11_DepthStencilDesc;
extern ID3D11DepthStencilState* D3D11_DepthStencilState = nullptr;

const char* D3D11_TextureShader = R"(
cbuffer ConstantBuffer : register(b0)
{
    matrix projection;
};

Texture2D shaderTexture : register(t0);
sampler sam : register(s0);

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

PixelInput VS(float4 pos : POSITION, float2 texCoord : TEXCOORD)
{
    PixelInput output;
    output.pos = mul( projection, pos );
    output.texCoord = texCoord;
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 texColor = shaderTexture.Sample(sam, input.texCoord);
    return float4(texColor.rgb, texColor.a);
}
)";



// --- Functions ---
std::vector<uintptr_t> GetVTable_D3D11()
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

    // Create D3D11 device
    const auto hModDXGI = GetModuleHandleA("DXGI.dll");
    const auto hModD3D11 = GetModuleHandleA("D3D11.dll");
    DXGI_SWAP_CHAIN_DESC sd;
    {
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = tmpWindow;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    }
    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[3] = { D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0 };
    const auto hD3D11CreateDeviceAndSwapChain = static_cast<LPVOID>(GetProcAddress(hModD3D11, "D3D11CreateDeviceAndSwapChain"));
    const auto hr11 = static_cast<HRESULT(WINAPI*)(IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT, const D3D_FEATURE_LEVEL*, UINT, UINT, const DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**, ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**)>(hD3D11CreateDeviceAndSwapChain)( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 1, D3D11_SDK_VERSION, &sd, &D3D11_SwapChain, &D3D11_Device, &featureLevel, &D3D11_DeviceContext);

    // Clean up window
    DestroyWindow(tmpWindow);
    UnregisterClass(tmpWindowClass.lpszClassName, tmpWindowClass.hInstance);

    // Return VTable
    return std::vector<uintptr_t>(*reinterpret_cast<uintptr_t**>(D3D11_SwapChain), *reinterpret_cast<uintptr_t**>(D3D11_SwapChain) + 18);
}

void BackUpOldStates_D3D11(D3D11RenderStatesBackup& backup)
{
    D3D11_DeviceContext->IAGetInputLayout(&backup.inputLayout);
    D3D11_DeviceContext->IAGetPrimitiveTopology(&backup.topology);
    D3D11_DeviceContext->IAGetVertexBuffers(0, 1, &backup.vertexBuffer, &backup.vertexBufferStride, &backup.vertexBufferOffset);
    D3D11_DeviceContext->IAGetIndexBuffer(&backup.indexBuffer, &backup.indexBufferFormat, &backup.indexBufferOffset);
    D3D11_DeviceContext->VSGetShader(&backup.vertexShader, nullptr, &backup.vertexShaderNumClassInstances);
    D3D11_DeviceContext->VSGetConstantBuffers(0, 1, &backup.constantBuffer);
    D3D11_DeviceContext->PSGetShader(&backup.pixelShader, nullptr, &backup.pixelShaderNumClassInstances);
    D3D11_DeviceContext->PSGetConstantBuffers(0, 1, &backup.pixelConstantBuffer);
    D3D11_DeviceContext->PSGetShaderResources(0, 1, &backup.shaderResourceView);
    D3D11_DeviceContext->PSGetSamplers(0, 1, &backup.sampler);
    D3D11_DeviceContext->RSGetViewports(&backup.numViewports, &backup.viewport);
    D3D11_DeviceContext->RSGetScissorRects(&backup.numScissorRects, &backup.scissorRect);
    D3D11_DeviceContext->RSGetState(&backup.rasterizerState);
    D3D11_DeviceContext->OMGetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, backup.renderTargetView, &backup.depthStencilView);
    D3D11_DeviceContext->OMGetBlendState(&backup.blendState, backup.blendFactor, &backup.sampleMask);
    D3D11_DeviceContext->OMGetDepthStencilState(&backup.depthStencilState, &backup.stencilRef);
}

void RestoreOldStates_D3D11(D3D11RenderStatesBackup& backup)
{
    D3D11_DeviceContext->IASetInputLayout(backup.inputLayout);
    D3D11_DeviceContext->IASetPrimitiveTopology(backup.topology);
    D3D11_DeviceContext->IASetVertexBuffers(0, 1, &backup.vertexBuffer, &backup.vertexBufferStride, &backup.vertexBufferOffset);
    D3D11_DeviceContext->IASetIndexBuffer(backup.indexBuffer, backup.indexBufferFormat, backup.indexBufferOffset);
    D3D11_DeviceContext->VSSetShader(backup.vertexShader, nullptr, backup.vertexShaderNumClassInstances);
    D3D11_DeviceContext->VSSetConstantBuffers(0, 1, &backup.constantBuffer);
    D3D11_DeviceContext->PSSetShader(backup.pixelShader, nullptr, backup.pixelShaderNumClassInstances);
    D3D11_DeviceContext->PSSetConstantBuffers(0, 1, &backup.pixelConstantBuffer);
    D3D11_DeviceContext->PSSetShaderResources(0, 1, &backup.shaderResourceView);
    D3D11_DeviceContext->PSSetSamplers(0, 1, &backup.sampler);
    D3D11_DeviceContext->RSSetViewports(backup.numViewports, &backup.viewport);
    D3D11_DeviceContext->RSSetScissorRects(backup.numScissorRects, &backup.scissorRect);
    D3D11_DeviceContext->RSSetState(backup.rasterizerState);
    D3D11_DeviceContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, backup.renderTargetView, backup.depthStencilView);
    D3D11_DeviceContext->OMSetBlendState(backup.blendState, backup.blendFactor, backup.sampleMask);
    D3D11_DeviceContext->OMSetDepthStencilState(backup.depthStencilState, backup.stencilRef);

    if (backup.inputLayout != nullptr) backup.inputLayout->Release();
    if (backup.vertexBuffer != nullptr) backup.vertexBuffer->Release();
    if (backup.indexBuffer != nullptr) backup.indexBuffer->Release();
    if (backup.vertexShader != nullptr) backup.vertexShader->Release();
    if (backup.constantBuffer != nullptr) backup.constantBuffer->Release();
    if (backup.pixelShader != nullptr) backup.pixelShader->Release();
    if (backup.pixelConstantBuffer != nullptr) backup.pixelConstantBuffer->Release();
    if (backup.shaderResourceView != nullptr) backup.shaderResourceView->Release();
    if (backup.sampler != nullptr) backup.sampler->Release();
    if (backup.rasterizerState != nullptr) backup.rasterizerState->Release();
    for (UINT i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) if (backup.renderTargetView[i] != nullptr) backup.renderTargetView[i]->Release();
    if (backup.depthStencilView != nullptr) backup.depthStencilView->Release();
    if (backup.blendState != nullptr) backup.blendState->Release();
    if (backup.depthStencilState != nullptr) backup.depthStencilState->Release();
}

void ClearOldStates_D3D11()
{
    D3D11_DeviceContext->IASetInputLayout(nullptr);
    D3D11_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ID3D11Buffer* nullBuffer = nullptr;
    UINT stride = 0;
    UINT offset = 0;
    D3D11_DeviceContext->IASetVertexBuffers(0, 1, &nullBuffer, &stride, &offset);
    D3D11_DeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
    D3D11_DeviceContext->VSSetShader(nullptr, nullptr, 0);
    ID3D11Buffer* nullConstantBuffer = nullptr;
    D3D11_DeviceContext->VSSetConstantBuffers(0, 1, &nullConstantBuffer);
    D3D11_DeviceContext->PSSetShader(nullptr, nullptr, 0);
    D3D11_DeviceContext->PSSetConstantBuffers(0, 1, &nullConstantBuffer);
    ID3D11ShaderResourceView* nullSRV = nullptr;
    D3D11_DeviceContext->PSSetShaderResources(0, 1, &nullSRV);
    ID3D11SamplerState* nullSampler = nullptr;
    D3D11_DeviceContext->PSSetSamplers(0, 1, &nullSampler);
    D3D11_VIEWPORT nullViewport = {};
    D3D11_DeviceContext->RSSetViewports(1, &nullViewport);
    D3D11_RECT nullRect = {};
    D3D11_DeviceContext->RSSetScissorRects(1, &nullRect);
    D3D11_DeviceContext->RSSetState(nullptr);
    ID3D11RenderTargetView* nullRTV[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
    FLOAT blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    D3D11_DeviceContext->OMSetBlendState(nullptr, blendFactor, 0xFFFFFFFF);
    D3D11_DeviceContext->OMSetDepthStencilState(nullptr, 0);
    D3D11_DeviceContext->OMSetBlendState(nullptr, blendFactor, 0xFFFFFFFF);
    D3D11_DeviceContext->OMSetDepthStencilState(nullptr, 0);
}

void Draw_D3D11()
{
    HRESULT hr = -1;

    // Back up old states
    D3D11RenderStatesBackup RenderStatesBackup_D3D11 = D3D11RenderStatesBackup();
    BackUpOldStates_D3D11(RenderStatesBackup_D3D11);

    // Clear the old states
    ClearOldStates_D3D11();

    // Get back buffer for resolution
    ID3D11Texture2D* backBuffer = nullptr;
    D3D11_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
    D3D11_TEXTURE2D_DESC backBufferDesc;
    backBuffer->GetDesc(&backBufferDesc);
    backBuffer->Release();

    int x = 0;
    int y = 0;
    int w = backBufferDesc.Width;
    int h = backBufferDesc.Height;

    ID3D11ShaderResourceView* textureShaderResourceView = nullptr;
    ID3D11Texture2D* texture = nullptr;
    if ((hr = D3D11_Device->CreateTexture2D(&D3D11_TextureDesc, &D3D11_TextureData, &texture)) != MB_OK) { DebugConsoleOutput("Error: CreateTexture2D()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }

    if ((hr = D3D11_Device->CreateShaderResourceView(texture, &D3D11_ViewDesc, &textureShaderResourceView)) != MB_OK) { DebugConsoleOutput("Error: CreateShaderResourceView()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }

    // Vertex buffer settings
    D3D11_Verts[0] = { XMFLOAT3(x, y, 0.0f), XMFLOAT2(0.0f, 1.0f) };
    D3D11_Verts[1] = { XMFLOAT3(x + w, y, 0.0f), XMFLOAT2(1.0f, 1.0f) };
    D3D11_Verts[2] = { XMFLOAT3(x + w, y + h, 0.0f), XMFLOAT2(1.0f, 0.0f) };
    D3D11_Verts[3] = { XMFLOAT3(x, y + h, 0.0f), XMFLOAT2(0.0f, 0.0f) };

    // Set render targets
    D3D11_DeviceContext->OMSetRenderTargets(1, &D3D11_RenderTargetView, D3D11_DepthStencilView);

    // Setting layout
    D3D11_DeviceContext->IASetInputLayout(D3D11_VertexLayout);

    // Set stencil depth
    D3D11_DeviceContext->OMSetDepthStencilState(D3D11_DepthStencilState, 0);

    // Creating and setting the mandatory buffers
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    D3D11_DeviceContext->Map(D3D11_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    memcpy(mappedResource.pData, D3D11_Verts, sizeof(D3D11_Verts));
    D3D11_DeviceContext->Unmap(D3D11_VertexBuffer, 0);

    D3D11_DeviceContext->VSSetConstantBuffers(0, 1, &D3D11_ConstantBuffer);
    D3D11_DeviceContext->IASetIndexBuffer(D3D11_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    D3D11_DeviceContext->IASetVertexBuffers(0, 1, &D3D11_VertexBuffer, &D3D11_StrideVertex, &D3D11_OffsetVertex);

    // Setting shaders
    D3D11_DeviceContext->PSSetSamplers(0, 1, &D3D11_SamplerState);
    D3D11_DeviceContext->PSSetShaderResources(0, 1, &textureShaderResourceView);
    D3D11_DeviceContext->VSSetShader(D3D11_VertexShader, nullptr, 0);
    D3D11_DeviceContext->PSSetShader(D3D11_PixelShader, nullptr, 0);
    D3D11_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Setting Viewport
    D3D11_DeviceContext->RSSetViewports(1, &D3D11_CustomViewport);

    // Setting blendstate
    D3D11_DeviceContext->OMSetBlendState(D3D11_BlendState, D3D11_BlendFactor, D3D11_SampleMask);

    // Draw
    D3D11_DeviceContext->DrawIndexed(6, 0, 0);

    texture->Release();
    textureShaderResourceView->Release();

    // Setting old states
    RestoreOldStates_D3D11(RenderStatesBackup_D3D11);
}

bool HookInit_D3D11()
{
    if (GetModuleHandleA("d3d11.dll") == NULL) return false;

    try
    {
        DebugConsoleOutput("DirectX 11 detected!", false, "green");

        // Get vTable
        std::vector<uintptr_t> vTable = GetVTable_D3D11();

        if (!D3D11_PresentHook<D3D11_PresentT>::instance) D3D11_PresentHook<D3D11_PresentT>::instance = new D3D11_PresentHook<D3D11_PresentT>((void*)vTable[8]);
        D3D11_PresentHook<D3D11_PresentT>::instance->install();

        return true;
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error when init D3D11:", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
    }

    return false;
}

bool HookUninit_D3D10()
{
    if (D3D11_PresentHook<D3D11_PresentT>::instance && D3D11_PresentHook<D3D11_PresentT>::instance->isActive()) D3D11_PresentHook<D3D11_PresentT>::instance->remove();
    return true;
}



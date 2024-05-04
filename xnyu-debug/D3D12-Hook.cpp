#include "pch.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include "Conversions.h"
#include "Logging.h"
#include "xNyuHook.h"
#include "DrawingEssentials.h"
#include "D3D12-Hook.h"



// --- Variables ---
ID3D12Device* D3D12_Device = nullptr;
ID3D12CommandQueue* D3D12_CommandQueue = nullptr;
IDXGISwapChain* D3D12_SwapChain = nullptr;
IDXGISwapChain3* D3D12_SwapChain3 = nullptr;
ID3D12CommandAllocator* D3D12_CommandAllocator = nullptr;
ID3D12GraphicsCommandList* D3D12_GraphicsCommandList = nullptr;
D3D12_GRAPHICS_PIPELINE_STATE_DESC D3D12_PSODesc = {};
ID3D12PipelineState* D3D12_PipelineState = nullptr;
VertexD3D12 D3D12_Verts[4];

const char* D3D12_TextureShader = R"(
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
std::vector<uintptr_t> GetVTable_D3D12()
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

    // Create D3D12 device
    const auto hModDXGI = GetModuleHandleA("DXGI.dll");
    const auto hModD3D12 = GetModuleHandleA("D3D12.dll");
    const auto hD3D12CreateDevice = static_cast<LPVOID>(GetProcAddress(hModD3D12, "D3D12CreateDevice"));
    const auto hCreateDXGIFactory1 = static_cast<LPVOID>(GetProcAddress(hModDXGI, "CreateDXGIFactory1"));
    IDXGIFactory4* pFactory;
    auto hr = static_cast<HRESULT(WINAPI*)(REFIID, void**)>(hCreateDXGIFactory1)(IID_PPV_ARGS(&pFactory));
    const auto hr12 = static_cast<HRESULT(WINAPI*)(IUnknown*, D3D_FEATURE_LEVEL, REFIID, void**)>(hD3D12CreateDevice)(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&D3D12_Device));
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    D3D12_Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&D3D12_CommandQueue));

    DXGI_SWAP_CHAIN_DESC scDesc;
    ZeroMemory(&scDesc, sizeof(scDesc));
    scDesc.BufferCount = 2;
    scDesc.BufferDesc.Width = 0;
    scDesc.BufferDesc.Height = 0;
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.BufferDesc.RefreshRate.Numerator = 60;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.OutputWindow = tmpWindow;
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;
    scDesc.Windowed = TRUE;
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    pFactory->CreateSwapChain(D3D12_CommandQueue, &scDesc, &D3D12_SwapChain);

    // Clean up window
    DestroyWindow(tmpWindow);
    UnregisterClass(tmpWindowClass.lpszClassName, tmpWindowClass.hInstance);

    // Return VTable
    return std::vector<uintptr_t>(*reinterpret_cast<uintptr_t**>(D3D12_SwapChain), *reinterpret_cast<uintptr_t**>(D3D12_SwapChain) + 18);
}

void BackUpOldStates_D3D12(D3D12RenderStatesBackup& backup)
{
    /*
    Just a concept, Get function are not really existing in DX12

    D3D12_GraphicsCommandList->IAGetPrimitiveTopology(&backup.topology);
    D3D12_GraphicsCommandList->IAGetIndexBuffer(&backup.indexBufferView);
    D3D12_GraphicsCommandList->IAGetVertexBuffers(0, D3D12_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT, backup.vertexBufferViews);
    UINT numDescriptorHeaps = D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES;
    D3D12_GraphicsCommandList->GetDescriptorHeaps(&numDescriptorHeaps, backup.descriptorHeaps);
    D3D12_GraphicsCommandList->GetGraphicsRootSignature(&backup.rootSignature);
    UINT numViewports = 1;
    UINT numScissorRects = 1;
    D3D12_GraphicsCommandList->RSGetViewports(&numViewports, &backup.viewport);
    D3D12_GraphicsCommandList->RSGetScissorRects(&numScissorRects, &backup.scissorRect);
    D3D12_GraphicsCommandList->OMGetBlendFactor(backup.blendFactor);
    D3D12_GraphicsCommandList->OMGetStencilRef(&backup.stencilRef);
    */
}

void RestoreOldStates_D3D12(D3D12RenderStatesBackup& backup)
{
    /*
    Just a concept, beacuse Get BackUpOldStates_D3D12() isn't really possible

    D3D12_GraphicsCommandList->SetPipelineState(backup.pipelineState);
    D3D12_GraphicsCommandList->SetDescriptorHeaps(D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES, backup.descriptorHeaps);
    D3D12_GraphicsCommandList->SetGraphicsRootSignature(backup.rootSignature);
    D3D12_GraphicsCommandList->RSSetViewports(1, &backup.viewport);
    D3D12_GraphicsCommandList->RSSetScissorRects(1, &backup.scissorRect);
    D3D12_GraphicsCommandList->IASetIndexBuffer(&backup.indexBufferView);
    D3D12_GraphicsCommandList->IASetVertexBuffers(0, D3D12_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT, backup.vertexBufferViews);
    D3D12_GraphicsCommandList->IASetPrimitiveTopology(backup.topology);
    D3D12_GraphicsCommandList->OMSetBlendFactor(backup.blendFactor);
    D3D12_GraphicsCommandList->OMSetStencilRef(backup.stencilRef);

    if (backup.pipelineState != nullptr) backup.pipelineState->Release();
    for (auto& heap : backup.descriptorHeaps)
        if (heap != nullptr) heap->Release();
    if (backup.rootSignature != nullptr) backup.rootSignature->Release();
    */
}

void ClearStates_D3D12()
{
    /*
    Just a concept, beacuse Get BackUpOldStates_D3D12() amd RestoreOldStates_D3D12() aren't really possible

    D3D12_GraphicsCommandList->SetPipelineState(nullptr);
    ID3D12DescriptorHeap* nullDescriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES] = { nullptr };
    D3D12_GraphicsCommandList->SetDescriptorHeaps(D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES, nullDescriptorHeaps);
    D3D12_GraphicsCommandList->SetGraphicsRootSignature(nullptr);
    D3D12_VIEWPORT nullViewport = {};
    D3D12_RECT nullScissorRect = {};
    D3D12_GraphicsCommandList->RSSetViewports(1, &nullViewport);
    D3D12_GraphicsCommandList->RSSetScissorRects(1, &nullScissorRect);
    D3D12_INDEX_BUFFER_VIEW nullIndexBufferView = {};
    D3D12_VERTEX_BUFFER_VIEW nullVertexBufferView = {};
    D3D12_GraphicsCommandList->IASetIndexBuffer(&nullIndexBufferView);
    D3D12_GraphicsCommandList->IASetVertexBuffers(0, 1, &nullVertexBufferView);
    D3D12_GraphicsCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_UNDEFINED);
    FLOAT nullBlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    D3D12_GraphicsCommandList->OMSetBlendFactor(nullBlendFactor);
    D3D12_GraphicsCommandList->OMSetStencilRef(0);
    */
}

void Draw_D3D12()
{
    // Back up old states
    D3D12RenderStatesBackup RenderStatesBackup_D3D12 = D3D12RenderStatesBackup();
    BackUpOldStates_D3D12(RenderStatesBackup_D3D12);

    // Clear the old states
    ClearStates_D3D12();

    // Get back buffer for resolution
    ID3D12Resource* backBuffer = nullptr;
    D3D12_SwapChain3->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    D3D12_RESOURCE_DESC backBufferDesc = backBuffer->GetDesc();
    int x = 0;
    int y = 0;
    int w = static_cast<int>(backBufferDesc.Width);
    int h = static_cast<int>(backBufferDesc.Height);
    backBuffer->Release();

    D3D12_Verts[0] = { XMFLOAT3(x, y, 0.0f), XMFLOAT2(0.0f, 1.0f) };
    D3D12_Verts[1] = { XMFLOAT3(x + w, y, 0.0f), XMFLOAT2(1.0f, 1.0f) };
    D3D12_Verts[2] = { XMFLOAT3(x + w, y + h, 0.0f), XMFLOAT2(1.0f, 0.0f) };
    D3D12_Verts[3] = { XMFLOAT3(x, y + h, 0.0f), XMFLOAT2(0.0f, 0.0f) };



    // ...
    // Create texture, copy raw pixel bytes to the texutre, set shaders, draw texture quad and render texture
    // ...



    // Restore the old states
    RestoreOldStates_D3D12(RenderStatesBackup_D3D12);
}

bool HookInit_D3D12()
{
    if (GetModuleHandleA("d3d12.dll") == NULL) return false;

    try
    {
        DebugConsoleOutput("DirectX 12 detected!", false, "green");

        // Get vTable
        std::vector<uintptr_t> vTable = GetVTable_D3D12();

        if (!D3D12_PresentHook<D3D12_PresentT>::instance) D3D12_PresentHook<D3D12_PresentT>::instance = new D3D12_PresentHook<D3D12_PresentT>((void*)vTable[17]);
        D3D12_PresentHook<D3D12_PresentT>::instance->install();

        return true;
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error when init D3D12:", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
    }

    return false;
}

bool HookUninit_D3D12()
{
    if (D3D12_PresentHook<D3D12_PresentT>::instance && D3D12_PresentHook<D3D12_PresentT>::instance->isActive()) D3D12_PresentHook<D3D12_PresentT>::instance->remove();
    return true;
}



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

#include <d3d11.h>
#include <D3DX11.h>
#include <d2d1_1.h>
#include <dxgi1_2.h>
#include <d3dcompiler.h>
#include <wchar.h>
#include <DXErr.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DX11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "DXErr.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

namespace Direct3D11Hooking
{
    enum D3D11DeviceVTbl : short
    {
        // IUnknown
        QueryInterface = 0,
        AddRef = 1,
        Release = 2,

        // ID3D11Device
        CreateBuffer = 3,
        CreateTexture1D = 4,
        CreateTexture2D = 5,
        CreateTexture3D = 6,
        CreateShaderResourceView = 7,
        CreateUnorderedAccessView = 8,
        CreateRenderTargetView = 9,
        CreateDepthStencilView = 10,
        CreateInputLayout = 11,
        CreateVertexShader = 12,
        CreateGeometryShader = 13,
        CreateGeometryShaderWithStreamOutput = 14,
        CreatePixelShader = 15,
        CreateHullShader = 16,
        CreateDomainShader = 17,
        CreateComputeShader = 18,
        CreateClassLinkage = 19,
        CreateBlendState = 20,
        CreateDepthStencilState = 21,
        CreateRasterizerState = 22,
        CreateSamplerState = 23,
        CreateQuery = 24,
        CreatePredicate = 25,
        CreateCounter = 26,
        CreateDeferredContext = 27,
        OpenSharedResource = 28,
        CheckFormatSupport = 29,
        CheckMultisampleQualityLevels = 30,
        CheckCounterInfo = 31,
        CheckCounter = 32,
        CheckFeatureSupport = 33,
        GetPrivateData = 34,
        SetPrivateData = 35,
        SetPrivateDataInterface = 36,
        GetFeatureLevel = 37,
        GetCreationFlags = 38,
        GetDeviceRemovedReason = 39,
        GetImmediateContext = 40,
        SetExceptionMode = 41,
        GetExceptionMode = 42
    };

    class Direct3D11 :
        public Direct3DHooking::Direct3DBase
    {
        ID3D11Device* pd3dDevice;
        ID3D11DeviceContext* pd3dDeviceContext;
        IDXGISwapChain* pSwapChain;
    public:
        Direct3D11();
        ~Direct3D11();
        static const int VTableElements = 43;

        std::vector<size_t> vtable() const override;
    };
}

using namespace Indicium::Core::Exceptions;

Direct3D11Hooking::Direct3D11::Direct3D11() :
	pd3dDevice(nullptr), pd3dDeviceContext(nullptr), pSwapChain(nullptr)
{
	temp_window = std::make_unique<Window>("TempDirect3D11OverlayWindow");

	const auto hModDXGI = GetModuleHandleA("DXGI.dll");
	const auto hModD3D11 = GetModuleHandleA("D3D11.dll");

	if (hModDXGI == nullptr)
	{
		throw ModuleNotFoundException("Could not get handle to DXGI.dll");
	}

	if (hModD3D11 == nullptr)
	{
		throw ModuleNotFoundException("Could not get handle to D3D11.dll");
	}

	// Setup swap chain
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
		sd.OutputWindow = temp_window->windowHandle();
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	UINT createDeviceFlags = 0;
	D3D_FEATURE_LEVEL featureLevel;
	// Note: requesting lower feature level in case of missing hardware support
	const D3D_FEATURE_LEVEL featureLevelArray[3] = {
		D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0
	};

	const auto hD3D11CreateDeviceAndSwapChain = static_cast<LPVOID>(GetProcAddress(
		hModD3D11,
		"D3D11CreateDeviceAndSwapChain"
	));
	if (hD3D11CreateDeviceAndSwapChain == nullptr)
	{
		throw ProcAddressNotFoundException("Could not get handle to D3D11CreateDeviceAndSwapChain");
	}

	const auto hr11 = static_cast<HRESULT(WINAPI*)(
		IDXGIAdapter*,
		D3D_DRIVER_TYPE,
		HMODULE,
		UINT,
		const D3D_FEATURE_LEVEL*,
		UINT,
		UINT,
		const DXGI_SWAP_CHAIN_DESC*,
		IDXGISwapChain**,
		ID3D11Device**,
		D3D_FEATURE_LEVEL*,
		ID3D11DeviceContext**)>(hD3D11CreateDeviceAndSwapChain)(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			createDeviceFlags,
			featureLevelArray,
			1,
			D3D11_SDK_VERSION,
			&sd,
			&pSwapChain,
			&pd3dDevice,
			&featureLevel,
			&pd3dDeviceContext);

	if (FAILED(hr11))
	{
		throw DXAPIException("Could not create D3D11 device", hr11);
	}
}

// D3D11 Device
IDXGISwapChain* pD3D11_SwapChain = nullptr;;
IDXGISurface* pD3D11_Surface = nullptr;
ID3D11Device* pD3D11_Device = nullptr;;
ID2D1Device* pD2D1_Device = nullptr;;
void* pD3D11_SwapChain_vTable[18];
IDXGIOutput* pD3D11_OutputMode = nullptr;

std::vector<size_t> Direct3D11Hooking::Direct3D11::vtable() const
{
	pD3D11_SwapChain = pSwapChain;
	return std::vector<size_t>(*reinterpret_cast<size_t**>(pSwapChain),
		*reinterpret_cast<size_t**>(pSwapChain) + DXGIHooking::DXGI::SwapChainVTableElements);
}

Direct3D11Hooking::Direct3D11::~Direct3D11()
{
	if (pSwapChain)
		pSwapChain->Release();

	if (pd3dDevice)
		pd3dDevice->Release();

	if (pd3dDeviceContext)
		pd3dDeviceContext->Release();
}

// Present()
typedef HRESULT(__stdcall* Present11T)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
Present11T pD3D11_Present = nullptr;
void* D3D11_Present_Original_Address = 0;
void* D3D11_Present_Hook_Address = 0;
subhook::Hook D3D11_Subhook;

// Texture rendering
struct VertexD3D11Texture
{
    XMFLOAT3 pos;
    XMFLOAT2 texCoord;
};
ID3D11VertexShader* pD3D11_VertexShader = nullptr;
ID3D11InputLayout* pD3D11_VertexLayout = nullptr;
ID3D11PixelShader* pD3D11_PixelShader = nullptr;
ID3D11Buffer* pD3D11_VertexBuffer = nullptr;
ID3D11Buffer* pD3D11_IndexBuffer = nullptr;
ID3D11Buffer* pD3D11_ConstantBuffer = nullptr;
ID3D11SamplerState* pD3D11_SamplerState = nullptr;
XMMATRIX pD3D11_OrthographicProjectionMatrix;
VertexD3D11Texture pD3D11_Verts[4];
D3D11_BUFFER_DESC pD3D11_BufferVertexDesc;
D3D11_SUBRESOURCE_DATA pD3D11_BufferVertexSubresourceLine;
UINT pD3D11_StrideVertex = sizeof(VertexD3D11Texture);
UINT pD3D11_OffsetVertex = 0;
D3D11_SAMPLER_DESC pD3D11_SamplerDesc;
D3D11_TEXTURE2D_DESC pD3D11_TextureDesc;
D3D11_SUBRESOURCE_DATA pD3D11_TextureData;
D3D11_SHADER_RESOURCE_VIEW_DESC pD3D11_ViewDesc;
D3D11_INPUT_ELEMENT_DESC pD3D11_Layout[2];

// Shared
HWND pD3D11_Window = nullptr;
ID3D11DeviceContext* pD3D11_DeviceContext = nullptr;
ID3D11RenderTargetView* pD3D11_RenderTargetView = nullptr;
ID3D11DepthStencilView* pD3D11_DepthStencilView;
D3D11_VIEWPORT pD3D11_Viewport;
D3D11_VIEWPORT pD3D11_CustomViewport;
D3D11_BLEND_DESC pD3D11_BlendDesc;
ID3D11BlendState* pD3D11_BlendState = nullptr;
float pD3D11_BlendFactor[4];
UINT pD3D11_SampleMask;
D3D11_DEPTH_STENCIL_DESC pD3D11_DepthStencilDesc;
ID3D11DepthStencilState* pD3D11_DepthStencilState;


constexpr const char* TextureShader = R"(
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



// Colors
XMFLOAT4 Red_D3D11 = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
XMFLOAT4 Green_D3D11 = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
XMFLOAT4 Blue_D3D11 = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
XMFLOAT4 Black_D3D11 = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
XMFLOAT4 White_D3D11 = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
XMFLOAT4 Gray_D3D11 = XMFLOAT4(0.588f, 0.588f, 0.588f, 1.0f);
XMFLOAT4 Yellow_D3D11 = XMFLOAT4(1.0f, 0.969f, 0.0f, 1.0f);
XMFLOAT4 Purple_D3D11 = XMFLOAT4(0.667f, 0.0f, 1.0f, 1.0f);
XMFLOAT4 Pink_D3D11 = XMFLOAT4(1.0f, 0.0f, 0.867f, 1.0f);
XMFLOAT4 Orange_D3D11 = XMFLOAT4(1.0f, 0.616f, 0.0f, 1.0f);
XMFLOAT4 Cyan_D3D11 = XMFLOAT4(0.0f, 1.0f, 0.949f, 1.0f);




//
// Drawing -------------------------------------------------------------------------
//

ID3D11InputLayout* backupInputLayout = nullptr;
D3D11_PRIMITIVE_TOPOLOGY backupTopology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
ID3D11Buffer* backupVertexBuffer = nullptr;
UINT backupStride = 0;
UINT backupOffset = 0;
ID3D11Buffer* backupIndexBuffer = nullptr;
DXGI_FORMAT backupIndexBufferFormat = DXGI_FORMAT_UNKNOWN;
UINT backupIndexBufferOffset = 0;
ID3D11VertexShader* backupVertexShader = nullptr;
UINT backupVertexShaderNumClassInstance = 0;
ID3D11Buffer* backupConstantBuffer = nullptr;
ID3D11PixelShader* backupPixelShader = nullptr;
UINT backupPixelShaderNumClassInstance = 0;
ID3D11Buffer* backupPixelConstantBuffer = nullptr;
ID3D11ShaderResourceView* backupShaderResourceView = nullptr;
ID3D11SamplerState* backupSampler = nullptr;
UINT backupViewportNum = 1;
D3D11_VIEWPORT backupViewport = {};
UINT backupScissorRectNum = 1;
D3D11_RECT backupScissorRect[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE] = {};
ID3D11RasterizerState* backupRasterizerState = nullptr;
ID3D11RenderTargetView* backupRenderTarget[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = {};
ID3D11DepthStencilView* backupDepthStencilView = nullptr;
ID3D11BlendState* backupBlendState = nullptr;
FLOAT backupBlendFactor[4] = {};
UINT backupSampleMask = 0;
ID3D11DepthStencilState* backupDepthStencilState = nullptr;
UINT backupStencilRef = 0;
ID3D11BlendState* backupRenderTargetBlendState = nullptr;
FLOAT backupRenderTargetBlendFactor[4] = {};
UINT backupRenderTargetSampleMask = 0;
ID3D11DepthStencilState* backupRenderTargetDepthStencilState = nullptr;
UINT backupRenderTargetStencilRef = 0;

void BackUpOldStates_D3D11()
{
    pD3D11_DeviceContext->IAGetInputLayout(&backupInputLayout);
    pD3D11_DeviceContext->IAGetPrimitiveTopology(&backupTopology);
    pD3D11_DeviceContext->IAGetVertexBuffers(0, 1, &backupVertexBuffer, &backupStride, &backupOffset);
    pD3D11_DeviceContext->IAGetIndexBuffer(&backupIndexBuffer, &backupIndexBufferFormat, &backupIndexBufferOffset);
    pD3D11_DeviceContext->VSGetShader(&backupVertexShader, nullptr, &backupVertexShaderNumClassInstance);
    pD3D11_DeviceContext->VSGetConstantBuffers(0, 1, &backupConstantBuffer);
    pD3D11_DeviceContext->PSGetShader(&backupPixelShader, nullptr, &backupPixelShaderNumClassInstance);
    pD3D11_DeviceContext->PSGetConstantBuffers(0, 1, &backupPixelConstantBuffer);
    pD3D11_DeviceContext->PSGetShaderResources(0, 1, &backupShaderResourceView);
    pD3D11_DeviceContext->PSGetSamplers(0, 1, &backupSampler);
    pD3D11_DeviceContext->RSGetViewports(&backupViewportNum, &backupViewport);
    pD3D11_DeviceContext->RSGetScissorRects(&backupScissorRectNum, backupScissorRect);
    pD3D11_DeviceContext->RSGetState(&backupRasterizerState);
    pD3D11_DeviceContext->OMGetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, backupRenderTarget, &backupDepthStencilView);
    pD3D11_DeviceContext->OMGetBlendState(&backupBlendState, backupBlendFactor, &backupSampleMask);
    pD3D11_DeviceContext->OMGetDepthStencilState(&backupDepthStencilState, &backupStencilRef);
    pD3D11_DeviceContext->OMGetBlendState(&backupRenderTargetBlendState, backupRenderTargetBlendFactor, &backupRenderTargetSampleMask);
    pD3D11_DeviceContext->OMGetDepthStencilState(&backupRenderTargetDepthStencilState, &backupRenderTargetStencilRef);
}

void RestoreOldStates_D3D11()
{
    pD3D11_DeviceContext->IASetInputLayout(backupInputLayout);
    pD3D11_DeviceContext->IASetPrimitiveTopology(backupTopology);
    pD3D11_DeviceContext->IASetVertexBuffers(0, 1, &backupVertexBuffer, &backupStride, &backupOffset);
    pD3D11_DeviceContext->IASetIndexBuffer(backupIndexBuffer, backupIndexBufferFormat, backupIndexBufferOffset);
    pD3D11_DeviceContext->VSSetShader(backupVertexShader, nullptr, backupVertexShaderNumClassInstance);
    pD3D11_DeviceContext->VSSetConstantBuffers(0, 1, &backupConstantBuffer);
    pD3D11_DeviceContext->PSSetShader(backupPixelShader, nullptr, backupPixelShaderNumClassInstance);
    pD3D11_DeviceContext->PSSetConstantBuffers(0, 1, &backupPixelConstantBuffer);
    pD3D11_DeviceContext->PSSetShaderResources(0, 1, &backupShaderResourceView);
    pD3D11_DeviceContext->PSSetSamplers(0, 1, &backupSampler);
    pD3D11_DeviceContext->RSSetViewports(backupViewportNum, &backupViewport);
    pD3D11_DeviceContext->RSSetScissorRects(backupScissorRectNum, backupScissorRect);
    pD3D11_DeviceContext->RSSetState(backupRasterizerState);
    pD3D11_DeviceContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, backupRenderTarget, backupDepthStencilView);
    pD3D11_DeviceContext->OMSetBlendState(backupBlendState, backupBlendFactor, backupSampleMask);
    pD3D11_DeviceContext->OMSetDepthStencilState(backupDepthStencilState, backupStencilRef);
    pD3D11_DeviceContext->OMSetBlendState(backupRenderTargetBlendState, backupRenderTargetBlendFactor, backupRenderTargetSampleMask);
    pD3D11_DeviceContext->OMSetDepthStencilState(backupRenderTargetDepthStencilState, backupRenderTargetStencilRef);

    if (backupInputLayout != nullptr) backupInputLayout->Release();
    if (backupVertexBuffer != nullptr) backupVertexBuffer->Release();
    if (backupIndexBuffer != nullptr) backupIndexBuffer->Release();
    if (backupVertexShader != nullptr) backupVertexShader->Release();
    if (backupConstantBuffer != nullptr) backupConstantBuffer->Release();
    if (backupPixelShader != nullptr) backupPixelShader->Release();
    if (backupPixelConstantBuffer != nullptr) backupPixelConstantBuffer->Release();
    if (backupShaderResourceView != nullptr) backupShaderResourceView->Release();
    if (backupSampler != nullptr) backupSampler->Release();
    if (backupRasterizerState != nullptr) backupRasterizerState->Release();
    for (UINT i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++) {
        if (backupRenderTarget[i] != nullptr) backupRenderTarget[i]->Release();
    }
    if (backupDepthStencilView != nullptr) backupDepthStencilView->Release();
    if (backupBlendState != nullptr) backupBlendState->Release();
    if (backupDepthStencilState != nullptr) backupDepthStencilState->Release();
    if (backupRenderTargetBlendState != nullptr) backupRenderTargetBlendState->Release();
    if (backupRenderTargetDepthStencilState != nullptr) backupRenderTargetDepthStencilState->Release();
}

void ClearOldStates_D3D11()
{
    pD3D11_DeviceContext->IASetInputLayout(nullptr);
    pD3D11_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ID3D11Buffer* nullBuffer = nullptr;
    UINT stride = 0;
    UINT offset = 0;
    pD3D11_DeviceContext->IASetVertexBuffers(0, 1, &nullBuffer, &stride, &offset);
    pD3D11_DeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
    pD3D11_DeviceContext->VSSetShader(nullptr, nullptr, 0);
    ID3D11Buffer* nullConstantBuffer = nullptr;
    pD3D11_DeviceContext->VSSetConstantBuffers(0, 1, &nullConstantBuffer);
    pD3D11_DeviceContext->PSSetShader(nullptr, nullptr, 0);
    pD3D11_DeviceContext->PSSetConstantBuffers(0, 1, &nullConstantBuffer);
    ID3D11ShaderResourceView* nullSRV = nullptr;
    pD3D11_DeviceContext->PSSetShaderResources(0, 1, &nullSRV);
    ID3D11SamplerState* nullSampler = nullptr;
    pD3D11_DeviceContext->PSSetSamplers(0, 1, &nullSampler);
    D3D11_VIEWPORT nullViewport = {};
    pD3D11_DeviceContext->RSSetViewports(1, &nullViewport);
    D3D11_RECT nullRect = {};
    pD3D11_DeviceContext->RSSetScissorRects(1, &nullRect);
    pD3D11_DeviceContext->RSSetState(nullptr);
    ID3D11RenderTargetView* nullRTV[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
    FLOAT blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    pD3D11_DeviceContext->OMSetBlendState(nullptr, blendFactor, 0xFFFFFFFF);
    pD3D11_DeviceContext->OMSetDepthStencilState(nullptr, 0);
    pD3D11_DeviceContext->OMSetBlendState(nullptr, blendFactor, 0xFFFFFFFF);
    pD3D11_DeviceContext->OMSetDepthStencilState(nullptr, 0);
}

void Draw_D3D11()
{
    HRESULT hr = -1;

    // Back up old states
    BackUpOldStates_D3D11();

    // Clear the old states
    ClearOldStates_D3D11();

    // Setting position and size
    float x = 0;
    float y = 0;
    float w = MainWindowRect.right;
    float h = MainWindowRect.bottom;

    ID3D11ShaderResourceView* textureShaderResourceView = nullptr;
    ID3D11Texture2D* texture = nullptr;
    if ((hr = pD3D11_Device->CreateTexture2D(&pD3D11_TextureDesc, &pD3D11_TextureData, &texture)) != MB_OK) { DebugConsoleOutput("Error: CreateTexture2D()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
    
    if ((hr = pD3D11_Device->CreateShaderResourceView(texture, &pD3D11_ViewDesc, &textureShaderResourceView)) != MB_OK) { DebugConsoleOutput("Error: CreateShaderResourceView()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
    
    // Vertex buffer settings
    pD3D11_Verts[0] = { XMFLOAT3(x, y, 0.0f), XMFLOAT2(0.0f, 1.0f) };
    pD3D11_Verts[1] = { XMFLOAT3(x + w, y, 0.0f), XMFLOAT2(1.0f, 1.0f) };
    pD3D11_Verts[2] = { XMFLOAT3(x + w, y + h, 0.0f), XMFLOAT2(1.0f, 0.0f) };
    pD3D11_Verts[3] = { XMFLOAT3(x, y + h, 0.0f), XMFLOAT2(0.0f, 0.0f) };

    // Set render targets
    pD3D11_DeviceContext->OMSetRenderTargets(1, &pD3D11_RenderTargetView, pD3D11_DepthStencilView);

    // Setting layout
    pD3D11_DeviceContext->IASetInputLayout(pD3D11_VertexLayout);

    // Set stencil depth
    pD3D11_DeviceContext->OMSetDepthStencilState(pD3D11_DepthStencilState, 0);

    // Creating and setting the mandatory buffers
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    pD3D11_DeviceContext->Map(pD3D11_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    memcpy(mappedResource.pData, pD3D11_Verts, sizeof(pD3D11_Verts));
    pD3D11_DeviceContext->Unmap(pD3D11_VertexBuffer, 0);

    pD3D11_DeviceContext->VSSetConstantBuffers(0, 1, &pD3D11_ConstantBuffer);
    pD3D11_DeviceContext->IASetIndexBuffer(pD3D11_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    pD3D11_DeviceContext->IASetVertexBuffers(0, 1, &pD3D11_VertexBuffer, &pD3D11_StrideVertex, &pD3D11_OffsetVertex);

    // Setting shaders
    pD3D11_DeviceContext->PSSetSamplers(0, 1, &pD3D11_SamplerState);
    pD3D11_DeviceContext->PSSetShaderResources(0, 1, &textureShaderResourceView);
    pD3D11_DeviceContext->VSSetShader(pD3D11_VertexShader, nullptr, 0);
    pD3D11_DeviceContext->PSSetShader(pD3D11_PixelShader, nullptr, 0);
    pD3D11_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Setting Viewport
    pD3D11_DeviceContext->RSSetViewports(1, &pD3D11_CustomViewport);

    // Setting blendstate
    pD3D11_DeviceContext->OMSetBlendState(pD3D11_BlendState, pD3D11_BlendFactor, pD3D11_SampleMask);

    // Draw
    pD3D11_DeviceContext->DrawIndexed(6, 0, 0);

    texture->Release();
    textureShaderResourceView->Release();

    // Setting old states
    RestoreOldStates_D3D11();
}


//
// Hook Routine ---------------------------------------------------------------------
//

HRESULT D3D11_Present_Hook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (DebugMenuInit)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(pD3D11_Device), (void**)&pD3D11_Device)))
        {
            HRESULT hr = -1;

            ///////////////////////
            // INIT GLOBAL STUFF //
            ///////////////////////

            // Getting swapchain
            pD3D11_SwapChain = pSwapChain;

            // Getting device context
            pD3D11_Device->GetImmediateContext(&pD3D11_DeviceContext);

            // Create custom viewport
            UINT numViewports = 1;
            pD3D11_DeviceContext->RSGetViewports(&numViewports, &pD3D11_Viewport);
            if (pD3D11_Viewport.Width > 0 && pD3D11_Viewport.Height > 0)
            {
                RECT windowRect;
                if (!GetClientRect(MainWindowHandle, &windowRect)) DebugConsoleOutput("Error: GetClientRect()", false, "red");
                
                pD3D11_CustomViewport.Width = windowRect.right;
                pD3D11_CustomViewport.Height = windowRect.bottom;
                pD3D11_CustomViewport.TopLeftX = windowRect.left;
                pD3D11_CustomViewport.TopLeftY = windowRect.top;
                pD3D11_CustomViewport.MinDepth = 0.0f;
                pD3D11_CustomViewport.MaxDepth = 1.0f;
                pD3D11_DeviceContext->RSSetViewports(1, &pD3D11_CustomViewport);
            }
            else
            {
                pD3D11_CustomViewport = pD3D11_Viewport;
                pD3D11_DeviceContext->RSSetViewports(1, &pD3D11_CustomViewport);
            }

            // Get render target
            pD3D11_DeviceContext->OMGetRenderTargets(1, &pD3D11_RenderTargetView, nullptr);
            ID3D11Texture2D* pBackbuffer = nullptr;
            if ((hr = pD3D11_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackbuffer))) != MB_OK) { DebugConsoleOutput("Error: GetBuffer()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
            if (SUCCEEDED(hr))
            {
                if ((hr = pD3D11_Device->CreateRenderTargetView(pBackbuffer, nullptr, &pD3D11_RenderTargetView)) != MB_OK) { DebugConsoleOutput("Error: CreateRenderTargetView()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                if (SUCCEEDED(hr))
                {
                    // Create stencil depth view
                    D3D11_TEXTURE2D_DESC depthStencilDesc = {};
                    depthStencilDesc.Width = pD3D11_CustomViewport.Width;
                    depthStencilDesc.Height = pD3D11_CustomViewport.Height;
                    depthStencilDesc.MipLevels = 1;
                    depthStencilDesc.ArraySize = 1;
                    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
                    depthStencilDesc.SampleDesc.Count = 1;
                    depthStencilDesc.SampleDesc.Quality = 0;
                    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
                    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
                    depthStencilDesc.CPUAccessFlags = 0;
                    depthStencilDesc.MiscFlags = 0;
                    ID3D11Texture2D* depthStencilBuffer;
                    if ((hr = pD3D11_Device->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilBuffer)) != MB_OK) { DebugConsoleOutput("Error: CreateTexture2D()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                    if (SUCCEEDED(hr))
                    {
                        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
                        depthStencilViewDesc.Format = depthStencilDesc.Format;
                        depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
                        depthStencilViewDesc.Texture2D.MipSlice = 0;
                        if ((hr = pD3D11_Device->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &pD3D11_DepthStencilView)) != MB_OK) { DebugConsoleOutput("Error: CreateDepthStencilView()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                        if (SUCCEEDED(hr))
                        {
                            // Create stencil depth state
                            pD3D11_DepthStencilDesc.DepthEnable = false;
                            pD3D11_DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
                            pD3D11_DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
                            pD3D11_DepthStencilDesc.StencilEnable = true;
                            pD3D11_DepthStencilDesc.StencilReadMask = 0xFF;
                            pD3D11_DepthStencilDesc.StencilWriteMask = 0xFF;
                            pD3D11_DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
                            pD3D11_DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
                            pD3D11_DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
                            pD3D11_DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
                            pD3D11_DepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
                            pD3D11_DepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
                            pD3D11_DepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
                            pD3D11_DepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
                            pD3D11_Device->CreateDepthStencilState(&pD3D11_DepthStencilDesc, &pD3D11_DepthStencilState);

                            // Creating blend state
                            pD3D11_BlendDesc.AlphaToCoverageEnable = false;
                            pD3D11_BlendDesc.IndependentBlendEnable = false;
                            pD3D11_BlendDesc.RenderTarget[0].BlendEnable = true;
                            pD3D11_BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
                            pD3D11_BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
                            pD3D11_BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
                            pD3D11_BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;// D3D11_BLEND_ONE;
                            pD3D11_BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;// D3D11_BLEND_ZERO;
                            pD3D11_BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
                            pD3D11_BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
                            pD3D11_BlendFactor[0] = 0.0f;
                            pD3D11_BlendFactor[1] = 0.0f;
                            pD3D11_BlendFactor[2] = 0.0f;
                            pD3D11_BlendFactor[3] = 0.0f;
                            pD3D11_SampleMask = 0xffffffff;
                            if ((hr = pD3D11_Device->CreateBlendState(&pD3D11_BlendDesc, &pD3D11_BlendState)) != MB_OK) { DebugConsoleOutput("Error: CreateBlendState()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                            if (SUCCEEDED(hr))
                            {
                                ////////////////////////
                                // INIT TEXTURE STUFF //
                                ////////////////////////

                                // Create Vertex shader
                                ID3D10Blob* pCompiledShaderBlob = nullptr;
                                if ((hr = D3DCompile(TextureShader, strlen(TextureShader), 0, nullptr, nullptr, "VS", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &pCompiledShaderBlob, nullptr)) != MB_OK) { DebugConsoleOutput("Error: D3DCompile()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                if (SUCCEEDED(hr))
                                {
                                    if ((hr = pD3D11_Device->CreateVertexShader(pCompiledShaderBlob->GetBufferPointer(), pCompiledShaderBlob->GetBufferSize(), nullptr, &pD3D11_VertexShader)) != MB_OK) { DebugConsoleOutput("Error: CreateVertexShader()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                    if (SUCCEEDED(hr))
                                    {
                                        // Create Pixel shader
                                        pD3D11_Layout[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
                                        pD3D11_Layout[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };

                                        UINT numElements = ARRAYSIZE(pD3D11_Layout);
                                        if ((hr = pD3D11_Device->CreateInputLayout(pD3D11_Layout, numElements, pCompiledShaderBlob->GetBufferPointer(), pCompiledShaderBlob->GetBufferSize(), &pD3D11_VertexLayout)) != MB_OK) { DebugConsoleOutput("Error: CreateInputLayout()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                        if (SUCCEEDED(hr))
                                        {
                                            pD3D11_DeviceContext->IASetInputLayout(pD3D11_VertexLayout);
                                            pCompiledShaderBlob->Release();
                                            if ((hr = D3DCompile(TextureShader, strlen(TextureShader), 0, nullptr, nullptr, "PS", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &pCompiledShaderBlob, nullptr)) != MB_OK) { DebugConsoleOutput("Error: D3DCompile()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                            if (SUCCEEDED(hr))
                                            {
                                                if ((hr = pD3D11_Device->CreatePixelShader(pCompiledShaderBlob->GetBufferPointer(), pCompiledShaderBlob->GetBufferSize(), nullptr, &pD3D11_PixelShader)) != MB_OK) { DebugConsoleOutput("Error: CreatePixelShader()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                                if (SUCCEEDED(hr))
                                                {
                                                    // Constant buffer settings 
                                                    pD3D11_OrthographicProjectionMatrix = XMMatrixOrthographicOffCenterLH(0, pD3D11_CustomViewport.Width, pD3D11_CustomViewport.Height, 0, 0.0f, 1.0f);
                                                    D3D11_BUFFER_DESC buffer_desc_{ 0 };
                                                    buffer_desc_.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                                                    buffer_desc_.ByteWidth = sizeof(pD3D11_OrthographicProjectionMatrix);
                                                    buffer_desc_.Usage = D3D11_USAGE_DEFAULT;
                                                    D3D11_SUBRESOURCE_DATA subresource_rectangle_constant_{ 0 };
                                                    subresource_rectangle_constant_.pSysMem = &pD3D11_OrthographicProjectionMatrix;
                                                    if ((hr = pD3D11_Device->CreateBuffer(&buffer_desc_, &subresource_rectangle_constant_, &pD3D11_ConstantBuffer)) != MB_OK) { DebugConsoleOutput("Error: CreateBuffer()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                                    if (SUCCEEDED(hr))
                                                    {
                                                        // Index buffer settings 
                                                        WORD indices_[] = { 0, 1, 2, 0, 2, 3 };
                                                        D3D11_BUFFER_DESC buffer_desc_index_{ 0 };
                                                        buffer_desc_index_.BindFlags = D3D11_BIND_INDEX_BUFFER;
                                                        buffer_desc_index_.ByteWidth = sizeof(WORD) * 6;
                                                        buffer_desc_index_.Usage = D3D11_USAGE_IMMUTABLE;
                                                        D3D11_SUBRESOURCE_DATA subresource_index_{ 0 };
                                                        subresource_index_.pSysMem = &indices_;
                                                        if ((hr = pD3D11_Device->CreateBuffer(&buffer_desc_index_, &subresource_index_, &pD3D11_IndexBuffer)) != MB_OK) { DebugConsoleOutput("Error: CreateBuffer()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                                        if (SUCCEEDED(hr))
                                                        {
                                                            // Vertex buffer settings 
                                                            pD3D11_BufferVertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                                                            pD3D11_BufferVertexDesc.ByteWidth = sizeof(VertexD3D11Texture) * 4;
                                                            pD3D11_BufferVertexDesc.Usage = D3D11_USAGE_DYNAMIC;
                                                            pD3D11_BufferVertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                                                            pD3D11_BufferVertexDesc.MiscFlags = 0;
                                                            pD3D11_BufferVertexDesc.StructureByteStride = 0;
                                                            pD3D11_BufferVertexSubresourceLine.pSysMem = &pD3D11_Verts;
                                                            if ((hr = pD3D11_Device->CreateBuffer(&pD3D11_BufferVertexDesc, &pD3D11_BufferVertexSubresourceLine, &pD3D11_VertexBuffer)) != MB_OK) { DebugConsoleOutput("Error: CreateBuffer()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                                            if (SUCCEEDED(hr))
                                                            {
                                                                // Texture settings
                                                                pD3D11_SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
                                                                pD3D11_SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
                                                                pD3D11_SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
                                                                pD3D11_SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
                                                                pD3D11_SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
                                                                pD3D11_SamplerDesc.MinLOD = 0;
                                                                pD3D11_SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
                                                                pD3D11_TextureDesc.Width = SurfaceTextureWidth;
                                                                pD3D11_TextureDesc.Height = SurfaceTextureHeight;
                                                                pD3D11_TextureDesc.MipLevels = 1;
                                                                pD3D11_TextureDesc.ArraySize = 1;
                                                                pD3D11_TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                                                                pD3D11_TextureDesc.SampleDesc.Count = 1;
                                                                pD3D11_TextureDesc.Usage = D3D11_USAGE_DEFAULT;
                                                                pD3D11_TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                                                                pD3D11_TextureDesc.CPUAccessFlags = 0;
                                                                pD3D11_TextureDesc.MiscFlags = 0;
                                                                pD3D11_TextureData.pSysMem = SurfaceTextureRaw;
                                                                pD3D11_TextureData.SysMemPitch = SurfaceTextureWidth * 4;
                                                                pD3D11_TextureData.SysMemSlicePitch = 0;
                                                                pD3D11_ViewDesc.Format = pD3D11_TextureDesc.Format;
                                                                pD3D11_ViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                                                                pD3D11_ViewDesc.Texture2D.MipLevels = pD3D11_TextureDesc.MipLevels;
                                                                pD3D11_ViewDesc.Texture2D.MostDetailedMip = 0;
                                                                if ((hr = pD3D11_Device->CreateSamplerState(&pD3D11_SamplerDesc, &pD3D11_SamplerState)) != MB_OK) { DebugConsoleOutput("Error: CreateSamplerState()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                                                if (SUCCEEDED(hr))
                                                                {
                                                                    // Set DebugMenu function
                                                                    DebugDraw = (DebugDrawT)Draw_D3D11;

                                                                    // Deactivate DebugMenu
                                                                    DebugMenuInit = false;
                                                                    DebugConsoleOutput("DirectX11 init success!", false, "green");
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            pBackbuffer->Release();
        }
        if (DebugMenuInit)
        {
            // Remove hook
            D3D11_Subhook.Remove();

            // Trampoline
            HRESULT Trampoline = pD3D11_Present(pSwapChain, SyncInterval, Flags);

            // Reinstall Hook
            D3D11_Subhook.Install(D3D11_Present_Original_Address, D3D11_Present_Hook_Address);

            DebugConsoleOutput("DirectX 11 init failed!", false, "red");
            return Trampoline;
        }
    }
    else
    {
        RECT newWindowRect;
        BOOL windowRectReuslt = GetClientRect(MainWindowHandle, &newWindowRect);
        if (windowRectReuslt)
        {
            if (newWindowRect.right != MainWindowRect.right || newWindowRect.bottom != MainWindowRect.bottom)
            {
                // Resolution changed
                MainWindowRect = newWindowRect;
                UINT numViewports = 1;
                pD3D11_DeviceContext->RSGetViewports(&numViewports, &pD3D11_Viewport);
                if (pD3D11_Viewport.Width > 0 && pD3D11_Viewport.Height > 0)
                {
                    pD3D11_CustomViewport.Width = MainWindowRect.right;
                    pD3D11_CustomViewport.Height = MainWindowRect.bottom;
                    pD3D11_CustomViewport.TopLeftX = 0;
                    pD3D11_CustomViewport.TopLeftY = 0;
                    pD3D11_CustomViewport.MinDepth = 0.0f;
                    pD3D11_CustomViewport.MaxDepth = 1.0f;
                    pD3D11_DeviceContext->RSSetViewports(1, &pD3D11_CustomViewport);
                }
                else
                {
                    pD3D11_CustomViewport = pD3D11_Viewport;
                    pD3D11_DeviceContext->RSSetViewports(1, &pD3D11_CustomViewport);
                }
            }
        }
    }

    // Remove hook
    D3D11_Subhook.Remove();

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

    // Trampoline
    HRESULT Trampoline = pD3D11_Present(pSwapChain, SyncInterval, Flags);

    // Reinstall Hook
    if (sizeof(void*) == 8) D3D11_Subhook.Install(D3D11_Present_Original_Address, D3D11_Present_Hook_Address, subhook::HookFlags::HookFlag64BitOffset);
    if (sizeof(void*) == 4) D3D11_Subhook.Install(D3D11_Present_Original_Address, D3D11_Present_Hook_Address);

    return Trampoline;

    return 0;
}



//
// Init function --------------------------------------------------------------------
//
BOOL D3D11HookInit()
{
    if (GetModuleHandleA("d3d11.dll") == NULL) return false;

    try {
        // I love to comment comments
        DebugConsoleOutput("DirectX 11 detected!", false, "green");

        // Get vTable
        Direct3D11Hooking::Direct3D11 D3D11Hookah;
        std::vector<uintptr_t> vTable = D3D11Hookah.vtable();

        std::memcpy(pD3D11_SwapChain_vTable, pD3D11_SwapChain, sizeof(void*) * 18);

        // Set addresses
        D3D11_Present_Original_Address = (void*)vTable[8];
        D3D11_Present_Hook_Address = D3D11_Present_Hook;
        pD3D11_Present = (Present11T)D3D11_Present_Original_Address;

        // Install the Hook
        if (sizeof(void*) == 8) return D3D11_Subhook.Install(D3D11_Present_Original_Address, D3D11_Present_Hook_Address, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) return D3D11_Subhook.Install(D3D11_Present_Original_Address, D3D11_Present_Hook_Address);
        return false;
    }
    catch (const std::exception e)
    {
        DebugConsoleOutput("Error when init D3D11:", false, "red");
        DebugConsoleOutput(e.what(), false, "red");
    }

    return false;
}



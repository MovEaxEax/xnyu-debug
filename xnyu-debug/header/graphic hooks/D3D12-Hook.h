#pragma once
#define XM_NO_INTRINSICS

#include <d3d12.h>
#include <dxgi1_4.h>

namespace Direct3D12Hooking
{
    class Direct3D12 :
        public Direct3DHooking::Direct3DBase
    {
        ID3D12Device* pd3dDevice;
        ID3D12CommandQueue* pQueue;
        IDXGISwapChain* pSwapChain;

    public:
        Direct3D12();
        ~Direct3D12();
        std::vector<size_t> vtable() const override;
    };
}


using namespace Indicium::Core::Exceptions;

Direct3D12Hooking::Direct3D12::Direct3D12() :
	pd3dDevice(nullptr), pQueue(nullptr), pSwapChain(nullptr)
{
	temp_window = std::make_unique<Window>("TempDirect3D12OverlayWindow");

	const auto hModDXGI = GetModuleHandleA("DXGI.dll");
	const auto hModD3D12 = GetModuleHandleA("D3D12.dll");

	if (hModDXGI == nullptr)
	{
		throw ModuleNotFoundException("Could not get handle to DXGI.dll");
	}

	if (hModD3D12 == nullptr)
	{
		throw ModuleNotFoundException("Could not get handle to D3D12.dll");
	}

	const auto hD3D12CreateDevice = static_cast<LPVOID>(GetProcAddress(hModD3D12, "D3D12CreateDevice"));

	if (hD3D12CreateDevice == nullptr)
	{
		throw ProcAddressNotFoundException("Could not get handle to D3D12CreateDevice");
	}

	const auto hCreateDXGIFactory1 = static_cast<LPVOID>(GetProcAddress(hModDXGI, "CreateDXGIFactory1"));
	if (hCreateDXGIFactory1 == nullptr)
	{
		throw ProcAddressNotFoundException("Could not get handle to CreateDXGIFactory1");
	}

	IDXGIFactory4* pFactory;
	auto hr = static_cast<HRESULT(WINAPI*)(
		REFIID,
		void**)>(hCreateDXGIFactory1)(IID_PPV_ARGS(&pFactory));

	if (FAILED(hr))
	{
		throw DXAPIException("Could not create DXGI factory", hr);
	}

	const auto hr12 = static_cast<HRESULT(WINAPI*)(
		IUnknown*,
		D3D_FEATURE_LEVEL,
		REFIID,
		void**)>(hD3D12CreateDevice)(
			nullptr,
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&pd3dDevice));

	if (FAILED(hr12))
	{
		throw DXAPIException("Could not create D3D12 device", hr12);
	}

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	hr = pd3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pQueue));

	if (FAILED(hr))
	{
		throw DXAPIException("Command queue creation failed", hr);
	}

	DXGI_SWAP_CHAIN_DESC scDesc;
	ZeroMemory(&scDesc, sizeof(scDesc));
	scDesc.BufferCount = 2;
	scDesc.BufferDesc.Width = 0;
	scDesc.BufferDesc.Height = 0;
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.OutputWindow = temp_window->windowHandle();
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;
	scDesc.Windowed = TRUE;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	hr = pFactory->CreateSwapChain(
		pQueue,
		&scDesc,
		&pSwapChain
	);

	if (FAILED(hr))
	{
		throw DXAPIException("Swap chain creation failed", hr);
	}
}

// D3D12 Device
IDXGISwapChain* pD3D12_SwapChain;
IDXGISwapChain3* pD3D12_SwapChain3;
ID3D12Device* pD3D12_Device;
ID3D12GraphicsCommandList* pD3D12_GraphicsCommandList;
ID3D12CommandAllocator* pD3D12_CommandAllocator;
ID3D12CommandList* pD3D12_CommandList;
void* pD3D12_SwapChain_vTable[18];

std::vector<size_t> Direct3D12Hooking::Direct3D12::vtable() const
{
	pD3D12_SwapChain = pSwapChain;
	return std::vector<size_t>(*reinterpret_cast<size_t**>(pSwapChain),
		*reinterpret_cast<size_t**>(pSwapChain) + DXGIHooking::DXGI::SwapChainVTableElements);
}

Direct3D12Hooking::Direct3D12::~Direct3D12()
{
	if (pSwapChain)
		pSwapChain->Release();

	if (pd3dDevice)
		pd3dDevice->Release();

	if (pQueue)
		pQueue->Release();
}

// EndScene() Function Pointer
typedef HRESULT(__stdcall* Present12T)(IDXGISwapChain* swapChain, UINT SyncInterval, UINT Flags);
Present12T pD3D12_Present = nullptr;

// Addresses
void* D3D12_Present_Original_Address = 0;
void* D3D12_Present_Hook_Address = 0;

// Subhooks
subhook::Hook D3D12_Subhook;



//
// Drawing -------------------------------------------------------------------------
//
/*
void DrawFilledRectWithAlpha(ID3D12GraphicsCommandList* commandList, D3D12_RECT rect, XMFLOAT4 color)
{
	const float left = static_cast<float>(rect.left);
	const float top = static_cast<float>(rect.top);
	const float right = static_cast<float>(rect.right);
	const float bottom = static_cast<float>(rect.bottom);

	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

	Vertex vertices[] =
	{
		{ { left,  top,    0.0f }, color },
		{ { right, top,    0.0f }, color },
		{ { right, bottom, 0.0f }, color },
		{ { left,  bottom, 0.0f }, color }
	};

	D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices));
	ID3D12Resource* vertexBuffer = nullptr;
	commandList->GetDevice()->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexBuffer));

	void* mappedData = nullptr;
	vertexBuffer->Map(0, nullptr, &mappedData);
	memcpy(mappedData, vertices, sizeof(vertices));
	vertexBuffer->Unmap(0, nullptr);

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = {};
	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.StrideInBytes = sizeof(Vertex);
	vertexBufferView.SizeInBytes = sizeof(vertices);

	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
	commandList->DrawInstanced(6, 1, 0, 0);

	if (vertexBuffer)
	{
		vertexBuffer->Release();
		vertexBuffer = nullptr;
	}
}



void DrawTextureOnVertices(ID3D12GraphicsCommandList* commandList, ID3D12Device* device, unsigned char* textureData, int textureWidth, int textureHeight, float x, float y, float width, float height)
{
	struct Vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texcoord;
	};

	Vertex vertices[] =
	{
		{ { x,          y + height, 0.0f }, { 0.0f, 0.0f } },
		{ { x + width,  y + height, 0.0f }, { 1.0f, 0.0f } },
		{ { x + width,  y,          0.0f }, { 1.0f, 1.0f } },
		{ { x,          y,          0.0f }, { 0.0f, 1.0f } }
	};

	D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_R8G8B8A8_UNORM, textureWidth, textureHeight, 1, 1);
	ID3D12Resource* texture = nullptr;
	device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc,
		D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&texture));

	D3D12_SUBRESOURCE_DATA textureDataDesc = {};
	textureDataDesc.pData = textureData;
	textureDataDesc.RowPitch = textureWidth * 4;
	textureDataDesc.SlicePitch = textureDataDesc.RowPitch * textureHeight;

	UpdateSubresources(commandList, texture, nullptr, 0, 0, 1, &textureDataDesc);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView(texture, &srvDesc, commandList->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = {};
	vertexBufferView.BufferLocation = reinterpret_cast<UINT64>(vertices);
	vertexBufferView.StrideInBytes = sizeof(Vertex);
	vertexBufferView.SizeInBytes = sizeof(vertices);

	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	commandList->IASetVertexBuffers(0, 1, &vertexBufferView);

	commandList->SetGraphicsRootDescriptorTable(0, commandList->GetGPUDescriptorHandleForHeapStart());
	commandList->DrawInstanced(4, 1, 0, 0);

	if (texture)
	{
		texture->Release();
		texture = nullptr;
	}
}
*/



//
// Hook Routine ---------------------------------------------------------------------
//
HRESULT D3D12_Present_Hook(IDXGISwapChain* swapChain, UINT SyncInterval, UINT Flags)
{
	HRESULT Trampoline = 0;
	if (DebugMenuInit == true)
	{
		HRESULT hr = 0;

		// Set the device for the globals
		pD3D12_SwapChain = swapChain;
		pD3D12_SwapChain3 = reinterpret_cast<IDXGISwapChain3*>(pD3D12_SwapChain);
		pD3D12_SwapChain3->GetDevice(IID_PPV_ARGS(&pD3D12_Device));
		UINT currentBackBufferIndex = pD3D12_SwapChain3->GetCurrentBackBufferIndex();
		ID3D12CommandList* commandList = nullptr;
		IDXGIOutput* tmpBufferOutput = nullptr;
		pD3D12_SwapChain3->GetContainingOutput(&tmpBufferOutput);
		ID3D12CommandAllocator* commandAllocators[2];
		for (int i = 0; i < 2; i++) pD3D12_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocators[i]));
		hr = commandAllocators[currentBackBufferIndex]->QueryInterface(IID_PPV_ARGS(&pD3D12_CommandAllocator));
		pD3D12_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pD3D12_CommandAllocator, nullptr, IID_PPV_ARGS(&pD3D12_CommandList));

		// Set DebugMenu function
		//DebugDrawText = (DebugDrawTextT)DrawMessage_D3D12;
		//DebugDrawText = (DebugDrawTextT)DrawMessage_D3D12;

		// Deactivate DebugMenu
		DebugMenuInit = false;
	}

	// Remove hook
	D3D12_Subhook.Remove();

	// Trampoline
	Trampoline = pD3D12_Present(swapChain, SyncInterval, Flags);

	// Reinstall Hook
	if (sizeof(void*) == 8) D3D12_Subhook.Install(D3D12_Present_Original_Address, D3D12_Present_Hook_Address, subhook::HookFlags::HookFlag64BitOffset);
	if (sizeof(void*) == 4) D3D12_Subhook.Install(D3D12_Present_Original_Address, D3D12_Present_Hook_Address);

	// Debug Menu
	//DebugMenuMainRoutine();

	return Trampoline;
}



//
// Init function --------------------------------------------------------------------
//
BOOL D3D12HookInit()
{
	if (GetModuleHandleA("d3d12.dll") == NULL) return false;

	try {
		// I love to comment comments
		std::cout << "DirectX 12 detected!" << std::endl;

		// Get vTable
		Direct3D12Hooking::Direct3D12 D3D12Hookah;
		std::vector<uintptr_t> vTable = D3D12Hookah.vtable();

		std::memcpy(pD3D12_SwapChain_vTable, pD3D12_SwapChain, sizeof(void*) * 18);

		// Set addresses
		D3D12_Present_Original_Address = (void*)vTable[8];
		pD3D12_Present = (Present12T)D3D12_Present_Original_Address;
		D3D12_Present_Hook_Address = D3D12_Present_Hook;

		// Install the Hook
		if (sizeof(void*) == 8) return D3D12_Subhook.Install(D3D12_Present_Original_Address, D3D12_Present_Hook_Address, subhook::HookFlags::HookFlag64BitOffset);
		if (sizeof(void*) == 4) return D3D12_Subhook.Install(D3D12_Present_Original_Address, D3D12_Present_Hook_Address);

		return true;
	}
	catch (const std::exception e)
	{
		std::cout << "Error when init D3D12: \n" << e.what() << std::endl;
	}

	return false;
}

bool D3D12HookUninit()
{
	return true;

}


#pragma once
#define XM_NO_INTRINSICS



// --- Typedefs ---
typedef HRESULT(__stdcall* D3D12_PresentT)(IDXGISwapChain* swapChain, UINT SyncInterval, UINT Flags);



// --- Structs ---
struct VertexD3D12
{
	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
};

struct D3D12RenderStatesBackup
{
	D3D12_PRIMITIVE_TOPOLOGY topology;
	ID3D12PipelineState* pipelineState;
	ID3D12DescriptorHeap* descriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
	ID3D12RootSignature* rootSignature;
	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;
	ID3D12Resource* vertexBuffers[D3D12_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViews[D3D12_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	ID3D12Resource* indexBuffer;
	D3D12_INDEX_BUFFER_VIEW indexBufferView;
	ID3D12Resource* constantBuffers[D3D12_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
	FLOAT blendFactor[4];
	UINT stencilRef;
};



// --- Variables ---
extern ID3D12Device* D3D12_Device;
extern ID3D12CommandQueue* D3D12_CommandQueue;
extern IDXGISwapChain* D3D12_SwapChain;
extern IDXGISwapChain3* D3D12_SwapChain3;
extern ID3D12CommandAllocator* D3D12_CommandAllocator;
extern ID3D12GraphicsCommandList* D3D12_GraphicsCommandList;
extern D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
extern ID3D12PipelineState* D3D12_PipelineState;
extern VertexD3D12 D3D12_Verts[4];

extern const char* D3D12_TextureShader;



// --- Functions ---
std::vector<uintptr_t> GetVTable_D3D12();
void BackUpOldStates_D3D12(D3D12RenderStatesBackup& backup);
void RestoreOldStates_D3D12(D3D12RenderStatesBackup& backup);
void ClearStates_D3D12();
void Draw_D3D12();
bool HookInit_D3D12();
bool HookUninit_D3D12();



// --- D3D12 Present() ---
template <typename FuncT>
class D3D12_PresentHook : public xNyuHook<D3D12_PresentT> {
private:

public:
	static D3D12_PresentHook* instance;
	D3D12_PresentHook(void* originalAddress) : xNyuHook<D3D12_PresentT>(originalAddress, CustomHook) { instance = this; }
	static HRESULT __stdcall CustomHook(IDXGISwapChain* swapChain, UINT SyncInterval, UINT Flags)
	{
		if (instance->HookInit)
		{
			DebugConsoleOutput("D3D12_Present() Hook active...", true, "yellow");
			instance->HookInit = false;

			// Init D3D12
			D3D12_SwapChain = swapChain;
			D3D12_SwapChain3 = reinterpret_cast<IDXGISwapChain3*>(D3D12_SwapChain);
			D3D12_SwapChain3->GetDevice(IID_PPV_ARGS(&D3D12_Device));
			UINT currentBackBufferIndex = D3D12_SwapChain3->GetCurrentBackBufferIndex();
			ID3D12CommandList* commandList = nullptr;
			IDXGIOutput* tmpBufferOutput = nullptr;
			D3D12_SwapChain3->GetContainingOutput(&tmpBufferOutput);
			ID3D12CommandAllocator* commandAllocators[2];
			for (int i = 0; i < 2; i++) D3D12_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocators[i]));
			hr = commandAllocators[currentBackBufferIndex]->QueryInterface(IID_PPV_ARGS(&D3D12_CommandAllocator));
			D3D12_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_CommandAllocator, nullptr, IID_PPV_ARGS(&D3D12_GraphicsCommandList));

			// Create PSO shader
			ID3DBlob* vertexShaderBlob;
			D3DCompile(D3D11_TextureShader, strlen(D3D11_TextureShader), nullptr, nullptr, nullptr, "VS", "vs_5_0", 0, 0, &vertexShaderBlob, nullptr);
			ID3DBlob* pixelShaderBlob;
			D3DCompile(D3D11_TextureShader, strlen(D3D11_TextureShader), nullptr, nullptr, nullptr, "PS", "ps_5_0", 0, 0, &pixelShaderBlob, nullptr);
			D3D12_PSODesc.VS = { reinterpret_cast<UINT8*>(vertexShaderBlob->GetBufferPointer()), vertexShaderBlob->GetBufferSize() };
			D3D12_PSODesc.PS = { reinterpret_cast<UINT8*>(pixelShaderBlob->GetBufferPointer()), pixelShaderBlob->GetBufferSize() };
			D3D12_Device->CreateGraphicsPipelineState(&D3D12_PSODesc, IID_PPV_ARGS(&D3D12_PipelineState));
			vertexShaderBlob->Release();
			pixelShaderBlob->Release();

			// Set DebugMenu function
			DebugDraw = (DebugDrawT)Draw_D3D12;

			DebugConsoleOutput("DirectX 12 init success!", false, "green");
		}

		// Remove hook
		instance->remove();

		ThreadHookerUpdateThreads();

		// TAS routine
		if (GlobalSettings.config_tashook == "graphics") pTASRoutine();

		// Debug Menu
		DebugMenuMainRoutine();

		return instance->callTrampoline(swapChain, SyncInterval, Flags);
	}
};



#pragma once


// --- Typedefs ---
typedef HRESULT(__stdcall* D3D10_PresentT)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);



// --- Structs ---
struct VertexD3D10
{
    float x, y, z, rhw;
    float u, v;
};

struct D3D10RenderStatesBackup
{
    ID3D10BlendState* blendState;
    FLOAT blendFactor[4];
    UINT sampleMask;
    ID3D10DepthStencilState* depthStencilState;
    UINT stencilRef;
    ID3D10RasterizerState* rasterizerState;
    ID3D10VertexShader* vertexShader;
    ID3D10PixelShader* pixelShader;
    ID3D10GeometryShader* geometryShader;
    ID3D10SamplerState* samplerState[4];
    ID3D10InputLayout* inputLayout;
    D3D10_VIEWPORT viewports[D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
    UINT numViewports;
    ID3D10RenderTargetView* renderTargetViews[D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT];
    ID3D10DepthStencilView* depthStencilView;
};



// --- Variables ---
extern ID3D10Device* D3D10_Device;
extern IDXGISwapChain* D3D10_SwapChain;

extern D3D10_INPUT_ELEMENT_DESC D3D10_TextureLayoutDesc[];
extern UINT D3D10_TextureLayoutElements = 0;
extern ID3D10InputLayout* D3D10_TextureLayout;

extern D3D10_TEXTURE2D_DESC D3D10_TextureDesc;
extern ID3D10Texture2D* D3D10_Texture;
extern ID3D10ShaderResourceView* D3D10_TextureSRV;

extern D3D10_BUFFER_DESC D3D10_VertexBufferDesc;
extern ID3D10Buffer* D3D10_VertexBuffer;

extern ID3D10PixelShader* D3D10_PixelShader;
extern ID3D10VertexShader* D3D10_VertexShader;

extern const char* D3D10_TextureShader;



// --- Functions ---
std::vector<uintptr_t> GetVTable_D3D10();
void BackUpOldStates_D3D10(D3D10RenderStatesBackup& backup);
void RestoreOldStates_D3D10(D3D10RenderStatesBackup& backup);
void ClearStates_D3D10();
void Draw_D3D10();
bool HookInit_D3D10();
bool HookUninit_D3D10();



// --- D3D10 Present() ---
template <typename FuncT>
class D3D10_PresentHook : public xNyuHook<D3D10_PresentT> {
private:

public:
    static D3D10_PresentHook* instance;
    D3D10_PresentHook(void* originalAddress) : xNyuHook<D3D10_PresentT>(originalAddress, CustomHook) { instance = this; }
    static HRESULT __stdcall CustomHook(IDirect3DDevice10* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
    {
        if (instance->HookInit)
        {
            DebugConsoleOutput("D3D10_Present() Hook active...", true, "yellow");
            instance->HookInit = false;

            // Get device
            D3D10_SwapChain->GetDevice(__uuidof(D3D10_Device), (void**)&D3D10_Device);

            // Create texture and SRV
            ZeroMemory(&D3D10_TextureDesc, sizeof(D3D10_TextureDesc));
            D3D10_SurfaceTextureDesc.Width = SurfaceTextureWidth;
            D3D10_SurfaceTextureDesc.Height = SurfaceTextureHeight;
            D3D10_SurfaceTextureDesc.MipLevels = 1;
            D3D10_SurfaceTextureDesc.ArraySize = 1;
            D3D10_SurfaceTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            D3D10_SurfaceTextureDesc.SampleDesc.Count = 1;
            D3D10_SurfaceTextureDesc.Usage = D3D10_USAGE_DYNAMIC;
            D3D10_SurfaceTextureDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
            D3D10_Device->CreateTexture2D(&D3D10_TextureDesc, NULL, &D3D10_Texture);
            D3D10_Device->CreateShaderResourceView(D3D10_Texture, NULL, &D3D10_TextureSRV);

            // Shader Compilation
            ID3D10Blob* vertexShaderBlob = nullptr;
            ID3D10Blob* pixelShaderBlob = nullptr;
            ID3D10Blob* pErrorBlob = nullptr;

            // Compile/Create pixel and vertex shader
            D3DCompile(D3D10_TextureShader, strlen(D3D10_TextureShader), nullptr, nullptr, nullptr, "VertexShader", "vs_4_0", 0, 0, &vertexShaderBlob, &pErrorBlob);
            D3DCompile(D3D10_TextureShader, strlen(D3D10_TextureShader), nullptr, nullptr, nullptr, "PixelShader", "ps_4_0", 0, 0, &pixelShaderBlob, &pErrorBlob);
            D3D10_Device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &D3D10_VertexShader);
            D3D10_Device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), &D3D10_PixelShader);

            // Create layout
            D3D10_TextureLayoutDesc[] =
            {
                { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
                { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D10_INPUT_PER_VERTEX_DATA, 0 }
            };
            D3D10_TextureLayoutElements = sizeof(layout) / sizeof(layout[0]);
            D3D10_Device->CreateInputLayout(D3D10_TextureLayoutDesc, D3D10_TextureLayoutElements, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &D3D10_TextureLayout);

            // Create vertex buffer
            ZeroMemory(&D3D10_VertexBufferDesc, sizeof(D3D10_VertexBufferDesc));
            D3D10_VertexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
            D3D10_VertexBufferDesc.ByteWidth = sizeof(VertexD3D10) * 4;
            D3D10_VertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
            D3D10_VertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
            D3D10_VertexBufferDesc.MiscFlags = 0;
            D3D10_Device->CreateBuffer(&D3D10_VertexBufferDesc, NULL, D3D10_VertexBuffer);

            // Clean up
            vertexShaderBlob->Release();
            pixelShaderBlob->Release();

            // Set DebugMenu function
            DebugDraw = (DebugDrawT)Draw_D3D10;

            DebugConsoleOutput("DirectX 10 init success!", false, "green");
        }

        // Remove hook
        instance->remove();

        ThreadHookerUpdateThreads();

        // TAS routine
        if (GlobalSettings.config_tashook == "graphics") pTASRoutine();

        // Debug Menu
        DebugMenuMainRoutine();

        return instance->callTrampoline(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
    }
};



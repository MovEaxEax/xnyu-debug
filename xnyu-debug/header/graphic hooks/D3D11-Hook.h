#pragma once



// --- Typedefs ---
typedef HRESULT(__stdcall* D3D11_PresentT)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);



// --- Structs ---
struct VertexD3D11
{
    XMFLOAT3 pos;
    XMFLOAT2 texCoord;
};

struct D3D11RenderStatesBackup
{
    ID3D11InputLayout* inputLayout;
    D3D11_PRIMITIVE_TOPOLOGY topology;
    ID3D11Buffer* vertexBuffer;
    UINT vertexBufferStride;
    UINT vertexBufferOffset;
    ID3D11Buffer* indexBuffer;
    DXGI_FORMAT indexBufferFormat;
    UINT indexBufferOffset;
    ID3D11VertexShader* vertexShader;
    UINT vertexShaderNumClassInstances;
    ID3D11Buffer* constantBuffer;
    ID3D11PixelShader* pixelShader;
    UINT pixelShaderNumClassInstances;
    ID3D11Buffer* pixelConstantBuffer;
    ID3D11ShaderResourceView* shaderResourceView;
    ID3D11SamplerState* sampler;
    UINT numViewports;
    D3D11_VIEWPORT viewport;
    UINT numScissorRects;
    D3D11_RECT scissorRect;
    ID3D11RasterizerState* rasterizerState;
    ID3D11RenderTargetView* renderTargetView[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
    ID3D11DepthStencilView* depthStencilView;
    ID3D11BlendState* blendState;
    FLOAT blendFactor[4];
    UINT sampleMask;
    ID3D11DepthStencilState* depthStencilState;
    UINT stencilRef;
};



// --- Variables ---
extern IDXGISwapChain* D3D11_SwapChain;
extern IDXGISurface* D3D11_Surface;
extern ID3D11Device* D3D11_Device;
extern ID3D11DeviceContext* D3D11_DeviceContext;

extern ID3D11VertexShader* D3D11_VertexShader;
extern ID3D11InputLayout* D3D11_VertexLayout;
extern ID3D11PixelShader* D3D11_PixelShader;
extern ID3D11Buffer* D3D11_VertexBuffer;
extern ID3D11Buffer* D3D11_IndexBuffer;
extern ID3D11Buffer* D3D11_ConstantBuffer;
extern ID3D11SamplerState* D3D11_SamplerState;
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

extern HWND D3D11_Window;
extern ID3D11DeviceContext* D3D11_DeviceContext;
extern ID3D11RenderTargetView* D3D11_RenderTargetView;
extern ID3D11DepthStencilView* D3D11_DepthStencilView;
extern D3D11_VIEWPORT D3D11_Viewport;
extern D3D11_VIEWPORT D3D11_CustomViewport;
extern D3D11_BLEND_DESC D3D11_BlendDesc;
extern ID3D11BlendState* D3D11_BlendState;
extern float D3D11_BlendFactor[4];
extern UINT D3D11_SampleMask;
extern D3D11_DEPTH_STENCIL_DESC D3D11_DepthStencilDesc;
extern ID3D11DepthStencilState* D3D11_DepthStencilState;

extern const char* D3D11_TextureShader;



// --- Functions ---
std::vector<uintptr_t> GetVTable_D3D11();
void BackUpOldStates_D3D11(D3D11RenderStatesBackup& backup);
void RestoreOldStates_D3D11(D3D11RenderStatesBackup& backup);
void ClearStates_D3D11();
void Draw_D3D11();
bool HookInit_D3D11();
bool HookUninit_D3D11();



// --- D3D11 Present() ---
template <typename FuncT>
class D3D11_PresentHook : public xNyuHook<D3D11_PresentT> {
private:

public:
    static D3D11_PresentHook* instance;
    D3D11_PresentHook(void* originalAddress) : xNyuHook<D3D11_PresentT>(originalAddress, CustomHook) { instance = this; }
    static HRESULT __stdcall CustomHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
    {
        if (instance->HookInit)
        {
            DebugConsoleOutput("D3D11_Present() Hook active...", true, "yellow");
            instance->HookInit = false;

            if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(D3D11_Device), (void**)&D3D11_Device)))
            {
                HRESULT hr = -1;

                ///////////////////////
                // INIT GLOBAL STUFF //
                ///////////////////////

                // Getting swapchain
                D3D11_SwapChain = pSwapChain;

                // Getting device context
                D3D11_Device->GetImmediateContext(&D3D11_DeviceContext);

                // Create custom viewport
                UINT numViewports = 1;
                D3D11_DeviceContext->RSGetViewports(&numViewports, &D3D11_Viewport);
                if (D3D11_Viewport.Width > 0 && D3D11_Viewport.Height > 0)
                {
                    RECT windowRect;
                    if (!GetClientRect(MainWindowHandle, &windowRect)) DebugConsoleOutput("Error: GetClientRect()", false, "red");

                    D3D11_CustomViewport.Width = windowRect.right;
                    D3D11_CustomViewport.Height = windowRect.bottom;
                    D3D11_CustomViewport.TopLeftX = windowRect.left;
                    D3D11_CustomViewport.TopLeftY = windowRect.top;
                    D3D11_CustomViewport.MinDepth = 0.0f;
                    D3D11_CustomViewport.MaxDepth = 1.0f;
                    D3D11_DeviceContext->RSSetViewports(1, &D3D11_CustomViewport);
                }
                else
                {
                    D3D11_CustomViewport = D3D11_Viewport;
                    D3D11_DeviceContext->RSSetViewports(1, &D3D11_CustomViewport);
                }

                // Get render target
                D3D11_DeviceContext->OMGetRenderTargets(1, &D3D11_RenderTargetView, nullptr);
                ID3D11Texture2D* pBackbuffer = nullptr;
                if ((hr = D3D11_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackbuffer))) != MB_OK) { DebugConsoleOutput("Error: GetBuffer()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                if (SUCCEEDED(hr))
                {
                    if ((hr = D3D11_Device->CreateRenderTargetView(pBackbuffer, nullptr, &D3D11_RenderTargetView)) != MB_OK) { DebugConsoleOutput("Error: CreateRenderTargetView()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                    if (SUCCEEDED(hr))
                    {
                        // Create stencil depth view
                        D3D11_TEXTURE2D_DESC depthStencilDesc = {};
                        depthStencilDesc.Width = D3D11_CustomViewport.Width;
                        depthStencilDesc.Height = D3D11_CustomViewport.Height;
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
                        if ((hr = D3D11_Device->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilBuffer)) != MB_OK) { DebugConsoleOutput("Error: CreateTexture2D()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                        if (SUCCEEDED(hr))
                        {
                            D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
                            depthStencilViewDesc.Format = depthStencilDesc.Format;
                            depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
                            depthStencilViewDesc.Texture2D.MipSlice = 0;
                            if ((hr = D3D11_Device->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &D3D11_DepthStencilView)) != MB_OK) { DebugConsoleOutput("Error: CreateDepthStencilView()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                            if (SUCCEEDED(hr))
                            {
                                // Create stencil depth state
                                D3D11_DepthStencilDesc.DepthEnable = false;
                                D3D11_DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
                                D3D11_DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
                                D3D11_DepthStencilDesc.StencilEnable = true;
                                D3D11_DepthStencilDesc.StencilReadMask = 0xFF;
                                D3D11_DepthStencilDesc.StencilWriteMask = 0xFF;
                                D3D11_DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
                                D3D11_DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
                                D3D11_DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
                                D3D11_DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
                                D3D11_DepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
                                D3D11_DepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
                                D3D11_DepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
                                D3D11_DepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
                                D3D11_Device->CreateDepthStencilState(&D3D11_DepthStencilDesc, &D3D11_DepthStencilState);

                                // Creating blend state
                                D3D11_BlendDesc.AlphaToCoverageEnable = false;
                                D3D11_BlendDesc.IndependentBlendEnable = false;
                                D3D11_BlendDesc.RenderTarget[0].BlendEnable = true;
                                D3D11_BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
                                D3D11_BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
                                D3D11_BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
                                D3D11_BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;// D3D11_BLEND_ONE;
                                D3D11_BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;// D3D11_BLEND_ZERO;
                                D3D11_BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
                                D3D11_BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
                                D3D11_BlendFactor[0] = 0.0f;
                                D3D11_BlendFactor[1] = 0.0f;
                                D3D11_BlendFactor[2] = 0.0f;
                                D3D11_BlendFactor[3] = 0.0f;
                                D3D11_SampleMask = 0xffffffff;
                                if ((hr = D3D11_Device->CreateBlendState(&D3D11_BlendDesc, &D3D11_BlendState)) != MB_OK) { DebugConsoleOutput("Error: CreateBlendState()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
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
                                        if ((hr = D3D11_Device->CreateVertexShader(pCompiledShaderBlob->GetBufferPointer(), pCompiledShaderBlob->GetBufferSize(), nullptr, &D3D11_VertexShader)) != MB_OK) { DebugConsoleOutput("Error: CreateVertexShader()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                        if (SUCCEEDED(hr))
                                        {
                                            // Create Pixel shader
                                            D3D11_Layout[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
                                            D3D11_Layout[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };

                                            UINT numElements = ARRAYSIZE(D3D11_Layout);
                                            if ((hr = D3D11_Device->CreateInputLayout(D3D11_Layout, numElements, pCompiledShaderBlob->GetBufferPointer(), pCompiledShaderBlob->GetBufferSize(), &D3D11_VertexLayout)) != MB_OK) { DebugConsoleOutput("Error: CreateInputLayout()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                            if (SUCCEEDED(hr))
                                            {
                                                D3D11_DeviceContext->IASetInputLayout(D3D11_VertexLayout);
                                                pCompiledShaderBlob->Release();
                                                if ((hr = D3DCompile(TextureShader, strlen(TextureShader), 0, nullptr, nullptr, "PS", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &pCompiledShaderBlob, nullptr)) != MB_OK) { DebugConsoleOutput("Error: D3DCompile()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                                if (SUCCEEDED(hr))
                                                {
                                                    if ((hr = D3D11_Device->CreatePixelShader(pCompiledShaderBlob->GetBufferPointer(), pCompiledShaderBlob->GetBufferSize(), nullptr, &D3D11_PixelShader)) != MB_OK) { DebugConsoleOutput("Error: CreatePixelShader()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                                    if (SUCCEEDED(hr))
                                                    {
                                                        // Constant buffer settings 
                                                        D3D11_OrthographicProjectionMatrix = XMMatrixOrthographicOffCenterLH(0, D3D11_CustomViewport.Width, D3D11_CustomViewport.Height, 0, 0.0f, 1.0f);
                                                        D3D11_BUFFER_DESC buffer_desc_{ 0 };
                                                        buffer_desc_.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
                                                        buffer_desc_.ByteWidth = sizeof(D3D11_OrthographicProjectionMatrix);
                                                        buffer_desc_.Usage = D3D11_USAGE_DEFAULT;
                                                        D3D11_SUBRESOURCE_DATA subresource_rectangle_constant_{ 0 };
                                                        subresource_rectangle_constant_.pSysMem = &D3D11_OrthographicProjectionMatrix;
                                                        if ((hr = D3D11_Device->CreateBuffer(&buffer_desc_, &subresource_rectangle_constant_, &D3D11_ConstantBuffer)) != MB_OK) { DebugConsoleOutput("Error: CreateBuffer()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
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
                                                            if ((hr = D3D11_Device->CreateBuffer(&buffer_desc_index_, &subresource_index_, &D3D11_IndexBuffer)) != MB_OK) { DebugConsoleOutput("Error: CreateBuffer()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                                            if (SUCCEEDED(hr))
                                                            {
                                                                // Vertex buffer settings 
                                                                D3D11_BufferVertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                                                                D3D11_BufferVertexDesc.ByteWidth = sizeof(VertexD3D11) * 4;
                                                                D3D11_BufferVertexDesc.Usage = D3D11_USAGE_DYNAMIC;
                                                                D3D11_BufferVertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
                                                                D3D11_BufferVertexDesc.MiscFlags = 0;
                                                                D3D11_BufferVertexDesc.StructureByteStride = 0;
                                                                D3D11_BufferVertexSubresourceLine.pSysMem = &D3D11_Verts;
                                                                if ((hr = D3D11_Device->CreateBuffer(&D3D11_BufferVertexDesc, &D3D11_BufferVertexSubresourceLine, &D3D11_VertexBuffer)) != MB_OK) { DebugConsoleOutput("Error: CreateBuffer()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
                                                                if (SUCCEEDED(hr))
                                                                {
                                                                    // Texture settings
                                                                    D3D11_SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
                                                                    D3D11_SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
                                                                    D3D11_SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
                                                                    D3D11_SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
                                                                    D3D11_SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
                                                                    D3D11_SamplerDesc.MinLOD = 0;
                                                                    D3D11_SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
                                                                    D3D11_TextureDesc.Width = SurfaceTextureWidth;
                                                                    D3D11_TextureDesc.Height = SurfaceTextureHeight;
                                                                    D3D11_TextureDesc.MipLevels = 1;
                                                                    D3D11_TextureDesc.ArraySize = 1;
                                                                    D3D11_TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                                                                    D3D11_TextureDesc.SampleDesc.Count = 1;
                                                                    D3D11_TextureDesc.Usage = D3D11_USAGE_DEFAULT;
                                                                    D3D11_TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                                                                    D3D11_TextureDesc.CPUAccessFlags = 0;
                                                                    D3D11_TextureDesc.MiscFlags = 0;
                                                                    D3D11_TextureData.pSysMem = SurfaceTextureRaw;
                                                                    D3D11_TextureData.SysMemPitch = SurfaceTextureWidth * 4;
                                                                    D3D11_TextureData.SysMemSlicePitch = 0;
                                                                    D3D11_ViewDesc.Format = D3D11_TextureDesc.Format;
                                                                    D3D11_ViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                                                                    D3D11_ViewDesc.Texture2D.MipLevels = D3D11_TextureDesc.MipLevels;
                                                                    D3D11_ViewDesc.Texture2D.MostDetailedMip = 0;
                                                                    if ((hr = D3D11_Device->CreateSamplerState(&D3D11_SamplerDesc, &D3D11_SamplerState)) != MB_OK) { DebugConsoleOutput("Error: CreateSamplerState()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
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

            // Set DebugMenu function
            DebugDraw = (DebugDrawT)Draw_D3D11;

            DebugConsoleOutput("DirectX 11 init success!", false, "green");
        }

        // Remove hook
        instance->remove();

        ThreadHookerUpdateThreads();

        // TAS routine
        if (GlobalSettings.config_tashook == "graphics") pTASRoutine();

        // Debug Menu
        DebugMenuMainRoutine();

        return instance->callTrampoline(pSwapChain, SyncInterval, Flags);
    }
};





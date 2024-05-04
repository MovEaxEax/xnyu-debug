#pragma once



// --- Structs ---
struct VertexD3D9
{
    float x, y, z, rhw;
    float u, v;
};

struct D3D9RenderStatesBackup
{
    IDirect3DVertexShader9* vertexShader;
    IDirect3DPixelShader9* pixelShader;
    DWORD renderStates[D3DRS_POINTSIZE_MAX];
    DWORD samplerStates[2][D3DSAMP_DMAPOFFSET + 1];
};



// --- Variables ---
extern IDirect3DDevice9* D3D9_Device;

extern const char* D3D9_TextureShader;

extern LPDIRECT3DVERTEXSHADER9 D3D9_BackupVertexShader;
extern LPDIRECT3DPIXELSHADER9 D3D9_BackupPixelShader;
extern LPDIRECT3DPIXELSHADER9 D3D9_PixelShader;
extern LPDIRECT3DTEXTURE9 D3D9_SurfaceTexture;



// --- Functions ---
std::vector<uintptr_t> GetVTable_D3D9();
void BackUpOldStates_D3D9(D3D9RenderStatesBackup& backup);
void RestoreOldStates_D3D9(D3D9RenderStatesBackup& backup);
void ClearStates_D3D9();
void Draw_D3D9();
bool HookInit_D3D9();
bool HookUninit_D3D9();



// --- D3D9 Present() ---
template <typename FuncT>
class D3D9_PresentHook : public xNyuHook<D3D9_PresentT> {
private:

public:
    static D3D9_PresentHook* instance;
    D3D9_PresentHook(void* originalAddress) : xNyuHook<D3D9_PresentT>(originalAddress, CustomHook) { instance = this; }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
    {
        if (instance->HookInit)
        {
            DebugConsoleOutput("D3D9_Present() Hook active...", true, "yellow");
            instance->HookInit = false;

            // Init D3D9
            pD3D9_Device = pDevice;

            // Error buffer
            LPD3DXBUFFER pShaderBuffer = NULL;
            LPD3DXBUFFER pErrorBuffer = NULL;

            // Create Texture
            HRESULT hr = 0;
            hr = D3DXCreateTexture(pD3D9_Device, SurfaceTextureWidth, SurfaceTextureHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &D3D9_SurfaceTexture);
            if (FAILED(hr)) { DebugConsoleOutput("Error: D3DXCreateTexture()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }

            // Compile shader code
            hr = D3DXCompileShader(D3D9_TextureShader, strlen(D3D9_TextureShader), NULL, NULL, "main", "ps_2_0", 0, &pShaderBuffer, &pErrorBuffer, NULL);
            if (FAILED(hr)) { DebugConsoleOutput("Error: CompilePixelShader()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }
            hr = pD3D9_Device->CreatePixelShader(reinterpret_cast<DWORD*>(pShaderBuffer->GetBufferPointer()), &D3D9_PixelShader);
            if (FAILED(hr)) { DebugConsoleOutput("Error: CreatePixelShader()", false, "red"); DebugConsoleOutput(std::string(DXGetErrorStringA(hr)), false, "red"); }

            // Set DebugMenu function
            DebugDraw = (DebugDrawT)Draw_D3D9;

            DebugConsoleOutput("DirectX 9 init success!", false, "green");
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





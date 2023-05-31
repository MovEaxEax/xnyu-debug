#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#include <DXErr.h>
#pragma comment(lib, "DXErr.lib")

typedef HRESULT(__stdcall* D3D9_QueryInterfaceT)(IDirect3DDevice9* pDevice, REFIID riid, void** ppvObj);
typedef ULONG(__stdcall* D3D9_AddRefT)(IDirect3DDevice9* pDevice);
typedef ULONG(__stdcall* D3D9_ReleaseT)(IDirect3DDevice9* pDevice);
typedef HRESULT(__stdcall* D3D9_TestCooperativeLevelT)(IDirect3DDevice9* pDevice);
typedef UINT(__stdcall* D3D9_GetAvailableTextureMemT)(IDirect3DDevice9* pDevice);
typedef HRESULT(__stdcall* D3D9_EvictManagedResourcesT)(IDirect3DDevice9* pDevice);
typedef HRESULT(__stdcall* D3D9_GetDirect3DT)(IDirect3DDevice9* pDevice, IDirect3D9** ppD3D9);
typedef HRESULT(__stdcall* D3D9_GetDeviceCapsT)(IDirect3DDevice9* pDevice, D3DCAPS9* pCaps);
typedef HRESULT(__stdcall* D3D9_GetDisplayModeT)(IDirect3DDevice9* pDevice, UINT iSwapChain, D3DDISPLAYMODE* pMode);
typedef HRESULT(__stdcall* D3D9_GetCreationParametersT)(IDirect3DDevice9* pDevice, D3DDEVICE_CREATION_PARAMETERS* pParameters);
typedef HRESULT(__stdcall* D3D9_SetCursorPropertiesT)(IDirect3DDevice9* pDevice, UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap);
typedef void(__stdcall* D3D9_SetCursorPositionT)(IDirect3DDevice9* pDevice, int X, int Y, DWORD Flags);
typedef BOOL(__stdcall* D3D9_ShowCursorT)(IDirect3DDevice9* pDevice, BOOL bShow);
typedef HRESULT(__stdcall* D3D9_CreateAdditionalSwapChainT)(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain);
typedef HRESULT(__stdcall* D3D9_GetSwapChainT)(IDirect3DDevice9* pDevice, UINT iSwapChain, IDirect3DSwapChain9** pSwapChain);
typedef UINT(__stdcall* D3D9_GetNumberOfSwapChainsT)(IDirect3DDevice9* pDevice);
typedef HRESULT(__stdcall* D3D9_ResetT)(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
typedef HRESULT(__stdcall* D3D9_PresentT)(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
typedef HRESULT(__stdcall* D3D9_GetBackBufferT)(IDirect3DDevice9* pDevice, UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer);
typedef HRESULT(__stdcall* D3D9_GetRasterStatusT)(IDirect3DDevice9* pDevice, UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus);
typedef HRESULT(__stdcall* D3D9_SetDialogBoxModeT)(IDirect3DDevice9* pDevice, BOOL bEnableDialogs);
typedef void(__stdcall* D3D9_SetGammaRampT)(IDirect3DDevice9* pDevice, UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP* pRamp);
typedef void(__stdcall* D3D9_GetGammaRampT)(IDirect3DDevice9* pDevice, UINT iSwapChain, D3DGAMMARAMP* pRamp);
typedef HRESULT(__stdcall* D3D9_CreateTextureT)(IDirect3DDevice9* pDevice, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle);
typedef HRESULT(__stdcall* D3D9_CreateVolumeTextureT)(IDirect3DDevice9* pDevice, UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle);
typedef HRESULT(__stdcall* D3D9_CreateCubeTextureT)(IDirect3DDevice9* pDevice, UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle);
typedef HRESULT(__stdcall* D3D9_CreateVertexBufferT)(IDirect3DDevice9* pDevice, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle);
typedef HRESULT(__stdcall* D3D9_CreateIndexBufferT)(IDirect3DDevice9* pDevice, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle);
typedef HRESULT(__stdcall* D3D9_CreateRenderTargetT)(IDirect3DDevice9* pDevice, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle);
typedef HRESULT(__stdcall* D3D9_CreateDepthStencilSurfaceT)(IDirect3DDevice9* pDevice, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle);
typedef HRESULT(__stdcall* D3D9_UpdateSurfaceT)(IDirect3DDevice9* pDevice, IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, POINT* pDestPoint);
typedef HRESULT(__stdcall* D3D9_UpdateTextureT)(IDirect3DDevice9* pDevice, IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture);
typedef HRESULT(__stdcall* D3D9_GetRenderTargetDataT)(IDirect3DDevice9* pDevice, IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface);
typedef HRESULT(__stdcall* D3D9_GetFrontBufferDataT)(IDirect3DDevice9* pDevice, UINT iSwapChain, IDirect3DSurface9* pDestSurface);
typedef HRESULT(__stdcall* D3D9_StretchRectT)(IDirect3DDevice9* pDevice, IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter);
typedef HRESULT(__stdcall* D3D9_ColorFillT)(IDirect3DDevice9* pDevice, IDirect3DSurface9* pSurface, const RECT* pRect, D3DCOLOR color);
typedef HRESULT(__stdcall* D3D9_CreateOffscreenPlainSurfaceT)(IDirect3DDevice9* pDevice, UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle);
typedef HRESULT(__stdcall* D3D9_SetRenderTargetT)(IDirect3DDevice9* pDevice, DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget);
typedef HRESULT(__stdcall* D3D9_GetRenderTargetT)(IDirect3DDevice9* pDevice, DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget);
typedef HRESULT(__stdcall* D3D9_SetDepthStencilSurfaceT)(IDirect3DDevice9* pDevice, IDirect3DSurface9* pNewZStencil);
typedef HRESULT(__stdcall* D3D9_GetDepthStencilSurfaceT)(IDirect3DDevice9* pDevice, IDirect3DSurface9** ppZStencilSurface);
typedef HRESULT(__stdcall* D3D9_BeginSceneT)(IDirect3DDevice9* pDevice);
typedef HRESULT(__stdcall* D3D9_EndSceneT)(IDirect3DDevice9* pDevice);
typedef HRESULT(__stdcall* D3D9_ClearT)(IDirect3DDevice9* pDevice, DWORD Count, const D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil);
typedef HRESULT(__stdcall* D3D9_SetTransformT)(IDirect3DDevice9* pDevice, D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix);
typedef HRESULT(__stdcall* D3D9_GetTransformT)(IDirect3DDevice9* pDevice, D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix);
typedef HRESULT(__stdcall* D3D9_MultiplyTransformT)(IDirect3DDevice9* pDevice, D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix);
typedef HRESULT(__stdcall* D3D9_SetViewportT)(IDirect3DDevice9* pDevice, const D3DVIEWPORT9* pViewport);
typedef HRESULT(__stdcall* D3D9_GetViewportT)(IDirect3DDevice9* pDevice, D3DVIEWPORT9* pViewport);
typedef HRESULT(__stdcall* D3D9_SetMaterialT)(IDirect3DDevice9* pDevice, const D3DMATERIAL9* pMaterial);
typedef HRESULT(__stdcall* D3D9_GetMaterialT)(IDirect3DDevice9* pDevice, D3DMATERIAL9* pMaterial);
typedef HRESULT(__stdcall* D3D9_SetLightT)(IDirect3DDevice9* pDevice, DWORD Index, const D3DLIGHT9* pLight);
typedef HRESULT(__stdcall* D3D9_GetLightT)(IDirect3DDevice9* pDevice, DWORD Index, D3DLIGHT9* pLight);
typedef HRESULT(__stdcall* D3D9_LightEnableT)(IDirect3DDevice9* pDevice, DWORD Index, BOOL Enable);
typedef HRESULT(__stdcall* D3D9_GetLightEnableT)(IDirect3DDevice9* pDevice, DWORD Index, BOOL* pEnable);
typedef HRESULT(__stdcall* D3D9_SetClipPlaneT)(IDirect3DDevice9* pDevice, DWORD Index, const float* pPlane);
typedef HRESULT(__stdcall* D3D9_GetClipPlaneT)(IDirect3DDevice9* pDevice, DWORD Index, float* pPlane);
typedef HRESULT(__stdcall* D3D9_SetRenderStateT)(IDirect3DDevice9* pDevice, D3DRENDERSTATETYPE State, DWORD Value);
typedef HRESULT(__stdcall* D3D9_GetRenderStateT)(IDirect3DDevice9* pDevice, D3DRENDERSTATETYPE State, DWORD* pValue);
typedef HRESULT(__stdcall* D3D9_CreateStateBlockT)(IDirect3DDevice9* pDevice, D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB);
typedef HRESULT(__stdcall* D3D9_BeginStateBlockT)(IDirect3DDevice9* pDevice);
typedef HRESULT(__stdcall* D3D9_EndStateBlockT)(IDirect3DDevice9* pDevice, IDirect3DStateBlock9** ppSB);
typedef HRESULT(__stdcall* D3D9_SetClipStatusT)(IDirect3DDevice9* pDevice, const D3DCLIPSTATUS9* pClipStatus);
typedef HRESULT(__stdcall* D3D9_GetClipStatusT)(IDirect3DDevice9* pDevice, D3DCLIPSTATUS9* pClipStatus);
typedef HRESULT(__stdcall* D3D9_GetTextureT)(IDirect3DDevice9* pDevice, DWORD Stage, IDirect3DBaseTexture9** ppTexture);
typedef HRESULT(__stdcall* D3D9_SetTextureT)(IDirect3DDevice9* pDevice, DWORD Stage, IDirect3DBaseTexture9* pTexture);
typedef HRESULT(__stdcall* D3D9_GetTextureStageStateT)(IDirect3DDevice9* pDevice, DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue);
typedef HRESULT(__stdcall* D3D9_SetTextureStageStateT)(IDirect3DDevice9* pDevice, DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value);
typedef HRESULT(__stdcall* D3D9_GetSamplerStateT)(IDirect3DDevice9* pDevice, DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue);
typedef HRESULT(__stdcall* D3D9_SetSamplerStateT)(IDirect3DDevice9* pDevice, DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value);
typedef HRESULT(__stdcall* D3D9_ValidateDeviceT)(IDirect3DDevice9* pDevice, DWORD* pNumPasses);
typedef HRESULT(__stdcall* D3D9_SetPaletteEntriesT)(IDirect3DDevice9* pDevice, UINT PaletteNumber, const PALETTEENTRY* pEntries);
typedef HRESULT(__stdcall* D3D9_GetPaletteEntriesT)(IDirect3DDevice9* pDevice, UINT PaletteNumber, PALETTEENTRY* pEntries);
typedef HRESULT(__stdcall* D3D9_SetCurrentTexturePaletteT)(IDirect3DDevice9* pDevice, UINT PaletteNumber);
typedef HRESULT(__stdcall* D3D9_GetCurrentTexturePaletteT)(IDirect3DDevice9* pDevice, UINT* PaletteNumber);
typedef HRESULT(__stdcall* D3D9_SetScissorRectT)(IDirect3DDevice9* pDevice, const RECT* pRect);
typedef HRESULT(__stdcall* D3D9_GetScissorRectT)(IDirect3DDevice9* pDevice, RECT* pRect);
typedef HRESULT(__stdcall* D3D9_SetSoftwareVertexProcessingT)(IDirect3DDevice9* pDevice, BOOL bSoftware);
typedef HRESULT(__stdcall* D3D9_GetSoftwareVertexProcessingT)(IDirect3DDevice9* pDevice, BOOL* pSoftware);
typedef HRESULT(__stdcall* D3D9_SetNPatchModeT)(IDirect3DDevice9* pDevice, float nSegments);
typedef HRESULT(__stdcall* D3D9_GetNPatchModeT)(IDirect3DDevice9* pDevice, float* pSegments);
typedef HRESULT(__stdcall* D3D9_DrawPrimitiveT)(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
typedef HRESULT(__stdcall* D3D9_DrawIndexedPrimitiveT)(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
typedef HRESULT(__stdcall* D3D9_DrawPrimitiveUPT)(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride);
typedef HRESULT(__stdcall* D3D9_DrawIndexedPrimitiveUPT)(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void* pIndexData, D3DFORMAT IndexDataFormat, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride);
typedef HRESULT(__stdcall* D3D9_ProcessVerticesT)(IDirect3DDevice9* pDevice, UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags);
typedef HRESULT(__stdcall* D3D9_CreateVertexDeclarationT)(IDirect3DDevice9* pDevice, const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl);
typedef HRESULT(__stdcall* D3D9_SetVertexDeclarationT)(IDirect3DDevice9* pDevice, IDirect3DVertexDeclaration9* pDecl);
typedef HRESULT(__stdcall* D3D9_GetVertexDeclarationT)(IDirect3DDevice9* pDevice, IDirect3DVertexDeclaration9** ppDecl);
typedef HRESULT(__stdcall* D3D9_SetFVFT)(IDirect3DDevice9* pDevice, DWORD FVF);
typedef HRESULT(__stdcall* D3D9_GetFVFT)(IDirect3DDevice9* pDevice, DWORD* pFVF);
typedef HRESULT(__stdcall* D3D9_CreateVertexShaderT)(IDirect3DDevice9* pDevice, const DWORD* pFunction, IDirect3DVertexShader9** ppShader);
typedef HRESULT(__stdcall* D3D9_SetVertexShaderT)(IDirect3DDevice9* pDevice, IDirect3DVertexShader9* pShader);
typedef HRESULT(__stdcall* D3D9_GetVertexShaderT)(IDirect3DDevice9* pDevice, IDirect3DVertexShader9** ppShader);
typedef HRESULT(__stdcall* D3D9_SetVertexShaderConstantFT)(IDirect3DDevice9* pDevice, UINT StartRegister, const float* pConstantData, UINT Vector4fCount);
typedef HRESULT(__stdcall* D3D9_GetVertexShaderConstantFT)(IDirect3DDevice9* pDevice, UINT StartRegister, float* pConstantData, UINT Vector4fCount);
typedef HRESULT(__stdcall* D3D9_SetVertexShaderConstantIT)(IDirect3DDevice9* pDevice, UINT StartRegister, const int* pConstantData, UINT Vector4iCount);
typedef HRESULT(__stdcall* D3D9_GetVertexShaderConstantIT)(IDirect3DDevice9* pDevice, UINT StartRegister, int* pConstantData, UINT Vector4iCount);
typedef HRESULT(__stdcall* D3D9_SetVertexShaderConstantBT)(IDirect3DDevice9* pDevice, UINT StartRegister, const BOOL* pConstantData, UINT BoolCount);
typedef HRESULT(__stdcall* D3D9_GetVertexShaderConstantBT)(IDirect3DDevice9* pDevice, UINT StartRegister, BOOL* pConstantData, UINT BoolCount);
typedef HRESULT(__stdcall* D3D9_SetStreamSourceT)(IDirect3DDevice9* pDevice, UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride);
typedef HRESULT(__stdcall* D3D9_GetStreamSourceT)(IDirect3DDevice9* pDevice, UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride);
typedef HRESULT(__stdcall* D3D9_SetStreamSourceFreqT)(IDirect3DDevice9* pDevice, UINT StreamNumber, UINT Setting);
typedef HRESULT(__stdcall* D3D9_GetStreamSourceFreqT)(IDirect3DDevice9* pDevice, UINT StreamNumber, UINT* pSetting);
typedef HRESULT(__stdcall* D3D9_SetIndicesT)(IDirect3DDevice9* pDevice, IDirect3DIndexBuffer9* pIndexData);
typedef HRESULT(__stdcall* D3D9_GetIndicesT)(IDirect3DDevice9* pDevice, IDirect3DIndexBuffer9** ppIndexData);
typedef HRESULT(__stdcall* D3D9_CreatePixelShaderT)(IDirect3DDevice9* pDevice, const DWORD* pFunction, IDirect3DPixelShader9** ppShader);
typedef HRESULT(__stdcall* D3D9_SetPixelShaderT)(IDirect3DDevice9* pDevice, IDirect3DPixelShader9* pShader);
typedef HRESULT(__stdcall* D3D9_GetPixelShaderT)(IDirect3DDevice9* pDevice, IDirect3DPixelShader9** ppShader);
typedef HRESULT(__stdcall* D3D9_SetPixelShaderConstantFT)(IDirect3DDevice9* pDevice, UINT StartRegister, const float* pConstantData, UINT Vector4fCount);
typedef HRESULT(__stdcall* D3D9_GetPixelShaderConstantFT)(IDirect3DDevice9* pDevice, UINT StartRegister, float* pConstantData, UINT Vector4fCount);
typedef HRESULT(__stdcall* D3D9_SetPixelShaderConstantIT)(IDirect3DDevice9* pDevice, UINT StartRegister, const int* pConstantData, UINT Vector4iCount);
typedef HRESULT(__stdcall* D3D9_GetPixelShaderConstantIT)(IDirect3DDevice9* pDevice, UINT StartRegister, int* pConstantData, UINT Vector4iCount);
typedef HRESULT(__stdcall* D3D9_SetPixelShaderConstantBT)(IDirect3DDevice9* pDevice, UINT StartRegister, const BOOL* pConstantData, UINT BoolCount);
typedef HRESULT(__stdcall* D3D9_GetPixelShaderConstantBT)(IDirect3DDevice9* pDevice, UINT StartRegister, BOOL* pConstantData, UINT BoolCount);
typedef HRESULT(__stdcall* D3D9_DrawRectPatchT)(IDirect3DDevice9* pDevice, UINT Handle, const float* pNumSegs, const D3DRECTPATCH_INFO* pRectPatchInfo);
typedef HRESULT(__stdcall* D3D9_DrawTriPatchT)(IDirect3DDevice9* pDevice, UINT Handle, const float* pNumSegs, const D3DTRIPATCH_INFO* pTriPatchInfo);
typedef HRESULT(__stdcall* D3D9_DeletePatchT)(IDirect3DDevice9* pDevice, UINT Handle);
typedef HRESULT(__stdcall* D3D9_CreateQueryT)(IDirect3DDevice9* pDevice, D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery);



template <typename FuncT>
class D3D9_QueryInterface : public xNyuHook<D3D9_QueryInterfaceT> {
public:
    static D3D9_QueryInterface* instance;
    D3D9_QueryInterface(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_QueryInterfaceT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, REFIID riid, void** ppvObj)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, riid, ppvObj);
        HRESULT result = instance->pFunction(pDevice, riid, ppvObj);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, riid, ppvObj);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_QueryInterface<D3D9_QueryInterfaceT>* D3D9_QueryInterface<D3D9_QueryInterfaceT>::instance = nullptr;

template <typename FuncT>
class D3D9_AddRef : public xNyuHook<D3D9_AddRefT> {
public:
    static D3D9_AddRef* instance;
    D3D9_AddRef(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_AddRefT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static ULONG __stdcall CustomHook(IDirect3DDevice9* pDevice)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice);
        ULONG result = instance->pFunction(pDevice);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_AddRef<D3D9_AddRefT>* D3D9_AddRef<D3D9_AddRefT>::instance = nullptr;

template <typename FuncT>
class D3D9_Release : public xNyuHook<D3D9_ReleaseT> {
public:
    static D3D9_Release* instance;
    D3D9_Release(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_ReleaseT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static ULONG __stdcall CustomHook(IDirect3DDevice9* pDevice)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice);
        ULONG result = instance->pFunction(pDevice);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_Release<D3D9_ReleaseT>* D3D9_Release<D3D9_ReleaseT>::instance = nullptr;

template <typename FuncT>
class D3D9_TestCooperativeLevel : public xNyuHook<D3D9_TestCooperativeLevelT> {
public:
    static D3D9_TestCooperativeLevel* instance;
    D3D9_TestCooperativeLevel(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_TestCooperativeLevelT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice);
        HRESULT result = instance->pFunction(pDevice);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_TestCooperativeLevel<D3D9_TestCooperativeLevelT>* D3D9_TestCooperativeLevel<D3D9_TestCooperativeLevelT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetAvailableTextureMem : public xNyuHook<D3D9_GetAvailableTextureMemT> {
public:
    static D3D9_GetAvailableTextureMem* instance;
    D3D9_GetAvailableTextureMem(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetAvailableTextureMemT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static UINT __stdcall CustomHook(IDirect3DDevice9* pDevice)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice);
        UINT result = instance->pFunction(pDevice);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetAvailableTextureMem<D3D9_GetAvailableTextureMemT>* D3D9_GetAvailableTextureMem<D3D9_GetAvailableTextureMemT>::instance = nullptr;

template <typename FuncT>
class D3D9_EvictManagedResources : public xNyuHook<D3D9_EvictManagedResourcesT> {
public:
    static D3D9_EvictManagedResources* instance;
    D3D9_EvictManagedResources(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_EvictManagedResourcesT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice);
        HRESULT result = instance->pFunction(pDevice);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_EvictManagedResources<D3D9_EvictManagedResourcesT>* D3D9_EvictManagedResources<D3D9_EvictManagedResourcesT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetDirect3D : public xNyuHook<D3D9_GetDirect3DT> {
public:
    static D3D9_GetDirect3D* instance;
    D3D9_GetDirect3D(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetDirect3DT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3D9** ppD3D9)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, ppD3D9);
        HRESULT result = instance->pFunction(pDevice, ppD3D9);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, ppD3D9);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetDirect3D<D3D9_GetDirect3DT>* D3D9_GetDirect3D<D3D9_GetDirect3DT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetDeviceCaps : public xNyuHook<D3D9_GetDeviceCapsT> {
public:
    static D3D9_GetDeviceCaps* instance;
    D3D9_GetDeviceCaps(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetDeviceCapsT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DCAPS9* pCaps)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pCaps);
        HRESULT result = instance->pFunction(pDevice, pCaps);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pCaps);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetDeviceCaps<D3D9_GetDeviceCapsT>* D3D9_GetDeviceCaps<D3D9_GetDeviceCapsT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetDisplayMode : public xNyuHook<D3D9_GetDisplayModeT> {
public:
    static D3D9_GetDisplayMode* instance;
    D3D9_GetDisplayMode(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetDisplayModeT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT iSwapChain, D3DDISPLAYMODE* pMode)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, iSwapChain, pMode);
        HRESULT result = instance->pFunction(pDevice, iSwapChain, pMode);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, iSwapChain, pMode);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetDisplayMode<D3D9_GetDisplayModeT>* D3D9_GetDisplayMode<D3D9_GetDisplayModeT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetCreationParameters : public xNyuHook<D3D9_GetCreationParametersT> {
public:
    static D3D9_GetCreationParameters* instance;
    D3D9_GetCreationParameters(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetCreationParametersT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DDEVICE_CREATION_PARAMETERS* pParameters)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pParameters);
        HRESULT result = instance->pFunction(pDevice, pParameters);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pParameters);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetCreationParameters<D3D9_GetCreationParametersT>* D3D9_GetCreationParameters<D3D9_GetCreationParametersT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetCursorProperties : public xNyuHook<D3D9_SetCursorPropertiesT> {
public:
    static D3D9_SetCursorProperties* instance;
    D3D9_SetCursorProperties(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetCursorPropertiesT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, XHotSpot, YHotSpot, pCursorBitmap);
        HRESULT result = instance->pFunction(pDevice, XHotSpot, YHotSpot, pCursorBitmap);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, XHotSpot, YHotSpot, pCursorBitmap);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetCursorProperties<D3D9_SetCursorPropertiesT>* D3D9_SetCursorProperties<D3D9_SetCursorPropertiesT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetCursorPosition : public xNyuHook<D3D9_SetCursorPositionT> {
public:
    static D3D9_SetCursorPosition* instance;
    D3D9_SetCursorPosition(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetCursorPositionT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static void __stdcall CustomHook(IDirect3DDevice9* pDevice, int X, int Y, DWORD Flags)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, X, Y, Flags);
        instance->pFunction(pDevice, X, Y, Flags);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, X, Y, Flags);
        instance->install();

    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetCursorPosition<D3D9_SetCursorPositionT>* D3D9_SetCursorPosition<D3D9_SetCursorPositionT>::instance = nullptr;

template <typename FuncT>
class D3D9_ShowCursor : public xNyuHook<D3D9_ShowCursorT> {
public:
    static D3D9_ShowCursor* instance;
    D3D9_ShowCursor(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_ShowCursorT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static BOOL __stdcall CustomHook(IDirect3DDevice9* pDevice, BOOL bShow)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, bShow);
        BOOL result = instance->pFunction(pDevice, bShow);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, bShow);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_ShowCursor<D3D9_ShowCursorT>* D3D9_ShowCursor<D3D9_ShowCursorT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateAdditionalSwapChain : public xNyuHook<D3D9_CreateAdditionalSwapChainT> {
public:
    static D3D9_CreateAdditionalSwapChain* instance;
    D3D9_CreateAdditionalSwapChain(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateAdditionalSwapChainT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pPresentationParameters, pSwapChain);
        HRESULT result = instance->pFunction(pDevice, pPresentationParameters, pSwapChain);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pPresentationParameters, pSwapChain);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateAdditionalSwapChain<D3D9_CreateAdditionalSwapChainT>* D3D9_CreateAdditionalSwapChain<D3D9_CreateAdditionalSwapChainT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetSwapChain : public xNyuHook<D3D9_GetSwapChainT> {
public:
    static D3D9_GetSwapChain* instance;
    D3D9_GetSwapChain(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetSwapChainT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, iSwapChain, pSwapChain);
        HRESULT result = instance->pFunction(pDevice, iSwapChain, pSwapChain);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, iSwapChain, pSwapChain);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetSwapChain<D3D9_GetSwapChainT>* D3D9_GetSwapChain<D3D9_GetSwapChainT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetNumberOfSwapChains : public xNyuHook<D3D9_GetNumberOfSwapChainsT> {
public:
    static D3D9_GetNumberOfSwapChains* instance;
    D3D9_GetNumberOfSwapChains(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetNumberOfSwapChainsT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static UINT __stdcall CustomHook(IDirect3DDevice9* pDevice)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice);
        UINT result = instance->pFunction(pDevice);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetNumberOfSwapChains<D3D9_GetNumberOfSwapChainsT>* D3D9_GetNumberOfSwapChains<D3D9_GetNumberOfSwapChainsT>::instance = nullptr;

template <typename FuncT>
class D3D9_Reset : public xNyuHook<D3D9_ResetT> {
public:
    static D3D9_Reset* instance;
    D3D9_Reset(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_ResetT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pPresentationParameters);
        HRESULT result = instance->pFunction(pDevice, pPresentationParameters);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pPresentationParameters);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_Reset<D3D9_ResetT>* D3D9_Reset<D3D9_ResetT>::instance = nullptr;

template <typename FuncT>
class D3D9_Present : public xNyuHook<D3D9_PresentT> {
public:
    static D3D9_Present* instance;
    D3D9_Present(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_PresentT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
        HRESULT result = instance->pFunction(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_Present<D3D9_PresentT>* D3D9_Present<D3D9_PresentT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetBackBuffer : public xNyuHook<D3D9_GetBackBufferT> {
public:
    static D3D9_GetBackBuffer* instance;
    D3D9_GetBackBuffer(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetBackBufferT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, iSwapChain, iBackBuffer, Type, ppBackBuffer);
        HRESULT result = instance->pFunction(pDevice, iSwapChain, iBackBuffer, Type, ppBackBuffer);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, iSwapChain, iBackBuffer, Type, ppBackBuffer);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetBackBuffer<D3D9_GetBackBufferT>* D3D9_GetBackBuffer<D3D9_GetBackBufferT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetRasterStatus : public xNyuHook<D3D9_GetRasterStatusT> {
public:
    static D3D9_GetRasterStatus* instance;
    D3D9_GetRasterStatus(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetRasterStatusT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, iSwapChain, pRasterStatus);
        HRESULT result = instance->pFunction(pDevice, iSwapChain, pRasterStatus);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, iSwapChain, pRasterStatus);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetRasterStatus<D3D9_GetRasterStatusT>* D3D9_GetRasterStatus<D3D9_GetRasterStatusT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetDialogBoxMode : public xNyuHook<D3D9_SetDialogBoxModeT> {
public:
    static D3D9_SetDialogBoxMode* instance;
    D3D9_SetDialogBoxMode(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetDialogBoxModeT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, BOOL bEnableDialogs)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, bEnableDialogs);
        HRESULT result = instance->pFunction(pDevice, bEnableDialogs);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, bEnableDialogs);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetDialogBoxMode<D3D9_SetDialogBoxModeT>* D3D9_SetDialogBoxMode<D3D9_SetDialogBoxModeT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetGammaRamp : public xNyuHook<D3D9_SetGammaRampT> {
public:
    static D3D9_SetGammaRamp* instance;
    D3D9_SetGammaRamp(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetGammaRampT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static void __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP* pRamp)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, iSwapChain, Flags, pRamp);
        instance->pFunction(pDevice, iSwapChain, Flags, pRamp);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, iSwapChain, Flags, pRamp);
        instance->install();

    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetGammaRamp<D3D9_SetGammaRampT>* D3D9_SetGammaRamp<D3D9_SetGammaRampT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetGammaRamp : public xNyuHook<D3D9_GetGammaRampT> {
public:
    static D3D9_GetGammaRamp* instance;
    D3D9_GetGammaRamp(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetGammaRampT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static void __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT iSwapChain, D3DGAMMARAMP* pRamp)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, iSwapChain, pRamp);
        instance->pFunction(pDevice, iSwapChain, pRamp);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, iSwapChain, pRamp);
        instance->install();

    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetGammaRamp<D3D9_GetGammaRampT>* D3D9_GetGammaRamp<D3D9_GetGammaRampT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateTexture : public xNyuHook<D3D9_CreateTextureT> {
public:
    static D3D9_CreateTexture* instance;
    D3D9_CreateTexture(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateTextureT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
        HRESULT result = instance->pFunction(pDevice, Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateTexture<D3D9_CreateTextureT>* D3D9_CreateTexture<D3D9_CreateTextureT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateVolumeTexture : public xNyuHook<D3D9_CreateVolumeTextureT> {
public:
    static D3D9_CreateVolumeTexture* instance;
    D3D9_CreateVolumeTexture(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateVolumeTextureT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
        HRESULT result = instance->pFunction(pDevice, Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateVolumeTexture<D3D9_CreateVolumeTextureT>* D3D9_CreateVolumeTexture<D3D9_CreateVolumeTextureT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateCubeTexture : public xNyuHook<D3D9_CreateCubeTextureT> {
public:
    static D3D9_CreateCubeTexture* instance;
    D3D9_CreateCubeTexture(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateCubeTextureT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
        HRESULT result = instance->pFunction(pDevice, EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateCubeTexture<D3D9_CreateCubeTextureT>* D3D9_CreateCubeTexture<D3D9_CreateCubeTextureT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateVertexBuffer : public xNyuHook<D3D9_CreateVertexBufferT> {
public:
    static D3D9_CreateVertexBuffer* instance;
    D3D9_CreateVertexBuffer(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateVertexBufferT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
        HRESULT result = instance->pFunction(pDevice, Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateVertexBuffer<D3D9_CreateVertexBufferT>* D3D9_CreateVertexBuffer<D3D9_CreateVertexBufferT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateIndexBuffer : public xNyuHook<D3D9_CreateIndexBufferT> {
public:
    static D3D9_CreateIndexBuffer* instance;
    D3D9_CreateIndexBuffer(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateIndexBufferT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
        HRESULT result = instance->pFunction(pDevice, Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateIndexBuffer<D3D9_CreateIndexBufferT>* D3D9_CreateIndexBuffer<D3D9_CreateIndexBufferT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateRenderTarget : public xNyuHook<D3D9_CreateRenderTargetT> {
public:
    static D3D9_CreateRenderTarget* instance;
    D3D9_CreateRenderTarget(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateRenderTargetT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
        HRESULT result = instance->pFunction(pDevice, Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateRenderTarget<D3D9_CreateRenderTargetT>* D3D9_CreateRenderTarget<D3D9_CreateRenderTargetT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateDepthStencilSurface : public xNyuHook<D3D9_CreateDepthStencilSurfaceT> {
public:
    static D3D9_CreateDepthStencilSurface* instance;
    D3D9_CreateDepthStencilSurface(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateDepthStencilSurfaceT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
        HRESULT result = instance->pFunction(pDevice, Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateDepthStencilSurface<D3D9_CreateDepthStencilSurfaceT>* D3D9_CreateDepthStencilSurface<D3D9_CreateDepthStencilSurfaceT>::instance = nullptr;

template <typename FuncT>
class D3D9_UpdateSurface : public xNyuHook<D3D9_UpdateSurfaceT> {
public:
    static D3D9_UpdateSurface* instance;
    D3D9_UpdateSurface(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_UpdateSurfaceT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, POINT* pDestPoint)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
        HRESULT result = instance->pFunction(pDevice, pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_UpdateSurface<D3D9_UpdateSurfaceT>* D3D9_UpdateSurface<D3D9_UpdateSurfaceT>::instance = nullptr;

template <typename FuncT>
class D3D9_UpdateTexture : public xNyuHook<D3D9_UpdateTextureT> {
public:
    static D3D9_UpdateTexture* instance;
    D3D9_UpdateTexture(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_UpdateTextureT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pSourceTexture, pDestinationTexture);
        HRESULT result = instance->pFunction(pDevice, pSourceTexture, pDestinationTexture);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pSourceTexture, pDestinationTexture);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_UpdateTexture<D3D9_UpdateTextureT>* D3D9_UpdateTexture<D3D9_UpdateTextureT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetRenderTargetData : public xNyuHook<D3D9_GetRenderTargetDataT> {
public:
    static D3D9_GetRenderTargetData* instance;
    D3D9_GetRenderTargetData(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetRenderTargetDataT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pRenderTarget, pDestSurface);
        HRESULT result = instance->pFunction(pDevice, pRenderTarget, pDestSurface);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pRenderTarget, pDestSurface);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetRenderTargetData<D3D9_GetRenderTargetDataT>* D3D9_GetRenderTargetData<D3D9_GetRenderTargetDataT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetFrontBufferData : public xNyuHook<D3D9_GetFrontBufferDataT> {
public:
    static D3D9_GetFrontBufferData* instance;
    D3D9_GetFrontBufferData(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetFrontBufferDataT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT iSwapChain, IDirect3DSurface9* pDestSurface)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, iSwapChain, pDestSurface);
        HRESULT result = instance->pFunction(pDevice, iSwapChain, pDestSurface);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, iSwapChain, pDestSurface);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetFrontBufferData<D3D9_GetFrontBufferDataT>* D3D9_GetFrontBufferData<D3D9_GetFrontBufferDataT>::instance = nullptr;

template <typename FuncT>
class D3D9_StretchRect : public xNyuHook<D3D9_StretchRectT> {
public:
    static D3D9_StretchRect* instance;
    D3D9_StretchRect(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_StretchRectT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
        HRESULT result = instance->pFunction(pDevice, pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_StretchRect<D3D9_StretchRectT>* D3D9_StretchRect<D3D9_StretchRectT>::instance = nullptr;

template <typename FuncT>
class D3D9_ColorFill : public xNyuHook<D3D9_ColorFillT> {
public:
    static D3D9_ColorFill* instance;
    D3D9_ColorFill(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_ColorFillT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DSurface9* pSurface, const RECT* pRect, D3DCOLOR color)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pSurface, pRect, color);
        HRESULT result = instance->pFunction(pDevice, pSurface, pRect, color);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pSurface, pRect, color);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_ColorFill<D3D9_ColorFillT>* D3D9_ColorFill<D3D9_ColorFillT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateOffscreenPlainSurface : public xNyuHook<D3D9_CreateOffscreenPlainSurfaceT> {
public:
    static D3D9_CreateOffscreenPlainSurface* instance;
    D3D9_CreateOffscreenPlainSurface(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateOffscreenPlainSurfaceT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Width, Height, Format, Pool, ppSurface, pSharedHandle);
        HRESULT result = instance->pFunction(pDevice, Width, Height, Format, Pool, ppSurface, pSharedHandle);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Width, Height, Format, Pool, ppSurface, pSharedHandle);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateOffscreenPlainSurface<D3D9_CreateOffscreenPlainSurfaceT>* D3D9_CreateOffscreenPlainSurface<D3D9_CreateOffscreenPlainSurfaceT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetRenderTarget : public xNyuHook<D3D9_SetRenderTargetT> {
public:
    static D3D9_SetRenderTarget* instance;
    D3D9_SetRenderTarget(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetRenderTargetT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, RenderTargetIndex, pRenderTarget);
        HRESULT result = instance->pFunction(pDevice, RenderTargetIndex, pRenderTarget);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, RenderTargetIndex, pRenderTarget);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetRenderTarget<D3D9_SetRenderTargetT>* D3D9_SetRenderTarget<D3D9_SetRenderTargetT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetRenderTarget : public xNyuHook<D3D9_GetRenderTargetT> {
public:
    static D3D9_GetRenderTarget* instance;
    D3D9_GetRenderTarget(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetRenderTargetT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, RenderTargetIndex, ppRenderTarget);
        HRESULT result = instance->pFunction(pDevice, RenderTargetIndex, ppRenderTarget);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, RenderTargetIndex, ppRenderTarget);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetRenderTarget<D3D9_GetRenderTargetT>* D3D9_GetRenderTarget<D3D9_GetRenderTargetT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetDepthStencilSurface : public xNyuHook<D3D9_SetDepthStencilSurfaceT> {
public:
    static D3D9_SetDepthStencilSurface* instance;
    D3D9_SetDepthStencilSurface(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetDepthStencilSurfaceT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DSurface9* pNewZStencil)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pNewZStencil);
        HRESULT result = instance->pFunction(pDevice, pNewZStencil);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pNewZStencil);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetDepthStencilSurface<D3D9_SetDepthStencilSurfaceT>* D3D9_SetDepthStencilSurface<D3D9_SetDepthStencilSurfaceT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetDepthStencilSurface : public xNyuHook<D3D9_GetDepthStencilSurfaceT> {
public:
    static D3D9_GetDepthStencilSurface* instance;
    D3D9_GetDepthStencilSurface(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetDepthStencilSurfaceT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DSurface9** ppZStencilSurface)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, ppZStencilSurface);
        HRESULT result = instance->pFunction(pDevice, ppZStencilSurface);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, ppZStencilSurface);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetDepthStencilSurface<D3D9_GetDepthStencilSurfaceT>* D3D9_GetDepthStencilSurface<D3D9_GetDepthStencilSurfaceT>::instance = nullptr;

template <typename FuncT>
class D3D9_BeginScene : public xNyuHook<D3D9_BeginSceneT> {
public:
    static D3D9_BeginScene* instance;
    D3D9_BeginScene(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_BeginSceneT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice);
        HRESULT result = instance->pFunction(pDevice);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_BeginScene<D3D9_BeginSceneT>* D3D9_BeginScene<D3D9_BeginSceneT>::instance = nullptr;

template <typename FuncT>
class D3D9_EndScene : public xNyuHook<D3D9_EndSceneT> {
public:
    static D3D9_EndScene* instance;
    D3D9_EndScene(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_EndSceneT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice);
        HRESULT result = instance->pFunction(pDevice);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_EndScene<D3D9_EndSceneT>* D3D9_EndScene<D3D9_EndSceneT>::instance = nullptr;

template <typename FuncT>
class D3D9_Clear : public xNyuHook<D3D9_ClearT> {
public:
    static D3D9_Clear* instance;
    D3D9_Clear(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_ClearT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Count, const D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Count, pRects, Flags, Color, Z, Stencil);
        HRESULT result = instance->pFunction(pDevice, Count, pRects, Flags, Color, Z, Stencil);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Count, pRects, Flags, Color, Z, Stencil);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_Clear<D3D9_ClearT>* D3D9_Clear<D3D9_ClearT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetTransform : public xNyuHook<D3D9_SetTransformT> {
public:
    static D3D9_SetTransform* instance;
    D3D9_SetTransform(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetTransformT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, State, pMatrix);
        HRESULT result = instance->pFunction(pDevice, State, pMatrix);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, State, pMatrix);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetTransform<D3D9_SetTransformT>* D3D9_SetTransform<D3D9_SetTransformT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetTransform : public xNyuHook<D3D9_GetTransformT> {
public:
    static D3D9_GetTransform* instance;
    D3D9_GetTransform(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetTransformT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, State, pMatrix);
        HRESULT result = instance->pFunction(pDevice, State, pMatrix);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, State, pMatrix);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetTransform<D3D9_GetTransformT>* D3D9_GetTransform<D3D9_GetTransformT>::instance = nullptr;

template <typename FuncT>
class D3D9_MultiplyTransform : public xNyuHook<D3D9_MultiplyTransformT> {
public:
    static D3D9_MultiplyTransform* instance;
    D3D9_MultiplyTransform(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_MultiplyTransformT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, State, pMatrix);
        HRESULT result = instance->pFunction(pDevice, State, pMatrix);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, State, pMatrix);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_MultiplyTransform<D3D9_MultiplyTransformT>* D3D9_MultiplyTransform<D3D9_MultiplyTransformT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetViewport : public xNyuHook<D3D9_SetViewportT> {
public:
    static D3D9_SetViewport* instance;
    D3D9_SetViewport(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetViewportT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, const D3DVIEWPORT9* pViewport)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pViewport);
        HRESULT result = instance->pFunction(pDevice, pViewport);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pViewport);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetViewport<D3D9_SetViewportT>* D3D9_SetViewport<D3D9_SetViewportT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetViewport : public xNyuHook<D3D9_GetViewportT> {
public:
    static D3D9_GetViewport* instance;
    D3D9_GetViewport(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetViewportT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DVIEWPORT9* pViewport)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pViewport);
        HRESULT result = instance->pFunction(pDevice, pViewport);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pViewport);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetViewport<D3D9_GetViewportT>* D3D9_GetViewport<D3D9_GetViewportT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetMaterial : public xNyuHook<D3D9_SetMaterialT> {
public:
    static D3D9_SetMaterial* instance;
    D3D9_SetMaterial(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetMaterialT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, const D3DMATERIAL9* pMaterial)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pMaterial);
        HRESULT result = instance->pFunction(pDevice, pMaterial);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pMaterial);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetMaterial<D3D9_SetMaterialT>* D3D9_SetMaterial<D3D9_SetMaterialT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetMaterial : public xNyuHook<D3D9_GetMaterialT> {
public:
    static D3D9_GetMaterial* instance;
    D3D9_GetMaterial(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetMaterialT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DMATERIAL9* pMaterial)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pMaterial);
        HRESULT result = instance->pFunction(pDevice, pMaterial);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pMaterial);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetMaterial<D3D9_GetMaterialT>* D3D9_GetMaterial<D3D9_GetMaterialT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetLight : public xNyuHook<D3D9_SetLightT> {
public:
    static D3D9_SetLight* instance;
    D3D9_SetLight(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetLightT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Index, const D3DLIGHT9* pLight)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Index, pLight);
        HRESULT result = instance->pFunction(pDevice, Index, pLight);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Index, pLight);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetLight<D3D9_SetLightT>* D3D9_SetLight<D3D9_SetLightT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetLight : public xNyuHook<D3D9_GetLightT> {
public:
    static D3D9_GetLight* instance;
    D3D9_GetLight(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetLightT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Index, D3DLIGHT9* pLight)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Index, pLight);
        HRESULT result = instance->pFunction(pDevice, Index, pLight);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Index, pLight);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetLight<D3D9_GetLightT>* D3D9_GetLight<D3D9_GetLightT>::instance = nullptr;

template <typename FuncT>
class D3D9_LightEnable : public xNyuHook<D3D9_LightEnableT> {
public:
    static D3D9_LightEnable* instance;
    D3D9_LightEnable(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_LightEnableT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Index, BOOL Enable)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Index, Enable);
        HRESULT result = instance->pFunction(pDevice, Index, Enable);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Index, Enable);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_LightEnable<D3D9_LightEnableT>* D3D9_LightEnable<D3D9_LightEnableT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetLightEnable : public xNyuHook<D3D9_GetLightEnableT> {
public:
    static D3D9_GetLightEnable* instance;
    D3D9_GetLightEnable(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetLightEnableT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Index, BOOL* pEnable)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Index, pEnable);
        HRESULT result = instance->pFunction(pDevice, Index, pEnable);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Index, pEnable);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetLightEnable<D3D9_GetLightEnableT>* D3D9_GetLightEnable<D3D9_GetLightEnableT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetClipPlane : public xNyuHook<D3D9_SetClipPlaneT> {
public:
    static D3D9_SetClipPlane* instance;
    D3D9_SetClipPlane(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetClipPlaneT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Index, const float* pPlane)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Index, pPlane);
        HRESULT result = instance->pFunction(pDevice, Index, pPlane);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Index, pPlane);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetClipPlane<D3D9_SetClipPlaneT>* D3D9_SetClipPlane<D3D9_SetClipPlaneT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetClipPlane : public xNyuHook<D3D9_GetClipPlaneT> {
public:
    static D3D9_GetClipPlane* instance;
    D3D9_GetClipPlane(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetClipPlaneT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Index, float* pPlane)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Index, pPlane);
        HRESULT result = instance->pFunction(pDevice, Index, pPlane);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Index, pPlane);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetClipPlane<D3D9_GetClipPlaneT>* D3D9_GetClipPlane<D3D9_GetClipPlaneT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetRenderState : public xNyuHook<D3D9_SetRenderStateT> {
public:
    static D3D9_SetRenderState* instance;
    D3D9_SetRenderState(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetRenderStateT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DRENDERSTATETYPE State, DWORD Value)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, State, Value);
        HRESULT result = instance->pFunction(pDevice, State, Value);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, State, Value);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetRenderState<D3D9_SetRenderStateT>* D3D9_SetRenderState<D3D9_SetRenderStateT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetRenderState : public xNyuHook<D3D9_GetRenderStateT> {
public:
    static D3D9_GetRenderState* instance;
    D3D9_GetRenderState(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetRenderStateT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DRENDERSTATETYPE State, DWORD* pValue)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, State, pValue);
        HRESULT result = instance->pFunction(pDevice, State, pValue);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, State, pValue);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetRenderState<D3D9_GetRenderStateT>* D3D9_GetRenderState<D3D9_GetRenderStateT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateStateBlock : public xNyuHook<D3D9_CreateStateBlockT> {
public:
    static D3D9_CreateStateBlock* instance;
    D3D9_CreateStateBlock(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateStateBlockT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Type, ppSB);
        HRESULT result = instance->pFunction(pDevice, Type, ppSB);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Type, ppSB);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateStateBlock<D3D9_CreateStateBlockT>* D3D9_CreateStateBlock<D3D9_CreateStateBlockT>::instance = nullptr;

template <typename FuncT>
class D3D9_BeginStateBlock : public xNyuHook<D3D9_BeginStateBlockT> {
public:
    static D3D9_BeginStateBlock* instance;
    D3D9_BeginStateBlock(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_BeginStateBlockT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice);
        HRESULT result = instance->pFunction(pDevice);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_BeginStateBlock<D3D9_BeginStateBlockT>* D3D9_BeginStateBlock<D3D9_BeginStateBlockT>::instance = nullptr;

template <typename FuncT>
class D3D9_EndStateBlock : public xNyuHook<D3D9_EndStateBlockT> {
public:
    static D3D9_EndStateBlock* instance;
    D3D9_EndStateBlock(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_EndStateBlockT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DStateBlock9** ppSB)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, ppSB);
        HRESULT result = instance->pFunction(pDevice, ppSB);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, ppSB);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_EndStateBlock<D3D9_EndStateBlockT>* D3D9_EndStateBlock<D3D9_EndStateBlockT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetClipStatus : public xNyuHook<D3D9_SetClipStatusT> {
public:
    static D3D9_SetClipStatus* instance;
    D3D9_SetClipStatus(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetClipStatusT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, const D3DCLIPSTATUS9* pClipStatus)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pClipStatus);
        HRESULT result = instance->pFunction(pDevice, pClipStatus);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pClipStatus);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetClipStatus<D3D9_SetClipStatusT>* D3D9_SetClipStatus<D3D9_SetClipStatusT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetClipStatus : public xNyuHook<D3D9_GetClipStatusT> {
public:
    static D3D9_GetClipStatus* instance;
    D3D9_GetClipStatus(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetClipStatusT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DCLIPSTATUS9* pClipStatus)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pClipStatus);
        HRESULT result = instance->pFunction(pDevice, pClipStatus);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pClipStatus);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetClipStatus<D3D9_GetClipStatusT>* D3D9_GetClipStatus<D3D9_GetClipStatusT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetTexture : public xNyuHook<D3D9_GetTextureT> {
public:
    static D3D9_GetTexture* instance;
    D3D9_GetTexture(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetTextureT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Stage, IDirect3DBaseTexture9** ppTexture)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Stage, ppTexture);
        HRESULT result = instance->pFunction(pDevice, Stage, ppTexture);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Stage, ppTexture);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetTexture<D3D9_GetTextureT>* D3D9_GetTexture<D3D9_GetTextureT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetTexture : public xNyuHook<D3D9_SetTextureT> {
public:
    static D3D9_SetTexture* instance;
    D3D9_SetTexture(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetTextureT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Stage, IDirect3DBaseTexture9* pTexture)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Stage, pTexture);
        HRESULT result = instance->pFunction(pDevice, Stage, pTexture);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Stage, pTexture);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetTexture<D3D9_SetTextureT>* D3D9_SetTexture<D3D9_SetTextureT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetTextureStageState : public xNyuHook<D3D9_GetTextureStageStateT> {
public:
    static D3D9_GetTextureStageState* instance;
    D3D9_GetTextureStageState(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetTextureStageStateT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Stage, Type, pValue);
        HRESULT result = instance->pFunction(pDevice, Stage, Type, pValue);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Stage, Type, pValue);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetTextureStageState<D3D9_GetTextureStageStateT>* D3D9_GetTextureStageState<D3D9_GetTextureStageStateT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetTextureStageState : public xNyuHook<D3D9_SetTextureStageStateT> {
public:
    static D3D9_SetTextureStageState* instance;
    D3D9_SetTextureStageState(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetTextureStageStateT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Stage, Type, Value);
        HRESULT result = instance->pFunction(pDevice, Stage, Type, Value);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Stage, Type, Value);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetTextureStageState<D3D9_SetTextureStageStateT>* D3D9_SetTextureStageState<D3D9_SetTextureStageStateT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetSamplerState : public xNyuHook<D3D9_GetSamplerStateT> {
public:
    static D3D9_GetSamplerState* instance;
    D3D9_GetSamplerState(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetSamplerStateT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Sampler, Type, pValue);
        HRESULT result = instance->pFunction(pDevice, Sampler, Type, pValue);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Sampler, Type, pValue);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetSamplerState<D3D9_GetSamplerStateT>* D3D9_GetSamplerState<D3D9_GetSamplerStateT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetSamplerState : public xNyuHook<D3D9_SetSamplerStateT> {
public:
    static D3D9_SetSamplerState* instance;
    D3D9_SetSamplerState(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetSamplerStateT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Sampler, Type, Value);
        HRESULT result = instance->pFunction(pDevice, Sampler, Type, Value);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Sampler, Type, Value);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetSamplerState<D3D9_SetSamplerStateT>* D3D9_SetSamplerState<D3D9_SetSamplerStateT>::instance = nullptr;

template <typename FuncT>
class D3D9_ValidateDevice : public xNyuHook<D3D9_ValidateDeviceT> {
public:
    static D3D9_ValidateDevice* instance;
    D3D9_ValidateDevice(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_ValidateDeviceT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD* pNumPasses)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pNumPasses);
        HRESULT result = instance->pFunction(pDevice, pNumPasses);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pNumPasses);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_ValidateDevice<D3D9_ValidateDeviceT>* D3D9_ValidateDevice<D3D9_ValidateDeviceT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetPaletteEntries : public xNyuHook<D3D9_SetPaletteEntriesT> {
public:
    static D3D9_SetPaletteEntries* instance;
    D3D9_SetPaletteEntries(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetPaletteEntriesT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT PaletteNumber, const PALETTEENTRY* pEntries)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, PaletteNumber, pEntries);
        HRESULT result = instance->pFunction(pDevice, PaletteNumber, pEntries);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, PaletteNumber, pEntries);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetPaletteEntries<D3D9_SetPaletteEntriesT>* D3D9_SetPaletteEntries<D3D9_SetPaletteEntriesT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetPaletteEntries : public xNyuHook<D3D9_GetPaletteEntriesT> {
public:
    static D3D9_GetPaletteEntries* instance;
    D3D9_GetPaletteEntries(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetPaletteEntriesT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT PaletteNumber, PALETTEENTRY* pEntries)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, PaletteNumber, pEntries);
        HRESULT result = instance->pFunction(pDevice, PaletteNumber, pEntries);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, PaletteNumber, pEntries);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetPaletteEntries<D3D9_GetPaletteEntriesT>* D3D9_GetPaletteEntries<D3D9_GetPaletteEntriesT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetCurrentTexturePalette : public xNyuHook<D3D9_SetCurrentTexturePaletteT> {
public:
    static D3D9_SetCurrentTexturePalette* instance;
    D3D9_SetCurrentTexturePalette(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetCurrentTexturePaletteT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT PaletteNumber)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, PaletteNumber);
        HRESULT result = instance->pFunction(pDevice, PaletteNumber);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, PaletteNumber);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetCurrentTexturePalette<D3D9_SetCurrentTexturePaletteT>* D3D9_SetCurrentTexturePalette<D3D9_SetCurrentTexturePaletteT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetCurrentTexturePalette : public xNyuHook<D3D9_GetCurrentTexturePaletteT> {
public:
    static D3D9_GetCurrentTexturePalette* instance;
    D3D9_GetCurrentTexturePalette(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetCurrentTexturePaletteT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT* PaletteNumber)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, PaletteNumber);
        HRESULT result = instance->pFunction(pDevice, PaletteNumber);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, PaletteNumber);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetCurrentTexturePalette<D3D9_GetCurrentTexturePaletteT>* D3D9_GetCurrentTexturePalette<D3D9_GetCurrentTexturePaletteT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetScissorRect : public xNyuHook<D3D9_SetScissorRectT> {
public:
    static D3D9_SetScissorRect* instance;
    D3D9_SetScissorRect(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetScissorRectT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, const RECT* pRect)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pRect);
        HRESULT result = instance->pFunction(pDevice, pRect);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pRect);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetScissorRect<D3D9_SetScissorRectT>* D3D9_SetScissorRect<D3D9_SetScissorRectT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetScissorRect : public xNyuHook<D3D9_GetScissorRectT> {
public:
    static D3D9_GetScissorRect* instance;
    D3D9_GetScissorRect(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetScissorRectT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, RECT* pRect)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pRect);
        HRESULT result = instance->pFunction(pDevice, pRect);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pRect);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetScissorRect<D3D9_GetScissorRectT>* D3D9_GetScissorRect<D3D9_GetScissorRectT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetSoftwareVertexProcessing : public xNyuHook<D3D9_SetSoftwareVertexProcessingT> {
public:
    static D3D9_SetSoftwareVertexProcessing* instance;
    D3D9_SetSoftwareVertexProcessing(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetSoftwareVertexProcessingT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, BOOL bSoftware)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, bSoftware);
        HRESULT result = instance->pFunction(pDevice, bSoftware);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, bSoftware);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetSoftwareVertexProcessing<D3D9_SetSoftwareVertexProcessingT>* D3D9_SetSoftwareVertexProcessing<D3D9_SetSoftwareVertexProcessingT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetSoftwareVertexProcessing : public xNyuHook<D3D9_GetSoftwareVertexProcessingT> {
public:
    static D3D9_GetSoftwareVertexProcessing* instance;
    D3D9_GetSoftwareVertexProcessing(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetSoftwareVertexProcessingT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, BOOL* pSoftware)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pSoftware);
        HRESULT result = instance->pFunction(pDevice, pSoftware);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pSoftware);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetSoftwareVertexProcessing<D3D9_GetSoftwareVertexProcessingT>* D3D9_GetSoftwareVertexProcessing<D3D9_GetSoftwareVertexProcessingT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetNPatchMode : public xNyuHook<D3D9_SetNPatchModeT> {
public:
    static D3D9_SetNPatchMode* instance;
    D3D9_SetNPatchMode(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetNPatchModeT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, float nSegments)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, nSegments);
        HRESULT result = instance->pFunction(pDevice, nSegments);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, nSegments);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetNPatchMode<D3D9_SetNPatchModeT>* D3D9_SetNPatchMode<D3D9_SetNPatchModeT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetNPatchMode : public xNyuHook<D3D9_GetNPatchModeT> {
public:
    static D3D9_GetNPatchMode* instance;
    D3D9_GetNPatchMode(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetNPatchModeT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, float* pSegments)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pSegments);
        HRESULT result = instance->pFunction(pDevice, pSegments);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pSegments);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetNPatchMode<D3D9_GetNPatchModeT>* D3D9_GetNPatchMode<D3D9_GetNPatchModeT>::instance = nullptr;

template <typename FuncT>
class D3D9_DrawPrimitive : public xNyuHook<D3D9_DrawPrimitiveT> {
public:
    static D3D9_DrawPrimitive* instance;
    D3D9_DrawPrimitive(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_DrawPrimitiveT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, PrimitiveType, StartVertex, PrimitiveCount);
        HRESULT result = instance->pFunction(pDevice, PrimitiveType, StartVertex, PrimitiveCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, PrimitiveType, StartVertex, PrimitiveCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_DrawPrimitive<D3D9_DrawPrimitiveT>* D3D9_DrawPrimitive<D3D9_DrawPrimitiveT>::instance = nullptr;

template <typename FuncT>
class D3D9_DrawIndexedPrimitive : public xNyuHook<D3D9_DrawIndexedPrimitiveT> {
public:
    static D3D9_DrawIndexedPrimitive* instance;
    D3D9_DrawIndexedPrimitive(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_DrawIndexedPrimitiveT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
        HRESULT result = instance->pFunction(pDevice, PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_DrawIndexedPrimitive<D3D9_DrawIndexedPrimitiveT>* D3D9_DrawIndexedPrimitive<D3D9_DrawIndexedPrimitiveT>::instance = nullptr;

template <typename FuncT>
class D3D9_DrawPrimitiveUP : public xNyuHook<D3D9_DrawPrimitiveUPT> {
public:
    static D3D9_DrawPrimitiveUP* instance;
    D3D9_DrawPrimitiveUP(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_DrawPrimitiveUPT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
        HRESULT result = instance->pFunction(pDevice, PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_DrawPrimitiveUP<D3D9_DrawPrimitiveUPT>* D3D9_DrawPrimitiveUP<D3D9_DrawPrimitiveUPT>::instance = nullptr;

template <typename FuncT>
class D3D9_DrawIndexedPrimitiveUP : public xNyuHook<D3D9_DrawIndexedPrimitiveUPT> {
public:
    static D3D9_DrawIndexedPrimitiveUP* instance;
    D3D9_DrawIndexedPrimitiveUP(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_DrawIndexedPrimitiveUPT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void* pIndexData, D3DFORMAT IndexDataFormat, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
        HRESULT result = instance->pFunction(pDevice, PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_DrawIndexedPrimitiveUP<D3D9_DrawIndexedPrimitiveUPT>* D3D9_DrawIndexedPrimitiveUP<D3D9_DrawIndexedPrimitiveUPT>::instance = nullptr;

template <typename FuncT>
class D3D9_ProcessVertices : public xNyuHook<D3D9_ProcessVerticesT> {
public:
    static D3D9_ProcessVertices* instance;
    D3D9_ProcessVertices(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_ProcessVerticesT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
        HRESULT result = instance->pFunction(pDevice, SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_ProcessVertices<D3D9_ProcessVerticesT>* D3D9_ProcessVertices<D3D9_ProcessVerticesT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateVertexDeclaration : public xNyuHook<D3D9_CreateVertexDeclarationT> {
public:
    static D3D9_CreateVertexDeclaration* instance;
    D3D9_CreateVertexDeclaration(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateVertexDeclarationT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pVertexElements, ppDecl);
        HRESULT result = instance->pFunction(pDevice, pVertexElements, ppDecl);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pVertexElements, ppDecl);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateVertexDeclaration<D3D9_CreateVertexDeclarationT>* D3D9_CreateVertexDeclaration<D3D9_CreateVertexDeclarationT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetVertexDeclaration : public xNyuHook<D3D9_SetVertexDeclarationT> {
public:
    static D3D9_SetVertexDeclaration* instance;
    D3D9_SetVertexDeclaration(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetVertexDeclarationT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DVertexDeclaration9* pDecl)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pDecl);
        HRESULT result = instance->pFunction(pDevice, pDecl);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pDecl);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetVertexDeclaration<D3D9_SetVertexDeclarationT>* D3D9_SetVertexDeclaration<D3D9_SetVertexDeclarationT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetVertexDeclaration : public xNyuHook<D3D9_GetVertexDeclarationT> {
public:
    static D3D9_GetVertexDeclaration* instance;
    D3D9_GetVertexDeclaration(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetVertexDeclarationT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DVertexDeclaration9** ppDecl)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, ppDecl);
        HRESULT result = instance->pFunction(pDevice, ppDecl);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, ppDecl);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetVertexDeclaration<D3D9_GetVertexDeclarationT>* D3D9_GetVertexDeclaration<D3D9_GetVertexDeclarationT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetFVF : public xNyuHook<D3D9_SetFVFT> {
public:
    static D3D9_SetFVF* instance;
    D3D9_SetFVF(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetFVFT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD FVF)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, FVF);
        HRESULT result = instance->pFunction(pDevice, FVF);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, FVF);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetFVF<D3D9_SetFVFT>* D3D9_SetFVF<D3D9_SetFVFT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetFVF : public xNyuHook<D3D9_GetFVFT> {
public:
    static D3D9_GetFVF* instance;
    D3D9_GetFVF(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetFVFT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, DWORD* pFVF)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pFVF);
        HRESULT result = instance->pFunction(pDevice, pFVF);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pFVF);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetFVF<D3D9_GetFVFT>* D3D9_GetFVF<D3D9_GetFVFT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateVertexShader : public xNyuHook<D3D9_CreateVertexShaderT> {
public:
    static D3D9_CreateVertexShader* instance;
    D3D9_CreateVertexShader(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateVertexShaderT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, const DWORD* pFunction, IDirect3DVertexShader9** ppShader)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pFunction, ppShader);
        HRESULT result = instance->pFunction(pDevice, pFunction, ppShader);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pFunction, ppShader);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateVertexShader<D3D9_CreateVertexShaderT>* D3D9_CreateVertexShader<D3D9_CreateVertexShaderT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetVertexShader : public xNyuHook<D3D9_SetVertexShaderT> {
public:
    static D3D9_SetVertexShader* instance;
    D3D9_SetVertexShader(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetVertexShaderT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DVertexShader9* pShader)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pShader);
        HRESULT result = instance->pFunction(pDevice, pShader);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pShader);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetVertexShader<D3D9_SetVertexShaderT>* D3D9_SetVertexShader<D3D9_SetVertexShaderT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetVertexShader : public xNyuHook<D3D9_GetVertexShaderT> {
public:
    static D3D9_GetVertexShader* instance;
    D3D9_GetVertexShader(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetVertexShaderT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DVertexShader9** ppShader)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, ppShader);
        HRESULT result = instance->pFunction(pDevice, ppShader);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, ppShader);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetVertexShader<D3D9_GetVertexShaderT>* D3D9_GetVertexShader<D3D9_GetVertexShaderT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetVertexShaderConstantF : public xNyuHook<D3D9_SetVertexShaderConstantFT> {
public:
    static D3D9_SetVertexShaderConstantF* instance;
    D3D9_SetVertexShaderConstantF(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetVertexShaderConstantFT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StartRegister, const float* pConstantData, UINT Vector4fCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StartRegister, pConstantData, Vector4fCount);
        HRESULT result = instance->pFunction(pDevice, StartRegister, pConstantData, Vector4fCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StartRegister, pConstantData, Vector4fCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetVertexShaderConstantF<D3D9_SetVertexShaderConstantFT>* D3D9_SetVertexShaderConstantF<D3D9_SetVertexShaderConstantFT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetVertexShaderConstantF : public xNyuHook<D3D9_GetVertexShaderConstantFT> {
public:
    static D3D9_GetVertexShaderConstantF* instance;
    D3D9_GetVertexShaderConstantF(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetVertexShaderConstantFT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StartRegister, float* pConstantData, UINT Vector4fCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StartRegister, pConstantData, Vector4fCount);
        HRESULT result = instance->pFunction(pDevice, StartRegister, pConstantData, Vector4fCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StartRegister, pConstantData, Vector4fCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetVertexShaderConstantF<D3D9_GetVertexShaderConstantFT>* D3D9_GetVertexShaderConstantF<D3D9_GetVertexShaderConstantFT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetVertexShaderConstantI : public xNyuHook<D3D9_SetVertexShaderConstantIT> {
public:
    static D3D9_SetVertexShaderConstantI* instance;
    D3D9_SetVertexShaderConstantI(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetVertexShaderConstantIT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StartRegister, const int* pConstantData, UINT Vector4iCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StartRegister, pConstantData, Vector4iCount);
        HRESULT result = instance->pFunction(pDevice, StartRegister, pConstantData, Vector4iCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StartRegister, pConstantData, Vector4iCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetVertexShaderConstantI<D3D9_SetVertexShaderConstantIT>* D3D9_SetVertexShaderConstantI<D3D9_SetVertexShaderConstantIT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetVertexShaderConstantI : public xNyuHook<D3D9_GetVertexShaderConstantIT> {
public:
    static D3D9_GetVertexShaderConstantI* instance;
    D3D9_GetVertexShaderConstantI(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetVertexShaderConstantIT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StartRegister, int* pConstantData, UINT Vector4iCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StartRegister, pConstantData, Vector4iCount);
        HRESULT result = instance->pFunction(pDevice, StartRegister, pConstantData, Vector4iCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StartRegister, pConstantData, Vector4iCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetVertexShaderConstantI<D3D9_GetVertexShaderConstantIT>* D3D9_GetVertexShaderConstantI<D3D9_GetVertexShaderConstantIT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetVertexShaderConstantB : public xNyuHook<D3D9_SetVertexShaderConstantBT> {
public:
    static D3D9_SetVertexShaderConstantB* instance;
    D3D9_SetVertexShaderConstantB(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetVertexShaderConstantBT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StartRegister, const BOOL* pConstantData, UINT BoolCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StartRegister, pConstantData, BoolCount);
        HRESULT result = instance->pFunction(pDevice, StartRegister, pConstantData, BoolCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StartRegister, pConstantData, BoolCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetVertexShaderConstantB<D3D9_SetVertexShaderConstantBT>* D3D9_SetVertexShaderConstantB<D3D9_SetVertexShaderConstantBT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetVertexShaderConstantB : public xNyuHook<D3D9_GetVertexShaderConstantBT> {
public:
    static D3D9_GetVertexShaderConstantB* instance;
    D3D9_GetVertexShaderConstantB(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetVertexShaderConstantBT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StartRegister, pConstantData, BoolCount);
        HRESULT result = instance->pFunction(pDevice, StartRegister, pConstantData, BoolCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StartRegister, pConstantData, BoolCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetVertexShaderConstantB<D3D9_GetVertexShaderConstantBT>* D3D9_GetVertexShaderConstantB<D3D9_GetVertexShaderConstantBT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetStreamSource : public xNyuHook<D3D9_SetStreamSourceT> {
public:
    static D3D9_SetStreamSource* instance;
    D3D9_SetStreamSource(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetStreamSourceT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StreamNumber, pStreamData, OffsetInBytes, Stride);
        HRESULT result = instance->pFunction(pDevice, StreamNumber, pStreamData, OffsetInBytes, Stride);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StreamNumber, pStreamData, OffsetInBytes, Stride);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetStreamSource<D3D9_SetStreamSourceT>* D3D9_SetStreamSource<D3D9_SetStreamSourceT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetStreamSource : public xNyuHook<D3D9_GetStreamSourceT> {
public:
    static D3D9_GetStreamSource* instance;
    D3D9_GetStreamSource(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetStreamSourceT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StreamNumber, ppStreamData, pOffsetInBytes, pStride);
        HRESULT result = instance->pFunction(pDevice, StreamNumber, ppStreamData, pOffsetInBytes, pStride);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StreamNumber, ppStreamData, pOffsetInBytes, pStride);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetStreamSource<D3D9_GetStreamSourceT>* D3D9_GetStreamSource<D3D9_GetStreamSourceT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetStreamSourceFreq : public xNyuHook<D3D9_SetStreamSourceFreqT> {
public:
    static D3D9_SetStreamSourceFreq* instance;
    D3D9_SetStreamSourceFreq(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetStreamSourceFreqT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StreamNumber, UINT Setting)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StreamNumber, Setting);
        HRESULT result = instance->pFunction(pDevice, StreamNumber, Setting);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StreamNumber, Setting);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetStreamSourceFreq<D3D9_SetStreamSourceFreqT>* D3D9_SetStreamSourceFreq<D3D9_SetStreamSourceFreqT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetStreamSourceFreq : public xNyuHook<D3D9_GetStreamSourceFreqT> {
public:
    static D3D9_GetStreamSourceFreq* instance;
    D3D9_GetStreamSourceFreq(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetStreamSourceFreqT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StreamNumber, UINT* pSetting)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StreamNumber, pSetting);
        HRESULT result = instance->pFunction(pDevice, StreamNumber, pSetting);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StreamNumber, pSetting);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetStreamSourceFreq<D3D9_GetStreamSourceFreqT>* D3D9_GetStreamSourceFreq<D3D9_GetStreamSourceFreqT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetIndices : public xNyuHook<D3D9_SetIndicesT> {
public:
    static D3D9_SetIndices* instance;
    D3D9_SetIndices(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetIndicesT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DIndexBuffer9* pIndexData)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pIndexData);
        HRESULT result = instance->pFunction(pDevice, pIndexData);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pIndexData);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetIndices<D3D9_SetIndicesT>* D3D9_SetIndices<D3D9_SetIndicesT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetIndices : public xNyuHook<D3D9_GetIndicesT> {
public:
    static D3D9_GetIndices* instance;
    D3D9_GetIndices(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetIndicesT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DIndexBuffer9** ppIndexData)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, ppIndexData);
        HRESULT result = instance->pFunction(pDevice, ppIndexData);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, ppIndexData);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetIndices<D3D9_GetIndicesT>* D3D9_GetIndices<D3D9_GetIndicesT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreatePixelShader : public xNyuHook<D3D9_CreatePixelShaderT> {
public:
    static D3D9_CreatePixelShader* instance;
    D3D9_CreatePixelShader(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreatePixelShaderT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, const DWORD* pFunction, IDirect3DPixelShader9** ppShader)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pFunction, ppShader);
        HRESULT result = instance->pFunction(pDevice, pFunction, ppShader);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pFunction, ppShader);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreatePixelShader<D3D9_CreatePixelShaderT>* D3D9_CreatePixelShader<D3D9_CreatePixelShaderT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetPixelShader : public xNyuHook<D3D9_SetPixelShaderT> {
public:
    static D3D9_SetPixelShader* instance;
    D3D9_SetPixelShader(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetPixelShaderT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DPixelShader9* pShader)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, pShader);
        HRESULT result = instance->pFunction(pDevice, pShader);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, pShader);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetPixelShader<D3D9_SetPixelShaderT>* D3D9_SetPixelShader<D3D9_SetPixelShaderT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetPixelShader : public xNyuHook<D3D9_GetPixelShaderT> {
public:
    static D3D9_GetPixelShader* instance;
    D3D9_GetPixelShader(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetPixelShaderT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, IDirect3DPixelShader9** ppShader)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, ppShader);
        HRESULT result = instance->pFunction(pDevice, ppShader);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, ppShader);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetPixelShader<D3D9_GetPixelShaderT>* D3D9_GetPixelShader<D3D9_GetPixelShaderT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetPixelShaderConstantF : public xNyuHook<D3D9_SetPixelShaderConstantFT> {
public:
    static D3D9_SetPixelShaderConstantF* instance;
    D3D9_SetPixelShaderConstantF(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetPixelShaderConstantFT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StartRegister, const float* pConstantData, UINT Vector4fCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StartRegister, pConstantData, Vector4fCount);
        HRESULT result = instance->pFunction(pDevice, StartRegister, pConstantData, Vector4fCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StartRegister, pConstantData, Vector4fCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetPixelShaderConstantF<D3D9_SetPixelShaderConstantFT>* D3D9_SetPixelShaderConstantF<D3D9_SetPixelShaderConstantFT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetPixelShaderConstantF : public xNyuHook<D3D9_GetPixelShaderConstantFT> {
public:
    static D3D9_GetPixelShaderConstantF* instance;
    D3D9_GetPixelShaderConstantF(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetPixelShaderConstantFT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StartRegister, float* pConstantData, UINT Vector4fCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StartRegister, pConstantData, Vector4fCount);
        HRESULT result = instance->pFunction(pDevice, StartRegister, pConstantData, Vector4fCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StartRegister, pConstantData, Vector4fCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetPixelShaderConstantF<D3D9_GetPixelShaderConstantFT>* D3D9_GetPixelShaderConstantF<D3D9_GetPixelShaderConstantFT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetPixelShaderConstantI : public xNyuHook<D3D9_SetPixelShaderConstantIT> {
public:
    static D3D9_SetPixelShaderConstantI* instance;
    D3D9_SetPixelShaderConstantI(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetPixelShaderConstantIT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StartRegister, const int* pConstantData, UINT Vector4iCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StartRegister, pConstantData, Vector4iCount);
        HRESULT result = instance->pFunction(pDevice, StartRegister, pConstantData, Vector4iCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StartRegister, pConstantData, Vector4iCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetPixelShaderConstantI<D3D9_SetPixelShaderConstantIT>* D3D9_SetPixelShaderConstantI<D3D9_SetPixelShaderConstantIT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetPixelShaderConstantI : public xNyuHook<D3D9_GetPixelShaderConstantIT> {
public:
    static D3D9_GetPixelShaderConstantI* instance;
    D3D9_GetPixelShaderConstantI(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetPixelShaderConstantIT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StartRegister, int* pConstantData, UINT Vector4iCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StartRegister, pConstantData, Vector4iCount);
        HRESULT result = instance->pFunction(pDevice, StartRegister, pConstantData, Vector4iCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StartRegister, pConstantData, Vector4iCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetPixelShaderConstantI<D3D9_GetPixelShaderConstantIT>* D3D9_GetPixelShaderConstantI<D3D9_GetPixelShaderConstantIT>::instance = nullptr;

template <typename FuncT>
class D3D9_SetPixelShaderConstantB : public xNyuHook<D3D9_SetPixelShaderConstantBT> {
public:
    static D3D9_SetPixelShaderConstantB* instance;
    D3D9_SetPixelShaderConstantB(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_SetPixelShaderConstantBT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StartRegister, const BOOL* pConstantData, UINT BoolCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StartRegister, pConstantData, BoolCount);
        HRESULT result = instance->pFunction(pDevice, StartRegister, pConstantData, BoolCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StartRegister, pConstantData, BoolCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_SetPixelShaderConstantB<D3D9_SetPixelShaderConstantBT>* D3D9_SetPixelShaderConstantB<D3D9_SetPixelShaderConstantBT>::instance = nullptr;

template <typename FuncT>
class D3D9_GetPixelShaderConstantB : public xNyuHook<D3D9_GetPixelShaderConstantBT> {
public:
    static D3D9_GetPixelShaderConstantB* instance;
    D3D9_GetPixelShaderConstantB(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_GetPixelShaderConstantBT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, StartRegister, pConstantData, BoolCount);
        HRESULT result = instance->pFunction(pDevice, StartRegister, pConstantData, BoolCount);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, StartRegister, pConstantData, BoolCount);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_GetPixelShaderConstantB<D3D9_GetPixelShaderConstantBT>* D3D9_GetPixelShaderConstantB<D3D9_GetPixelShaderConstantBT>::instance = nullptr;

template <typename FuncT>
class D3D9_DrawRectPatch : public xNyuHook<D3D9_DrawRectPatchT> {
public:
    static D3D9_DrawRectPatch* instance;
    D3D9_DrawRectPatch(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_DrawRectPatchT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT Handle, const float* pNumSegs, const D3DRECTPATCH_INFO* pRectPatchInfo)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Handle, pNumSegs, pRectPatchInfo);
        HRESULT result = instance->pFunction(pDevice, Handle, pNumSegs, pRectPatchInfo);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Handle, pNumSegs, pRectPatchInfo);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_DrawRectPatch<D3D9_DrawRectPatchT>* D3D9_DrawRectPatch<D3D9_DrawRectPatchT>::instance = nullptr;

template <typename FuncT>
class D3D9_DrawTriPatch : public xNyuHook<D3D9_DrawTriPatchT> {
public:
    static D3D9_DrawTriPatch* instance;
    D3D9_DrawTriPatch(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_DrawTriPatchT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT Handle, const float* pNumSegs, const D3DTRIPATCH_INFO* pTriPatchInfo)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Handle, pNumSegs, pTriPatchInfo);
        HRESULT result = instance->pFunction(pDevice, Handle, pNumSegs, pTriPatchInfo);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Handle, pNumSegs, pTriPatchInfo);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_DrawTriPatch<D3D9_DrawTriPatchT>* D3D9_DrawTriPatch<D3D9_DrawTriPatchT>::instance = nullptr;

template <typename FuncT>
class D3D9_DeletePatch : public xNyuHook<D3D9_DeletePatchT> {
public:
    static D3D9_DeletePatch* instance;
    D3D9_DeletePatch(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_DeletePatchT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, UINT Handle)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Handle);
        HRESULT result = instance->pFunction(pDevice, Handle);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Handle);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_DeletePatch<D3D9_DeletePatchT>* D3D9_DeletePatch<D3D9_DeletePatchT>::instance = nullptr;

template <typename FuncT>
class D3D9_CreateQuery : public xNyuHook<D3D9_CreateQueryT> {
public:
    static D3D9_CreateQuery* instance;
    D3D9_CreateQuery(void* originalAddress, void* hookExecuteBefore = nullptr, void* hookExecuteAfter = nullptr)
        : xNyuHook<D3D9_CreateQueryT>(originalAddress, hookExecuteBefore, hookExecuteAfter) {
        instance = this;
    }
    static HRESULT __stdcall CustomHook(IDirect3DDevice9* pDevice, D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
    {
        instance->remove();
        if (instance->pFunctionBefore != nullptr) instance->pFunctionBefore(pDevice, Type, ppQuery);
        HRESULT result = instance->pFunction(pDevice, Type, ppQuery);
        if (instance->pFunctionAfter != nullptr) instance->pFunctionAfter(pDevice, Type, ppQuery);
        instance->install();
        return result;
    }
    void install() {
        if (sizeof(void*) == 8) Subhook.Install((void*)instance->pFunction, instance->CustomHook, subhook::HookFlags::HookFlag64BitOffset);
        if (sizeof(void*) == 4) Subhook.Install((void*)instance->pFunction, instance->CustomHook);
    }
};
D3D9_CreateQuery<D3D9_CreateQueryT>* D3D9_CreateQuery<D3D9_CreateQueryT>::instance = nullptr;



void D3D9_InitExtraHooks(std::vector<uintptr_t> vTable)
{
    D3D9_QueryInterface<D3D9_QueryInterfaceT>::instance = new D3D9_QueryInterface<D3D9_QueryInterfaceT>((void*)vTable[0]);
    D3D9_AddRef<D3D9_AddRefT>::instance = new D3D9_AddRef<D3D9_AddRefT>((void*)vTable[1]);
    D3D9_Release<D3D9_ReleaseT>::instance = new D3D9_Release<D3D9_ReleaseT>((void*)vTable[2]);
    D3D9_TestCooperativeLevel<D3D9_TestCooperativeLevelT>::instance = new D3D9_TestCooperativeLevel<D3D9_TestCooperativeLevelT>((void*)vTable[3]);
    D3D9_GetAvailableTextureMem<D3D9_GetAvailableTextureMemT>::instance = new D3D9_GetAvailableTextureMem<D3D9_GetAvailableTextureMemT>((void*)vTable[4]);
    D3D9_EvictManagedResources<D3D9_EvictManagedResourcesT>::instance = new D3D9_EvictManagedResources<D3D9_EvictManagedResourcesT>((void*)vTable[5]);
    D3D9_GetDirect3D<D3D9_GetDirect3DT>::instance = new D3D9_GetDirect3D<D3D9_GetDirect3DT>((void*)vTable[6]);
    D3D9_GetDeviceCaps<D3D9_GetDeviceCapsT>::instance = new D3D9_GetDeviceCaps<D3D9_GetDeviceCapsT>((void*)vTable[7]);
    D3D9_GetDisplayMode<D3D9_GetDisplayModeT>::instance = new D3D9_GetDisplayMode<D3D9_GetDisplayModeT>((void*)vTable[8]);
    D3D9_GetCreationParameters<D3D9_GetCreationParametersT>::instance = new D3D9_GetCreationParameters<D3D9_GetCreationParametersT>((void*)vTable[9]);
    D3D9_SetCursorProperties<D3D9_SetCursorPropertiesT>::instance = new D3D9_SetCursorProperties<D3D9_SetCursorPropertiesT>((void*)vTable[10]);
    D3D9_SetCursorPosition<D3D9_SetCursorPositionT>::instance = new D3D9_SetCursorPosition<D3D9_SetCursorPositionT>((void*)vTable[11]);
    D3D9_ShowCursor<D3D9_ShowCursorT>::instance = new D3D9_ShowCursor<D3D9_ShowCursorT>((void*)vTable[12]);
    D3D9_CreateAdditionalSwapChain<D3D9_CreateAdditionalSwapChainT>::instance = new D3D9_CreateAdditionalSwapChain<D3D9_CreateAdditionalSwapChainT>((void*)vTable[13]);
    D3D9_GetSwapChain<D3D9_GetSwapChainT>::instance = new D3D9_GetSwapChain<D3D9_GetSwapChainT>((void*)vTable[14]);
    D3D9_GetNumberOfSwapChains<D3D9_GetNumberOfSwapChainsT>::instance = new D3D9_GetNumberOfSwapChains<D3D9_GetNumberOfSwapChainsT>((void*)vTable[15]);
    D3D9_Reset<D3D9_ResetT>::instance = new D3D9_Reset<D3D9_ResetT>((void*)vTable[16]);
    //D3D9_Present<D3D9_PresentT>::instance = new D3D9_Present<D3D9_PresentT>((void*)vTable[17]);
    D3D9_GetBackBuffer<D3D9_GetBackBufferT>::instance = new D3D9_GetBackBuffer<D3D9_GetBackBufferT>((void*)vTable[18]);
    D3D9_GetRasterStatus<D3D9_GetRasterStatusT>::instance = new D3D9_GetRasterStatus<D3D9_GetRasterStatusT>((void*)vTable[19]);
    D3D9_SetDialogBoxMode<D3D9_SetDialogBoxModeT>::instance = new D3D9_SetDialogBoxMode<D3D9_SetDialogBoxModeT>((void*)vTable[20]);
    D3D9_SetGammaRamp<D3D9_SetGammaRampT>::instance = new D3D9_SetGammaRamp<D3D9_SetGammaRampT>((void*)vTable[21]);
    D3D9_GetGammaRamp<D3D9_GetGammaRampT>::instance = new D3D9_GetGammaRamp<D3D9_GetGammaRampT>((void*)vTable[22]);
    D3D9_CreateTexture<D3D9_CreateTextureT>::instance = new D3D9_CreateTexture<D3D9_CreateTextureT>((void*)vTable[23]);
    D3D9_CreateVolumeTexture<D3D9_CreateVolumeTextureT>::instance = new D3D9_CreateVolumeTexture<D3D9_CreateVolumeTextureT>((void*)vTable[24]);
    D3D9_CreateCubeTexture<D3D9_CreateCubeTextureT>::instance = new D3D9_CreateCubeTexture<D3D9_CreateCubeTextureT>((void*)vTable[25]);
    D3D9_CreateVertexBuffer<D3D9_CreateVertexBufferT>::instance = new D3D9_CreateVertexBuffer<D3D9_CreateVertexBufferT>((void*)vTable[26]);
    D3D9_CreateIndexBuffer<D3D9_CreateIndexBufferT>::instance = new D3D9_CreateIndexBuffer<D3D9_CreateIndexBufferT>((void*)vTable[27]);
    D3D9_CreateRenderTarget<D3D9_CreateRenderTargetT>::instance = new D3D9_CreateRenderTarget<D3D9_CreateRenderTargetT>((void*)vTable[28]);
    D3D9_CreateDepthStencilSurface<D3D9_CreateDepthStencilSurfaceT>::instance = new D3D9_CreateDepthStencilSurface<D3D9_CreateDepthStencilSurfaceT>((void*)vTable[29]);
    D3D9_UpdateSurface<D3D9_UpdateSurfaceT>::instance = new D3D9_UpdateSurface<D3D9_UpdateSurfaceT>((void*)vTable[30]);
    D3D9_UpdateTexture<D3D9_UpdateTextureT>::instance = new D3D9_UpdateTexture<D3D9_UpdateTextureT>((void*)vTable[31]);
    D3D9_GetRenderTargetData<D3D9_GetRenderTargetDataT>::instance = new D3D9_GetRenderTargetData<D3D9_GetRenderTargetDataT>((void*)vTable[32]);
    D3D9_GetFrontBufferData<D3D9_GetFrontBufferDataT>::instance = new D3D9_GetFrontBufferData<D3D9_GetFrontBufferDataT>((void*)vTable[33]);
    D3D9_StretchRect<D3D9_StretchRectT>::instance = new D3D9_StretchRect<D3D9_StretchRectT>((void*)vTable[34]);
    D3D9_ColorFill<D3D9_ColorFillT>::instance = new D3D9_ColorFill<D3D9_ColorFillT>((void*)vTable[35]);
    D3D9_CreateOffscreenPlainSurface<D3D9_CreateOffscreenPlainSurfaceT>::instance = new D3D9_CreateOffscreenPlainSurface<D3D9_CreateOffscreenPlainSurfaceT>((void*)vTable[36]);
    D3D9_SetRenderTarget<D3D9_SetRenderTargetT>::instance = new D3D9_SetRenderTarget<D3D9_SetRenderTargetT>((void*)vTable[37]);
    D3D9_GetRenderTarget<D3D9_GetRenderTargetT>::instance = new D3D9_GetRenderTarget<D3D9_GetRenderTargetT>((void*)vTable[38]);
    D3D9_SetDepthStencilSurface<D3D9_SetDepthStencilSurfaceT>::instance = new D3D9_SetDepthStencilSurface<D3D9_SetDepthStencilSurfaceT>((void*)vTable[39]);
    D3D9_GetDepthStencilSurface<D3D9_GetDepthStencilSurfaceT>::instance = new D3D9_GetDepthStencilSurface<D3D9_GetDepthStencilSurfaceT>((void*)vTable[40]);
    D3D9_BeginScene<D3D9_BeginSceneT>::instance = new D3D9_BeginScene<D3D9_BeginSceneT>((void*)vTable[41]);
    D3D9_EndScene<D3D9_EndSceneT>::instance = new D3D9_EndScene<D3D9_EndSceneT>((void*)vTable[42]);
    D3D9_Clear<D3D9_ClearT>::instance = new D3D9_Clear<D3D9_ClearT>((void*)vTable[43]);
    D3D9_SetTransform<D3D9_SetTransformT>::instance = new D3D9_SetTransform<D3D9_SetTransformT>((void*)vTable[44]);
    D3D9_GetTransform<D3D9_GetTransformT>::instance = new D3D9_GetTransform<D3D9_GetTransformT>((void*)vTable[45]);
    D3D9_MultiplyTransform<D3D9_MultiplyTransformT>::instance = new D3D9_MultiplyTransform<D3D9_MultiplyTransformT>((void*)vTable[46]);
    D3D9_SetViewport<D3D9_SetViewportT>::instance = new D3D9_SetViewport<D3D9_SetViewportT>((void*)vTable[47]);
    D3D9_GetViewport<D3D9_GetViewportT>::instance = new D3D9_GetViewport<D3D9_GetViewportT>((void*)vTable[48]);
    D3D9_SetMaterial<D3D9_SetMaterialT>::instance = new D3D9_SetMaterial<D3D9_SetMaterialT>((void*)vTable[49]);
    D3D9_GetMaterial<D3D9_GetMaterialT>::instance = new D3D9_GetMaterial<D3D9_GetMaterialT>((void*)vTable[50]);
    D3D9_SetLight<D3D9_SetLightT>::instance = new D3D9_SetLight<D3D9_SetLightT>((void*)vTable[51]);
    D3D9_GetLight<D3D9_GetLightT>::instance = new D3D9_GetLight<D3D9_GetLightT>((void*)vTable[52]);
    D3D9_LightEnable<D3D9_LightEnableT>::instance = new D3D9_LightEnable<D3D9_LightEnableT>((void*)vTable[53]);
    D3D9_GetLightEnable<D3D9_GetLightEnableT>::instance = new D3D9_GetLightEnable<D3D9_GetLightEnableT>((void*)vTable[54]);
    D3D9_SetClipPlane<D3D9_SetClipPlaneT>::instance = new D3D9_SetClipPlane<D3D9_SetClipPlaneT>((void*)vTable[55]);
    D3D9_GetClipPlane<D3D9_GetClipPlaneT>::instance = new D3D9_GetClipPlane<D3D9_GetClipPlaneT>((void*)vTable[56]);
    D3D9_SetRenderState<D3D9_SetRenderStateT>::instance = new D3D9_SetRenderState<D3D9_SetRenderStateT>((void*)vTable[57]);
    D3D9_GetRenderState<D3D9_GetRenderStateT>::instance = new D3D9_GetRenderState<D3D9_GetRenderStateT>((void*)vTable[58]);
    D3D9_CreateStateBlock<D3D9_CreateStateBlockT>::instance = new D3D9_CreateStateBlock<D3D9_CreateStateBlockT>((void*)vTable[59]);
    D3D9_BeginStateBlock<D3D9_BeginStateBlockT>::instance = new D3D9_BeginStateBlock<D3D9_BeginStateBlockT>((void*)vTable[60]);
    D3D9_EndStateBlock<D3D9_EndStateBlockT>::instance = new D3D9_EndStateBlock<D3D9_EndStateBlockT>((void*)vTable[61]);
    D3D9_SetClipStatus<D3D9_SetClipStatusT>::instance = new D3D9_SetClipStatus<D3D9_SetClipStatusT>((void*)vTable[62]);
    D3D9_GetClipStatus<D3D9_GetClipStatusT>::instance = new D3D9_GetClipStatus<D3D9_GetClipStatusT>((void*)vTable[63]);
    D3D9_GetTexture<D3D9_GetTextureT>::instance = new D3D9_GetTexture<D3D9_GetTextureT>((void*)vTable[64]);
    D3D9_SetTexture<D3D9_SetTextureT>::instance = new D3D9_SetTexture<D3D9_SetTextureT>((void*)vTable[65]);
    D3D9_GetTextureStageState<D3D9_GetTextureStageStateT>::instance = new D3D9_GetTextureStageState<D3D9_GetTextureStageStateT>((void*)vTable[66]);
    D3D9_SetTextureStageState<D3D9_SetTextureStageStateT>::instance = new D3D9_SetTextureStageState<D3D9_SetTextureStageStateT>((void*)vTable[67]);
    D3D9_GetSamplerState<D3D9_GetSamplerStateT>::instance = new D3D9_GetSamplerState<D3D9_GetSamplerStateT>((void*)vTable[68]);
    D3D9_SetSamplerState<D3D9_SetSamplerStateT>::instance = new D3D9_SetSamplerState<D3D9_SetSamplerStateT>((void*)vTable[69]);
    D3D9_ValidateDevice<D3D9_ValidateDeviceT>::instance = new D3D9_ValidateDevice<D3D9_ValidateDeviceT>((void*)vTable[70]);
    D3D9_SetPaletteEntries<D3D9_SetPaletteEntriesT>::instance = new D3D9_SetPaletteEntries<D3D9_SetPaletteEntriesT>((void*)vTable[71]);
    D3D9_GetPaletteEntries<D3D9_GetPaletteEntriesT>::instance = new D3D9_GetPaletteEntries<D3D9_GetPaletteEntriesT>((void*)vTable[72]);
    D3D9_SetCurrentTexturePalette<D3D9_SetCurrentTexturePaletteT>::instance = new D3D9_SetCurrentTexturePalette<D3D9_SetCurrentTexturePaletteT>((void*)vTable[73]);
    D3D9_GetCurrentTexturePalette<D3D9_GetCurrentTexturePaletteT>::instance = new D3D9_GetCurrentTexturePalette<D3D9_GetCurrentTexturePaletteT>((void*)vTable[74]);
    D3D9_SetScissorRect<D3D9_SetScissorRectT>::instance = new D3D9_SetScissorRect<D3D9_SetScissorRectT>((void*)vTable[75]);
    D3D9_GetScissorRect<D3D9_GetScissorRectT>::instance = new D3D9_GetScissorRect<D3D9_GetScissorRectT>((void*)vTable[76]);
    D3D9_SetSoftwareVertexProcessing<D3D9_SetSoftwareVertexProcessingT>::instance = new D3D9_SetSoftwareVertexProcessing<D3D9_SetSoftwareVertexProcessingT>((void*)vTable[77]);
    D3D9_GetSoftwareVertexProcessing<D3D9_GetSoftwareVertexProcessingT>::instance = new D3D9_GetSoftwareVertexProcessing<D3D9_GetSoftwareVertexProcessingT>((void*)vTable[78]);
    D3D9_SetNPatchMode<D3D9_SetNPatchModeT>::instance = new D3D9_SetNPatchMode<D3D9_SetNPatchModeT>((void*)vTable[79]);
    D3D9_GetNPatchMode<D3D9_GetNPatchModeT>::instance = new D3D9_GetNPatchMode<D3D9_GetNPatchModeT>((void*)vTable[80]);
    D3D9_DrawPrimitive<D3D9_DrawPrimitiveT>::instance = new D3D9_DrawPrimitive<D3D9_DrawPrimitiveT>((void*)vTable[81]);
    D3D9_DrawIndexedPrimitive<D3D9_DrawIndexedPrimitiveT>::instance = new D3D9_DrawIndexedPrimitive<D3D9_DrawIndexedPrimitiveT>((void*)vTable[82]);
    D3D9_DrawPrimitiveUP<D3D9_DrawPrimitiveUPT>::instance = new D3D9_DrawPrimitiveUP<D3D9_DrawPrimitiveUPT>((void*)vTable[83]);
    D3D9_DrawIndexedPrimitiveUP<D3D9_DrawIndexedPrimitiveUPT>::instance = new D3D9_DrawIndexedPrimitiveUP<D3D9_DrawIndexedPrimitiveUPT>((void*)vTable[84]);
    D3D9_ProcessVertices<D3D9_ProcessVerticesT>::instance = new D3D9_ProcessVertices<D3D9_ProcessVerticesT>((void*)vTable[85]);
    D3D9_CreateVertexDeclaration<D3D9_CreateVertexDeclarationT>::instance = new D3D9_CreateVertexDeclaration<D3D9_CreateVertexDeclarationT>((void*)vTable[86]);
    D3D9_SetVertexDeclaration<D3D9_SetVertexDeclarationT>::instance = new D3D9_SetVertexDeclaration<D3D9_SetVertexDeclarationT>((void*)vTable[87]);
    D3D9_GetVertexDeclaration<D3D9_GetVertexDeclarationT>::instance = new D3D9_GetVertexDeclaration<D3D9_GetVertexDeclarationT>((void*)vTable[88]);
    D3D9_SetFVF<D3D9_SetFVFT>::instance = new D3D9_SetFVF<D3D9_SetFVFT>((void*)vTable[89]);
    D3D9_GetFVF<D3D9_GetFVFT>::instance = new D3D9_GetFVF<D3D9_GetFVFT>((void*)vTable[90]);
    D3D9_CreateVertexShader<D3D9_CreateVertexShaderT>::instance = new D3D9_CreateVertexShader<D3D9_CreateVertexShaderT>((void*)vTable[91]);
    D3D9_SetVertexShader<D3D9_SetVertexShaderT>::instance = new D3D9_SetVertexShader<D3D9_SetVertexShaderT>((void*)vTable[92]);
    D3D9_GetVertexShader<D3D9_GetVertexShaderT>::instance = new D3D9_GetVertexShader<D3D9_GetVertexShaderT>((void*)vTable[93]);
    D3D9_SetVertexShaderConstantF<D3D9_SetVertexShaderConstantFT>::instance = new D3D9_SetVertexShaderConstantF<D3D9_SetVertexShaderConstantFT>((void*)vTable[94]);
    D3D9_GetVertexShaderConstantF<D3D9_GetVertexShaderConstantFT>::instance = new D3D9_GetVertexShaderConstantF<D3D9_GetVertexShaderConstantFT>((void*)vTable[95]);
    D3D9_SetVertexShaderConstantI<D3D9_SetVertexShaderConstantIT>::instance = new D3D9_SetVertexShaderConstantI<D3D9_SetVertexShaderConstantIT>((void*)vTable[96]);
    D3D9_GetVertexShaderConstantI<D3D9_GetVertexShaderConstantIT>::instance = new D3D9_GetVertexShaderConstantI<D3D9_GetVertexShaderConstantIT>((void*)vTable[97]);
    D3D9_SetVertexShaderConstantB<D3D9_SetVertexShaderConstantBT>::instance = new D3D9_SetVertexShaderConstantB<D3D9_SetVertexShaderConstantBT>((void*)vTable[98]);
    D3D9_GetVertexShaderConstantB<D3D9_GetVertexShaderConstantBT>::instance = new D3D9_GetVertexShaderConstantB<D3D9_GetVertexShaderConstantBT>((void*)vTable[99]);
    D3D9_SetStreamSource<D3D9_SetStreamSourceT>::instance = new D3D9_SetStreamSource<D3D9_SetStreamSourceT>((void*)vTable[100]);
    D3D9_GetStreamSource<D3D9_GetStreamSourceT>::instance = new D3D9_GetStreamSource<D3D9_GetStreamSourceT>((void*)vTable[101]);
    D3D9_SetStreamSourceFreq<D3D9_SetStreamSourceFreqT>::instance = new D3D9_SetStreamSourceFreq<D3D9_SetStreamSourceFreqT>((void*)vTable[102]);
    D3D9_GetStreamSourceFreq<D3D9_GetStreamSourceFreqT>::instance = new D3D9_GetStreamSourceFreq<D3D9_GetStreamSourceFreqT>((void*)vTable[103]);
    D3D9_SetIndices<D3D9_SetIndicesT>::instance = new D3D9_SetIndices<D3D9_SetIndicesT>((void*)vTable[104]);
    D3D9_GetIndices<D3D9_GetIndicesT>::instance = new D3D9_GetIndices<D3D9_GetIndicesT>((void*)vTable[105]);
    D3D9_CreatePixelShader<D3D9_CreatePixelShaderT>::instance = new D3D9_CreatePixelShader<D3D9_CreatePixelShaderT>((void*)vTable[106]);
    D3D9_SetPixelShader<D3D9_SetPixelShaderT>::instance = new D3D9_SetPixelShader<D3D9_SetPixelShaderT>((void*)vTable[107]);
    D3D9_GetPixelShader<D3D9_GetPixelShaderT>::instance = new D3D9_GetPixelShader<D3D9_GetPixelShaderT>((void*)vTable[108]);
    D3D9_SetPixelShaderConstantF<D3D9_SetPixelShaderConstantFT>::instance = new D3D9_SetPixelShaderConstantF<D3D9_SetPixelShaderConstantFT>((void*)vTable[109]);
    D3D9_GetPixelShaderConstantF<D3D9_GetPixelShaderConstantFT>::instance = new D3D9_GetPixelShaderConstantF<D3D9_GetPixelShaderConstantFT>((void*)vTable[110]);
    D3D9_SetPixelShaderConstantI<D3D9_SetPixelShaderConstantIT>::instance = new D3D9_SetPixelShaderConstantI<D3D9_SetPixelShaderConstantIT>((void*)vTable[111]);
    D3D9_GetPixelShaderConstantI<D3D9_GetPixelShaderConstantIT>::instance = new D3D9_GetPixelShaderConstantI<D3D9_GetPixelShaderConstantIT>((void*)vTable[112]);
    D3D9_SetPixelShaderConstantB<D3D9_SetPixelShaderConstantBT>::instance = new D3D9_SetPixelShaderConstantB<D3D9_SetPixelShaderConstantBT>((void*)vTable[113]);
    D3D9_GetPixelShaderConstantB<D3D9_GetPixelShaderConstantBT>::instance = new D3D9_GetPixelShaderConstantB<D3D9_GetPixelShaderConstantBT>((void*)vTable[114]);
    D3D9_DrawRectPatch<D3D9_DrawRectPatchT>::instance = new D3D9_DrawRectPatch<D3D9_DrawRectPatchT>((void*)vTable[115]);
    D3D9_DrawTriPatch<D3D9_DrawTriPatchT>::instance = new D3D9_DrawTriPatch<D3D9_DrawTriPatchT>((void*)vTable[116]);
    D3D9_DeletePatch<D3D9_DeletePatchT>::instance = new D3D9_DeletePatch<D3D9_DeletePatchT>((void*)vTable[117]);
    D3D9_CreateQuery<D3D9_CreateQueryT>::instance = new D3D9_CreateQuery<D3D9_CreateQueryT>((void*)vTable[118]);
}

void D3D9_InjectExtraHooks(std::string name, void* before, void* after)
{

}



#pragma once

// Globals types
typedef void(__stdcall* InstallGraphicHookT)(std::string functionName, void* functionHookBefore, void* functionHookAfter);
InstallGraphicHookT pInstallGraphicHook = nullptr;
typedef void(__stdcall* RemoveGraphicHookT)(std::string functionName);
RemoveGraphicHookT pRemoveGraphicHook = nullptr;

std::vector<void*> GraphicHookFunctionsBefore;
std::vector<void*> GraphicHookFunctionsAfter;
std::vector<std::string> GraphicHookNames;

void __stdcall InstallGraphicHook(std::string functionName, void* functionHookBefore, void* functionHookAfter = nullptr)
{
	bool found = false;
	for (int i = 0; i < GraphicHookNames.size(); i++)
	{
		if (GraphicHookNames[i] == functionName)
		{
			// Update functions
			GraphicHookFunctionsBefore[i] = functionHookBefore;
			GraphicHookFunctionsAfter[i] = functionHookAfter;
			found = true;
			break;
		}
	}

	if (!found)
	{
		// Add new hook
		GraphicHookNames.push_back(functionName);
		GraphicHookFunctionsBefore.push_back(functionHookBefore);
		GraphicHookFunctionsAfter.push_back(functionHookAfter);
	}

	// Update a specific hook
	ThreadHookerSuspendThreads(5);

	if (GlobalSettings.config_graphicdriver == "directx12")
	{

	}
	else if (GlobalSettings.config_graphicdriver == "directx11")
	{

	}
	else if (GlobalSettings.config_graphicdriver == "directx10")
	{

	}
	else if (GlobalSettings.config_graphicdriver == "directx9")
	{
		if (functionName == "QueryInterface")
		{
			D3D9_QueryInterface<D3D9_QueryInterfaceT>::instance->setHookBefore(functionHookBefore);
			D3D9_QueryInterface<D3D9_QueryInterfaceT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_QueryInterface<D3D9_QueryInterfaceT>::instance->install();
		}
		if (functionName == "AddRef")
		{
			D3D9_AddRef<D3D9_AddRefT>::instance->setHookBefore(functionHookBefore);
			D3D9_AddRef<D3D9_AddRefT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_AddRef<D3D9_AddRefT>::instance->install();
		}
		if (functionName == "Release")
		{
			D3D9_Release<D3D9_ReleaseT>::instance->setHookBefore(functionHookBefore);
			D3D9_Release<D3D9_ReleaseT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_Release<D3D9_ReleaseT>::instance->install();
		}
		if (functionName == "TestCooperativeLevel")
		{
			D3D9_TestCooperativeLevel<D3D9_TestCooperativeLevelT>::instance->setHookBefore(functionHookBefore);
			D3D9_TestCooperativeLevel<D3D9_TestCooperativeLevelT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_TestCooperativeLevel<D3D9_TestCooperativeLevelT>::instance->install();
		}
		if (functionName == "GetAvailableTextureMem")
		{
			D3D9_GetAvailableTextureMem<D3D9_GetAvailableTextureMemT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetAvailableTextureMem<D3D9_GetAvailableTextureMemT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetAvailableTextureMem<D3D9_GetAvailableTextureMemT>::instance->install();
		}
		if (functionName == "EvictManagedResources")
		{
			D3D9_EvictManagedResources<D3D9_EvictManagedResourcesT>::instance->setHookBefore(functionHookBefore);
			D3D9_EvictManagedResources<D3D9_EvictManagedResourcesT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_EvictManagedResources<D3D9_EvictManagedResourcesT>::instance->install();
		}
		if (functionName == "GetDirect3D")
		{
			D3D9_GetDirect3D<D3D9_GetDirect3DT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetDirect3D<D3D9_GetDirect3DT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetDirect3D<D3D9_GetDirect3DT>::instance->install();
		}
		if (functionName == "GetDeviceCaps")
		{
			D3D9_GetDeviceCaps<D3D9_GetDeviceCapsT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetDeviceCaps<D3D9_GetDeviceCapsT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetDeviceCaps<D3D9_GetDeviceCapsT>::instance->install();
		}
		if (functionName == "GetDisplayMode")
		{
			D3D9_GetDisplayMode<D3D9_GetDisplayModeT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetDisplayMode<D3D9_GetDisplayModeT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetDisplayMode<D3D9_GetDisplayModeT>::instance->install();
		}
		if (functionName == "GetCreationParameters")
		{
			D3D9_GetCreationParameters<D3D9_GetCreationParametersT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetCreationParameters<D3D9_GetCreationParametersT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetCreationParameters<D3D9_GetCreationParametersT>::instance->install();
		}
		if (functionName == "SetCursorProperties")
		{
			D3D9_SetCursorProperties<D3D9_SetCursorPropertiesT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetCursorProperties<D3D9_SetCursorPropertiesT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetCursorProperties<D3D9_SetCursorPropertiesT>::instance->install();
		}
		if (functionName == "SetCursorPosition")
		{
			D3D9_SetCursorPosition<D3D9_SetCursorPositionT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetCursorPosition<D3D9_SetCursorPositionT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetCursorPosition<D3D9_SetCursorPositionT>::instance->install();
		}
		if (functionName == "ShowCursor")
		{
			D3D9_ShowCursor<D3D9_ShowCursorT>::instance->setHookBefore(functionHookBefore);
			D3D9_ShowCursor<D3D9_ShowCursorT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_ShowCursor<D3D9_ShowCursorT>::instance->install();
		}
		if (functionName == "CreateAdditionalSwapChain")
		{
			D3D9_CreateAdditionalSwapChain<D3D9_CreateAdditionalSwapChainT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateAdditionalSwapChain<D3D9_CreateAdditionalSwapChainT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateAdditionalSwapChain<D3D9_CreateAdditionalSwapChainT>::instance->install();
		}
		if (functionName == "GetSwapChain")
		{
			D3D9_GetSwapChain<D3D9_GetSwapChainT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetSwapChain<D3D9_GetSwapChainT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetSwapChain<D3D9_GetSwapChainT>::instance->install();
		}
		if (functionName == "GetNumberOfSwapChains")
		{
			D3D9_GetNumberOfSwapChains<D3D9_GetNumberOfSwapChainsT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetNumberOfSwapChains<D3D9_GetNumberOfSwapChainsT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetNumberOfSwapChains<D3D9_GetNumberOfSwapChainsT>::instance->install();
		}
		if (functionName == "Reset")
		{
			D3D9_Reset<D3D9_ResetT>::instance->setHookBefore(functionHookBefore);
			D3D9_Reset<D3D9_ResetT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_Reset<D3D9_ResetT>::instance->install();
		}
		if (functionName == "Present")
		{
			D3D9_Present<D3D9_PresentT>::instance->setHookBefore(functionHookBefore);
			D3D9_Present<D3D9_PresentT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_Present<D3D9_PresentT>::instance->install();
		}
		if (functionName == "GetBackBuffer")
		{
			D3D9_GetBackBuffer<D3D9_GetBackBufferT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetBackBuffer<D3D9_GetBackBufferT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetBackBuffer<D3D9_GetBackBufferT>::instance->install();
		}
		if (functionName == "GetRasterStatus")
		{
			D3D9_GetRasterStatus<D3D9_GetRasterStatusT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetRasterStatus<D3D9_GetRasterStatusT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetRasterStatus<D3D9_GetRasterStatusT>::instance->install();
		}
		if (functionName == "SetDialogBoxMode")
		{
			D3D9_SetDialogBoxMode<D3D9_SetDialogBoxModeT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetDialogBoxMode<D3D9_SetDialogBoxModeT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetDialogBoxMode<D3D9_SetDialogBoxModeT>::instance->install();
		}
		if (functionName == "SetGammaRamp")
		{
			D3D9_SetGammaRamp<D3D9_SetGammaRampT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetGammaRamp<D3D9_SetGammaRampT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetGammaRamp<D3D9_SetGammaRampT>::instance->install();
		}
		if (functionName == "GetGammaRamp")
		{
			D3D9_GetGammaRamp<D3D9_GetGammaRampT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetGammaRamp<D3D9_GetGammaRampT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetGammaRamp<D3D9_GetGammaRampT>::instance->install();
		}
		if (functionName == "CreateTexture")
		{
			D3D9_CreateTexture<D3D9_CreateTextureT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateTexture<D3D9_CreateTextureT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateTexture<D3D9_CreateTextureT>::instance->install();
		}
		if (functionName == "CreateVolumeTexture")
		{
			D3D9_CreateVolumeTexture<D3D9_CreateVolumeTextureT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateVolumeTexture<D3D9_CreateVolumeTextureT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateVolumeTexture<D3D9_CreateVolumeTextureT>::instance->install();
		}
		if (functionName == "CreateCubeTexture")
		{
			D3D9_CreateCubeTexture<D3D9_CreateCubeTextureT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateCubeTexture<D3D9_CreateCubeTextureT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateCubeTexture<D3D9_CreateCubeTextureT>::instance->install();
		}
		if (functionName == "CreateVertexBuffer")
		{
			D3D9_CreateVertexBuffer<D3D9_CreateVertexBufferT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateVertexBuffer<D3D9_CreateVertexBufferT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateVertexBuffer<D3D9_CreateVertexBufferT>::instance->install();
		}
		if (functionName == "CreateIndexBuffer")
		{
			D3D9_CreateIndexBuffer<D3D9_CreateIndexBufferT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateIndexBuffer<D3D9_CreateIndexBufferT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateIndexBuffer<D3D9_CreateIndexBufferT>::instance->install();
		}
		if (functionName == "CreateRenderTarget")
		{
			D3D9_CreateRenderTarget<D3D9_CreateRenderTargetT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateRenderTarget<D3D9_CreateRenderTargetT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateRenderTarget<D3D9_CreateRenderTargetT>::instance->install();
		}
		if (functionName == "CreateDepthStencilSurface")
		{
			D3D9_CreateDepthStencilSurface<D3D9_CreateDepthStencilSurfaceT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateDepthStencilSurface<D3D9_CreateDepthStencilSurfaceT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateDepthStencilSurface<D3D9_CreateDepthStencilSurfaceT>::instance->install();
		}
		if (functionName == "UpdateSurface")
		{
			D3D9_UpdateSurface<D3D9_UpdateSurfaceT>::instance->setHookBefore(functionHookBefore);
			D3D9_UpdateSurface<D3D9_UpdateSurfaceT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_UpdateSurface<D3D9_UpdateSurfaceT>::instance->install();
		}
		if (functionName == "UpdateTexture")
		{
			D3D9_UpdateTexture<D3D9_UpdateTextureT>::instance->setHookBefore(functionHookBefore);
			D3D9_UpdateTexture<D3D9_UpdateTextureT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_UpdateTexture<D3D9_UpdateTextureT>::instance->install();
		}
		if (functionName == "GetRenderTargetData")
		{
			D3D9_GetRenderTargetData<D3D9_GetRenderTargetDataT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetRenderTargetData<D3D9_GetRenderTargetDataT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetRenderTargetData<D3D9_GetRenderTargetDataT>::instance->install();
		}
		if (functionName == "GetFrontBufferData")
		{
			D3D9_GetFrontBufferData<D3D9_GetFrontBufferDataT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetFrontBufferData<D3D9_GetFrontBufferDataT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetFrontBufferData<D3D9_GetFrontBufferDataT>::instance->install();
		}
		if (functionName == "StretchRect")
		{
			D3D9_StretchRect<D3D9_StretchRectT>::instance->setHookBefore(functionHookBefore);
			D3D9_StretchRect<D3D9_StretchRectT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_StretchRect<D3D9_StretchRectT>::instance->install();
		}
		if (functionName == "ColorFill")
		{
			D3D9_ColorFill<D3D9_ColorFillT>::instance->setHookBefore(functionHookBefore);
			D3D9_ColorFill<D3D9_ColorFillT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_ColorFill<D3D9_ColorFillT>::instance->install();
		}
		if (functionName == "CreateOffscreenPlainSurface")
		{
			D3D9_CreateOffscreenPlainSurface<D3D9_CreateOffscreenPlainSurfaceT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateOffscreenPlainSurface<D3D9_CreateOffscreenPlainSurfaceT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateOffscreenPlainSurface<D3D9_CreateOffscreenPlainSurfaceT>::instance->install();
		}
		if (functionName == "SetRenderTarget")
		{
			D3D9_SetRenderTarget<D3D9_SetRenderTargetT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetRenderTarget<D3D9_SetRenderTargetT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetRenderTarget<D3D9_SetRenderTargetT>::instance->install();
		}
		if (functionName == "GetRenderTarget")
		{
			D3D9_GetRenderTarget<D3D9_GetRenderTargetT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetRenderTarget<D3D9_GetRenderTargetT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetRenderTarget<D3D9_GetRenderTargetT>::instance->install();
		}
		if (functionName == "SetDepthStencilSurface")
		{
			D3D9_SetDepthStencilSurface<D3D9_SetDepthStencilSurfaceT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetDepthStencilSurface<D3D9_SetDepthStencilSurfaceT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetDepthStencilSurface<D3D9_SetDepthStencilSurfaceT>::instance->install();
		}
		if (functionName == "GetDepthStencilSurface")
		{
			D3D9_GetDepthStencilSurface<D3D9_GetDepthStencilSurfaceT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetDepthStencilSurface<D3D9_GetDepthStencilSurfaceT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetDepthStencilSurface<D3D9_GetDepthStencilSurfaceT>::instance->install();
		}
		if (functionName == "BeginScene")
		{
			D3D9_BeginScene<D3D9_BeginSceneT>::instance->setHookBefore(functionHookBefore);
			D3D9_BeginScene<D3D9_BeginSceneT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_BeginScene<D3D9_BeginSceneT>::instance->install();
		}
		if (functionName == "EndScene")
		{
			D3D9_EndScene<D3D9_EndSceneT>::instance->setHookBefore(functionHookBefore);
			D3D9_EndScene<D3D9_EndSceneT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_EndScene<D3D9_EndSceneT>::instance->install();
		}
		if (functionName == "Clear")
		{
			D3D9_Clear<D3D9_ClearT>::instance->setHookBefore(functionHookBefore);
			D3D9_Clear<D3D9_ClearT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_Clear<D3D9_ClearT>::instance->install();
		}
		if (functionName == "SetTransform")
		{
			D3D9_SetTransform<D3D9_SetTransformT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetTransform<D3D9_SetTransformT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetTransform<D3D9_SetTransformT>::instance->install();
		}
		if (functionName == "GetTransform")
		{
			D3D9_GetTransform<D3D9_GetTransformT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetTransform<D3D9_GetTransformT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetTransform<D3D9_GetTransformT>::instance->install();
		}
		if (functionName == "MultiplyTransform")
		{
			D3D9_MultiplyTransform<D3D9_MultiplyTransformT>::instance->setHookBefore(functionHookBefore);
			D3D9_MultiplyTransform<D3D9_MultiplyTransformT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_MultiplyTransform<D3D9_MultiplyTransformT>::instance->install();
		}
		if (functionName == "SetViewport")
		{
			D3D9_SetViewport<D3D9_SetViewportT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetViewport<D3D9_SetViewportT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetViewport<D3D9_SetViewportT>::instance->install();
		}
		if (functionName == "GetViewport")
		{
			D3D9_GetViewport<D3D9_GetViewportT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetViewport<D3D9_GetViewportT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetViewport<D3D9_GetViewportT>::instance->install();
		}
		if (functionName == "SetMaterial")
		{
			D3D9_SetMaterial<D3D9_SetMaterialT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetMaterial<D3D9_SetMaterialT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetMaterial<D3D9_SetMaterialT>::instance->install();
		}
		if (functionName == "GetMaterial")
		{
			D3D9_GetMaterial<D3D9_GetMaterialT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetMaterial<D3D9_GetMaterialT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetMaterial<D3D9_GetMaterialT>::instance->install();
		}
		if (functionName == "SetLight")
		{
			D3D9_SetLight<D3D9_SetLightT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetLight<D3D9_SetLightT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetLight<D3D9_SetLightT>::instance->install();
		}
		if (functionName == "GetLight")
		{
			D3D9_GetLight<D3D9_GetLightT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetLight<D3D9_GetLightT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetLight<D3D9_GetLightT>::instance->install();
		}
		if (functionName == "LightEnable")
		{
			D3D9_LightEnable<D3D9_LightEnableT>::instance->setHookBefore(functionHookBefore);
			D3D9_LightEnable<D3D9_LightEnableT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_LightEnable<D3D9_LightEnableT>::instance->install();
		}
		if (functionName == "GetLightEnable")
		{
			D3D9_GetLightEnable<D3D9_GetLightEnableT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetLightEnable<D3D9_GetLightEnableT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetLightEnable<D3D9_GetLightEnableT>::instance->install();
		}
		if (functionName == "SetClipPlane")
		{
			D3D9_SetClipPlane<D3D9_SetClipPlaneT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetClipPlane<D3D9_SetClipPlaneT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetClipPlane<D3D9_SetClipPlaneT>::instance->install();
		}
		if (functionName == "GetClipPlane")
		{
			D3D9_GetClipPlane<D3D9_GetClipPlaneT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetClipPlane<D3D9_GetClipPlaneT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetClipPlane<D3D9_GetClipPlaneT>::instance->install();
		}
		if (functionName == "SetRenderState")
		{
			D3D9_SetRenderState<D3D9_SetRenderStateT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetRenderState<D3D9_SetRenderStateT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetRenderState<D3D9_SetRenderStateT>::instance->install();
		}
		if (functionName == "GetRenderState")
		{
			D3D9_GetRenderState<D3D9_GetRenderStateT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetRenderState<D3D9_GetRenderStateT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetRenderState<D3D9_GetRenderStateT>::instance->install();
		}
		if (functionName == "CreateStateBlock")
		{
			D3D9_CreateStateBlock<D3D9_CreateStateBlockT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateStateBlock<D3D9_CreateStateBlockT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateStateBlock<D3D9_CreateStateBlockT>::instance->install();
		}
		if (functionName == "BeginStateBlock")
		{
			D3D9_BeginStateBlock<D3D9_BeginStateBlockT>::instance->setHookBefore(functionHookBefore);
			D3D9_BeginStateBlock<D3D9_BeginStateBlockT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_BeginStateBlock<D3D9_BeginStateBlockT>::instance->install();
		}
		if (functionName == "EndStateBlock")
		{
			D3D9_EndStateBlock<D3D9_EndStateBlockT>::instance->setHookBefore(functionHookBefore);
			D3D9_EndStateBlock<D3D9_EndStateBlockT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_EndStateBlock<D3D9_EndStateBlockT>::instance->install();
		}
		if (functionName == "SetClipStatus")
		{
			D3D9_SetClipStatus<D3D9_SetClipStatusT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetClipStatus<D3D9_SetClipStatusT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetClipStatus<D3D9_SetClipStatusT>::instance->install();
		}
		if (functionName == "GetClipStatus")
		{
			D3D9_GetClipStatus<D3D9_GetClipStatusT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetClipStatus<D3D9_GetClipStatusT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetClipStatus<D3D9_GetClipStatusT>::instance->install();
		}
		if (functionName == "GetTexture")
		{
			D3D9_GetTexture<D3D9_GetTextureT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetTexture<D3D9_GetTextureT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetTexture<D3D9_GetTextureT>::instance->install();
		}
		if (functionName == "SetTexture")
		{
			D3D9_SetTexture<D3D9_SetTextureT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetTexture<D3D9_SetTextureT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetTexture<D3D9_SetTextureT>::instance->install();
		}
		if (functionName == "GetTextureStageState")
		{
			D3D9_GetTextureStageState<D3D9_GetTextureStageStateT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetTextureStageState<D3D9_GetTextureStageStateT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetTextureStageState<D3D9_GetTextureStageStateT>::instance->install();
		}
		if (functionName == "SetTextureStageState")
		{
			D3D9_SetTextureStageState<D3D9_SetTextureStageStateT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetTextureStageState<D3D9_SetTextureStageStateT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetTextureStageState<D3D9_SetTextureStageStateT>::instance->install();
		}
		if (functionName == "GetSamplerState")
		{
			D3D9_GetSamplerState<D3D9_GetSamplerStateT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetSamplerState<D3D9_GetSamplerStateT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetSamplerState<D3D9_GetSamplerStateT>::instance->install();
		}
		if (functionName == "SetSamplerState")
		{
			D3D9_SetSamplerState<D3D9_SetSamplerStateT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetSamplerState<D3D9_SetSamplerStateT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetSamplerState<D3D9_SetSamplerStateT>::instance->install();
		}
		if (functionName == "ValidateDevice")
		{
			D3D9_ValidateDevice<D3D9_ValidateDeviceT>::instance->setHookBefore(functionHookBefore);
			D3D9_ValidateDevice<D3D9_ValidateDeviceT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_ValidateDevice<D3D9_ValidateDeviceT>::instance->install();
		}
		if (functionName == "SetPaletteEntries")
		{
			D3D9_SetPaletteEntries<D3D9_SetPaletteEntriesT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetPaletteEntries<D3D9_SetPaletteEntriesT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetPaletteEntries<D3D9_SetPaletteEntriesT>::instance->install();
		}
		if (functionName == "GetPaletteEntries")
		{
			D3D9_GetPaletteEntries<D3D9_GetPaletteEntriesT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetPaletteEntries<D3D9_GetPaletteEntriesT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetPaletteEntries<D3D9_GetPaletteEntriesT>::instance->install();
		}
		if (functionName == "SetCurrentTexturePalette")
		{
			D3D9_SetCurrentTexturePalette<D3D9_SetCurrentTexturePaletteT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetCurrentTexturePalette<D3D9_SetCurrentTexturePaletteT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetCurrentTexturePalette<D3D9_SetCurrentTexturePaletteT>::instance->install();
		}
		if (functionName == "GetCurrentTexturePalette")
		{
			D3D9_GetCurrentTexturePalette<D3D9_GetCurrentTexturePaletteT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetCurrentTexturePalette<D3D9_GetCurrentTexturePaletteT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetCurrentTexturePalette<D3D9_GetCurrentTexturePaletteT>::instance->install();
		}
		if (functionName == "SetScissorRect")
		{
			D3D9_SetScissorRect<D3D9_SetScissorRectT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetScissorRect<D3D9_SetScissorRectT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetScissorRect<D3D9_SetScissorRectT>::instance->install();
		}
		if (functionName == "GetScissorRect")
		{
			D3D9_GetScissorRect<D3D9_GetScissorRectT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetScissorRect<D3D9_GetScissorRectT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetScissorRect<D3D9_GetScissorRectT>::instance->install();
		}
		if (functionName == "SetSoftwareVertexProcessing")
		{
			D3D9_SetSoftwareVertexProcessing<D3D9_SetSoftwareVertexProcessingT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetSoftwareVertexProcessing<D3D9_SetSoftwareVertexProcessingT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetSoftwareVertexProcessing<D3D9_SetSoftwareVertexProcessingT>::instance->install();
		}
		if (functionName == "GetSoftwareVertexProcessing")
		{
			D3D9_GetSoftwareVertexProcessing<D3D9_GetSoftwareVertexProcessingT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetSoftwareVertexProcessing<D3D9_GetSoftwareVertexProcessingT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetSoftwareVertexProcessing<D3D9_GetSoftwareVertexProcessingT>::instance->install();
		}
		if (functionName == "SetNPatchMode")
		{
			D3D9_SetNPatchMode<D3D9_SetNPatchModeT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetNPatchMode<D3D9_SetNPatchModeT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetNPatchMode<D3D9_SetNPatchModeT>::instance->install();
		}
		if (functionName == "GetNPatchMode")
		{
			D3D9_GetNPatchMode<D3D9_GetNPatchModeT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetNPatchMode<D3D9_GetNPatchModeT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetNPatchMode<D3D9_GetNPatchModeT>::instance->install();
		}
		if (functionName == "DrawPrimitive")
		{
			D3D9_DrawPrimitive<D3D9_DrawPrimitiveT>::instance->setHookBefore(functionHookBefore);
			D3D9_DrawPrimitive<D3D9_DrawPrimitiveT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_DrawPrimitive<D3D9_DrawPrimitiveT>::instance->install();
		}
		if (functionName == "DrawIndexedPrimitive")
		{
			D3D9_DrawIndexedPrimitive<D3D9_DrawIndexedPrimitiveT>::instance->setHookBefore(functionHookBefore);
			D3D9_DrawIndexedPrimitive<D3D9_DrawIndexedPrimitiveT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_DrawIndexedPrimitive<D3D9_DrawIndexedPrimitiveT>::instance->install();
		}
		if (functionName == "DrawPrimitiveUP")
		{
			D3D9_DrawPrimitiveUP<D3D9_DrawPrimitiveUPT>::instance->setHookBefore(functionHookBefore);
			D3D9_DrawPrimitiveUP<D3D9_DrawPrimitiveUPT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_DrawPrimitiveUP<D3D9_DrawPrimitiveUPT>::instance->install();
		}
		if (functionName == "DrawIndexedPrimitiveUP")
		{
			D3D9_DrawIndexedPrimitiveUP<D3D9_DrawIndexedPrimitiveUPT>::instance->setHookBefore(functionHookBefore);
			D3D9_DrawIndexedPrimitiveUP<D3D9_DrawIndexedPrimitiveUPT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_DrawIndexedPrimitiveUP<D3D9_DrawIndexedPrimitiveUPT>::instance->install();
		}
		if (functionName == "ProcessVertices")
		{
			D3D9_ProcessVertices<D3D9_ProcessVerticesT>::instance->setHookBefore(functionHookBefore);
			D3D9_ProcessVertices<D3D9_ProcessVerticesT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_ProcessVertices<D3D9_ProcessVerticesT>::instance->install();
		}
		if (functionName == "CreateVertexDeclaration")
		{
			D3D9_CreateVertexDeclaration<D3D9_CreateVertexDeclarationT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateVertexDeclaration<D3D9_CreateVertexDeclarationT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateVertexDeclaration<D3D9_CreateVertexDeclarationT>::instance->install();
		}
		if (functionName == "SetVertexDeclaration")
		{
			D3D9_SetVertexDeclaration<D3D9_SetVertexDeclarationT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetVertexDeclaration<D3D9_SetVertexDeclarationT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetVertexDeclaration<D3D9_SetVertexDeclarationT>::instance->install();
		}
		if (functionName == "GetVertexDeclaration")
		{
			D3D9_GetVertexDeclaration<D3D9_GetVertexDeclarationT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetVertexDeclaration<D3D9_GetVertexDeclarationT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetVertexDeclaration<D3D9_GetVertexDeclarationT>::instance->install();
		}
		if (functionName == "SetFVF")
		{
			D3D9_SetFVF<D3D9_SetFVFT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetFVF<D3D9_SetFVFT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetFVF<D3D9_SetFVFT>::instance->install();
		}
		if (functionName == "GetFVF")
		{
			D3D9_GetFVF<D3D9_GetFVFT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetFVF<D3D9_GetFVFT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetFVF<D3D9_GetFVFT>::instance->install();
		}
		if (functionName == "CreateVertexShader")
		{
			D3D9_CreateVertexShader<D3D9_CreateVertexShaderT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateVertexShader<D3D9_CreateVertexShaderT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateVertexShader<D3D9_CreateVertexShaderT>::instance->install();
		}
		if (functionName == "SetVertexShader")
		{
			D3D9_SetVertexShader<D3D9_SetVertexShaderT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetVertexShader<D3D9_SetVertexShaderT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetVertexShader<D3D9_SetVertexShaderT>::instance->install();
		}
		if (functionName == "GetVertexShader")
		{
			D3D9_GetVertexShader<D3D9_GetVertexShaderT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetVertexShader<D3D9_GetVertexShaderT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetVertexShader<D3D9_GetVertexShaderT>::instance->install();
		}
		if (functionName == "SetVertexShaderConstantF")
		{
			D3D9_SetVertexShaderConstantF<D3D9_SetVertexShaderConstantFT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetVertexShaderConstantF<D3D9_SetVertexShaderConstantFT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetVertexShaderConstantF<D3D9_SetVertexShaderConstantFT>::instance->install();
		}
		if (functionName == "GetVertexShaderConstantF")
		{
			D3D9_GetVertexShaderConstantF<D3D9_GetVertexShaderConstantFT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetVertexShaderConstantF<D3D9_GetVertexShaderConstantFT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetVertexShaderConstantF<D3D9_GetVertexShaderConstantFT>::instance->install();
		}
		if (functionName == "SetVertexShaderConstantI")
		{
			D3D9_SetVertexShaderConstantI<D3D9_SetVertexShaderConstantIT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetVertexShaderConstantI<D3D9_SetVertexShaderConstantIT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetVertexShaderConstantI<D3D9_SetVertexShaderConstantIT>::instance->install();
		}
		if (functionName == "GetVertexShaderConstantI")
		{
			D3D9_GetVertexShaderConstantI<D3D9_GetVertexShaderConstantIT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetVertexShaderConstantI<D3D9_GetVertexShaderConstantIT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetVertexShaderConstantI<D3D9_GetVertexShaderConstantIT>::instance->install();
		}
		if (functionName == "SetVertexShaderConstantB")
		{
			D3D9_SetVertexShaderConstantB<D3D9_SetVertexShaderConstantBT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetVertexShaderConstantB<D3D9_SetVertexShaderConstantBT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetVertexShaderConstantB<D3D9_SetVertexShaderConstantBT>::instance->install();
		}
		if (functionName == "GetVertexShaderConstantB")
		{
			D3D9_GetVertexShaderConstantB<D3D9_GetVertexShaderConstantBT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetVertexShaderConstantB<D3D9_GetVertexShaderConstantBT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetVertexShaderConstantB<D3D9_GetVertexShaderConstantBT>::instance->install();
		}
		if (functionName == "SetStreamSource")
		{
			D3D9_SetStreamSource<D3D9_SetStreamSourceT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetStreamSource<D3D9_SetStreamSourceT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetStreamSource<D3D9_SetStreamSourceT>::instance->install();
		}
		if (functionName == "GetStreamSource")
		{
			D3D9_GetStreamSource<D3D9_GetStreamSourceT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetStreamSource<D3D9_GetStreamSourceT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetStreamSource<D3D9_GetStreamSourceT>::instance->install();
		}
		if (functionName == "SetStreamSourceFreq")
		{
			D3D9_SetStreamSourceFreq<D3D9_SetStreamSourceFreqT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetStreamSourceFreq<D3D9_SetStreamSourceFreqT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetStreamSourceFreq<D3D9_SetStreamSourceFreqT>::instance->install();
		}
		if (functionName == "GetStreamSourceFreq")
		{
			D3D9_GetStreamSourceFreq<D3D9_GetStreamSourceFreqT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetStreamSourceFreq<D3D9_GetStreamSourceFreqT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetStreamSourceFreq<D3D9_GetStreamSourceFreqT>::instance->install();
		}
		if (functionName == "SetIndices")
		{
			D3D9_SetIndices<D3D9_SetIndicesT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetIndices<D3D9_SetIndicesT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetIndices<D3D9_SetIndicesT>::instance->install();
		}
		if (functionName == "GetIndices")
		{
			D3D9_GetIndices<D3D9_GetIndicesT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetIndices<D3D9_GetIndicesT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetIndices<D3D9_GetIndicesT>::instance->install();
		}
		if (functionName == "CreatePixelShader")
		{
			D3D9_CreatePixelShader<D3D9_CreatePixelShaderT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreatePixelShader<D3D9_CreatePixelShaderT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreatePixelShader<D3D9_CreatePixelShaderT>::instance->install();
		}
		if (functionName == "SetPixelShader")
		{
			D3D9_SetPixelShader<D3D9_SetPixelShaderT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetPixelShader<D3D9_SetPixelShaderT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetPixelShader<D3D9_SetPixelShaderT>::instance->install();
		}
		if (functionName == "GetPixelShader")
		{
			D3D9_GetPixelShader<D3D9_GetPixelShaderT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetPixelShader<D3D9_GetPixelShaderT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetPixelShader<D3D9_GetPixelShaderT>::instance->install();
		}
		if (functionName == "SetPixelShaderConstantF")
		{
			D3D9_SetPixelShaderConstantF<D3D9_SetPixelShaderConstantFT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetPixelShaderConstantF<D3D9_SetPixelShaderConstantFT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetPixelShaderConstantF<D3D9_SetPixelShaderConstantFT>::instance->install();
		}
		if (functionName == "GetPixelShaderConstantF")
		{
			D3D9_GetPixelShaderConstantF<D3D9_GetPixelShaderConstantFT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetPixelShaderConstantF<D3D9_GetPixelShaderConstantFT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetPixelShaderConstantF<D3D9_GetPixelShaderConstantFT>::instance->install();
		}
		if (functionName == "SetPixelShaderConstantI")
		{
			D3D9_SetPixelShaderConstantI<D3D9_SetPixelShaderConstantIT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetPixelShaderConstantI<D3D9_SetPixelShaderConstantIT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetPixelShaderConstantI<D3D9_SetPixelShaderConstantIT>::instance->install();
		}
		if (functionName == "GetPixelShaderConstantI")
		{
			D3D9_GetPixelShaderConstantI<D3D9_GetPixelShaderConstantIT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetPixelShaderConstantI<D3D9_GetPixelShaderConstantIT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetPixelShaderConstantI<D3D9_GetPixelShaderConstantIT>::instance->install();
		}
		if (functionName == "SetPixelShaderConstantB")
		{
			D3D9_SetPixelShaderConstantB<D3D9_SetPixelShaderConstantBT>::instance->setHookBefore(functionHookBefore);
			D3D9_SetPixelShaderConstantB<D3D9_SetPixelShaderConstantBT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_SetPixelShaderConstantB<D3D9_SetPixelShaderConstantBT>::instance->install();
		}
		if (functionName == "GetPixelShaderConstantB")
		{
			D3D9_GetPixelShaderConstantB<D3D9_GetPixelShaderConstantBT>::instance->setHookBefore(functionHookBefore);
			D3D9_GetPixelShaderConstantB<D3D9_GetPixelShaderConstantBT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_GetPixelShaderConstantB<D3D9_GetPixelShaderConstantBT>::instance->install();
		}
		if (functionName == "DrawRectPatch")
		{
			D3D9_DrawRectPatch<D3D9_DrawRectPatchT>::instance->setHookBefore(functionHookBefore);
			D3D9_DrawRectPatch<D3D9_DrawRectPatchT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_DrawRectPatch<D3D9_DrawRectPatchT>::instance->install();
		}
		if (functionName == "DrawTriPatch")
		{
			D3D9_DrawTriPatch<D3D9_DrawTriPatchT>::instance->setHookBefore(functionHookBefore);
			D3D9_DrawTriPatch<D3D9_DrawTriPatchT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_DrawTriPatch<D3D9_DrawTriPatchT>::instance->install();
		}
		if (functionName == "DeletePatch")
		{
			D3D9_DeletePatch<D3D9_DeletePatchT>::instance->setHookBefore(functionHookBefore);
			D3D9_DeletePatch<D3D9_DeletePatchT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_DeletePatch<D3D9_DeletePatchT>::instance->install();
		}
		if (functionName == "CreateQuery")
		{
			D3D9_CreateQuery<D3D9_CreateQueryT>::instance->setHookBefore(functionHookBefore);
			D3D9_CreateQuery<D3D9_CreateQueryT>::instance->setHookAfter(functionHookAfter);
			if (!found) D3D9_CreateQuery<D3D9_CreateQueryT>::instance->install();
		}
	}

	ThreadHookerResumeThreads(5);
}

void __stdcall RemoveGraphicHook(std::string functionName)
{
	bool found = false;
	int updateIndex = 0;
	for (int i = 0; i < GraphicHookNames.size(); i++)
	{
		if (GraphicHookNames[i] == functionName)
		{
			// Target hook
			found = true;
			updateIndex = i;
			break;
		}
	}

	if (found)
	{
		// Remove hook
		while (true)
		{
			// Probably add mutex in future?
			// std::lock_guard<std::mutex> lock(GraphicsHookMutex);

			ThreadHookerSuspendThreads(5);

			bool deactivate = true;

			if (GlobalSettings.config_graphicdriver == "directx12")
			{

			}
			else if (GlobalSettings.config_graphicdriver == "directx11")
			{

			}
			else if (GlobalSettings.config_graphicdriver == "directx10")
			{

			}
			else if (GlobalSettings.config_graphicdriver == "directx9")
			{
				if (functionName == "QueryInterface" && D3D9_QueryInterface<D3D9_QueryInterfaceT>::instance->isInstalled())
				{
					D3D9_QueryInterface<D3D9_QueryInterfaceT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "AddRef" && D3D9_AddRef<D3D9_AddRefT>::instance->isInstalled())
				{
					D3D9_AddRef<D3D9_AddRefT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "Release" && D3D9_Release<D3D9_ReleaseT>::instance->isInstalled())
				{
					D3D9_Release<D3D9_ReleaseT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "TestCooperativeLevel" && D3D9_TestCooperativeLevel<D3D9_TestCooperativeLevelT>::instance->isInstalled())
				{
					D3D9_TestCooperativeLevel<D3D9_TestCooperativeLevelT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetAvailableTextureMem" && D3D9_GetAvailableTextureMem<D3D9_GetAvailableTextureMemT>::instance->isInstalled())
				{
					D3D9_GetAvailableTextureMem<D3D9_GetAvailableTextureMemT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "EvictManagedResources" && D3D9_EvictManagedResources<D3D9_EvictManagedResourcesT>::instance->isInstalled())
				{
					D3D9_EvictManagedResources<D3D9_EvictManagedResourcesT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetDirect3D" && D3D9_GetDirect3D<D3D9_GetDirect3DT>::instance->isInstalled())
				{
					D3D9_GetDirect3D<D3D9_GetDirect3DT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetDeviceCaps" && D3D9_GetDeviceCaps<D3D9_GetDeviceCapsT>::instance->isInstalled())
				{
					D3D9_GetDeviceCaps<D3D9_GetDeviceCapsT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetDisplayMode" && D3D9_GetDisplayMode<D3D9_GetDisplayModeT>::instance->isInstalled())
				{
					D3D9_GetDisplayMode<D3D9_GetDisplayModeT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetCreationParameters" && D3D9_GetCreationParameters<D3D9_GetCreationParametersT>::instance->isInstalled())
				{
					D3D9_GetCreationParameters<D3D9_GetCreationParametersT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetCursorProperties" && D3D9_SetCursorProperties<D3D9_SetCursorPropertiesT>::instance->isInstalled())
				{
					D3D9_SetCursorProperties<D3D9_SetCursorPropertiesT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetCursorPosition" && D3D9_SetCursorPosition<D3D9_SetCursorPositionT>::instance->isInstalled())
				{
					D3D9_SetCursorPosition<D3D9_SetCursorPositionT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "ShowCursor" && D3D9_ShowCursor<D3D9_ShowCursorT>::instance->isInstalled())
				{
					D3D9_ShowCursor<D3D9_ShowCursorT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateAdditionalSwapChain" && D3D9_CreateAdditionalSwapChain<D3D9_CreateAdditionalSwapChainT>::instance->isInstalled())
				{
					D3D9_CreateAdditionalSwapChain<D3D9_CreateAdditionalSwapChainT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetSwapChain" && D3D9_GetSwapChain<D3D9_GetSwapChainT>::instance->isInstalled())
				{
					D3D9_GetSwapChain<D3D9_GetSwapChainT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetNumberOfSwapChains" && D3D9_GetNumberOfSwapChains<D3D9_GetNumberOfSwapChainsT>::instance->isInstalled())
				{
					D3D9_GetNumberOfSwapChains<D3D9_GetNumberOfSwapChainsT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "Reset" && D3D9_Reset<D3D9_ResetT>::instance->isInstalled())
				{
					D3D9_Reset<D3D9_ResetT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "Present" && D3D9_Present<D3D9_PresentT>::instance->isInstalled())
				{
					D3D9_Present<D3D9_PresentT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetBackBuffer" && D3D9_GetBackBuffer<D3D9_GetBackBufferT>::instance->isInstalled())
				{
					D3D9_GetBackBuffer<D3D9_GetBackBufferT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetRasterStatus" && D3D9_GetRasterStatus<D3D9_GetRasterStatusT>::instance->isInstalled())
				{
					D3D9_GetRasterStatus<D3D9_GetRasterStatusT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetDialogBoxMode" && D3D9_SetDialogBoxMode<D3D9_SetDialogBoxModeT>::instance->isInstalled())
				{
					D3D9_SetDialogBoxMode<D3D9_SetDialogBoxModeT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetGammaRamp" && D3D9_SetGammaRamp<D3D9_SetGammaRampT>::instance->isInstalled())
				{
					D3D9_SetGammaRamp<D3D9_SetGammaRampT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetGammaRamp" && D3D9_GetGammaRamp<D3D9_GetGammaRampT>::instance->isInstalled())
				{
					D3D9_GetGammaRamp<D3D9_GetGammaRampT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateTexture" && D3D9_CreateTexture<D3D9_CreateTextureT>::instance->isInstalled())
				{
					D3D9_CreateTexture<D3D9_CreateTextureT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateVolumeTexture" && D3D9_CreateVolumeTexture<D3D9_CreateVolumeTextureT>::instance->isInstalled())
				{
					D3D9_CreateVolumeTexture<D3D9_CreateVolumeTextureT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateCubeTexture" && D3D9_CreateCubeTexture<D3D9_CreateCubeTextureT>::instance->isInstalled())
				{
					D3D9_CreateCubeTexture<D3D9_CreateCubeTextureT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateVertexBuffer" && D3D9_CreateVertexBuffer<D3D9_CreateVertexBufferT>::instance->isInstalled())
				{
					D3D9_CreateVertexBuffer<D3D9_CreateVertexBufferT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateIndexBuffer" && D3D9_CreateIndexBuffer<D3D9_CreateIndexBufferT>::instance->isInstalled())
				{
					D3D9_CreateIndexBuffer<D3D9_CreateIndexBufferT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateRenderTarget" && D3D9_CreateRenderTarget<D3D9_CreateRenderTargetT>::instance->isInstalled())
				{
					D3D9_CreateRenderTarget<D3D9_CreateRenderTargetT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateDepthStencilSurface" && D3D9_CreateDepthStencilSurface<D3D9_CreateDepthStencilSurfaceT>::instance->isInstalled())
				{
					D3D9_CreateDepthStencilSurface<D3D9_CreateDepthStencilSurfaceT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "UpdateSurface" && D3D9_UpdateSurface<D3D9_UpdateSurfaceT>::instance->isInstalled())
				{
					D3D9_UpdateSurface<D3D9_UpdateSurfaceT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "UpdateTexture" && D3D9_UpdateTexture<D3D9_UpdateTextureT>::instance->isInstalled())
				{
					D3D9_UpdateTexture<D3D9_UpdateTextureT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetRenderTargetData" && D3D9_GetRenderTargetData<D3D9_GetRenderTargetDataT>::instance->isInstalled())
				{
					D3D9_GetRenderTargetData<D3D9_GetRenderTargetDataT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetFrontBufferData" && D3D9_GetFrontBufferData<D3D9_GetFrontBufferDataT>::instance->isInstalled())
				{
					D3D9_GetFrontBufferData<D3D9_GetFrontBufferDataT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "StretchRect" && D3D9_StretchRect<D3D9_StretchRectT>::instance->isInstalled())
				{
					D3D9_StretchRect<D3D9_StretchRectT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "ColorFill" && D3D9_ColorFill<D3D9_ColorFillT>::instance->isInstalled())
				{
					D3D9_ColorFill<D3D9_ColorFillT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateOffscreenPlainSurface" && D3D9_CreateOffscreenPlainSurface<D3D9_CreateOffscreenPlainSurfaceT>::instance->isInstalled())
				{
					D3D9_CreateOffscreenPlainSurface<D3D9_CreateOffscreenPlainSurfaceT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetRenderTarget" && D3D9_SetRenderTarget<D3D9_SetRenderTargetT>::instance->isInstalled())
				{
					D3D9_SetRenderTarget<D3D9_SetRenderTargetT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetRenderTarget" && D3D9_GetRenderTarget<D3D9_GetRenderTargetT>::instance->isInstalled())
				{
					D3D9_GetRenderTarget<D3D9_GetRenderTargetT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetDepthStencilSurface" && D3D9_SetDepthStencilSurface<D3D9_SetDepthStencilSurfaceT>::instance->isInstalled())
				{
					D3D9_SetDepthStencilSurface<D3D9_SetDepthStencilSurfaceT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetDepthStencilSurface" && D3D9_GetDepthStencilSurface<D3D9_GetDepthStencilSurfaceT>::instance->isInstalled())
				{
					D3D9_GetDepthStencilSurface<D3D9_GetDepthStencilSurfaceT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "BeginScene" && D3D9_BeginScene<D3D9_BeginSceneT>::instance->isInstalled())
				{
					D3D9_BeginScene<D3D9_BeginSceneT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "EndScene" && D3D9_EndScene<D3D9_EndSceneT>::instance->isInstalled())
				{
					D3D9_EndScene<D3D9_EndSceneT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "Clear" && D3D9_Clear<D3D9_ClearT>::instance->isInstalled())
				{
					D3D9_Clear<D3D9_ClearT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetTransform" && D3D9_SetTransform<D3D9_SetTransformT>::instance->isInstalled())
				{
					D3D9_SetTransform<D3D9_SetTransformT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetTransform" && D3D9_GetTransform<D3D9_GetTransformT>::instance->isInstalled())
				{
					D3D9_GetTransform<D3D9_GetTransformT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "MultiplyTransform" && D3D9_MultiplyTransform<D3D9_MultiplyTransformT>::instance->isInstalled())
				{
					D3D9_MultiplyTransform<D3D9_MultiplyTransformT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetViewport" && D3D9_SetViewport<D3D9_SetViewportT>::instance->isInstalled())
				{
					D3D9_SetViewport<D3D9_SetViewportT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetViewport" && D3D9_GetViewport<D3D9_GetViewportT>::instance->isInstalled())
				{
					D3D9_GetViewport<D3D9_GetViewportT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetMaterial" && D3D9_SetMaterial<D3D9_SetMaterialT>::instance->isInstalled())
				{
					D3D9_SetMaterial<D3D9_SetMaterialT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetMaterial" && D3D9_GetMaterial<D3D9_GetMaterialT>::instance->isInstalled())
				{
					D3D9_GetMaterial<D3D9_GetMaterialT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetLight" && D3D9_SetLight<D3D9_SetLightT>::instance->isInstalled())
				{
					D3D9_SetLight<D3D9_SetLightT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetLight" && D3D9_GetLight<D3D9_GetLightT>::instance->isInstalled())
				{
					D3D9_GetLight<D3D9_GetLightT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "LightEnable" && D3D9_LightEnable<D3D9_LightEnableT>::instance->isInstalled())
				{
					D3D9_LightEnable<D3D9_LightEnableT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetLightEnable" && D3D9_GetLightEnable<D3D9_GetLightEnableT>::instance->isInstalled())
				{
					D3D9_GetLightEnable<D3D9_GetLightEnableT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetClipPlane" && D3D9_SetClipPlane<D3D9_SetClipPlaneT>::instance->isInstalled())
				{
					D3D9_SetClipPlane<D3D9_SetClipPlaneT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetClipPlane" && D3D9_GetClipPlane<D3D9_GetClipPlaneT>::instance->isInstalled())
				{
					D3D9_GetClipPlane<D3D9_GetClipPlaneT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetRenderState" && D3D9_SetRenderState<D3D9_SetRenderStateT>::instance->isInstalled())
				{
					D3D9_SetRenderState<D3D9_SetRenderStateT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetRenderState" && D3D9_GetRenderState<D3D9_GetRenderStateT>::instance->isInstalled())
				{
					D3D9_GetRenderState<D3D9_GetRenderStateT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateStateBlock" && D3D9_CreateStateBlock<D3D9_CreateStateBlockT>::instance->isInstalled())
				{
					D3D9_CreateStateBlock<D3D9_CreateStateBlockT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "BeginStateBlock" && D3D9_BeginStateBlock<D3D9_BeginStateBlockT>::instance->isInstalled())
				{
					D3D9_BeginStateBlock<D3D9_BeginStateBlockT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "EndStateBlock" && D3D9_EndStateBlock<D3D9_EndStateBlockT>::instance->isInstalled())
				{
					D3D9_EndStateBlock<D3D9_EndStateBlockT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetClipStatus" && D3D9_SetClipStatus<D3D9_SetClipStatusT>::instance->isInstalled())
				{
					D3D9_SetClipStatus<D3D9_SetClipStatusT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetClipStatus" && D3D9_GetClipStatus<D3D9_GetClipStatusT>::instance->isInstalled())
				{
					D3D9_GetClipStatus<D3D9_GetClipStatusT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetTexture" && D3D9_GetTexture<D3D9_GetTextureT>::instance->isInstalled())
				{
					D3D9_GetTexture<D3D9_GetTextureT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetTexture" && D3D9_SetTexture<D3D9_SetTextureT>::instance->isInstalled())
				{
					D3D9_SetTexture<D3D9_SetTextureT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetTextureStageState" && D3D9_GetTextureStageState<D3D9_GetTextureStageStateT>::instance->isInstalled())
				{
					D3D9_GetTextureStageState<D3D9_GetTextureStageStateT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetTextureStageState" && D3D9_SetTextureStageState<D3D9_SetTextureStageStateT>::instance->isInstalled())
				{
					D3D9_SetTextureStageState<D3D9_SetTextureStageStateT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetSamplerState" && D3D9_GetSamplerState<D3D9_GetSamplerStateT>::instance->isInstalled())
				{
					D3D9_GetSamplerState<D3D9_GetSamplerStateT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetSamplerState" && D3D9_SetSamplerState<D3D9_SetSamplerStateT>::instance->isInstalled())
				{
					D3D9_SetSamplerState<D3D9_SetSamplerStateT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "ValidateDevice" && D3D9_ValidateDevice<D3D9_ValidateDeviceT>::instance->isInstalled())
				{
					D3D9_ValidateDevice<D3D9_ValidateDeviceT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetPaletteEntries" && D3D9_SetPaletteEntries<D3D9_SetPaletteEntriesT>::instance->isInstalled())
				{
					D3D9_SetPaletteEntries<D3D9_SetPaletteEntriesT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetPaletteEntries" && D3D9_GetPaletteEntries<D3D9_GetPaletteEntriesT>::instance->isInstalled())
				{
					D3D9_GetPaletteEntries<D3D9_GetPaletteEntriesT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetCurrentTexturePalette" && D3D9_SetCurrentTexturePalette<D3D9_SetCurrentTexturePaletteT>::instance->isInstalled())
				{
					D3D9_SetCurrentTexturePalette<D3D9_SetCurrentTexturePaletteT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetCurrentTexturePalette" && D3D9_GetCurrentTexturePalette<D3D9_GetCurrentTexturePaletteT>::instance->isInstalled())
				{
					D3D9_GetCurrentTexturePalette<D3D9_GetCurrentTexturePaletteT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetScissorRect" && D3D9_SetScissorRect<D3D9_SetScissorRectT>::instance->isInstalled())
				{
					D3D9_SetScissorRect<D3D9_SetScissorRectT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetScissorRect" && D3D9_GetScissorRect<D3D9_GetScissorRectT>::instance->isInstalled())
				{
					D3D9_GetScissorRect<D3D9_GetScissorRectT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetSoftwareVertexProcessing" && D3D9_SetSoftwareVertexProcessing<D3D9_SetSoftwareVertexProcessingT>::instance->isInstalled())
				{
					D3D9_SetSoftwareVertexProcessing<D3D9_SetSoftwareVertexProcessingT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetSoftwareVertexProcessing" && D3D9_GetSoftwareVertexProcessing<D3D9_GetSoftwareVertexProcessingT>::instance->isInstalled())
				{
					D3D9_GetSoftwareVertexProcessing<D3D9_GetSoftwareVertexProcessingT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetNPatchMode" && D3D9_SetNPatchMode<D3D9_SetNPatchModeT>::instance->isInstalled())
				{
					D3D9_SetNPatchMode<D3D9_SetNPatchModeT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetNPatchMode" && D3D9_GetNPatchMode<D3D9_GetNPatchModeT>::instance->isInstalled())
				{
					D3D9_GetNPatchMode<D3D9_GetNPatchModeT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "DrawPrimitive" && D3D9_DrawPrimitive<D3D9_DrawPrimitiveT>::instance->isInstalled())
				{
					D3D9_DrawPrimitive<D3D9_DrawPrimitiveT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "DrawIndexedPrimitive" && D3D9_DrawIndexedPrimitive<D3D9_DrawIndexedPrimitiveT>::instance->isInstalled())
				{
					D3D9_DrawIndexedPrimitive<D3D9_DrawIndexedPrimitiveT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "DrawPrimitiveUP" && D3D9_DrawPrimitiveUP<D3D9_DrawPrimitiveUPT>::instance->isInstalled())
				{
					D3D9_DrawPrimitiveUP<D3D9_DrawPrimitiveUPT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "DrawIndexedPrimitiveUP" && D3D9_DrawIndexedPrimitiveUP<D3D9_DrawIndexedPrimitiveUPT>::instance->isInstalled())
				{
					D3D9_DrawIndexedPrimitiveUP<D3D9_DrawIndexedPrimitiveUPT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "ProcessVertices" && D3D9_ProcessVertices<D3D9_ProcessVerticesT>::instance->isInstalled())
				{
					D3D9_ProcessVertices<D3D9_ProcessVerticesT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateVertexDeclaration" && D3D9_CreateVertexDeclaration<D3D9_CreateVertexDeclarationT>::instance->isInstalled())
				{
					D3D9_CreateVertexDeclaration<D3D9_CreateVertexDeclarationT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetVertexDeclaration" && D3D9_SetVertexDeclaration<D3D9_SetVertexDeclarationT>::instance->isInstalled())
				{
					D3D9_SetVertexDeclaration<D3D9_SetVertexDeclarationT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetVertexDeclaration" && D3D9_GetVertexDeclaration<D3D9_GetVertexDeclarationT>::instance->isInstalled())
				{
					D3D9_GetVertexDeclaration<D3D9_GetVertexDeclarationT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetFVF" && D3D9_SetFVF<D3D9_SetFVFT>::instance->isInstalled())
				{
					D3D9_SetFVF<D3D9_SetFVFT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetFVF" && D3D9_GetFVF<D3D9_GetFVFT>::instance->isInstalled())
				{
					D3D9_GetFVF<D3D9_GetFVFT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateVertexShader" && D3D9_CreateVertexShader<D3D9_CreateVertexShaderT>::instance->isInstalled())
				{
					D3D9_CreateVertexShader<D3D9_CreateVertexShaderT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetVertexShader" && D3D9_SetVertexShader<D3D9_SetVertexShaderT>::instance->isInstalled())
				{
					D3D9_SetVertexShader<D3D9_SetVertexShaderT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetVertexShader" && D3D9_GetVertexShader<D3D9_GetVertexShaderT>::instance->isInstalled())
				{
					D3D9_GetVertexShader<D3D9_GetVertexShaderT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetVertexShaderConstantF" && D3D9_SetVertexShaderConstantF<D3D9_SetVertexShaderConstantFT>::instance->isInstalled())
				{
					D3D9_SetVertexShaderConstantF<D3D9_SetVertexShaderConstantFT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetVertexShaderConstantF" && D3D9_GetVertexShaderConstantF<D3D9_GetVertexShaderConstantFT>::instance->isInstalled())
				{
					D3D9_GetVertexShaderConstantF<D3D9_GetVertexShaderConstantFT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetVertexShaderConstantI" && D3D9_SetVertexShaderConstantI<D3D9_SetVertexShaderConstantIT>::instance->isInstalled())
				{
					D3D9_SetVertexShaderConstantI<D3D9_SetVertexShaderConstantIT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetVertexShaderConstantI" && D3D9_GetVertexShaderConstantI<D3D9_GetVertexShaderConstantIT>::instance->isInstalled())
				{
					D3D9_GetVertexShaderConstantI<D3D9_GetVertexShaderConstantIT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetVertexShaderConstantB" && D3D9_SetVertexShaderConstantB<D3D9_SetVertexShaderConstantBT>::instance->isInstalled())
				{
					D3D9_SetVertexShaderConstantB<D3D9_SetVertexShaderConstantBT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetVertexShaderConstantB" && D3D9_GetVertexShaderConstantB<D3D9_GetVertexShaderConstantBT>::instance->isInstalled())
				{
					D3D9_GetVertexShaderConstantB<D3D9_GetVertexShaderConstantBT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetStreamSource" && D3D9_SetStreamSource<D3D9_SetStreamSourceT>::instance->isInstalled())
				{
					D3D9_SetStreamSource<D3D9_SetStreamSourceT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetStreamSource" && D3D9_GetStreamSource<D3D9_GetStreamSourceT>::instance->isInstalled())
				{
					D3D9_GetStreamSource<D3D9_GetStreamSourceT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetStreamSourceFreq" && D3D9_SetStreamSourceFreq<D3D9_SetStreamSourceFreqT>::instance->isInstalled())
				{
					D3D9_SetStreamSourceFreq<D3D9_SetStreamSourceFreqT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetStreamSourceFreq" && D3D9_GetStreamSourceFreq<D3D9_GetStreamSourceFreqT>::instance->isInstalled())
				{
					D3D9_GetStreamSourceFreq<D3D9_GetStreamSourceFreqT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetIndices" && D3D9_SetIndices<D3D9_SetIndicesT>::instance->isInstalled())
				{
					D3D9_SetIndices<D3D9_SetIndicesT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetIndices" && D3D9_GetIndices<D3D9_GetIndicesT>::instance->isInstalled())
				{
					D3D9_GetIndices<D3D9_GetIndicesT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreatePixelShader" && D3D9_CreatePixelShader<D3D9_CreatePixelShaderT>::instance->isInstalled())
				{
					D3D9_CreatePixelShader<D3D9_CreatePixelShaderT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetPixelShader" && D3D9_SetPixelShader<D3D9_SetPixelShaderT>::instance->isInstalled())
				{
					D3D9_SetPixelShader<D3D9_SetPixelShaderT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetPixelShader" && D3D9_GetPixelShader<D3D9_GetPixelShaderT>::instance->isInstalled())
				{
					D3D9_GetPixelShader<D3D9_GetPixelShaderT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetPixelShaderConstantF" && D3D9_SetPixelShaderConstantF<D3D9_SetPixelShaderConstantFT>::instance->isInstalled())
				{
					D3D9_SetPixelShaderConstantF<D3D9_SetPixelShaderConstantFT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetPixelShaderConstantF" && D3D9_GetPixelShaderConstantF<D3D9_GetPixelShaderConstantFT>::instance->isInstalled())
				{
					D3D9_GetPixelShaderConstantF<D3D9_GetPixelShaderConstantFT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetPixelShaderConstantI" && D3D9_SetPixelShaderConstantI<D3D9_SetPixelShaderConstantIT>::instance->isInstalled())
				{
					D3D9_SetPixelShaderConstantI<D3D9_SetPixelShaderConstantIT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetPixelShaderConstantI" && D3D9_GetPixelShaderConstantI<D3D9_GetPixelShaderConstantIT>::instance->isInstalled())
				{
					D3D9_GetPixelShaderConstantI<D3D9_GetPixelShaderConstantIT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "SetPixelShaderConstantB" && D3D9_SetPixelShaderConstantB<D3D9_SetPixelShaderConstantBT>::instance->isInstalled())
				{
					D3D9_SetPixelShaderConstantB<D3D9_SetPixelShaderConstantBT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "GetPixelShaderConstantB" && D3D9_GetPixelShaderConstantB<D3D9_GetPixelShaderConstantBT>::instance->isInstalled())
				{
					D3D9_GetPixelShaderConstantB<D3D9_GetPixelShaderConstantBT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "DrawRectPatch" && D3D9_DrawRectPatch<D3D9_DrawRectPatchT>::instance->isInstalled())
				{
					D3D9_DrawRectPatch<D3D9_DrawRectPatchT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "DrawTriPatch" && D3D9_DrawTriPatch<D3D9_DrawTriPatchT>::instance->isInstalled())
				{
					D3D9_DrawTriPatch<D3D9_DrawTriPatchT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "DeletePatch" && D3D9_DeletePatch<D3D9_DeletePatchT>::instance->isInstalled())
				{
					D3D9_DeletePatch<D3D9_DeletePatchT>::instance->remove();
					deactivate = false;
				}
				if (functionName == "CreateQuery" && D3D9_CreateQuery<D3D9_CreateQueryT>::instance->isInstalled())
				{
					D3D9_CreateQuery<D3D9_CreateQueryT>::instance->remove();
					deactivate = false;
				}

			}

			ThreadHookerResumeThreads(5);

			if (deactivate)
			{
				GraphicHookNames.erase(GraphicHookNames.begin() + updateIndex);
				GraphicHookFunctionsBefore.erase(GraphicHookFunctionsBefore.begin() + updateIndex);
				GraphicHookFunctionsAfter.erase(GraphicHookFunctionsAfter.begin() + updateIndex);
				break;
			}
		}
	}

}


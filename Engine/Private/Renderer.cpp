#include "..\Public\Renderer.h"

#include "GameObject.h"
#include "GameInstance.h"

CRenderer::CRenderer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: m_pDevice { pDevice }
	, m_pContext { pContext }
	, m_pGameInstance{ CGameInstance::GetInstance() }
{
	Safe_AddRef(m_pContext);
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pGameInstance);
}

HRESULT CRenderer::Initialize()
{
	_uint   iNumViewports = { 1 };
	D3D11_VIEWPORT  ViewportDesc{};

	m_pContext->RSGetViewports(&iNumViewports, &ViewportDesc);	

	m_iOriginalViewportWidth  = static_cast<_uint>(ViewportDesc.Width);		
	m_iOriginalViewportHeight = static_cast<_uint>(ViewportDesc.Height);

	/* Target_Diffuse */
	if (FAILED(m_pGameInstance->Add_RenderTarget(TEXT("Target_Diffuse"), m_iOriginalViewportWidth, m_iOriginalViewportHeight, DXGI_FORMAT_R8G8B8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* Target_Normal */
	if (FAILED(m_pGameInstance->Add_RenderTarget(TEXT("Target_Normal"), m_iOriginalViewportWidth, m_iOriginalViewportHeight, DXGI_FORMAT_R16G16B16A16_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* Target_Depth */
	if (FAILED(m_pGameInstance->Add_RenderTarget(TEXT("Target_Depth"), m_iOriginalViewportWidth, m_iOriginalViewportHeight, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(0.f, 1000.f, 0.f, 0.f))))
		return E_FAIL;	

	/* Target_Shade */
	if (FAILED(m_pGameInstance->Add_RenderTarget(TEXT("Target_Shade"), m_iOriginalViewportWidth, m_iOriginalViewportHeight, DXGI_FORMAT_R16G16B16A16_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* Target_Specular */
	if (FAILED(m_pGameInstance->Add_RenderTarget(TEXT("Target_Specular"), m_iOriginalViewportWidth, m_iOriginalViewportHeight, DXGI_FORMAT_R16G16B16A16_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* Target_Shadow */
	if (FAILED(m_pGameInstance->Add_RenderTarget(TEXT("Target_Shadow"), g_iMaxWidth, g_iMaxHeight, DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(1.f, 1000.f, 1.f, 0.f))))
		return E_FAIL;	

	if (FAILED(Ready_Depth_Stencil_Buffer(g_iMaxWidth, g_iMaxHeight, &m_pShadowDSV)))		
		return E_FAIL;	

	/* Target_Final */
	if (FAILED(m_pGameInstance->Add_RenderTarget(TEXT("Target_Final"), m_iOriginalViewportWidth, m_iOriginalViewportHeight, DXGI_FORMAT_R8G8B8A8_UNORM, _float4(0.f, 0.f, 0.f, 1.f))))
		return E_FAIL;	

	/* Target_BlurX */
	if (FAILED(m_pGameInstance->Add_RenderTarget(TEXT("Target_BlurX"), m_iOriginalViewportWidth, m_iOriginalViewportHeight, DXGI_FORMAT_R8G8B8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;	

	/* Target_BlurY */
	if (FAILED(m_pGameInstance->Add_RenderTarget(TEXT("Target_BlurY"), m_iOriginalViewportWidth, m_iOriginalViewportHeight, DXGI_FORMAT_R8G8B8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;	

	/* Target_Blur_Final */
	if (FAILED(m_pGameInstance->Add_RenderTarget(TEXT("Target_Blur_Final"), m_iOriginalViewportWidth, m_iOriginalViewportHeight, DXGI_FORMAT_R8G8B8A8_UNORM, _float4(0.f, 0.f, 0.f, 1.f))))
		return E_FAIL;


	/* MRT_GameObjects */
	if (FAILED(m_pGameInstance->Add_MRT(TEXT("MRT_GameObjects"), TEXT("Target_Diffuse"))))	
		return E_FAIL;	
	if (FAILED(m_pGameInstance->Add_MRT(TEXT("MRT_GameObjects"), TEXT("Target_Normal"))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_MRT(TEXT("MRT_GameObjects"), TEXT("Target_Depth"))))
		return E_FAIL;

	/* MRT_LightAcc */
	if (FAILED(m_pGameInstance->Add_MRT(TEXT("MRT_LightAcc"), TEXT("Target_Shade"))))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Add_MRT(TEXT("MRT_LightAcc"), TEXT("Target_Specular"))))	
		return E_FAIL;	

	/* MRT_Shadow */
	if (FAILED(m_pGameInstance->Add_MRT(TEXT("MRT_Shadow"), TEXT("Target_Shadow"))))	
		return E_FAIL;	

	/* MRT_Final */
	if (FAILED(m_pGameInstance->Add_MRT(TEXT("MRT_Final"), TEXT("Target_Final"))))	
		return E_FAIL;	

	/* MRT_BlurX */
	if (FAILED(m_pGameInstance->Add_MRT(TEXT("MRT_BlurX"), TEXT("Target_BlurX"))))	
		return E_FAIL;	

	/* MRT_BlurY */
	if (FAILED(m_pGameInstance->Add_MRT(TEXT("MRT_BlurY"), TEXT("Target_BlurY"))))	
		return E_FAIL;	

	/* MRT_Blur_Final */
	if (FAILED(m_pGameInstance->Add_MRT(TEXT("MRT_Blur_Final"), TEXT("Target_Blur_Final"))))
		return E_FAIL;

    m_pShader = CShader::Create(m_pDevice, m_pContext, TEXT("../../EngineSDK/Hlsl/Shader_Deferred.hlsl"), VTXPOSTEX::Elements, VTXPOSTEX::iNumElements);
	if (nullptr == m_pShader)
		return E_FAIL; 

	m_pVIBuffer = CVIBuffer_Rect::Create(m_pDevice, m_pContext);
	if (nullptr == m_pVIBuffer)
		return E_FAIL; 
	
	XMStoreFloat4x4(&m_WorldMatrix, XMMatrixScaling(ViewportDesc.Width, ViewportDesc.Height, 1.f));
	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixOrthographicLH(ViewportDesc.Width, ViewportDesc.Height, 0.f, 1.f));	

#ifdef _DEBUG
	//if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Diffuse"), 100.f, 100.f, 200.f, 200.f)))	
	//	return E_FAIL;
	//if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Normal"), 100.f, 300.f, 200.f, 200.f)))
	//	return E_FAIL;
	//if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Depth"), 100.f, 500.f, 200.f, 200.f)))
	//	return E_FAIL;
	//if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Shade"), 350.f, 150.f, 300.f, 300.f)))	
	//	return E_FAIL;	
	//if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Specular"), 350.f, 450.f, 300.f, 300.f)))	
	//	return E_FAIL;	

	//if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Shadow"), ViewportDesc.Width - 150.f, 150.f, 300.f, 300.f)))	
	//	return E_FAIL;	
	//
	////if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Final"), 650.f, 150.f, 150.f, 150.f)))
	////	return E_FAIL;
	////if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_BlurX"), 650.f, 300.f, 150.f, 150.f)))
	////	return E_FAIL;
	////if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_BlurY"), 650.f, 450.f, 150.f, 150.f)))
	////	return E_FAIL;

	if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Diffuse"), 300.f, 100.f, 200.f, 200.f)))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Normal"), 300.f, 300.f, 200.f, 200.f)))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Depth"), 300.f, 500.f, 200.f, 200.f)))
		return E_FAIL;
	//if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Shade"), 350.f, 150.f, 300.f, 300.f)))
	//	return E_FAIL;
	//if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Specular"), 350.f, 450.f, 300.f, 300.f)))
	//	return E_FAIL;

	if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Shadow"), ViewportDesc.Width - 150.f, 150.f, 300.f, 300.f)))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_Final"), 100.f, 100.f, 200.f, 200.f)))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_BlurX"), 100.f, 300.f, 200.f, 200.f)))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Ready_RT_Debug(TEXT("Target_BlurY"), 100.f, 500.f, 200.f, 200.f)))
		return E_FAIL;

#endif // _DEBUG


 	return S_OK;
}

HRESULT CRenderer::Add_RenderGroup(RENDERGROUP eRenderGroupID, CGameObject * pGameObject)
{
	if (nullptr == pGameObject || 
		eRenderGroupID >= RG_END )
		return E_FAIL;

	m_RenderObjects[eRenderGroupID].push_back(pGameObject);

	Safe_AddRef(pGameObject);

	return S_OK;
}

HRESULT CRenderer::Render()
{
 	if (FAILED(Render_Priority()))
		return E_FAIL;

	if (FAILED(Render_Shadow()))	
		return E_FAIL;	

	if (FAILED(Render_NonBlend()))
		return E_FAIL;

	if (FAILED(Render_LightAcc()))	
		return E_FAIL;	

	/*  블러 테스트 하는 곳 */
	if (FAILED(Render_BlurBegin()))		
		return E_FAIL;	

	if (FAILED(Render_BlurX()))		
		return E_FAIL;	
			
	if (FAILED(Render_BlurY()))		
		return E_FAIL;

	if (FAILED(Render_Final()))	
		return E_FAIL;
	/* */


	if (FAILED(Render_Deferred()))	
		return E_FAIL;	

	/*if (FAILED(Render_BlurX()))	
		return E_FAIL;	

	if (FAILED(Render_BlurY()))	
		return E_FAIL;

	if (FAILED(Render_Final()))
		return E_FAIL;*/
		
	if (FAILED(Render_NonLight()))
		return E_FAIL;	

	if (FAILED(Render_Blend()))
		return E_FAIL;

	if (FAILED(Render_UI()))
		return E_FAIL;


#ifdef _DEBUG
	//if (FAILED(Render_Debug()))	
	//	return E_FAIL;	
#endif

	return S_OK;
}

HRESULT CRenderer::Render_Priority()
{

	for (auto& pRenderObject : m_RenderObjects[RG_PRIORITY])
	{
		if (FAILED(pRenderObject->Render()))
			return E_FAIL;

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[RG_PRIORITY].clear();


	return S_OK;
}

HRESULT CRenderer::Render_Shadow()			
{
	/* Shadow */
  	if (FAILED(m_pGameInstance->Begin_MRT(TEXT("MRT_Shadow"),true, m_pShadowDSV)))	
		return E_FAIL;

	if (FAILED(SetUp_ViewportDesc(g_iMaxWidth, g_iMaxHeight)))	
		return E_FAIL;	

	for (auto& pRenderObject : m_RenderObjects[RG_SHADOW])	
	{
		if (FAILED(pRenderObject->Render_Shadow()))
			return E_FAIL;

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[RG_SHADOW].clear();

	if (FAILED(m_pGameInstance->End_MRT(m_pShadowDSV)))		
		return E_FAIL;	

	if (FAILED(SetUp_ViewportDesc(m_iOriginalViewportWidth, m_iOriginalViewportHeight)))			
		return E_FAIL;	


	return S_OK;	
}

HRESULT CRenderer::Render_NonBlend()
{
	/* Diffuse + Normal */
	if (FAILED(m_pGameInstance->Begin_MRT(TEXT("MRT_GameObjects"))))		
		return E_FAIL;	

	for (auto& pRenderObject : m_RenderObjects[RG_NONBLEND])
	{
		if (FAILED(pRenderObject->Render()))
			return E_FAIL;

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[RG_NONBLEND].clear();

	if (FAILED(m_pGameInstance->End_MRT()))	
		return E_FAIL;	

	return S_OK;
}

HRESULT CRenderer::Render_NonLight()
{
	for (auto& pRenderObject : m_RenderObjects[RG_NONLIGHT])
	{
		if (FAILED(pRenderObject->Render()))
			return E_FAIL;

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[RG_NONLIGHT].clear();
	
	return S_OK;
}

HRESULT CRenderer::Render_LightAcc()
{
	/* Shade */

	if (FAILED(m_pGameInstance->Begin_MRT(TEXT("MRT_LightAcc"))))	
		return E_FAIL;

	if (FAILED(m_pGameInstance->Bind_RT_ShaderResource(TEXT("Target_Normal"), m_pShader, "g_NormalTexture")))	
		return E_FAIL;
	if (FAILED(m_pGameInstance->Bind_RT_ShaderResource(TEXT("Target_Depth"), m_pShader, "g_DepthTexture")))	
		return E_FAIL;	
	
	m_pShader->Bind_Matrix("g_WorldMatrix", &m_WorldMatrix);
	m_pShader->Bind_Matrix("g_ViewMatrix",  &m_ViewMatrix);
	m_pShader->Bind_Matrix("g_ProjMatrix",  &m_ProjMatrix); 
	
	m_pShader->Bind_Matrix("g_ViewMatrixInv", &m_pGameInstance->Get_Transform_Float4x4_Inverse(CPipeLine::D3DTS_VIEW));
	m_pShader->Bind_Matrix("g_ProjMatrixInv", &m_pGameInstance->Get_Transform_Float4x4_Inverse(CPipeLine::D3DTS_PROJ));

	m_pShader->Bind_RawValue("g_vCamPosition", &m_pGameInstance->Get_CamPosition(), sizeof(_float4));

 	m_pGameInstance->Render_Lights(m_pShader, m_pVIBuffer);

	if (FAILED(m_pGameInstance->End_MRT()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_Deferred()
{                  
	
	if (FAILED(m_pGameInstance->Bind_RT_ShaderResource(TEXT("Target_Diffuse"), m_pShader, "g_DiffuseTexture")))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Bind_RT_ShaderResource(TEXT("Target_Shade"), m_pShader, "g_ShadeTexture")))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Bind_RT_ShaderResource(TEXT("Target_Specular"), m_pShader, "g_SpecularTexture")))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Bind_RT_ShaderResource(TEXT("Target_Shadow"), m_pShader, "g_ShadowTexture")))	
		return E_FAIL;	

	if (FAILED(m_pGameInstance->Bind_RT_ShaderResource(TEXT("Target_Depth"), m_pShader, "g_DepthTexture")))	
		return E_FAIL;	

	if (FAILED(m_pGameInstance->Bind_RT_ShaderResource(TEXT("Target_Blur_Final"), m_pShader, "g_FinalTexture")))
		return E_FAIL;


	if (FAILED(m_pShader->Bind_Matrix("g_WorldMatrix", &m_WorldMatrix)))	
		return E_FAIL;	
	if (FAILED(m_pShader->Bind_Matrix("g_ViewMatrix", &m_ViewMatrix)))	
		return E_FAIL;	
	if (FAILED(m_pShader->Bind_Matrix("g_ProjMatrix", &m_ProjMatrix)))	
		return E_FAIL;	

	if (FAILED(m_pGameInstance->Bind_Shadow_Matrices(m_pShader, "g_LightViewMatrix", "g_LightProjMatrix")))		
		return E_FAIL;		

	m_pShader->Bind_Matrix("g_ViewMatrixInv", &m_pGameInstance->Get_Transform_Float4x4_Inverse(CPipeLine::D3DTS_VIEW));		
	m_pShader->Bind_Matrix("g_ProjMatrixInv", &m_pGameInstance->Get_Transform_Float4x4_Inverse(CPipeLine::D3DTS_PROJ));		
		


	m_pShader->Begin(3);	

	m_pVIBuffer->Bind_InputAssembler();	
	m_pVIBuffer->Render();	

	

	return S_OK;
}

HRESULT CRenderer::Render_BlurBegin()	
{
	if (FAILED(m_pGameInstance->Begin_MRT(TEXT("MRT_Final"))))
		return E_FAIL;


	for (auto& pRenderObject : m_RenderObjects[RG_BLUR])		
	{
		if (FAILED(pRenderObject->Render_Blur()))		
			return E_FAIL;	
			
		Safe_Release(pRenderObject);	
	}

	m_RenderObjects[RG_BLUR].clear();

	if (FAILED(m_pGameInstance->End_MRT()))
		return E_FAIL;	

	return S_OK;	
}

HRESULT CRenderer::Render_BlurX()
{
	if (FAILED(m_pGameInstance->Begin_MRT(TEXT("MRT_BlurX"))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Bind_RT_ShaderResource(TEXT("Target_Final"), m_pShader, "g_FinalTexture")))
		return E_FAIL;


	if (FAILED(m_pShader->Bind_Matrix("g_WorldMatrix", &m_WorldMatrix)))
		return E_FAIL;
	if (FAILED(m_pShader->Bind_Matrix("g_ViewMatrix", &m_ViewMatrix)))
		return E_FAIL;
	if (FAILED(m_pShader->Bind_Matrix("g_ProjMatrix", &m_ProjMatrix)))
		return E_FAIL;

	m_pShader->Begin(4);	

	m_pVIBuffer->Bind_InputAssembler();	
	m_pVIBuffer->Render();	

	if (FAILED(m_pGameInstance->End_MRT()))	
		return E_FAIL;

	return S_OK;	

}

HRESULT CRenderer::Render_BlurY()
{
	if (FAILED(m_pGameInstance->Begin_MRT(TEXT("MRT_BlurY"))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Bind_RT_ShaderResource(TEXT("Target_BlurX"), m_pShader, "g_BlurXTexture")))
		return E_FAIL;

	if (FAILED(m_pShader->Bind_Matrix("g_WorldMatrix", &m_WorldMatrix)))
		return E_FAIL;
	if (FAILED(m_pShader->Bind_Matrix("g_ViewMatrix", &m_ViewMatrix)))
		return E_FAIL;
	if (FAILED(m_pShader->Bind_Matrix("g_ProjMatrix", &m_ProjMatrix)))
		return E_FAIL;


	m_pShader->Begin(5);	

	m_pVIBuffer->Bind_InputAssembler();		
	m_pVIBuffer->Render();	

	if (FAILED(m_pGameInstance->End_MRT()))	
		return E_FAIL;	

	return S_OK;
}

HRESULT CRenderer::Render_Final()
{
	if (FAILED(m_pGameInstance->Begin_MRT(TEXT("MRT_Blur_Final"))))	
		return E_FAIL;	

	if (FAILED(m_pGameInstance->Bind_RT_ShaderResource(TEXT("Target_BlurY"), m_pShader, "g_BlurYTexture")))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Bind_RT_ShaderResource(TEXT("Target_Final"), m_pShader, "g_FinalTexture")))
		return E_FAIL;


	if (FAILED(m_pShader->Bind_Matrix("g_WorldMatrix", &m_WorldMatrix)))
		return E_FAIL;
	if (FAILED(m_pShader->Bind_Matrix("g_ViewMatrix", &m_ViewMatrix)))
		return E_FAIL;
	if (FAILED(m_pShader->Bind_Matrix("g_ProjMatrix", &m_ProjMatrix)))
		return E_FAIL;

	m_pShader->Begin(6);

	m_pVIBuffer->Bind_InputAssembler();	
	m_pVIBuffer->Render();	

	if (FAILED(m_pGameInstance->End_MRT()))
		return E_FAIL;

	return S_OK;	
}

HRESULT CRenderer::Render_Blend()
{
	for (auto& pRenderObject : m_RenderObjects[RG_BLEND])
	{
		if (FAILED(pRenderObject->Render()))
			return E_FAIL;

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[RG_BLEND].clear();

	return S_OK;
}

HRESULT CRenderer::Render_UI()
{
	for (auto& pRenderObject : m_RenderObjects[RG_UI])
	{
		if (FAILED(pRenderObject->Render()))
			return E_FAIL;

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[RG_UI].clear();

	return S_OK;
}

HRESULT CRenderer::Ready_Depth_Stencil_Buffer(_uint iWidth, _uint iHeight, ID3D11DepthStencilView** ppOut)
{
	ID3D11Texture2D* pDepthStencilTexture = { nullptr };

	D3D11_TEXTURE2D_DESC	TextureDesc;
	ZeroMemory(&TextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

	/* 깊이 버퍼의 픽셀으 ㄴ백버퍼의 픽셀과 갯수가 동일해야만 깊이 텍스트가 가능해진다. */
	/* 픽셀의 수가 다르면 아에 렌덜잉을 못함. */
	TextureDesc.Width = iWidth;
	TextureDesc.Height = iHeight;
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	TextureDesc.SampleDesc.Quality = 0;
	TextureDesc.SampleDesc.Count = 1;


	TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	TextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = 0;

	if (FAILED(m_pDevice->CreateTexture2D(&TextureDesc, nullptr, &pDepthStencilTexture)))
		return E_FAIL;

	if (FAILED(m_pDevice->CreateDepthStencilView(pDepthStencilTexture, nullptr, ppOut)))
		return E_FAIL;

	Safe_Release(pDepthStencilTexture);

	return S_OK;
}

HRESULT CRenderer::SetUp_ViewportDesc(_uint iWidth, _uint iHeight)
{
	D3D11_VIEWPORT			ViewPortDesc;	
	ZeroMemory(&ViewPortDesc, sizeof(D3D11_VIEWPORT));	
	ViewPortDesc.TopLeftX = 0;		
	ViewPortDesc.TopLeftY = 0;	
	ViewPortDesc.Width = (_float)iWidth;	
	ViewPortDesc.Height = (_float)iHeight;	
	ViewPortDesc.MinDepth = 0.f;	
	ViewPortDesc.MaxDepth = 1.f;	

	m_pContext->RSSetViewports(1, &ViewPortDesc);	

	return S_OK;
}

HRESULT CRenderer::Render_Debug()
{
	if (FAILED(m_pShader->Bind_Matrix("g_ViewMatrix", &m_ViewMatrix)))
		return E_FAIL;
	if (FAILED(m_pShader->Bind_Matrix("g_ProjMatrix", &m_ProjMatrix)))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Render_RT_Debug(TEXT("MRT_GameObjects"), m_pShader, m_pVIBuffer)))
		return E_FAIL;
	//if (FAILED(m_pGameInstance->Render_RT_Debug(TEXT("MRT_LightAcc"), m_pShader, m_pVIBuffer)))
	//	return E_FAIL;

	if (FAILED(m_pGameInstance->Render_RT_Debug(TEXT("MRT_Shadow"), m_pShader, m_pVIBuffer)))	
		return E_FAIL;	

	if (FAILED(m_pGameInstance->Render_RT_Debug(TEXT("MRT_Final"), m_pShader, m_pVIBuffer)))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Render_RT_Debug(TEXT("MRT_BlurX"), m_pShader, m_pVIBuffer)))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Render_RT_Debug(TEXT("MRT_BlurY"), m_pShader, m_pVIBuffer)))
		return E_FAIL;

	return S_OK;
}

CRenderer * CRenderer::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRenderer*	pInstance = new CRenderer(pDevice, pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed To Created : CRenderer");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRenderer::Free()
{
	__super::Free();

	for (auto& RenderObjects : m_RenderObjects)
	{
		for (auto& pRenderObject : RenderObjects)		
			Safe_Release(pRenderObject);

		RenderObjects.clear();
	}

	Safe_Release(m_pShadowDSV);	
	Safe_Release(m_pShader);
	Safe_Release(m_pVIBuffer);


	Safe_Release(m_pGameInstance);	
	Safe_Release(m_pContext);	
	Safe_Release(m_pDevice);
}	


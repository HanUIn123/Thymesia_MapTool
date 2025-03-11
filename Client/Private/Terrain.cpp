#include "pch.h" 
#include "..\Public\Terrain.h"
#include "GameInstance.h"

CTerrain::CTerrain(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject{ pDevice, pContext }
{

}

CTerrain::CTerrain(const CTerrain& Prototype)
	: CGameObject(Prototype)
{
}

HRESULT CTerrain::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTerrain::Initialize(void* pArg)
{
	TERRAINDESC* pDesc = static_cast<TERRAINDESC*>(pArg);

	if (pDesc->pMaskTexture != nullptr)
		m_pMaskTexture = pDesc->pMaskTexture;

	if (pDesc->pWaterMapTexture != nullptr)
		m_pWaterMapTexture = pDesc->pWaterMapTexture;

	if (FAILED(__super::Initialize(nullptr)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(30.0f, 0.0f, -150.0f, 1.0f));

	return S_OK;
}

void CTerrain::Priority_Update(_float fTimeDelta)
{
	//m_pNavigationCom->SetUp_WorldMatrix(XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrix_Ptr()));
}

void CTerrain::Update(_float fTimeDelta)
{
	int a = 10;

	ImGui::Begin("Switch FrameMode", NULL, ImGuiWindowFlags_MenuBar);
	ImGui::Checkbox("Switching To WireFrame", &m_bWireFrameMode);
	if (ImGui::Button("WireFrame On"))
		m_bWireFrameMode = true;
	if (ImGui::Button("WireFrame Off"))
		m_bWireFrameMode = false;
	ImGui::End();
}

void CTerrain::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this);
}

HRESULT CTerrain::Render()
{
	/* 네비이게이션 버퍼 확인용으로 잠깐 뺌*/
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	m_bWireFrameMode ? m_pShaderCom->Begin(1) : m_pShaderCom->Begin(2);

	//m_pShaderCom->Begin(0);

	m_pVIBufferCom->Bind_InputAssembler();

	//CTempManager::GetInstance()->SwitchFrameMode();

	m_pVIBufferCom->Render();

#ifdef _DEBUG				
	m_pNavigationCom->Render();
#endif // _DEBUG


	return S_OK;
}

void CTerrain::Set_TerrainPickPos(_float3 _fPickPos, _float _fRange)
{
	m_fPickPos = _fPickPos;
	m_fRange = _fRange;
}

HRESULT CTerrain::Ready_Components()
{
	/* Com_Texture */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Terrain"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Terrain_Normal"),
		TEXT("Com_NormalTexture"), reinterpret_cast<CComponent**>(&m_pTextureNormalCom))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Terrain_ORM"),
		TEXT("Com_ORMTexture"), reinterpret_cast<CComponent**>(&m_pTextureORMCom))))
		return E_FAIL;

	// Prototype_Component_Texture__MouseRange
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture__MouseRange"),
		TEXT("Com_MouseTexture"), reinterpret_cast<CComponent**>(&m_pMouseTextureCom))))
		return E_FAIL;

	/* Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxNorTex"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* Com_VIBuffer */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Terrain"),
		TEXT("Com_VIBuffer_Terrain"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	/* Com_Navigation */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Navigation"),
		TEXT("Com_Navigation"), reinterpret_cast<CComponent**>(&m_pNavigationCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CTerrain::Bind_ShaderResources()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->Bind_ShaderResources(m_pShaderCom, "g_DiffuseTexture")))
		return E_FAIL;

	if (FAILED(m_pTextureNormalCom->Bind_ShaderResources(m_pShaderCom, "g_NormalTexture")))
		return E_FAIL;

	if (FAILED(m_pTextureORMCom->Bind_ShaderResources(m_pShaderCom, "g_ORMTexture")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Bind_SRV("g_MaskTexture", m_pMaskTexture)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Bind_SRV("g_WaterMapTexture", m_pWaterMapTexture)))
		return E_FAIL;

	if (FAILED(m_pMouseTextureCom->Bind_ShaderResource(m_pShaderCom, "g_MouseTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Bind_RawValue("g_BrushRange", &m_fRange, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Bind_RawValue("g_PickedPoints", &m_fPickPos, sizeof(_float3))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Bind_RawValue("g_WireFrameMode", &m_bWireFrameMode, sizeof(_bool))))
		return E_FAIL;


	return S_OK;
}

CTerrain* CTerrain::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CTerrain* pInstance = new CTerrain(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed To Created : CTerrain");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CTerrain::Clone(void* pArg)
{
	CTerrain* pInstance = new CTerrain(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Cloned : CTerrain");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTerrain::Free()
{
	__super::Free();

	Safe_Release(m_pNavigationCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pMouseTextureCom);
	Safe_Release(m_pTextureNormalCom);
	Safe_Release(m_pTextureORMCom);
}

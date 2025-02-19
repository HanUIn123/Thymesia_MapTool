#include "pch.h"

#include "SM_WoodenFence03.h"

#include "GameInstance.h"

CSM_WoodenFence03::CSM_WoodenFence03(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CObject(pDevice, pContext)
{
}

CSM_WoodenFence03::CSM_WoodenFence03(const CSM_WoodenFence03& Prototype)
	: CObject(Prototype)
{
}

HRESULT CSM_WoodenFence03::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSM_WoodenFence03::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CSM_WoodenFence03::Priority_Update(_float fTimeDelta)
{
}

void CSM_WoodenFence03::Update(_float fTimeDelta)
{
}

void CSM_WoodenFence03::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this);
}

HRESULT CSM_WoodenFence03::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	_uint			iNumMeshes = m_pModelCom->Get_NumMeshes();

	for (size_t i = 0; i < iNumMeshes; i++)
	{
		if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_DIFFUSE, "g_DiffuseTexture", 0)))
			return E_FAIL;

		if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_NORMALS, "g_NormalTexture", 0)))
			return E_FAIL;

		m_pShaderCom->Begin(0);
		m_pModelCom->Render(i);
	}

	return S_OK;
}

HRESULT CSM_WoodenFence03::Ready_Components()
{
	if (FAILED(__super::Ready_Components()))
		return E_FAIL;

	/* Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_HORSE_P_WoodenFrame02_05"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CSM_WoodenFence03::Bind_ShaderResources()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;

	return S_OK;
}

CSM_WoodenFence03* CSM_WoodenFence03::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CSM_WoodenFence03* pInstance = new CSM_WoodenFence03(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed To Created : CSM_WoodenFence03");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CSM_WoodenFence03::Clone(void* pArg)
{
	CSM_WoodenFence03* pInstance = new CSM_WoodenFence03(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Created : CSM_WoodenFence03");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSM_WoodenFence03::Free()
{
	__super::Free();
}

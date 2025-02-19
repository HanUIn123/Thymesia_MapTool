#include "pch.h"

#include "HORSE_P_WoodenFrame02_05.h"

#include "GameInstance.h"

CHORSE_P_WoodenFrame02_05::CHORSE_P_WoodenFrame02_05(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CObject(pDevice, pContext)
{
}

CHORSE_P_WoodenFrame02_05::CHORSE_P_WoodenFrame02_05(const CHORSE_P_WoodenFrame02_05& Prototype)
	: CObject(Prototype)
{
}

HRESULT CHORSE_P_WoodenFrame02_05::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CHORSE_P_WoodenFrame02_05::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CHORSE_P_WoodenFrame02_05::Priority_Update(_float fTimeDelta)
{
}

void CHORSE_P_WoodenFrame02_05::Update(_float fTimeDelta)
{
}

void CHORSE_P_WoodenFrame02_05::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this);
}

HRESULT CHORSE_P_WoodenFrame02_05::Render()
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

HRESULT CHORSE_P_WoodenFrame02_05::Ready_Components()
{
	if (FAILED(__super::Ready_Components()))
		return E_FAIL;

	/* Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_HORSE_P_WoodenFrame02_05"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CHORSE_P_WoodenFrame02_05::Bind_ShaderResources()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;

	return S_OK;
}

CHORSE_P_WoodenFrame02_05* CHORSE_P_WoodenFrame02_05::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CHORSE_P_WoodenFrame02_05* pInstance = new CHORSE_P_WoodenFrame02_05(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed To Created : CSM_Wall_Shelf");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CHORSE_P_WoodenFrame02_05::Clone(void* pArg)
{
	CHORSE_P_WoodenFrame02_05* pInstance = new CHORSE_P_WoodenFrame02_05(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Created : CSM_Wall_Shelf");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CHORSE_P_WoodenFrame02_05::Free()
{
	__super::Free();
}

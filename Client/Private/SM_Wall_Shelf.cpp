#include "pch.h"

#include "SM_Wall_Shelf.h"

#include "GameInstance.h"

CSM_Wall_Shelf::CSM_Wall_Shelf(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CObject(pDevice, pContext)
{
}

CSM_Wall_Shelf::CSM_Wall_Shelf(const CSM_Wall_Shelf& Prototype)
	: CObject(Prototype)
{
}

HRESULT CSM_Wall_Shelf::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSM_Wall_Shelf::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CSM_Wall_Shelf::Priority_Update(_float fTimeDelta)
{
}

void CSM_Wall_Shelf::Update(_float fTimeDelta)
{
}

void CSM_Wall_Shelf::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this);
}

HRESULT CSM_Wall_Shelf::Render()
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

HRESULT CSM_Wall_Shelf::Ready_Components()
{
	if (FAILED(__super::Ready_Components()))
		return E_FAIL;

	/* Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SM_Wall_Shelf"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CSM_Wall_Shelf::Bind_ShaderResources()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;

	return S_OK;
}

CSM_Wall_Shelf* CSM_Wall_Shelf::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CSM_Wall_Shelf* pInstance = new CSM_Wall_Shelf(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed To Created : CSM_Wall_Shelf");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CSM_Wall_Shelf::Clone(void* pArg)
{
	CSM_Wall_Shelf* pInstance = new CSM_Wall_Shelf(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Created : CSM_Wall_Shelf");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSM_Wall_Shelf::Free()
{
	__super::Free();
}

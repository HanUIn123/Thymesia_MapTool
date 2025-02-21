#include "pch.h"

#include "NonMoveObject.h"

#include "GameInstance.h"

CNonMoveObject::CNonMoveObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CObject(pDevice, pContext)
{
}

CNonMoveObject::CNonMoveObject(const CNonMoveObject& Prototype)
	: CObject(Prototype)
{
}

HRESULT CNonMoveObject::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CNonMoveObject::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CNonMoveObject::Priority_Update(_float fTimeDelta)
{
}

void CNonMoveObject::Update(_float fTimeDelta)
{
#ifdef _DEBUG
	_matrix matWorld = XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrix_Ptr());

	matWorld.r[0] = XMVector3Normalize(matWorld.r[0]) * m_fFrustumRadius;
	matWorld.r[1] = XMVector3Normalize(matWorld.r[1]) * m_fFrustumRadius;
	matWorld.r[2] = XMVector3Normalize(matWorld.r[2]) * m_fFrustumRadius;

	m_pColliderCom->Update(matWorld);
#endif
}

void CNonMoveObject::Late_Update(_float fTimeDelta)
{
	if(m_pGameInstance->isIn_Frustum_WorldSpace(m_pTransformCom->Get_State(CTransform::STATE_POSITION), m_fFrustumRadius))
		m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this);

}

HRESULT CNonMoveObject::Render()
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


#ifdef _DEBUG
	m_pColliderCom->Render();
#endif

	return S_OK;
}

HRESULT CNonMoveObject::Ready_Components()
{
	if (FAILED(__super::Ready_Components()))
		return E_FAIL;

	string strComponentName = "Prototype_Component_Model_";
	strComponentName += m_MeshName;

	_tchar		szComponentName[MAX_PATH] = {};

	MultiByteToWideChar(CP_ACP, 0, strComponentName.c_str(), strlen(strComponentName.c_str()), szComponentName, MAX_PATH);

	/* Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, szComponentName,
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CNonMoveObject::Bind_ShaderResources()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;

	return S_OK;
}

CNonMoveObject* CNonMoveObject::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CNonMoveObject* pInstance = new CNonMoveObject(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed To Created : CNonMoveObject");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CNonMoveObject::Clone(void* pArg)
{
	CNonMoveObject* pInstance = new CNonMoveObject(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Created : CNonMoveObject");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CNonMoveObject::Free()
{
	__super::Free();
}

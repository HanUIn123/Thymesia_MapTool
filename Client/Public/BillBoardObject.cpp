#include "pch.h"

#include "BillBoardObject.h"

#include "GameInstance.h"

CBillBoardObject::CBillBoardObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CObject(pDevice, pContext)
{
}

CBillBoardObject::CBillBoardObject(const CBillBoardObject& Prototype)
	: CObject(Prototype)
{
}

HRESULT CBillBoardObject::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBillBoardObject::Initialize(void* pArg)
{
	BILLBOARDOBJECTDESC* pDesc = static_cast<BILLBOARDOBJECTDESC*>(pArg);

	m_iBillBoardMeshNum = pDesc->iBillBoardMeshNum;

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	XMStoreFloat4x4(&m_pOriginalMatrix, XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrix_Ptr())); // 기존 Transform 저장

	m_iObjectType = OBJECT_BILLBOARD;

	return S_OK;
}

void CBillBoardObject::Priority_Update(_float fTimeDelta)
{
}

void CBillBoardObject::Update(_float fTimeDelta)
{
	BillBoard(); // 빌보드 Transform 계산

#ifdef _DEBUG
	_matrix matWorld = XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrix_Ptr());

	matWorld.r[0] = XMVector3Normalize(matWorld.r[0]) * m_fFrustumRadius;
	matWorld.r[1] = XMVector3Normalize(matWorld.r[1]) * m_fFrustumRadius;
	matWorld.r[2] = XMVector3Normalize(matWorld.r[2]) * m_fFrustumRadius;

	m_pColliderCom->Update(matWorld);
#endif
}

void CBillBoardObject::Late_Update(_float fTimeDelta)
{
	if(m_pGameInstance->isIn_Frustum_WorldSpace(m_pTransformCom->Get_State(CTransform::STATE_POSITION), m_fFrustumRadius))
		m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this);

}

HRESULT CBillBoardObject::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	_uint			iNumMeshes = m_pModelCom->Get_NumMeshes();

	for (size_t i = 0; i < iNumMeshes; i++)
	{
		if (i != m_iBillBoardMeshNum)
		{
			if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_DIFFUSE, "g_DiffuseTexture", 0)))
				return E_FAIL;

			if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_NORMALS, "g_NormalTexture", 0)))
				return E_FAIL;

			m_pShaderCom->Begin(m_iCullPass);
			m_pModelCom->Render(i);
		}
	}

	//빌보드 메쉬 제외하고 Render후 BillBoard용 메쉬 다시 render()

	if (FAILED(Bind_ShaderResourcesForBillBoard()))
		return E_FAIL;

	if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, m_iBillBoardMeshNum, aiTextureType_DIFFUSE, "g_DiffuseTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, m_iBillBoardMeshNum, aiTextureType_NORMALS, "g_NormalTexture", 0)))
		return E_FAIL;

	m_pShaderCom->Begin(m_iCullPass);
	m_pModelCom->Render(m_iBillBoardMeshNum);

	if (m_bFrustumSphere)
	{
		m_pColliderCom->Render();
	}

	return S_OK;
}

HRESULT CBillBoardObject::Ready_Components()
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

HRESULT CBillBoardObject::Bind_ShaderResources()
{
	if (FAILED(m_pShaderCom->Bind_Matrix("g_WorldMatrix", &m_pOriginalMatrix)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;

	return S_OK;
}

void CBillBoardObject::BillBoard()
{
	_vector vCamPos = XMLoadFloat4(&m_pGameInstance->Get_CamPosition());

	m_pTransformCom->LookAt(vCamPos);
}

HRESULT CBillBoardObject::Bind_ShaderResourcesForBillBoard()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;

	return S_OK;
}

CBillBoardObject* CBillBoardObject::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CBillBoardObject* pInstance = new CBillBoardObject(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed To Created : CBillBoardObject");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CBillBoardObject::Clone(void* pArg)
{
	CBillBoardObject* pInstance = new CBillBoardObject(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Created : CNonMoveObject");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBillBoardObject::Free()
{
	__super::Free();
}

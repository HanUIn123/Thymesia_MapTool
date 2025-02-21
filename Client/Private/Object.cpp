#include "pch.h"
#include "Object.h"



CObject::CObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CGameObject(pDevice, pContext)
{
}

CObject::CObject(const CObject& Prototype)
	:CGameObject(Prototype)
{
}

HRESULT CObject::Initialize(void* pArg)
{
	CObject::OBJECT_DESC* pDesc = static_cast<CObject::OBJECT_DESC*>(pArg);

	m_fFrustumRadius = pDesc->fFrustumRadius;

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	strcpy_s(m_MeshName, pDesc->ObjectName.c_str());

	if (FAILED(Ready_Components()))
		return E_FAIL;

	m_pTransformCom->Rotation(XMConvertToRadians(pDesc->fRotation.x), XMConvertToRadians(pDesc->fRotation.y), XMConvertToRadians(pDesc->fRotation.z));

	m_Meshes = m_pModelCom->Get_Meshes();


	return S_OK;
}

_bool CObject::Picking_Objects(MESHINFO &pInfo)
{
	vector <MESHINFO> vMesh;

	MESHINFO sMesh;

	_vector fPos;


	for (auto pModel : m_Meshes)
	{
		if (m_pCalculatorCom->PickingOnMesh(g_hWnd, pModel, m_pTransformCom, sMesh.fDist, fPos))
		{
			XMStoreFloat3(&sMesh.fPosition, fPos);
			vMesh.push_back(sMesh);
		}
	}

	if (vMesh.size() != 0)
	{
		sort(vMesh.begin(), vMesh.end(), [](MESHINFO a, MESHINFO b) {
			if (a.fDist < b.fDist) return true;
			else
				return false;
			});

		pInfo.fPosition = vMesh.front().fPosition;
		pInfo.fDist = vMesh.front().fDist;

		return true;
	}

	return false;
}

CObject::OBJECT_INFO CObject::Get_ObjectInfo()
{
	OBJECT_INFO pInfo{};

	strcpy_s(pInfo.szName, m_MeshName);

	pInfo.fFrustumRadius = m_fFrustumRadius;
	pInfo.fScale		 = m_pTransformCom->Get_Scale();
	pInfo.fRotation		 = m_pTransformCom->Get_Rotation();
	XMStoreFloat4(&pInfo.fPosition, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	return pInfo;
}

void CObject::Set_FrustumRadius(_float fFrustumRadius)
{
	m_fFrustumRadius = fFrustumRadius;
}

HRESULT CObject::Ready_Components()
{
	/* Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxMesh"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* Com_Calculator */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Calculator"),
		TEXT("Com_Calculator"), reinterpret_cast<CComponent**>(&m_pCalculatorCom))))
		return E_FAIL;

	CBounding_Sphere::BOUNDING_SPHERE_DESC SphereDesc{};

	SphereDesc.fRadius = 1.f;
	SphereDesc.vCenter = _float3(0.f, 0.f, 0.f);

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Collider_SPHERE"),
		TEXT("Com_Colldier"), reinterpret_cast<CComponent**>(&m_pColliderCom), &SphereDesc)))
		return E_FAIL;


	return S_OK;
}

void CObject::Free()
{
	__super::Free();

	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pCalculatorCom);
	Safe_Release(m_pColliderCom);
}

#include "pch.h"
#include "EnvironmentObject.h"

CEnvironmentObject::CEnvironmentObject(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
	:CGameObject{ _pDevice, _pContext }
{
}

CEnvironmentObject::CEnvironmentObject(const CEnvironmentObject& _Prototype)
	:CGameObject(_Prototype)
{
}

HRESULT CEnvironmentObject::Initialize(void* _pArg)
{
	CEnvironmentObject::ENVIRONMENT_OBJECT_DESC* pDesc = static_cast<CEnvironmentObject::ENVIRONMENT_OBJECT_DESC*>(_pArg);

	m_fFrustumRadius = pDesc->fFrustumRadius;

	if (FAILED(__super::Initialize(_pArg)))
		return E_FAIL;

	strcpy_s(m_EnvironmentMeshName, pDesc->ObjectName.c_str());

	if (FAILED(Ready_Components()))
		return E_FAIL;

	m_pTransformCom->Rotation(XMConvertToRadians(pDesc->fRotation.x), XMConvertToRadians(pDesc->fRotation.y), XMConvertToRadians(pDesc->fRotation.z));

	m_vecMeshes = m_pModelCom->Get_Meshes();

	return S_OK;
}

_bool CEnvironmentObject::Picking_En_Objects(EN_MESH_INFO& _pInfo)
{
	vector <EN_MESH_INFO> vMesh;

	EN_MESH_INFO sMesh;
	_vector fPos;

	for (auto pModel : m_vecMeshes)
	{
		if (m_pCalculatorCom->PickingOnMesh(g_hWnd, pModel, m_pTransformCom, sMesh.fDist, fPos))
		{
			XMStoreFloat3(&sMesh.fPosition, fPos);
			vMesh.push_back(sMesh);
		}
	}

	if (vMesh.size() != 0)
	{
		sort(vMesh.begin(), vMesh.end(), [](EN_MESH_INFO a, EN_MESH_INFO b) {
			if (a.fDist < b.fDist) return true;
			else
				return false;
			});

		_pInfo.fPosition = vMesh.front().fPosition;
		_pInfo.fDist = vMesh.front().fDist;

		return true;
	}

	return false;
}

CEnvironmentObject::EN_OBJECT_INFO CEnvironmentObject::Get_EnvironmentObjectInfo()
{
	EN_OBJECT_INFO pInfo{};

	strcpy_s(pInfo.szName, m_EnvironmentMeshName);

	pInfo.fFrustumRadius = m_fFrustumRadius;
	pInfo.fScale = m_pTransformCom->Get_Scale();
	pInfo.fRotation = m_pTransformCom->Get_Rotation();
	XMStoreFloat4(&pInfo.fPosition, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	return pInfo;
}

void CEnvironmentObject::Set_FrustumRadius(_float _fFrustumRadius)
{
	m_fFrustumRadius = _fFrustumRadius;
}

HRESULT CEnvironmentObject::Ready_Components()
{
	/* Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxInstanceMesh"),
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

void CEnvironmentObject::Free()
{
	__super::Free();

	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pCalculatorCom);
	Safe_Release(m_pColliderCom);
}

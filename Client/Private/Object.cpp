#include "pch.h"
#include "Object.h"

#include "GameInstance.h"

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

	if (FAILED(Ready_Components()))
		return E_FAIL;

	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&pDesc->fPosition));

	m_Meshes = m_pModelCom->Get_Meshes();

	return S_OK;
}

_float3 CObject::Picking_Objects()
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

		return vMesh.front().fPosition;
	}

	return _float3(0.f, 0.f, 0.f);
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

	return S_OK;
}

void CObject::Free()
{
	__super::Free();

	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pCalculatorCom);
}

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

void CObject::Free()
{
	__super::Free();

	//Safe_Release(m_pShaderCom);
	//Safe_Release(m_pModelCom);
}

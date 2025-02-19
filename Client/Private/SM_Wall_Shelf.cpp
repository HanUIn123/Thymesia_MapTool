#include "pch.h"

#include "SM_Wall_Shelf.h"

CSM_Wall_Shelf::CSM_Wall_Shelf(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CObject(pDevice, pContext)
{
}

CSM_Wall_Shelf::CSM_Wall_Shelf(const CSM_Wall_Shelf& Prototype)
	: CObject(Prototype)
{
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

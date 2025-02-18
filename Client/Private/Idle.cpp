#include "pch.h"
#include "Idle.h"

CIdle::CIdle()
{
}

CIdle::~CIdle()
{
}

HRESULT CIdle::Initialize()
{
	return S_OK;	

}

void CIdle::State_Enter()
{

}

void CIdle::State_Update()
{

}

void CIdle::State_Exit()
{

}


CIdle* CIdle::Create()
{
	CIdle* pInstance = new CIdle();
	
	if(pInstance->Initialize())
	{
		MSG_BOX("Failed to Created : Idle_State");
		Safe_Release(pInstance); 
	}

	return pInstance;
}

void CIdle::Free()
{
	__super::Free();	
}

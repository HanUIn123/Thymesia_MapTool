#include "..\Public\Component.h"
#include "GameInstance.h"

CComponent::CComponent(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: m_pDevice{ pDevice }
	, m_pContext{ pContext }
	, m_pGameInstance{ CGameInstance::GetInstance() }
	, m_isCloned(false)
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

CComponent::CComponent(const CComponent & Prototype)
	: m_pDevice{ Prototype.m_pDevice }
	, m_pContext{ Prototype.m_pContext }
	, m_pGameInstance{ Prototype.m_pGameInstance }
	, m_isCloned(true)
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

HRESULT CComponent::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CComponent::Initialize(void * pArg)
{
	return S_OK;
}

void CComponent::Free()
{
	__super::Free();

	Safe_Release(m_pGameInstance);
	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
}

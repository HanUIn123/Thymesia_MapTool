#include "..\Public\Prototype_Manager.h"
#include "GameObject.h"
#include "Component.h"


CPrototype_Manager::CPrototype_Manager()
{
}

HRESULT CPrototype_Manager::Initialize(_uint iNumLevels)
{
	m_iNumLevels = iNumLevels;

	m_pPrototypes = new PROTOTYPES[iNumLevels];

	return S_OK;
}

HRESULT CPrototype_Manager::Add_Prototype(_uint iLevelIndex, const _wstring & strPrototypeTag, CBase * pPrototype)
{
	if (iLevelIndex >= m_iNumLevels || 
		nullptr != Find_Prototype(iLevelIndex, strPrototypeTag))
		return E_FAIL;

 	m_pPrototypes[iLevelIndex].emplace(strPrototypeTag, pPrototype);

	return S_OK;
}

CBase * CPrototype_Manager::Clone_Prototype(PROTOTYPE eType, _uint iLevelIndex, const _wstring & strPrototypeTag, void * pArg)
{
	CBase*		pPrototype = Find_Prototype(iLevelIndex, strPrototypeTag);
	if (nullptr == pPrototype)
		return nullptr;

	CBase*		pResult = { nullptr };

	if (eType == PROTOTYPE::TYPE_GAMEOBJECT)
		pResult = dynamic_cast<CGameObject*>(pPrototype)->Clone(pArg);
	else
		pResult = dynamic_cast<CComponent*>(pPrototype)->Clone(pArg);

	return pResult;




	/* TODO.삼항연산자의 결과값 두개는 항상 같은 타입으로 리턴되어야한다. */
	/*return eType == PROTOTYPE::TYPE_GAMEOBJECT ? 
		dynamic_cast<CGameObject*>(pPrototype)->Clone(pArg) : 
		dynamic_cast<CComponent*>(pPrototype)->Clone(pArg);*/
	
}

void CPrototype_Manager::Clear(_uint iLevelIndex)
{
	for (auto& Pair : m_pPrototypes[iLevelIndex])	
		Safe_Release(Pair.second);

	m_pPrototypes[iLevelIndex].clear();	
}

CBase * CPrototype_Manager::Find_Prototype(_uint iLevelIndex, const _wstring & strPrototypeTag)
{
	auto	iter = m_pPrototypes[iLevelIndex].find(strPrototypeTag);

	if (iter == m_pPrototypes[iLevelIndex].end())
		return nullptr;

	return iter->second;
}

CPrototype_Manager * CPrototype_Manager::Create(_uint iNumLevels)
{
	CPrototype_Manager*	pInstance = new CPrototype_Manager();

	if (FAILED(pInstance->Initialize(iNumLevels)))
	{
		MSG_BOX("Failed To Created : CPrototype_Manager");
		Safe_Release(pInstance);
	}

	return pInstance;
}
void CPrototype_Manager::Free()
{
	__super::Free();

	for (size_t i = 0; i < m_iNumLevels; i++)
	{
		for (auto& Pair : m_pPrototypes[i])		
			Safe_Release(Pair.second);

		m_pPrototypes[i].clear();		
	}

	Safe_Delete_Array(m_pPrototypes);	
}

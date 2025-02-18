#include "..\Public\Object_Manager.h"
#include "Layer.h"

#include "GameInstance.h"
#include "GameObject.h"
#include "Component.h"


CObject_Manager::CObject_Manager()	
	: m_pGameInstance { CGameInstance::GetInstance() }
{
	Safe_AddRef(m_pGameInstance);
}

HRESULT CObject_Manager::Initialize(_uint iNumLevels)
{
	m_iNumLevels = iNumLevels;

	m_pLayers = new map<const _wstring, CLayer*>[iNumLevels];

	return S_OK;
}

void CObject_Manager::Priority_Update(_float fTimeDelta)
{
	for (size_t i = 0; i < m_iNumLevels; i++)
	{
		for (auto& Pair : m_pLayers[i])
		{
			Pair.second->Priority_Update(fTimeDelta);		
		}
	}
}

void CObject_Manager::Update(_float fTimeDelta)
{
	for (size_t i = 0; i < m_iNumLevels; i++)
	{
		for (auto& Pair : m_pLayers[i])
			Pair.second->Update(fTimeDelta);
	}
}

void CObject_Manager::Late_Update(_float fTimeDelta)
{
	for (size_t i = 0; i < m_iNumLevels; i++)
	{
		for (auto& Pair : m_pLayers[i])
			Pair.second->Late_Update(fTimeDelta);
	}
}

void CObject_Manager::Clear(_uint iLevelIndex)
{
	for (auto& Pair : m_pLayers[iLevelIndex])	
		Safe_Release(Pair.second);

	m_pLayers[iLevelIndex].clear();
}

HRESULT CObject_Manager::Add_GameObject_To_Layer(_uint iPrototypeLevelIndex, const _wstring & strPrototypeTag, _uint iLevelIndex, const _wstring & strLayerTag, void * pArg, _char* pName)
{
	/* 레이어에 추가할 사본객체를 복제해서 가져온다. */
	CGameObject* pGameObject = dynamic_cast<CGameObject*>(m_pGameInstance->Clone_Prototype(PROTOTYPE::TYPE_GAMEOBJECT, iPrototypeLevelIndex, strPrototypeTag, pArg));
	if (nullptr == pGameObject)
		return E_FAIL;

	

	/* 사본객체를 추가할 레이어를 찾자. */
	CLayer*		pLayer = Find_Layer(iLevelIndex, strLayerTag);

	/* 사본객체를 추가할 렝이어가 없었다. \*/
	/* 지정한 레이엉체 최초 추가하기위한 객체였다. */
	/* 그러니까 레이어를 만들어야된다. */
	if (nullptr == pLayer)
	{
		pLayer = CLayer::Create();

		pLayer->Add_GameObject(pGameObject);
		if (pName != nullptr)
			pGameObject->Set_Name(pName);

		m_pLayers[iLevelIndex].emplace(strLayerTag, pLayer);
	}
	else /* 사본객체를 추가할 레이어가 이미 있었다. 그러니까 그 레이어에 그냥 넣으면 되지./ */
	{
		pLayer->Add_GameObject(pGameObject);
		if (pName != nullptr)
			pGameObject->Set_Name(pName);	
	}

	return S_OK;
}

HRESULT CObject_Manager::Sub_GameObject_To_Layer(_uint iLevelIndex, const _wstring& strLayerTag, CGameObject* _pGameObject)	
{
	/* 사본객체를 추가할 레이어를 찾자. */
	CLayer* pLayer = Find_Layer(iLevelIndex, strLayerTag);	

	if (pLayer == nullptr)
		return E_FAIL; 

	list<class CGameObject*>& listGameObject = pLayer->Get_GameObject_List();		

	for (auto& iterator = listGameObject.begin(); iterator != listGameObject.end(); iterator++)
	{
		if (*iterator == _pGameObject)
		{
			listGameObject.erase(iterator);
			Safe_Release(_pGameObject);
			return S_OK;	
		}
	}
	
	return E_FAIL;	
}

CGameObject* CObject_Manager::Get_Player_GameObject_To_Layer(_uint iLevelIndex, const _wstring& strLayerTag)	
{
	
	CLayer* pLayer = Find_Layer(iLevelIndex, strLayerTag);	

	if (pLayer == nullptr)	
		return nullptr;			

	list<class CGameObject*>& listGameObject = pLayer->Get_GameObject_List();
	

	return *listGameObject.begin();		
}

CComponent* CObject_Manager::Find_Component(_uint iLevelIndex, const _wstring& strLayerTag, const _wstring& strComponentName)
{
	/*컴포넌트 들어간 레이어 찾고*/
	CLayer* pLayer = Find_Layer(iLevelIndex, strLayerTag);

	/* 레이어에 있는 게임 오브젝트 찾고*/
	CComponent* pComponents = pLayer->Find_GameObject(strComponentName);	

	if (pComponents != nullptr)	
	{

		return pComponents;	
	}
	/* 게임오브젝트 안에있는 컴포넌트 찾고*/

	return nullptr;	
}

CLayer * CObject_Manager::Find_Layer(_uint iLevelIndex, const _wstring & strLayerTag)
{
	auto	iter = m_pLayers[iLevelIndex].find(strLayerTag);

	if (iter == m_pLayers[iLevelIndex].end())
		return nullptr;

	return iter->second;	
}

CObject_Manager * CObject_Manager::Create(_uint iNumLevels)
{
	CObject_Manager*	pInstance = new CObject_Manager();

	if (FAILED(pInstance->Initialize(iNumLevels)))
	{
		MSG_BOX("Failed To Created : CObject_Manager");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CObject_Manager::Free()
{
	__super::Free();

	for (size_t i = 0; i < m_iNumLevels; i++)
	{
		for (auto& Pair : m_pLayers[i])		
			Safe_Release(Pair.second);

		m_pLayers[i].clear();
	}

	Safe_Delete_Array(m_pLayers);
	Safe_Release(m_pGameInstance);
}

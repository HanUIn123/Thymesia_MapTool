#include "..\Public\Layer.h"
#include "GameObject.h"
#include "Component.h"

CLayer::CLayer()
{
}

void CLayer::Priority_Update(_float fTimeDelta)
{
	for (auto& pGameObject : m_GameObjects)
		pGameObject->Priority_Update(fTimeDelta);
}

void CLayer::Update(_float fTimeDelta)
{
	for (auto& pGameObject : m_GameObjects)
		pGameObject->Update(fTimeDelta);
}

void CLayer::Late_Update(_float fTimeDelta)
{
	for (auto& pGameObject : m_GameObjects)
		pGameObject->Late_Update(fTimeDelta);
}

CComponent* CLayer::Find_GameObject(const wstring& strComponentName)
{
	for (auto& pGameObejct : m_GameObjects)
	{
		for (auto& iter : *(pGameObejct->Get_Components()))
		{
			if (false == lstrcmp(iter.first.c_str(), strComponentName.c_str()))
				return iter.second;
		}
	}

	return nullptr;

}

CLayer * CLayer::Create()
{
	return new CLayer();
}

void CLayer::Free()
{
	__super::Free();

	for (auto& pGameObject : m_GameObjects)
		Safe_Release(pGameObject);

	m_GameObjects.clear();
}

#include "..\Public\Layer.h"
#include "GameObject.h"
#include "Component.h"

CLayer::CLayer()
{
}

HRESULT CLayer::Add_GameObject(CGameObject* _pGameObject, const _wstring& _strProtoTypeTag)
{
	// m_mapGameObjects 에 들어가는 애들 이름이 다 똑같았다. 4마리든 5마리든.. 
	// 그럼, 이 map container 를 이용할 때는,, 그냥 객체 하나! 일 때 만 쓰기. 
	//원래는 너가 생각한 01234 +c_str() 이걸로 차례대로 추가하면 가능할텐데
	// 내가 그 영역을 통달하지 못해서 저렇게 알아서 스트링값이 다르게 저장하는거를 못하겠더라고
	//이게되면 map Container 를 써도될거야

	//저의 얕은 지식 수준으로 인한. 
	//결국 여기서 제가 만든 겟겜옵의 한계가
	//드러난 순간이엇다.. ㅠㅠ.



	_pGameObject->Set_PrototypeTag(_strProtoTypeTag);


	m_mapGameObjects.emplace(_strProtoTypeTag, _pGameObject);
	m_GameObjects.push_back(_pGameObject);

	//m_iObjectsNum++;

	return S_OK;
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

CGameObject* CLayer::Get_GameObject(const _wstring& _strProtoTypeTag)
{
	auto iter = m_mapGameObjects.find(_strProtoTypeTag);
	if (iter != m_mapGameObjects.end())
		return iter->second;

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

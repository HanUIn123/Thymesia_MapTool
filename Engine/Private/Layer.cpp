#include "..\Public\Layer.h"
#include "GameObject.h"
#include "Component.h"

CLayer::CLayer()
{
}

HRESULT CLayer::Add_GameObject(CGameObject* _pGameObject, const _wstring& _strProtoTypeTag)
{
	// m_mapGameObjects �� ���� �ֵ� �̸��� �� �Ȱ��Ҵ�. 4������ 5������.. 
	// �׷�, �� map container �� �̿��� ����,, �׳� ��ü �ϳ�! �� �� �� ����. 
	//������ �ʰ� ������ 01234 +c_str() �̰ɷ� ���ʴ�� �߰��ϸ� �������ٵ�
	// ���� �� ������ ������� ���ؼ� ������ �˾Ƽ� ��Ʈ������ �ٸ��� �����ϴ°Ÿ� ���ϰڴ����
	//�̰ԵǸ� map Container �� �ᵵ�ɰž�

	//���� ���� ���� �������� ����. 
	//�ᱹ ���⼭ ���� ���� �ٰ׿��� �Ѱ谡
	//�巯�� �����̾���.. �Ф�.



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

#pragma once

#include "Base.h"

/*1. 원형객체를 복제하여 == CPrototype_Manager에 추가해놓은 원형객체를 클론하여 오브젝트 매니져에 보관하낟. */
/*2. 보관시에 CLayer클래스에 분류하여 객체들을 저장해놓자. */
/*3. 보관하고 있는 객체들을 반복적으로 Update를 호출해준다. */
/*4. 모아놓은 객체들의 렌더함수를 호출한다.(x) */

BEGIN(Engine)

class CComponent;
class CGameObject; 

class CObject_Manager final : public CBase
{
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	HRESULT Initialize(_uint iNumLevels);
	void Priority_Update(_float fTimeDelta);
	void Update(_float fTimeDelta);
	void Late_Update(_float fTimeDelta);

	void Clear(_uint iLevelIndex);

public:
	/* 원형객체를 찾고 -> 복제하고 -> 지정한 레이어에 추가한다. */
	HRESULT Add_GameObject_To_Layer(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, _uint iLevelIndex, const _wstring& strLayerTag, void* pArg = nullptr, _char* pName = nullptr);	
	HRESULT Sub_GameObject_To_Layer(_uint iLevelIndex, const _wstring& strLayerTag, CGameObject* _pGameObject);		
	CGameObject* Get_Player_GameObject_To_Layer(_uint iLevelIndex, const _wstring& strLayerTag);

	CComponent* Find_Component(_uint iLevelIndex, const _wstring& strLayerTag, const _wstring& strComponentName);

	map<const _wstring, class CLayer*>* Get_Layers()   { return m_pLayers; }	
	_uint								Get_NumLevel() { return m_iNumLevels; }	

private:
	map<const _wstring, class CLayer*>*			m_pLayers = { nullptr };
	_uint										m_iNumLevels = {};

	class CGameInstance*						m_pGameInstance = { nullptr };

private:
	class CLayer* Find_Layer(_uint iLevelIndex, const _wstring& strLayerTag);
	

public:
	static CObject_Manager* Create(_uint iNumLevels);
	virtual void Free() override;
};

END
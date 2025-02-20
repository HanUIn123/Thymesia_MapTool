#pragma once

#include "Base.h"

/* 1.사본 객체들을 분류해놓은 하나의 묶음?  */

BEGIN(Engine)

class CGameObject;	
class CComponent;	

class CLayer final : public CBase
{
private:
	CLayer();
	virtual ~CLayer() = default;

public:
	HRESULT Add_GameObject(class CGameObject* _pGameObject, const _wstring& _strProtoTypeTag);

	void Priority_Update(_float fTimeDelta);
	void Update(_float fTimeDelta);
	void Late_Update(_float fTimeDelta);

	/* 11월 11일 새로만듬*/
	CComponent* Find_GameObject(const wstring& strComponentName);	


public:
	CGameObject* Get_GameObject(const _wstring& _strProtoTypeTag);


public:
	list<CGameObject*>& Get_GameObject_List() { return m_GameObjects; }	

private:
	list<class CGameObject*>			m_GameObjects;

	map<const _wstring, class CGameObject*> m_mapGameObjects;

public:
	static CLayer* Create();
	virtual void Free() override;
};

END
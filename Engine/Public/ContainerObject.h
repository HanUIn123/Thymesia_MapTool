#pragma once

#include "GameObject.h"
#include "PartObject.h"


BEGIN(Engine)

class ENGINE_DLL CContainerObject abstract : public CGameObject
{
public:
	struct CONTAINEROBJECT_DESC : public CGameObject::GAMEOBJECT_DESC 
	{

	};

protected:
	CContainerObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CContainerObject(const CContainerObject& Prototype);
	virtual ~CContainerObject() = default;


public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override; 

protected:
	map<const _wstring, class CPartObject*>   m_PartObjects;


protected:
	HRESULT Add_PartObject(const _wstring& strPartTag, _uint ePrototypeLevelID, const _wstring& strPrototypeTag, CPartObject::PARTOBJECT_DESC* pDesc = nullptr);
	CComponent* Find_PartObject_Component(const _wstring& strPartTag, const _wstring& strComponentTag);


public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override; 

};

END
#pragma once

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CUIObject abstract : public CGameObject
{
public:
	struct UIOBJECT_DESC : public CGameObject::GAMEOBJECT_DESC	
	{
		_float			fX, fY;
		_float			fSizeX, fSizeY;
		_float			fNear, fFar;
		_char*			szName;	
	};

protected:
	CUIObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CUIObject(const CUIObject& Prototype);
	virtual ~CUIObject() = default;

public:
	virtual HRESULT Initialize_Prototype()override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Priority_Update(_float fTimeDelta)override;
	virtual void Update(_float fTimeDelta)override;
	virtual void Late_Update(_float fTimeDelta)override;
	virtual HRESULT Render()override;

protected:
	_float4x4			m_ViewMatrix{}, m_ProjMatrix{};

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END
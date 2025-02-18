#pragma once

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CCamera abstract : public CGameObject
{
public:
	struct CAMERA_DESC : public CGameObject::GAMEOBJECT_DESC	
	{
		_float3			vEye;
		_float3			vAt;
		_float			fFovy;
		_float			fNear;
		_float			fFar;		
	};

protected:
	CCamera(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCamera(const CCamera& Prototype);
	virtual ~CCamera() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	_float				m_fFovy = {};
	_float				m_fNear = {};
	_float				m_fFar = {};
	_float				m_fAspect = {};

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END
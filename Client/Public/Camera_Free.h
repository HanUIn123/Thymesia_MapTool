#pragma once

#include "Client_Defines.h"
#include "Camera.h"

BEGIN(Engine)
class CCollider;
END

BEGIN(Client)

class CCamera_Free final : public CCamera
{
public:
	struct FREE_CAMERA_DESC : public CCamera::CAMERA_DESC
	{
		_float			fMouseSensor = {};
	};

private:
	CCamera_Free(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCamera_Free(const CCamera_Free& Prototype);
	virtual ~CCamera_Free() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	_float*				m_fPlayerPosition = {nullptr};
	_float				m_fMouseSensor = {};
	_bool				m_bStop = false;

	CTransform*			m_pPlayerTransformCom = { false };
	CCollider*			m_pPlayerColliderTransformCom = { false };

	_long			    m_MouseMoveAmount = {};

	_vector				m_vCurCamPos = {};
	_vector				m_vCurCamDir = {};
	_float				m_fLerpTime  = {3.f};		

public:
	static CCamera_Free* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
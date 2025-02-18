#pragma once
#include "Client_Defines.h"
#include "ContainerObject.h"

BEGIN(Engine)
class CModel; /* 루트 모션 때매 추가 */
class CCollider;	
class CNavigation;	
END


BEGIN(Client)

class CPlayer final : public CContainerObject
{
public:
	enum STATE
	{
		STATE_IDLE,
		STATE_WALK,
	};


private:
	CPlayer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CPlayer(const CPlayer& Prototype);
	virtual ~CPlayer() = default; 

public:
	virtual HRESULT Initialize_Prototype() override;	
	virtual HRESULT Initialize(void* pArg) override;	
	virtual void Priority_Update(_float fTimeDelta) override;	
	virtual void Update(_float fTimeDelta) override;	
	virtual void Late_Update(_float fTimeDelta) override;	
	virtual HRESULT Render() override;	
	
public:
	HRESULT Ready_Components();	
	HRESULT Ready_PartObjects();	

private:
	_uint								m_iState         = { STATE_IDLE };
	_uint								m_iPreState		 = { STATE_IDLE };
	



	CNavigation*						m_pNavigationCom = { nullptr };	
	CCollider*							m_pColliderCom   = { nullptr };
	CModel*								m_pModel         = { nullptr };
	const _float4x4*					m_pRootMatrix    = { nullptr };
	const _float4x4*					m_CombinedMatrix = { nullptr };


	_bool								m_bIsRootMotionApplied = { false };
	_float4x4 					        m_CurrentTransformWorldMatrix = {};
	_float4x4 							m_FinalTransformWorldMatrix   = {};	

	_bool								m_bRootMotion  = { false };


	_bool								m_bFalling = { false };
	_bool								m_bGround = { true };


private:


	_float								m_fTimeDelta = { 0.f };



public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
	virtual void OnCollision(CGameObject* _pOther);
	virtual void OnCollisionExit(CGameObject* _pOther);

public:
	static CPlayer* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);	
	virtual CGameObject* Clone(void* pArg) override;	
	virtual void Free() override;	

};

END
#pragma once

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CPartObject abstract : public CGameObject
{
public:
	struct PARTOBJECT_DESC : public CGameObject::GAMEOBJECT_DESC
	{
		const _float4x4* pParentWorldMatrix; 
	};

protected:
	CPartObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CPartObject(const CPartObject& Prototype);
	virtual ~CPartObject() = default; 

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Priority_Update(_float fTimeDelta);
	virtual void Update(_float fTimeDelta);
	virtual void Late_Update(_float fTimeDelta);
	virtual HRESULT Render(); 


protected:
	const _float4x4*				m_pParentWorldMatrix = { nullptr };
	_float4x4						m_CombinedWorldMatrix;
	/* 루트 모션 때매 추가 */
	_float4x4*						m_MotionWorldMatrix = { nullptr };


public:
	virtual CGameObject* Clone(void* pArg) = 0; 
	virtual void Free() override;





};

END
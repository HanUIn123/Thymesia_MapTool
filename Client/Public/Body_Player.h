#pragma once

#include "Client_Defines.h"
#include "PartObject.h"

BEGIN(Engine)
class CShader;
class CModel;
END

BEGIN(Client)

class CBody_Player final : public CPartObject
{
	enum STATE	
	{
		STATE_IDLE    = 0x00000001,	
		STATE_WALK    = 0x00000002,
		STATE_ATTACK  = 0x00000004,	
		STATE_ATTACK2 = 0x00000008,
		STATE_JUMP    = 0x00000010,
		STATE_JUMP2   = 0x00000020,
		STATE_RUN     = 0x00000040,
		STATE_ROLL    = 0x00000080,
		STATE_HURT    = 0x00000100,	
		STATE_FALLING = 0x00000200,
		STATE_PUSH    = 0x00000400,
		STATE_PULL    = 0x00000800,
		STATE_NOGROUND= 0x00001000,
	};

public:
	struct BODY_PLAYER_DESC : public CPartObject::PARTOBJECT_DESC
	{
		_uint* pParentState = { nullptr };	
	};

private:
	CBody_Player(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CBody_Player(const CBody_Player& Prototype);
	virtual ~CBody_Player() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT Render_Shadow() override;

private:
	CShader* m_pShaderCom = { nullptr };
	CModel* m_pModelCom = { nullptr };
	_float							m_fAnimSpeed = 1.f;	


private:
	_uint* m_pParentState = { nullptr };

public:
	HRESULT Ready_Components();
	HRESULT Bind_ShaderResources();

public:
	static CBody_Player* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
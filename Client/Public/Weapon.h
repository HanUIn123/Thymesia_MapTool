#pragma once

#include "Client_Defines.h"
#include "PartObject.h"


BEGIN(Engine)
class CShader;
class CModel;
class CCollider;	

END

class CSwordEffect;
class CHitEffect;

BEGIN(Client)



class CWeapon final : public CPartObject
{
public:
	struct WEAPON_DESC : public CPartObject::PARTOBJECT_DESC
	{
		const _float4x4* pSocketMatrix = { nullptr };	
		const _uint*     pParentState = { nullptr };	
	};
private:
	CWeapon(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CWeapon(const CWeapon& Prototype);
	virtual ~CWeapon() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	CShader*	       m_pShaderCom         = { nullptr };
	CModel*		       m_pModelCom          = { nullptr };
	CCollider*         m_pColliderCom       = { nullptr };
	const _float4x4*   m_pSocketMatrix      = { nullptr };
	float			   m_AccColliderLifeAttack1	= { 0.f };
	float			   m_AccColliderLifeAttack2   = { 0.f };


	CSwordEffect*	   m_pSwordEffect       = { nullptr };


private:
	_float			   m_fTimeDelta = { 0.f };


private:
	const _uint* m_pParentState = { nullptr };	


public:
	HRESULT Ready_Components();
	HRESULT Bind_ShaderResources();

	virtual void OnCollisionEnter(CGameObject* _pOther);
	virtual void OnCollision(CGameObject* _pOther);
	virtual void OnCollisionExit(CGameObject* _pOther);

public:
	static CWeapon* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
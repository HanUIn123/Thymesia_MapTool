#pragma once

#include "Client_Defines.h"
#include "GameObject.h"


BEGIN(Engine)
class CModel;
class CCollider;
class CShader;
class CNavigation;
END

BEGIN(Client)

class CBoss_Magician : public CGameObject
{
private:
	CBoss_Magician(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CBoss_Magician(const CBoss_Magician& Prototype);
	virtual ~CBoss_Magician() = default;
public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT Ready_Components();
	HRESULT Bind_ShaderResources();

private:
	_uint								m_iState = {};
	_uint								m_iPreState = {};

	CNavigation* m_pNavigationCom = { nullptr };
	CCollider* m_pColliderCom = { nullptr };
	CShader* m_pShaderCom = { nullptr };
	CModel* m_pModelCom = { nullptr };
public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
	virtual void OnCollision(CGameObject* _pOther);
	virtual void OnCollisionExit(CGameObject* _pOther);

public:
	static CBoss_Magician* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END
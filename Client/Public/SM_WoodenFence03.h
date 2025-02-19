#pragma once

#include "Object.h"

BEGIN(Client)

class CSM_WoodenFence03 final : public CObject
{
public:
	typedef struct SM_WoodenFence03_Desc : public CObject::OBJECT_DESC
	{

	}CSM_WOODENFENCE03;

private:
	CSM_WoodenFence03(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CSM_WoodenFence03(const CSM_WoodenFence03& Prototype);
	virtual ~CSM_WoodenFence03() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Bind_ShaderResources() override;

public:
	static CSM_WoodenFence03* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END
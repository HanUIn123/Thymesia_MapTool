#pragma once

#include "Object.h"

BEGIN(Client)

class CSM_WoodStairs03 final : public CObject
{
private:
	CSM_WoodStairs03(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CSM_WoodStairs03(const CSM_WoodStairs03& Prototype);
	virtual ~CSM_WoodStairs03() = default;

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
	static CSM_WoodStairs03* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END
#pragma once

#include "Object.h"

BEGIN(Client)

class CHORSE_P_WoodenFrame02_05 final : public CObject
{
public:
	typedef struct HORSE_P_WoodenFrame02_05 : public CObject::OBJECT_DESC
	{

	}HORSE_P_WOODENFRAME02_05;

private:
	CHORSE_P_WoodenFrame02_05(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CHORSE_P_WoodenFrame02_05(const CHORSE_P_WoodenFrame02_05& Prototype);
	virtual ~CHORSE_P_WoodenFrame02_05() = default;

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
	static CHORSE_P_WoodenFrame02_05* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END
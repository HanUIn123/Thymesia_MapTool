#pragma once

#include "Object.h"

BEGIN(Client)

class CSM_Wall_Shelf final : public CObject
{
public:
	typedef struct CSM_Wall_Shelf_Desc : public CObject::OBJECT_DESC
	{

	}CSM_WALL_SHELF_DESC;

private:
	CSM_Wall_Shelf(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CSM_Wall_Shelf(const CSM_Wall_Shelf& Prototype);
	virtual ~CSM_Wall_Shelf() = default;

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
	static CSM_Wall_Shelf* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END
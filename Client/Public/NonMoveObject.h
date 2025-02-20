#pragma once

#include "Object.h"

BEGIN(Client)

class CNonMoveObject final : public CObject
{
public:
	typedef struct NonMoveObjectDesc : public CObject::OBJECT_DESC
	{

	}NONMOVEOBJECTDESC;

private:
	CNonMoveObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CNonMoveObject(const CNonMoveObject& Prototype);
	virtual ~CNonMoveObject() = default;

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
	static CNonMoveObject* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END
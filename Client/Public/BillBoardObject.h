#pragma once

#include "Object.h"

BEGIN(Client)

class CBillBoardObject final : public CObject
{
public:
	typedef struct BillBoardObjectDesc : public CObject::OBJECT_DESC
	{
	}BILLBOARDOBJECTDESC;

private:
	CBillBoardObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CBillBoardObject(const CBillBoardObject& Prototype);
	virtual ~CBillBoardObject() = default;

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

	void BillBoard();
	HRESULT Bind_ShaderResourcesForBillBoard();

public:
	static CBillBoardObject* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

private:
	const _float4x4* m_pOriginalMatrix = {};

};

END
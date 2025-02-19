#pragma once

#include "Object.h"

BEGIN(Client)

class CP_Rag03 final : public CObject
{
public:
	typedef struct P_Rag03_Desc : public CObject::OBJECT_DESC
	{

	}P_RAG03_DESC;

private:
	CP_Rag03(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CP_Rag03(const CP_Rag03& Prototype);
	virtual ~CP_Rag03() = default;

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
	static CP_Rag03* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END
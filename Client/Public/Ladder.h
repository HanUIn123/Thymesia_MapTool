#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CModel; /* 루트 모션 때매 추가 */
class CShader;
END


BEGIN(Client)
class CLadder final : public CGameObject
{
private:
	CLadder(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CLadder(const CLadder& Prototype);
	virtual ~CLadder() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT Ready_Components();
	HRESULT	Bind_ShaderResources();

	CModel* m_pModelCom = { nullptr };
	CShader* m_pShaderCom = { nullptr };


public:
	static CLadder* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};
END
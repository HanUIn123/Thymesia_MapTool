#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "TempManager.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CTransform;
class CVIBuffer_Terrain;
class CNavigation;
END

BEGIN(Client)

class CTerrain final : public CGameObject
{
private:
	CTerrain(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CTerrain(const CTerrain& Prototype);
	virtual ~CTerrain() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void	Set_TerrainPickPos(_float3 _fPickPos, _float _fRange);
	void	Set_Brushing(_bool _bBrushing) { m_bBrushing = _bBrushing; }
private:
	CShader* m_pShaderCom = { nullptr };
	CTexture* m_pTextureCom = { nullptr };
	CTexture* m_pMouseTextureCom = { nullptr };
	CVIBuffer_Terrain* m_pVIBufferCom = { nullptr };
	CNavigation* m_pNavigationCom = { nullptr };

private:
	_float                          m_fRange = {};
	_float3                         m_fPickPos = {};
	_bool							m_bBrushing = { false };


public:
	HRESULT Ready_Components();
	HRESULT Bind_ShaderResources();

public:
	static CTerrain* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
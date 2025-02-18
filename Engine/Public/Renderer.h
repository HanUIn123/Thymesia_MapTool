#pragma once

#include "Base.h"

/* 1.화면에ㅐ 그려져야할 객체들을 모아둔다.  */
/* 1_1. 내가 그리고자하는 순서대로 객체들을 분류하여 모아둔다. */

/* 2.순서대로 모아놓은 객체들을 저장해놓은 순서대로 돌면서 렌더함수를 호출(렌더콜, 드로우콜)해준다. */

BEGIN(Engine)

class CRenderer final : public CBase
{
public:
	enum RENDERGROUP { RG_PRIORITY, RG_SHADOW, RG_NONBLEND, RG_NONLIGHT, RG_BLEND, RG_UI, RG_BLUR, RG_END };	
	
private:
	CRenderer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CRenderer() = default;

public:
	HRESULT Initialize();
	HRESULT Add_RenderGroup(RENDERGROUP eRenderGroupID, class CGameObject* pGameObject);
	HRESULT Render();

private:
	ID3D11Device*					m_pDevice = { nullptr };
	ID3D11DeviceContext*			m_pContext = { nullptr };
	class CGameInstance*			m_pGameInstance = { nullptr };
	list<class CGameObject*>		m_RenderObjects[RG_END];

	class CShader*		  m_pShader    = { nullptr };
	class CVIBuffer_Rect* m_pVIBuffer  = { nullptr };

	_float4x4		      m_WorldMatrix{}, m_ViewMatrix{}, m_ProjMatrix{};
	_float4x4		      m_BlurWorldMatrix{}, m_BlurViewMatrix{}, m_BlurProjMatrix{};

	ID3D11DepthStencilView* m_pShadowDSV = { nullptr };	

	_uint					m_iOriginalViewportWidth{}, m_iOriginalViewportHeight{};		

private:
	HRESULT Render_Priority();
	HRESULT Render_Shadow();	
	HRESULT Render_NonBlend();
	HRESULT Render_NonLight();
	HRESULT Render_LightAcc();
	HRESULT Render_Deferred();
	HRESULT Render_BlurBegin();
	HRESULT Render_BlurX();
	HRESULT Render_BlurY();
	HRESULT Render_Final();
	HRESULT Render_Blend();
	HRESULT Render_UI();
	

private:
	HRESULT Ready_Depth_Stencil_Buffer(_uint iWidth, _uint iHeight, ID3D11DepthStencilView** ppOut);	
	HRESULT SetUp_ViewportDesc(_uint iWidth, _uint iHeight);	


#ifdef _DEBUG
private:
	HRESULT Render_Debug();

#endif

public:
	static CRenderer* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual void Free() override;
};

END
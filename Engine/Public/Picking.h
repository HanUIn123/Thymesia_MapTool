#pragma once
#include "Base.h"

BEGIN(Engine)
class CPicking final : public CBase
{
private:
	CPicking(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext);
	virtual ~CPicking() = default;

public:
	HRESULT							Initialize(HWND _hWnd);
	void							Update();
	_bool							Compute_PickPos(_float3* _pOut);

private:
	HWND							m_hWnd = {};
	_float							m_fViewportWidth, m_fViewportHeight;

	ID3D11Device* m_pDevice = { nullptr };
	ID3D11DeviceContext* m_pContext = { nullptr };

	/* 픽킹을 위한 픽셀의 깊이를 저장해놓았던 렌더타겟텍스쳐(map, unmap이 안되니깐)를 복사하여 저장하는 텍스쳐 정보. */
	ID3D11Texture2D* m_pTexture2D = { nullptr };

	class CGameInstance* m_pGameInstance = { nullptr };

public:
	static CPicking* Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext, HWND _hWnd);
	virtual void					Free() override;
};

END
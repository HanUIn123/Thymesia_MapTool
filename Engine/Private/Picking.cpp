#include "Picking.h"
#include "GameInstance.h"

CPicking::CPicking(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
	:m_pDevice{ _pDevice }
	, m_pContext{ _pContext }
	, m_pGameInstance{ CGameInstance::GetInstance() }
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

HRESULT CPicking::Initialize(HWND _hWnd)
{
	m_hWnd = _hWnd;

	D3D11_TEXTURE2D_DESC			TextureDesc{};

	_uint							iNumViewports = { 1 };
	D3D11_VIEWPORT					ViewportDesc{};

	m_pContext->RSGetViewports(&iNumViewports, &ViewportDesc);

	m_fViewportWidth = ViewportDesc.Width;
	m_fViewportHeight = ViewportDesc.Height;

	TextureDesc.Width = (UINT)ViewportDesc.Width;
	TextureDesc.Height = (UINT)ViewportDesc.Height;
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	// 부동소수점 정밀도 포맷값 float4 로 
	TextureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	TextureDesc.SampleDesc.Quality = 0;
	TextureDesc.SampleDesc.Count = 1;
	TextureDesc.Usage = D3D11_USAGE_STAGING;
	TextureDesc.BindFlags = 0;
	TextureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	TextureDesc.MiscFlags = 0;

	if (FAILED(m_pDevice->CreateTexture2D(&TextureDesc, nullptr, &m_pTexture2D)))
		return E_FAIL;

	return S_OK;
}

void CPicking::Update()
{
	m_pGameInstance->Copy_RenderTarget_TextureResource(TEXT("Target_PickDepth"), m_pTexture2D);
}

_bool CPicking::Compute_PickPos(_float3* _pOut)
{
	POINT		ptMouse;

	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);

	D3D11_MAPPED_SUBRESOURCE	SubResource{};

	m_pContext->Map(m_pTexture2D, 0, D3D11_MAP_READ_WRITE, 0, &SubResource);

	_uint		iPixelIndex = (_uint)(ptMouse.y * m_fViewportWidth + ptMouse.x);

	_float4		vDepthDesc = static_cast<_float4*>(SubResource.pData)[iPixelIndex];

	m_pContext->Unmap(m_pTexture2D, 0);

	if (0.f == vDepthDesc.z)
		return false;

	_vector			vWorldPos = XMVectorSet((_float)ptMouse.x, (_float)ptMouse.y, 0.f, 0.f);

	vWorldPos = XMVectorSetX(vWorldPos, ptMouse.x / (m_fViewportWidth * 0.5f) - 1.f);
	vWorldPos = XMVectorSetY(vWorldPos, ptMouse.y / (m_fViewportHeight * -0.5f) + 1.f);
	vWorldPos = XMVectorSetZ(vWorldPos, vDepthDesc.x);
	vWorldPos = XMVectorSetW(vWorldPos, 1.f);

	vWorldPos = XMVector3TransformCoord(vWorldPos, m_pGameInstance->Get_Transform_Matrix_Inverse(CPipeLine::D3DTS_PROJ));
	vWorldPos = XMVector3TransformCoord(vWorldPos, m_pGameInstance->Get_Transform_Matrix_Inverse(CPipeLine::D3DTS_VIEW));

	XMStoreFloat3(_pOut, vWorldPos);

	return true;
}

CPicking* CPicking::Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext, HWND _hWnd)
{
	CPicking* pInstance = new CPicking(_pDevice, _pContext);

	if (FAILED(pInstance->Initialize(_hWnd)))
	{
		MSG_BOX("Failed To Created : CPicking");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPicking::Free()
{
	__super::Free();

	Safe_Release(m_pTexture2D);

	Safe_Release(m_pGameInstance);
	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
}

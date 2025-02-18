#pragma once

#include "Base.h"

BEGIN(Engine)

/* 1. ID3D11Device, ID3D11DeviceContext라는 객체를 우선 생성한다. */
/* 2. IDXGISwapChain를 생성한다.(백버퍼(ID3D11Texture2D)도 같이 생성한거야.) */
/* 3. 백버퍼뷰를 생성한다. */
/* 4. 깊이버퍼 텍스쳐를 생성하고 깊이버퍼 뷰를 생성한다. */

class CGraphic_Device final : public CBase
{	
private:
	CGraphic_Device();
	virtual ~CGraphic_Device() = default;

public:
	/* 그래픽 디바이스의 초기화. */
	HRESULT Initialize(HWND hWnd, _bool isWindowed, _uint iWinSizeX, _uint iWinSizeY,
		_Inout_ ID3D11Device** ppDevice, _Inout_ ID3D11DeviceContext** ppContext);
	/* 백버퍼를 지운다. */
	HRESULT Clear_BackBuffer_View(_float4 vClearColor);
	/* 깊이버퍼 + 스텐실버퍼를 지운다. */
	HRESULT Clear_DepthStencil_View();
	
	/* 후면 버퍼를 전면버퍼로 교체한다.(백버퍼를 화면에 직접 보여준다.) */
	HRESULT Present();

private:	
	// IDirect3DDevice9* == LPDIRECT3DDEVICE9 == ID3D11Device + ID3D11DeviceContext 	

	/* 스레드를 생성한다 : 내 코드를 읽는 흐름을 하나 더 만들어주낟. */
	/* 내 코드를 읽는 프로세스가 두개구나. (X) */
	/* 하나의 프로세스로 읽는 흐름을 다수 생성하는 작업(O) */
	/* 메인 스레드가 출력시에 메인스레드는 논다. 이 때 놀고 있는 메인스레드로 다른 역활을 좀더 수행하고싶다.(추가 스레드를 생성하여 처리하는것이다.)*/


	/* 리소스 로드 및 출력. */
	/* 연산. */


	/* 메모리 할당. (정점버퍼, 인덱스버퍼, 텍스쳐로드, 쉐이더객체를 생성한다. ) 컴객체의 생성과 관련된 역할 */
	/* 추가적으로 생성된 모든 스레드에서 사용하는데 전혀 문제가 없다. */
	ID3D11Device*				m_pDevice = { nullptr };
		
	/* 기능실행.(바인딩작업, 정점버퍼를 SetVertexBuffers(), SetIndexBuffer(), Apply() */
	/* 그린다. DrawIndexed() */
	/* 컨텍스트 객체를 생성해낸 스레드 외에 스레드에서는 사용해서는 안된다. */
	/* 고정기능렌더링파이프라인 : 월드, 뷰, 투영행렬을 바인딩 + 텍스쳐 정보를 바인딩. */

	/* 생성된 스레드로 그리면 안돼?(X) */
	ID3D11DeviceContext*		m_pDeviceContext = { nullptr };

	/* 후면버퍼와 전면버퍼를 교체해가면서 화면에 보여주는 역할 */
	IDXGISwapChain*				m_pSwapChain = { nullptr };


	/* IDirect3DTexture9 */
	/* ID3D11Texture2D : 텍스쳐를 표현하는 사전객체 타입이다. 실제 이 타입으로는 아무 역활도 못함. 
	why? 용도에 맞는 실질적으로 사용하기 위한 텍스쳐객체를 만들어내기위해.  */	
	/* ID3D11Texture2D를 통해 픽셀의 락언락을 통해 색을 강제로 바꾸거나 파일로 출력하거나 등등의 일은 가능 */
	/* ID3D11Texture2D를 통해 픽셀의 색을 샘플링해서 화면에 그리는 작업(x), 렌더타겟용으로 사용(x), 깊이 버퍼용으로 사용(x)  */

	/* dx11에선느 실제 사용하기위한 텍스쳐타입뒤에 View를 붙여놨다. */
	/* ID3D11ShaderResourceView : 셰이더에 전달될 수 있는 텍스처 타입. */	
	/* ID3D11RenderTargetView : 렌더타겟용으로 사용될 수 있는 텍스처 타입. */
	/* ID3D11DepthStencilView : 깊이스텐실 버퍼로서 사용될 수 있는 타입.  */
	ID3D11RenderTargetView*		m_pBackBufferRTV = { nullptr };	
	ID3D11DepthStencilView*		m_pDepthStencilView = { nullptr };

private:
	/* 스왑체인에게 필수적으로 필요한 데이터는 백버퍼가 필요하여 백버퍼를 생성하기위한 정보를 던져준다. */
	/* 스왑체인을 만들었다 == 백버퍼(텍스쳐)가 생성된다. */
	HRESULT Ready_SwapChain(HWND hWnd, _bool isWindowed, _uint iWinCX, _uint iWinCY);
	HRESULT Ready_BackBufferRenderTargetView();	
	HRESULT Ready_DepthStencilView(_uint iWinCX, _uint iWinCY);

public:
	static CGraphic_Device* Create(HWND hWnd, _bool isWindowed, _uint iViewportWidth, _uint iViewportHeight, 
		_Inout_ ID3D11Device** ppDevice,
		_Inout_ ID3D11DeviceContext** ppDeviceContextOut);
	virtual void Free() override;
};

END
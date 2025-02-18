#include "..\Public\VIBuffer.h"

CVIBuffer::CVIBuffer(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CComponent { pDevice, pContext }
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & Prototype)
	: CComponent(Prototype)
	, m_pVB { Prototype.m_pVB }
	, m_pIB { Prototype.m_pIB }
	, m_iNumVertices { Prototype.m_iNumVertices}
	, m_iVertexStride { Prototype.m_iVertexStride}
	, m_iNumIndices { Prototype.m_iNumIndices }
	, m_iIndexStride { Prototype.m_iIndexStride }
	, m_iNumVertexBuffers { Prototype.m_iNumVertexBuffers }
	, m_eIndexFormat { Prototype.m_eIndexFormat }
	, m_ePrimitiveTopology { Prototype.m_ePrimitiveTopology}
{
	Safe_AddRef(m_pVB);
	Safe_AddRef(m_pIB);
}

HRESULT CVIBuffer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CVIBuffer::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CVIBuffer::Bind_InputAssembler()
{
	if (nullptr == m_pContext)
		return E_FAIL;

	ID3D11Buffer*		pVertexBuffer[] = {
		m_pVB, 		
	};

	_uint				iVertexStrides[] = {
		m_iVertexStride, 
	};

	_uint				iOffsets[] = {
		0
	};


	m_pContext->IASetVertexBuffers(0, m_iNumVertexBuffers, pVertexBuffer, iVertexStrides, iOffsets);
	m_pContext->IASetIndexBuffer(m_pIB, m_eIndexFormat, 0);
	m_pContext->IASetPrimitiveTopology(m_ePrimitiveTopology);	

	

	return S_OK;
}

HRESULT CVIBuffer::Render()
{
	if (nullptr == m_pContext)
		return E_FAIL;

	m_pContext->DrawIndexed(m_iNumIndices, 0, 0);	

	return S_OK;
}

HRESULT CVIBuffer::Render_NumIndices(_uint _NumIndices)	
{
	if (nullptr == m_pContext)
		return E_FAIL;

	m_pContext->DrawIndexed(_NumIndices, 0, 0);	 

	return S_OK;
}

HRESULT CVIBuffer::Create_Buffer(ID3D11Buffer ** ppOut)
{
	// D3D11_BUFFER_DESC : 내가 지금 만들고자하는 버퍼의 속성을 설정해달라(할당하고자하는 크기, 동적 or 정적, );
	// D3D11_SUBRESOURCE_DATA : 내가 지금 만드는 공간에 채워줄 초기 값 ;
	return m_pDevice->CreateBuffer(&m_BufferDesc, &m_InitialData, ppOut);	
}

HRESULT CVIBuffer::Create_BufferZ(ID3D11Buffer** ppVIBuffer, D3D11_BUFFER_DESC* meshbuffer)
{
	if (FAILED(m_pDevice->CreateBuffer(meshbuffer, &m_InitialData, ppVIBuffer)))	
		return E_FAIL;	

	return S_OK;	
}

void CVIBuffer::Free()
{
	__super::Free();

	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
}

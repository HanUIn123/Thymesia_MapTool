#pragma once

#include "Component.h"

/* VIBuffer = Vertex, Index Buffer*/
/* 기타 구체적인 정점인덱스버퍼(ex.CVIBuffer_Rect)의 부모가 되는 클래스다. */


BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVIBuffer(const CVIBuffer& Prototype);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Bind_InputAssembler();
	virtual HRESULT Render();
	virtual HRESULT Render_NumIndices(_uint _NumIndices);	



	ID3D11Buffer* Get_VB_Buffer() { return m_pVB; }	
	ID3D11Buffer* Get_IB_Buffer() { return m_pIB; }	
	_uint		  Get_NumVertices() { return m_iNumVertices; }	
	_uint		  Get_NumIndices() { return m_iNumIndices; }	

	_uint& Get_Width_X() { return m_iCntX; }
	_uint& Get_Height_Z() { return m_iCntY; }


protected:
	ID3D11Buffer*					m_pVB = { nullptr };
	ID3D11Buffer*					m_pIB = { nullptr };

	D3D11_BUFFER_DESC				m_BufferDesc = {};
	D3D11_SUBRESOURCE_DATA			m_InitialData = {};

protected:
	D3D11_PRIMITIVE_TOPOLOGY		m_ePrimitiveTopology = {};	
	DXGI_FORMAT						m_eIndexFormat = {};
	_uint							m_iNumVertexBuffers = {};
	_uint							m_iNumVertices = {};
	_uint							m_iVertexStride = {};
	_uint							m_iNumIndices = {};
	_uint							m_iIndexStride = {};
	_uint							m_iNumPrimitive = { 0 };	


	_float4* m_pVertexPositions = { nullptr };

	/* 점 개수들 */
	_uint                    m_iCntX = { 0 };
	_uint                    m_iCntY = { 0 };

protected:
	HRESULT Create_Buffer(ID3D11Buffer** ppOut);
	HRESULT Create_BufferZ(ID3D11Buffer** ppVIBuffer, D3D11_BUFFER_DESC* meshbuffer);


public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free();
};

END
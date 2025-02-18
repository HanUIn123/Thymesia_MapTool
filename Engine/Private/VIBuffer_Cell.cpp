#include "VIBuffer_Cell.h"

CVIBuffer_Cell::CVIBuffer_Cell(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CVIBuffer(pDevice,pContext)	
{
}

CVIBuffer_Cell::CVIBuffer_Cell(const CVIBuffer_Cell& Prototype)
	:CVIBuffer(Prototype)
{
}

HRESULT CVIBuffer_Cell::Initialize_Prototype(const _float3* pPoints)
{
	m_iNumVertices = 3;
	m_iVertexStride = sizeof(VTXPOS);
	m_iNumIndices = 4; 
	m_iIndexStride = 2;
	m_iNumVertexBuffers = 1;
	m_eIndexFormat = DXGI_FORMAT_R16_UINT;
	m_ePrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;

#pragma region VERTEX_BUFFER 
	ZeroMemory(&m_BufferDesc, sizeof(m_BufferDesc));
	m_BufferDesc.ByteWidth = m_iNumVertices * m_iVertexStride;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDesc.StructureByteStride = m_iVertexStride;
	m_BufferDesc.CPUAccessFlags = 0; 
	m_BufferDesc.MiscFlags = 0; 

	VTXPOS* pVertices = new VTXPOS[m_iNumVertices];
	ZeroMemory(pVertices, sizeof(VTXPOS) * m_iNumVertices);

	memcpy(pVertices, pPoints, sizeof(_float3) * 3);

	ZeroMemory(&m_InitialData, sizeof(m_InitialData));	
	m_InitialData.pSysMem = pVertices;	

	if (FAILED(__super::Create_Buffer(&m_pVB)))
		return E_FAIL;
	
	Safe_Delete_Array(pVertices);

#pragma endregion

#pragma region INDEX_BUFFER
	ZeroMemory(&m_BufferDesc, sizeof(m_BufferDesc));
	m_BufferDesc.ByteWidth = m_iNumIndices * m_iIndexStride; 
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_BufferDesc.StructureByteStride = m_iIndexStride;	
	m_BufferDesc.CPUAccessFlags = 0;	
	m_BufferDesc.MiscFlags = 0;	

	_ushort*   pIndices = new _ushort[m_iNumIndices];
	ZeroMemory(pIndices, sizeof(_ushort) * m_iNumIndices);	

	pIndices[0] = 0; 
	pIndices[1] = 1; 
	pIndices[2] = 2; 
	pIndices[3] = 0; 

	ZeroMemory(&m_InitialData, sizeof(m_InitialData));
	m_InitialData.pSysMem = pIndices; 

	if (FAILED(__super::Create_Buffer(&m_pIB)))
		return E_FAIL;


	Safe_Delete_Array(pIndices);
#pragma endregion


	return S_OK;
}

HRESULT CVIBuffer_Cell::Initialize(void* pArg)
{
	return S_OK;
}

CVIBuffer_Cell* CVIBuffer_Cell::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const _float3* pPoints)
{
	CVIBuffer_Cell* pInstance = new CVIBuffer_Cell(pDevice, pContext);

	if(FAILED(pInstance->Initialize_Prototype(pPoints)))
	{
		MSG_BOX("Failed to Created : VIBuffer_Cell");
		Safe_Release(pInstance);
	}

	return pInstance;	
}

CComponent* CVIBuffer_Cell::Clone(void* pArg)
{
	CVIBuffer_Cell* pInstance = new CVIBuffer_Cell(*this);

	if(FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : VIBuffer_Cell");
		Safe_Release(pInstance);
	}
	
	return pInstance;
}

void CVIBuffer_Cell::Free()
{
	__super::Free();
}

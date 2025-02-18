#include "VIBuffer_Cube.h"

CVIBuffer_Cube::CVIBuffer_Cube(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CVIBuffer{ pDevice, pContext }
{

}

CVIBuffer_Cube::CVIBuffer_Cube(const CVIBuffer_Cube& Prototype)
	: CVIBuffer(Prototype)
{

}

HRESULT CVIBuffer_Cube::Initialize_Prototype()
{
	m_iNumVertices = 8;
	m_iVertexStride = sizeof(VTXCUBE);
	m_iNumIndices = 36;
	m_iIndexStride = 2;
	m_iNumVertexBuffers = 1;
	m_eIndexFormat = DXGI_FORMAT_R16_UINT;
	m_ePrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

#pragma region VERTEX_BUFFER
	ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);
	m_BufferDesc.ByteWidth = m_iNumVertices * m_iVertexStride;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDesc.StructureByteStride = m_iVertexStride;
	m_BufferDesc.CPUAccessFlags = 0;
	m_BufferDesc.MiscFlags = 0;

	VTXCUBE* pVertices = new VTXCUBE[m_iNumVertices];
	ZeroMemory(pVertices, sizeof(VTXCUBE) * m_iNumVertices);

	pVertices[0].vPosition = _float3(-1.f, 1.f, -1.f);
	pVertices[0].vTexcoord = pVertices[0].vPosition;

	pVertices[1].vPosition = _float3(1.f, 1.f, -1.f);
	pVertices[1].vTexcoord = pVertices[1].vPosition;

	pVertices[2].vPosition = _float3(1.f, -1.f, -1.f);
	pVertices[2].vTexcoord = pVertices[2].vPosition;

	pVertices[3].vPosition = _float3(-1.f, -1.f, -1.f);
	pVertices[3].vTexcoord = pVertices[3].vPosition;

	// ÈÄ¸é
	pVertices[4].vPosition = _float3(-1.f, 1.f, 1.f);
	pVertices[4].vTexcoord = pVertices[4].vPosition;

	pVertices[5].vPosition = _float3(1.f, 1.f, 1.f);
	pVertices[5].vTexcoord = pVertices[5].vPosition;

	pVertices[6].vPosition = _float3(1.f, -1.f, 1.f);
	pVertices[6].vTexcoord = pVertices[6].vPosition;

	pVertices[7].vPosition = _float3(-1.f, -1.f, 1.f);
	pVertices[7].vTexcoord = pVertices[7].vPosition;


	ZeroMemory(&m_InitialData, sizeof m_InitialData);
	m_InitialData.pSysMem = pVertices;

	if (FAILED(__super::Create_Buffer(&m_pVB)))
		return E_FAIL;

	Safe_Delete_Array(pVertices);
#pragma endregion


#pragma region INDEX_BUFFER
	ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);
	m_BufferDesc.ByteWidth = m_iNumIndices * m_iIndexStride;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_BufferDesc.StructureByteStride = m_iIndexStride;
	m_BufferDesc.CPUAccessFlags = 0;
	m_BufferDesc.MiscFlags = 0;

	_ushort* pIndices = new _ushort[m_iNumIndices];
	ZeroMemory(pIndices, sizeof(_ushort) * m_iNumIndices);


	pIndices[0] = 1; pIndices[1] = 5; pIndices[2] = 6;
	pIndices[3] = 1; pIndices[4] = 6; pIndices[5] = 2;

	pIndices[6] = 4; pIndices[7] = 0; pIndices[8] = 3;
	pIndices[9] = 4; pIndices[10] = 3; pIndices[11] = 7;


	pIndices[12] = 4; pIndices[13] = 5; pIndices[14] = 1;
	pIndices[15] = 4; pIndices[16] = 1; pIndices[17] = 0;


	pIndices[18] = 3; pIndices[19] = 2; pIndices[20] = 6;
	pIndices[21] = 3; pIndices[22] = 6; pIndices[23] = 7;


	pIndices[24] = 7; pIndices[25] = 6; pIndices[26] = 5;
	pIndices[27] = 7; pIndices[28] = 5; pIndices[29] = 4;


	pIndices[30] = 0; pIndices[31] = 1; pIndices[32] = 2;
	pIndices[33] = 0; pIndices[34] = 2; pIndices[35] = 3;

	ZeroMemory(&m_InitialData, sizeof m_InitialData);
	m_InitialData.pSysMem = pIndices;

	if (FAILED(__super::Create_Buffer(&m_pIB)))
		return E_FAIL;

	Safe_Delete_Array(pIndices);
#pragma endregion

	return S_OK;
}

HRESULT CVIBuffer_Cube::Initialize(void* pArg)
{
	return S_OK;
}

CVIBuffer_Cube* CVIBuffer_Cube::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CVIBuffer_Cube* pInstance = new CVIBuffer_Cube(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed To Created : CVIBuffer_Cube");
		Safe_Release(pInstance);
	}

	return pInstance;
}


CComponent* CVIBuffer_Cube::Clone(void* pArg)
{
	CVIBuffer_Cube* pInstance = new CVIBuffer_Cube(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Created : CVIBuffer_Cube");
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CVIBuffer_Cube::Free()
{
	__super::Free();


}

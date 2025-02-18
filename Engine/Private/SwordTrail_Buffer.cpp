#include "SwordTrail_Buffer.h"

CSwordTrail_Buffer::CSwordTrail_Buffer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CVIBuffer{ pDevice, pContext }
{

}

CSwordTrail_Buffer::CSwordTrail_Buffer(const CSwordTrail_Buffer& Prototype)
	: CVIBuffer(Prototype)	
{

}

HRESULT CSwordTrail_Buffer::Initialize_Prototype()
{
	m_iNumVertices = 4;
	m_iVertexStride = sizeof(VTXPOSTEXAGE);			
	m_iNumIndices = 6;
	m_iIndexStride = 4;
	m_iNumVertexBuffers = 1;	
	m_eIndexFormat = DXGI_FORMAT_R32_UINT;
	m_ePrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

#pragma region VERTEX_BUFFER
	ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);
	m_BufferDesc.ByteWidth = m_iNumVertices * m_iVertexStride * 10000;	
	m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;		
	m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	
	m_BufferDesc.StructureByteStride = m_iVertexStride;	
	m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	
	m_BufferDesc.MiscFlags = 0;

	VTXPOSTEXAGE* pVertices = new VTXPOSTEXAGE[m_iNumVertices * 10000];
	ZeroMemory(pVertices, sizeof(VTXPOSTEXAGE) * m_iNumVertices * 10000);

	/*pVertices[0].vPosition = _float3(-0.5f, 0.5f, 0.f);
	pVertices[0].vTexcoord = _float2(0.f, 0.f);

	pVertices[1].vPosition = _float3(0.5f, 0.5f, 0.f);
	pVertices[1].vTexcoord = _float2(1.f, 0.f);

	pVertices[2].vPosition = _float3(0.5f, -0.5f, 0.f);
	pVertices[2].vTexcoord = _float2(1.f, 1.f);

	pVertices[3].vPosition = _float3(-0.5f, -0.5f, 0.f);
	pVertices[3].vTexcoord = _float2(0.f, 1.f);*/

	ZeroMemory(&m_InitialData, sizeof m_InitialData);
	m_InitialData.pSysMem = pVertices;

	if (FAILED(__super::Create_Buffer(&m_pVB)))
		return E_FAIL;

	Safe_Delete_Array(pVertices);
#pragma endregion


#pragma region INDEX_BUFFER
	ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);
	m_BufferDesc.ByteWidth = m_iNumIndices * m_iIndexStride * 10000;
	m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;	
	m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_BufferDesc.StructureByteStride = m_iIndexStride;
	m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	
	m_BufferDesc.MiscFlags = 0;

	_uint* pIndices = new _uint[m_iNumIndices * 10000];	
	ZeroMemory(pIndices, sizeof(_uint) * m_iNumIndices * 10000);

	//pIndices[0] = 0;
	//pIndices[1] = 1;
	//pIndices[2] = 2;

	//pIndices[3] = 0;
	//pIndices[4] = 2;
	//pIndices[5] = 3;

	ZeroMemory(&m_InitialData, sizeof m_InitialData);
	m_InitialData.pSysMem = pIndices;

	if (FAILED(__super::Create_Buffer(&m_pIB)))
		return E_FAIL;

	Safe_Delete_Array(pIndices);
#pragma endregion

	return S_OK;
}

HRESULT CSwordTrail_Buffer::Initialize(void* pArg)
{
	return S_OK;
}

CSwordTrail_Buffer* CSwordTrail_Buffer::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CSwordTrail_Buffer* pInstance = new CSwordTrail_Buffer(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed To Created : CSwordTrail_Buffer");
		Safe_Release(pInstance);
	}

	return pInstance;
}


CComponent* CSwordTrail_Buffer::Clone(void* pArg)
{
	CSwordTrail_Buffer* pInstance = new CSwordTrail_Buffer(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Created : CSwordTrail_Buffer");
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CSwordTrail_Buffer::Free()
{
	__super::Free();


}

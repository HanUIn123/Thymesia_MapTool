#include "VIBuffer_Terrain.h"

CVIBuffer_Terrain::CVIBuffer_Terrain(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CVIBuffer(pDevice, pContext)
{

}

CVIBuffer_Terrain::CVIBuffer_Terrain(const CVIBuffer_Terrain& Prototype)
	:CVIBuffer(Prototype)

{

}

HRESULT CVIBuffer_Terrain::Initialize_Prototype(const _uint dwCntX, const  _uint dwCntZ, _uint dwVertexItv, const _tchar* path)
{
	/* 버텍스버퍼와 인덱스 버퍼의 정보*/
	m_ePrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_eIndexFormat = DXGI_FORMAT_R32_UINT;
	m_iNumVertexBuffers = 1;
	m_iVertexStride = sizeof(VTXNORTEX);
	m_iNumVertices = dwCntX * dwCntZ;
	m_iIndexStride = 4;
	m_iNumIndices = (dwCntX - 1) * (dwCntZ - 1) * 2 * 3;

	m_iCntX = dwCntX;
	m_iCntY = dwCntZ;

	/* 그러면 내가 해야할 일이 VTXNORTEX에 있는 POSITION, NORAML , Texcoord 내용 채워주기*/

	VTXNORTEX* pVertices = new VTXNORTEX[m_iNumVertices];

	/*이제 여기서 버텍스 정보 넣어줘야하는데. 일단 path가 있는지부터 확인하자*/

	if (nullptr == path)
	{

		/* 버텍스 정보 넣어주기 */
		for (size_t i = 0; i < dwCntZ; i++)
		{
			for (size_t j = 0; j < dwCntX; j++)
			{
				pVertices[dwCntZ * i + j].vPosition = _float3(j * dwVertexItv, 0.f, i);
				pVertices[dwCntZ * i + j].vNormal = _float3(0.f, 1.f, 0.f);
				pVertices[dwCntZ * i + j].vTexcoord = _float2(j * dwVertexItv / (dwCntX - 1.f), i / (dwCntZ - 1.f));
			}
		}

		/* 만든 버텍스 데이터 다시 이제 그래픽장치에 넣어주기
		   CPU 만 알고있는 메모리 이므로 */

		ZeroMemory(&m_InitialData, sizeof(D3D11_SUBRESOURCE_DATA));
		m_InitialData.pSysMem = pVertices;


		/* 버텍스 버퍼 만들기*/
		m_BufferDesc.ByteWidth = m_iVertexStride * m_iNumVertices;
		m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		m_BufferDesc.MiscFlags = 0;
		m_BufferDesc.StructureByteStride = m_iVertexStride;


		if (FAILED(__super::Create_Buffer(&m_pVB)))
			return E_FAIL;

		Safe_Delete_Array(pVertices);

		/*이제 인덱스 정보 넣어주기*/

		_uint* pIndices = new _uint[m_iNumIndices];
		_ulong index = { 0 };

		/* 인덱스를 그럼 어떻게 설정할지를 결정하기*/

		for (size_t i = 0; i < dwCntZ - 1; i++)
		{
			for (size_t j = 0; j < dwCntX - 1; j++)
			{
				/* 1개의 사각형을 완성시켜야함.*/
				/*인덱스 6개 배치*/

				_uint iIndex = i * dwCntZ + j;

				_uint iIndices[4] =
				{
					iIndex + dwCntX,         /* 왼쪽 위*/
					iIndex + dwCntX + 1,	 /* 오른쪽 위 */
					iIndex + 1,				 /* 오른쪽 아래*/
					iIndex,					 /* 왼쪽 아래*/
				};

				pIndices[index++] = iIndices[0];
				pIndices[index++] = iIndices[1];
				pIndices[index++] = iIndices[2];

				pIndices[index++] = iIndices[0];
				pIndices[index++] = iIndices[2];
				pIndices[index++] = iIndices[3];
			}
		}

		/* 인덱스 버퍼 만들기*/
		m_BufferDesc.ByteWidth = m_iNumIndices * m_iIndexStride;
		m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		m_BufferDesc.MiscFlags = 0;
		m_BufferDesc.StructureByteStride = m_iIndexStride;

		m_InitialData.pSysMem = pIndices;
		if (FAILED(__super::Create_Buffer(&m_pIB)))
			return E_FAIL;

		Safe_Delete_Array(pIndices);
	}

	/* 파일 경로가 있을 때 */
	else
	{
		_ulong dwByte = {};
		HANDLE hFile = CreateFile(path, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (0 == hFile)
		{
			MSG_BOX("Failed to Read : HeightMap");
			return E_FAIL;
		}

		BITMAPFILEHEADER fh{};   /* 파일 이름 및 파일 생성날짜가 저장되있는곳*/
		ReadFile(hFile, &fh, sizeof(BITMAPFILEHEADER), &dwByte, nullptr);

		BITMAPINFOHEADER ih{};   /* 픽셀 개수를 저장 및 가로, 세로 개수 정보를 담음*/
		ReadFile(hFile, &ih, sizeof(BITMAPINFOHEADER), &dwByte, nullptr);
		/* ReadFile을 하는 이유는 파일에서 읽을 커서를 옮겨주는 작업*/

		_uint* pPixel = new _uint[m_iNumVertices]; /* 32 비트이므로 _uint로 */
		ReadFile(hFile, pPixel, sizeof(_uint) * m_iNumVertices, &dwByte, nullptr);

		//	A8 R8 G8 B8 
//
//	0b  11111111 10101010 10101010 10101010
//&	0b  00000000 00000000 00000000 11111111
//		00000000 00000000 00000000 10101010
//
//
		/* 버텍스 정보 넣어주기 */
		for (size_t i = 0; i < dwCntZ; i++)
		{
			for (size_t j = 0; j < dwCntX; j++)
			{
				_uint			iIndex = i * dwCntX + j;

				pVertices[iIndex].vPosition = _float3(j * dwVertexItv, (pPixel[iIndex] & 0x000000ff) / 10.f, i);
				pVertices[iIndex].vNormal = _float3(0.f, 0.f, 0.f);
				pVertices[iIndex].vTexcoord = _float2(j * dwVertexItv / (dwCntX - 1.f), i / (dwCntZ - 1.f));
			}
		}

		/* 만든 버텍스 데이터 다시 이제 그래픽장치에 넣어주기
		   CPU 만 알고있는 메모리 이므로 */



		   /*이제 인덱스 정보 넣어주기*/

		_uint* pIndices = new _uint[m_iNumIndices];
		ZeroMemory(pIndices, sizeof(_uint) * m_iNumIndices);
		_ulong index = { 0 };

		/* 인덱스를 그럼 어떻게 설정할지를 결정하기*/

		for (size_t i = 0; i < dwCntZ - 1; i++)
		{
			for (size_t j = 0; j < dwCntX - 1; j++)
			{
				/* 1개의 사각형을 완성시켜야함.*/
				/*인덱스 6개 배치*/

				_uint iIndex = i * dwCntZ + j;

				_uint iIndices[4] =
				{
					iIndex + dwCntX,         /* 왼쪽 위*/
					iIndex + dwCntX + 1,	 /* 오른쪽 위 */
					iIndex + 1,				 /* 오른쪽 아래*/
					iIndex,					 /* 왼쪽 아래*/
				};

				_vector vSour, vDest, vNormal;

				pIndices[index++] = iIndices[0];
				pIndices[index++] = iIndices[1];
				pIndices[index++] = iIndices[2];

				vSour = XMLoadFloat3(&pVertices[iIndices[1]].vPosition) - XMLoadFloat3(&pVertices[iIndices[0]].vPosition);
				vDest = XMLoadFloat3(&pVertices[iIndices[2]].vPosition) - XMLoadFloat3(&pVertices[iIndices[1]].vPosition);
				vNormal = XMVector3Normalize(XMVector3Cross(vSour, vDest));

				XMStoreFloat3(&pVertices[iIndices[0]].vNormal, XMLoadFloat3(&pVertices[iIndices[0]].vNormal) + vNormal);
				XMStoreFloat3(&pVertices[iIndices[1]].vNormal, XMLoadFloat3(&pVertices[iIndices[1]].vNormal) + vNormal);
				XMStoreFloat3(&pVertices[iIndices[2]].vNormal, XMLoadFloat3(&pVertices[iIndices[2]].vNormal) + vNormal);

				pIndices[index++] = iIndices[0];
				pIndices[index++] = iIndices[2];
				pIndices[index++] = iIndices[3];

				vSour = XMLoadFloat3(&pVertices[iIndices[2]].vPosition) - XMLoadFloat3(&pVertices[iIndices[0]].vPosition);
				vDest = XMLoadFloat3(&pVertices[iIndices[3]].vPosition) - XMLoadFloat3(&pVertices[iIndices[2]].vPosition);
				vNormal = XMVector3Normalize(XMVector3Cross(vSour, vDest));

				XMStoreFloat3(&pVertices[iIndices[0]].vNormal, XMLoadFloat3(&pVertices[iIndices[0]].vNormal) + vNormal);
				XMStoreFloat3(&pVertices[iIndices[2]].vNormal, XMLoadFloat3(&pVertices[iIndices[2]].vNormal) + vNormal);
				XMStoreFloat3(&pVertices[iIndices[3]].vNormal, XMLoadFloat3(&pVertices[iIndices[3]].vNormal) + vNormal);

			}
		}

		for (size_t i = 0; i < m_iNumVertices; i++)
		{
			XMStoreFloat3(&pVertices[i].vNormal, XMVector3Normalize(XMLoadFloat3(&pVertices[i].vNormal)));
		}


		/* 버텍스 버퍼 정보 그래픽 카드에 넘겨주기 */
		ZeroMemory(&m_InitialData, sizeof(D3D11_SUBRESOURCE_DATA));
		m_InitialData.pSysMem = pVertices;

		/* 버텍스 버퍼 만들기*/
		ZeroMemory(&m_BufferDesc, sizeof(m_BufferDesc));
		m_BufferDesc.ByteWidth = m_iVertexStride * m_iNumVertices;
		m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		m_BufferDesc.CPUAccessFlags = 0;
		m_BufferDesc.MiscFlags = 0;
		m_BufferDesc.StructureByteStride = m_iVertexStride;

		if (FAILED(__super::Create_Buffer(&m_pVB)))
			return E_FAIL;


		/* 인덱스 버퍼 정보 그래픽 카드에 넘겨주기 */
		ZeroMemory(&m_InitialData, sizeof(D3D11_SUBRESOURCE_DATA));
		m_InitialData.pSysMem = pIndices;

		/* 버텍스 버퍼 만들기*/
		ZeroMemory(&m_BufferDesc, sizeof(m_BufferDesc));
		m_BufferDesc.ByteWidth = m_iNumIndices * m_iIndexStride;
		m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		m_BufferDesc.CPUAccessFlags = 0;
		m_BufferDesc.MiscFlags = 0;
		m_BufferDesc.StructureByteStride = m_iIndexStride;

		if (FAILED(__super::Create_Buffer(&m_pIB)))
			return E_FAIL;

		Safe_Delete_Array(pVertices);
		Safe_Delete_Array(pPixel);
		Safe_Delete_Array(pIndices);
		CloseHandle(hFile);
	}

	return S_OK;
}

HRESULT CVIBuffer_Terrain::Initialize(void* pArg)
{
	return S_OK;
}


CVIBuffer_Terrain* CVIBuffer_Terrain::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext,
	_uint iCountX, _uint iCountY, _uint iVertexItv, const _tchar* pPath)
{
	CVIBuffer_Terrain* pInstance = new CVIBuffer_Terrain(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype(iCountX, iCountY, iVertexItv, pPath)))
	{
		MSG_BOX("Failed to Created : Terrain");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CVIBuffer_Terrain::Clone(void* pArg)
{
	CVIBuffer_Terrain* pInstance = new CVIBuffer_Terrain(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : Terrain");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Terrain::Free()
{
	__super::Free();
}

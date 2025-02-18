#include "..\Public\Mesh.h"
#include "Shader.h"
#include "Bone.h"


CMesh::CMesh(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CVIBuffer { pDevice, pContext }
{
}

CMesh::CMesh(const CMesh & Prototype)
	: CVIBuffer (Prototype )
{
}

HRESULT CMesh::Initialize_Prototype(CModel::MODEL eModelType, CModel* pModel, const aiMesh * pAIMesh, _fmatrix PreTransformMatrix)
{
	strcpy_s(m_szName, pAIMesh->mName.data);	

	m_iNumPrimitive = pAIMesh->mNumFaces;	
	m_iMaterialIndex = pAIMesh->mMaterialIndex; 
	m_iNumVertices = pAIMesh->mNumVertices;

	m_iNumIndices = pAIMesh->mNumFaces * 3;
	m_iIndexStride = 4;
	m_iNumVertexBuffers = 1;
	m_ePrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;	
	m_eIndexFormat = DXGI_FORMAT_R32_UINT;

#pragma region VERTEX_BUFFER
	HRESULT hr = CModel::MODEL_NONANIM == eModelType ? Ready_VertexBuffer_ForNonAnim(pAIMesh, PreTransformMatrix) : Ready_VertexBuffer_ForAnim(pModel, pAIMesh,PreTransformMatrix);	
	if (FAILED(hr))
		return E_FAIL;
#pragma endregion
	m_ModelType = eModelType;

#pragma region INDEX_BUFFER
	ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);
	m_BufferDesc.ByteWidth = m_iNumIndices * m_iIndexStride;
	m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_BufferDesc.StructureByteStride = m_iIndexStride;
	m_BufferDesc.CPUAccessFlags = 0;
	m_BufferDesc.MiscFlags = 0;

	_uint*			pIndices = new _uint[m_iNumIndices];
	ZeroMemory(pIndices, sizeof(_uint) * m_iNumIndices);

	/* 바이너리화 코드*/
	pNewIndices = new _uint[m_iNumIndices];
	ZeroMemory(pNewIndices, sizeof(_uint) * m_iNumIndices);
	//

	_uint			iNumIndices = { 0 };

	for (size_t i = 0; i < pAIMesh->mNumFaces; i++)
	{		
		pIndices[iNumIndices++] = pNewIndices[iNumIndices] = pAIMesh->mFaces[i].mIndices[0];
		pIndices[iNumIndices++] = pNewIndices[iNumIndices] = pAIMesh->mFaces[i].mIndices[1];
		pIndices[iNumIndices++] = pNewIndices[iNumIndices] = pAIMesh->mFaces[i].mIndices[2];
	}


	ZeroMemory(&m_InitialData, sizeof m_InitialData);
	m_InitialData.pSysMem = pIndices;

	if (FAILED(__super::Create_Buffer(&m_pIB)))
		return E_FAIL;

	Safe_Delete_Array(pIndices);
#pragma endregion

	return S_OK;
}

HRESULT CMesh::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CMesh::Bind_BoneMatrices(CShader* pShader, const _char* pContstantName, const vector<class CBone*>& Bones)
{
	D3D11_MAPPED_SUBRESOURCE mapped_StrBuffer_Resource;
	ZeroMemory(&mapped_StrBuffer_Resource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	ZeroMemory(m_ColMajorBoneMatrices, sizeof(m_ColMajorBoneMatrices));		

	/* 여기 D3D11_MAP_DISCARD로 교체해서 해보기 */
	HRESULT hr = m_pContext->Map(m_pStrBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_StrBuffer_Resource);


	for (size_t i = 0; i < m_iNumBones; i++)
		XMStoreFloat4x4(&m_BoneMatrices[i], XMLoadFloat4x4(&m_OffsetMatrices[i]) * Bones[m_BoneIndices[i]]->Get_CombinedTransformationMatrix());

	for (size_t i = 0; i < m_iNumBones; i++)
		XMStoreFloat4x4(&m_ColMajorBoneMatrices[i], XMMatrixTranspose(XMLoadFloat4x4(&m_BoneMatrices[i])));


	_float4x4* pBoneMatrices = reinterpret_cast<_float4x4*>(mapped_StrBuffer_Resource.pData);
	memcpy(pBoneMatrices, m_ColMajorBoneMatrices, sizeof(_float4x4) * m_iNumBones);

	m_pContext->Unmap(m_pStrBuffer, 0);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	//srvDesc.Buffer.FirstElement = 0;		
	srvDesc.Buffer.NumElements = m_iNumBones;


	ID3D11ShaderResourceView* pSRV;
	m_pDevice->CreateShaderResourceView(m_pStrBuffer, &srvDesc, &pSRV);
	if(FAILED(pShader->Bind_SRV(pContstantName, pSRV)))
		return E_FAIL;
	Safe_Release(pSRV);		
	return 	S_OK; //이렇게하면 될거같은데	
	

}

HRESULT CMesh::Ready_VertexBuffer_ForNonAnim(const aiMesh* pAIMesh, _fmatrix PreTransforMatrix)
{
	m_iVertexStride = sizeof(VTXMESH);

	ZeroMemory(&m_MeshBufferdesc, sizeof(m_MeshBufferdesc));
	m_MeshBufferdesc.ByteWidth = m_iNumVertices * m_iVertexStride;
	m_MeshBufferdesc.Usage     = D3D11_USAGE_DEFAULT;
	m_MeshBufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_MeshBufferdesc.StructureByteStride = m_iVertexStride;
	m_MeshBufferdesc.CPUAccessFlags = 0;
	m_MeshBufferdesc.MiscFlags = 0; 

	VTXMESH* pVertices = new VTXMESH[m_iNumVertices];
	m_nonAnimpVertices = new VTXMESH[m_iNumVertices];	
	ZeroMemory(pVertices, sizeof(VTXMESH) * m_iNumVertices);
	ZeroMemory(m_nonAnimpVertices, sizeof(VTXMESH) * m_iNumVertices);	

	for(size_t i =0; i < m_iNumVertices; i++)
	{
		/* 점의 정보 채워주기 */
		memcpy(&pVertices[i].vPosition, &pAIMesh->mVertices[i], sizeof(_float3));
		XMStoreFloat3(&pVertices[i].vPosition, XMVector3TransformCoord(XMLoadFloat3(&pVertices[i].vPosition), PreTransforMatrix));
		
		/* 바이너리 저장 */
		memcpy(&m_nonAnimpVertices[i].vPosition, &pAIMesh->mVertices[i], sizeof(_float3));
		XMStoreFloat3(&m_nonAnimpVertices[i].vPosition, XMVector3TransformCoord(XMLoadFloat3(&m_nonAnimpVertices[i].vPosition), PreTransforMatrix));
		//

		memcpy(&pVertices[i].vNormal, &pAIMesh->mNormals[i], sizeof(_float3));
		XMStoreFloat3(&pVertices[i].vNormal, XMVector3TransformNormal(XMLoadFloat3(&pVertices[i].vNormal), PreTransforMatrix));

		/* 바이너리 저장 */
		memcpy(&m_nonAnimpVertices[i].vNormal, &pAIMesh->mNormals[i], sizeof(_float3));
		XMStoreFloat3(&m_nonAnimpVertices[i].vNormal, XMVector3TransformNormal(XMLoadFloat3(&m_nonAnimpVertices[i].vNormal), PreTransforMatrix));
		//

		memcpy(&pVertices[i].vTexcoord, &pAIMesh->mTextureCoords[0][i], sizeof(_float2));	 /* diffuse가 텍스처니깐 0 을 넣은듯*/
		memcpy(&pVertices[i].vTangent, &pAIMesh->mTangents[i], sizeof(_float3));
		XMStoreFloat3(&pVertices[i].vTangent, XMVector3TransformNormal(XMLoadFloat3(&pVertices[i].vTangent), PreTransforMatrix));	

		/* 바이너리 저장 */	
		memcpy(&m_nonAnimpVertices[i].vTexcoord, &pAIMesh->mTextureCoords[0][i], sizeof(_float2));	
		memcpy(&m_nonAnimpVertices[i].vTangent, &pAIMesh->mTangents[i], sizeof(_float3));	
		//

	}
	
	ZeroMemory(&m_InitialData, sizeof(m_InitialData));
	m_InitialData.pSysMem = pVertices;

	if (FAILED(__super::Create_BufferZ(&m_pVB, &m_MeshBufferdesc)))	
		return E_FAIL;	

	Safe_Delete_Array(pVertices);

	return S_OK;
}

HRESULT CMesh::Ready_VertexBuffer_ForAnim(CModel* pModel, const aiMesh* pAIMesh, _fmatrix PreTransforMatrix)	
{
	m_iVertexStride = sizeof(VTXANIMMESH);

	ZeroMemory(&m_MeshBufferdesc, sizeof(m_MeshBufferdesc));	
	m_MeshBufferdesc.ByteWidth = m_iNumVertices * m_iVertexStride;	
	m_MeshBufferdesc.Usage = D3D11_USAGE_DEFAULT;		
	m_MeshBufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	
	m_MeshBufferdesc.StructureByteStride = m_iVertexStride;		
	m_MeshBufferdesc.CPUAccessFlags = 0;	
	m_MeshBufferdesc.MiscFlags = 0; 

	VTXANIMMESH* pVertices = new VTXANIMMESH[m_iNumVertices];
	ZeroMemory(pVertices, sizeof(VTXANIMMESH) * m_iNumVertices);


	m_AnimVertices = new VTXANIMMESH[m_iNumVertices];
	ZeroMemory(m_AnimVertices, sizeof(VTXANIMMESH) * m_iNumVertices);


	for(size_t i =0; i< m_iNumVertices; i++)
	{
		memcpy(&pVertices[i].vPosition, &pAIMesh->mVertices[i], sizeof(_float3));
		memcpy(&pVertices[i].vNormal, &pAIMesh->mNormals[i], sizeof(_float3));
		memcpy(&pVertices[i].vTexcoord, &pAIMesh->mTextureCoords[0][i], sizeof(_float2));
		memcpy(&pVertices[i].vTangent, &pAIMesh->mTangents[i], sizeof(_float3));
		XMStoreFloat3(&pVertices[i].vTangent, XMVector3TransformNormal(XMLoadFloat3(&pVertices[i].vTangent), PreTransforMatrix));	
		

		memcpy(&m_AnimVertices[i].vPosition, &pAIMesh->mVertices[i], sizeof(_float3));	
		memcpy(&m_AnimVertices[i].vNormal, &pAIMesh->mNormals[i], sizeof(_float3));	
		memcpy(&m_AnimVertices[i].vTexcoord, &pAIMesh->mTextureCoords[0][i], sizeof(_float2));	
		memcpy(&m_AnimVertices[i].vTangent, &pAIMesh->mTangents[i], sizeof(_float3));	
	}


	m_iNumBones = pAIMesh->mNumBones;

	for (size_t i=0; i< m_iNumBones; i++)
	{
		aiBone* pAIBone = pAIMesh->mBones[i]; /* 매쉬의 첫번째 뼈를 가져옴*/

		_float4x4 OffsetMatrix; 

		memcpy(&OffsetMatrix, &pAIBone->mOffsetMatrix, sizeof(_float4x4)); 
		
		/* 항상 기억해야 할점은 바로 ai(assimp)에서 가져오는 행렬은 column major 행렬이므로 우리가 사용하는 row major 바꾸기 위해서는
		전치 행렬을 곱해줘야 한다.*/
		XMStoreFloat4x4(&OffsetMatrix, XMMatrixTranspose(XMLoadFloat4x4(&OffsetMatrix)));

		m_OffsetMatrices.push_back(OffsetMatrix);	

		m_BoneIndices.push_back(pModel->Get_BoneIndex(pAIBone->mName.data)); /* 여기다가 "SWORD"을 주고*/
		
		/*pAIBone->mNumWeights : 이 뼈는 몇개의 정점에게 영향을 주는지에 대해 알려줌*/
		for (size_t j = 0; j < pAIBone->mNumWeights; j++)
		{
			/* pAIBone->mWeights[j] : 이 뼈가 영향을 주는 j번째 정점의 정보 */
			aiVertexWeight AIWeight = pAIBone->mWeights[j];

			/* AIWeight.mVertexId : 이 뼈가 영향을 주는 j번째 정점의 인덱스 */
			/* 예를 들어 pIndices[1] = 129 이면  pVertices[129]의 인덱스버퍼의 인덱스가 1이라는 소리*/
			/* 즉 여기서의 pAIBone->mWeights[j]의 값은 그러면 129가 된다는 의미 */
			if (0.f == pVertices[AIWeight.mVertexId].vBlendWeight.x)
			{
				pVertices[AIWeight.mVertexId].vBlendIndex.x = i;  /* 이 정점이 영향받는 뼈의 인덱스 */
				m_AnimVertices[AIWeight.mVertexId].vBlendIndex.x = i;	
				pVertices[AIWeight.mVertexId].vBlendWeight.x = AIWeight.mWeight; /* 이 정점이 이 뼈에 얼마나 영향을 받는지에 대한 가중치*/
				m_AnimVertices[AIWeight.mVertexId].vBlendWeight.x = AIWeight.mWeight;
			}

			else if (0.f == pVertices[AIWeight.mVertexId].vBlendWeight.y)
			{
				pVertices[AIWeight.mVertexId].vBlendIndex.y = i;	
				m_AnimVertices[AIWeight.mVertexId].vBlendIndex.y = i;		
				pVertices[AIWeight.mVertexId].vBlendWeight.y = AIWeight.mWeight;
				m_AnimVertices[AIWeight.mVertexId].vBlendWeight.y = AIWeight.mWeight;
			}

			else if (0.f == pVertices[AIWeight.mVertexId].vBlendWeight.z)
			{
				pVertices[AIWeight.mVertexId].vBlendIndex.z = i;
				m_AnimVertices[AIWeight.mVertexId].vBlendIndex.z = i;
				pVertices[AIWeight.mVertexId].vBlendWeight.z = AIWeight.mWeight;
				m_AnimVertices[AIWeight.mVertexId].vBlendWeight.z = AIWeight.mWeight;	
			}

			else if (0.f == pVertices[AIWeight.mVertexId].vBlendWeight.w)
			{
				pVertices[AIWeight.mVertexId].vBlendIndex.w = i;
				m_AnimVertices[AIWeight.mVertexId].vBlendIndex.w = i;
				pVertices[AIWeight.mVertexId].vBlendWeight.w = AIWeight.mWeight;
				m_AnimVertices[AIWeight.mVertexId].vBlendWeight.w = AIWeight.mWeight;	
			}

		}

	}
	

	if (0 == m_iNumBones)
	{
		/* 이 메시와 이름이 같은 뼈를 찾아서 강제로 하나 추가한다. */
		m_iNumBones = 1;

		m_BoneIndices.push_back(pModel->Get_BoneIndex(m_szName));

		_float4x4		OffsetMatrix;

		XMStoreFloat4x4(&OffsetMatrix, XMMatrixIdentity());

		m_OffsetMatrices.push_back(OffsetMatrix);
	}

	ZeroMemory(&m_InitialData, sizeof(m_InitialData));	
	m_InitialData.pSysMem = pVertices;	

	if (FAILED(__super::Create_BufferZ(&m_pVB,&m_MeshBufferdesc)))	
		return E_FAIL;

	Safe_Delete_Array(pVertices);


#pragma region Structed Buffer 

	ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);
	m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_BufferDesc.ByteWidth = sizeof(_float4x4) * m_iNumBones;  // 행렬 데이터 크기						
	m_BufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	m_BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	m_BufferDesc.StructureByteStride = sizeof(_float4x4);
	m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	_float4x4* pBoneMatrices = new _float4x4[m_iNumBones];
	ZeroMemory(pBoneMatrices, sizeof(_float4x4)* m_iNumBones);

	ZeroMemory(&m_InitialData, sizeof(m_InitialData));
	m_InitialData.pSysMem = pBoneMatrices;

	if (FAILED(__super::Create_Buffer(&m_pStrBuffer)))
		return E_FAIL;

	Safe_Delete_Array(pBoneMatrices);
#pragma endregion 
	return S_OK;	

}

HRESULT CMesh::Save_Mesh(ostream& os)
{
	os.write(m_szName, sizeof(_char) * MAX_PATH);

	os.write((char*)&m_iNumPrimitive, sizeof(_uint));
	os.write((char*)&m_iMaterialIndex, sizeof(_uint));
	os.write((char*)&m_ePrimitiveTopology, sizeof(D3D11_PRIMITIVE_TOPOLOGY));
	os.write((char*)&m_eIndexFormat, sizeof(DXGI_FORMAT));
	os.write((char*)&m_iNumVertexBuffers, sizeof(_uint));
	os.write((char*)&m_iNumVertices, sizeof(_uint));
	os.write((char*)&m_iIndexStride, sizeof(_uint));
	os.write((char*)&m_iNumIndices, sizeof(_uint));
	os.write((char*)&m_iVertexStride, sizeof(_uint));

	os.write((char*)&m_MeshBufferdesc.ByteWidth, sizeof(_uint));
	os.write((char*)&m_MeshBufferdesc.Usage, sizeof(D3D11_USAGE));
	os.write((char*)&m_MeshBufferdesc.BindFlags, sizeof(_uint));
	os.write((char*)&m_MeshBufferdesc.CPUAccessFlags, sizeof(_uint));
	os.write((char*)&m_MeshBufferdesc.MiscFlags, sizeof(_uint));
	os.write((char*)&m_MeshBufferdesc.StructureByteStride, sizeof(_uint));

	os.write((char*)&m_ModelType, sizeof(CModel::MODEL));
	os.write((char*)&m_iNumBones, sizeof(_uint));

	writeVectorToBinary(m_BoneIndices, os);
	writeVectorToBinary(m_OffsetMatrices, os);

	if (m_ModelType == CModel::MODEL_NONANIM)
	{
		os.write((char*)m_nonAnimpVertices, sizeof(VTXMESH) * m_iNumVertices);
	}

	else
	{
		os.write((char*)m_AnimVertices, sizeof(VTXANIMMESH) * m_iNumVertices);
	}

	os.write((char*)&m_BufferDesc.ByteWidth, sizeof(_uint));
	os.write((char*)&m_BufferDesc.Usage, sizeof(D3D11_USAGE));
	os.write((char*)&m_BufferDesc.BindFlags, sizeof(_uint));
	os.write((char*)&m_BufferDesc.CPUAccessFlags, sizeof(_uint));
	os.write((char*)&m_BufferDesc.MiscFlags, sizeof(_uint));
	os.write((char*)&m_BufferDesc.StructureByteStride, sizeof(_uint));
	os.write((char*)(pNewIndices), sizeof(_uint) * m_iNumIndices);


	return S_OK;
}

HRESULT CMesh::Load_Mesh(istream& is)
{
	is.read(m_szName, sizeof(_char) * MAX_PATH);

	is.read((char*)&m_iNumPrimitive, sizeof(_uint));
	is.read((char*)&m_iMaterialIndex, sizeof(_uint));
	is.read((char*)&m_ePrimitiveTopology, sizeof(D3D11_PRIMITIVE_TOPOLOGY));
	is.read((char*)&m_eIndexFormat, sizeof(DXGI_FORMAT));
	is.read((char*)&m_iNumVertexBuffers, sizeof(_uint));
	is.read((char*)&m_iNumVertices, sizeof(_uint));
	is.read((char*)&m_iIndexStride, sizeof(_uint));
	is.read((char*)&m_iNumIndices, sizeof(_uint));
	is.read((char*)&m_iVertexStride, sizeof(_uint));

	is.read((char*)&m_MeshBufferdesc.ByteWidth, sizeof(_uint));
	is.read((char*)&m_MeshBufferdesc.Usage, sizeof(D3D11_USAGE));
	is.read((char*)&m_MeshBufferdesc.BindFlags, sizeof(_uint));
	is.read((char*)&m_MeshBufferdesc.CPUAccessFlags, sizeof(_uint));
	is.read((char*)&m_MeshBufferdesc.MiscFlags, sizeof(_uint));
	is.read((char*)&m_MeshBufferdesc.StructureByteStride, sizeof(_uint));

	is.read((char*)&m_ModelType, sizeof(CModel::MODEL));

	is.read((char*)&m_iNumBones, sizeof(_uint));
	readVectorFromBinary(is, m_BoneIndices);
	readVectorFromBinary(is, m_OffsetMatrices);

	if (m_ModelType == CModel::MODEL_NONANIM)
	{
		m_nonAnimpVertices = new VTXMESH[m_iNumVertices];
		is.read((char*)(m_nonAnimpVertices), sizeof(VTXMESH) * m_iNumVertices);

		m_InitialData.pSysMem = m_nonAnimpVertices;
		if (FAILED(__super::Create_BufferZ(&m_pVB, &m_MeshBufferdesc)))
			return E_FAIL;
	}

	else
	{
		m_AnimVertices = new VTXANIMMESH[m_iNumVertices];
		is.read((char*)(m_AnimVertices), sizeof(VTXANIMMESH) * m_iNumVertices);

		m_InitialData.pSysMem = m_AnimVertices;
		if (FAILED(__super::Create_BufferZ(&m_pVB, &m_MeshBufferdesc)))
			return E_FAIL;

#pragma region Structed Buffer 

		ZeroMemory(&m_BufferDesc, sizeof m_BufferDesc);
		m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		m_BufferDesc.ByteWidth = sizeof(_float4x4) * m_iNumBones;  // 행렬 데이터 크기						
		m_BufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		m_BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		m_BufferDesc.StructureByteStride = sizeof(_float4x4);
		m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		_float4x4* pBoneMatrices = new _float4x4[m_iNumBones];
		ZeroMemory(pBoneMatrices, sizeof(_float4x4) * m_iNumBones);

		ZeroMemory(&m_InitialData, sizeof(m_InitialData));
		m_InitialData.pSysMem = pBoneMatrices;

		if (FAILED(__super::Create_Buffer(&m_pStrBuffer)))
			return E_FAIL;

		Safe_Delete_Array(pBoneMatrices);
#pragma endregion 

	}


	is.read((char*)&m_BufferDesc.ByteWidth, sizeof(_uint));
	is.read((char*)&m_BufferDesc.Usage, sizeof(D3D11_USAGE));
	is.read((char*)&m_BufferDesc.BindFlags, sizeof(_uint));
	is.read((char*)&m_BufferDesc.CPUAccessFlags, sizeof(_uint));
	is.read((char*)&m_BufferDesc.MiscFlags, sizeof(_uint));
	is.read((char*)&m_BufferDesc.StructureByteStride, sizeof(_uint));


	pNewIndices = new _uint[m_iNumIndices];
	is.read((char*)(pNewIndices), sizeof(_uint) * m_iNumIndices);


	m_InitialData.pSysMem = pNewIndices;

	if (FAILED(__super::Create_Buffer(&m_pIB)))
		return E_FAIL;



	return S_OK;
}

CMesh * CMesh::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, CModel::MODEL eModelType, CModel* pModel, const aiMesh * pAIMesh, _fmatrix PreTransformMatrix)
{
	CMesh*	pInstance = new CMesh(pDevice, pContext);
		
	if (FAILED(pInstance->Initialize_Prototype(eModelType,pModel,pAIMesh,PreTransformMatrix)))
	{
		MSG_BOX("Failed To Created : CMesh");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CMesh* CMesh::LoadCreate(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, istream& is)
{
	CMesh* pInstance = new CMesh(pDevice, pContext);
	if (FAILED(pInstance->Load_Mesh(is)))
	{
		MSG_BOX("Failed to Created : CMesh");
		Safe_Release(pInstance);
	}

	return pInstance;	
}

CComponent * CMesh::Clone(void * pArg)
{
	return nullptr;
}

void CMesh::Free()
{
	__super::Free();

	if (m_ModelType == CModel::MODEL_NONANIM)	
		Safe_Delete_Array(m_nonAnimpVertices);	
	else
		Safe_Delete_Array(m_AnimVertices);	

	Safe_Delete_Array(pNewIndices);	

	Safe_Release(m_pStrBuffer);

}

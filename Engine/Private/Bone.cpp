#include "Bone.h"

CBone::CBone()
{
}

HRESULT CBone::Initialize(const aiNode* pAINode, _int iParentBoneIndex)
{
	strcpy_s(m_szName, pAINode->mName.data); /* data를 붙여준 이유는 char로 반환해주기 때문에 data를 붙여줌*/
	

	/*pAINode->mTransformation**은 해당 노드의 로컬 변환 행렬*/
	/*지금 받아오는 노드는 루트노드라서 단위행렬이 맞음 (왜냐하면 루트노드의 부모가 없으니깐) */
	memcpy(&m_TransformationMatrix, &pAINode->mTransformation, sizeof(_float4x4)); 
	/* 자료형이 다르기 때문에 대입이 안됨 그러나 안에 들어있는 자료형은 float으로 같기 때문에 복사를 이용해 메모리 크기만큼 복사를 진행*/

	XMStoreFloat4x4(&m_TransformationMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_TransformationMatrix)));
	/* 전치행렬을 해주는 이유는 Assimp에서 행렬은 column 우선 즉 열 우선 방식으로 저장하므로 
	    _11, _21, _31, _41 순서로 저장된다 우리는 major 우선 방식이므로  _11 , _12 , _13, _14 로 순서로 저장해야 되기 때문에 
		전치행렬을 적용시켰다.*/

	XMStoreFloat4x4(&m_CombinedTransformationMatrix, XMMatrixIdentity());

	m_iParentBoneIndex = iParentBoneIndex; 

	

	return S_OK; 
}

void CBone::Update_CombinedTransformationMatrix(const vector<class CBone*>& Bones, _fmatrix PreTransformMatrix)	
{
	if (-1 == m_iParentBoneIndex)
		XMStoreFloat4x4(&m_CombinedTransformationMatrix, PreTransformMatrix * XMLoadFloat4x4(&m_TransformationMatrix));

	else
	{
		XMStoreFloat4x4(&m_CombinedTransformationMatrix,
			XMLoadFloat4x4(&m_TransformationMatrix) * XMLoadFloat4x4(&Bones[m_iParentBoneIndex]->m_CombinedTransformationMatrix));
	}

	/* 루트 모션 애니메이션 이동 행렬 저장하기*/
	if (m_iParentBoneIndex == 1) 
	{
		//XMStoreFloat4x4(m_pPreRootMatrix, XMMatrixIdentity());	

		/*XMMATRIX matrix = 
			XMLoadFloat4x4(&m_CombinedTransformationMatrix) - XMLoadFloat4x4(m_pPreRootMatrix);*/

		XMMATRIX matrix = XMMatrixIdentity();	

		if (m_CombinedTransformationMatrix._41 == 0.f &&		
			m_CombinedTransformationMatrix._42 == 0.f &&	
			m_CombinedTransformationMatrix._43 == 0.f &&		
			m_CombinedTransformationMatrix._44 == 1.f)		
		{
			// 단위 행렬로 초기화		
			XMStoreFloat4x4(&m_pPreRootMatrix, XMMatrixIdentity());	

			/* 보간 때 발생하는 문제 해결해야함 */
		}
		

		// 단위 행렬의 회전/스케일 부분 (_11 ~ _33)을 유지
		//matrix.r[0] = XMVectorSet(1.f, 0.f, 0.f, 0.f); // 첫 번째 행	
		//matrix.r[1] = XMVectorSet(0.f, 1.f, 0.f, 0.f); // 두 번째 행	
		//matrix.r[2] = XMVectorSet(0.f, 0.f, 1.f, 0.f); // 세 번째 행
		matrix.r[3] = XMVectorSubtract(XMLoadFloat4x4(&m_CombinedTransformationMatrix).r[3],XMLoadFloat4x4(&m_pPreRootMatrix).r[3]);
		matrix.r[3] = XMVectorSetW(matrix.r[3], 1.f); // W 값을 1로 고정	
		
		// 나머지 이동 값은 그대로 유지
		// 네 번째 행 (_41, _42, _43, _44)은 변경하지 않음

		
		// 결과를 저장
		XMStoreFloat4x4(&m_RootMotionMatrix, matrix);	
		XMStoreFloat4x4(&m_pPreRootMatrix, XMLoadFloat4x4(&m_CombinedTransformationMatrix));
		

		/* 여기서 이제 만약에 루트모션이 아니라면 pre CombinedBorn행렬 초기화하기*/
		//if (m_CombinedTransformationMatrix._41 == 0.f &&	
		//	m_CombinedTransformationMatrix._42 == 0.f &&	 // 이 값을 조건문 위로 올려버리기 
		//	m_CombinedTransformationMatrix._43 == 0.f &&	
		//	m_CombinedTransformationMatrix._44 == 1.f)	
		//{
		//	// 단위 행렬로 초기화	
		//	XMStoreFloat4x4(&m_pPreRootMatrix, XMMatrixIdentity());	
		//}

		m_CombinedTransformationMatrix._41 = 0.f;
		m_CombinedTransformationMatrix._42 = 0.f;
		m_CombinedTransformationMatrix._43 = 0.f;
		m_CombinedTransformationMatrix._44 = 1.f;

		
		

	}

}

HRESULT CBone::Save_Bone(ostream& os)
{
	os.write(m_szName, sizeof(_char) * MAX_PATH);	
	os.write((char*)&m_iParentBoneIndex, sizeof(_int));	
	os.write((char*)&m_TransformationMatrix, sizeof(_float4x4));	

	return S_OK;
}

HRESULT CBone::Load_Bone(istream& os)
{
	os.read(m_szName, sizeof(_char) * MAX_PATH);
	os.read((char*)&m_iParentBoneIndex, sizeof(_int));
	os.read((char*)&m_TransformationMatrix, sizeof(_float4x4));
	
	return S_OK;
}

CBone* CBone::Create(const aiNode* pAINode, _int iParentBoneIndex)
{
	CBone* pInstance = new CBone();
	if(FAILED(pInstance->Initialize(pAINode,iParentBoneIndex)))
	{
		MSG_BOX("Failed to Created : Bone");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CBone* CBone::LoadCreate(std::istream& os)
{
	CBone* pInstance = new CBone();

	if (FAILED(pInstance->Load_Bone(os)))
	{
		MSG_BOX("Failed to Created : Bone");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CBone* CBone::Clone()
{
	return new CBone(*this);
}

void CBone::Free()
{
	__super::Free();

}

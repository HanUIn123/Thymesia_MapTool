#include "..\Public\PipeLine.h"



CPipeLine::CPipeLine()
{
}

HRESULT CPipeLine::Initialize()
{
	for (size_t i = 0; i < D3DTS_END; i++)
	{
		XMStoreFloat4x4(&m_TransformationMatrices[i], XMMatrixIdentity());
		XMStoreFloat4x4(&m_TransformationInverseMatrices[i], XMMatrixIdentity());
	}

	m_vCamPosition = _float4(0.f, 0.f, 0.f, 1.f);	

	return S_OK;
}

void CPipeLine::Update()
{
	for (size_t i = 0; i < D3DTS_END; i++)
	{
		XMStoreFloat4x4(&m_TransformationInverseMatrices[i], XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_TransformationMatrices[i])));
	}

	XMStoreFloat4(&m_vCamPosition, XMLoadFloat4x4(&m_TransformationInverseMatrices[D3DTS_VIEW]).r[3]);
	
}

CPipeLine * CPipeLine::Create()
{
	CPipeLine*		pInstance = new CPipeLine();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CPipeLine");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPipeLine::Free()
{
	__super::Free();

}



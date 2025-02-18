#pragma once

#include "Base.h"

/* 원근 투영을 위한 뷰, 투영행렬을 저장한다. */
/* 반복적인 갱신을 통해 각 행렬의 역행렬도 구하여 저장한다. */
/* Set, Get함수를 통해 행렬을 저장 또는 리턶나다. */

BEGIN(Engine)

class CPipeLine final : public CBase
{
public:
	enum D3DTRANSFORMSTATE {D3DTS_VIEW, D3DTS_PROJ, D3DTS_END };
private:
	CPipeLine();
	virtual ~CPipeLine() = default;

public:
	_float4x4 Get_Transform_Float4x4(D3DTRANSFORMSTATE eState) const {
		return m_TransformationMatrices[eState];
	}
	_matrix Get_Transform_Matrix(D3DTRANSFORMSTATE eState) const {
		return XMLoadFloat4x4(&m_TransformationMatrices[eState]);
	}
	_float4x4 Get_Transform_Float4x4_Inverse(D3DTRANSFORMSTATE eState) const {
		return m_TransformationInverseMatrices[eState];
	}
	_matrix Get_Transform_Matrix_Inverse(D3DTRANSFORMSTATE eState)const {
		return XMLoadFloat4x4(&m_TransformationInverseMatrices[eState]);
	}

	_float4 Get_CamPosition() const {
		return m_vCamPosition;
	}

public:
	void Set_Transform(D3DTRANSFORMSTATE eState, _fmatrix TransformMatrix) {
		XMStoreFloat4x4(&m_TransformationMatrices[eState], TransformMatrix);
	}

public:
	HRESULT Initialize();
	/* 원근 투영을 위한 뷰, 투영행렬의 역행렬을 구해서 저장한다. */
	/* 하는 김에 카메라 위치도 구해놓는다. */
	void Update();

private:
	_float4x4				m_TransformationMatrices[D3DTS_END] = {};
	_float4x4				m_TransformationInverseMatrices[D3DTS_END] = {};
	_float4					m_vCamPosition = {};

public:
	static CPipeLine* Create();
	virtual void Free() override;	
};

END
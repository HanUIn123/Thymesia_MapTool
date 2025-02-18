#pragma once

#include "Base.h"

BEGIN(Engine)

class CCell final : public CBase
{
public:
	enum POINT { POINT_A , POINT_B , POINT_C , POINT_END};
	enum LINE  { LINE_AB, LINE_BC, LINE_CA, LINE_END };

private:
	CCell(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CCell() = default; 

public:
	_vector Get_Point(POINT ePoint) {
		return XMLoadFloat3(&m_vPoints[ePoint]);
	}

public:
	void Set_Neighbor(LINE eLine, CCell* pNeighbor)
	{
		m_iNeighborIndices[eLine] = pNeighbor->m_iIndex;
	}

public:
	HRESULT Initialize(const _float3* pPoints, _int iIndex);
	_bool   isIn(_fvector vPosition, _int* pNeighborIndex);
	_bool   Compare_Points(_fvector vSourPoint, _fvector vDestPoint);
	
	_float  Compute_Height(_fvector vPosition);


#ifdef  _DEBUG
public:
	HRESULT Render();

#endif


private:
	ID3D11Device*				m_pDevice  = { nullptr }; 
	ID3D11DeviceContext*		m_pContext = { nullptr };

	_float3						m_vPoints[POINT_END] = {};
	_int						m_iNeighborIndices[LINE_END] = { -1, -1, -1 };
	_int						m_iIndex = {};

	_float4						m_vPlane = {};

#ifdef _DEBUG
private:
	class CVIBuffer_Cell*		m_pVIBuffer = { nullptr };
#endif


public:
	static CCell* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const _float3* pPoints, _int iIndex);
	virtual void  Free() override;

};

END
#pragma once

#include "Component.h"

BEGIN(Engine)
class ENGINE_DLL CNavigation final : public CComponent 
{
public:
	struct NAVIGATION_DESC
	{
		_int   iCurrentCellIndex = { -1 };	
	};

private:
	CNavigation(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CNavigation(const CNavigation& Prototype);
	virtual ~CNavigation() = default; 


public:
	virtual HRESULT Initialize_Prototype(const _tchar* pNavigationDataFile);
	virtual HRESULT Initialize(void* pArg) override; 

public:
	void SetUp_WorldMatrix(_fmatrix WorldMatrix) {
		XMStoreFloat4x4(&m_WorldMatrix, WorldMatrix);
		XMStoreFloat4x4(&m_WorldMatrixInverse, XMMatrixInverse(nullptr, WorldMatrix));
	}

public:
	_bool  isMove(_fvector vWorldPos);
	_float Compute_Height(_fvector vWorldPos);
	vector<class CCell*>* Get_VecCells() { return &m_Cells; }	
	void   Set_CurCellIndex(_uint _CellIndex) { m_iCurrentCellIndex = _CellIndex; }
	_uint  Get_CurCellIndex() { return m_iCurrentCellIndex; }

#ifdef _DEBUG
public:
	HRESULT Render();
#endif

private:
	/* 이 네비를 이용하는 객체가 현재 어떤 셀 안에 있는지? */
	_int					m_iCurrentCellIndex = { -1 };
	vector<class CCell*>	m_Cells;	 


	static _float4x4       m_WorldMatrix; 
	static _float4x4       m_WorldMatrixInverse;

#ifdef _DEBUG
private:
	class CShader*			m_pShader = { nullptr };
#endif

private:
	HRESULT SetUp_Neighbors();


public:
	static CNavigation* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const _tchar* pNavigationDataFile);
	virtual CComponent* Clone(void* pArg) override; 
	virtual void Free() override; 
};
END

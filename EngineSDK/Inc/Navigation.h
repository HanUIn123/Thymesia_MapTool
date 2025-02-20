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
	bool Get_FirstPick() const{return m_bFirstPick;}
	void Set_FirstPick(bool bFirstPick) {m_bFirstPick = bFirstPick;}

public:
	virtual HRESULT Initialize_Prototype(const _tchar* pNavigationDataFile);
	HRESULT	Initialize_Prototype_CreateOnly();
	virtual HRESULT Initialize(void* pArg) override; 

public:
	void SetUp_WorldMatrix(_fmatrix WorldMatrix) {
		XMStoreFloat4x4(&m_WorldMatrix, WorldMatrix);
		XMStoreFloat4x4(&m_WorldMatrixInverse, XMMatrixInverse(nullptr, WorldMatrix));
	}

	void Set_CurrentNaviIndex(_vector _vWorldPos);

public:
	_bool  isMove(_fvector vWorldPos);
	_float Compute_Height(_fvector vWorldPos);
	vector<class CCell*>* Get_VecCells() { return &m_Cells; }	
	void   Set_CurCellIndex(_uint _CellIndex) { m_iCurrentCellIndex = _CellIndex; }
	_uint  Get_CurCellIndex() { return m_iCurrentCellIndex; }

	_vector                         Setting_SlidingMove(_fvector _vWorldPos);
	_bool                           bIsOn_Line(_fvector _vWorldPos);


#ifdef _DEBUG
public:
	HRESULT Render();
#endif

private:
	/* �� �׺� �̿��ϴ� ��ü�� ���� � �� �ȿ� �ִ���? */
	_int					m_iCurrentCellIndex = { -1 };
	vector<class CCell*>	m_Cells;	 


	static _float4x4       m_WorldMatrix; 
	static _float4x4       m_WorldMatrixInverse;
	int                     m_iNeighborIndex = {};

#ifdef _DEBUG
private:
	class CShader*			m_pShader = { nullptr };
	_bool                   m_bFirstPick = { true };

#endif

private:
	HRESULT SetUp_Neighbors();


public:
	static CNavigation* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const _tchar* pNavigationDataFile);
	static CNavigation* CreateOnly(ID3D11Device* pdevice, ID3D11DeviceContext* pContext);


	HRESULT	Create_Cell(const _float3 _vPoints[3]);
	HRESULT Delete_Cell(const _float3 _vPoints[3]);


	virtual CComponent* Clone(void* pArg) override; 
	virtual void Free() override; 
};
END

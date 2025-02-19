#pragma once

#include "Component.h"

BEGIN(Engine)

class CMesh;
class CTransform;

class ENGINE_DLL CCalculator final : public CComponent
{
public:
	typedef struct IntersectPos {
		_float fDist;
		_vector vPos;
	}INTERSECTPOS;

	typedef struct IntersectVtx {
		_vector v0;
		_vector v1;
		_vector v2;

		_vector vPoint;

		_vector vOutPoint;

		_float fDistance;

	}INTERSECTVTX;

	typedef struct VerticePos {
		_float fPointDistance;

		_vector vPointPosition;

	}VERTICEPOS;

private:
	CCalculator(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCalculator(const CCalculator& Prototype);
	virtual ~CCalculator() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	_bool PickingOnMesh(HWND hWnd, CMesh* pMeshBufferCom, CTransform* pMeshTransformCom, _Out_ _float& _fDist, _Out_ _vector& _fPos);
	_bool PickingOnVertice(HWND hWnd, CMesh* pMeshBufferCom, CTransform* pMeshTransformCom, _Out_ _float& _fDist, _Out_ _vector& _fPos);

	bool Intersects(
		FXMVECTOR Origin, FXMVECTOR Direction, FXMVECTOR V0,
		GXMVECTOR V1,
		HXMVECTOR V2, float& Dist, _Out_ float& V3, _Out_ float& V4);

public:
	static CCalculator* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END
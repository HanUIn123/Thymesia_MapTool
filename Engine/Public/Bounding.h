#pragma once

#include "Collider.h"
#include "DebugDraw.h"


BEGIN(Engine)

class CBounding abstract : public CBase
{
public:
	struct BOUNDING_DESC
	{
		_float3 vCenter;
	};

protected:
	CBounding(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CBounding() = default; 

public:
	virtual void* Get_Desc() const = 0;	

public:
	virtual HRESULT Initialize(const CBounding::BOUNDING_DESC* pArg) = 0;
	virtual void Update(_fmatrix WorldMatrix) = 0;
	virtual HRESULT Render(PrimitiveBatch<VertexPositionColor>* pBatch, _fvector vColor) = 0;	

public:
	virtual _bool Intersect(CCollider::TYPE eColliderType, CBounding* pTargetBounding) = 0;		

protected:
	ID3D11Device*				 m_pDevice  = { nullptr };
	ID3D11DeviceContext*		 m_pContext = { nullptr };

public:
	virtual void Free();

};

END
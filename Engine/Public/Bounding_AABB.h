#pragma once

#include "Bounding.h"


BEGIN(Engine)

class CBounding_AABB final : public CBounding
{
public:
	struct BOUNDING_AABB_DESC : public CBounding::BOUNDING_DESC
	{
		_float3 vExtents; 
	};

private:
	CBounding_AABB(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CBounding_AABB() = default; 

public:
	virtual void* Get_Desc() const override
	{
		return m_pDesc;	 
	}

public:
	virtual HRESULT Initialize(const CBounding::BOUNDING_DESC* pArg) override; 
	virtual void Update(_fmatrix WorldMatrix) override; 
	virtual HRESULT Render(PrimitiveBatch<VertexPositionColor>* pBatch, _fvector vColor) override;

public:
	virtual _bool Intersect(CCollider::TYPE eColliderType, CBounding* pTargetBounding) override; 
	//virtual BoundingBox*

private:
	BoundingBox* m_pOriginalDesc		= { nullptr };
	BoundingBox* m_pDesc				= { nullptr };

private:
	_bool Intersect_AABB(BoundingBox* pTargetDesc);


public:
	static CBounding_AABB* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const CBounding::BOUNDING_DESC* pArg);
	virtual void Free() override; 

};


END

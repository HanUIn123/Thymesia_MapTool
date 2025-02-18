#pragma once

#include "Bounding.h"

BEGIN(Engine)

class CBounding_Sphere final : public CBounding
{
public:
	struct BOUNDING_SPHERE_DESC : public CBounding::BOUNDING_DESC
	{
		_float     fRadius;
	};


private:
	CBounding_Sphere(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CBounding_Sphere() = default;

public:
	virtual void* Get_Desc() const override
	{
		return m_pDesc;
	}

public:
	virtual HRESULT Initialize(const CBounding::BOUNDING_DESC* pArg) override; 
	virtual void    Update(_fmatrix WorldMatrix) override;
	virtual HRESULT Render(PrimitiveBatch<VertexPositionColor>* pBatch, _fvector vColor) override; 

public:
	virtual _bool Intersect(CCollider::TYPE eColliderType, CBounding* pTargetBounding) override;

private:
	BoundingSphere* m_pOriginalDesc = { nullptr };
	BoundingSphere* m_pDesc         = { nullptr };

public:
	static CBounding_Sphere* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext,const CBounding::BOUNDING_DESC* pArg); 
	virtual void Free() override;	
};

END
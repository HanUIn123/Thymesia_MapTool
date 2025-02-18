#pragma once

#include "Bounding.h"

BEGIN(Engine)

class CBounding_OBB final : public CBounding
{
public:
	struct BOUNDING_OBB_DESC : public CBounding::BOUNDING_DESC
	{
		_float3  vExtents; 
		_float3  vRotation; 
	};


private:
	CBounding_OBB(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CBounding_OBB() = default; 


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

private:	
	BoundingOrientedBox*			m_pOriginalDesc = { nullptr };
	BoundingOrientedBox*			m_pDesc			= { nullptr };

public:
	static CBounding_OBB* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const CBounding::BOUNDING_DESC* pArg);
	virtual void Free() override;	
};

END
#include "Bounding_AABB.h"

CBounding_AABB::CBounding_AABB(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	:CBounding(pDevice, pContext)
{
}

HRESULT CBounding_AABB::Initialize(const CBounding::BOUNDING_DESC* pArg)
{
	const BOUNDING_AABB_DESC* pDesc = static_cast<const BOUNDING_AABB_DESC*>(pArg);

	m_pOriginalDesc		= new BoundingBox(pDesc->vCenter, pDesc->vExtents);
	m_pDesc				= new BoundingBox(*m_pOriginalDesc);

	return S_OK;	
}

void CBounding_AABB::Update(_fmatrix WorldMatrix)
{
	_matrix TransformMatrix = WorldMatrix;

	TransformMatrix.r[0] = XMVectorSet(1.f, 0.f, 0.f, 0.f) * XMVector3Length(WorldMatrix.r[0]);
	TransformMatrix.r[1] = XMVectorSet(0.f, 1.f, 0.f, 0.f) * XMVector3Length(WorldMatrix.r[1]);
	TransformMatrix.r[2] = XMVectorSet(0.f, 0.f, 1.f, 0.f) * XMVector3Length(WorldMatrix.r[2]);

	m_pOriginalDesc->Transform(*m_pDesc, TransformMatrix);	
}

HRESULT CBounding_AABB::Render(PrimitiveBatch<VertexPositionColor>* pBatch, _fvector vColor)
{

	DX::Draw(pBatch, *m_pDesc, vColor);

	return S_OK;	
}

_bool CBounding_AABB::Intersect(CCollider::TYPE eColliderType, CBounding* pTargetBounding)
{
	void* pTargetDesc = pTargetBounding->Get_Desc();

	_bool isColl = { false };

	switch(eColliderType)
	{
	case CCollider::TYPE_AABB:
		isColl = m_pDesc->Intersects(*static_cast<BoundingBox*>(pTargetDesc));	
		break;
	case CCollider::TYPE_OBB:
		isColl = m_pDesc->Intersects(*static_cast<BoundingOrientedBox*>(pTargetDesc));
		break;
	case CCollider::TYPE_SPHERE:
		isColl = m_pDesc->Intersects(*static_cast<BoundingSphere*>(pTargetDesc));
		break;
	}

	return isColl;	 

}

_bool CBounding_AABB::Intersect_AABB(BoundingBox* pTargetDesc)
{
	_float3		vSourMin, vSourMax;
	_float3		vDestMin, vDestMax;

	XMStoreFloat3(&vSourMin, XMLoadFloat3(&m_pDesc->Center) - XMLoadFloat3(&m_pDesc->Extents));
	XMStoreFloat3(&vSourMax, XMLoadFloat3(&m_pDesc->Center) + XMLoadFloat3(&m_pDesc->Extents));

	XMStoreFloat3(&vDestMin, XMLoadFloat3(&pTargetDesc->Center) - XMLoadFloat3(&pTargetDesc->Extents));
	XMStoreFloat3(&vDestMax, XMLoadFloat3(&pTargetDesc->Center) + XMLoadFloat3(&pTargetDesc->Extents));

	if (max(vSourMin.x, vDestMin.x) > min(vSourMax.x, vDestMax.x))
		return false;
	if (max(vSourMin.y, vDestMin.y) > min(vSourMax.y, vDestMax.y))
		return false;
	if (max(vSourMin.z, vDestMin.z) > min(vSourMax.z, vDestMax.z))
		return false;
	return true;
}

CBounding_AABB* CBounding_AABB::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const CBounding::BOUNDING_DESC* pArg)
{
	CBounding_AABB* pInstance = new CBounding_AABB(pDevice, pContext);

	if(FAILED(pInstance->Initialize(pArg)))	
	{
		MSG_BOX("Failed To Created : CBounding_AABB");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBounding_AABB::Free()
{
	__super::Free();	

	Safe_Delete(m_pOriginalDesc);
	Safe_Delete(m_pDesc);
}

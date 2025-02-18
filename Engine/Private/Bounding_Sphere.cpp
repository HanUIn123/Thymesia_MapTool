#include "Bounding_Sphere.h"

CBounding_Sphere::CBounding_Sphere(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :CBounding(pDevice, pContext)
{
}

HRESULT CBounding_Sphere::Initialize(const CBounding::BOUNDING_DESC* pArg)
{
    const BOUNDING_SPHERE_DESC*         pDesc = static_cast<const BOUNDING_SPHERE_DESC*>(pArg);

    m_pOriginalDesc = new BoundingSphere(pDesc->vCenter, pDesc->fRadius);
    m_pDesc         = new BoundingSphere(*m_pOriginalDesc);


    return S_OK;
}

void CBounding_Sphere::Update(_fmatrix WorldMatrix)
{
    m_pOriginalDesc->Transform(*m_pDesc, WorldMatrix);
}

HRESULT CBounding_Sphere::Render(PrimitiveBatch<VertexPositionColor>* pBatch, _fvector vColor)
{
    DX::Draw(pBatch, *m_pDesc, vColor);

    return S_OK;
}

_bool CBounding_Sphere::Intersect(CCollider::TYPE eColliderType, CBounding* pTargetBounding)
{
    void* pTargetDesc = pTargetBounding->Get_Desc();

    _bool isColl = { false };

    switch (eColliderType)  
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

CBounding_Sphere* CBounding_Sphere::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const CBounding::BOUNDING_DESC* pArg)
{
    CBounding_Sphere* pInstance = new CBounding_Sphere(pDevice, pContext);

    if(FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Created : CBounding_Sphere");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CBounding_Sphere::Free()
{
    __super::Free();

    Safe_Delete(m_pOriginalDesc);
    Safe_Delete(m_pDesc);
}

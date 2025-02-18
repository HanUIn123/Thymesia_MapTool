#include "Bounding_OBB.h"

CBounding_OBB::CBounding_OBB(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :CBounding(pDevice,pContext)
{
}

HRESULT CBounding_OBB::Initialize(const CBounding::BOUNDING_DESC* pArg)
{
    const BOUNDING_OBB_DESC* pDesc = static_cast<const BOUNDING_OBB_DESC*>(pArg);   
    
    _float4     vOrientation = {};

    XMStoreFloat4(&vOrientation, XMQuaternionRotationRollPitchYaw(pDesc->vRotation.x, pDesc->vRotation.y, pDesc->vRotation.z));

    m_pOriginalDesc = new BoundingOrientedBox(pDesc->vCenter, pDesc->vExtents, vOrientation);
    m_pDesc         = new BoundingOrientedBox(*m_pOriginalDesc);

    return S_OK;
}

void CBounding_OBB::Update(_fmatrix WorldMatrix)
{
    m_pOriginalDesc->Transform(*m_pDesc, WorldMatrix);  
}

HRESULT CBounding_OBB::Render(PrimitiveBatch<VertexPositionColor>* pBatch, _fvector vColor)
{

    DX::Draw(pBatch, *m_pDesc, vColor);

    return S_OK;    
}

_bool CBounding_OBB::Intersect(CCollider::TYPE eColliderType, CBounding* pTargetBounding)
{
    void* pTargetDesc = pTargetBounding->Get_Desc();

    _bool isColl = { false };

    switch (eColliderType)
    {
    case Engine::CCollider::TYPE_AABB:
        isColl = m_pDesc->Intersects(*static_cast<BoundingBox*>(pTargetDesc));
        break;
    case Engine::CCollider::TYPE_OBB:
        isColl = m_pDesc->Intersects(*static_cast<BoundingOrientedBox*>(pTargetDesc));  
        break;
    case Engine::CCollider::TYPE_SPHERE:
        isColl = m_pDesc->Intersects(*static_cast<BoundingSphere*>(pTargetDesc));   
        break;
    }

    return isColl;  
}

CBounding_OBB* CBounding_OBB::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const CBounding::BOUNDING_DESC* pArg)
{
    CBounding_OBB* pInstance = new CBounding_OBB(pDevice, pContext);

    if(FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Created : CBounding_OBB");
        Safe_Release(pInstance);
    }
    
    return pInstance;
}

void CBounding_OBB::Free()
{
    __super::Free();
    
    Safe_Delete(m_pOriginalDesc);   
    Safe_Delete(m_pDesc);   
    
}

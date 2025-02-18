#include "Collider.h"
#include "Bounding_AABB.h"
#include "GameInstance.h"   

UINT CCollider::g_iNextID = 0;  

CCollider::CCollider(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :CComponent(pDevice, pContext)
    , m_iID(0)
{
}

CCollider::CCollider(const CCollider& Prototype)
    :CComponent(Prototype)
    , m_eType(Prototype.m_eType)
#ifdef _DEBUG
    , m_pBatch(Prototype.m_pBatch)
    , m_pEffect(Prototype.m_pEffect)
    , m_pInputLayout(Prototype.m_pInputLayout)
#endif // _DEBUG
    , m_iID(g_iNextID++)
{
#ifdef _DEBUG
    Safe_AddRef(m_pInputLayout);
#endif // _DEBUG
}

HRESULT CCollider::Initialize_Prototype(TYPE eColliderType)
{
    m_eType = eColliderType;

#ifdef _DEBUG
    m_pBatch  = new PrimitiveBatch<VertexPositionColor>(m_pContext);
    m_pEffect = new BasicEffect(m_pDevice);

    m_pEffect->SetVertexColorEnabled(true);

    const void* pShaderByteCode = { nullptr };
    size_t      iShaderByteCodeLength = {};

    m_pEffect->GetVertexShaderBytecode(&pShaderByteCode, &iShaderByteCodeLength);
    //이 함수는 GPU와의 데이터 매핑(정점 데이터와 셰이더의 호환성)을 위해 셰이더 코드의 메모리 포인터를 반환합니다.

    if (FAILED(m_pDevice->CreateInputLayout(VertexPositionColor::InputElements,  // 입력 요소
        VertexPositionColor::InputElementCount, // 입력 요소 개수 
        pShaderByteCode,  // 셰이더 바이트 코드 시작 주소 
        iShaderByteCodeLength,  // 셰이더 바이트 코드 크기 
        &m_pInputLayout))) // 생성된 입력 레이아웃 출력
        return E_FAIL;
    

#endif // _DEBUG

    return S_OK;
}

HRESULT CCollider::Initialize(void* pArg)
{
    CBounding::BOUNDING_DESC* pBoundingDesc = static_cast<CBounding::BOUNDING_DESC*>(pArg);

    switch (m_eType)    
    {
    case Engine::CCollider::TYPE_AABB:
        m_pBounding = CBounding_AABB::Create(m_pDevice, m_pContext, pBoundingDesc);
        break;
    case Engine::CCollider::TYPE_OBB:
        break;
    case Engine::CCollider::TYPE_SPHERE:
        m_pBounding = CBounding_Sphere::Create(m_pDevice, m_pContext, pBoundingDesc);   
        break;
    }

    if (nullptr == m_pBounding)
        return E_FAIL;


    return S_OK;
}

void CCollider::Update(_fmatrix WorldMatrix)
{
    m_pBounding->Update(WorldMatrix);
}

_bool CCollider::Intersect(CCollider* pTargetCollider)
{
    m_isColl = m_pBounding->Intersect(pTargetCollider->m_eType, pTargetCollider->m_pBounding);

    return m_isColl;
}

HRESULT CCollider::Render()
{
    if (nullptr == m_pBounding)
        return E_FAIL;

    m_pEffect->SetWorld(XMMatrixIdentity()); // 로컬에서 월드매트릭스를 곱해서 나와서 단위행렬을 곱해주는거 (형식상)
    m_pEffect->SetView(m_pGameInstance->Get_Transform_Matrix(CPipeLine::D3DTS_VIEW));
    m_pEffect->SetProjection(m_pGameInstance->Get_Transform_Matrix(CPipeLine::D3DTS_PROJ));

    m_pEffect->Apply(m_pContext);

    m_pContext->IASetInputLayout(m_pInputLayout);
    
    m_pBatch->Begin();

    m_pBounding->Render(m_pBatch, true == m_isColl ? XMVectorSet(1.f, 0.f, 0.f, 1.f) : XMVectorSet(0.f, 1.f, 0.f, 1.f));


    m_pBatch->End();

    return S_OK;
}

CCollider* CCollider::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, TYPE eColliderType)
{
    CCollider* pInstance = new CCollider(pDevice, pContext);

    if(FAILED(pInstance->Initialize_Prototype(eColliderType)))
    {
        MSG_BOX("Failed to Created : CCollider");
        Safe_Release(pInstance);

    }

    return pInstance;
}

CComponent* CCollider::Clone(void* pArg)
{
    CCollider* pInstance = new CCollider(*this);

    if(FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Created : CCollider");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CCollider::Free()
{
    __super::Free();

    Safe_Release(m_pBounding);

#ifdef _DEBUG
    Safe_Release(m_pInputLayout);

    if(false == m_isCloned)
    {
        Safe_Delete(m_pBatch);
        Safe_Delete(m_pEffect);
    }

#endif // _DEBUG

}

#include "pch.h"
#include "TempCollider.h"
//#include "BlackScreen.h"
#include "GameInstance.h"
//#include "Bounding_AABB.h"
//#include "Bounding.h"

CTempCollider::CTempCollider(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
    :CGameObject{ _pDevice, _pContext }
{
}

CTempCollider::CTempCollider(const CTempCollider& _Prototype)
    :CGameObject(_Prototype)
{
}

HRESULT CTempCollider::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    return S_OK;
}

HRESULT CTempCollider::Initialize(void* _pArg)
{
    TC_DESC* pDesc = static_cast<TC_DESC*>(_pArg);

    m_tagInfoTempCollider.fPosition = pDesc->fPosition;
    m_tagInfoTempCollider.fRotation = pDesc->fRotation;
    m_tagInfoTempCollider.fScale = pDesc->fScale;

    if (FAILED(__super::Initialize(_pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;


    m_pTransformCom->Scaling(m_tagInfoTempCollider.fScale);
    //m_pTransformCom->Scaling(_float3(m_tagInfoTempCollider.fScale.x * 10.0f, m_tagInfoTempCollider.fScale.y * 10.0f, m_tagInfoTempCollider.fScale.z * 10.0f));
    m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_tagInfoTempCollider.fPosition.x, m_tagInfoTempCollider.fPosition.y, m_tagInfoTempCollider.fPosition.z, m_tagInfoTempCollider.fPosition.w));


    
    return S_OK;
}

void CTempCollider::Priority_Update(_float _fTimeDelta)
{
}

void CTempCollider::Update(_float _fTimeDelta)
{
}

void CTempCollider::Late_Update(_float _fTimeDelta)
{
    m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this);
}

HRESULT CTempCollider::Render()
{
    if (FAILED(Bind_ShaderResources()))
        return E_FAIL;

    m_pShaderCom->Begin(1);

    m_pVIBufferCom->Bind_InputAssembler();

    m_pVIBufferCom->Render();

    return S_OK;
}

HRESULT CTempCollider::Ready_Components()
{
    if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Cube"), TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
        return E_FAIL;

    if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxCube"), TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
        return E_FAIL;

    return S_OK;
}

HRESULT CTempCollider::Bind_ShaderResources()
{
    if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
        return E_FAIL;

    _float4x4   ViewMatrix, ProjMatrix;
    ViewMatrix = m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW);
    ProjMatrix = m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ);

    if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &ViewMatrix)))
        return E_FAIL;

    if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &ProjMatrix)))
        return E_FAIL;

    return S_OK;
}

_bool CTempCollider::Check_Collision_With_Player()
{
    return true;
}

void CTempCollider::Set_TempColliderScale(_float3 _vScale)
{
    m_tagInfoTempCollider.fScale = _vScale;
    m_pTransformCom->Scaling(_vScale);
}


CTempCollider* CTempCollider::Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
{
    CTempCollider* pInstance = new CTempCollider(_pDevice, _pContext);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed To Created : CTempCollider");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CTempCollider::Clone(void* _pArg)
{
    CTempCollider* pInstance = new CTempCollider(*this);

    if (FAILED(pInstance->Initialize(_pArg)))
    {
        MSG_BOX("Failed To Cloned : CTempCollider");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CTempCollider::Free()
{
    __super::Free();

    Safe_Release(m_pVIBufferCom);
    Safe_Release(m_pShaderCom);
}

#include "pch.h"
#include "SpecificObject.h"
#include "GameInstance.h"

CSpecificObject::CSpecificObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :CGameObject{pDevice, pContext}
{
}

CSpecificObject::CSpecificObject(const CSpecificObject& Prototype)
    :CGameObject(Prototype)
{
}

HRESULT CSpecificObject::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    return S_OK;
}

HRESULT CSpecificObject::Initialize(void* pArg)
{
    SpecificObject_Desc* pDesc = static_cast<SpecificObject_Desc*>(pArg);

    m_fFrustumRadius = pDesc->fFrustumRadius;

    m_fPosition = pDesc->fPosition;
    //m_fScale = pDesc->fScale;
    //m_fRotation = pDesc->fRotation;


    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    strcpy_s(m_MeshName, pDesc->ObjectName.c_str());

    if (FAILED(Ready_Components()))
        return E_FAIL;

    //m_pTransformCom->Scaling(_float3(m_fScale.x, m_fScale.y, m_fScale.z));
    m_pTransformCom->Rotation(pDesc->fRotation.x, pDesc->fRotation.y, pDesc->fRotation.z, pDesc->fRotation.w);
    //m_pTransformCom->Rotation(m_fRotation.x, m_fRotation.y, m_fRotation.z, m_fRotation.w);

    return S_OK;
}

void CSpecificObject::Priority_Update(_float fTimeDelta)
{
}

void CSpecificObject::Update(_float fTimeDelta)
{
#ifdef _DEBUG
    _matrix matWorld = XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrix_Ptr());

    matWorld.r[0] = XMVector3Normalize(matWorld.r[0]) * m_fFrustumRadius;
    matWorld.r[1] = XMVector3Normalize(matWorld.r[1]) * m_fFrustumRadius;
    matWorld.r[2] = XMVector3Normalize(matWorld.r[2]) * m_fFrustumRadius;

    _float yOffset = m_fFrustumRadius * 0.5f;
    matWorld.r[3] = XMVectorAdd(matWorld.r[3], XMVectorSet(0.f, yOffset, 0.f, 0.f));


    m_pColliderCom->Update(matWorld);
#endif
}

void CSpecificObject::Late_Update(_float fTimeDelta)
{
    m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this);
}

HRESULT CSpecificObject::Render()
{
    if (FAILED(Bind_ShaderResources()))
        return E_FAIL;

    _uint			iNumMeshes = m_pModelCom->Get_NumMeshes();

    for (size_t i = 0; i < iNumMeshes; i++)
    {
        if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_DIFFUSE, "g_DiffuseTexture", 0)))
            return E_FAIL;

        if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_NORMALS, "g_NormalTexture", 0)))
            return E_FAIL;

        m_pShaderCom->Begin(0);
        m_pModelCom->Render(i);
    }

    if (m_bFrustumSphere)
    {
        m_pColliderCom->Render();
    }

    return S_OK;
}

CSpecificObject::SpecificObject_Info CSpecificObject::Get_SpecificObjectInfo()
{
    SpecificObject_Info pInfo = {};

    strcpy_s(pInfo.szName, m_MeshName);

    pInfo.fFrustumRadius = m_fFrustumRadius;
    pInfo.fScale = m_pTransformCom->Get_Scale();
    //pInfo.fScale = m_fScale;
    pInfo.fRotation = m_pTransformCom->Get_Rotation();
    //pInfo.fRotation = m_fRotation;
    XMStoreFloat4(&pInfo.fPosition, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
    return pInfo;
}

void CSpecificObject::Set_SpecificObjectPosition(_float4 _vPosition)
{
    m_tagSpecificInfo.fPosition = _vPosition;
    m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&_vPosition));
}

void CSpecificObject::Set_SpecificObjectScale(_float3 _vScale)
{
    m_tagSpecificInfo.fScale = _vScale;
    m_pTransformCom->Scaling(_vScale);
}

void CSpecificObject::Set_SpecificObjectRotation(_float4 _vRotation)
{
    m_tagSpecificInfo.fRotation = _vRotation;

    _vector vQuat = XMQuaternionRotationRollPitchYaw(_vRotation.x, _vRotation.y, _vRotation.z);

    _float4 vQuaternion;
    XMStoreFloat4(&vQuaternion, vQuat);

    m_pTransformCom->Rotation(vQuaternion.x, vQuaternion.y, vQuaternion.z, vQuaternion.w);
}

void CSpecificObject::Set_FrustumRadius(_float fFrustumRadius)
{
    m_fFrustumRadius = fFrustumRadius;
}

HRESULT CSpecificObject::Ready_Components()
{
    if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxMesh"),
        TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
        return E_FAIL;

    CBounding_Sphere::BOUNDING_SPHERE_DESC SphereDesc{};
    SphereDesc.fRadius = 1.f;
    SphereDesc.vCenter = _float3(0.f, 0.f, 0.f);
    if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Collider_SPHERE"),
        TEXT("Com_Colldier"), reinterpret_cast<CComponent**>(&m_pColliderCom), &SphereDesc)))
        return E_FAIL;


    string strComponentName = "Prototype_Component_Model_";
    strComponentName += m_MeshName;
    _tchar		szComponentName[MAX_PATH] = {};

    MultiByteToWideChar(CP_ACP, 0, strComponentName.c_str(), strlen(strComponentName.c_str()), szComponentName, MAX_PATH);

    /* Com_Model */
    if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, szComponentName,TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
        return E_FAIL;

    return S_OK;
}

HRESULT CSpecificObject::Bind_ShaderResources()
{
    if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
        return E_FAIL;
    if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
        return E_FAIL;
    if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
        return E_FAIL;

    return S_OK;
}

CSpecificObject* CSpecificObject::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
    CSpecificObject* pInstance = new CSpecificObject(pDevice, pContext);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed To Created : CSpecificObject");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CSpecificObject::Clone(void* pArg)
{
    CSpecificObject* pInstance = new CSpecificObject(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed To Created : CSpecificObject");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CSpecificObject::Free()
{
    __super::Free();

    Safe_Release(m_pShaderCom);
    Safe_Release(m_pModelCom);
    Safe_Release(m_pColliderCom);
}

#include "pch.h"
#include "GroundObject.h"
#include "GameInstance.h"

CGroundObject::CGroundObject(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
    :CEnvironmentObject{ _pDevice, _pContext }
{
}

CGroundObject::CGroundObject(const CGroundObject& _Prototype)
    :CEnvironmentObject(_Prototype)
{
}

HRESULT CGroundObject::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    return S_OK;
}

HRESULT CGroundObject::Initialize(void* _pArg)
{
    if (FAILED(__super::Initialize(_pArg)))
        return E_FAIL;

    GROUND_OBJECCT_DESC* pDesc = static_cast<GROUND_OBJECCT_DESC*>(_pArg);

    if (pDesc->vecInstancePosition.empty())
        return E_FAIL;

    m_vecInstancePosition = pDesc->vecInstancePosition;
    m_vecInstanceScale = pDesc->vecInstanceScale;
    m_vecInstanceRotation = pDesc->vecInstanceRotation;

    m_iNumInstance = static_cast<_uint>(pDesc->vecInstancePosition.size());
    m_vecInstanceData.clear();
    m_vecInstanceData.reserve(m_iNumInstance);

    for (UINT i = 0; i < m_iNumInstance; ++i)
    {
        VTX_MODEL_INSTANCE instance;

        XMFLOAT3 fTerrainPos = pDesc->vecInstancePosition[i];

        XMMATRIX matScale = XMMatrixScaling(
            XMVectorGetX(XMLoadFloat3(&pDesc->vecInstanceScale[i])),
            XMVectorGetY(XMLoadFloat3(&pDesc->vecInstanceScale[i])),
            XMVectorGetZ(XMLoadFloat3(&pDesc->vecInstanceScale[i]))
        );

        XMMATRIX matRotationX = XMMatrixRotationX(m_vecInstanceRotation[i].x);
        XMMATRIX matRotationY = XMMatrixRotationY(m_vecInstanceRotation[i].y);
        XMMATRIX matRotationZ = XMMatrixRotationZ(m_vecInstanceRotation[i].z);
        XMMATRIX matRotation = matRotationX * matRotationY * matRotationZ;

        XMMATRIX matPosition = XMMatrixTranslation(fTerrainPos.x, fTerrainPos.y, fTerrainPos.z);
        XMMATRIX matWorld = matScale * matRotation * matPosition;

        XMFLOAT4X4 tempMatrix;
        XMStoreFloat4x4(&tempMatrix, matWorld);

        instance.InstanceMatrix[0] = XMFLOAT4(tempMatrix._11, tempMatrix._12, tempMatrix._13, tempMatrix._14);
        instance.InstanceMatrix[1] = XMFLOAT4(tempMatrix._21, tempMatrix._22, tempMatrix._23, tempMatrix._24);
        instance.InstanceMatrix[2] = XMFLOAT4(tempMatrix._31, tempMatrix._32, tempMatrix._33, tempMatrix._34);
        instance.InstanceMatrix[3] = XMFLOAT4(tempMatrix._41, tempMatrix._42, tempMatrix._43, tempMatrix._44);

        m_vecInstanceData.push_back(instance);
    }

    if (m_vecInstanceData.empty())
        return E_FAIL;

    if (FAILED(m_pModelCom->Create_InstanceBuffer(m_iNumInstance, m_vecInstanceData.data())))
    {
        return E_FAIL;
    }

    return S_OK;
}

void CGroundObject::Priority_Update(_float _fTimeDelta)
{
}

void CGroundObject::Update(_float _fTimeDelta)
{

#ifdef _DEBUG
    _matrix matWorld = XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrix_Ptr());

    matWorld.r[0] = XMVector3Normalize(matWorld.r[0]) * m_fFrustumRadius;
    matWorld.r[1] = XMVector3Normalize(matWorld.r[1]) * m_fFrustumRadius;
    matWorld.r[2] = XMVector3Normalize(matWorld.r[2]) * m_fFrustumRadius;


    m_pColliderCom->Update(matWorld);
#endif
}

void CGroundObject::Late_Update(_float _fTimeDelta)
{
    //if (m_pGameInstance->isIn_Frustum_WorldSpace(m_pTransformCom->Get_State(CTransform::STATE_POSITION), m_fFrustumRadius))
    m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this);
}

HRESULT CGroundObject::Render()
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
        m_pModelCom->Render_Instance(i, m_iNumInstance);
    }

    if (m_bFrustumSphere)
    {
        m_pColliderCom->Render();
    }


    return S_OK;
}

void CGroundObject::Update_InstanceBuffer(_uint _iInstanceIndex, const XMFLOAT3& _vPosition, const XMFLOAT3& _vScale, const XMFLOAT3& _vRotation)
{
    if (_iInstanceIndex >= m_iNumInstance)
        return;

    m_vecInstancePosition[_iInstanceIndex] = _vPosition;
    m_vecInstanceScale[_iInstanceIndex] = _vScale;
    m_vecInstanceRotation[_iInstanceIndex] = _vRotation;

    for (_uint i = 0; i < m_iNumInstance; ++i)
    {
        XMMATRIX matPosition = XMMatrixTranslation(m_vecInstancePosition[i].x, m_vecInstancePosition[i].y, m_vecInstancePosition[i].z);
        XMMATRIX matScale = XMMatrixScaling(m_vecInstanceScale[i].x, m_vecInstanceScale[i].y, m_vecInstanceScale[i].z);
        XMMATRIX matRotationX = XMMatrixRotationX(m_vecInstanceRotation[i].x);
        XMMATRIX matRotationY = XMMatrixRotationY(m_vecInstanceRotation[i].y);
        XMMATRIX matRotationZ = XMMatrixRotationZ(m_vecInstanceRotation[i].z);
        XMMATRIX matRotation = matRotationX * matRotationY * matRotationZ;

        XMMATRIX matWorld = matScale * matRotation * matPosition;

        XMFLOAT4X4 tempMatrix;
        XMStoreFloat4x4(&tempMatrix, matWorld);

        m_vecInstanceData[i].InstanceMatrix[0] = XMFLOAT4(tempMatrix._11, tempMatrix._12, tempMatrix._13, tempMatrix._14);
        m_vecInstanceData[i].InstanceMatrix[1] = XMFLOAT4(tempMatrix._21, tempMatrix._22, tempMatrix._23, tempMatrix._24);
        m_vecInstanceData[i].InstanceMatrix[2] = XMFLOAT4(tempMatrix._31, tempMatrix._32, tempMatrix._33, tempMatrix._34);
        m_vecInstanceData[i].InstanceMatrix[3] = XMFLOAT4(tempMatrix._41, tempMatrix._42, tempMatrix._43, tempMatrix._44);
    }

    m_pModelCom->Update_InstanceBuffer(m_iNumInstance, m_vecInstanceData.data());

}

HRESULT CGroundObject::Ready_Components()
{
    if (FAILED(__super::Ready_Components()))
        return E_FAIL;

    string strComponentName = "Prototype_Component_Model_";
    strComponentName += m_EnvironmentMeshName;

    _tchar		szComponentName[MAX_PATH] = {};

    MultiByteToWideChar(CP_ACP, 0, strComponentName.c_str(), strlen(strComponentName.c_str()), szComponentName, MAX_PATH);

    if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, szComponentName, TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
        return E_FAIL;


    return S_OK;
}

HRESULT CGroundObject::Bind_ShaderResources()
{
    if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
        return E_FAIL;
    if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
        return E_FAIL;
    if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
        return E_FAIL;

    return S_OK;
}

CGroundObject* CGroundObject::Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
{
    CGroundObject* pInstance = new CGroundObject(_pDevice, _pContext);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed To Created : CGroundObject");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CGroundObject::Clone(void* pArg)
{
    CGroundObject* pInstance = new CGroundObject(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed To Cloned : CGroundObject");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CGroundObject::Free()
{
    __super::Free();
}

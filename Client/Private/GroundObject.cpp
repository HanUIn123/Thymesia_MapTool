#include "pch.h"
#include "GroundObject.h"
#include "GameInstance.h"

CGroundObject::CGroundObject(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
    :CEnvironmentObject{_pDevice, _pContext}
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

    //pDesc->fPosition
    //_float fRadius = pDesc->fRange;
    //_float fSpacing = pDesc->fSpace;

    //m_iNumInstance = static_cast<_uint>(XM_PI * fRadius * fRadius);
    if (pDesc->vecPosition.empty())
        return E_FAIL;

    m_iNumInstance = static_cast<_uint>(pDesc->vecPosition.size());



    //m_iNumInstance = 10;
    m_vecInstanceData.clear();
    m_vecInstanceData.reserve(m_iNumInstance);


    //_float fMinRange = 1.0f;
    //_float fMaxRange = 10.0f;

    for (UINT i = 0; i < m_iNumInstance; ++i)
    {
        VTX_MODEL_INSTANCE instance;

       /* _float randX = fMinRange + static_cast<_float>(rand()) / (static_cast<_float>(RAND_MAX / (fMaxRange - fMinRange)));
        _float randZ = fMinRange + static_cast<_float>(rand()) / (static_cast<_float>(RAND_MAX / (fMaxRange - fMinRange)));

        XMMATRIX matScale = XMMatrixScaling(0.01f, 0.01f, 0.01f);
        XMMATRIX matTranslation = XMMatrixTranslation(randX, 0.0f, randZ);
        XMMATRIX matWorld = matScale * matTranslation;*/
        //XMMATRIX matScale = XMLoadFloat4x4(pDesc->fScaling);


        XMFLOAT3 fTerrainPos = pDesc->vecPosition[i];


        XMMATRIX matScale = XMMatrixScaling(
            XMVectorGetX(XMLoadFloat3(&pDesc->fScaling)), 
            XMVectorGetY(XMLoadFloat3(&pDesc->fScaling)),
            XMVectorGetZ(XMLoadFloat3(&pDesc->fScaling))
            );
     /*   XMMATRIX matPosition = XMMatrixTranslation(
            XMVectorGetX(XMLoadFloat4(&pDesc->fPosition)),
            XMVectorGetY(XMLoadFloat4(&pDesc->fPosition)),
            XMVectorGetZ(XMLoadFloat4(&pDesc->fPosition))
        );*/

        XMMATRIX matPosition = XMMatrixTranslation(fTerrainPos.x, fTerrainPos.y, fTerrainPos.z);
        XMMATRIX matWorld = matScale * matPosition;

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
#endif
}

void CGroundObject::Late_Update(_float _fTimeDelta)
{
    if (m_pGameInstance->isIn_Frustum_WorldSpace(m_pTransformCom->Get_State(CTransform::STATE_POSITION), m_fFrustumRadius))
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
        //m_pModelCom->Render(i);

        m_pModelCom->Render_Instance(m_iNumInstance);
    }

    return S_OK;
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

    //if (FAILED(m_pShaderCom->Bind_SRV("g_InstanceMatrix", m_pModelCom->Get_InstanceBuffer())))
    //    return E_FAIL;

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

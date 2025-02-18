#include "pch.h"
#include "Ladder.h"
#include "GameInstance.h"

CLadder::CLadder(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :CGameObject(pDevice, pContext)
{
}

CLadder::CLadder(const CLadder& Prototype)
    :CGameObject(Prototype)
{
}

HRESULT CLadder::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    return S_OK;
}

HRESULT CLadder::Initialize(void* pArg)
{
    CGameObject::GAMEOBJECT_DESC        Desc{};

    Desc.fSpeedPerSec = 45.f;
    Desc.fRotationPerSec = XMConvertToRadians(90.f);

    if (FAILED(__super::Initialize(&Desc)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    return S_OK;
}

void CLadder::Priority_Update(_float fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CLadder::Update(_float fTimeDelta)
{
    _vector		vCurPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
    _vector test = { 0.f,0.f,0.f,1.f };

    __super::Update(fTimeDelta);
}

void CLadder::Late_Update(_float fTimeDelta)
{
    __super::Late_Update(fTimeDelta);

#ifdef _DEBUG
    m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this);
#endif
}

HRESULT CLadder::Render()
{
    if (FAILED(Bind_ShaderResources()))
        return E_FAIL;

    _uint			iNumMeshes = m_pModelCom->Get_NumMeshes();

    for (size_t i = 0; i < iNumMeshes; i++)
    {
        if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_DIFFUSE, "g_DiffuseTexture", 0)))
            return E_FAIL;

        if (i != 8)  // 이거 나중에 이유 찾아보기 
        {
            if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_NORMALS, "g_NormalTexture", 0)))
                return E_FAIL;
        }

        //if (FAILED(m_pModelCom->Bind_BoneMatrices(m_pShaderCom, i, "g_BoneMatrices")))   // 여기서 이동값을 없애줘야겟네
        //    return E_FAIL;

        m_pShaderCom->Begin(0);
        m_pModelCom->Render(i);
    }

    return S_OK;
}

HRESULT CLadder::Ready_Components()
{
    /* Com_Shader */
    if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxMesh"),
        TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
        return E_FAIL;

    /* Com_Model */
    if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Ladder"),
        TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
        return E_FAIL;

    return S_OK;
}

HRESULT CLadder::Bind_ShaderResources()
{
    if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
        return E_FAIL;
    if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
        return E_FAIL;
    if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
        return E_FAIL;

    return S_OK;
}

CLadder* CLadder::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
    CLadder* pInstance = new CLadder(pDevice, pContext);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed To Created : CLadder");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CLadder::Clone(void* pArg)
{
    CLadder* pInstance = new CLadder(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed To Cloned : CLadder");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CLadder::Free()
{
    __super::Free();

    Safe_Release(m_pModelCom);
    Safe_Release(m_pShaderCom);
}


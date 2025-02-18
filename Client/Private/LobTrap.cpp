#include "pch.h" 
#include "LobTrap.h" 
#include "GameInstance.h"
#include "Animation.h"

CLobTrap::CLobTrap(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    : CGameObject{ pDevice, pContext }
{
}

CLobTrap::CLobTrap(const CLobTrap& Prototype)
    : CGameObject(Prototype) 
{
}

HRESULT CLobTrap::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))    
        return E_FAIL;  

    return S_OK;    
}

HRESULT CLobTrap::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))  
        return E_FAIL;  

    if (FAILED(Ready_Components())) 
        return E_FAIL;  

    m_pTransformCom->Set_State(CTransform::STATE_POSITION, _fvector{ 232.f,62.f,60.f,1.f });
    //m_pTransformCom->Scaling(_float3(0.1f, 0.1f, 0.1f));

    return S_OK;
}

void CLobTrap::Priority_Update(_float fTimeDelta)
{
}

void CLobTrap::Update(_float fTimeDelta)
{
  
  
}

void CLobTrap::Late_Update(_float fTimeDelta)
{
    m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this); 
}

HRESULT CLobTrap::Render()
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

        m_pShaderCom->Begin(0); 
        m_pModelCom->Render(i);
    }

    return S_OK;
}

HRESULT CLobTrap::Render_Shadow()
{
    if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
        return E_FAIL;
    if (FAILED(m_pGameInstance->Bind_Shadow_Matrices(m_pShaderCom, "g_ViewMatrix", "g_ProjMatrix")))
        return E_FAIL;

    _uint			iNumMeshes = m_pModelCom->Get_NumMeshes();

    for (size_t i = 0; i < iNumMeshes; i++)
    {
        if (FAILED(m_pModelCom->Bind_BoneMatrices(m_pShaderCom, i, "g_BoneMatrices")))
            return E_FAIL;

        m_pShaderCom->Begin(2);
        m_pModelCom->Render(i);
    }

    return S_OK;    
}

HRESULT CLobTrap::Ready_Components()
{
    /* Com_Shader */
    if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxMesh"),
        TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
        return E_FAIL;

    /* Com_Model */
    if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_LobTrap"),
        TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
        return E_FAIL;


    return S_OK;
}

HRESULT CLobTrap::Bind_ShaderResources()
{
    if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
        return E_FAIL;
    if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
        return E_FAIL;
    if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
        return E_FAIL;

    return S_OK;
}

CLobTrap* CLobTrap::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
    CLobTrap* pInstance = new CLobTrap(pDevice, pContext);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed To Created : CLobTrap");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CLobTrap::Clone(void* pArg)
{
    CLobTrap* pInstance = new CLobTrap(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed To Cloned : CLobTrap");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CLobTrap::Free()
{
    __super::Free();

    Safe_Release(m_pShaderCom);
    Safe_Release(m_pModelCom);

}

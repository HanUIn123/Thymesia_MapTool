#include "pch.h"
#include "Boss_Varg.h"
#include "GameInstance.h"

CBoss_Varg::CBoss_Varg(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    : CGameObject(pDevice, pContext)
{
}

CBoss_Varg::CBoss_Varg(const CBoss_Varg& Prototype)
    : CGameObject(Prototype)
{
}

HRESULT CBoss_Varg::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    return S_OK;
}

HRESULT CBoss_Varg::Initialize(void* pArg)
{
    strcpy_s(m_szName, "BOSS_VARG");

    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    m_pTransformCom->Set_State(CTransform::STATE_POSITION, _fvector{ 232.f,62.f,60.f,1.f });
    m_pTransformCom->Scaling(_float3{ 0.1f, 0.1f, 0.1f });

    m_pModelCom->SetUp_Animation(25, true);
    return S_OK;
}

void CBoss_Varg::Priority_Update(_float fTimeDelta)
{
}

void CBoss_Varg::Update(_float fTimeDelta)
{
    m_pModelCom->Play_Animation(fTimeDelta * 2.f);
}

void CBoss_Varg::Late_Update(_float fTimeDelta)
{
    m_pGameInstance->Add_RenderGroup(CRenderer::RG_NONBLEND, this);
}

HRESULT CBoss_Varg::Render()
{
    if (FAILED(Bind_ShaderResources()))
        return E_FAIL;

    _uint			iNumMeshes = m_pModelCom->Get_NumMeshes();

    for (size_t i = 0; i < iNumMeshes; i++)
    {

        if (FAILED(m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_DIFFUSE, "g_DiffuseTexture", 0)))
            return E_FAIL;

        m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_NORMALS, "g_NormalTexture", 0);


        if (FAILED(m_pModelCom->Bind_BoneMatrices(m_pShaderCom, i, "g_BoneMatrices")))   // 여기서 이동값을 없애줘야겟네
            return E_FAIL;

        m_pShaderCom->Begin(0);
        m_pModelCom->Render(i);
    }

    return S_OK;
}

HRESULT CBoss_Varg::Ready_Components()
{
    /* Com_Shader */
    if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxAnimMesh"),
        TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
        return E_FAIL;

    /* Com_Model */
    if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Boss_Varg"),
        TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
        return E_FAIL;

    return S_OK;
}

HRESULT CBoss_Varg::Bind_ShaderResources()
{
    if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
        return E_FAIL;

    if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
        return E_FAIL;
    if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
        return E_FAIL;

    return S_OK;
}

void CBoss_Varg::OnCollisionEnter(CGameObject* _pOther)
{
}

void CBoss_Varg::OnCollision(CGameObject* _pOther)
{
}

void CBoss_Varg::OnCollisionExit(CGameObject* _pOther)
{
}

CBoss_Varg* CBoss_Varg::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
    CBoss_Varg* pInstance = new CBoss_Varg(pDevice, pContext);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed To Created : CBoss_Varg");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CBoss_Varg::Clone(void* pArg)
{
    CBoss_Varg* pInstance = new CBoss_Varg(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed To Cloned : CBoss_Varg");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CBoss_Varg::Free()
{
    __super::Free();

    Safe_Release(m_pColliderCom);
    Safe_Release(m_pShaderCom);
    Safe_Release(m_pModelCom);
    Safe_Release(m_pNavigationCom);
}

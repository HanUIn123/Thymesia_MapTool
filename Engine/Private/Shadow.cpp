#include "Shadow.h"
#include "Shader.h"
#include "GameObject.h"

CShadow::CShadow(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :m_pDevice{pDevice}
    ,m_pContext{pContext}
{
    Safe_AddRef(m_pDevice);
    Safe_AddRef(m_pContext);
}

HRESULT CShadow::Initialize()
{
    return S_OK;    
}

HRESULT CShadow::SetUp_ShadowLight(_fvector vEye, _fvector vAt, _float fLightAngle, _float fAspect, _float fNear, _float fFar,class CGameObject* _pPlayer)
{
    XMStoreFloat4x4(&m_LightViewMatrix, XMMatrixLookAtLH(vEye, vAt, XMVectorSet(0.f, 1.f, 0.f, 0.f)));
    XMStoreFloat4x4(&m_LightProjMatrix, XMMatrixPerspectiveFovLH(fLightAngle, fAspect, fNear, fFar));

    m_pPlayer = _pPlayer; 
     

    m_pPlayerTransform = _pPlayer->Get_Transfrom(); 
    

    return S_OK;    
}

void CShadow::Update()  
{
    if (m_pPlayer != nullptr)
    {
        _fvector  m_pPlayerPos = m_pPlayerTransform->Get_State(CTransform::STATE_POSITION);


        _fvector  vEye = { m_pPlayerPos.m128_f32[0], m_pPlayerPos.m128_f32[1] + 150.f , m_pPlayerPos.m128_f32[2] + 100.f, 1.f };
        _fvector  vAt = { m_pPlayerPos.m128_f32[0],  m_pPlayerPos.m128_f32[1], m_pPlayerPos.m128_f32[2], 1.f };

        XMStoreFloat4x4(&m_LightViewMatrix, XMMatrixLookAtLH(vEye, vAt, XMVectorSet(0.f, 1.f, 0.f, 0.f)));
        XMStoreFloat4x4(&m_LightProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(90.f), g_iWinSize_X / static_cast<_float>(g_iWinSize_Y), 0.1f, 1000.f));
    }
}

HRESULT CShadow::Bind_ViewMatrix(CShader* pShader, const _char* pConstantName)
{
    if (FAILED(pShader->Bind_Matrix(pConstantName, &m_LightViewMatrix)))    
        return E_FAIL;  

    return S_OK;    
}

HRESULT CShadow::Bind_ProjMatrix(CShader* pShader, const _char* pConstantName)
{
    if (FAILED(pShader->Bind_Matrix(pConstantName, &m_LightProjMatrix)))
        return E_FAIL;

    return S_OK;    
}


CShadow* CShadow::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
    CShadow* pInstance = new CShadow(pDevice, pContext);

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed To Created : CShadow");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CShadow::Free()
{
    __super::Free();

    Safe_Release(m_pDevice);
    Safe_Release(m_pContext);
}

#include "EffectMgr.h"
#include "GameObject.h"

CEffectMgr::CEffectMgr(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :m_pDevice(pDevice)
    ,m_pContext(pContext)
{
    Safe_AddRef(pDevice);
    Safe_AddRef(pContext);
}

HRESULT CEffectMgr::Initialize()
{

    return S_OK;    
}

void CEffectMgr::Priority_Update(_float _fTimeDelta)
{
    for (auto& iter : m_vecEffect)
        iter->Priority_Update(_fTimeDelta); 
}

void CEffectMgr::Update(_float _fTimeDelta)
{
    for (auto& iter : m_vecEffect)
        iter->Update(_fTimeDelta);
}

void CEffectMgr::Late_Update(_float _fTimeDelta)
{
    for (auto& iter : m_vecEffect)
        iter->Late_Update(_fTimeDelta); 
}



HRESULT CEffectMgr::Add_Effect(CGameObject* pEffect)
{
    if (pEffect == nullptr)
        return E_FAIL; 

    m_vecEffect.push_back(pEffect); 

    return S_OK;    
}

HRESULT CEffectMgr::Sub_Effect(CGameObject* pEffect)
{
    for (auto iter = m_vecEffect.begin(); iter != m_vecEffect.end(); iter++)
    {
        if (*iter == pEffect)
        {
            m_vecEffect.erase(iter);
            pEffect->Release();
            return S_OK;    
        }
    }

    return E_FAIL;  
}

CEffectMgr* CEffectMgr::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
    CEffectMgr* pInstance = new CEffectMgr(pDevice, pContext);
  
    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CEffectMgr");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CEffectMgr::Free()
{
    __super::Free();

    for (auto& iter : m_vecEffect)
        Safe_Release(iter);

    m_vecEffect.clear();    

    Safe_Release(m_pDevice);
    Safe_Release(m_pContext);   
}

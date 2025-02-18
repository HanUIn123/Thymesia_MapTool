#include "Event.h"
#include "GameObject.h"

CEvent::CEvent(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :m_pDevice(pDevice)
    ,m_pContext(pContext)
{
    Safe_AddRef(pDevice);
    Safe_AddRef(pContext);
}

HRESULT CEvent::Initalize()
{
    m_vecEventObject.reserve(20);   

    return S_OK;
}

void CEvent::Activate(_wstring _EventName)
{
    for (auto& iter : m_vecEventObject)
        iter->IsTriggerOn(_EventName);    
}

HRESULT CEvent::Add_EventObject(CGameObject* pGameObject)
{
    if (pGameObject == nullptr)
        return E_FAIL;

    m_vecEventObject.push_back(pGameObject);
    Safe_AddRef(pGameObject);

    return S_OK;
}

HRESULT CEvent::Sub_EventObject(CGameObject* pGameObject)
{
    if (pGameObject == nullptr) 
        return E_FAIL;  


    for (auto& iterator = m_vecEventObject.begin(); iterator != m_vecEventObject.end(); iterator++)
    {
        if (*iterator == pGameObject)   
        {
            m_vecEventObject.erase(iterator);       
            Safe_Release(pGameObject);  

            if (m_vecEventObject.size() == 0)   
                break; 
        }
    }


    return S_OK;
}

CEvent* CEvent::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
    CEvent* pInstance = new CEvent(pDevice, pContext);

    if (FAILED(pInstance->Initalize()))
    {
        MSG_BOX("Failed to Created : CEvent");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CEvent::Free()
{
    __super::Free();

    for (auto& iter : m_vecEventObject)
        Safe_Release(iter);

    m_vecEventObject.clear();   

    Safe_Release(m_pDevice);
    Safe_Release(m_pContext);
}

#include "ItemMgr.h"
#include "GameInstance.h"

CItemMgr::CItemMgr()
    :m_pGameInstance(CGameInstance::GetInstance())  
{
    Safe_AddRef(m_pGameInstance);
}

HRESULT CItemMgr::Initialize()
{
    return S_OK;    
}

HRESULT CItemMgr::Update()
{
    return S_OK;
}



_uint CItemMgr::Count_Item(_wstring _ItemName)
{
    auto& iter = m_mapItemBag.find(_ItemName);


    if (iter != m_mapItemBag.end())
    {
        return iter->second;
    }

    else
        return 0;

}

HRESULT CItemMgr::Add_Item(_wstring _ItemName)
{
    auto& iter = m_mapItemBag.find(_ItemName);  


    if(iter != m_mapItemBag.end())
    {
        iter->second++; 
    }

    else
       m_mapItemBag.emplace(_ItemName, 1); 
    

    return S_OK;    
}

HRESULT CItemMgr::Sub_Item(_wstring _ItemName)
{

    auto& iter = m_mapItemBag.find(_ItemName);

    if (iter != m_mapItemBag.end())
    {
        if (iter->second != 0)
            iter->second--;

    }

    else
        return E_FAIL;  


    return S_OK;
}

CItemMgr* CItemMgr::Create()
{
    CItemMgr* pInstance = new CItemMgr();

    if(FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : ItemMgr");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CItemMgr::Free()
{
    __super::Free();    

    Safe_Release(m_pGameInstance);  
    m_mapItemBag.clear();   
}

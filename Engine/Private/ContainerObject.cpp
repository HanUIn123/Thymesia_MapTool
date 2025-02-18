#include "ContainerObject.h"
#include "GameInstance.h"



CContainerObject::CContainerObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :CGameObject(pDevice,pContext)
{
}

CContainerObject::CContainerObject(const CContainerObject& Prototype)
    :CGameObject(Prototype)
{
}

HRESULT CContainerObject::Initialize_Prototype()
{
    return S_OK;
}

HRESULT CContainerObject::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;  

    return S_OK;    
}

void CContainerObject::Priority_Update(_float fTimeDelta)
{
    for (auto& Pair : m_PartObjects)
    {
        if (nullptr != Pair.second)
            Pair.second->Priority_Update(fTimeDelta);
    }
}

void CContainerObject::Update(_float fTimeDelta)
{
    for (auto& Pair : m_PartObjects)
    {
        if (nullptr != Pair.second)
            Pair.second->Update(fTimeDelta);
    }
}

void CContainerObject::Late_Update(_float fTimeDelta)
{
    for (auto& Pair : m_PartObjects)
    {
        if (nullptr != Pair.second)
            Pair.second->Late_Update(fTimeDelta);   
    }
}

HRESULT CContainerObject::Render()
{
    return S_OK;
}

HRESULT CContainerObject::Add_PartObject(const _wstring& strPartTag, _uint ePrototypeLevelID, const _wstring& strPrototypeTag, CPartObject::PARTOBJECT_DESC* pDesc)
{
    CPartObject*      pPartObject = { nullptr }; 

    pPartObject = dynamic_cast<CPartObject*>(m_pGameInstance->Clone_Prototype(PROTOTYPE::TYPE_GAMEOBJECT, ePrototypeLevelID, strPrototypeTag, pDesc));
    if (nullptr == pPartObject)
        return E_FAIL;  

    m_PartObjects.emplace(strPartTag, pPartObject);

    return S_OK;    
}

CComponent* CContainerObject::Find_PartObject_Component(const _wstring& strPartTag, const _wstring& strComponentTag)
{
    auto iter = m_PartObjects.find(strPartTag);
    if (iter == m_PartObjects.end())
        return nullptr; 

    return (iter->second)->Find_Component(strComponentTag); 
}

void CContainerObject::Free()
{
    __super::Free();

    for (auto& Pair : m_PartObjects)
        Safe_Release(Pair.second);
    
    m_PartObjects.clear();  
}

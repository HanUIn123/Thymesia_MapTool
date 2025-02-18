#include "Bounding.h"

CBounding::CBounding(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :m_pDevice(pDevice)
    ,m_pContext(pContext)
{
    Safe_AddRef(m_pContext);    
    Safe_AddRef(m_pDevice); 
}

void CBounding::Free()
{
    __super::Free();

    Safe_Release(m_pContext);   
    Safe_Release(m_pDevice);    

}

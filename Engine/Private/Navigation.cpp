#include "Navigation.h"
#include "Cell.h"   


#ifdef _DEBUG
#include "Shader.h"
#include "GameInstance.h"   
#endif

_float4x4 CNavigation::m_WorldMatrix = {}; // static변수라 바로 초기화 못하고 이렇게 cpp와서 초기화 해줘야함.
_float4x4 CNavigation::m_WorldMatrixInverse = {}; // 그리고 또한 월드 매트릭스가 현재 여러개 생성되면 안되니깐 이렇게
// Staic 변수로 만들어줘서 하나의 메모리 주소만 생성되게 해서 공유할 수 있도록 함. 

CNavigation::CNavigation(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :CComponent(pDevice,pContext)
{
}

CNavigation::CNavigation(const CNavigation& Prototype)
    :CComponent(Prototype)
    ,m_Cells(Prototype.m_Cells)
#ifdef _DEBUG
    ,m_pShader(Prototype.m_pShader)
#endif // _DEBUG
{
#ifdef _DEBUG
    Safe_AddRef(m_pShader);
#endif // _DEBUG
    for (auto& pCell : m_Cells)
        Safe_AddRef(pCell);
}

HRESULT CNavigation::Initialize_Prototype(const _tchar* pNavigationDataFile)
{
    _ulong  dwByte = {};
    HANDLE  hFile = CreateFile(pNavigationDataFile, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    while (true)
    {
        _float3  vPoints[CCell::POINT_END] = {};

        ReadFile(hFile, vPoints, sizeof(_float3) * 3, &dwByte, nullptr);

        if (dwByte == 0)
            break;

        CCell* pCell = CCell::Create(m_pDevice, m_pContext, vPoints, m_Cells.size());

        if (nullptr == pCell)
            return E_FAIL;

        m_Cells.push_back(pCell);
    }

    CloseHandle(hFile);
    
    XMStoreFloat4x4(&m_WorldMatrix, XMMatrixIdentity());
    XMStoreFloat4x4(&m_WorldMatrixInverse, XMMatrixIdentity());


#ifdef _DEBUG
    m_pShader = CShader::Create(m_pDevice, m_pContext, TEXT("../../EngineSDK/Hlsl/Shader_Cell.hlsl"), VTXPOS::Elements, VTXPOS::iNumElements);
    if (nullptr == m_pShader)
        return E_FAIL;
#endif // _DEBUG

    if (FAILED(SetUp_Neighbors()))
        return E_FAIL;

    return S_OK;
}

HRESULT CNavigation::Initialize(void* pArg)
{
    if (nullptr != pArg)
    {
        NAVIGATION_DESC* pDesc = static_cast<NAVIGATION_DESC*>(pArg);

        m_iCurrentCellIndex    = pDesc->iCurrentCellIndex; 
    }

    return S_OK;
}

_bool CNavigation::isMove(_fvector vWorldPos)
{
    _vector     vPosition = XMVector3TransformCoord(vWorldPos, XMLoadFloat4x4(&m_WorldMatrixInverse));

    _int        iNeighborIndex = { -1 }; // -1로 설정되면 이웃이 없다는 거를 의미.

    if (false == m_Cells[m_iCurrentCellIndex]->isIn(vPosition, &iNeighborIndex))
    {
        /* 나간 방향에 이웃이 있다면? */
        if (-1 != iNeighborIndex)
        {
            while (true)
            {
                if (-1 == iNeighborIndex)
                    return false;
                if (true == m_Cells[iNeighborIndex]->isIn(vPosition, &iNeighborIndex))
                    break;
            }

            m_iCurrentCellIndex = iNeighborIndex;
            return true;
        }
        else
            return false;
    }
    else
        return true;

}

_float CNavigation::Compute_Height(_fvector vWorldPos)
{
    if (-1 == m_iCurrentCellIndex)
        return 0.f;

    _vector vPosition = XMVector3TransformCoord(vWorldPos, XMLoadFloat4x4(&m_WorldMatrixInverse));

    vPosition = XMVectorSetY(vPosition, m_Cells[m_iCurrentCellIndex]->Compute_Height(vPosition));

    vPosition = XMVector3TransformCoord(vPosition, XMLoadFloat4x4(&m_WorldMatrix));  
    
    return XMVectorGetY(vPosition);
}

#ifdef _DEBUG
HRESULT CNavigation::Render()
{
    if (FAILED(m_pShader->Bind_Matrix("g_WorldMatrix", &m_WorldMatrix)))
        return E_FAIL;

    if (FAILED(m_pShader->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW))))
        return E_FAIL;

    if (FAILED(m_pShader->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ))))
        return E_FAIL;


    _float4  vColor = -1 == m_iCurrentCellIndex ? _float4(0.f, 1.f, 0.f, 1.f) : _float4(1.f, 0.f, 0.f, 1.f);
    
    if(FAILED(m_pShader->Bind_RawValue("g_vColor",&vColor, sizeof(_float4))))
        return E_FAIL;

    if( -1 == m_iCurrentCellIndex)
    {
        m_pShader->Begin(0);
        for (auto& pCell : m_Cells)
            pCell->Render();
    }
    
    else
    {
        _float4x4 WorldMatrix = m_WorldMatrix;

        WorldMatrix.m[3][1] += 0.1f;  // 이거는 월드매트릭스에 직접 접근한거 3번째줄이 POSITION줄을 의미하고 거기에 1번은 Y값

        if (FAILED(m_pShader->Bind_Matrix("g_WorldMatrix", &WorldMatrix)))
            return E_FAIL;

        m_pShader->Begin(0);
        
        m_Cells[m_iCurrentCellIndex]->Render(); 
    }

    return S_OK;
}
#endif

HRESULT CNavigation::SetUp_Neighbors()
{
    for (auto& pSourCell : m_Cells)
    {
        for (auto& pDestCell : m_Cells)
        {
            if (pSourCell == pDestCell)
                continue;

            if (true == pDestCell->Compare_Points(pSourCell->Get_Point(CCell::POINT_A), pSourCell->Get_Point(CCell::POINT_B)))
                pSourCell->Set_Neighbor(CCell::LINE_AB, pDestCell);
            if (true == pDestCell->Compare_Points(pSourCell->Get_Point(CCell::POINT_B), pSourCell->Get_Point(CCell::POINT_C)))
                pSourCell->Set_Neighbor(CCell::LINE_BC, pDestCell);
            if (true == pDestCell->Compare_Points(pSourCell->Get_Point(CCell::POINT_C), pSourCell->Get_Point(CCell::POINT_A)))
                pSourCell->Set_Neighbor(CCell::LINE_CA, pDestCell);
        }
    }

    return S_OK;    
}

CNavigation* CNavigation::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const _tchar* pNavigationDataFile)
{
    CNavigation* pInstance = new CNavigation(pDevice, pContext);

    if (FAILED(pInstance->Initialize_Prototype(pNavigationDataFile)))
    {
        MSG_BOX("Failed To Created : CNavigation");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CComponent* CNavigation::Clone(void* pArg)
{
    CNavigation* pInstance = new CNavigation(*this);    

    if (FAILED(pInstance->Initialize(pArg)))    
    {
        MSG_BOX("Failed To Cloned : CNavigation");
        Safe_Release(pInstance);    
    }

    return pInstance;
}

void CNavigation::Free()
{
    __super::Free();

#ifdef _DEBUG
    Safe_Release(m_pShader);
#endif

    for (auto& pCell : m_Cells)
        Safe_Release(pCell);

    m_Cells.clear();
}

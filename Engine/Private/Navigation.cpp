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
    :CComponent(pDevice, pContext)
{
}

CNavigation::CNavigation(const CNavigation& Prototype)
    :CComponent(Prototype)
    , m_Cells(Prototype.m_Cells)
#ifdef _DEBUG
    , m_pShader(Prototype.m_pShader)
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
    _ulong      dwByte = {};
    HANDLE hFile = CreateFile(pNavigationDataFile, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    _uint iTotalFloorNum = {};
    ReadFile(hFile, &iTotalFloorNum, sizeof(_uint), &dwByte, nullptr);


    _uint iCellCountNum = {};
    ReadFile(hFile, &iCellCountNum, sizeof(_uint), &dwByte, nullptr);

    //while (true)
    //map<_uint>
    for (_uint t = 0; t < iTotalFloorNum; ++t)
    {
        for (_uint i = 0; i < iCellCountNum; ++i)
        {
            //_float3         vPoints[CCell::POINT_END] = {};
            _float3         vPoints[CCell::POINT_END] = {};

            ReadFile(hFile, vPoints, sizeof(_float3) * 3, &dwByte, nullptr);

            // 루프 탈출문 조건
            if (0 == dwByte)
                break;

            // size 로 줘서 처음에 하나 들어가면 용량 1개, 하나 또 들어가면 2개.~~ 
            CCell* pCell = CCell::Create(m_pDevice, m_pContext, vPoints, (_uint)(m_Cells.size()));
            //CCell* pCell = CCell::Create(m_pDevice, m_pContext, vPoints, iCellCountNum);
            if (nullptr == pCell)
                return E_FAIL;

            m_Cells.push_back(pCell);
        }
    }

    CloseHandle(hFile);

    XMStoreFloat4x4(&m_WorldMatrix, XMMatrixIdentity());
    XMStoreFloat4x4(&m_WorldMatrixInverse, XMMatrixIdentity());

#ifdef _DEBUG
    m_pShader = CShader::Create(m_pDevice, m_pContext, TEXT("../../EngineSDK/Hlsl/Shader_Cell.hlsl"), VTXPOS::Elements, VTXPOS::iNumElements);
    if (nullptr == m_pShader)
        return E_FAIL;
#endif

    // 이제 이걸 호출해줘야 최종적으로 현재 셀 4개 를 뛰놀수 있게 되었음. 
    if (FAILED(SetUp_Neighbors()))
        return E_FAIL;


    return S_OK;
}

HRESULT CNavigation::Initialize_Prototype_CreateOnly()
{
    XMStoreFloat4x4(&m_WorldMatrix, XMMatrixIdentity());
    XMStoreFloat4x4(&m_WorldMatrixInverse, XMMatrixIdentity());

#ifdef _DEBUG
    m_pShader = CShader::Create(m_pDevice, m_pContext, TEXT("../../EngineSDK/Hlsl/Shader_Cell.hlsl"), VTXPOS::Elements, VTXPOS::iNumElements);
    if (nullptr == m_pShader)
        return E_FAIL;
#endif

    if (FAILED(SetUp_Neighbors()))
        return E_FAIL;

    return S_OK;
}

HRESULT CNavigation::Initialize(void* pArg)
{
    if (nullptr != pArg)
    {
        NAVIGATION_DESC* pDesc = static_cast<NAVIGATION_DESC*>(pArg);

        m_iCurrentCellIndex = pDesc->iCurrentCellIndex;
    }

    return S_OK;
}

void CNavigation::Set_CurrentNaviIndex(_vector _vWorldPos)
{
    _int                iNeighborIndex = { -1 };

    for (_uint i = 0; i < m_Cells.size(); ++i)
    {
        if (true == m_Cells[i]->isIn(_vWorldPos, &iNeighborIndex))
        {
            m_iCurrentCellIndex = i;
            return;
        }
    }
}

_uint CNavigation::Find_Closest_Cell(/*_uint _iFloorNum, */_vector _vWorldPos)
{
    _float fMinsDistance = FLT_MAX;
    _uint iClosestCellIndex = 0;
    _float fPosX = XMVectorGetX(_vWorldPos);
    _float fPosY = XMVectorGetY(_vWorldPos);
    _float fPosZ = XMVectorGetZ(_vWorldPos);


    for (_uint i = 0; i < m_Cells.size(); ++i)
    {
        XMFLOAT3 vCellCenter = m_Cells[i]->Get_Center();
        _float fDistance = sqrt(
            powf(fPosX - vCellCenter.x, 2) +
            powf(fPosY - vCellCenter.y, 2) +
            powf(fPosZ - vCellCenter.z, 2)
        );

        if (fDistance < fMinsDistance)
        {
            fMinsDistance = fDistance;
            iClosestCellIndex = i;
        }
    }

    return iClosestCellIndex;
}

void CNavigation::Set_NaviFloor(_uint _iFloorNumber)
{
    m_iFloorNumber = _iFloorNumber;

    m_iCurrentCellIndex = 0;
}

_bool CNavigation::isMove(_fvector vWorldPos)
{
    _vector     vPosition = XMVector3TransformCoord(vWorldPos, XMLoadFloat4x4(&m_WorldMatrixInverse));

    _int        iNeighborIndex = { -1 }; // -1로 설정되면 이웃이 없다는 거를 의미.
    m_iNeighborIndex = iNeighborIndex;

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
            m_iNeighborIndex = iNeighborIndex;
            return true;
        }
        else
        {
            m_iNeighborIndex = -1;
            return false;
        }
    }
    else
    {
        m_iNeighborIndex = iNeighborIndex;
        return true;
    }

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

_vector CNavigation::Setting_SlidingMove(_fvector _vWorldPos)
{
    if (m_iNeighborIndex == -1)
    {
        _vector vPosition = XMVector3TransformCoord(_vWorldPos, XMLoadFloat4x4(&m_WorldMatrixInverse));

        for (_uint i = 0; i < CCell::LINE_END; ++i)
        {
            // 방향 벡터 구하기 .
            _vector vDir = (vPosition - m_Cells[m_iCurrentCellIndex]->Get_Point((CCell::POINT)i));

            // 법선 벡터 구하기 위해서, 해당 라인.  삼각형의 01 라인인지, 12 라인인지, 20 라인인지.
            _vector vLine = (m_Cells[m_iCurrentCellIndex]->Get_Point((CCell::POINT)((i + 1) % 3)) - m_Cells[m_iCurrentCellIndex]->Get_Point((CCell::POINT)i));

            // 법선 벡터 구하기 
            _vector vNormal = XMVector3Normalize(XMVectorSet(XMVectorGetZ(vLine) * -1.0f, 0.0f, XMVectorGetX(vLine), 0.0f));

            // 이제 방향벡터와 법선 벡터 내적을 해가지구, 깂이, 음수이면 안에있다.  양수이면 바깥에 있다.
            if (0.0f < XMVectorGetX(XMVector3Dot(vDir, vNormal)))
            {
                // 투영벡터 플레이어 위치에서 충돌할 선분으로 내려꽂아버릴, 방향벡터.
                _vector vLineCollisionPoint = m_Cells[m_iCurrentCellIndex]->Get_Point((CCell::POINT)i) + XMVector3Dot(vDir, vLine) * vLine / XMVector3Dot(vLine, vLine);
                _vector vSlideDir = XMVector3Normalize(vLineCollisionPoint - vPosition);
                return vPosition + (vSlideDir * 0.1f);
            }
        }
    }

    return _vWorldPos;
}

_bool CNavigation::bIsOn_Line(_fvector _vWorldPos)
{
    _vector vPosition = XMVector3TransformCoord(_vWorldPos, XMLoadFloat4x4(&m_WorldMatrixInverse));

    for (_uint i = 0; i < CCell::LINE_END; ++i)
    {
        _vector vDir = (vPosition - m_Cells[m_iCurrentCellIndex]->Get_Point((CCell::POINT)i));
        _vector vLine = (m_Cells[m_iCurrentCellIndex]->Get_Point((CCell::POINT)((i + 1) % 3)) - m_Cells[m_iCurrentCellIndex]->Get_Point((CCell::POINT)i));
        _vector vNormal = XMVector3Normalize(XMVectorSet(XMVectorGetZ(vLine) * -1.0f, 0.0f, XMVectorGetX(vLine), 0.0f));

        // 음수이면 안에있다.양수이면 바깥에 있다.
        if (0.0f < XMVectorGetX(XMVector3Dot(vDir, vNormal)))
        {
            return true;
        }
    }

    return false;
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

    if (FAILED(m_pShader->Bind_RawValue("g_vColor", &vColor, sizeof(_float4))))
        return E_FAIL;

    if (-1 == m_iCurrentCellIndex)
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

CNavigation* CNavigation::CreateOnly(ID3D11Device* pdevice, ID3D11DeviceContext* pContext)
{
    CNavigation* pInstance = new CNavigation(pdevice, pContext);
    if (FAILED(pInstance->Initialize_Prototype_CreateOnly()))
    {
        MSG_BOX("Failed To Created : CNavigation");
        Safe_Release(pInstance);
    }

    return pInstance;
}

HRESULT CNavigation::Create_Cell(const _float3 _vPoints[3])
{
    CCell* pCell = CCell::Create(m_pDevice, m_pContext, _vPoints, (_uint)(m_Cells.size()));
    if (nullptr == pCell)
        return E_FAIL;

    m_Cells.push_back(pCell);

    cout << "셀 하나 생성! 후 push_back 완료!" << endl;

    return S_OK;
}

HRESULT CNavigation::Delete_Cell(const _float3 _vPoints[3])
{
    for (auto iter = m_Cells.begin(); iter != m_Cells.end(); ++iter)
    {
        if ((*iter)->Compare_Points(XMLoadFloat3(&_vPoints[0]), XMLoadFloat3(&_vPoints[1])) &&
            (*iter)->Compare_Points(XMLoadFloat3(&_vPoints[1]), XMLoadFloat3(&_vPoints[2])) &&
            (*iter)->Compare_Points(XMLoadFloat3(&_vPoints[2]), XMLoadFloat3(&_vPoints[0])))
        {
            Safe_Release(*iter);
            m_Cells.erase(iter);

            return S_OK;
        }
    }

    return E_FAIL;
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

#include "Navigation.h"
#include "Cell.h"   


#ifdef _DEBUG
#include "Shader.h"
#include "GameInstance.h"   
#endif

_float4x4 CNavigation::m_WorldMatrix = {}; // static������ �ٷ� �ʱ�ȭ ���ϰ� �̷��� cpp�ͼ� �ʱ�ȭ �������.
_float4x4 CNavigation::m_WorldMatrixInverse = {}; // �׸��� ���� ���� ��Ʈ������ ���� ������ �����Ǹ� �ȵǴϱ� �̷���
// Staic ������ ������༭ �ϳ��� �޸� �ּҸ� �����ǰ� �ؼ� ������ �� �ֵ��� ��. 

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

            // ���� Ż�⹮ ����
            if (0 == dwByte)
                break;

            // size �� �༭ ó���� �ϳ� ���� �뷮 1��, �ϳ� �� ���� 2��.~~ 
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

    // ���� �̰� ȣ������� ���������� ���� �� 4�� �� �ٳ�� �ְ� �Ǿ���. 
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

    _int        iNeighborIndex = { -1 }; // -1�� �����Ǹ� �̿��� ���ٴ� �Ÿ� �ǹ�.
    m_iNeighborIndex = iNeighborIndex;

    if (false == m_Cells[m_iCurrentCellIndex]->isIn(vPosition, &iNeighborIndex))
    {
        /* ���� ���⿡ �̿��� �ִٸ�? */
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
            // ���� ���� ���ϱ� .
            _vector vDir = (vPosition - m_Cells[m_iCurrentCellIndex]->Get_Point((CCell::POINT)i));

            // ���� ���� ���ϱ� ���ؼ�, �ش� ����.  �ﰢ���� 01 ��������, 12 ��������, 20 ��������.
            _vector vLine = (m_Cells[m_iCurrentCellIndex]->Get_Point((CCell::POINT)((i + 1) % 3)) - m_Cells[m_iCurrentCellIndex]->Get_Point((CCell::POINT)i));

            // ���� ���� ���ϱ� 
            _vector vNormal = XMVector3Normalize(XMVectorSet(XMVectorGetZ(vLine) * -1.0f, 0.0f, XMVectorGetX(vLine), 0.0f));

            // ���� ���⺤�Ϳ� ���� ���� ������ �ذ�����, ����, �����̸� �ȿ��ִ�.  ����̸� �ٱ��� �ִ�.
            if (0.0f < XMVectorGetX(XMVector3Dot(vDir, vNormal)))
            {
                // �������� �÷��̾� ��ġ���� �浹�� �������� �����Ⱦƹ���, ���⺤��.
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

        // �����̸� �ȿ��ִ�.����̸� �ٱ��� �ִ�.
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

        WorldMatrix.m[3][1] += 0.1f;  // �̰Ŵ� �����Ʈ������ ���� �����Ѱ� 3��°���� POSITION���� �ǹ��ϰ� �ű⿡ 1���� Y��

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

    cout << "�� �ϳ� ����! �� push_back �Ϸ�!" << endl;

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

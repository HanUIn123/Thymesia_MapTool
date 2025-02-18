#include "VIBuffer_Effect_Rect_Instancing.h"
#include "GameInstance.h"

CVIBuffer_Effect_Rect_Instancing::CVIBuffer_Effect_Rect_Instancing(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :CVIBuffer_Particle_Instancing(pDevice,pContext)
{
}

CVIBuffer_Effect_Rect_Instancing::CVIBuffer_Effect_Rect_Instancing(const CVIBuffer_Effect_Rect_Instancing& Prototype)
    :CVIBuffer_Particle_Instancing(Prototype)
{
}


HRESULT CVIBuffer_Effect_Rect_Instancing::Initialize(void* pArg)
{
    const PARTICLE_RECT_INSTANCING_DESC* pDesc = static_cast<const PARTICLE_RECT_INSTANCING_DESC*>(pArg);

    m_iNumInstance = pDesc->iNumInstance; 
    m_iNumVertices = 4; 
    m_iVertexStride = sizeof(VTXPOSTEX);
    m_iInstanceVertexStride = sizeof(VTX_PARTICLE_INSTANCE);
    m_iNumIndexPerInstance = 6; /* 하나의 Rect를 만드는데 필요한 인덱스 */
    m_iNumIndices = m_iNumIndexPerInstance * m_iNumInstance; /* 총 인덱스 수 */
    m_iIndexStride = 2;
    m_iNumVertexBuffers = 2; 
    m_eIndexFormat = DXGI_FORMAT_R16_UINT; 
    m_ePrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; 

#pragma region INSTANCE_VERTEX_BUFFER
    ZeroMemory(&m_InstanceBufferDesc, sizeof(m_InstanceBufferDesc));
    m_InstanceBufferDesc.ByteWidth = m_iNumInstance * m_iInstanceVertexStride;
    m_InstanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    m_InstanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    m_InstanceBufferDesc.StructureByteStride = m_iInstanceVertexStride;
    m_InstanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    m_InstanceBufferDesc.MiscFlags = 0;

    m_pInstanceVertices = new VTX_PARTICLE_INSTANCE[m_iNumInstance];
    ZeroMemory(m_pInstanceVertices, sizeof(VTX_PARTICLE_INSTANCE) * m_iNumInstance);

    m_pSpeeds = new _float[m_iNumInstance];
    ZeroMemory(m_pSpeeds, sizeof(_float) * m_iNumInstance);

    m_isLoop = pDesc->isLoop;
    m_vPivot = pDesc->vPivot;

    for (size_t i = 0; i < m_iNumInstance; i++)
    {
        _float4   vTranslation = {};

        vTranslation.x = m_pGameInstance->Compute_Random(pDesc->vCenter.x - pDesc->vRange.x * 0.5f, pDesc->vCenter.x + pDesc->vRange.x * 0.5f);
        vTranslation.y = m_pGameInstance->Compute_Random(pDesc->vCenter.y - pDesc->vRange.y * 0.5f, pDesc->vCenter.y + pDesc->vRange.y * 0.5f);
        vTranslation.z = m_pGameInstance->Compute_Random(pDesc->vCenter.z - pDesc->vRange.z * 0.5f, pDesc->vCenter.z + pDesc->vRange.z * 0.5f);
        vTranslation.w = 1;

        m_pSpeeds[i] = m_pGameInstance->Compute_Random(pDesc->vSpeed.x, pDesc->vSpeed.y);

        m_pInstanceVertices[i].vRight = _float4(1.f, 0.f, 0.f, 0.f);
        m_pInstanceVertices[i].vUp = _float4(0.f, 1.f, 0.f, 0.f);
        m_pInstanceVertices[i].vLook = _float4(0.f, 0.f, 1.f, 0.f);
        m_pInstanceVertices[i].vTranslation = vTranslation;
        m_pInstanceVertices[i].vLifeTime.x = m_pGameInstance->Compute_Random(pDesc->vLifeTime.x, pDesc->vLifeTime.y);

        _float         fScale = m_pGameInstance->Compute_Random(pDesc->vSize.x, pDesc->vSize.y);

        XMStoreFloat4(&m_pInstanceVertices[i].vRight, XMLoadFloat4(&m_pInstanceVertices[i].vRight) * fScale);
        XMStoreFloat4(&m_pInstanceVertices[i].vUp, XMLoadFloat4(&m_pInstanceVertices[i].vUp) * fScale);
        XMStoreFloat4(&m_pInstanceVertices[i].vLook, XMLoadFloat4(&m_pInstanceVertices[i].vLook) * fScale);
    }

    ZeroMemory(&m_InstanceInitialData, sizeof(m_InstanceInitialData));
    m_InstanceInitialData.pSysMem = m_pInstanceVertices;

#pragma region VERTEX_BUFFER
    ZeroMemory(&m_BufferDesc, sizeof(m_BufferDesc));
    m_BufferDesc.ByteWidth = m_iNumVertices * m_iVertexStride;
    m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
    m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    m_BufferDesc.StructureByteStride = m_iVertexStride;
    m_BufferDesc.CPUAccessFlags = 0;
    m_BufferDesc.MiscFlags = 0;

    VTXPOSTEX* pVertices = new VTXPOSTEX[m_iNumVertices];
    ZeroMemory(pVertices, sizeof(VTXPOSTEX) * m_iNumVertices);

    pVertices[0].vPosition = _float3(-0.5f, 0.5f, 0.f);
    pVertices[0].vTexcoord = _float2(0.f, 0.f);

    pVertices[1].vPosition = _float3(0.5f, 0.5f, 0.f);
    pVertices[1].vTexcoord = _float2(1.f, 0.f);

    pVertices[2].vPosition = _float3(0.5f, -0.5f, 0.f);
    pVertices[2].vTexcoord = _float2(1.f, 1.f);

    pVertices[3].vPosition = _float3(-0.5f, -0.5f, 0.f);
    pVertices[3].vTexcoord = _float2(0.f, 1.f);

    ZeroMemory(&m_InitialData, sizeof m_InitialData);
    m_InitialData.pSysMem = pVertices;

    if (FAILED(__super::Create_Buffer(&m_pVB)))
        return E_FAIL;

    Safe_Delete_Array(pVertices);
#pragma endregion 

#pragma region INDEX_BUFFER
    ZeroMemory(&m_BufferDesc, sizeof(m_BufferDesc));
    m_BufferDesc.ByteWidth = m_iNumIndices * m_iIndexStride;
    m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
    m_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    m_BufferDesc.StructureByteStride = m_iIndexStride;
    m_BufferDesc.CPUAccessFlags = 0;
    m_BufferDesc.MiscFlags = 0;


    _ushort* pIndices = new _ushort[m_iNumIndices];
    ZeroMemory(pIndices, sizeof(_ushort) * m_iNumIndices);

    _uint iNumInstance = { 0 };

    for (size_t i = 0; i < m_iNumInstance; i++)
    {
        pIndices[iNumInstance++] = 0;
        pIndices[iNumInstance++] = 1;
        pIndices[iNumInstance++] = 2;

        pIndices[iNumInstance++] = 0;
        pIndices[iNumInstance++] = 2;
        pIndices[iNumInstance++] = 3;
    }

    ZeroMemory(&m_InitialData, sizeof(m_InitialData));
    m_InitialData.pSysMem = pIndices;

    if (FAILED(__super::Create_Buffer(&m_pIB)))
        return E_FAIL;

    Safe_Delete_Array(pIndices);

#pragma endregion 

    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    return S_OK;    
}

CVIBuffer_Effect_Rect_Instancing* CVIBuffer_Effect_Rect_Instancing::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, PARTICLE_INSTANCING_DESC* pArg)
{
    CVIBuffer_Effect_Rect_Instancing* pInstance = new CVIBuffer_Effect_Rect_Instancing(pDevice, pContext);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Created : VIBuffer_Effect_Rect_Instancing");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CComponent* CVIBuffer_Effect_Rect_Instancing::Clone(void* pArg)
{
    return nullptr;
}

void CVIBuffer_Effect_Rect_Instancing::Free()
{
    __super::Free();
}

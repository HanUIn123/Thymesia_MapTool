#include "VIBuffer_Point_Instancing.h"
#include "GameInstance.h"

CVIBuffer_Point_Instancing::CVIBuffer_Point_Instancing(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :CVIBuffer_Particle_Instancing(pDevice,pContext)
{
}

CVIBuffer_Point_Instancing::CVIBuffer_Point_Instancing(const CVIBuffer_Point_Instancing& Prototype)
    :CVIBuffer_Particle_Instancing(Prototype)   
{
}

HRESULT CVIBuffer_Point_Instancing::Initialize_Prototype(const PARTICLE_INSTANCING_DESC* pArg)
{
    const PARTICLE_POINT_INSTANCING_DESC* pDesc = static_cast<const PARTICLE_POINT_INSTANCING_DESC*>(pArg); 

    m_iNumInstance = pDesc->iNumInstance;
    m_iNumVertices = 1; 
    m_iVertexStride = sizeof(VTXPOINT);
    m_iInstanceVertexStride = sizeof(VTX_PARTICLE_INSTANCE);
    m_iNumIndexPerInstance = 1; 
    m_iNumIndices = m_iNumIndexPerInstance * m_iNumInstance;
    m_iIndexStride = 2; 
    m_iNumVertexBuffers = 2; 
    m_eIndexFormat = DXGI_FORMAT_R16_UINT;  
    m_ePrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
    m_vBornTime = pDesc->vBornTime; 
    m_vTexInterval = pDesc->vTexInterval;
    m_fTextDurationTime = pDesc->fTexDurationTime;
    m_vTexOffSet = pDesc->vTexOffSet;


#pragma region INSTANCE_BUFFER
    /* 사본을 만들 때 실제 활용하기 위한 인스턴스 정점 버퍼를 할당하기 위해 필요한 초기 데이터를 미리 다 셋팅해놓는다.*/
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
    
    m_pBezierCurvePos = new _float3[m_iNumIndexPerInstance];         
    //m_pCombinedMatrix = new _float4x4[m_iNumInstance];  
    //memcpy(m_pCombinedMatrix, &XMMatrixIdentity(), sizeof(_float4x4) * m_iNumInstance); 
  

    for(size_t i =0; i< m_iNumInstance; i++)
    {
        _float4         vTranslation = {}; 

        vTranslation.x = m_pGameInstance->Compute_Random(pDesc->vCenter.x - pDesc->vRange.x * 0.5f, pDesc->vCenter.x + pDesc->vRange.x * 0.5f);
        vTranslation.y = m_pGameInstance->Compute_Random(pDesc->vCenter.y - pDesc->vRange.y * 0.5f, pDesc->vCenter.y + pDesc->vRange.y * 0.5f);
        vTranslation.z = m_pGameInstance->Compute_Random(pDesc->vCenter.z - pDesc->vRange.z * 0.5f, pDesc->vCenter.z + pDesc->vRange.z * 0.5f);
        vTranslation.w = 1; 
    
        m_pSpeeds[i] = m_pGameInstance->Compute_Random(pDesc->vSpeed.x, pDesc->vSpeed.y);

        m_pInstanceVertices[i].vRight = _float4(1.f, 0.f, 0.f, 0.f);
        m_pInstanceVertices[i].vUp    = _float4(0.f, 1.f, 0.f, 0.f);
        m_pInstanceVertices[i].vLook  = _float4(0.f, 0.f, 1.f, 0.f);
        m_pInstanceVertices[i].vTranslation = vTranslation; 
        m_pInstanceVertices[i].vLifeTime.x = m_pGameInstance->Compute_Random(pDesc->vLifeTime.x, pDesc->vLifeTime.y);   
        m_pInstanceVertices[i].vBornTime.x = m_pGameInstance->Compute_Random(pDesc->vBornTime.x, pDesc->vBornTime.y);   
        m_pInstanceVertices[i].vTexcoord   = _float2(0.f, 0.f);
        m_pInstanceVertices[i].iFrame = 0;
        m_pInstanceVertices[i].fDurationTime = 0.f;
      
        
        _float fScale = m_pGameInstance->Compute_Random(pDesc->vSize.x, pDesc->vSize.y);

        XMStoreFloat4(&m_pInstanceVertices[i].vRight, XMLoadFloat4(&m_pInstanceVertices[i].vRight) * fScale);
        XMStoreFloat4(&m_pInstanceVertices[i].vUp   , XMLoadFloat4(&m_pInstanceVertices[i].vUp)    * fScale);
        XMStoreFloat4(&m_pInstanceVertices[i].vLook , XMLoadFloat4(&m_pInstanceVertices[i].vLook)  * fScale);

        m_pBezierCurvePos->x = m_pGameInstance->Compute_Random(pDesc->vCenter.x - pDesc->vRange.x * 30.f, pDesc->vCenter.x + pDesc->vRange.x * 40.f);
        m_pBezierCurvePos->y = m_pGameInstance->Compute_Random(pDesc->vCenter.y - pDesc->vRange.y * 20.f, pDesc->vCenter.y + pDesc->vRange.y * 40.f);
        m_pBezierCurvePos->z = m_pGameInstance->Compute_Random(pDesc->vCenter.z - pDesc->vRange.z * 30.f, pDesc->vCenter.z + pDesc->vRange.z * 40.f);
        
    }

    m_InstanceInitialData.pSysMem = m_pInstanceVertices;     
    
#pragma endregion 

#pragma region VERTEX_BUFFER
    ZeroMemory(&m_BufferDesc, sizeof(m_BufferDesc));
    m_BufferDesc.ByteWidth = m_iNumVertices * m_iVertexStride;
    m_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
    m_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    m_BufferDesc.StructureByteStride = m_iVertexStride;
    m_BufferDesc.CPUAccessFlags = 0; 
    m_BufferDesc.MiscFlags = 0; 

    VTXPOINT* pVertices = new VTXPOINT[m_iNumVertices];     
    ZeroMemory(pVertices, sizeof(VTXPOINT) * m_iNumVertices);   

    pVertices[0].vPosition = _float3(0.f, 0.f, 0.f);
    pVertices[0].fPSize = 1.f; 

    ZeroMemory(&m_InitialData, sizeof(m_InitialData));
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
    
    //for(int i =0; i< m_iNumIndices; i++)
    //{
    //    pIndices[i] = 0; 
    //}

    ZeroMemory(&m_InitialData, sizeof(m_InitialData));
    m_InitialData.pSysMem = pIndices;

    if (FAILED(__super::Create_Buffer(&m_pIB)))
        return E_FAIL; 
    
    Safe_Delete_Array(pIndices);
#pragma endregion 

    return S_OK;    
}

HRESULT CVIBuffer_Point_Instancing::Initialize(void* pArg)
{
    /* 사본을 만들 때 실제 활용하기 위한 인스턴스 정점 버퍼를 할당한다. */
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;  

    return S_OK;    
}

CVIBuffer_Point_Instancing* CVIBuffer_Point_Instancing::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const PARTICLE_INSTANCING_DESC* pArg)
{
    CVIBuffer_Point_Instancing* pInstance = new CVIBuffer_Point_Instancing(pDevice, pContext);

    if(FAILED(pInstance->Initialize_Prototype(pArg)))
    {
        MSG_BOX("Failed to Created : CVIBuffer_Point_Instancing");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CComponent* CVIBuffer_Point_Instancing::Clone(void* pArg)
{
    CVIBuffer_Point_Instancing* pInstance = new CVIBuffer_Point_Instancing(*this);  

    if(FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CVIBuffer_Point_Instancing");
        Safe_Release(pInstance);
    }
    
    return pInstance;

}

void CVIBuffer_Point_Instancing::Free()
{
    __super::Free();    

    //Safe_Delete_Array(m_pBezierCurvePos);   
}

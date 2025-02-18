#include "VIBuffer_Mesh_Instancing.h"
#include "GameInstance.h"   

CVIBuffer_Mesh_Instancing::CVIBuffer_Mesh_Instancing(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :CVIBuffer_Particle_Instancing(pDevice,pContext)
{

}

CVIBuffer_Mesh_Instancing::CVIBuffer_Mesh_Instancing(const CVIBuffer_Mesh_Instancing& Prototype)
    :CVIBuffer_Particle_Instancing(Prototype)
{
}

HRESULT CVIBuffer_Mesh_Instancing::Initialize_Prototype(const PARTICLE_INSTANCING_DESC* pArg)
{
    const PARTICLE_MESH_INSTANCING_DESC* pDesc = static_cast<const PARTICLE_MESH_INSTANCING_DESC*>(pArg);  
   
    m_iNumInstance = pDesc->iNumInstance;   
    m_iInstanceVertexStride = sizeof(VTX_PARTICLE_INSTANCE);      

#pragma region INSTANCE_VERTEXT_BUFFER
    /* 사본을 만들때 실제 활용하기 위한 인스턴스 정점 버퍼를 할당하기 위해 초기 데이터를 미리 다 셋팅해놓는다. */
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
    /* 버퍼를 안만들었으니깐 삭제해주면 안됨!*/

#pragma endregion 

    return E_NOTIMPL;
}

HRESULT CVIBuffer_Mesh_Instancing::Initialize(void* pArg)
{
    return E_NOTIMPL;
}

CVIBuffer_Mesh_Instancing* CVIBuffer_Mesh_Instancing::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const PARTICLE_INSTANCING_DESC* pArg)
{
    return nullptr;
}

CComponent* CVIBuffer_Mesh_Instancing::Clone(void* pArg)
{
    return nullptr;
}

void CVIBuffer_Mesh_Instancing::Free()
{
}

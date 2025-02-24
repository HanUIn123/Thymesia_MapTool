#include "VIBuffer_Instancing.h"

CVIBuffer_Instancing::CVIBuffer_Instancing(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext)
    :CVIBuffer{_pDevice, _pContext}
{
}

CVIBuffer_Instancing::CVIBuffer_Instancing(const CVIBuffer_Instancing& _Prototype)
    :CVIBuffer(_Prototype)
    ,m_iNumInstance(_Prototype.m_iNumInstance)
{
}

HRESULT CVIBuffer_Instancing::Initialize_Prototype(_uint _iNumInstanceNumber)
{
    m_iNumInstance = _iNumInstanceNumber;
    m_pInstanceData = new INSTANCE_DATA[m_iNumInstance];
    ZeroMemory(&m_InstanceBufferDesc, sizeof(m_InstanceBufferDesc));
    m_InstanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    m_InstanceBufferDesc.ByteWidth = m_iNumInstance * sizeof(INSTANCE_DATA);
    m_InstanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    m_InstanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    m_InstanceBufferDesc.MiscFlags = 0;
    m_InstanceInitialData.pSysMem = m_pInstanceData;





    m_pDevice->CreateBuffer(&m_InstanceBufferDesc, &m_InstanceInitialData, &m_pInstanceBuffer);

    return S_OK;
}

HRESULT CVIBuffer_Instancing::Initialize(void* _pArg)
{
    return S_OK;
}

void CVIBuffer_Instancing::Update_InstanceBuffer(const vector<XMFLOAT4X4>& _vecInstanceMatrices)
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    HRESULT hr = m_pContext->Map(m_pInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(hr))
        return;

    INSTANCE_DATA* pInstanceData = reinterpret_cast<INSTANCE_DATA*>(mappedResource.pData);

    for (size_t i = 0; i < _vecInstanceMatrices.size(); i++)
    {
        pInstanceData[i].WorldMatrix = _vecInstanceMatrices[i];
    }

    m_pContext->Unmap(m_pInstanceBuffer, 0);
}

HRESULT CVIBuffer_Instancing::Render_Instance(_uint _iMeshIndexNumber, _uint _iNumInstanceNumber)
{
    if (nullptr == m_pContext)
        return E_FAIL;

    ID3D11Buffer* pVertexBuffers[] = { m_pVB, m_pInstanceBuffer };

    _uint iStrides[] =
    {
        m_iVertexStride, sizeof(INSTANCE_DATA)
    };

    _uint iOffsets[] =
    {
        0, 0
    };

    m_pContext->IASetVertexBuffers(0, 2, pVertexBuffers, iStrides, iOffsets);
    m_pContext->IASetIndexBuffer(m_pIB, m_eIndexFormat, 0);
    m_pContext->IASetPrimitiveTopology(m_ePrimitiveTopology);

    m_pContext->DrawIndexedInstanced(3, _iNumInstanceNumber, 0, 0, 0);

    return S_OK;
}

CVIBuffer_Instancing* CVIBuffer_Instancing::Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext, const _uint _iNumInstanceNumber)
{
    CVIBuffer_Instancing* pInstance = new CVIBuffer_Instancing(_pDevice, _pContext);

    if (FAILED(pInstance->Initialize_Prototype(_iNumInstanceNumber)))
    {
        MSG_BOX("Failed To Created : CVIBuffer_Instancing");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CComponent* CVIBuffer_Instancing::Clone(void* _pArg)
{
    CVIBuffer_Instancing* pInstance = new CVIBuffer_Instancing(*this);

    if (FAILED(pInstance->Initialize(_pArg)))
    {
        MSG_BOX("Failed To Created : CVIBuffer_Instancing");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CVIBuffer_Instancing::Free()
{
    __super::Free();


    Safe_Release(m_pInstanceBuffer);
    //Safe_Release(m_pInstanceData);
}

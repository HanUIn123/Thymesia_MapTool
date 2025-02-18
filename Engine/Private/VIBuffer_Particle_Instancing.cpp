#include "VIBuffer_Particle_Instancing.h"

CVIBuffer_Particle_Instancing::CVIBuffer_Particle_Instancing(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    :CVIBuffer(pDevice,pContext)
{
}

CVIBuffer_Particle_Instancing::CVIBuffer_Particle_Instancing(const CVIBuffer_Particle_Instancing& Prototype)
    :CVIBuffer(Prototype)
    , m_InstanceBufferDesc(Prototype.m_InstanceBufferDesc)
    , m_InstanceInitialData(Prototype.m_InstanceInitialData)
    , m_iInstanceVertexStride(Prototype.m_iInstanceVertexStride)
    , m_iNumIndexPerInstance(Prototype.m_iNumIndexPerInstance)
    , m_iNumInstance(Prototype.m_iNumInstance)
    , m_pVBInstance(Prototype.m_pVBInstance)
    , m_pInstanceVertices(Prototype.m_pInstanceVertices)
    , m_pSpeeds(Prototype.m_pSpeeds)
    , m_isLoop(Prototype.m_isLoop)
    , m_vPivot(Prototype.m_vPivot)
    , m_pBezierCurvePos(Prototype.m_pBezierCurvePos)
    , m_vTexInterval(Prototype.m_vTexInterval)
    , m_fTextDurationTime(Prototype.m_fTextDurationTime)
    , m_vTexOffSet(Prototype.m_vTexOffSet)
    //, m_pCombinedMatrix(Prototype.m_pCombinedMatrix)    
{
    Safe_AddRef(m_pVBInstance);

    //XMStoreFloat4x4(&m_ParticleLocalMatrix, XMMatrixIdentity());
}

HRESULT CVIBuffer_Particle_Instancing::Initialize_Prototype(const PARTICLE_INSTANCING_DESC* pDesc)
{
    return S_OK;
}

HRESULT CVIBuffer_Particle_Instancing::Initialize(void* pArg)
{
    return m_pDevice->CreateBuffer(&m_InstanceBufferDesc, &m_InstanceInitialData, &m_pVBInstance);
}

HRESULT CVIBuffer_Particle_Instancing::Bind_InputAssembler()
{
    if (nullptr == m_pContext)
        return E_FAIL;

    ID3D11Buffer* pVertexBuffer[] =
    {
        m_pVB,
        m_pVBInstance,
    };

    _uint         iVertexStrides[] =
    {
        m_iVertexStride,
        m_iInstanceVertexStride,
    };

    _uint         iOffsets[] =
    {
        0,
        0,
    };


    m_pContext->IASetVertexBuffers(0, m_iNumVertexBuffers, pVertexBuffer, iVertexStrides, iOffsets);
    m_pContext->IASetIndexBuffer(m_pIB, m_eIndexFormat, 0);
    m_pContext->IASetPrimitiveTopology(m_ePrimitiveTopology);       


    return S_OK;
}

HRESULT CVIBuffer_Particle_Instancing::Render()
{
    if (nullptr == m_pContext)
        return E_FAIL;

    m_pContext->DrawIndexedInstanced(m_iNumIndexPerInstance, m_iNumInstance, 0, 0, 0);  

    return S_OK; 
}

HRESULT CVIBuffer_Particle_Instancing::Render_Spawn()  
{
    if (nullptr == m_pContext)  
        return E_FAIL;  
 
    if (m_iNumDrawPoint > m_iNumInstance)
        return E_FAIL;   

    m_pContext->DrawIndexedInstanced(m_iNumIndexPerInstance, m_iNumDrawPoint, 0, 0, 0);     

    return S_OK;
}

void CVIBuffer_Particle_Instancing::Drop(_float fTimeDelta)
{
    D3D11_MAPPED_SUBRESOURCE SubResource{};

    m_pContext->Map(m_pVBInstance, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &SubResource);

    VTX_PARTICLE_INSTANCE* pVertices = static_cast<VTX_PARTICLE_INSTANCE*>(SubResource.pData);

    for(size_t i =0; i< m_iNumInstance; i++)
    {
        pVertices[i].vTranslation.y -= m_pSpeeds[i] * fTimeDelta;
        pVertices[i].vLifeTime.y += fTimeDelta;
        if(pVertices[i].vLifeTime.x <= pVertices[i].vLifeTime.y)
        {
            if(true == m_isLoop)
            {
                pVertices[i].vTranslation.y = m_pInstanceVertices[i].vTranslation.y;
                pVertices[i].vLifeTime.y = 0.f; 
            }
        }
    }

    m_pContext->Unmap(m_pVBInstance, 0);    
}

void CVIBuffer_Particle_Instancing::Rise(_float fTimeDelta)
{
    /* 여기서 이제 born time 에 따라서 설정해줘야한다. */
    D3D11_MAPPED_SUBRESOURCE SubResource{};

    m_pContext->Map(m_pVBInstance, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &SubResource);

    VTX_PARTICLE_INSTANCE* pVertices = static_cast<VTX_PARTICLE_INSTANCE*>(SubResource.pData);

    for (size_t i = 0; i < m_iNumInstance; i++)
    {
        pVertices[i].vTranslation.y += m_pSpeeds[i] * fTimeDelta;
        pVertices[i].vLifeTime.y += fTimeDelta;
        if (pVertices[i].vLifeTime.x <= pVertices[i].vLifeTime.y)
        {
            if (true == m_isLoop)
            {
                pVertices[i].vTranslation.y = m_pInstanceVertices[i].vTranslation.y;
                pVertices[i].vLifeTime.y = 0.f;
            }
        }
    }

    m_pContext->Unmap(m_pVBInstance, 0);
}

void CVIBuffer_Particle_Instancing::Explosion(_float fTimeDelta)
{
    D3D11_MAPPED_SUBRESOURCE SubResource{};

    m_pContext->Map(m_pVBInstance, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &SubResource);

    VTX_PARTICLE_INSTANCE* pVertices = static_cast<VTX_PARTICLE_INSTANCE*>(SubResource.pData);

    for (size_t i = 0; i < m_iNumInstance; i++)
    {
        _vector		vMoveDir = XMVectorSetW(XMVector3Normalize(XMLoadFloat4(&pVertices[i].vTranslation) - XMLoadFloat3(&m_vPivot)), 0.f);

        XMStoreFloat4(&pVertices[i].vTranslation, XMLoadFloat4(&pVertices[i].vTranslation) + vMoveDir * m_pSpeeds[i] * fTimeDelta);

        //XMLoadFloat4(&pVertices[i].vTranslation) + vMoveDir * m_pSpeeds[i] * fTimeDelta 베지에 곡선 식을 여기다가 대입하면됨

        pVertices[i].vLifeTime.y += fTimeDelta;
        if (pVertices[i].vLifeTime.x <= pVertices[i].vLifeTime.y)
        {
            if (true == m_isLoop)
            {
                pVertices[i].vTranslation = m_pInstanceVertices[i].vTranslation;
                pVertices[i].vLifeTime.y = 0.f;
            }
        }
    }

    m_pContext->Unmap(m_pVBInstance, 0);
}

void CVIBuffer_Particle_Instancing::Collect(_float fTimeDelta)
{
    D3D11_MAPPED_SUBRESOURCE SubResource{};

    m_pContext->Map(m_pVBInstance, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &SubResource);

    VTX_PARTICLE_INSTANCE* pVertices = static_cast<VTX_PARTICLE_INSTANCE*>(SubResource.pData);

    for (size_t i = 0; i < m_iNumInstance; i++)
    {
        _vector		vMoveDir = XMVectorSetW(XMVector3Normalize(XMLoadFloat3(&m_vPivot) - XMLoadFloat4(&pVertices[i].vTranslation)), 0.f);   

        XMStoreFloat4(&pVertices[i].vTranslation, XMLoadFloat4(&pVertices[i].vTranslation) + vMoveDir * m_pSpeeds[i] * fTimeDelta);

        //XMLoadFloat4(&pVertices[i].vTranslation) + vMoveDir * m_pSpeeds[i] * fTimeDelta 베지에 곡선 식을 여기다가 대입하면됨

        pVertices[i].vLifeTime.y += fTimeDelta;
        if (pVertices[i].vLifeTime.x <= pVertices[i].vLifeTime.y)
        {
            if (true == m_isLoop)
            {
                pVertices[i].vTranslation = m_pInstanceVertices[i].vTranslation;
                pVertices[i].vLifeTime.y = 0.f;
            }
        }
    }

    m_pContext->Unmap(m_pVBInstance, 0);
}

void CVIBuffer_Particle_Instancing::FireBreath(_float fTimeDelta, _fmatrix _pCombinedMatrix)    
{
    D3D11_MAPPED_SUBRESOURCE SubResource{}; 

    m_fAccTimeDelta += fTimeDelta;  
    

    m_pContext->Map(m_pVBInstance, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &SubResource);   

    VTX_PARTICLE_INSTANCE* pVertices = static_cast<VTX_PARTICLE_INSTANCE*>(SubResource.pData);  

    m_iNumDrawPoint = 0;    

    for (size_t i = 0; i < m_iNumInstance; i++)     
    {
        if (m_fAccTimeDelta > pVertices[i].vBornTime.x)
        {
            m_iNumDrawPoint++;

            pVertices[i].fDurationTime += fTimeDelta;   

            pVertices[i].vTranslation.y += m_pSpeeds[i] * fTimeDelta;
            
          
            pVertices[i].vLifeTime.y += fTimeDelta;
            
            
            pVertices[i].vTexcoord.x = m_vTexInterval.x;
            pVertices[i].vTexcoord.y = m_vTexInterval.y;


            /* 2월 10일 작업 파티클 개개인의 움직임 조절 */
            //
            //_float4 Position = {};

            //XMStoreFloat4(&Position,XMLoadFloat4(reinterpret_cast<_float4*>(m_pCombinedMatrix[i].m[3])));       
            //_float PositionScale = XMVectorGetX(XMVector3Length(XMLoadFloat4(&Position)));      

            //if(PositionScale == 0.f)    
            //{
            //    XMStoreFloat4(reinterpret_cast<_float4*>(&m_ParticleLocalMatrix.m[0]), XMLoadFloat4(&pVertices[i].vRight));           
            //    XMStoreFloat4(reinterpret_cast<_float4*>(&m_ParticleLocalMatrix.m[1]), XMLoadFloat4(&pVertices[i].vUp));             
            //    XMStoreFloat4(reinterpret_cast<_float4*>(&m_ParticleLocalMatrix.m[2]), XMLoadFloat4(&pVertices[i].vLook));           
            //    XMStoreFloat4(reinterpret_cast<_float4*>(&m_ParticleLocalMatrix.m[3]), XMLoadFloat4(&pVertices[i].vTranslation));       

            //    XMStoreFloat4x4(&m_pCombinedMatrix[i],      
            //        XMLoadFloat4x4(&m_ParticleLocalMatrix) * // 이게 원래       
            //        _pCombinedMatrix); //이게 부모      
            //        
            //    XMStoreFloat4(&pVertices[i].vRight,       XMLoadFloat4(reinterpret_cast<_float4*>(m_pCombinedMatrix[i].m[0])));           
            //    XMStoreFloat4(&pVertices[i].vUp,          XMLoadFloat4(reinterpret_cast<_float4*>(m_pCombinedMatrix[i].m[1])));           
            //    XMStoreFloat4(&pVertices[i].vLook,        XMLoadFloat4(reinterpret_cast<_float4*>(m_pCombinedMatrix[i].m[2])));           
            //    XMStoreFloat4(&pVertices[i].vTranslation, XMLoadFloat4(reinterpret_cast<_float4*>(m_pCombinedMatrix[i].m[3])));          
            //    
            //}

            
               

            
            if (pVertices[i].fDurationTime > m_fTextDurationTime)
            {
                pVertices[i].fDurationTime = 0.f; 
                pVertices[i].iFrame++;  
            }


            // 셀의 위치 계산
            int cellX = pVertices[i].iFrame % 4;            // m_iCountX    
            int cellY = pVertices[i].iFrame / 6;            // m_iCountY 가 필요하겠네.   

            pVertices[i].vTexcoord = _float2(cellX * m_vTexOffSet.x, cellY * m_vTexOffSet.y);   


            if (pVertices[i].vLifeTime.x <= pVertices[i].vLifeTime.y)
            {
                //if (true == m_isLoop)
                //{
                //    pVertices[i].vTranslation.y = m_pInstanceVertices[i].vTranslation.y;
                //    pVertices[i].vLifeTime.y = 0.f;
                //}
            }
        }
    }
    m_pContext->Unmap(m_pVBInstance, 0);    

}

void CVIBuffer_Particle_Instancing::Gain(_float3 endPos,_float fTimeDelta)  
{
    D3D11_MAPPED_SUBRESOURCE SubResource{}; 

    m_pContext->Map(m_pVBInstance, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &SubResource);   

    VTX_PARTICLE_INSTANCE* pVertices = static_cast<VTX_PARTICLE_INSTANCE*>(SubResource.pData);  

    m_fAccTimeDelta += fTimeDelta;

    if (m_fAccTimeDelta > 1.f)
        m_fAccTimeDelta = 1.f;


    if (m_fAccTimeDelta < 0.3f)
    {

        for (size_t i = 0; i < m_iNumInstance; i++)
        {
            _vector		vMoveDir = XMVectorSetW(XMVector3Normalize(XMLoadFloat4(&pVertices[i].vTranslation) - XMLoadFloat3(&m_vPivot)), 0.f);

            XMStoreFloat4(&pVertices[i].vTranslation, XMLoadFloat4(&pVertices[i].vTranslation) + vMoveDir * m_pSpeeds[i] * fTimeDelta);

            //XMLoadFloat4(&pVertices[i].vTranslation) + vMoveDir * m_pSpeeds[i] * fTimeDelta 베지에 곡선 식을 여기다가 대입하면됨

            pVertices[i].vLifeTime.y += fTimeDelta;
            /*if (pVertices[i].vLifeTime.x <= pVertices[i].vLifeTime.y)
            {
                if (true == m_isLoop)
                {
                    pVertices[i].vTranslation = m_pInstanceVertices[i].vTranslation;
                    pVertices[i].vLifeTime.y = 0.f;
                }
            }*/
        }
    }

    else
    {
        for (size_t i = 0; i < m_iNumInstance; i++)
        {
            _vector		vMoveDir = XMVectorSetW(XMVector3Normalize(XMLoadFloat3(&endPos) - XMLoadFloat4(&pVertices[i].vTranslation) ), 0.f);    

            XMStoreFloat4(&pVertices[i].vTranslation, XMLoadFloat4(&pVertices[i].vTranslation) + vMoveDir * m_pSpeeds[i] * fTimeDelta);
            
            //XMLoadFloat4(&pVertices[i].vTranslation) + vMoveDir * m_pSpeeds[i] * fTimeDelta 베지에 곡선 식을 여기다가 대입하면됨

            pVertices[i].vLifeTime.y += fTimeDelta;
            /*if (pVertices[i].vLifeTime.x <= pVertices[i].vLifeTime.y)
            {
                if (true == m_isLoop)
                {
                    pVertices[i].vTranslation = m_pInstanceVertices[i].vTranslation;
                    pVertices[i].vLifeTime.y = 0.f;
                }
            }*/
        }
    }

    m_pContext->Unmap(m_pVBInstance, 0);

}

//CurvePos는 initalize 에서 설정하면 될듯 
void CVIBuffer_Particle_Instancing::Bezier(_float4 startPos, _float3 endPos,_float fTimeDelta)          
{
    D3D11_MAPPED_SUBRESOURCE SubResource{}; 

    m_pContext->Map(m_pVBInstance, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &SubResource);   

    VTX_PARTICLE_INSTANCE* pVertices = static_cast<VTX_PARTICLE_INSTANCE*>(SubResource.pData);

    m_fAccTimeDelta += fTimeDelta;

    if (m_fAccTimeDelta > 1.f)
        m_fAccTimeDelta = 1.f;  


    //_vector localPlayerPos = XMLoadFloat3(&endPos) - XMLoadFloat4(&startPos);
    //localPlayerPos = XMVectorSetW(localPlayerPos, 1.f); 
    
    // 최초 시작지점을 고정시켜야함. 그러면  
    for (size_t i = 0; i < m_iNumInstance; i++)
    {
        //_vector		vMoveDir = XMVectorSetW(XMVector3Normalize(XMLoadFloat4(&pVertices[i].vTranslation) - XMLoadFloat3(&m_vPivot)), 0.f);

        // 여기서 배지에 곡선 m_pBezierCurvePos[i] 값이 이제 vCurvePos가 된다. 
        //XMStoreFloat4(&pVertices[i].vTranslation, XMLoadFloat4(&pVertices[i].vTranslation) + vMoveDir * m_pSpeeds[i] * fTimeDelta);
       
        
        
        XMStoreFloat4(&pVertices[i].vTranslation,
            XMVectorSetW((1.f - m_fAccTimeDelta) * (1.f - m_fAccTimeDelta) * XMLoadFloat4(&m_pInstanceVertices[i].vTranslation)
                + 2.f * (1.f - m_fAccTimeDelta) * m_fAccTimeDelta * XMLoadFloat3(&m_pBezierCurvePos[i])
                + m_fAccTimeDelta * m_fAccTimeDelta * XMLoadFloat3(&endPos), 1.f));
        
        //XMLoadFloat4(&pVertices[i].vTranslation) + vMoveDir * m_pSpeeds[i] * fTimeDelta 베지에 곡선 식을 여기다가 대입하면됨

        pVertices[i].vLifeTime.y += fTimeDelta; 
        if (pVertices[i].vLifeTime.x <= pVertices[i].vLifeTime.y)
        {
            /*if (true == m_isLoop)
            {
                pVertices[i].vTranslation = m_pInstanceVertices[i].vTranslation;
                pVertices[i].vLifeTime.y = 0.f;
            }*/
        }
    }

    m_pContext->Unmap(m_pVBInstance, 0);
    
}


void CVIBuffer_Particle_Instancing::Free()
{
    __super::Free();

    if (false == m_isCloned)
    {
        Safe_Delete_Array(m_pSpeeds);
        Safe_Delete_Array(m_pInstanceVertices);
        Safe_Delete_Array(m_pBezierCurvePos);
        //Safe_Delete_Array(m_pCombinedMatrix);
       
    }

    Safe_Release(m_pVBInstance);    
}

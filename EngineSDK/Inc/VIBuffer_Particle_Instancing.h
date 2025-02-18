#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Particle_Instancing abstract : public CVIBuffer
{
public:
	struct PARTICLE_INSTANCING_DESC
	{
		_uint		iNumInstance = {};
		_float3     vRange = {};
		_float3     vCenter = {};
		_float2     vSize = {};
		_float2     vSpeed = {};
		_float3		vPivot = {};
		_float2     vLifeTime = {};
		_float2     vBornTime = {};	
		_bool		isLoop = {};
		_float2     vTexInterval = {};			
		_float      fTexDurationTime = {};
		_float2     vTexOffSet = {};
	};


protected:
	CVIBuffer_Particle_Instancing(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVIBuffer_Particle_Instancing(const CVIBuffer_Particle_Instancing& Prototype);
	virtual ~CVIBuffer_Particle_Instancing() = default;


public:
	virtual HRESULT Initialize_Prototype(const PARTICLE_INSTANCING_DESC* pDesc);
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Bind_InputAssembler() override;
	virtual HRESULT Render() override;
	virtual HRESULT Render_Spawn();

public:
	void Drop(_float fTimeDelta);
	void Rise(_float fTimeDelta);
	void Explosion(_float fTimeDelta);
	void Gain(_float3 endPos, _float fTimeDelta);
	void Bezier(_float4 startPos, _float3 endPos, _float fTimeDelta);
	void FireBreath(_float fTimeDelta, _fmatrix _pCombinedMatrix);	
	void Collect(_float fTimeDelta);

protected:
	D3D11_BUFFER_DESC				m_InstanceBufferDesc = {};
	D3D11_SUBRESOURCE_DATA			m_InstanceInitialData = {};
	_uint							m_iInstanceVertexStride = {};
	_uint							m_iNumIndexPerInstance = {};
	_uint							m_iNumInstance = {};



	VTX_PARTICLE_INSTANCE* m_pInstanceVertices = { nullptr };
	ID3D11Buffer* m_pVBInstance = { nullptr };


	_float*						    m_pSpeeds = { nullptr };
	_bool							m_isLoop = { false };
	_float3							m_vPivot = {};
	

	_float3*						m_pBezierCurvePos = { nullptr };

	_float							m_fAccTimeDelta = {};



	_uint							m_iNumDrawPoint = {};
	_float2							m_vBornTime = {};
	_float2							m_vTexInterval = {};
	_float							m_fTextDurationTime = {}; 
	_float2							m_vTexOffSet = {};


	_float4x4*						m_pCombinedMatrix = {};
	_float4x4						m_ParticleLocalMatrix = {}; 

public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free();

};

END
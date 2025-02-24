#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Instancing final : public CVIBuffer
{
public:
	struct INSTANCE_DATA
	{
		_float4x4 WorldMatrix;
	};

private:
	CVIBuffer_Instancing(ID3D11Device* _pDevice, ID3D11DeviceContext* _pContext);
	CVIBuffer_Instancing(const CVIBuffer_Instancing& _Prototype);
	virtual ~CVIBuffer_Instancing() = default;

public:
	virtual HRESULT Initialize_Prototype(_uint _iNumInstanceNumber);
	virtual HRESULT Initialize(void* _pArg) override;
	virtual void	Update_InstanceBuffer(const vector<XMFLOAT4X4>& _vecInstanceMatrices);
	virtual HRESULT	Render_Instance(_uint _iMeshIndexNumber, _uint _iNumInstanceNumber);

private:
	ID3D11Buffer*				m_pInstanceBuffer = { nullptr };
	D3D11_BUFFER_DESC			m_InstanceBufferDesc = {};
	D3D11_SUBRESOURCE_DATA		m_InstanceInitialData = {};
	_uint						m_iInstanceVertexStride = {};
	INSTANCE_DATA*				m_pInstanceData = { nullptr };
	_uint						m_iNumInstance = {};

	_float4x4					m_WorldMatrix = {};
public:
	static CVIBuffer_Instancing* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const _uint _iNumInstanceNumber);
	virtual CComponent*			 Clone(void* _pArg);
	virtual void				 Free() override;
};

END
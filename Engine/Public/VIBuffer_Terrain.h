#pragma once

#include "VIBuffer.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer_Terrain : public CVIBuffer
{
public:
	XMVECTOR* Get_VertexPos() const { return m_VertexPos; }
	_uint     Get_NumVerticesX() const {return m_iNumverticesX;}
	_uint     Get_NumVerticesZ() const {return m_iNumverticesZ;}

private:
	CVIBuffer_Terrain(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVIBuffer_Terrain(const CVIBuffer_Terrain& Prototype);
	virtual ~CVIBuffer_Terrain() = default;

public:
	virtual HRESULT Initialize_Prototype(const _uint dwCntX, const  _uint dwCntZ, _uint dwVertexItv, const _tchar* path);
	virtual HRESULT Initialize(void* pArg) override;

private:
	XMVECTOR*				m_VertexPos = { nullptr };
	_uint                   m_iNumverticesX, m_iNumverticesZ;

public:
	static CVIBuffer_Terrain* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const _uint dwCntX, const  _uint dwCntZ, _uint dwVertexItv, const _tchar* pPath);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END
#pragma once

#include "VIBuffer_Particle_Instancing.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Point_Instancing final : public CVIBuffer_Particle_Instancing
{
public:
	struct PARTICLE_POINT_INSTANCING_DESC : public CVIBuffer_Particle_Instancing::PARTICLE_INSTANCING_DESC
	{

	};

private:
	CVIBuffer_Point_Instancing(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVIBuffer_Point_Instancing(const CVIBuffer_Point_Instancing& Prototype);
	virtual ~CVIBuffer_Point_Instancing() = default; 


public:
	virtual HRESULT Initialize_Prototype(const PARTICLE_INSTANCING_DESC* pArg) override;
	virtual HRESULT Initialize(void* pArg) override; 


private:
	

public:
	static CVIBuffer_Point_Instancing* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const PARTICLE_INSTANCING_DESC* pArg);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;	 
};

END
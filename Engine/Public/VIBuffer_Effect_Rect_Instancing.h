#pragma once

#include "VIBuffer_Particle_Instancing.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Effect_Rect_Instancing final : public CVIBuffer_Particle_Instancing
{
public:
	struct PARTICLE_RECT_INSTANCING_DESC : public CVIBuffer_Particle_Instancing::PARTICLE_INSTANCING_DESC
	{
		/* 원본 생성할 때 인스턴스 갯수 등 넣어주기 위해 선언하였음.*/
	};

private:
	CVIBuffer_Effect_Rect_Instancing(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVIBuffer_Effect_Rect_Instancing(const CVIBuffer_Effect_Rect_Instancing& Prototype);
	virtual ~CVIBuffer_Effect_Rect_Instancing() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:

public:
	static  CVIBuffer_Effect_Rect_Instancing* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, PARTICLE_INSTANCING_DESC* pArg);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;

};

END
#pragma once

/* 절두체의 정보를 보관할 수 있을꺼야. */
/* 안에 있다 밖에 있다에 대한 판단을 할 ㅅ 있는 기능. */

#include "Base.h"

BEGIN(Engine)

class CFrustum final : public CBase
{
private:
	CFrustum();
	virtual ~CFrustum() = default;

public:
	HRESULT Initialize();
	void Update();

public:
	_bool isIn_WorldSpace(_fvector vWorldPoint, _float fRange = 0.f);
	_bool isIn_AABB_Box(const XMFLOAT3& _fMin, const XMFLOAT3& _fMax);
private:
	class CGameInstance* m_pGameInstance = { nullptr };
	_float4					m_vOriginal_Points[8];
	_float4					m_vWorld_Points[8];
	_float4					m_vWorld_Planes[6];

private:
	void Make_Planes(const _float4* pPoints, _float4* pPlanes);

public:
	static CFrustum* Create();
	virtual void Free() override;
};

END
#pragma once

#include "Component.h"

BEGIN(Engine)
class CShader;		

class ENGINE_DLL CTransform final : public CComponent
{
public:
	struct TRANSFORM_DESC
	{
		_float			fSpeedPerSec    = {};	
		_float			fRotationPerSec = {};	
		_float4         fPosition = {};
		_float3         fScaling = {};
	};

	enum STATE {STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END };

private:
	CTransform(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);	
	virtual ~CTransform() = default;

public:
	_vector Get_State(STATE eState) {
		return XMLoadFloat4x4(&m_WorldMatrix).r[eState];
	}

	_matrix Get_WorldMatrix_Inverse() const {
		return XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_WorldMatrix));
	}

	const _float4x4* Get_WorldMatrix_Ptr() const {	
		return &m_WorldMatrix;		
	}	

	void Set_WorldMatrix(_float4x4 worldmat) { m_WorldMatrix = worldmat; }		

	/* set 하나만들어주자*/
	void Set_MulWorldMatrix(const _float4x4* _Matrix)	
	{
		// _float4x4 -> XMMATRIX 변환 후 곱셈 수행
		XMMATRIX result = XMLoadFloat4x4(_Matrix) * XMLoadFloat4x4(&m_WorldMatrix);	

		// 결과를 _float4x4로 변환하여 m_WorldMatrix에 저장
		XMStoreFloat4x4(&m_WorldMatrix, result);			
	}


	void Set_State(STATE eState, _fvector vState) {
		/*_matrix		WorldMatrix = XMLoadFloat4x4(&m_WorldMatrix);
		WorldMatrix.r[eState] = vState;
		XMStoreFloat4x4(&m_WorldMatrix, WorldMatrix);*/
		XMStoreFloat4(reinterpret_cast<_float4*>(&m_WorldMatrix.m[eState]), vState);		
	}



public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	void Go_Straight_NoNavi(_float fTimeDelta);	
	void Go_Straight(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Backward(_float fTimeDelta);
	void Go_Backward_With_Navi(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Left(_float fTimeDelta);
	void Go_Right(_float fTimeDelta);
	void Go_Dir(_fvector vDir, class CNavigation* pNavigation, _float fTimeDelta);
	void LookAt(_fvector vAt);
	
	void Turn(_fvector vAxis, _float fTimeDelta);/* 실시간 회전 : 매 프레임마다 현재 상태를 기준으로 정해진 속도로 추가로 회전해나간다. */
	void Turn_Navi(_fvector vAxis, _float fTimeDelta, CNavigation* pNavigation);
	
	void Turn_Degree(_fvector vAxis, _float Degree);	
	void Turn_Degree_Navi(_fvector vAxis, _float Degree, CNavigation* pNavigation);
	void Turn_Axis(_fvector vAxis);
	void Rotation(_fvector vAxis, _float fRadians); /* 고정 회전 : 항상 항등상태를 기준으로 전달해준 각도로 회전해놓는다.  */
	void Rotation(_float fX, _float fY, _float fZ);
	void Turn_Move(_fvector vAxis, _float fTimeDelta);	
	void Orbit_Move(_fvector vAxis, _float fTimeDelta, _fvector vCenter);	
	


public:
	HRESULT Bind_ShaderResource(class CShader* pShader, const _char* pConstantName);
	

public:
	void Scaling(const _float3& vScale);
	void Set_Speed(_float _fSpeed) { m_fSpeedPerSec = _fSpeed; }
	void Set_RotationSpeed(_float _fSpeed) { m_fRotationPerSec = _fSpeed; }
	_float3 Compute_Scaled();
	

private:
	/* 객체의 월드 상태를 원점을 기준으로 표현한 행렬(right, up, look, position).  */
	_float4x4				m_WorldMatrix = {};
	_float					m_fSpeedPerSec = { 0.f };
	_float					m_fRotationPerSec = { 0.f };
	_float4					m_fPosition = {};
	_float3					m_fScaling = {};



public:
	static CTransform* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CComponent* Clone(void* pArg) { return nullptr; };
	virtual void Free() override;
};

END
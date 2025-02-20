#pragma once

#include "Client_Defines.h"

#include "GameObject.h"
#include "GameInstance.h"


BEGIN(Engine)
class CModel;
class CShader;
class CCalculator;
class CMesh;
class CCollider;
END

BEGIN(Client)

class CObject  abstract : public CGameObject 
{
public:
	typedef struct Object_Desc : public CGameObject::GAMEOBJECT_DESC
	{
		_float		fFrustumRadius = { 0.f };
		_float3		fRotation = { };
		string		ObjectName = {};

	}OBJECT_DESC;

public:
	typedef struct Object_Info
	{
		_char szName[MAX_PATH] = {};
		_float4	fPosition ;
		_float3 fScale ;
		_float3 fRotation ;
		_float  fFrustumRadius ;

	}OBJECT_INFO;

	typedef struct Mesh_Info
	{
		_float fDist;
		_float3 fPosition;
	}MESHINFO;

protected:
	CObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CObject(const CObject& Prototype);
	virtual ~CObject() = default;

protected:
	virtual HRESULT Initialize(void* pArg) override;

public:
	_bool		 Picking_Objects(_float3& _fPos);

	OBJECT_INFO  Get_ObjectInfo();

	void		 Set_FrustumRadius(_float fFrustumRadius);

protected:
	//Components
	CShader*	 m_pShaderCom = { nullptr };
	CModel*		 m_pModelCom = { nullptr };
	CCalculator* m_pCalculatorCom = { nullptr };
	CCollider* m_pColliderCom = { nullptr };

protected:
	vector<CMesh*> m_Meshes;

	_float		   m_fFrustumRadius = { 0.f };
	_float3		   m_fRotation	= { 0.f, 0.f, 0.f };
	_float3		   m_fScale		= { 0.f, 0.f, 0.f };

	_char		   m_MeshName[MAX_PATH] = {};

protected:
	virtual HRESULT Ready_Components();
	virtual HRESULT Bind_ShaderResources() PURE;

public:

	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END
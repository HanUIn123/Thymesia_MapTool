#pragma once

#include "Client_Defines.h"

#include "GameObject.h"
#include "GameInstance.h"


BEGIN(Engine)
class CModel;
class CShader;
class CCalculator;
class CMesh;
END

BEGIN(Client)

class CObject  abstract : public CGameObject 
{
public:
	typedef struct Object_Desc : public CGameObject::GAMEOBJECT_DESC
	{
		_float		fFrustumRadius = { 0.f };

	}OBJECT_DESC;

private:
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
	_float3		 Picking_Objects();

protected:
	//Components
	CShader*	 m_pShaderCom = { nullptr };
	CModel*		 m_pModelCom = { nullptr };
	CCalculator* m_pCalculatorCom = { nullptr };

protected:
	vector<CMesh*> m_Meshes;

	_float		   m_fFrustumRadius = { 0.f };

protected:
	virtual HRESULT Ready_Components();
	virtual HRESULT Bind_ShaderResources() PURE;

public:

	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END
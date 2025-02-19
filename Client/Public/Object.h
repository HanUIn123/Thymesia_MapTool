#pragma once

#include "Client_Defines.h"

#include "GameObject.h"

BEGIN(Engine)
class CModel;
class CShader;
END

BEGIN(Client)

class CObject  abstract : public CGameObject 
{
public:
	typedef struct Object_Desc : public CGameObject::GAMEOBJECT_DESC
	{
		_float		fFrustumRadius = { 0.f };

	}OBJECT_DESC;

protected:
	CObject(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CObject(const CObject& Prototype);
	virtual ~CObject() = default;

protected:
	//Components
	CShader* m_pShaderCom = { nullptr };
	CModel*  m_pModelCom = { nullptr };

public:

	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END
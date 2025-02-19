#pragma once

#include "Object.h"

BEGIN(Client)

class CSM_Wall_Shelf final : public CObject
{
private:
	CSM_Wall_Shelf(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CSM_Wall_Shelf(const CSM_Wall_Shelf& Prototype);
	virtual ~CSM_Wall_Shelf() = default;

public:


private:

public:
	static CSM_Wall_Shelf* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END
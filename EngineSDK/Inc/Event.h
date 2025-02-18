#pragma once

#include "Base.h"


BEGIN(Engine)		
class CGameObject;

class CEvent final : public CBase
{
private:
	CEvent(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CEvent() = default; 


public:
	HRESULT Initalize();
	void    Activate(_wstring _EventName);	


private:
	ID3D11Device*         m_pDevice  = { nullptr };
	ID3D11DeviceContext*  m_pContext = { nullptr };

public:
	HRESULT	 Add_EventObject(CGameObject* pGameObject);
	HRESULT  Sub_EventObject(CGameObject* pGameObject);		
		

private:
	vector<CGameObject*>     m_vecEventObject;		 

public:
	static CEvent* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual void Free() override;

};
END	


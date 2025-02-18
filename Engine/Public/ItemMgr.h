#pragma once

#include "Base.h"

BEGIN(Engine)
class CBase;
class CGameInstance; 

class ENGINE_DLL CItemMgr : public CBase
{
private:
	CItemMgr();
	virtual ~CItemMgr() = default; 


public:
	HRESULT Initialize(); 
	HRESULT Update();

	_uint   Count_Item(_wstring _ItemName);		
	HRESULT Add_Item(_wstring _ItemName);	
	HRESULT Sub_Item(_wstring _ItemName);	

private:
	map<_wstring, _uint> m_mapItemBag; 
	CGameInstance* m_pGameInstance;		

public:
	static CItemMgr* Create();		
	virtual void Free() override; 

};
END

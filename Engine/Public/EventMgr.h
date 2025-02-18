#pragma once

#include "Base.h"
#include "Event.h"

BEGIN(Engine)
class CGameInstance; 

class CEventMgr : public CBase
{
private:
	CEventMgr(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CEventMgr() = default; 

private:
	HRESULT  Initialize();

public:
	/* 이벤트 관련 객체를 넣어줄 때 사용*/
	HRESULT  Add_EventObject(_wstring _EventName, CGameObject* pGaemObject);	
	HRESULT  Sub_EventObject(_wstring _EventName, CGameObject* pGaemObject);	

	/* 이벤트 관련 객체들의 트리거가 발생할 때 발생 */
	HRESULT  Event_Activate(_wstring _EventName);	

	/* 객체의 삭제와 생성과 관련된 함수들 */
	HRESULT  Add_DeadObject(_wstring _LayerName, CGameObject* pGaemObject);	
	HRESULT  Add_DeadEffect(CGameObject* pGameObject);	

	HRESULT  Update();

private:
	ID3D11Device*        m_pDevice       = { nullptr };
	ID3D11DeviceContext* m_pContext      = { nullptr };
	CGameInstance*       m_pGameInstance = { nullptr };

private:
	map<_wstring, CEvent*>		   m_mapEvent; 
	map<_wstring, CGameObject*>    m_mapDeadObejct; 
	vector<CGameObject*>		   m_vecDeadEffect; 

public:
	static CEventMgr* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual void Free() override; 
		 
};

END	
#pragma once


#include "Client_Defines.h"
#include "Base.h"

BEGIN(Engine)
class CGameInstance;
END

/* 절차지향(Window API) 만으로 게임을 구현하기 힘들기 때문에 */
/* 내 코드의 흐름을 CMainApp클래스의 반복적인 업데이트와 렌더쪽을 당겨온다. */
BEGIN(Client)

class CMainApp final : public CBase
{
private:
	CMainApp();
	virtual ~CMainApp() = default;

public:
	HRESULT Initialize();
	void Update(_float fTimeDelta);
	HRESULT Render();

private: /* 엔진의 기능을 이용ㅇ하기위해 게임인스튼서 클래스르 ㄱㄹ객체화 해놓았다. */
	CGameInstance*			m_pGameInstance = { nullptr };
	ID3D11Device*			m_pDevice = { nullptr };
	ID3D11DeviceContext*	m_pContext = { nullptr };

#ifdef _DEBUG
private:
	_float				m_fTimerAcc = {};
	_uint				m_iDrawCount = {};
	_tchar				m_szFPS[MAX_PATH] = {};
#endif

public:
	HRESULT Start_Level(LEVELID eStartLevelID);

public:
	static CMainApp* Create();
	virtual void Free() override;
};

END
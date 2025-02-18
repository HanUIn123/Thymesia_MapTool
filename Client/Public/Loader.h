#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)

class CLoader final : public CBase
{
private:
	CLoader(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CLoader() = default;


public:
	HRESULT Initialize(LEVELID eNextLevelID);
	HRESULT Start_Loading();
	_bool isFinished() const {
		return m_isFinished;
	}


#ifdef _DEBUG
public:
	void SetUp_WindowText();
#endif

private:
	ID3D11Device*			m_pDevice = { nullptr };
	ID3D11DeviceContext*	m_pContext = { nullptr };
	CGameInstance*			m_pGameInstance = { nullptr };
	LEVELID					m_eNextLevelID = { LEVEL_END };

	HANDLE					m_hThread = {};
	CRITICAL_SECTION		m_CriticalSection = {};

	_bool					m_isFinished = { false };
	_tchar					m_szLoadingText[MAX_PATH] = {};

private:
	HRESULT Loading_For_Level_Logo();
	HRESULT Loading_For_Level_GamePlay();
	

public:
	static CLoader* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LEVELID eNextLevelID);
	virtual void Free() override;
};

END
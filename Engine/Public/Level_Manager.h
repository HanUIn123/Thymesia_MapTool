#pragma once

#include "Base.h"

/* 1. 현재 할당된 레벨의 주소를 보관하낟. */
/* 2. 보관하고 있는 레벨의 반복적인 갱신과 드로우를 수행한다. */
/* 3. 새로운 레벨로 할당 시, 기존 레벨을 파괴하고 기존 레벨용 자원들도 파괴한다. */


BEGIN(Engine)

class CLevel_Manager final : public CBase
{
private:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default;

public:
	HRESULT Open_Level(_uint iNewLevelIndex, class CLevel* pNewLevel);

public:
	void Update(_float fTimeDelta);
	HRESULT Render();

private:
	_uint					m_iLevelIndex = {};
	class CLevel*			m_pCurrentLevel = { nullptr };
	class CGameInstance*	m_pGameInstance = { nullptr };

public:
	static CLevel_Manager* Create();
	virtual void Free() override;
};

END
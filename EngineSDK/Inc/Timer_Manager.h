#pragma once

#include "Base.h"

BEGIN(Engine)

class CTimer;
class CTimer_Manager : public CBase
{
private:
	CTimer_Manager();
	virtual ~CTimer_Manager() = default;

public:
	_float			Get_TimeDelta(const _wstring& strTimerTag);	

public:
	HRESULT			Add_Timer(const _wstring& strTimerTag);
	void			Compute_TimeDelta(const _wstring& strTimerTag);

private:
	// map<const _tchar*, CTimer*>			m_Timers;
	map<const _wstring, CTimer*>		m_Timers;

private:
	CTimer*	Find_Timer(const _wstring& strTimerTag);

public:
	static CTimer_Manager* Create();
	virtual void Free();
};

END
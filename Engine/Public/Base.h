#pragma once

#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	CBase();
	virtual ~CBase() = default;

public:
	/* 레퍼런스 카운트를 증가시키낟. */
	_uint AddRef();

	/* 레퍼런스 카운트를 감소시킨다. or 삭제한다. */
	_uint Release();
private:
	_uint			m_iRefCnt = {};

public:
	virtual void Free();
};

END
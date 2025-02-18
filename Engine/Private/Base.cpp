#include "..\Public\Base.h"



CBase::CBase()
{
}

_uint CBase::AddRef()
{
	return ++m_iRefCnt;
}

_uint CBase::Release()
{
	if (0 == m_iRefCnt)
	{
		Free(); 

		delete this;

		return 0;
	}

	else
		return m_iRefCnt--;
}

void CBase::Free()
{
}


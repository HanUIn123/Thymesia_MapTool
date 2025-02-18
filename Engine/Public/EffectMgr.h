#pragma once

#include "Base.h"

BEGIN(Engine)

class CGameObject;	


class CEffectMgr : public CBase 
{
private:
	CEffectMgr(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);	 
	virtual ~CEffectMgr() = default; 

public:
	HRESULT Initialize();
	void Priority_Update(_float _fTimeDelta);		
	void Update(_float _fTimeDelta);		
	void Late_Update(_float _fTimeDelta);

public:
	HRESULT Add_Effect(CGameObject* pEffect); 
	HRESULT Sub_Effect(CGameObject* pEffect);


private:
	ID3D11Device* m_pDevice = { nullptr };
	ID3D11DeviceContext* m_pContext = { nullptr };


private:
	vector<CGameObject*>  m_vecEffect;



public:
	static CEffectMgr* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual void Free() override; 
};

END
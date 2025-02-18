#pragma once

#include "Base.h"

BEGIN(Engine)

class CLight_Manager final : public CBase
{
private:
	CLight_Manager(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CLight_Manager() = default;

public:
	const LIGHT_DESC* Get_LightDesc(_uint iIndex) const;

public:
	HRESULT Initialize();
	HRESULT Add_Light(const LIGHT_DESC& LightDesc);
	void Render_Lights(class CShader* pShader, class CVIBuffer_Rect* pVIBuffer);		

private:
	ID3D11Device*					m_pDevice = {};
	ID3D11DeviceContext*			m_pContext = {};
	list<class CLight*>				m_Lights;

public:
	static CLight_Manager* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	virtual void Free() override;
};

END
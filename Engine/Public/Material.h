#pragma once

#include "Base.h"

BEGIN(Engine)

class CMaterial : public CBase
{
private:
	CMaterial(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CMaterial() = default; 

public:
	HRESULT Initialize(const aiMaterial* pAIMaterial, const _char* pModelFilePath);
	HRESULT Bind_Material(class CShader* pShader, aiTextureType eType, const _char* pConstantName, _uint iTextureIndex);


private:
	ID3D11Device*				m_pDevice  = { nullptr };
	ID3D11DeviceContext*		m_pContext = { nullptr };

	vector<ID3D11ShaderResourceView*> m_MtrlTextures[AI_TEXTURE_TYPE_MAX];

	/* 바이너리화 관련 */
	_uint								m_iNumTextures = {};
	vector<ID3D11ShaderResourceView*>	m_ForSaveMtrlTextures[AI_TEXTURE_TYPE_MAX];
	_tchar								m_szLastPath[MAX_PATH] = {};


public:
	HRESULT Save_Material(ostream& os, const aiMaterial* pAIMaterial, const _char* pModelFilePath);	
	HRESULT Load_Material(istream& os);	

	static CMaterial* LoadCreate(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, istream& os);	
	static CMaterial* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const aiMaterial* pAIMaterial, const _char* pModelFilePath);	
	virtual void Free() override; 

};

END
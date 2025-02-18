#include "..\Public\Texture.h"

#include "Shader.h"

CTexture::CTexture(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CComponent { pDevice, pContext }
{
}

CTexture::CTexture(const CTexture & Prototype)
	: CComponent( Prototype )
	, m_iNumSRVs { Prototype.m_iNumSRVs }
	, m_SRVs{ Prototype.m_SRVs }
{
	for (auto& pSRV : m_SRVs)
		Safe_AddRef(pSRV);
}

HRESULT CTexture::Initialize_Prototype(const _tchar * pTextureFilePath, _uint iNumTextures)
{
	m_iNumSRVs = iNumTextures;

	_tchar		szEXT[MAX_PATH] = {};

	_wsplitpath_s(pTextureFilePath, nullptr, 0, nullptr, 0, nullptr, 0, szEXT, MAX_PATH);

	for (size_t i = 0; i < m_iNumSRVs; i++)
	{
		ID3D11Texture2D*					pTexture2D = { nullptr };
		ID3D11ShaderResourceView*			pSRV = { nullptr };

		_tchar			szTextureFilePath[MAX_PATH] = TEXT("");

		wsprintf(szTextureFilePath, pTextureFilePath, i);
		
		HRESULT			hr = {};


		if (false == lstrcmp(szEXT, TEXT(".dds")))
		{
			/* .dds */
			hr = CreateDDSTextureFromFile(m_pDevice, szTextureFilePath, nullptr, &pSRV);
		}
		else if (false == lstrcmp(szEXT, TEXT(".tga")))
		{
			hr = E_FAIL;
		}
		else
		{	/* .jpg etc */
			hr = CreateWICTextureFromFile(m_pDevice, szTextureFilePath, nullptr, &pSRV);
		}

		if (FAILED(hr))
			return E_FAIL;

		m_SRVs.push_back(pSRV);
	}
	
	return S_OK;
}

HRESULT CTexture::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CTexture::Bind_ShaderResource(CShader * pShader, const _char * pConstantName, _uint iIndex)
{
	if (iIndex >= m_iNumSRVs)
		return E_FAIL;

	return pShader->Bind_SRV(pConstantName, m_SRVs[iIndex]);	
}

CTexture * CTexture::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, const _tchar * pTextureFilePath, _uint iNumTextures)
{
	CTexture*	pInstance = new CTexture(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype(pTextureFilePath, iNumTextures)))
	{
		MSG_BOX("Failed To Created : CTexture");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CTexture::Clone(void * pArg)
{
	CTexture*	pInstance = new CTexture(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Cloned : CTexture");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTexture::Free()
{
	__super::Free();

	for (auto& pSRV : m_SRVs)
		Safe_Release(pSRV);

	m_SRVs.clear();

}

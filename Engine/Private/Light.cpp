#include "..\Public\Light.h"
#include "Shader.h"
#include "VIBuffer_Rect.h"	


CLight::CLight(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: m_pDevice { pDevice }
	, m_pContext { pContext }
{
	Safe_AddRef(m_pContext);
	Safe_AddRef(m_pDevice);
}

HRESULT CLight::Initialize(const LIGHT_DESC & LightDesc)
{
	m_LightDesc = LightDesc;

	return S_OK;
}

void CLight::Render(CShader* pShader, CVIBuffer_Rect* pVIBuffer)	
{
	if (FAILED(pShader->Bind_RawValue("g_vLightDir", &m_LightDesc.vDirection, sizeof(_float4))))	
		return;		

	if (FAILED(pShader->Bind_RawValue("g_vLightDiffuse", &m_LightDesc.vDiffuse, sizeof(_float4))))
		return;

	if (FAILED(pShader->Bind_RawValue("g_vLightAmbient", &m_LightDesc.vAmbient, sizeof(_float4))))
		return;

	if (FAILED(pShader->Bind_RawValue("g_vLightSpecular", &m_LightDesc.vSpecular, sizeof(_float4))))
		return;


	pShader->Begin(1);		

	pVIBuffer->Bind_InputAssembler();		
	pVIBuffer->Render();		

}

CLight * CLight::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, const LIGHT_DESC & LightDesc)
{
	CLight*		pInstance = new CLight(pDevice, pContext);

	if (FAILED(pInstance->Initialize(LightDesc)))
	{
		MSG_BOX("Failed to Created : CLight");
		Safe_Release(pInstance);
	}

	return pInstance;
}


void CLight::Free()
{
	__super::Free();

	Safe_Release(m_pContext);
	Safe_Release(m_pDevice);
}

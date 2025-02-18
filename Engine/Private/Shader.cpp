#include "..\Public\Shader.h"

CShader::CShader(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CComponent { pDevice, pContext }
	, m_pEffect{ nullptr }
{

}

CShader::CShader(const CShader & Prototype)
	: CComponent( Prototype )
	, m_pEffect { Prototype.m_pEffect }
	, m_iNumPasses { Prototype.m_iNumPasses }
	, m_InputLayout { Prototype.m_InputLayout }
{
	for (auto& pInputLayout : m_InputLayout)
		Safe_AddRef(pInputLayout);

	Safe_AddRef(m_pEffect);
}

HRESULT CShader::Initialize_Prototype(const _tchar * pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC* pVertexElements, _uint iNumElements)
{
	_uint			iHlslFlag = {};

#ifdef _DEBUG
	iHlslFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	iHlslFlag = D3DCOMPILE_OPTIMIZATION_LEVEL1;
#endif

	ID3DBlob*		pErrMsg = { nullptr };	

	if (FAILED(D3DX11CompileEffectFromFile(pShaderFilePath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, iHlslFlag, 0, m_pDevice, &m_pEffect, &pErrMsg)))
		return E_FAIL;

	ID3DX11EffectTechnique*		pTechnique = m_pEffect->GetTechniqueByIndex(0);
	if (nullptr == pTechnique)
		return E_FAIL;

	D3DX11_TECHNIQUE_DESC		TechniqueDesc{};

	pTechnique->GetDesc(&TechniqueDesc);

	m_iNumPasses = TechniqueDesc.Passes;

	for (size_t i = 0; i < m_iNumPasses; i++)
	{
		ID3DX11EffectPass*		pPass = pTechnique->GetPassByIndex(i);
		ID3D11InputLayout*		pInputLayout = { nullptr };

		D3DX11_PASS_DESC		PassDesc{};

		pPass->GetDesc(&PassDesc);



		if (FAILED(m_pDevice->CreateInputLayout(pVertexElements, iNumElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &pInputLayout)))
			return E_FAIL;

		m_InputLayout.push_back(pInputLayout);

	}

	return S_OK;
}

HRESULT CShader::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CShader::Begin(_uint iPassIndex)
{
	if (iPassIndex >= m_iNumPasses)
		return E_FAIL;

	m_pContext->IASetInputLayout(m_InputLayout[iPassIndex]);

	m_pEffect->GetTechniqueByIndex(0)->GetPassByIndex(iPassIndex)->Apply(0, m_pContext);

	return S_OK;
}

HRESULT CShader::Bind_RawValue(const _char * pConstantName, const void * pData, _uint iSize)
{
	if (nullptr == m_pEffect)
		return E_FAIL;

	/* 내가 지정한 셰이더 내에 선언된 전역변수의 핸들을 얻어온다. */
	ID3DX11EffectVariable*		pVariable = m_pEffect->GetVariableByName(pConstantName);
	if (nullptr == pVariable)
		return E_FAIL;

	return pVariable->SetRawValue(pData, 0, iSize);
	
}



HRESULT CShader::Bind_Matrix(const _char* pConstantName, const _float4x4* pMatrix)
{
	if (nullptr == m_pEffect)
		return E_FAIL;

	/* 내가 지정한 셰이더 내에 선언된 전역변수의 핸들을 얻어온다. */
	ID3DX11EffectVariable*		pVariable = m_pEffect->GetVariableByName(pConstantName);
	if (nullptr == pVariable)
		return E_FAIL;

	ID3DX11EffectMatrixVariable*		pMatrixVariable = pVariable->AsMatrix();
	if (nullptr == pMatrixVariable)
		return E_FAIL;	

	return pMatrixVariable->SetMatrix(reinterpret_cast<const _float*>(pMatrix));	
}

HRESULT CShader::Bind_Matrices(const _char* pConstantName, const _float4x4* pMatrix, _uint iNumMatrices)
{
	ID3DX11EffectVariable* pVariable = m_pEffect->GetVariableByName(pConstantName);
	if (nullptr == pVariable)
		return E_FAIL; 

	ID3DX11EffectMatrixVariable* pMatrixVariable = pVariable->AsMatrix();
	if (nullptr == pMatrixVariable)
		return E_FAIL; 

	return pMatrixVariable->SetMatrixArray(reinterpret_cast<const _float*>(pMatrix), 0 , iNumMatrices);
}

HRESULT CShader::Bind_SRV(const _char * pConstantName, ID3D11ShaderResourceView * pSRV)
{
	/* 내가 지정한 셰이더 내에 선언된 전역변수의 핸들을 얻어온다. */
	ID3DX11EffectVariable*		pVariable = m_pEffect->GetVariableByName(pConstantName);
	if (nullptr == pVariable)
		return E_FAIL;

	ID3DX11EffectShaderResourceVariable*	pSRVariable = pVariable->AsShaderResource();
	if (nullptr == pSRVariable)
		return E_FAIL;

	return pSRVariable->SetResource(pSRV);
}

CShader * CShader::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, const _tchar * pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC* pVertexElements, _uint iNumElements)
{
	CShader*	pInstance = new CShader(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype(pShaderFilePath, pVertexElements, iNumElements)))
	{
		MSG_BOX("Failed To Created : CShader");
		Safe_Release(pInstance);
	}

	return pInstance;
}


CComponent * CShader::Clone(void * pArg)
{
	CShader*	pInstance = new CShader(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed To Created : CShader");
		Safe_Release(pInstance);
	}

	return pInstance;
}
void CShader::Free()
{
	__super::Free();

	for (auto& pInputLayout : m_InputLayout)
		Safe_Release(pInputLayout);

	m_InputLayout.clear();

	Safe_Release(m_pEffect);
}

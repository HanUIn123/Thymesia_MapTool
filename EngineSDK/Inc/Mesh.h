#pragma once

#include "VIBuffer.h"
#include "Model.h"

BEGIN(Engine)

class CMesh final : public CVIBuffer
{
private:
	CMesh(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);	
	CMesh(const CMesh& Prototype);
	virtual ~CMesh() = default;

public:
	_uint Get_MaterialIndex() const
	{
		return m_iMaterialIndex;	
	}

public:
	virtual HRESULT Initialize_Prototype(CModel::MODEL eModelType, CModel* pModel, const aiMesh* pAIMesh, _fmatrix PreTransformMatrix);
	virtual HRESULT Initialize(void* pArg) override;

public:
	HRESULT Bind_BoneMatrices(class CShader* pShader, const _char* pContstantName, const vector<class CBone*>& Bones);


private:
	_char			   m_szName[MAX_PATH] = {};
	/* 이 메시에 영향을 주는 뼈의 갯수 */
	_uint			   m_iMaterialIndex = {};

	/* 이 메시에 영향을 주는 뼈들의 인덱스 */
	_uint			   m_iNumBones = {};

	/* 인덱스 : 모델이 가지고 있는 전체 뼈 기준의 인덱스를 말하는 것이다*/
	vector<_uint>      m_BoneIndices;

	_float4x4          m_BoneMatrices[1500] = {}; /* 셰이더 코드의 전역 함수에 값을 넣을려고 준비*/
	_float4x4		   m_ColMajorBoneMatrices[1500] = {};

	vector<_float4x4>  m_OffsetMatrices;

	/* 바이너리화 관련 맴버 변수*/
	D3D11_BUFFER_DESC	  m_MeshBufferdesc = {};	
	VTXMESH*			  m_nonAnimpVertices;	
	VTXANIMMESH*		  m_AnimVertices;	
	CModel::MODEL         m_ModelType;	
	_uint*				  pNewIndices;	

private:
	/*structed Buffer 관련 코드*/
	ID3D11Buffer* m_pStrBuffer = { nullptr };	

private:
	HRESULT  Ready_VertexBuffer_ForNonAnim(const aiMesh* pAIMesh, _fmatrix PreTransforMatrix);
	HRESULT  Ready_VertexBuffer_ForAnim(CModel* pModel, const aiMesh* pAIMesh, _fmatrix PreTransforMatrix);

public:
	HRESULT Save_Mesh(ostream& os);	
	HRESULT Load_Mesh(istream& is);	


public:
	static CMesh* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, CModel::MODEL eModelType, CModel* pModel, const aiMesh* pAIMesh,_fmatrix PreTransformMatrix);
	static CMesh* LoadCreate(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, istream& is);	
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END
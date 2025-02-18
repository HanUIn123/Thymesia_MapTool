#pragma once

#include "Component.h"

BEGIN(Engine)
class CAnimation;	

class ENGINE_DLL CModel final : public CComponent
{
public:
	enum MODEL { MODEL_NONANIM, MODEL_ANIM, MODEL_END };	
private:
	CModel(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CModel(const CModel& Prototype);
	virtual ~CModel() = default;

public:
	_uint Get_NumMeshes() const 
	{
		return m_iNumMeshes;
	}

	_uint Get_BoneIndex(const _char* pBoneName) const;
	const _float4x4* Get_BoneMatrix(const _char* pBoneName) const;
	const _float4x4* Get_RootMotionMatrix(const _char* pBoneName) const;

public:
	virtual HRESULT Initialize_Prototype(MODEL eModelType, const _char* pModelFilePath, _fmatrix PreTransformMatrix);
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Render(_uint iMeshIndex);	

public:
	void SetUp_Animation(_uint iAnimIndex, _bool isLoop);
	_bool Play_Animation(_float fTimeDelta);
	HRESULT Bind_Material(class CShader* pShader, _uint iMeshIndex, aiTextureType eType, const _char* pConstantName, _uint iTextureIndex = 0);
	HRESULT Bind_BoneMatrices(class CShader* pShader, _uint iMeshIndex, const _char* pConstantName);	
	CAnimation* Get_CurAnimation() { return m_pCurrentAnimation; }	
	vector<class CAnimation*>& Get_VecAnimation() { return  m_Animations; }	
	_uint   Get_Current_Animation_Index() { return m_iCurrentAnimIndex; }



private:
	/* 가져온 정보를 저장한다. */
	//const aiScene*					m_pAIScene = { nullptr };
	const aiScene*					m_pAIScene = { nullptr };

	/* 파일을 뜯어서 읽고 정리해준다. */
	//Assimp::Importer				m_Importer = {};
	Assimp::Importer				m_Importer = {};  /* 새로 써야지만 다시 메모리 획득 */

private:
	_uint							m_iNumMeshes = {};
	vector<class CMesh*>			m_Meshes;

	MODEL							m_eModelType = MODEL_END;

private:
	_uint							m_iNumMaterials = {};
	vector<class CMaterial*>        m_Materials; 

private:
	vector<class CBone*>            m_Bones;

private:
	_uint							m_iNumAnimations = {};
	_uint							m_iCurrentAnimIndex = {};
	/* 11월 27일 추가*/
	_uint							m_iPAnimIndex = {};
	//
	vector<class CAnimation*>       m_Animations; 
	_bool							m_isAnimLoop = {};

	/* 쌤꺼 추가 */
	_float							m_fCurrentTrackPosition = {};
	vector<vector<_uint>>			m_CurrentKeyFrameIndices; /* 애니메이션을 관리 하는 인덱스 */
	_float4x4						m_PreTransformMatrix; 


	/* 애니메이션 관련*/
	_bool							m_bFirst = { true };


private:
	/* 선형보간 추가작업*/
	CAnimation* m_pNextAnimation = nullptr;
	CAnimation* m_pCurrentAnimation = nullptr;
	_uint       m_iNextAnimationIndex = {};
	_bool       m_bFinished = { false };
	_uint       m_iCurrentAnimationIndex = {};
	_bool       m_bLerpFinished = { false };

public:
	_bool       Get_LerpFinished()	    { return m_bLerpFinished; }
	/* 루트 모션 용 추가*/
	_bool		GetAniFinish()	 { return m_bFinished; }
	

/* 바이너리화 관련 */
private:
	string			m_fullpath; 
	_bool			isFile = false; 

private:
	HRESULT		Save_Model(const _char* pModelFilePath);
	HRESULT     Load_Model(_fmatrix PreTransformMatrix);

//

private:
	HRESULT Ready_Meshes(_fmatrix PreTransformMatrix);	
	HRESULT Ready_Materials(const _char* pModelFilePath);
	HRESULT Ready_Bones(const aiNode* pAIBone, _int iParentBoneIndex = -1);
	HRESULT Ready_Animations();

public:
	static CModel* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const _char* pModelFilePath, MODEL eModelType, _fmatrix  PreTransformMatrix = XMMatrixIdentity());
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;

};

END
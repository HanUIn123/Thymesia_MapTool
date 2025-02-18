#pragma once

#include "Base.h"

BEGIN(Engine)

class CChannel final : public CBase
{
private:
	CChannel();
	virtual ~CChannel() = default; 

public:
	HRESULT Initialize(const aiNodeAnim* pAIChannel, const class CModel* pModel);
	void Update_TransformationMatrix(_float fCurrentTrackPosition, _uint* pCurrentKeyFrameIndex, const vector<class CBone*>& Bones);
	void Lerp_TransformationMatrix(const vector<class CBone*>& Bones, CChannel* pNextChannel, _float LerpTime, _float LerpTimeAcc, _uint* pCurrentKeyFrameIndex);
	void Reset_TransformationMatrix(const vector<class CBone*>& Bones, _uint* pCurrentKeyFrameIndex);


	/*void Lerp(_uint _iCurrentAnimIndex)*/
	const _char* Get_Name() const {	
		return m_szName;	
	}	

private:
	char		m_szName[MAX_PATH] = {};
	
	/* 이 뼈가 특정 애니메이션을 구동하기 위해 특정 시간마다의 상태를 가진다. */

	/* KeyFrame : 특정 시간에 표현해야할 뼈의 상태. */
	_uint					m_iNumKeyframes = {};
	vector<KEYFRAME>		m_Keyframes;

	_uint                   m_iCurrentKeyFrameIndex = {};

	/* 이 채널(뼈)의 이름과 같은 이름을 가진 모델(전체뼈)중의 뼈를 찾아서 그 뼈의 인덱스를 저장한다.*/
	_uint					m_iBoneIndex = {};


	/* 12월 10일 루트 모션 */
	/* 이 채널(뼈)의 행렬을 월드매트릭스에 곱해주기 위해 행렬 따로 저장*/
	_float4x4               m_WorldTranslation = { };		



public:
	HRESULT Save_Channel(ostream& os);	
	HRESULT Load_Channel(istream& is);	
	static CChannel* LoadCreate(istream& is);	
	static CChannel* Create(const aiNodeAnim* pAIChannel, const class CModel* pModel);
	virtual void Free() override; 

};

END
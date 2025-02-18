#pragma once 

#include "Base.h"

BEGIN(Engine)


class CAnimation : public CBase
{
private:
	CAnimation();
	virtual ~CAnimation() = default; 


public:
	HRESULT Initialize(const aiAnimation* pAIAnimation, const class CModel* pModel, vector<_uint>& CurrentKeyFrameIndices);
	_bool Update_TransformationMatrix(_float fTimeDelta, const vector<class CBone*>& Bones, _float* pCurrentTrackPoisiton, vector<_uint>& CurrentKeyFrameIndices, _bool isLoop);


	/* 11월 27일 추가한 코드 */
	void  Reset(const vector<class CBone*>& Bones, vector<_uint>& CurrentKeyFrameIndices, _float* pCurrentTrackPoisiton);
	_uint Get_ChannelIndex(const _char* pChannelName);	
	_bool Lerp_NextAnimation(_float fTimeDelta, class CAnimation* pNextAnimation, const vector<class CBone*>& Bones, vector<_uint>& CurrentKeyFrameIndices);	
	void  SetLerpTime(_float _LerpTime) { m_LerpTime = _LerpTime; }	

	/*1월 15일 추가한 코드*/
	_bool isAniMationFinish() { return m_isFinished; }

private:
	_float					   m_fDuration = {};
	_float					   m_fTickPerSecond = {};
	_float					   m_fCurrentTrackPosition = {};
	_float					   m_iNumChannels = {};

	/*Channel == Bone*/
	vector<class CChannel*>    m_Channels;
	
	_char					   m_szName[MAX_PATH];	


	/*11월 27일 추가 코드*/
    /* 그러면 저기서 애니메이션을 초기화 시켜줘야하는데.*/

	bool                       m_bReset = { false };

	_float					   m_LerpTime = 1.2f;
	_float					   m_LerpTimeAcc = 0.f;

	_bool					   m_isFinished = { false };

	vector<_uint>*			   m_CurrentKeyFameIndices;	


public:

	HRESULT Save_Anim(ostream& os);
	HRESULT Load_Anim(istream& is, vector<_uint>& CurrentKeyFrameIndices);

	static CAnimation* Create(const aiAnimation* pAIAnimation, const class CModel* pModel, vector<_uint>& CurrentKeyFrameIndices);	
	static CAnimation* LoadCreate(istream& is, vector<_uint>* _CurrentKeyFrameIndices);	
	virtual void Free() override;

};
END
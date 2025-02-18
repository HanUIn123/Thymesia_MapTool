#include "Animation.h"
#include "Channel.h"

CAnimation::CAnimation()
{
}

HRESULT CAnimation::Initialize(const aiAnimation* pAIAnimation, const CModel* pModel, vector<_uint>& CurrentKeyFrameIndices)
{
    /* 이 애니메이션의 이름*/
    memcpy(m_szName, pAIAnimation->mName.data, sizeof(_char) * MAX_PATH);   
    

    /* 이 애니메이션의 전체 길이 (10) */
    m_fDuration = static_cast<_float>(pAIAnimation->mDuration);

    /* 이 애니메이션의 초당 재생 거리 */
    m_fTickPerSecond = static_cast<_float>(pAIAnimation->mTicksPerSecond);

    /* 이 애니메이션을 구동하는데 있어 필요한 뼈의 갯수*/
    m_iNumChannels = pAIAnimation->mNumChannels;

    CurrentKeyFrameIndices.resize(m_iNumChannels);

    m_CurrentKeyFameIndices = &CurrentKeyFrameIndices;          

    for(size_t i =0 ; i<m_iNumChannels; i++)
    {
        CChannel* pChannel = CChannel::Create(pAIAnimation->mChannels[i], pModel);
        if (nullptr == pChannel)
            return E_FAIL;

        m_Channels.push_back(pChannel);

    }

    return S_OK;
}

_bool CAnimation::Update_TransformationMatrix(_float fTimeDelta, const vector<class CBone*>& Bones, _float* pCurrentTrackPoisiton, vector<_uint>& CurrentKeyFrameIndices, _bool isLoop)
{
    *pCurrentTrackPoisiton += m_fTickPerSecond * fTimeDelta;    
   
    if (true == isLoop && *pCurrentTrackPoisiton >= m_fDuration)
    {
        m_isFinished = true;
        *pCurrentTrackPoisiton = 0.f;
    }


    /* 다음 애니메이션으로 이동전에는 여기 걸려서 true가 반환될거임.*/
    else if (*pCurrentTrackPoisiton >= m_fDuration)
    {
        m_isFinished = true;    
        return true;    
    }

    else
        m_isFinished = false;   
        
   

    _uint			iNumChannels = {};  

    for(auto& pChannel : m_Channels)
    {
        
        pChannel->Update_TransformationMatrix(*pCurrentTrackPoisiton, &CurrentKeyFrameIndices[iNumChannels++], Bones);
         
    }


    return false;
}

void CAnimation::Reset(const vector<class CBone*>& Bones, vector<_uint>& CurrentKeyFrameIndices, _float* pCurrentTrackPoisiton)
{
    *pCurrentTrackPoisiton = 0.0f;     
    m_isFinished =  false;
    
    _uint  iChannelIndex = { 0 };
    for(auto& pChannel : m_Channels)
    {
        pChannel->Reset_TransformationMatrix(Bones, &CurrentKeyFrameIndices[iChannelIndex++]);
    }

}

_uint CAnimation::Get_ChannelIndex(const _char* pChannelName)
{
    _uint	iChannelIndex = {};

    auto iter = find_if(m_Channels.begin(), m_Channels.end(), [&](CChannel* pChannel)->_bool {
        if (false == strcmp(pChannel->Get_Name(), pChannelName))
            return true;

        ++iChannelIndex;
        return false;
        });
   
    return iChannelIndex;
}

_bool CAnimation::Lerp_NextAnimation(_float fTimeDelta, CAnimation* pNextAnimation, const vector<class CBone*>& Bones, vector<_uint>& CurrentKeyFrameIndices)
{
    m_LerpTimeAcc += fTimeDelta;


    if(pNextAnimation && m_LerpTimeAcc <= m_LerpTime)
    {
        _uint iChannelIndex = 0; 
        for (auto& pChannel : m_Channels)
        {
            pChannel->Lerp_TransformationMatrix(Bones, pNextAnimation->m_Channels[iChannelIndex], m_LerpTime, m_LerpTimeAcc, &CurrentKeyFrameIndices[iChannelIndex]);
            iChannelIndex++;
        }
        return false; 
    }
                                                     
    else
    {
        m_LerpTimeAcc = 0.0f;
        return true; 
    }

    //return _bool();
}

HRESULT CAnimation::Save_Anim(ostream& os)
{
    os.write((char*)&m_szName, sizeof(_char) * MAX_PATH);   
    os.write((char*)&m_fDuration, sizeof(_float));  
    os.write((char*)&m_fTickPerSecond, sizeof(_float)); 
    os.write((char*)&m_fCurrentTrackPosition, sizeof(_float));  
    os.write((char*)&m_isFinished, sizeof(_bool));  
    os.write((char*)&m_iNumChannels, sizeof(_uint));    

    for (auto& channel : m_Channels)
        channel->Save_Channel(os);

    return S_OK;
}

HRESULT CAnimation::Load_Anim(istream& is, vector<_uint>& CurrentKeyFrameIndices)
{
    is.read((char*)&m_szName, sizeof(_char) * MAX_PATH);    
    is.read((char*)&m_fDuration, sizeof(_float));
    is.read((char*)&m_fTickPerSecond, sizeof(_float));
    is.read((char*)&m_fCurrentTrackPosition, sizeof(_float));
    is.read((char*)&m_isFinished, sizeof(_bool));
    is.read((char*)&m_iNumChannels, sizeof(_uint));
    /*readVectorFromBinary(is, m_CurrentKeyFrameIndices);*/
    CurrentKeyFrameIndices.resize(m_iNumChannels);


    for (_uint i = 0; i < m_iNumChannels; ++i)
    {
        CChannel* pChannel = CChannel::LoadCreate(is);
        m_Channels.push_back(pChannel);
    }

    return S_OK;
}

CAnimation* CAnimation::Create(const aiAnimation* pAIAnimation, const CModel* pModel, vector<_uint>& CurrentKeyFrameIndices)
{
    CAnimation* pInstance = new CAnimation();
    if(FAILED(pInstance->Initialize(pAIAnimation, pModel, CurrentKeyFrameIndices)))   
    {
        MSG_BOX("Failed to Created : Animation");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CAnimation* CAnimation::LoadCreate(istream& is, vector<_uint>* _CurrentKeyFrameIndices)
{
    CAnimation* pInstance = new CAnimation();
    if (FAILED(pInstance->Load_Anim(is, *_CurrentKeyFrameIndices)))
    {
        MSG_BOX("Failed To LoadCreated : CAnimation");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CAnimation::Free()
{
    __super::Free();

    for (auto& pChannels : m_Channels)
        Safe_Release(pChannels);

    m_Channels.clear();
}

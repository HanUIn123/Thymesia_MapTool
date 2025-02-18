#include "Channel.h"
#include "Model.h"
#include "Bone.h"

CChannel::CChannel()
{
}

HRESULT CChannel::Initialize(const aiNodeAnim* pAIChannel, const CModel* pModel)
{
    strcpy_s(m_szName, pAIChannel->mNodeName.data);

    /* 이 채널(뼈)의 시간에 맞는 상태(행렬)을 만들어내야하는 작업을 추후 수행해야하고 */
    /* 상태행렬을 같은 이름을 가진 뼈의 m_TransformationMatrix로 전달 갱신해줘야 하기 때문에 */

    m_iBoneIndex = pModel->Get_BoneIndex(m_szName); 

    m_iNumKeyframes = max(pAIChannel->mNumScalingKeys, pAIChannel->mNumRotationKeys);
    m_iNumKeyframes = max(m_iNumKeyframes, pAIChannel->mNumPositionKeys);
  

    _float3  vScale       = {};
    _float4  vRotation    = {};
    _float3  vTranslation = {};


    for(size_t i=0; i< m_iNumKeyframes; i++)
    {
        KEYFRAME   KeyFrame{};

        if(pAIChannel->mNumScalingKeys > i)
        {
            memcpy(&vScale, &pAIChannel->mScalingKeys[i].mValue, sizeof(_float3));
            KeyFrame.fTrackPosition = pAIChannel->mScalingKeys[i].mTime;
        }
        
        if(pAIChannel->mNumRotationKeys > i)
        {
            vRotation.x = pAIChannel->mRotationKeys[i].mValue.x;
            vRotation.y = pAIChannel->mRotationKeys[i].mValue.y;
            vRotation.z = pAIChannel->mRotationKeys[i].mValue.z;
            vRotation.w = pAIChannel->mRotationKeys[i].mValue.w;

            KeyFrame.fTrackPosition = pAIChannel->mRotationKeys[i].mTime;
        }

        if(pAIChannel->mNumPositionKeys > i)
        {
            memcpy(&vTranslation, &pAIChannel->mPositionKeys[i].mValue, sizeof(_float3));
            KeyFrame.fTrackPosition = pAIChannel->mPositionKeys[i].mTime;
        }

        KeyFrame.vScale = vScale; 
        KeyFrame.vRotation = vRotation;    
        KeyFrame.vTranslation = vTranslation;

        m_Keyframes.push_back(KeyFrame);    
    }

    /* 루트 모션 관련 추가 코드*/
    XMStoreFloat4x4(&m_WorldTranslation, XMMatrixIdentity()); // 단위 행렬로 초기화
   
    return S_OK;
}


void CChannel::Update_TransformationMatrix(_float fCurrentTrackPosition, _uint* pCurrentKeyFrameIndex, const vector<class CBone*>& Bones)
{
 
     if (0.f == fCurrentTrackPosition)
         *pCurrentKeyFrameIndex = 0;

     /* 현재 재생위치에 맞는 상태를 구한다. */
     _vector   vScale, vRotation, vTranslation;

     /* 현재 재생위치가 마지막 키프레임의 위치를 넘어가면 마지막 키프레임의 상태를 넣어준다*/
     KEYFRAME     LastKeyFrame = m_Keyframes.back();

     if (fCurrentTrackPosition >= LastKeyFrame.fTrackPosition)
     {
         vScale = XMLoadFloat3(&LastKeyFrame.vScale);
         vRotation = XMLoadFloat4(&LastKeyFrame.vRotation);
         vTranslation = XMVectorSetW(XMLoadFloat3(&LastKeyFrame.vTranslation), 1.f);
     }

     /* 나머지 모든 상태 : 좌, 우 키프레임 사이의 상태를 보간을 통해 구해내야한다. */
     else
     {
         /* while을 넣어준 이유는 프레임 드랍때문에 현재 프레임이 업데이트가 안되고 한꺼번에 진행될때 */
         /* 모델의 크기에 영향을 주므로 */
         while (fCurrentTrackPosition >= m_Keyframes[*pCurrentKeyFrameIndex + 1].fTrackPosition)
             ++*pCurrentKeyFrameIndex;

         _float  fRatio = (fCurrentTrackPosition - m_Keyframes[*pCurrentKeyFrameIndex].fTrackPosition) /
             (m_Keyframes[*pCurrentKeyFrameIndex + 1].fTrackPosition - m_Keyframes[*pCurrentKeyFrameIndex].fTrackPosition);


         vScale = XMVectorLerp(XMLoadFloat3(&m_Keyframes[*pCurrentKeyFrameIndex].vScale), XMLoadFloat3(&m_Keyframes[*pCurrentKeyFrameIndex + 1].vScale), fRatio);
         vRotation = XMQuaternionSlerp(XMLoadFloat4(&m_Keyframes[*pCurrentKeyFrameIndex].vRotation), XMLoadFloat4(&m_Keyframes[*pCurrentKeyFrameIndex + 1].vRotation), fRatio);
         vTranslation = XMVectorSetW(XMVectorLerp(XMLoadFloat3(&m_Keyframes[*pCurrentKeyFrameIndex].vTranslation), XMLoadFloat3(&m_Keyframes[*pCurrentKeyFrameIndex + 1].vTranslation), fRatio), 1.f);

     }


     //if(m_iBoneIndex ==2)
     //{
     //    
     //    _matrix Translation = XMMatrixIdentity();
     //    Translation.r[3] = vTranslation;   
     //
     //    XMStoreFloat4x4(&m_WorldTranslation, Translation); 
     //
     //    /* 근데 이걸 combined 매트릭스 즉 부모에거에 곱해줘야하는데*/
     //
     //    vTranslation = { 0.f,0.f,0.f,1.f };    // 이거 해주니깐 잘되네  
     //    // 그럼 이거의 combined 행렬을 따로 보관해야할거같은데 
     //
     //
     //    
     //}

     
     _matrix TransformationMatrix = XMMatrixAffineTransformation(vScale, XMVectorSet(0.f, 0.f, 0.f, 1.f), vRotation, vTranslation);
     Bones[m_iBoneIndex]->Set_TransformationMatrix(TransformationMatrix);

    /* 루트 모션 적용 */
    /* 여기서 bone 의 translation을 그러면 월드에도 넣어줘야 겠네요 ㅇㅇ... */
    //XMStoreFloat4x4(&m_ForWorldMatrix, TransformationMatrix);   // 그러기 위해서 저장. 
    //if(m_iBoneIndex == 3)  // 최상위 부모 뼈의 이동만 저장하면될듯 어차피 그럼 다 영향받으니깐 
    //{
    //    _matrix ForWorldMatrix = XMLoadFloat4x4(&m_WorldTranslation);
    //    ForWorldMatrix.r[3] = vTranslation; 
    //   
    //    XMStoreFloat4x4(&m_WorldTranslation, ForWorldMatrix);   
    //}
      

}

void CChannel::Lerp_TransformationMatrix(const vector<class CBone*>& Bones, CChannel* pNextChannel, _float LerpTime, _float LerpTimeAcc, _uint* pCurrentKeyFrameIndex)
{
    /* 11월 29일 여기서 부터 다시 하기 */
    _vector   vScale, vRotation, vTranslation;

    _float		fRatio = LerpTimeAcc / LerpTime;        
   
    /* 선형보간*/
    /* 여기서 작업해줘야할듯함 */
    /* 현재 위치의 애니메이션 가져와줘야할듯*/

      // 현재 위치와 다음 위치의 차이 계산
   
    vScale       = XMVectorLerp(XMLoadFloat3(&m_Keyframes[*pCurrentKeyFrameIndex].vScale), XMLoadFloat3(&pNextChannel->m_Keyframes.front().vScale), fRatio);
    vRotation    = XMQuaternionSlerp(XMLoadFloat4(&m_Keyframes[*pCurrentKeyFrameIndex].vRotation), XMLoadFloat4(&pNextChannel->m_Keyframes.front().vRotation), fRatio);    
    vTranslation = XMVectorLerp(XMLoadFloat3(&m_Keyframes[*pCurrentKeyFrameIndex].vTranslation), XMLoadFloat3(&pNextChannel->m_Keyframes.front().vTranslation), fRatio);        
    vTranslation = XMVectorSetW(vTranslation, 1.f); 


    //if(m_iBoneIndex==2)
    //{
    //    vTranslation = { 0.f,0.f,0.f,1.f }; 
    //
    //}

    _matrix  TransformationMatrix = XMMatrixAffineTransformation(vScale, XMVectorSet(0.f, 0.f, 0.f, 1.f), vRotation, vTranslation);
    Bones[m_iBoneIndex]->Set_TransformationMatrix(TransformationMatrix);


}

void CChannel::Reset_TransformationMatrix(const vector<class CBone*>& Bones, _uint* pCurrentKeyFrameIndex)
{
    *pCurrentKeyFrameIndex = 0;

    KEYFRAME FirstKeyFrame = m_Keyframes.front();   

    _vector vScale, vRotation, vTranslation;    
    
    vScale = XMLoadFloat3(&FirstKeyFrame.vScale);
    vRotation = XMLoadFloat4(&FirstKeyFrame.vRotation);
    vTranslation = XMVectorSetW(XMLoadFloat3(&FirstKeyFrame.vTranslation), 1.f);

    _matrix  TransformationMatrix = XMMatrixAffineTransformation(vScale, XMVectorSet(0.f, 0.f, 0.f, 1.f), vRotation, vTranslation);
    
    Bones[m_iBoneIndex]->Set_TransformationMatrix(TransformationMatrix);

}

HRESULT CChannel::Save_Channel(ostream& os)
{
    os.write(m_szName, sizeof(_char) * MAX_PATH);
    os.write((char*)&m_iBoneIndex, sizeof(_uint));
    os.write((char*)&m_iNumKeyframes, sizeof(_uint));
    writeVectorToBinary(m_Keyframes, os);

    return S_OK;

}

HRESULT CChannel::Load_Channel(istream& is)
{
    is.read(m_szName, sizeof(_char) * MAX_PATH);
    is.read((char*)&m_iBoneIndex, sizeof(_uint));
    is.read((char*)&m_iNumKeyframes, sizeof(_uint));
    readVectorFromBinary(is, m_Keyframes);

    return S_OK;
}

CChannel* CChannel::LoadCreate(istream& is)
{
    CChannel* pInstance = new CChannel();
    if (FAILED(pInstance->Load_Channel(is)))
    {
        MSG_BOX("Failed To LoadCreate : CChannel");
        Safe_Release(pInstance);
    }
    return pInstance;
}

CChannel* CChannel::Create(const aiNodeAnim* pAIChannel, const CModel* pModel)
{
    
    CChannel* pInstance = new CChannel();

    if(FAILED(pInstance->Initialize(pAIChannel,pModel)))
    {
        MSG_BOX("Failed to Created : Channel");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CChannel::Free()
{
    __super::Free();
}

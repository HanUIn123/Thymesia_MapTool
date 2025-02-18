#pragma once

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CSoundMgr : public CBase
{
private:
	CSoundMgr();
	virtual ~CSoundMgr() = default;	
private:
    // 사운드 리소스 정보를 갖는 객체 
    map<const _tchar*, FMOD::Sound*> m_mapSound;    

    // FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
    FMOD::Channel* m_pChannelArr[MAXCHANNEL];
    // 사운드 ,채널 객체 및 장치를 관리하는 객체 
    FMOD::System* m_pSystem = { nullptr };
    _tchar* m_CurBGM;

public:
	HRESULT Initialize();	    
	void Release();	    


public:
    void Play_Sound(const _tchar* pSoundKey, CHANNELID eID, float fVolume); 
    void PlayBGM(const _tchar* pSoundKey, float fVolume);
    void StopSound(CHANNELID eID);
    void StopAll();
    void SetChannelVolume(CHANNELID eID, float fVolume);
    bool CheckSoundPlaying(CHANNELID eID);
    _tchar* Get_CurBGM() { return m_CurBGM; };

private:
    void LoadSoundFile();

private:
    bool m_isPlaying = { false };

public:
    static CSoundMgr* Create(); 
    virtual void Free();

};

END

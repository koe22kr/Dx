#pragma once
#include "CAStd.h"

#include "CASound.h" 

#define MAX_SOUND 32
//FMOD/inc fmod.hpp      ,   FMOD/lib/x64   fmod_vc.lib
//fmod.dll 현재폴더 or 실행파일 위치[디벅 해서 나온 실행파일 위치]



class CASoundMgr : public CASingleton<CASoundMgr>
 {
    friend class CASingleton<CASoundMgr>;
    //사전식 컨테이너
public:
    float           m_fVolume = 1.0f;// 마스터 볼륨
    map<string, CASound*> m_SoundList; //CASound 클래스 안에서는 메모리 할당 관련 아무것도 하지 않는다.
    FMOD::System*   m_pSystem;
    FMOD::Channel*  m_pBGM_Channel;//게임의 BGM 단일 가정, SE는 지역체널(ㅋ) 사용
 public:

     int Load(const char* csound_file_name); //생성시 m_SoundList에 insert, CASound 동적할당, 키값=파일이름 ,실패시-1 성공시 1;
     
     void PlayBGM(const char* fime_name_key);
     void PlaySE(const char* fime_name_key);
     void Paused();
     void Stop();
     void Volume(float fVolume_stap = 1.0f, bool Vol_Up = true);
     //void VolumeSE(int ise_channel, float fVolume = 1.0f, bool Vol_Up = true);

    

    
 public:

     bool Init();
     bool Frame();
     bool Render();
     bool Release();//맵의 second 동적할당 해제, 해당 맵 erase  -> if(begin==end)

     
        
        
private:
    CASoundMgr();
public:
    ~CASoundMgr();
};

#define I_SoundMgr CASoundMgr::GetInstance()


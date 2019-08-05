#pragma once
#include "CAStd.h"

#include "CASound.h" 

#define MAX_SOUND 32
//FMOD/inc fmod.hpp      ,   FMOD/lib/x64   fmod_vc.lib
//fmod.dll �������� or �������� ��ġ[��� �ؼ� ���� �������� ��ġ]



class CASoundMgr : public CASingleton<CASoundMgr>
 {
    friend class CASingleton<CASoundMgr>;
    //������ �����̳�
public:
    float           m_fVolume = 1.0f;// ������ ����
    map<string, CASound*> m_SoundList; //CASound Ŭ���� �ȿ����� �޸� �Ҵ� ���� �ƹ��͵� ���� �ʴ´�.
    FMOD::System*   m_pSystem;
    FMOD::Channel*  m_pBGM_Channel;//������ BGM ���� ����, SE�� ����ü��(��) ���
 public:

     int Load(const char* csound_file_name); //������ m_SoundList�� insert, CASound �����Ҵ�, Ű��=�����̸� ,���н�-1 ������ 1;
     
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
     bool Release();//���� second �����Ҵ� ����, �ش� �� erase  -> if(begin==end)

     
        
        
private:
    CASoundMgr();
public:
    ~CASoundMgr();
};

#define I_SoundMgr CASoundMgr::GetInstance()


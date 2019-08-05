#include "CASoundMgr.h"


//시스템 사운드 체널 인터페이스만 사용
int CASoundMgr::Load(const char* csound_file_name)
{
    std::string strpath ="../../data/sound/";
    strpath += csound_file_name;
    char cpath[256];
    strcpy(cpath, strpath.c_str());
    
    CASound* newSound = new CASound;
    m_SoundList.insert(std::make_pair(csound_file_name, newSound));
    FMOD_RESULT ret = m_pSystem->createSound(cpath, FMOD_LOOP_OFF, 0,
        &newSound->m_pSound);
    if (ret != 0)
    {
        //  에러 메세지 호출 추가  요망
        return -1;
        delete newSound;
    }
    return 1;
}

void CASoundMgr::PlayBGM(const char* fime_name_key)
{
    bool isplaying;
    m_pBGM_Channel->isPlaying(&isplaying);
    if (isplaying) Stop();
    
    m_pBGM_Channel->setVolume(m_fVolume);
    m_pSystem->playSound(m_SoundList.find(fime_name_key)->second->m_pSound, 0, false, &m_pBGM_Channel);
    
    m_pBGM_Channel->setMode(FMOD_LOOP_NORMAL);
}

void CASoundMgr::PlaySE(const char* fime_name_key)
{
    FMOD::Channel* SE_Channel=nullptr;

    SE_Channel->setVolume(m_fVolume);
    m_pSystem->playSound(m_SoundList.find(fime_name_key)->second->m_pSound, 0, false, &SE_Channel);
   
    SE_Channel->setMode(FMOD_LOOP_OFF);
}

void CASoundMgr::Paused()
{
    bool Pause_flag;
    m_pBGM_Channel->getPaused(&Pause_flag);
    m_pBGM_Channel->setPaused(!Pause_flag);
}

void CASoundMgr::Stop()
{
    m_pBGM_Channel->stop();
}

void CASoundMgr::Volume(float fVolume_stap, bool Vol_Up)
{
    if (Vol_Up)
    {
        m_fVolume += fVolume_stap * g_fSecondPerFrame;
        m_fVolume = min(m_fVolume, 1.0f);
    }
    else
    {
        m_fVolume -= fVolume_stap * g_fSecondPerFrame;
        m_fVolume = max(m_fVolume, 0.0f);
    }
    
    m_pBGM_Channel->setVolume(m_fVolume);
}


bool CASoundMgr::Init()
{
    FMOD::System_Create(&m_pSystem);
    m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
    return true;
}
bool CASoundMgr::Frame()
{
    m_pSystem->update();
    //재생시간 ~/~;
    /*    이건 재생시간 표시용.
    UINT length = 0;
    UINT cur = 0;
    FMOD::Sound* currentsound;
    m_pBGM_Channel->getCurrentSound(&currentsound);
    currentsound->getLength(&length, FMOD_TIMEUNIT_MS);
    //m_pBGM_Sound[isound]->getLength(&length, FMOD_TIMEUNIT_MS);
    m_pBGM_Channel->getPosition(&cur, FMOD_TIMEUNIT_MS);
    static float fTimer;
    fTimer += g_fSeoundPerFrame;

    if(fTimer>1)
    {
        fTimer -= 1.0f;
        char szBuffer[256] = { 0 };
        sprintf_s(szBuffer,sizeof(szBuffer), "[%02d:%02d:%02d / %02d:%02d:%02d]",
            cur / 1000 / 60,    cur / 1000,     cur / 10,
            length / 1000 / 60, length / 1000, length / 10);
        OutputDebugStringA(szBuffer);
    }*/
    return true;
}
bool CASoundMgr::Render()
{
    return true;
}
bool CASoundMgr::Release()
{
    map<string, CASound*>::iterator ITOR;
    ITOR = m_SoundList.begin();
    while (ITOR != m_SoundList.end())
    {
        ITOR->second->m_pSound->release();
        //delete ITOR->second->m_pSound;
       ITOR = m_SoundList.erase(ITOR);
    }

    m_pSystem->close();
    m_pSystem->release();
    return true;
 
}



CASoundMgr::CASoundMgr()
{
    
}


CASoundMgr::~CASoundMgr()
{

}




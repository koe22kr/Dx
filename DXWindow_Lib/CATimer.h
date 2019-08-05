#pragma once
#include "CAStd.h"

class CATimer :public CASingleton<CATimer>
{//
    friend CASingleton<CATimer>;
public:
    float m_fSecondPerFrame; //1프레임 경과시간
    float m_fAccumulation; //실행 경과시간
    int m_iFPS; //초당 프레임수 카운터      초깃값 생성자에서 넣기.
    DWORD m_dwBeforeTick;
    float m_fFrameTime;
    DWORD m_dwFrameCount;
    TCHAR m_csBuffer[MAX_PATH];
    
public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

public:
    CATimer();
    virtual ~CATimer();
};


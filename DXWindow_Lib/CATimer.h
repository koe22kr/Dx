#pragma once
#include "CAStd.h"

class CATimer :public CASingleton<CATimer>
{//
    friend CASingleton<CATimer>;
public:
    float m_fSecondPerFrame; //1������ ����ð�
    float m_fAccumulation; //���� ����ð�
    int m_iFPS; //�ʴ� �����Ӽ� ī����      �ʱ갪 �����ڿ��� �ֱ�.
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


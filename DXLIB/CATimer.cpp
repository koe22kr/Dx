#include "CATimer.h"

float g_fSecondPerFrame = 0.0f;  //프레임당 sec
float g_fGameTimer = 0.0f;    //총시간

bool CATimer::Init()
{
    //__imp_timeGetTime 외부 기호 : winmm.lib
    m_dwBeforeTick = timeGetTime(); //
    return true;

};

bool CATimer::Frame()                       //init 후 frame 연속적으로 사용될듯. 아니라면 frame에서 init 호출해야 한다.
{
    DWORD m_dwCurrentTick = timeGetTime();
    DWORD dwElapseTick = m_dwCurrentTick - m_dwBeforeTick;
    m_fSecondPerFrame = dwElapseTick / 1000.0f;
    m_fAccumulation += m_fSecondPerFrame;
    m_fFrameTime += m_fSecondPerFrame;

    g_fSecondPerFrame = m_fSecondPerFrame;
    g_fGameTimer = m_fAccumulation;

    if (m_fFrameTime >= 1.0f)
    {
        m_iFPS = m_dwFrameCount;
        m_dwFrameCount = 0;
        m_fFrameTime -= 1.0f;

        _stprintf_s(m_csBuffer, _T("Timer:[%10.4f], FPS[%d]"),
            m_fAccumulation, m_iFPS);
      //  OutputDebugString(m_csBuffer);
    }
    m_dwFrameCount++;

    m_dwBeforeTick = m_dwCurrentTick;
    return true;
}
bool CATimer::Render()
{
    
    return true;

}
bool CATimer::Release()
{
    return true;
}

CATimer::CATimer()
{
    m_fSecondPerFrame = 0.0f;   //1프레임 경과시간
    m_fAccumulation = 0.0f;     //실행 경과시간 
    m_iFPS = 0;                 //1초 마다의 프레임 카운트
    m_fFrameTime = 0.0f;        //
    m_dwFrameCount = 0;         //매 프레임당 누적되는 카운트 누적되는 카운트
}


CATimer::~CATimer()
{
}

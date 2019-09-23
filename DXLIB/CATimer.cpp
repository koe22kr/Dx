#include "CATimer.h"

float g_fSecondPerFrame = 0.0f;  //�����Ӵ� sec
float g_fGameTimer = 0.0f;    //�ѽð�

bool CATimer::Init()
{
    //__imp_timeGetTime �ܺ� ��ȣ : winmm.lib
    m_dwBeforeTick = timeGetTime(); //
    return true;

};

bool CATimer::Frame()                       //init �� frame ���������� ���ɵ�. �ƴ϶�� frame���� init ȣ���ؾ� �Ѵ�.
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
    m_fSecondPerFrame = 0.0f;   //1������ ����ð�
    m_fAccumulation = 0.0f;     //���� ����ð� 
    m_iFPS = 0;                 //1�� ������ ������ ī��Ʈ
    m_fFrameTime = 0.0f;        //
    m_dwFrameCount = 0;         //�� �����Ӵ� �����Ǵ� ī��Ʈ �����Ǵ� ī��Ʈ
}


CATimer::~CATimer()
{
}

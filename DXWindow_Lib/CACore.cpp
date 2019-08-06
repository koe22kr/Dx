#include "CACore.h"

bool CACore::Init()
{
    return true;
}

bool CACore::Frame()
{
    return true;
}

bool CACore::Render()
{
    return true;
}


bool CACore::Release()
{
    return true;
}

bool CACore::CACoreInit()
{


    m_Device.Init();
    m_Timer.Init();
    I_Input.Init();
    I_SoundMgr.Init();
    return Init();
}
bool CACore::CACoreFrame()
{
    m_Device.Frame();
    m_Timer.Frame();
    I_Input.Frame();
    I_SoundMgr.Frame();
    return Frame();
    
}
bool CACore::CACoreRender()
{
    m_Device.Pre_Render();

    Render();

    m_Device.Render();
    m_Timer.Render();

    
    return Render();
    return true;
}
bool CACore::CACoreRelease()
{
    m_Device.Release();
    m_Timer.Release();
    I_Input.Release();
    I_SoundMgr.Release();
    return Release();
}
bool CACore::Run()
{
    CACoreInit();                                     
    MSG msg = { 0 };
    // WM_QUIT -> FALSE
    // �޼��� ť���� �ϳ��ϳ��� �����´�.
    //while (GetMessage(&msg, nullptr, 0, 0))
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // �޼��� ����
            DispatchMessage(&msg);	// �޼��� ���ν��� ����	
            MessageProc(msg);
        }
        else
        {
            // ���ӷ���
            CACoreFrame(); // ���Ӱ��
            CACoreRender();// ���ӵ�ο�
            //Sleep(1); //1�̸��� ���°ǵ� �ʿ��Ѱ�?
        }
    }
    CACoreRelease(); // ���� ���� 
    
    return true;        //��������
}

void CACore::MessageProc(MSG msg)
{
    I_Input.MouseCheck(msg);
  //  I_MSG.Msg_list.push_back(msg);
}

CACore::CACore()
{
}


CACore::~CACore()
{
}

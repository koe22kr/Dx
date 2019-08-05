#include "CAInput.h"

    //DWORD m_dwKeyState[256];
    //DWORD m_dwMouseState[3];

    //    bool       Init();
    //bool       Frame();
    //bool       Render();
    //bool       Release();
    //DWORD      KeyCheck(DWORD dwKey);
    //LRESULT		MsgProc(MSG msg);
    //DWORD MouseCheck(DWORD dwKey);
    //
    //enum { KEY_FREE, KEY_PUSH, KEY_HOLD, KEY_UP };

DWORD CAInput::KeyCheck(DWORD dwKey)//
{
   SHORT sKey = GetAsyncKeyState(dwKey);
   // enum { KEY_FREE, KEY_PUSH, KEY_HOLD, KEY_UP, MOUSE_DBL_CLICK, MB_UP, MB_DOWN}
       //  1000 0000 0000 0000
   if (sKey & 0x8000) // 
   {
       if (m_dwKeyState[dwKey] == KEY_FREE ||
           m_dwKeyState[dwKey] == KEY_UP)
       {
           m_dwKeyState[dwKey] = KEY_PUSH;
       }
       else
       {

           m_dwKeyState[dwKey] = KEY_HOLD;
       }
   }
   else
   {
       if (m_dwKeyState[dwKey] == KEY_PUSH ||
           m_dwKeyState[dwKey] == KEY_HOLD)
       {
           m_dwKeyState[dwKey] = KEY_UP;
       }
       else
       {
           m_dwKeyState[dwKey] = KEY_FREE;
           
       }
   }
   return m_dwKeyState[dwKey];
}

bool CAInput::Init()
{
    ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
    return true;

}

bool       CAInput::Frame()
{
    GetCursorPos(&m_MousePos);   //ȭ�� ��ũ��. ������ ��ǥ��
    ScreenToClient(g_hWnd, &m_MousePos);  //Ŭ���̾�Ʈ ��ǥ��� ����

    for (int iButton = 0; iButton < 3; iButton++)
    {
        if (m_dwBeforeMouseState[iButton] == KEY_PUSH)
        {
            if (m_dwMouseState[iButton] == KEY_PUSH)
            {
                m_dwMouseState[iButton] = KEY_HOLD;
            }
        }
        m_dwBeforeMouseState[iButton] = m_dwMouseState[iButton];
    }
    return true;

}
bool       CAInput::Render()
{
    return true;

}
bool       CAInput::Release()
{
    return true;

}
MSG CAInput::Getmessage(MSG dwkey)
{

    return dwkey;
}
LRESULT CAInput::MouseCheck(MSG dwmouse)
{
    {
        switch (dwmouse.message)            //�޼����� WParam ���� ���°� �´ٰ� �� MK_LBUTTON
        {
        //LB
        case WM_LBUTTONDOWN:
        {
            if (dwmouse.wParam & MK_LBUTTON) // ����������
            {
                m_dwMouseState[0] = KEY_HOLD;
            }
            else
                m_dwMouseState[0] = KEY_PUSH;
        }break;

        case WM_LBUTTONUP:
        {
            m_dwMouseState[0] = KEY_UP;
        }break;

        case WM_LBUTTONDBLCLK:
        {
            m_dwMouseState[0] = MOUSE_DBL_CLICK;
        }break;

        //MB
        case WM_MBUTTONDOWN:
        {
            if (dwmouse.wParam & MK_MBUTTON) // ����������
            {
                m_dwMouseState[1] = KEY_HOLD;
            }
            else
                m_dwMouseState[1] = KEY_PUSH;
        }break;

        case WM_MBUTTONUP:
        {
            m_dwMouseState[1] = KEY_UP;
        }break;


        //RB
        case WM_RBUTTONDOWN:
        {
            if (dwmouse.wParam & MK_MBUTTON) // ����������
            {
                m_dwMouseState[2] = KEY_HOLD;
            }
            else
                m_dwMouseState[2] = KEY_PUSH;
        }break;

        case WM_RBUTTONUP:
        {
            m_dwMouseState[2] = KEY_UP;
        }break;

        case WM_RBUTTONDBLCLK:
        {
            m_dwMouseState[2] = MOUSE_DBL_CLICK;
        }

        }
    }
    return 1;
}




CAInput::CAInput() 
{

}


CAInput::~CAInput()
{

}

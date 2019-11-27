#include "CAInput.h"
#include "CADx_Std.h"

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
    ZeroMemory(m_dwMouseState, sizeof(BYTE) * 3);
    ZeroMemory(m_dwBeforeMouseState, sizeof(BYTE) * 3);
    return true;

}


bool   CAInput::InitDirectInput()
{
    HRESULT hr = S_OK;
    if (FAILED(hr = DirectInput8Create(g_hInstance,
        DIRECTINPUT_VERSION,
        IID_IDirectInput8,
        (void**)&m_pDI, NULL)))
    {
        return false;
    }
    if (FAILED(hr = m_pDI->CreateDevice(GUID_SysKeyboard,
        &m_pKeyDevice, NULL)))
    {
        return false;
    }
    // 장치별 반환 데이터 설정
    m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
    // 장치별 독점 및 비독점 설정(협조레벨)
    if (FAILED(hr = m_pKeyDevice->SetCooperativeLevel(
        m_hWnd,
        DISCL_NONEXCLUSIVE |
        DISCL_FOREGROUND |
        DISCL_NOWINKEY)))
    {
        return false;
    }

    while (m_pKeyDevice->Acquire() == DIERR_INPUTLOST);


    if (FAILED(hr = m_pDI->CreateDevice(GUID_SysMouse,
        &m_pMouseDevice, NULL)))
    {
        return false;
    }
    m_pMouseDevice->SetDataFormat(&c_dfDIMouse);

    if (FAILED(hr = m_pMouseDevice->SetCooperativeLevel(
        m_hWnd,
        DISCL_NONEXCLUSIVE |
        DISCL_FOREGROUND)))
    {
        return true;
    }
    while (m_pMouseDevice->Acquire() == DIERR_INPUTLOST);
    return hr;
}

bool       CAInput::Frame()
{
    GetCursorPos(&m_MousePos);   //화면 스크린. 위도우 좌표계
    ScreenToClient(g_hWnd, &m_MousePos);  //클라이언트 좌표계로 변경

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

   // HRESULT hr;
   // if (m_pMouseDevice == NULL || m_pKeyDevice == NULL) return false;
   //
   // if (FAILED(hr = m_pKeyDevice->GetDeviceState(256, m_dwKeyState)))
   // {
   //     while (m_pKeyDevice->Acquire() == DIERR_INPUTLOST);
   //     //return true;
   // }
   //
   // if (FAILED(hr = m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_DIMouseState)))
   // {
   //     while (m_pMouseDevice->Acquire() == DIERR_INPUTLOST);
   //     //return true;
   // }
   // for (int iButton = 0; iButton < 3; iButton++)
   // {
   //     m_dwBeforeMouseState[iButton] = m_DIMouseState.rgbButtons[iButton];
   // }

    return true;


}
bool       CAInput::Render()
{
    return true;

}
bool       CAInput::Release()
{
    if (m_pKeyDevice)
    {
        m_pKeyDevice->Release();
    }
    if (m_pMouseDevice)
    {
        m_pMouseDevice->Release();
    }
    if (m_pDI)
    {
        m_pDI->Release();
    }
    return true;

}
MSG CAInput::Getmessage(MSG dwkey)
{

    return dwkey;
}
LRESULT CAInput::MouseCheck(MSG dwmouse)
{
    {
        switch (dwmouse.message)            //메세지의 WParam 으로 상태가 온다고 함 MK_LBUTTON
        {
        //LB
        case WM_LBUTTONDOWN:
        {
            if (m_dwBeforeMouseState[0]== KEY_PUSH) // 눌러져잇음
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
            if (m_dwBeforeMouseState[1] == KEY_PUSH) // 눌러져잇음
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
            if (m_dwBeforeMouseState[2] == KEY_PUSH) // 눌러져잇음
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

void CAInput::DeviceAcquire()
{
    if (m_pKeyDevice)
        m_pKeyDevice->Acquire();
    if (m_pMouseDevice)
        m_pMouseDevice->Acquire();
}

void CAInput::DeviceUnacquire()
{
    if (m_pKeyDevice)
        m_pKeyDevice->Unacquire();
    if (m_pMouseDevice)
        m_pMouseDevice->Unacquire();
}


CAInput::CAInput() 
{
    m_pMouseDevice = NULL;
    m_pKeyDevice = NULL;
}


CAInput::~CAInput()
{

}

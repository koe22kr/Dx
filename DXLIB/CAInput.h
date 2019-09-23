#pragma once
#include "CAStd.h"



enum { KEY_FREE, KEY_PUSH, KEY_HOLD, KEY_UP, MOUSE_DBL_CLICK, MB_UP, MB_DOWN };

class CAInput :public CASingleton<CAInput>
{
    friend CASingleton<CAInput>;/// ���� �� �߰� �Ǵ���?. �ʿ� ������ ������.
public:
    HWND   m_hWnd;

    LPDIRECTINPUT8		m_pDI;
    LPDIRECTINPUTDEVICE8  m_pKeyDevice; // Ű����
    LPDIRECTINPUTDEVICE8  m_pMouseDevice;// ���콺
    
public:
    DWORD m_dwKeyState[256];
    DWORD m_dwKeyState_Old[256];
    DIMOUSESTATE		  m_DIMouseState;


    DWORD m_dwBeforeMouseState[3];
    DWORD m_dwMouseState[3];
    POINT m_MousePos;
public:
    int a;
    bool       Init() ;
    bool       Frame() ;
    bool       Render() ;
    bool       Release() ;
    DWORD      KeyCheck(DWORD dwKey);
    MSG Getmessage(MSG dwkey);
    bool   InitDirectInput();
    void DeviceUnacquire();
    void DeviceAcquire();

    LRESULT MouseCheck(MSG dwKey);

private:
    CAInput();
public:
    virtual ~CAInput();
};

#define I_Input CAInput::GetInstance()
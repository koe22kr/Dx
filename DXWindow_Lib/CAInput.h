#pragma once
#include "CAStd.h"

enum { KEY_FREE, KEY_PUSH, KEY_HOLD, KEY_UP, MOUSE_DBL_CLICK, MB_UP, MB_DOWN };

class CAInput :public CASingleton<CAInput>
{
    friend CASingleton<CAInput>;/// 뭔가 더 추가 되던가?. 필요 없을것 같은데.

    
public:
    DWORD m_dwKeyState[256];
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

    LRESULT MouseCheck(MSG dwKey);

private:
    CAInput();
public:
    virtual ~CAInput();
};

#define I_Input CAInput::GetInstance()
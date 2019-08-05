#pragma once
#include "CAStd.h"
class CAWindow
{
public:
    virtual bool Init() { return true; };
    virtual bool Frame() { return true; };
    virtual bool Render() { return true; };
    virtual bool Release() { return true; };
    
public:
    HINSTANCE m_hInstance;
    HWND      m_hWnd;
    RECT      m_Src_rtClient;
    RECT      m_Src_rtWindow;
    DWORD     m_dwStyle; //디버깅 함하자.
    bool      InitWindow(HINSTANCE hInstance,
                           int iX = 0, int iY = 0, 
                           int iWidth = 800, int iHeight = 600);
    bool      MyRegisterClass();
    void      CenterWindow();

    virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


public:
    CAWindow();
    virtual ~CAWindow();
};


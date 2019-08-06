#pragma once
#include "CAWindow.h"
#include "CATimer.h"
#include "CAInput.h"
#include "CASoundMgr.h"
#include "CAStd.h"
#include "CAMessageList.h"
#include "Device.h"

class CACore :public CAWindow                 
{
public:
    CATimer m_Timer;   
    Device m_Device;
  //  CAInput m_Input;
public:
    virtual bool Init();
    virtual bool Frame();
    virtual bool Render();
    virtual bool Release();
    
public:

    bool CACoreInit();
    bool CACoreFrame();
    bool CACoreRender();
    bool CACoreRelease();
  
    bool Run();

    void MessageProc(MSG msg);
    virtual LRESULT MouseProc(MSG msg) { return true; };
    virtual LRESULT KeyProc(MSG msg) { return true; };
public:
    CACore();
    virtual ~CACore();
};

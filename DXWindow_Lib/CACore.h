#pragma once
#include "CAStd.h"
#include "CAWindow.h"
#include "CATimer.h"
#include "CAInput.h"
#include "CASoundMgr.h"
#include "CAMessageList.h"
#include "CADevice_Helper.h"
#include "CADx_Text.h"
#include "CADx_State.h"
#include "CAShape.h"
class CACore :public CAWindow                 
{
#if defined _DEBUG || DEBUG
    bool RS_FLAG = 1;
    bool AB_FLAG = 1;
    bool SS_FLAG = 1;

    DX::DXText m_Debug_Text;//data
    DX::CADx_Text Dx_Write;//class
    void Debug_Init();
    void Debug_Frame();
    void Debug_Render();
    void Debug_Release();
    void Refresh_m_Debug_Text();
    DX::CAShape_Line m_Debug_Shape;

#endif // DEBUG

public:
    CATimer m_Timer;   
    CADevice m_Device;
  //  CAInput m_Input;
public:
    virtual bool Init();
    virtual bool Frame();
    virtual bool Render();
    virtual bool Release();
public:
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

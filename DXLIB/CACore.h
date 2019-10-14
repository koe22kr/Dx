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
#include "CADx_Shape.h"
#include "TBackViewCamera.h"
#include "TModelViewCamera.h"
#include "CADx_Map.h"
#include "CADx_Light.h"

class CACore :public CAWindow                 
{
#if defined _DEBUG || DEBUG
    UINT RS_COUNT = 2;
    bool AB_FLAG = 1;
    bool SS_FLAG = 1;

    DX::DXText m_Debug_Text;//data
    DX::CADx_Text Dx_Write;//class
    void Debug_Init();
    void Debug_Frame();
    void Debug_Render();
    void Debug_Release();
    void Refresh_m_Debug_Text();
    DX::CADx_Shape_Line m_Debug_Shape;

#endif // DEBUG

public:
    CADx_Light m_DiffuseLight;

    DX::CADx_HeightMap m_Heightmap;
    CATimer m_Timer;   
    CADevice m_Device;
    DX::TBackViewCamera m_Default_Cam;
    static DX::TCamera* m_pMain_Cam;
   // DX::Sky Sky_box;


  //  CAInput m_Input;
public:
    virtual bool Init();
    virtual bool Frame();
    bool Pre_Render();
    virtual bool Render();
    bool Post_Render();
    virtual bool Release();
public:
public:

    bool CACoreInit();
    bool CACoreFrame();
    bool CACoreRender();
    bool CACoreRelease();
  
    bool Run();
    virtual void Msg_Proc(MSG msg);

    LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void MessageProc(MSG msg);
    virtual LRESULT MouseProc(MSG msg) { return true; };
    virtual LRESULT KeyProc(MSG msg) { return true; };
public:
    CACore();
    virtual ~CACore();
};

#include "CACore.h"



#if defined _DEBUG || DEBUG
void CACore::Debug_Init()
{
    Dx_Write.Init_Once(m_Device.m_pSwap_Chain);
    Dx_Write.Create_Fresh_Resource();
    m_Debug_Shape.Create_Debug_Coordinate();

}
void CACore::Debug_Frame()
{
    Dx_Write.Set_Text(m_Debug_Text, m_Timer.m_csBuffer);

    if (I_Input.KeyCheck('1') == KEY_PUSH)
    {
        if (RS_FLAG)
        {
            DX::Set_RSState(m_Device.m_pImmediate_Device_Context, DX::CADx_State::m_pRSWire_Frame);

        }
        else
        {
            DX::Set_RSState(m_Device.m_pImmediate_Device_Context, DX::CADx_State::m_pRSSolid_Frame);
        }
    }
    if (I_Input.KeyCheck('2') == KEY_PUSH)
    {
        if (AB_FLAG)
        {
            DX::Set_BState(m_Device.m_pImmediate_Device_Context, DX::CADx_State::m_pAlpha_Blend_Disable);
        }
        else
        {
            DX::Set_BState(m_Device.m_pImmediate_Device_Context, DX::CADx_State::m_pAlpha_Blend);
        }
    }
    if (I_Input.KeyCheck('3') == KEY_PUSH)
    {
        if (SS_FLAG)
        {
            DX::Set_SState(m_Device.m_pImmediate_Device_Context, DX::CADx_State::m_pSSWrap_Linear);
        }
        else
        {
        }
        //m_pSSWrap_Linear
    }

}
void CACore::Debug_Render()
{

    Dx_Write.Draw_Text(m_Debug_Text);
}
void CACore::Debug_Release()
{
    Dx_Write.Release_Once();
    Dx_Write.Release_Fresh_Resource();
}


void CACore::Refresh_m_Debug_Text()
{
    if (m_Device.m_pSwap_Chain != NULL)
    {
        Dx_Write.Release_Fresh_Resource();
        m_Device.Resize();

        Dx_Write.Create_Fresh_Resource();
    }
}

#endif // DEBUG


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
    DX::CADx_State::SetState(m_Device.m_pDevice,m_Device.m_pImmediate_Device_Context);
    
    // m_pDXHelper = new CADevice_Helper(/*m_Device.m_pFactory,*/&CADevice::m_Texture_Map, m_Device.m_pDevice, m_Device.m_pImmediate_Device_Context);
    //m_pDXHelper = new CADevice_Helper(/*m_Device.m_pFactory,*/&m_Device.m_Texture_Map,m_Device.m_pDevice, m_Device.m_pImmediate_Device_Context );


#if defined _DEBUG || DEBUG
    Debug_Init();

#endif

    return Init();
}
bool CACore::CACoreFrame()
{
    m_Device.Frame();// IASetPrimitiveTopology RESET;
    m_Timer.Frame();
    I_Input.Frame();
    I_SoundMgr.Frame();
    

#if defined _DEBUG || DEBUG
    Debug_Frame();
#endif
    return Frame();
    
}
bool CACore::CACoreRender()
{
    m_Device.Pre_Render();
    m_Device.Render();
    Render();
    m_Device.Post_Render();
    m_Timer.Render();
    

#ifdef _DEBUG

    Debug_Render();

#endif

    return true;
}
bool CACore::CACoreRelease()
{
    m_Device.Release();
    m_Timer.Release();
    I_Input.Release();
    I_SoundMgr.Release();
    
    DX::CADx_State::Release();
    
   

    return Release();
}
bool CACore::Run()
{
    CACoreInit();                                     
    MSG msg = { 0 };
    // WM_QUIT -> FALSE
    // 메세지 큐에서 하나하나씩 가져온다.
    //while (GetMessage(&msg, nullptr, 0, 0))
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // 메세지 번역
            DispatchMessage(&msg);	// 메세지 프로시져 전달	
            MessageProc(msg);
        }
        else
        {
            // 게임로직
            CACoreFrame(); // 게임계산
            CACoreRender();// 게임드로우
            //Sleep(1); //1미리초 쉬는건데 필요한가?
        }
    }
    CACoreRelease(); // 게임 종료 
    
    return true;        //정상종료
}

void CACore::MessageProc(MSG msg)
{
    I_Input.MouseCheck(msg);
    if (msg.message == WM_SIZE)
    {

#if defined _DEBUG || DEBUG
        Refresh_m_Debug_Text();
#endif

    }
  //  I_MSG.Msg_list.push_back(msg);
}


CACore::CACore()
{
    
}


CACore::~CACore()
{
}

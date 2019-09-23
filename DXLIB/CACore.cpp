#include "CACore.h"


#if defined _DEBUG || DEBUG
void CACore::Debug_Init()
{
    Dx_Write.Init_Once(m_Device.m_pSwap_Chain);
    Dx_Write.Create_Fresh_Resource();
    //m_Debug_Shape.Create_Debug_Coordinate();
    //m_Debug_Shape.Create(L"VS.vsh", L"PS.psh", "PS", "VS", nullptr, 0, 0, 0, true);
}
void CACore::Debug_Frame()
{
    Dx_Write.Set_Text(m_Debug_Text, m_Timer.m_csBuffer);

    if (I_Input.KeyCheck('1') == KEY_PUSH)
    {
        if (RS_FLAG)
        {
            DX::Set_RSState(m_Device.m_pImmediate_Device_Context, DX::CADx_State::m_pRSWire_Frame);
            RS_FLAG = !RS_FLAG;
        }
        else
        {
            RS_FLAG = !RS_FLAG;
            DX::Set_RSState(m_Device.m_pImmediate_Device_Context, DX::CADx_State::m_pRSSolid_Frame);
        }
    }
    if (I_Input.KeyCheck('2') == KEY_PUSH)
    {
        if (AB_FLAG)
        {
            DX::Set_BState(m_Device.m_pImmediate_Device_Context, DX::CADx_State::m_pAlpha_Blend_Disable);
            AB_FLAG = !AB_FLAG;
        }
        else
        {
            AB_FLAG =! AB_FLAG;
            DX::Set_BState(m_Device.m_pImmediate_Device_Context, DX::CADx_State::m_pAlpha_Blend);
        }
    }
    if (I_Input.KeyCheck('3') == KEY_PUSH)
    {
        if (SS_FLAG)
        {
            SS_FLAG =!SS_FLAG;
            DX::Set_SState(m_Device.m_pImmediate_Device_Context, DX::CADx_State::m_pSSWrap_Linear);
        }
        else
        {
            DX::Set_SState(m_Device.m_pImmediate_Device_Context, DX::CADx_State::m_pSSWrap_Aniso);
            SS_FLAG =! SS_FLAG;
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

LRESULT	CACore::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    
    if (m_pMain_Cam == nullptr) return 1;
    return m_pMain_Cam->WndProc(hWnd, msg, wParam, lParam);
    
}

bool CACore::Init()
{
    return true;
}

bool CACore::Frame()
{
    return true;
}
bool CACore::Pre_Render()
{
   
   
   
   

    // sky
    D3DXMATRIX matSkyWorld;
    D3DXMatrixScaling(&matSkyWorld, 10, 10, 10);
    D3DXMATRIX matSkyView = m_pMain_Cam->m_matView;
    matSkyView._41 = 0.0f;
    matSkyView._42 = 0.0f;
    matSkyView._43 = 0.0f;
   //Sky_box.SetMatrix(&matSkyWorld, &matSkyView,
   //    &m_pMain_Cam->m_matProj);
   //Sky_box.Render(CADevice::m_pImmediate_Device_Context);


    return true;
}

bool CACore::Render()
{
    Pre_Render();

    Post_Render();

    return true;
}
bool CACore::Post_Render()
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
    //Sky_box.Init();
    m_Default_Cam.Init();
    D3DXVECTOR3 Eye(0.0f, 5.0f, -5.0f);
    D3DXVECTOR3 Target(0.0f, 0.0f, 0.0f);
    m_Default_Cam.SetViewMatrix(Eye,Target);
    m_Default_Cam.SetProjMatrix(D3DX_PI / 4,
        (float)g_rtClient.right / (float)g_rtClient.bottom,
        1.0f,
        3000.0f);
    m_Default_Cam.m_vCameraPos = { 0.0f,100.0f,-100.0f };
    m_pMain_Cam = &m_Default_Cam;
    m_pMain_Cam->m_vTargetPos = *(D3DVECTOR*)&DirectX::XMVectorSet(m_pMain_Cam->m_vCameraPos.x, m_pMain_Cam->m_vCameraPos.y, m_pMain_Cam->m_vCameraPos.z, 0);
  /*  m_pMain_Cam->SetViewMatrix(
        m_pMain_Cam->m_vCameraPos, m_pMain_Cam->m_vTargetPos, m_pMain_Cam->m_vUpVector);*/
    m_Heightmap.Init(L"../../_shader/light.hlsl", L"../../_data/map/castle.jpg",L"../../_data/map/HEIGHT_CASTLE.bmp");
    /*if (!Sky_box.Create(CADevice::m_pDevice, L"sky.hlsl", nullptr))
    {
        return false;
    }*/
    DX::Set_BState(CADevice::m_pImmediate_Device_Context, DX::CADx_State::m_pAlpha_Blend);
    DX::Set_DSState(CADevice::m_pImmediate_Device_Context, DX::CADx_State::m_pDSSDepth_Less_Equal);
    DX::Set_RSState(CADevice::m_pImmediate_Device_Context, DX::CADx_State::m_pRSSolid_Frame);
    DX::Set_SState(CADevice::m_pImmediate_Device_Context, DX::CADx_State::m_pSSWrap_Linear);
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
    m_pMain_Cam->Frame();

#if defined _DEBUG || DEBUG
    Debug_Frame();
#endif
    return Frame();
    
}
bool CACore::CACoreRender()
{
    Pre_Render();
    m_Device.Pre_Render();
    m_Device.Render();
    m_Heightmap.Render(CADevice::m_pImmediate_Device_Context,nullptr, &m_pMain_Cam->m_matView,&m_pMain_Cam->m_matProj);
    Render();

#ifdef _DEBUG
    Debug_Render();
 //   m_Debug_Shape.Render(CADevice::m_pImmediate_Device_Context,m_Debug_Shape.m_Index_List.size());
#endif
    m_Device.Post_Render();
    m_Timer.Render();
    Post_Render();


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
void CACore::Msg_Proc(MSG msg)
{

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
            Msg_Proc(msg);
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

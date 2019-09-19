#include "Sample.h"


void Sample::Msg_Proc(MSG msg)
{

    if (msg.message == WM_LBUTTONDOWN)
    {
        int iMouseX = LOWORD(msg.lParam);
        int iMouseY = HIWORD(msg.lParam);
        Cam.m_Arc_Ball.Move_On(iMouseX, iMouseY);
    }
    if (msg.message == WM_RBUTTONDOWN)
    {
        int iMouseX = LOWORD(msg.lParam);
        int iMouseY = HIWORD(msg.lParam);
        Cam.m_Arc_Ball.Moving(iMouseX, iMouseY);
    }
    if (msg.message == WM_MOUSEMOVE)
    {
        int iMouseX = LOWORD(msg.lParam);
        int iMouseY = HIWORD(msg.lParam);
        Cam.m_Arc_Ball.Moving(iMouseX, iMouseY);
    }
    if (msg.message == WM_LBUTTONUP ||
        msg.message == WM_MBUTTONUP ||
        msg.message == WM_RBUTTONUP)
    {
        int iMouseX = LOWORD(msg.lParam);
        int iMouseY = HIWORD(msg.lParam);
        Cam.m_Arc_Ball.Move_End(iMouseX, iMouseY);
    }
 
}

//LRESULT Sample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    // switch (dwmouse.message)            //메세지의 WParam 으로 상태가 온다고 함 MK_LBUTTON
//    // {
//    //     //LB
//    // case WM_LBUTTONDOWN:
//    // {
//    //     if (dwmouse.wParam & MK_LBUTTON) // 눌러져잇음
//    //     {
//    //         m_dwMouseState[0] = KEY_HOLD;
//    //     }
//    //     else
//    //         m_dwMouseState[0] = KEY_PUSH;
//    // }break;
//    //
//    // case WM_LBUTTONUP:
//    // {
//    //     m_dwMouseState[0] = KEY_UP;
//    // }break;
//    //
//    // case WM_LBUTTONDBLCLK:
//    // {
//    //     m_dwMouseState[0] = MOUSE_DBL_CLICK;
//    // }break;
//    //
//    // //MB
//    // case WM_MBUTTONDOWN:
//    // {
//   
//}
//

    bool Sample::Init()
    {
        Cam.m_Arc_Ball.Init();

        HRESULT hr;
        m_Box.Create_Vertex_Index_Const_Data();
        if (!m_Box.Create(CADevice::m_pDevice,
            L"shader.hlsl",
            L"../../_data/sky/ft.bmp"))
        {
            return false;
        }
      /*  m_Obj.Create_Vertex_Index_Const_Data();
        if (!m_Obj.Create(CADevice::m_pDevice,
            L"shader.hlsl",
            L"../../data/bitmap/popup_normal_Alpha.bmp"))
        {
            return false;
        }*/
         m_Map.Init();
          m_Map.CreateNormalMap(CADevice::m_pDevice, CADevice::m_pImmediate_Device_Context, L"../../_data/map/test_normal_map.bmp");
         m_Map.CreateHeightMap(CADevice::m_pDevice, CADevice::m_pImmediate_Device_Context,
             L"../../_data/map/glow.png");
         MapDesc md;
         md.iNumCols = m_Map.m_iNumCols; 
         md.iNumRows = m_Map.m_iNumRows;
         md.fCellDistance = 1;
         md.szShaderFile = L"heightmap.hlsl";
         md.szTextureFile = L"../../_data/map/029_512.jpg";

         if (!m_Map.Load(CADevice::m_pDevice, md))
         {
             return false;
         }
        m_matBoxWorld = DirectX::XMMatrixIdentity();
        m_matPlaneWorld = DirectX::XMMatrixIdentity();

        //D3DXMatrixRotationX(&m_matPlaneWorld, D3DX_PI*0.5f);
        //D3DXMatrixRotationY(&m_matBoxWorld, D3DX_PI/4);

        DirectX::XMFLOAT4X4 temp;
        DirectX::XMStoreFloat4x4(&temp, m_matPlaneWorld);
        temp._42 = 1.0f;
        m_matPlaneWorld = DirectX::XMLoadFloat4x4(&temp);

        m_vPos.x = 0.0f;
        m_vPos.y = 1.0f;
        m_vPos.z = 0.0f;

        // m_backview.Init();

        Cam.m_vPos = DirectX::XMVectorSet(m_vPos.x, m_vPos.y + 10.0f, m_vPos.z - 3.0f, 0);

        Cam.m_vLook_Target_Pos = DirectX::XMVectorSet(m_vPos.x, m_vPos.y, m_vPos.z, 0);
        Cam.Set_View(
            Cam.m_vPos, Cam.m_vLook_Target_Pos, Cam.m_vUp);
        Cam.Set_Projection(1.0f,
            3000.0f,
            DirectX::XM_PI / 4,
            (float)g_rtClient.right / (float)g_rtClient.bottom);
        //m_Sky.Create_Vertex_Index_Const_Data();
        //m_Sky.LoadTextures(CADevice::m_pDevice);
        //메인카메라 건드리는거 찾아보기.

    //
    //box.Create_Vertex_Index_Const_Data();
    //box.Create(L"MAP.hlsl", L"MAP.hlsl", "PS", "VS", L"../../_data/sky/ft.bmp", 1, 800, 600, true);
    // Cam.Init();
    //
    //
    //
    // TMapDesc md;
    // md.iNumCols = map.m_iNumCols=25; // 105, 209
    // md.iNumRows = map.m_iNumRows=25;
    // md.fCellDistance = 1;
    // md.szShaderFile = L"MAP.hlsl";
    // md.szTextureFile = L"../../_data/sky/ft.bmp";
    // map.Load(CADevice::m_pDevice,md);
    // 
    // map.CreateVertexData();
     //map.CreateIndexData();
    // map.Create(L"MAP.hlsl", L"MAP.hlsl", "PS", "VS", L"../../_data/sky/ft.bmp", 1, 800, 600, true); 
    //    
        return true;
    }
    bool Sample::Frame()
    {
        if(I_Input.m_dwMouseState[0]==KEY_HOLD)
        {
                   
        }
        if (I_Input.m_dwMouseState[1] == KEY_HOLD)
        {
            int a = 0;
        }
        if (I_Input.m_dwMouseState[2] == KEY_HOLD)
        {
            int a = 0;
        }
        





        if (I_Input.KeyCheck('W') == KEY_HOLD)
        {
            Cam.Move_Look();
          
        }
        if (I_Input.KeyCheck('S') == KEY_HOLD)
        {
            Cam.Move_Back();

           
        }

        if (I_Input.KeyCheck('D') == KEY_HOLD)
        {
            Cam.Move_Right();

           
        }
        if (I_Input.KeyCheck('A') == KEY_HOLD)
        {
            Cam.Move_Left();

            
        }
        DirectX::XMFLOAT4X4 temp;
        DirectX::XMStoreFloat4x4(&temp, m_matBoxWorld);

        temp._41 = m_vPos.x;
        temp._42 = m_vPos.y;
        temp._43 = m_vPos.z;
        m_matBoxWorld = DirectX::XMLoadFloat4x4(&temp);


       // Cam.m_vPos = DirectX::XMVectorSet(m_vPos.x, m_vPos.y + 10.0f, m_vPos.z - 5.0f, 0);

        //Cam.m_vLook_Target_Pos = DirectX::XMVectorSet(m_vPos.x, m_vPos.y, m_vPos.z, 0);

         m_Map.Frame();
        Cam.Frame();
      //  m_Obj.Frame();
        m_Box.Frame();
        /*box.m_HDX.Set_Const_Buffer_Self(&box.m_Const_List, 0);

        if(I_Input.KeyCheck('Y')==KEY_HOLD)
        {
            Cam.Move_World_Y();
        }
        if (I_Input.KeyCheck('H') == KEY_HOLD)
        {
            Cam.Move_World_Rev_Y();
        }
        if (I_Input.KeyCheck('G') == KEY_HOLD)
        {
            Cam.Move_World_Rev_X();
        }
        if (I_Input.KeyCheck('J') == KEY_HOLD)
        {
            Cam.Move_World_X();
        }
        Cam.Rotation_No_Lerp(0.1, 0.1, 0.1);
        Cam.Frame();*/
        return true;
    }
    bool Sample::Render()
    {
        DX::Set_SState(CADevice::m_pImmediate_Device_Context, DX::CADx_State::m_pSSWrap_Aniso);
        //
        m_Box.SetMatrix(
            &m_matBoxWorld,
            &Cam.m_Matrix_View,
            &Cam.m_Matrix_Projection);
        m_Box.Render(CADevice::m_pImmediate_Device_Context);
        //

      /*  m_Obj.SetMatrix(
            &m_matPlaneWorld,
            &Cam.m_Matrix_View,
            &Cam.m_Matrix_Projection);
        m_Obj.Render(CADevice::m_pImmediate_Device_Context);*/
        //
         m_Map.SetMatrix(
             nullptr,
             &Cam.m_Matrix_View,
            &Cam.m_Matrix_Projection);
         m_Map.Render(CADevice::m_pImmediate_Device_Context);
         //
         DirectX::XMMATRIX sky_world;
         sky_world = DirectX::XMMatrixScaling(10, 10, 10);
         
         //m_Sky.SetMatrix(sky_world,);
         //m_Sky.Render(CADevice::m_pImmediate_Device_Context);

         //// sky
         //D3DXMATRIX matSkyWorld;
         //D3DXMatrixScaling(&matSkyWorld, 10, 10, 10);
         //D3DXMATRIX matSkyView = m_pMainCamera->m_matView;
         //matSkyView._41 = 0.0f;
         //matSkyView._42 = 0.0f;
         //matSkyView._43 = 0.0f;
         //m_SkyBox.SetMatrix(&matSkyWorld, &matSkyView,
         //    &m_pMainCamera->m_matProj);
         //m_SkyBox.Render(m_pImmediateContext);
         /*
          Set_RSState(CADevice::m_pImmediate_Device_Context, DX::CADx_State::m_pRSSolid_Frame);
          Set_SState(CADevice::m_pImmediate_Device_Context, CADx_State::m_pSSWrap_Linear);
          Set_DSState(CADevice::m_pImmediate_Device_Context, CADx_State::m_pDSSDepth_Enable);
          Set_BState(CADevice::m_pImmediate_Device_Context, CADx_State::m_pAlpha_Blend);
            box.Render();

            map.Render(CADevice::m_pImmediate_Device_Context);
      */
        return true;
    }
    bool Sample::Release()
    {
        return true;
    }


    bool Sample::CreateResource()
    {

        return true;
    }
    bool Sample::DeleteResource()
    {

        return true;

    }


    Sample::Sample()
    {
        m_matBoxWorld = DirectX::XMMatrixIdentity();
        m_matPlaneWorld = DirectX::XMMatrixIdentity();
    }


    Sample::~Sample()
    {
    }

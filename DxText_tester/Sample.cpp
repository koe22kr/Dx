#include "Sample.h"


bool Sample::Test()
{
    /////Create_Vertex_And_Index/////////

        ///////////// 설정해야함.

    FLOAT3 TAG[] = {
{1.0f, 1.0f, 0.6f} ,
{1.0f, -1.0f, 0.6f},
{0.0f, 0.0f, 0.6f },
{1.0f, -1.0f, 0.6f},
{1.0f, 1.0f, 0.6f} ,
{-1.0f ,-1.0f,0.6f},
    };
    FLOAT8 TAG2[] =
    {
        {(1.0f,1.0f,0.6f,0.0f,1.0f,1.0f,0.0f,0.0f)},
        {(1.0f,-1.0f,0.6f,0.0f,1.0f,-1.0f,0.0f,0.0f)},
        {(0.0f,-1.0f,0.6f,0.0f,0.0f,-1.0f,0.0f,0.0f)},
        {0.0f, 1.0f, 0.6f, 0.0f, 0.0f, 1.0f, 0.0f, 0.f}

    };
    DWORD Idata[] = { 0,1,2,2,1,3 };


    m_pDevice_Mgr->Create_Vertex_And_Index_Buffer(TAG, ARRAYSIZE(TAG), m_pVertex_Buffer, Idata, ARRAYSIZE(Idata),m_pIndex_Buffer, true);
    m_pDevice_Mgr->Create_Vertex_And_Index_Buffer(TAG2, ARRAYSIZE(TAG2), m_pVertex_Buffer2, Idata, ARRAYSIZE(Idata), m_pIndex_Buffer2, true);

    ////////// 
    m_pDevice_Mgr->Create_Const_Buffer(m_pConst_Buffer);

    m_pDevice_Mgr->Load_PS(m_pPixel_Shader, "PS");
    m_pDevice_Mgr->Load_PS(m_pPixel_Shader2, "Texture");
   

    const D3D11_INPUT_ELEMENT_DESC Lay_Out[] =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT ,0,0,D3D11_INPUT_PER_VERTEX_DATA ,0 }
    };
    const D3D11_INPUT_ELEMENT_DESC Lay_Out2[] =
    { 
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT ,0,0,D3D11_INPUT_PER_VERTEX_DATA ,0 },
        {"TEX",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12    ,D3D11_INPUT_PER_VERTEX_DATA,0}
    };

    m_pDevice_Mgr->Load_VS_And_Set_Input_Layout(m_pVertex_Shader, m_pInput_Layout, "VS", Lay_Out, ARRAYSIZE(Lay_Out));
    m_pDevice_Mgr->Load_VS_And_Set_Input_Layout(m_pVertex_Shader, m_pInput_Layout, "VS", Lay_Out2,ARRAYSIZE(Lay_Out2));

    m_pDevice_Mgr->Set_Draw_Flag(true);

    m_pDevice_Mgr->Set_Start_Location(6, 0, 0);
    //로케이션 세팅을 한다면!
    return true;
}
bool Sample::Init()
{
 
    m_pDevice_Mgr = new CADeviceMgr(m_Device.m_pFactory, m_Device.m_pDevice, m_Device.m_pImmediate_Device_Context, &m_Device.m_Texture_Map);
    Test();
    m_pDevice_Mgr->Load_Texture_2D_From_File(L"../../_data/bitmap1.bmp", 300, 300,0 );
    m_pDevice_Mgr->Create_Shader_Resource_View_From_Resource(L"../../_data/bitmap1.bmp", m_pSRV);
    m_pDevice_Mgr->Set_SRV_To_PS(m_pSRV, 0);
    return true;
}
bool Sample::Frame()
{
    Test_Frame();
    return true;
}

bool Sample::Render()
{
    m_pDevice_Mgr->Set_SRV_To_PS(m_pSRV, 0);

    m_pDevice_Mgr->Set_Pipe_Line(m_pInput_Layout, m_pVertex_Buffer, m_pIndex_Buffer, m_pConst_Buffer, m_pVertex_Shader, 0, 0, 0, m_pPixel_Shader);
    m_pDevice_Mgr->Draw();
    return true;
}
void Sample::Test_Frame()
{
    //Sample용 테스트 상수버퍼 타임값.
    float fbtime = cosf(g_fGameTimer)*0.5f + 0.5f;
    Const_Data CD = { D3DXVECTOR4(0.5,0.5,0.5, 1.0f), fbtime };

    
    m_pDevice_Mgr->Set_Const_Buffer(m_pConst_Buffer,&CD);

    /* m_Const_Data.Color = D3DXVECTOR4(cosf(g_fGameTimer), sinf(g_fGameTimer), tanf(g_fGameTimer), 1.0f);
     m_Const_Data.x = fbtime;*/
     //Unmap
}

Sample::Sample()
{
    
    
}


Sample::~Sample()
{
}

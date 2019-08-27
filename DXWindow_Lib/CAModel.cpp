#include "CAModel.h"


bool CAModel::Pipe(const char* PSname, const char* VSname,const WCHAR* file_name,int width,int height,bool index_drawing_flag)
{
    m_Texture.m_Index_Draw_Flag = index_drawing_flag;

  //  m_pDevice = pd3dDevice;
    m_HDX.Load_PS(m_pPixel_Shader, PSname, m_pDevice);
    D3D11_INPUT_ELEMENT_DESC m_Input_Desc[] = {
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA,0},
    {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    m_HDX.Load_VS_And_Set_Input_Layout(m_pVertex_Shader, m_pInput_Layout, VSname, m_Input_Desc, 4, m_pDevice);
    
    if (m_Vertex_List.size() == 0)
    {
        MessageBox(NULL, L"m_Vertex_List.size()==0", L"CAModel", MB_OK);
        return false;
    }

    m_HDX.Create_Vertex_And_Index_Buffer(m_Vertex_List[0], m_Vertex_List.size(), sizeof(D3DXVECTOR3), m_pVertex_Buffer, &m_Index_List[0], m_Index_List.size(), sizeof(DWORD), m_pIndex_Buffer);
    m_HDX.Create_Const_Buffer(m_pConst_Buffer, &m_Const_List[0],m_Const_List.size(), sizeof(VS_CB), m_pDevice); 
    
    m_HDX.Create_Shader_Resource_View_From_File(file_name, &m_Texture, m_pDevice);
    if (m_Texture.m_Index_Draw_Flag)
    {
        m_Texture.m_Draw_Count = m_Index_List.size();
    }
    else
    {
        m_Texture.m_Draw_Count = m_Vertex_List.size();
    }

   // if (!UpdateBuffer())
    //if (FAILED(CreateResource()))//.???
   // SetCollisionData();

     Init();
     return true;
}

bool CAModel::Create_Vertex_Index_Const_Data()
{
    return true;
}

bool CAModel::Init()
{
    return true;
}

bool CAModel::Frame()
{
    return true;
}

bool CAModel::Render()
{
    m_Texture.Draw(m_pImmediate_Device_Context);
    return true;
}

bool CAModel::Release()
{
    return true;
}
CAModel::CAModel()
{
    m_pDevice = CADevice::m_pDevice;
    m_pImmediate_Device_Context = CADevice::m_pImmediate_Device_Context;
}

CAModel::CAModel(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediate_Device_Context)
{
    m_pDevice = pDevice;
    m_pImmediate_Device_Context = pImmediate_Device_Context;
}
CAModel::~CAModel()
{
}

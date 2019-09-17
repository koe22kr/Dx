#include "CADx_Model.h"
namespace DX
{

    bool CADx_Model::Create(const WCHAR* VS_compiler, const WCHAR* PS_compiler, const char* PSname, const char* VSname, const WCHAR* file_name, UINT Key, int width, int height, bool index_drawing_flag)
    {


        //  m_pDevice = pd3dDevice;
        m_HDX.Load_PS_Self(PS_compiler, PSname);

        //m_HDX.Load_PS(PS_compiler,m_pPixel_Shader, PSname, m_pDevice);
        D3D11_INPUT_ELEMENT_DESC m_Input_Desc[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA,0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0}
        };

        m_HDX.Load_VS_And_Set_Input_Layout_Self(VS_compiler, VSname, m_Input_Desc, 4);
        //m_HDX.Load_VS_And_Set_Input_Layout(VS_compiler,m_pVertex_Shader, m_pInput_Layout, VSname, m_Input_Desc, 4, m_pDevice);
        m_HDX.Create_Vertex_And_Index_Buffer_Self(&m_Vertex_List, &m_Index_List);// , sizeof(D3DXVECTOR3), &m_Index_List[0], m_Index_List.size(), sizeof(DWORD));

        if (m_Vertex_List.size() == 0)
        {
            MessageBox(NULL, L"m_Vertex_List.size()==0", L"CADx_Model", MB_OK);
        }
        
        //m_HDX.Create_Vertex_And_Index_Buffer(m_Vertex_List[0], m_Vertex_List.size(), sizeof(D3DXVECTOR3), m_pVertex_Buffer, &m_Index_List[0], m_Index_List.size(), sizeof(DWORD), m_pIndex_Buffer);
        if (m_Const_List.size() != 0)
        {
            m_HDX.Create_Const_Buffer_Self(&m_Const_List[0], m_Const_List.size(), sizeof(VS_CB));
        }
        else
        {
            
            
            m_HDX.Create_Const_Buffer_Self(nullptr, 1, sizeof(VS_CB));

        }
        //m_HDX.Create_Const_Buffer(m_pConst_Buffer, &m_Const_List[0],m_Const_List.size(), sizeof(VS_CB), m_pDevice); 
        if (file_name != nullptr)
        {
            m_HDX.Load_Shader_Resource_View_From_File_Self(file_name, Key);
        }
        //    m_HDX.Load_Shader_Resource_View_From_File(file_name, ptexture, Key, m_pDevice);

           // if (!UpdateBuffer())
            //if (FAILED(CreateResource()))//
           // SetCollisionData();

        /*Init();*/
        return true;
    }

    bool CADx_Model::Set_Const_Data(VS_CB constdata)
    {
        m_Const_List.push_back(constdata);
        return true;
    }

    bool CADx_Model::Set_Vertex_Index_Data(std::vector<PNCT_VERTEX> Vertex_List, std::vector<DWORD> Index_List)
    {
        m_Vertex_List = Vertex_List;
        m_Index_List = Index_List;
        //m_HDX.Set_Const_Buffer; 
        //Create Vertex,Index;
        return true;
    }

  /*  bool CADx_Model::Init()
    {
        return true;
    }

    bool CADx_Model::Frame()
    {

        return true;
    }*/
    bool CADx_Model::Render()
    {
        m_HDX.Render(m_Index_List.size());
        return true;
    }
    bool CADx_Model::Render( ID3D11DeviceContext* pContext,UINT draw_count,  UINT vertex_location, UINT index_location)
    {
        if (draw_count != NULL)
        {
            m_HDX.Render(draw_count, vertex_location, index_location, pContext);
        }
        else
        {
            m_HDX.Render(m_Index_List.size(), vertex_location, index_location, pContext);
        }
        return true;
    }

    bool CADx_Model::Release()
    {
        return true;
    }
    CADx_Model::CADx_Model()
    {
        m_pDevice = CADevice::m_pDevice;
        m_pImmediate_Device_Context = CADevice::m_pImmediate_Device_Context;
    }

    CADx_Model::CADx_Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediate_Device_Context)
    {
        m_pDevice = pDevice;
        m_pImmediate_Device_Context = pImmediate_Device_Context;
    }
    CADx_Model::~CADx_Model()
    {
    }
}
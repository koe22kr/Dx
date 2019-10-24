#include "CADx_Model.h"
namespace DX
{

    bool CADx_Model::Create(const WCHAR* VS_compiler, const WCHAR* PS_compiler, const char* PSname, const char* VSname, const WCHAR* file_name, UINT Key, int width, int height, bool index_drawing_flag)
    {


        m_HDX.Load_PS_Self(PS_compiler, PSname);

        D3D11_INPUT_ELEMENT_DESC m_Input_Desc[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA,0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0}
        };

        m_HDX.Load_VS_And_Set_Input_Layout_Self(VS_compiler, VSname, m_Input_Desc, 4);
        m_HDX.Create_Vertex_And_Index_Buffer_Self(&m_Vertex_List, &m_Index_List);// , sizeof(D3DXVECTOR3), &m_Index_List[0], m_Index_List.size(), sizeof(DWORD));

        if (m_Vertex_List.size() == 0)
        {
            MessageBox(NULL, L"m_Vertex_List.size()==0", L"CADx_Model", MB_OK);
        }
        
        if (m_Const_List.size() != 0)
        {
            m_HDX.Create_Const_Buffer_Self(&m_Const_List.at(0), m_Const_List.size(), sizeof(VS_CB));
        }
        else
        {
            
            
            m_HDX.Create_Const_Buffer_Self(nullptr, 1, sizeof(VS_CB));

        }
        if (file_name != nullptr)
        {
            m_HDX.Load_Shader_Resource_View_From_File_Self(file_name, Key);
        }

         

        /*Init();*/
        return true;
    }

    bool CADx_Model::Set_Matrix(DirectX::XMMATRIX* world, DirectX::XMMATRIX* view, DirectX::XMMATRIX* proj)
    {
        if (proj != nullptr)
        {
            m_cb.matProj = DirectX::XMMatrixTranspose(*proj);
        }
        else
        {
            m_cb.matProj = DirectX::XMMatrixTranspose(m_Matrix_Projection);
        }
        if (view != nullptr)
        {
            m_cb.matView = DirectX::XMMatrixTranspose(*view);
        }
        else
        {
            m_cb.matProj = DirectX::XMMatrixTranspose(m_Matrix_View);
        }
        if(world!=nullptr)
        {
            m_cb.matWorld = DirectX::XMMatrixTranspose(*world);
        }
        else
        {
            m_cb.matProj = DirectX::XMMatrixTranspose(m_Matrix_World);
        }
        DirectX::XMFLOAT4X4 temp;
        DirectX::XMStoreFloat4x4(&temp, *world);
        m_box.vCenter.x = temp._41;
        m_box.vCenter.y = temp._42;
        m_box.vCenter.z = temp._43;
        m_sphere.vCenter = m_box.vCenter;
        return true;
    }

    bool CADx_Model::Set_Vertex_Index_Data(std::vector<PNCT_VERTEX> Vertex_List, std::vector<DWORD> Index_List)
    {
        m_Vertex_List = Vertex_List;
        m_Index_List = Index_List;
        return true;
    }

    bool CADx_Model::Init()
    {
       

        return true;
    }

    bool CADx_Model::Frame()
    {

        return true;
    }
    bool CADx_Model::Render()
    {
        Set_Matrix(&m_Matrix_World, &m_Matrix_View, &m_Matrix_Projection);
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
        m_Matrix_World = DirectX::XMMatrixIdentity();
        m_Matrix_View = DirectX::XMMatrixIdentity();
        m_Matrix_Projection = DirectX::XMMatrixIdentity();
        m_pDevice = CADevice::m_pDevice;
        m_pImmediate_Device_Context = CADevice::m_pImmediate_Device_Context;
    }

    CADx_Model::CADx_Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediate_Device_Context)
    {
        
        m_Matrix_World = DirectX::XMMatrixIdentity();
        m_Matrix_View = DirectX::XMMatrixIdentity();
        m_Matrix_Projection = DirectX::XMMatrixIdentity();

        m_pDevice = pDevice;
        m_pImmediate_Device_Context = pImmediate_Device_Context;
    }
    CADx_Model::~CADx_Model()
    {
    }
}
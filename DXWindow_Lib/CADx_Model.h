#pragma once
#include "CADevice_Helper.h"
#
//#include <wrl.h>
namespace DX
{

    struct CA_BOX
    {
        DirectX::XMFLOAT3 vCenter;
        DirectX::XMFLOAT3 vMin;
        DirectX::XMFLOAT3 vMax;
        DirectX::XMFLOAT3 vAxis[3];
        float       fExtent[3];
    };
    struct CA_SPHERE
    {
        DirectX::XMFLOAT3 vCenter;
        float       fRadius;
    };

    class CADx_Model
    {
    public:
    
        DirectX::XMMATRIX m_Matrix_World;
        DirectX::XMMATRIX m_Matrix_View;
        DirectX::XMMATRIX m_Matrix_Projection;

        VS_CB m_cb;
        CA_BOX m_box;
        CA_SPHERE m_sphere;
        ID3D11Device*            m_pDevice;
        ID3D11DeviceContext*     m_pImmediate_Device_Context;
        CADevice_Helper m_HDX;

        //CATexture        m_Texture;
        std::vector<PNCT_VERTEX> m_Vertex_List;
        std::vector<DWORD> m_Index_List;
        std::vector<VS_CB> m_Const_List;
        /* ¹Ì»ç¿ë
        ID3D11Buffer* m_pVertex_Buffer;
        ID3D11Buffer* m_pIndex_Buffer;
        ID3D11Buffer* m_pConst_Buffer;

        ID3D11VertexShader* m_pVertex_Shader;
        ID3D11PixelShader* m_pPixel_Shader;

        ID3D11ShaderResourceView* m_pSRV;*/

        /*ID3D11InputLayout* m_pInput_Layout;
        ID3D11ShaderResourceView* m_pSRV;
        ID3D11Buffer* m_pVertex_Buffer;
        ID3D11Buffer* m_pIndex_Buffer;
        ID3D11Buffer* m_pConst_Buffer;
        ID3D11VertexShader* m_pVertex_Shader;
        ID3D11PixelShader* m_pPixel_Shader;*/
    public:
        HRESULT hr;
        virtual bool Create(const WCHAR* VS_compiler, const WCHAR* PS_compiler, const char* PSname, const char* VSname, const WCHAR* file_name, UINT Key, int width, int height, bool index_drawing_flag) final;

        bool Set_Vertex_Index_Data(std::vector<PNCT_VERTEX> Vertex_List, std::vector<DWORD> Index_List);
        bool Set_Matrix(DirectX::XMMATRIX* world, DirectX::XMMATRIX* view, DirectX::XMMATRIX* proj);//pushback_in_constlist;
        

        virtual bool Init();
        virtual bool Frame();
        virtual bool Render();
        virtual bool Render( ID3D11DeviceContext* pContext, UINT draw_count , UINT vertex_location = 0, UINT index_location = 0);
        virtual bool Release();

        CADx_Model();
        CADx_Model(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediate_Device_Context);
        virtual ~CADx_Model();
    };

}
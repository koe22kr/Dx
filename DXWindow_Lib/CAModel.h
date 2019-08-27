#pragma once
#include "CADevice_Helper.h"
#
//#include <wrl.h>

struct PNCT_VERTEX
{
    
    D3DXVECTOR3 p;
    D3DXVECTOR3 n;
    D3DXVECTOR4 c;
    D3DXVECTOR2 t;
};

struct VS_CB
{
    D3DMATRIX matWorld;
    D3DMATRIX matView;
    D3DMATRIX matProj;
    D3DXVECTOR4 color;
    D3DXVECTOR4 etc;
};

class CAModel
{
    ID3D11Device*            m_pDevice;
    ID3D11DeviceContext*     m_pImmediate_Device_Context;
    CADevice_Helper m_HDX;

    CATexture        m_Texture;
    std::vector<D3DXVECTOR3> m_Vertex_List;
    std::vector<DWORD> m_Index_List;
    std::vector<VS_CB> m_Const_List;
  
    /* ¹Ì»ç¿ë
    ID3D11Buffer* m_pVertex_Buffer;
    ID3D11Buffer* m_pIndex_Buffer;
    ID3D11Buffer* m_pConst_Buffer;

    ID3D11VertexShader* m_pVertex_Shader;
    ID3D11PixelShader* m_pPixel_Shader;

    ID3D11ShaderResourceView* m_pSRV;*/
    ID3D11InputLayout* m_pInput_Layout;
    ID3D11ShaderResourceView* m_pSRV;
    ID3D11Buffer* m_pVertex_Buffer;
    ID3D11Buffer* m_pIndex_Buffer;
    ID3D11Buffer* m_pConst_Buffer;
    ID3D11VertexShader* m_pVertex_Shader;
    ID3D11PixelShader* m_pPixel_Shader;
public:
    HRESULT hr;
    virtual bool Pipe(const char* PSname, const char* VSname, const WCHAR* file_name, int width, int height, bool index_drawing_flag) final;
    virtual bool Create_Vertex_Index_Const_Data() = 0;
    virtual bool Init();
    virtual bool Frame();
    virtual bool Render();
    virtual bool Release();

    CAModel();
    CAModel(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediate_Device_Context);
    virtual ~CAModel();
};


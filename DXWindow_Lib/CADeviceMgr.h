#pragma once
#include "Device.h"

struct FLOAT3
{
    float x;
    float y;
    float z;
};
struct Const_Data
{
    D3DXVECTOR4 Color;
    float x;
    float y;
    float z;
    float w;
};

class CADeviceMgr
{

    HRESULT hr;
    map<wstring, ID3D11Texture2D*>* m_pTexture_Map;
    IDXGIFactory*            m_pFactory;
    ID3D11Device*            m_pDevice;
    ID3D11DeviceContext*     m_pImmediate_Device_Context;


public:
    bool m_Index_Draw_Flag;
    int m_Draw_Count;
    int m_Start_Vertex_Location;
    int m_Start_Index_Location;
    bool Draw_Flag;
    int m_Const_Buffer_Size;
    void Set_Draw_Flag(bool flag) { Draw_Flag = flag; }; //ÇÊ¼ö
    void Set_Start_Location(int draw_count, int vertex_location, int index_location = 0);

private:
    bool Create_Vertex_Buffer_F3(FLOAT3* float_2d, int obj_num, ID3D11Buffer*& pVertex_buffer);
    bool Create_Index_Buffer(DWORD* Idata, int m_Index_Num, ID3D11Buffer*& pIndex_buffer);
public:
    bool Create_Const_Buffer(ID3D11Buffer*& pConst_buffer);

    bool Create_Vertex_And_Index_Buffer(FLOAT3* vertex_array, int vertex_size,  ID3D11Buffer*& pVertex_Buffer, DWORD* index_array, int index_size, ID3D11Buffer*& pIndex_Buffer, bool index_drawing);
    bool Load_VS_And_Set_Input_Layout(ID3D11VertexShader*& pVertex_Shader, ID3D11InputLayout*& pInput_Layout, const char* VS_name, const D3D11_INPUT_ELEMENT_DESC Lay_Out);
    bool Load_PS(ID3D11PixelShader*& pPixel_Shader, const char* PS_name);


    void Load_Texture_2D_From_File(const TCHAR* texture_full_path, int width, int height, UINT key);
    bool Create_Shader_Resource_View_From_Resource(const TCHAR* texture_full_path, ID3D11ShaderResourceView*& pSRV);
    void Set_SRV_To_PS(ID3D11ShaderResourceView* pSRV, int start_slot);
    
    void Set_Const_Buffer(ID3D11Buffer* pConst_buffer, Const_Data* const_data);
  
    void Set_Pipe_Line(ID3D11InputLayout* pInput_Layout,ID3D11Buffer* pVertex_buffer = NULL, ID3D11Buffer* pIndex_Buffer = NULL, ID3D11Buffer* pConst_Buffer = NULL, ID3D11VertexShader* pVertex_Shader = NULL, ID3D11HullShader* pHull_Shader = NULL, ID3D11DomainShader* pDomain_Shader = NULL, ID3D11GeometryShader* pGeometry_Shader = NULL, ID3D11PixelShader* pPixel_Shader = NULL);
public:
    CADeviceMgr() = delete;
     CADeviceMgr(IDXGIFactory* pfactory, ID3D11Device* pdevice, ID3D11DeviceContext* pimmediate_device_context, map<wstring, ID3D11Texture2D*>* pTexture_Map) ;
    virtual ~CADeviceMgr();
   /* bool Init();
    bool Frame();
    bool Render();
    bool Release();*/
    bool Draw();
};


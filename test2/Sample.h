#pragma once
#include "CACore.h"


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

class Sample :public CACore
{
    bool Test();
    void Test_Frame();
    
private:
    HRESULT hr;
    IDXGIFactory*            m_pFactory;
    ID3D11Device*            m_pDevice;
    ID3D11DeviceContext*     m_pImmediate_Device_Context;
private:
    bool m_Index_Draw_Flag;
    int m_Draw_Count;
    int m_Start_Vertex_Location;
    int m_Start_Index_Location;
    bool Draw_Flag;
    int m_Const_Buffer_Size;
public:
    void Set_Draw_Flag(bool flag) { Draw_Flag = flag; }; //필수
    void Set_Start_Location(int draw_count, int vertex_location, int index_location=0);
private:
    ID3D11InputLayout* m_pInput_Layout;
    ID3D11Buffer* m_pVertex_Buffer;
    ID3D11Buffer* m_pIndex_Buffer;
    ID3D11Buffer* m_pConst_Buffer;
    Const_Data m_Const_Data;

    ID3D11VertexShader* m_pVertex_Shader;
    ID3D11PixelShader* m_pPixel_Shader;
public:
    bool Create_Vertex_Buffer_F3(FLOAT3* float_2d, int obj_num, ID3D11Buffer*& pVertex_buffer);
    bool Create_Index_Buffer(DWORD* Idata, int m_Index_Num, ID3D11Buffer*& pIndex_buffer);
    bool Create_Const_Buffer(ID3D11Buffer*& pConst_buffer);

    bool Create_Vertex_And_Index(FLOAT3* vertex_array, int vertex_size, DWORD* index_array, int index_size, bool index_drawing);
   
    bool Load_VS_And_Set_Input_Layout(ID3D11VertexShader*& pVertex_Shader, ID3D11InputLayout*& pInput_Layout, const char* VS_name, const D3D11_INPUT_ELEMENT_DESC Lay_Out);
    bool Load_PS(ID3D11PixelShader*& pPixel_Shader, const char* PS_name);
    
    void Set_Const_Buffer(float color_x = 0, float color_y = 0, float color_z = 0, float color_w = 0, float x = 0, float y = 0, float z = 0, float w = 0);
    void Set_Const_Buffer(Const_Data& data);
    void Set_Const_Buffer(const Const_Data& data);
   
    bool Draw();
    void Set_Box(int left, int top, int right, int bottom, int front, int back, int box_index);
    void Custom_Draw(int posx, int posy, int texture_key, int box_index);
public:
    ID3D11Texture2D* m_pBack_Buffer;
    D3D11_TEXTURE2D_DESC m_Back_Buffer_Desc;
    vector<ID3D11ShaderResourceView*> m_SRV_List;
    map<wstring,ID3D11Texture2D*> m_Texture_Map;// 디바이스나... 상위에 놓아야 할것 같다.
   
    void Load_Texture_2D_From_File(const TCHAR* texture_full_path,int width,int height, UINT key);
    void Create_Shader_Resource_View_From_Resource(const TCHAR* texture_full_path);
    void Set_SRV_To_PS(ID3D11ShaderResourceView* pSRV);


public:
    Sample();
    ~Sample();
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
};

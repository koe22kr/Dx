#pragma once
#include "CAStd.h"
#include <d3d11.h>
#include <d3dx11.h> 
#include "dxdiag.h"

#pragma comment( lib, "d3dx11.lib" )
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib,"dxgi.lib")

#define MAX_CONST_BUFFER 100
#include <d3dx10math.h>
#include <DirectXPackedVector.h>

#pragma comment(lib,"d3dx10.lib")

struct FLOAT3
{
    float x;
    float y;
    float z;
};
struct CONST_BUFFER_F8
{
    D3DXVECTOR4  vColor;
    float x;
    float y;
    float z;
    float w;

};

class Device
{
public:
    int m_Vertex_Num;
    int m_Index_Num;
    bool m_Index_Draw;
    int m_Start_Vertex_Location;
    int m_Draw_Count;
    int m_Start_Index_Location;
    bool Draw_Flag;
//    int m_
    void Set_Vertex_Num(int draw_num) { m_Vertex_Num = draw_num; };
    void Set_Index_Num(int Index_num) { m_Index_Num = Index_num; };
public:
    HRESULT hr;
    D3D_FEATURE_LEVEL m_Feature_Level;

    D3D11_VIEWPORT m_View_Port;
    IDXGIFactory*            m_pFactory;
    ID3D11Device*            m_pDevice;
    ID3D11DeviceContext*     m_pImmediate_Device_Context;
    IDXGISwapChain*          m_pSwap_Chain;
    ID3D11RenderTargetView*  m_pRender_Target_View;
public:
    bool Create_Device();
    bool Create_DXGIFactory();
    bool Create_Swap_Chain();
    bool Set_Render_Target_View();
    bool Set_View_Port(float pos_x = 0, float pos_y = 0, float width = g_rtClient.right, float height = g_rtClient.bottom, float min_depth = 0.0f, float max_depth = 1.0f);
public:
    DWORD m_Const_Buffer_Data[MAX_CONST_BUFFER];
    
    ID3D11InputLayout* m_pInput_Layout;
    ID3D11Buffer* m_pVertex_Buffer;
    ID3D11Buffer* m_pIndex_Buffer;
    ID3D11Buffer* m_pConst_Buffer;
    
    ID3D11VertexShader* m_pVertex_Shader;
    ID3D11PixelShader* m_pPixel_Shader;

    bool Load_VS_And_Set_Input_Layout(ID3D11VertexShader* pVertex_Shader, ID3D11InputLayout* pInput_Layout);
    bool Load_PS(ID3D11PixelShader* pPixel_Shader);

    bool Create_Vertex_Buffer_F3(FLOAT3* float_2d, int obj_num, ID3D11Buffer* pVertex_buffer);
    bool Create_Index_Buffer(DWORD* Idata, int m_Index_Num, ID3D11Buffer* pIndex_buffer);
    bool Create_Const_Buffer(ID3D11Buffer* pConst_buffer);
    bool Draw();
public:

    bool Init();
    bool Frame();
    bool Pre_Render();
    bool Render();
    bool Post_Render();

    bool Release();
    Device();
    virtual ~Device();
};


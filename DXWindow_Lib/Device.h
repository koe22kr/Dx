#pragma once
#include "CAStd.h"
#include <D2D1.h>
#include <d3d11.h>
#include <d3dx11.h> 
#include "dxdiag.h"
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib,"dxgi.lib")

#include <d3dx10math.h>
#include <DirectXPackedVector.h>

#pragma comment(lib,"d3dx10.lib")
//
//struct FLOAT3
//{
//    float x;
//    float y;
//    float z;
//};
/*
struct CONST_BUFFER_F8
{
    D3DXVECTOR4  vColor;
    float x;
    float y;
    float z;
    float w;

};*/

#define EM(hr,msg,_where) if (FAILED(hr)) MessageBox(g_hWnd, L#msg, L#_where, MB_OK)
    
    

class Device
{
public:
   
public:
    HRESULT hr;
    D3D_FEATURE_LEVEL m_Feature_Level;

    D3D11_VIEWPORT m_View_Port;
    IDXGIFactory*            m_pFactory;
    ID3D11Device*            m_pDevice;
    ID3D11DeviceContext*     m_pImmediate_Device_Context;
    IDXGISwapChain*          m_pSwap_Chain;
    ID3D11RenderTargetView*  m_pRender_Target_View;
    ID3D11Texture2D* m_pBack_Buffer;
    D3D11_TEXTURE2D_DESC m_Back_Buffer_Desc;

    map<wstring, ID3D11Texture2D*> m_Texture_Map;// 디바이스나... 상위에 놓아야 할것 같다.
public:
    bool Create_Device();
    bool Create_DXGIFactory();
    bool Create_Swap_Chain();
    bool Set_Render_Target_View();
    bool Set_View_Port(float pos_x = 0, float pos_y = 0, float width = g_rtClient.right, float height = g_rtClient.bottom, float min_depth = 0.0f, float max_depth = 1.0f);
public:
   // DWORD m_Const_Buffer_Data[MAX_CONST_BUFFER];
    
   
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


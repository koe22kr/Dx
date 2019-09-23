#pragma once
#include "CAStd.h"
#include "CADx_Std.h"

    
class CATexture;

class CADevice
{
public:
   
public:
    HRESULT hr;
    D3D_FEATURE_LEVEL m_Feature_Level;

    D3D11_VIEWPORT m_View_Port;
    static IDXGIFactory*            m_pFactory;
    static ID3D11Device*            m_pDevice;
    static ID3D11DeviceContext*     m_pImmediate_Device_Context;
    IDXGISwapChain*          m_pSwap_Chain;
    ID3D11RenderTargetView*  m_pRender_Target_View;
    ID3D11Texture2D* m_pBack_Buffer;
    D3D11_TEXTURE2D_DESC m_Back_Buffer_Desc;
    DXGI_SWAP_CHAIN_DESC m_Swap_Chain_Desc;
    ID3D11DepthStencilView* m_pDepth_Stencil_View;

   static map<UINT, CATexture*> m_Texture_Map;// 디바이스나... 상위에 놓아야 할것 같다.
public:
    bool Create_Device();
    bool Create_DXGIFactory();
    bool Create_Swap_Chain();
    bool Set_Render_Target_View();
    bool Set_View_Port(float pos_x = 0, float pos_y = 0, float width = g_rtClient.right, float height = g_rtClient.bottom, float min_depth = 0.0f, float max_depth = 1.0f);
    void Resize();
public:
   // DWORD m_Const_Buffer_Data[MAX_CONST_BUFFER];
    
   
public:

    bool Init();
    bool Frame();
    bool Pre_Render();
    bool Render();
    bool Post_Render();

    bool Release();
    CADevice();
    virtual ~CADevice();
};


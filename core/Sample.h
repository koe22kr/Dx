#include "CACore.h"
#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib,"dxgi.lib")



#pragma once

class Sample :public CACore
{
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
  
    
    
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    Sample();
    ~Sample();

private:

};

#pragma once
#include "CADevice.h"
#include <DWrite.h>
#pragma comment( lib, "dwrite.lib")

struct DXText
{
    D2D1_MATRIX_3X2_F mat_world;    
    D2D1_RECT_F  rt_f;
    D3DCOLORVALUE color;
    wstring text;
    IDWriteTextFormat* pText_Format;
    DXText()
    {
        mat_world = D2D1::IdentityMatrix();
        color = { 0,0,0,0 };
        rt_f.top = 0;
        rt_f.left = 0;
        rt_f.right = 0;
        rt_f.bottom = 0;
        pText_Format = nullptr;
    }
};

class CADx_Text
{

    HRESULT hr;
   	IDXGISwapChain*			m_pSwap_Chain;
   
    IDXGISurface1* m_pSurface;
    ID2D1Factory* m_p2DFactory;
    IDWriteFactory* m_pDWrite_Factory;
    IDWriteTextFormat* m_pDWrite_Text_Format;

    ID2D1RenderTarget* m_p2DRender_Target;
    ID2D1SolidColorBrush* m_pBrush;
    float m_fDpiX;
    float m_fDpiY;
    float m_fDpi_ScaleX;
    float m_fDpi_ScaleY;
public:
    void Init_Once(IDXGISwapChain* m_pSwap_Chain);
    void Create_Fresh_Resource();

    void Set_Text(DXText& text, WCHAR* data, D2D1_RECT_F* rt_f =nullptr, D3DCOLORVALUE* color = nullptr);
    void Draw_Text(DXText& dxtext);

    CADx_Text();
    CADx_Text(IDXGISwapChain* m_pSwap_Chain);
    ~CADx_Text();
    
    void Release();
    void Release_Once();
    void Release_Fresh_Resource();

};


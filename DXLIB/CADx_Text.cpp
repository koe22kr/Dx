
#include "CADx_Text.h"


namespace DX
{
    void CADx_Text::Set_Text(DXText& text, WCHAR* data, D2D1_RECT_F* rt_f, D3DCOLORVALUE* color)
    {
        text.text = data;
        if (rt_f != nullptr)
        {
            text.rt_f = *rt_f;
        }
        if (color != nullptr)
        {
            text.color = *color;
        }
    }


    void CADx_Text::Init_Once(IDXGISwapChain* m_pSwap_Chain)
    {
        this->m_pSwap_Chain = m_pSwap_Chain;
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_p2DFactory);
        EM(hr, D2D1CreateFactory, CADx_Text);

        m_p2DFactory->GetDesktopDpi(&m_fDpiX, &m_fDpiY);
        m_fDpi_ScaleX = m_fDpiX / 96.0f;
        m_fDpi_ScaleY = m_fDpiY / 96.0f;

        hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pDWrite_Factory);
        EM(hr, DWriteCreateFactory, CADx_Text);

        hr = m_pDWrite_Factory->CreateTextFormat(
            L"±Ã¼­",
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
            20,
            L"ko-kr",
            &m_pDWrite_Text_Format);
        EM(hr, CreateTextFormat, CADx_Text);

    }

    void CADx_Text::Create_Fresh_Resource()
    {
        //D2D1_RENDER_TARGET_TYPE type;
       //D2D1_PIXEL_FORMAT pixelFormat;
       //FLOAT dpiX;
       //FLOAT dpiY;
       //D2D1_RENDER_TARGET_USAGE usage;
       //D2D1_FEATURE_LEVEL minLevel;

        D2D1_RENDER_TARGET_PROPERTIES RTP;
        RTP.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
        RTP.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
        RTP.dpiX = m_fDpiX;
        RTP.dpiY = m_fDpiY;
        RTP.usage = D2D1_RENDER_TARGET_USAGE_NONE;
        RTP.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

        hr = m_pSwap_Chain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&m_pSurface);
        EM(hr, GetBuffer, CADx_Text);

        hr = m_p2DFactory->CreateDxgiSurfaceRenderTarget(m_pSurface, RTP, &m_p2DRender_Target);
        EM(hr, CreateDxgiSurfaceRenderTarget, CADx_Text);

        hr = m_p2DRender_Target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Violet), &m_pBrush);
        EM(hr, CreateSolidColorBrush, CADx_Text);
    }


    void CADx_Text::Release_Once()
    {
        if (m_pDWrite_Text_Format) m_pDWrite_Text_Format->Release();
        m_pDWrite_Text_Format = NULL;
        if (m_pDWrite_Factory) m_pDWrite_Factory->Release();
        m_pDWrite_Factory = NULL;
        if (m_p2DFactory) m_p2DFactory->Release();
        m_p2DFactory = NULL;
        if (m_pSurface)m_pSurface->Release();
        m_pSurface = NULL;

    }
    void CADx_Text::Release_Fresh_Resource()
    {
        if (m_p2DRender_Target) m_p2DRender_Target->Release();
        m_p2DRender_Target = NULL;

        if (m_pBrush) m_pBrush->Release();
        m_pBrush = NULL;

    }

    void CADx_Text::Draw_Text(DXText& dxtext)
    {
        m_p2DRender_Target->BeginDraw();

        m_p2DRender_Target->SetTransform(dxtext.mat_world);
        if (dxtext.color.a != 0 || dxtext.color.b != 0 || dxtext.color.g != 0 || dxtext.color.r != 0)
        {
            m_pBrush->SetColor(dxtext.color);
        }
        if (dxtext.rt_f.top == 0 && dxtext.rt_f.left == 0 && dxtext.rt_f.bottom == 0 && dxtext.rt_f.right == 0)
        {
            dxtext.rt_f.bottom = g_rtClient.bottom;
            dxtext.rt_f.right = g_rtClient.right;

        }
        if (dxtext.pText_Format == nullptr)
        {
            dxtext.pText_Format = m_pDWrite_Text_Format;
        }
        m_p2DRender_Target->DrawText(dxtext.text.c_str(),
            dxtext.text.size(),
            dxtext.pText_Format, dxtext.rt_f,
            m_pBrush);

        m_p2DRender_Target->EndDraw();
    }


    void CADx_Text::Release()
    {
        Release_Once();
        Release_Fresh_Resource();
    }

    CADx_Text::CADx_Text(IDXGISwapChain* m_pSwap_Chain)
    {
        this->m_pSwap_Chain = m_pSwap_Chain;
    }



    CADx_Text::CADx_Text()
    {


    }


    CADx_Text::~CADx_Text()
    {
        Release();
    }
}
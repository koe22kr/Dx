#include "CADx_Text.h"

void CADx_Text::Init_Once()
{
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_p2DFactory);
    EM(hr, D2D1CreateFactory, CADx_Text);

    m_p2DFactory->GetDesktopDpi(&m_fDpiX, &m_fDpiY);
    m_fDpi_ScaleX = m_fDpiX / 96.0f;
    m_fDpi_ScaleY = m_fDpiY / 96.0f;

    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pDWrite_Factory);
    EM(hr, DWriteCreateFactory, CADx_Text);

    hr = m_pDWriteFactory->CreateTextFormat(
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

    hr = m_pSwap_Chain->GetBuffer(0, __uuidof(IDXGISurface), (void**)m_pSurface);
    EM(hr, GetBuffer, CADx_Text);

    hr = m_p2DFactory->CreateDxgiSurfaceRenderTarget(m_pSurface, RTP, &m_p2DRender_Target);
    EM(hr, CreateDxgiSurfaceRenderTarget, CADx_Text);

    hr = m_p2DRender_Target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Violet), &m_pViolet_Brush);
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
}
void CADx_Text::Release_Fresh_Resource()
{
    if (m_p2DRender_Target) m_p2DRender_Target->Release();
    m_p2DRender_Target = NULL;

    if (m_pViolet_Brush) m_pViolet_Brush->Release();
    m_pViolet_Brush = NULL;

}

void CADx_Text::Render(DXText dxtext)
{
    m_p2DRender_Target->BeginDraw();

    m_p2DRender_Target->SetTransform(dxtext.mat_world);
    m_pViolet_Brush->SetColor(dxtext.color);

    IDWriteTextFormat*   pText_Format = dxtext.pText_Format;
    if (pText_Format == nullptr)
    {
        pText_Format = m_pDWrite_Text_Format;
    }
    m_p2DRender_Target->DrawText(dxtext.text.c_str(),
        dxtext.text.size(),
        pText_Format, dxtext.rt_f,
        m_pViolet_Brush);

    m_p2DRender_Target->EndDraw();
}

void CADx_Text::Release()
{
    Release_Once();
    Release_Fresh_Resource();
}

CADx_Text::CADx_Text()
{


}


CADx_Text::~CADx_Text()
{
    Release();
}

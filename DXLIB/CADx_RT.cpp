#include "CADx_RT.h"
namespace DX
{
    CADx_RT* CADx_RT::Create(FLOAT Width, FLOAT Height, ID3D11Device* pdevice, const char* name)
    {
        m_szName = name;

        D3D11_TEXTURE2D_DESC td;
        ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
        td.Width = Width;
        td.Height = Height;
        td.MipLevels = 1;
        td.SampleDesc.Count = 1;
        td.SampleDesc.Quality = 0;

        td.ArraySize = 1;
        td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        
        td.Usage = D3D11_USAGE_DEFAULT;
        td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
        td.CPUAccessFlags = 0;
        td.MiscFlags = 0;

        pdevice->CreateTexture2D(&td, NULL, m_pTexture.GetAddressOf());
        pdevice->CreateShaderResourceView(m_pTexture.Get(), NULL, m_pSRV.GetAddressOf());
        pdevice->CreateRenderTargetView(m_pTexture.Get(), NULL, m_pRTV.GetAddressOf());

        td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        td.BindFlags = D3D11_BIND_DEPTH_STENCIL;

        pdevice->CreateTexture2D(&td, NULL, m_pDSTexture.GetAddressOf());

        D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
        ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
        dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        pdevice->CreateDepthStencilView(m_pDSTexture.Get(), &dsvd, m_pDSDSV.GetAddressOf());


        m_View_Port.TopLeftX = 0;
        m_View_Port.TopLeftY = 0;
        m_View_Port.Width = Width;
        m_View_Port.Height = Height;
        m_View_Port.MinDepth = 0;
        m_View_Port.MaxDepth = 1;

        return this;
    }

    bool CADx_RT::Clear(ID3D11DeviceContext* pContext, float r, float g, float b, float a)
    {
        float fColor[4] = { r,g,b,a };
        pContext->ClearRenderTargetView(m_pRTV.Get(), fColor);
        if (m_pDSDSV)
        {
            pContext->ClearDepthStencilView(m_pDSDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
        }
        return true;
    }
    bool CADx_RT::Set(ID3D11DeviceContext* pContext)
    {
       // pContext->RSSetViewports(1, NULL);
        pContext->RSSetViewports(1, &m_View_Port);
        //pContext->OMSetRenderTargets(1, NULL, NULL);
        pContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), m_pDSDSV.Get());

       /* pContext->RSSetViewports(m_nTarget_RT, NULL);
        pContext->RSSetViewports(m_nTarget_RT, &m_vpOLD);
        pContext->OMSetRenderTargets(m_nTarget_RT, NULL, NULL);
        pContext->OMSetRenderTargets(m_nTarget_RT, m_prtvOLD.GetAddressOf(), m_pdsvOLD.Get());*/
        
       
        
        return true;
    }

    bool CADx_RT::Release()
    {
        m_pTexture->Release();
        m_pDSTexture->Release();
        m_pSRV->Release();
        m_pRTV->Release();
        m_pDSDSV->Release();
        return true;
    }


    CADx_RT::CADx_RT()
    {
    }


    CADx_RT::~CADx_RT()
    {
    }
}
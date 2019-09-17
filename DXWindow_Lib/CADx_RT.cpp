#include "CADx_RT.h"
namespace DX
{
    HRESULT CADx_RT::Create(FLOAT Width, FLOAT Height, ID3D11Device* pdevice)
    {
        HRESULT hr = S_OK;
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


        m_vp.TopLeftX = 0;
        m_vp.TopLeftY = 0;
        m_vp.Width = Width;
        m_vp.Height = Height;
        m_vp.MinDepth = 0;
        m_vp.MaxDepth = 1;

        return hr;
    }
    bool CADx_RT::Begin(ID3D11DeviceContext* pContext)
    {
        m_nTarget_RT;
        pContext->RSGetViewports(&m_nTarget_RT, &m_vpOLD);
        pContext->OMGetRenderTargets(m_nTarget_RT, m_prtvOLD.GetAddressOf(), m_pdsvOLD.GetAddressOf());

        float fColor[] = { 0,0,0,0 };
        pContext->ClearRenderTargetView(m_pRTV.Get(), fColor);
        pContext->ClearDepthStencilView(m_pDSDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
        pContext->OMSetRenderTargets(m_nTarget_RT, NULL, NULL);
        pContext->OMSetRenderTargets(m_nTarget_RT, m_pRTV.GetAddressOf(), m_pDSDSV.Get());

        pContext->RSSetViewports(m_nTarget_RT, NULL);
        pContext->RSSetViewports(m_nTarget_RT, &m_vp);
        return true;
    }
    bool CADx_RT::End(ID3D11DeviceContext* pContext)
    {
        pContext->OMSetRenderTargets(m_nTarget_RT, NULL, NULL);
        pContext->RSSetViewports(m_nTarget_RT, NULL);

        pContext->OMSetRenderTargets(m_nTarget_RT, m_prtvOLD.GetAddressOf(), m_pdsvOLD.Get());
        pContext->RSSetViewports(m_nTarget_RT, &m_vpOLD);
        
        m_prtvOLD.Reset();
        m_pdsvOLD.Reset();
        
        return true;
    }

    bool CADx_RT::Release()
    {
        return true;
    }


    CADx_RT::CADx_RT()
    {
    }


    CADx_RT::~CADx_RT()
    {
    }
}
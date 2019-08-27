#include "CADx_State.h"


namespace Dx
{
    ID3D11BlendState* CADx_State::m_pAlpha_Blend = 0;
    ID3D11BlendState* CADx_State::m_pAlpha_Blend_Disable = 0;
    ID3D11RasterizerState* CADx_State::m_pRSWire_Frame = 0;
    ID3D11RasterizerState* CADx_State::m_pRSSolid_Frame = 0;
    ID3D11SamplerState* CADx_State::m_pSSWrap_Linear = 0;
    ///////////////////////

    void CADx_State::SetState(ID3D11Device* pDevice,ID3D11DeviceContext* pContext)
    {
        if (pDevice == nullptr|| pContext==nullptr) return;
        

        HRESULT hr;

#pragma region ID3D11SamplerState
        D3D11_SAMPLER_DESC sd;
        ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
        sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sd.MaxLOD = FLT_MAX;
        sd.MinLOD = FLT_MIN;
        if (FAILED(hr = pDevice->CreateSamplerState(
            &sd,
            &m_pSSWrap_Linear)))
        {
            return;
        }
#pragma endregion ID3D11SamplerState

#pragma region BLEND
        D3D11_BLEND_DESC ds;
        ZeroMemory(&ds, sizeof(D3D11_BLEND_DESC));
        ds.AlphaToCoverageEnable = TRUE;
        ds.IndependentBlendEnable = TRUE;
        ds.RenderTarget[0].BlendEnable = TRUE;
        ds.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        ds.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        ds.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

        ds.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        ds.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        ds.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

        ds.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


        if (FAILED(hr = pDevice->CreateBlendState(&ds,
            &m_pAlpha_Blend)))
        {
            return;
        }
        ds.RenderTarget[0].BlendEnable = FALSE;
        if (FAILED(hr = pDevice->CreateBlendState(&ds,
            &m_pAlpha_Blend_Disable)))
        {
            return;
        }
#pragma endregion			BLEND

#pragma region rasterizer
        //레스터라이즈 상태 객체 생성
        D3D11_RASTERIZER_DESC rsDesc;
        ZeroMemory(&rsDesc, sizeof(rsDesc));
        rsDesc.DepthClipEnable = TRUE;
        rsDesc.FillMode = D3D11_FILL_WIREFRAME;
        rsDesc.CullMode = D3D11_CULL_NONE;
        if (FAILED(hr =
            pDevice->CreateRasterizerState(&rsDesc, &m_pRSWire_Frame)))
        {
            return;
        }
        rsDesc.FillMode = D3D11_FILL_SOLID;
        if (FAILED(hr =
            pDevice->CreateRasterizerState(&rsDesc, &m_pRSSolid_Frame)))
        {
            return;
        }
#pragma endregion		RESTERIZER

        if(m_pSSWrap_Linear!=NULL)
        Set_SState(pContext, m_pSSWrap_Linear);
        if (m_pRSSolid_Frame != NULL)
        Set_RSState(pContext, m_pRSSolid_Frame);
        if (m_pAlpha_Blend != NULL)
        Set_BState(pContext, m_pAlpha_Blend);
    }

    ////////////////

    void CADx_State::Release()
    {
        if (m_pSSWrap_Linear)
            m_pSSWrap_Linear->Release();
        if (m_pAlpha_Blend)
            m_pAlpha_Blend->Release();

        if (m_pAlpha_Blend_Disable)
            m_pAlpha_Blend_Disable->Release();

        if (m_pRSWire_Frame)
            m_pRSWire_Frame->Release();
        if (m_pRSSolid_Frame)
            m_pRSSolid_Frame->Release();
        m_pSSWrap_Linear = 0;

        m_pAlpha_Blend = 0;
        m_pAlpha_Blend_Disable = 0;

        m_pRSWire_Frame = 0;
        m_pRSSolid_Frame = 0;

    }

  
    CADx_State::CADx_State()
    {
    }


    CADx_State::~CADx_State()
    {
    }
}
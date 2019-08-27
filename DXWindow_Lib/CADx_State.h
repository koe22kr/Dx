#pragma once
#include "D3D11.h"
#include <memory>

namespace Dx
{
    class CADx_State
    {
    public:
        //ID3D11BlendState
        static ID3D11BlendState*	m_pAlpha_Blend;
        static ID3D11BlendState*	m_pAlpha_Blend_Disable;

        //ID3D11RasterizerState
        static ID3D11RasterizerState*  m_pRSWire_Frame;
        static ID3D11RasterizerState*  m_pRSSolid_Frame;

        //ID3D11SamplerState*  
        static ID3D11SamplerState*   m_pSSWrap_Linear;

        
        static void SetState(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
        static void Release();
    public:
        CADx_State();
        virtual ~CADx_State();

    };

    static void Set_SState(ID3D11DeviceContext* pContext,
        ID3D11SamplerState* pState, UINT iSlot = 0, UINT iArray = 1)
    {
        pContext->PSSetSamplers(iSlot, iArray, &pState);
    };

    static void Set_RSState(ID3D11DeviceContext* pContext,
        ID3D11RasterizerState* pState)
    {
        pContext->RSSetState(pState);
    };
    static void Set_BState(ID3D11DeviceContext* pContext,
        ID3D11BlendState*	   pState,
        const FLOAT fBlendFactor[] = 0,
        UINT iMask = 0xffffffff)
    {
        pContext->OMSetBlendState(pState, fBlendFactor, iMask);
    };
}
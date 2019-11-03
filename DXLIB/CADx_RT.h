#pragma once

#include "CADx_Std.h"



namespace DX
{
    class CADx_RT
    {
        Microsoft::WRL::ComPtr<ID3D11Texture2D>          m_pTexture;
        Microsoft::WRL::ComPtr<ID3D11Texture2D>          m_pDSTexture;
    public:
        string m_szName;
        D3D11_VIEWPORT m_View_Port;
        
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView>   m_pRTV;

        Microsoft::WRL::ComPtr<ID3D11DepthStencilView>   m_pDSDSV;

    public:

        CADx_RT* Create(FLOAT Width, FLOAT Height, ID3D11Device* pdevice,const char* name);
        bool    Release();
        bool Clear(ID3D11DeviceContext* pContext, float r, float g, float b, float a);
        bool Set(ID3D11DeviceContext* pContext);


    public:
        CADx_RT();
        virtual ~CADx_RT();
    };

}
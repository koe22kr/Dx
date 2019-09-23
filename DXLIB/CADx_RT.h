#pragma once

#include "CADevice_Helper.h"


namespace DX
{
    class CADx_RT
    {
    public:
        

        Microsoft::WRL::ComPtr<ID3D11Texture2D>          m_pTexture;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView>   m_pRTV;

        Microsoft::WRL::ComPtr<ID3D11Texture2D>          m_pDSTexture;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView>   m_pDSDSV;

        UINT m_nTarget_RT = 1;
        D3D11_VIEWPORT m_vp;

        //UINT  m_iViewPorts; //하나만 담당하는 클래스로 사용
        D3D11_VIEWPORT m_vpOLD;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_prtvOLD;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pdsvOLD;

    public:
        HRESULT Create(FLOAT Width=g_rtClient.right, FLOAT Height=g_rtClient.bottom, ID3D11Device* pdevice = CADevice::m_pDevice);
        bool    Begin(ID3D11DeviceContext*    pContext=CADevice::m_pImmediate_Device_Context);
        bool    End(ID3D11DeviceContext*    pContext = CADevice::m_pImmediate_Device_Context);
        bool    Release();
    public:
        CADx_RT();
        virtual ~CADx_RT();
    };

}
#include "CADx_Light.h"

using namespace DX;

    bool CADx_Light::Init()
    {
        //m_Debug_Line.Create(CADevice::m_pDevice, L"../../_shader/line.hlsl", nullptr);
        
        m_cbLight.g_cAmbientMaterial = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

        m_cbLight.g_cDiffuseMaterial = D3DXVECTOR4(1, 1, 1, 1);
        m_cbLight.g_cSpecularMaterial = D3DXVECTOR4(1, 1, 1, 1);


        m_cbLight.g_cAmbientLightColor = D3DXVECTOR4(1, 1, 1, 1);
        m_cbLight.g_cDiffuseLightColor = D3DXVECTOR4(1, 1, 1, 1);
        m_cbLight.g_cSpecularLightColor = D3DXVECTOR4(1, 1, 1, 1);

        ID3D11Buffer* tempcb;
        
        m_shape_Obj.m_helper.m_pSRV = I_TextureMgr.GetPtr(I_TextureMgr.Load(CADevice::m_pDevice, L"../../_data/obj/lightmap.bmp"))->m_pSRV;

        I_DXHELPER.Create_Const_Buffer(tempcb, &m_cbLight, 1, sizeof(m_cbLight), CADevice::m_pDevice);
        m_pConstantBufferLight.Attach(tempcb);
        CreateResource();
        
        return true;
    }
    bool CADx_Light::Release()
    {
        return true;

    }

    bool CADx_Light::Frame(DX::TCamera* now_cam)
    {
        CADevice::m_pImmediate_Device_Context->PSSetShaderResources(1, 1, m_shape_Obj.m_helper.m_pSRV.GetAddressOf());
        float t = g_fSecondPerFrame * D3DX_PI;

        D3DXMATRIX mLightWorld, mTranslate, mRotation;
        D3DXMatrixTranslation(&mTranslate, 100.0f, 100.0f, 0.0f);
        D3DXMatrixRotationY(&mRotation, t * 0);
        D3DXMatrixMultiply(&mLightWorld, &mTranslate, &mRotation);

        m_vLightVector.x = mLightWorld._41;
        m_vLightVector.y = mLightWorld._42;
        m_vLightVector.z = mLightWorld._43;

        D3DXVec3Normalize(&m_vLightVector, &m_vLightVector);
        m_vLightVector *= -1.0f;


        /////////////
        angleyaw += g_fSecondPerFrame;

        D3DXMATRIX matWorld, matScale;
        matWorld._43 = 5.0f;
        matWorld._42 = 5.0f;

        D3DXMatrixScaling(&matScale, 100, 100, 100);
        D3DXMatrixRotationY(&matWorld, angleyaw);
        D3DXMatrixMultiply(&matWorld, &matScale, &matWorld);

        D3DXVECTOR4 temp;
        D3DXVec3Transform(&temp, &m_vLightVector, &matWorld);
        ///

        m_cbLight.g_vLightDir.x = temp.x;
        m_cbLight.g_vLightDir.y = temp.y;
        m_cbLight.g_vLightDir.z = temp.z;
        m_cbLight.g_vLightDir.w = 1;

        D3DXMATRIX matInvWorld;
        D3DXMatrixIdentity(&matInvWorld);
        D3DXMatrixInverse(&matInvWorld, NULL, &matWorld);
        D3DXMatrixTranspose(&matInvWorld, &matInvWorld);
        D3DXMatrixTranspose(&m_cbLight.g_matInvWorld, &matInvWorld);

        m_cbLight.g_vEyeDir.x = now_cam->m_vLookVector.x;
        m_cbLight.g_vEyeDir.y = now_cam->m_vLookVector.y;
        m_cbLight.g_vEyeDir.z = now_cam->m_vLookVector.z;
        m_cbLight.g_vEyeDir.w = 0.1f; // ºûÀÇ ¹à±â °­µµ
        m_cbLight.g_cSpecularMaterial = D3DXVECTOR4(0.5, 0.5, 0.5, 1);

        CADevice::m_pImmediate_Device_Context->VSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());
        CADevice::m_pImmediate_Device_Context->PSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());

        D3DXMatrixIdentity(&m_cbLight.g_matInvWorld);
        CADevice::m_pImmediate_Device_Context->UpdateSubresource(m_pConstantBufferLight.Get(), 0, NULL, &m_cbLight, 0, 0);
        return true;
    }

    //--------------------------------------------------------------------------------------
    // 
    //--------------------------------------------------------------------------------------
    HRESULT CADx_Light::CreateResource()
    {
        /*  HRESULT hr;
          if (m_pMain_Cam != nullptr)
              m_pMain_Cam->SetProjMatrix((float)D3DX_PI * 0.25f,
                  m_Device.m_Swap_Chain_Desc.BufferDesc.Width / (FLOAT)m_Device.m_Swap_Chain_Desc.BufferDesc.Height, 1.0f, 1000.0f);*/
        return S_OK;
    }
    //--------------------------------------------------------------------------------------
    // 
    //--------------------------------------------------------------------------------------



    CADx_Light::CADx_Light()
    {
    }


    CADx_Light::~CADx_Light()
    {
    }

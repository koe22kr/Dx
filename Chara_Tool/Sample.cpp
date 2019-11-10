#include "stdafx.h"
#include "Sample.h"


void Sample::SetBlendState(D3D11_BLEND_DESC* pBD)
{
    HRESULT hr;
    if (m_pBlendState) m_pBlendState->Release();

    if (pBD == nullptr)
    {
        ZeroMemory(&m_BlendDesc, sizeof(D3D11_BLEND_DESC));
        m_BlendDesc.AlphaToCoverageEnable = FALSE;
        m_BlendDesc.IndependentBlendEnable = TRUE;
        m_BlendDesc.RenderTarget[0].BlendEnable = TRUE;
        m_BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        m_BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        m_BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

        m_BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        m_BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        m_BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

        m_BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    }
    else
    {
        m_BlendDesc = *pBD;
    }

    if (FAILED(hr = m_Device.m_pDevice->CreateBlendState(
        &m_BlendDesc, &m_pBlendState)))
    {
        EM(hr, SetBlendState, Sample);
        return;
    }
}
void Sample::SetRasterizerState(D3D11_RASTERIZER_DESC* pRD)
{
    HRESULT hr;
    if (pRD == nullptr)
    {
        ZeroMemory(&m_RasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
        m_RasterizerDesc.DepthClipEnable = TRUE;
        m_RasterizerDesc.FillMode = D3D11_FILL_SOLID;
        m_RasterizerDesc.CullMode = D3D11_CULL_NONE;
        m_RasterizerDesc.MultisampleEnable = TRUE;
        m_RasterizerDesc.AntialiasedLineEnable = TRUE;
    }
    else
    {
        m_RasterizerDesc = *pRD;
    }
    
    if (FAILED(hr =
        m_Device.m_pDevice->CreateRasterizerState(&m_RasterizerDesc, &m_pRasterizerState)))
    {
        EM(hr, SetRasterizerState, Sample);
        return;
    }
}
void Sample::SetSamplerState(D3D11_SAMPLER_DESC* pSD)
{
    HRESULT hr;
    if (pSD == nullptr)
    {
        ZeroMemory(&m_SamplerDesc, sizeof(D3D11_SAMPLER_DESC));
        m_SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        m_SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        m_SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        m_SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        m_SamplerDesc.MaxLOD = FLT_MAX;
        m_SamplerDesc.MinLOD = FLT_MIN;
        m_SamplerDesc.MaxAnisotropy = 16;
    }
    else
    {
        m_SamplerDesc = *pSD;
    }

    if (FAILED(hr = m_Device.m_pDevice->CreateSamplerState(&m_SamplerDesc, &m_pSamplerState)))
    {
        EM(hr, SetSamplerState, Sample);
        return;
    }
}
void Sample::SetDepthStencilState(D3D11_DEPTH_STENCIL_DESC* pDSD)
{
    HRESULT hr = S_OK;
    if (pDSD == nullptr)
    {
        ZeroMemory(&m_DepthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
        m_DepthStencilDesc.DepthEnable = TRUE;
        m_DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
        m_DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    }
    else
    {
        m_DepthStencilDesc = *pDSD;
    }

    if (FAILED(hr = CADevice::m_pDevice->CreateDepthStencilState(&m_DepthStencilDesc, &m_pDepthStencilState)))
    {
        EM(hr, SetDepthStencilState, Sample);
        return;
    }

    
}


HRESULT TPlaneObject::CreateVertexData()
{
    m_Vertex_List.resize(4);
    m_Vertex_List[0].p = *(DirectX::XMFLOAT3*)&D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
    m_Vertex_List[0].n = *(DirectX::XMFLOAT3*)&D3DXVECTOR3(0.0f, 0.0f, -10.0f);
    m_Vertex_List[0].c = *(DirectX::XMFLOAT4*)&D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
    m_Vertex_List[0].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(0.0f, 0.0f);

    m_Vertex_List[1].p = *(DirectX::XMFLOAT3*)&D3DXVECTOR3(10.0f, 10.0f, 0.0f);
    m_Vertex_List[1].n = *(DirectX::XMFLOAT3*)&D3DXVECTOR3(0.0f, 0.0f, -10.0f);
    m_Vertex_List[1].c = *(DirectX::XMFLOAT4*)&D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
    m_Vertex_List[1].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(1.0f, 0.0f);

    m_Vertex_List[2].p = *(DirectX::XMFLOAT3*)&D3DXVECTOR3(10.0f, -10.0f, 0.0f);
    m_Vertex_List[2].n = *(DirectX::XMFLOAT3*)&D3DXVECTOR3(0.0f, 0.0f, -10.0f);
    m_Vertex_List[2].c = *(DirectX::XMFLOAT4*)&D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
    m_Vertex_List[2].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(1.0f, 0.5f);

    m_Vertex_List[3].p = *(DirectX::XMFLOAT3*)&D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
    m_Vertex_List[3].n = *(DirectX::XMFLOAT3*)&D3DXVECTOR3(0.0f, 0.0f, -10.0f);
    m_Vertex_List[3].c = *(DirectX::XMFLOAT4*)&D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
    m_Vertex_List[3].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(0.0f, 0.5f);
    return S_OK;
}
HRESULT TPlaneObject::CreateIndexData()
{
    m_Index_List.resize(6);
    m_Index_List[0] = 1;
    m_Index_List[1] = 2;
    m_Index_List[2] = 0;

    m_Index_List[3] = 2;
    m_Index_List[4] = 3;
    m_Index_List[5] = 0;
    return S_OK;
}


TPlaneObject::TPlaneObject()
{

}

TPlaneObject::~TPlaneObject()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////
bool Sample::Init()
{
 /*   m_Render_List.m_Effect_Vertex_List.resize(MAX_EFFECT);
    m_Render_List.Create_Render_Obj(CADevice::m_pDevice,L"effect.hlsl");
    m_Render_List.Add();*/
    m_Plane.Create(CADevice::m_pDevice, L"effect.hlsl", L"../../_data/obj/attack_damage_01.dds");

    SetSamplerState(nullptr);
    SetDepthStencilState(nullptr);
    SetRasterizerState(nullptr);
    SetBlendState(nullptr);
    
    return true;
}
bool Sample::Frame()
{

    m_Render_List.Update_Buffer();

    static float tTime = 0.0f;
    tTime += g_fSecondPerFrame;
    if (tTime > 1.1f)
    {
        m_Render_List.Add();
        tTime -= 1.1f;
    }

    return true;

}
bool Sample::Render()
{
    DX::Set_BState(m_Device.m_pImmediate_Device_Context, m_pBlendState);
   DX::Set_DSState(m_Device.m_pImmediate_Device_Context, m_pDepthStencilState);
    DX::Set_RSState(m_Device.m_pImmediate_Device_Context, m_pRasterizerState);
    DX::Set_SState(m_Device.m_pImmediate_Device_Context, m_pSamplerState);

    
    // 복수 오브젝트시 함수화
    D3DXMATRIX matBillboard, Scale, Rot,Trans,matFinal;
    D3DXMatrixIdentity(&matBillboard);
    D3DXMatrixIdentity(&Scale);
    D3DXMatrixIdentity(&Rot);

    D3DXMatrixInverse(&matBillboard, NULL,
        &m_pMain_Cam->m_matView);
    matBillboard._41 = 0.0f;
    matBillboard._42 = 0.0f;
    matBillboard._43 = 0.0f;
    D3DXMatrixScaling(&Scale, m_Render_List.m_Base_Effect.m_vScale.x, m_Render_List.m_Base_Effect.m_vScale.y, m_Render_List.m_Base_Effect.m_vScale.z);
    D3DXMatrixRotationYawPitchRoll(&Rot,m_Render_List.m_Base_Effect.m_vRotation.y, m_Render_List.m_Base_Effect.m_vRotation.x, m_Render_List.m_Base_Effect.m_vRotation.z);
    
    
    D3DXMatrixTranslation(&Trans, m_Render_List.m_Base_Effect.m_vPos.x, m_Render_List.m_Base_Effect.m_vPos.y, m_Render_List.m_Base_Effect.m_vPos.z);


    matBillboard = Scale * Rot * Trans * matBillboard;

    //


    for (int a = 0; a < m_Render_List.m_Effect_Vertex_List.size(); a++)
    {
      
        D3DXVECTOR3 TargetVector;
        TargetVector.x = (m_Render_List.m_Base_Effect.m_vTargetPos.x - m_Render_List.m_Effect_Vertex_List[a].m_vPos.x);
        TargetVector.y = (m_Render_List.m_Base_Effect.m_vTargetPos.y - m_Render_List.m_Effect_Vertex_List[a].m_vPos.y);
        TargetVector.z = (m_Render_List.m_Base_Effect.m_vTargetPos.z - m_Render_List.m_Effect_Vertex_List[a].m_vPos.z);
        D3DXVec3Normalize(&TargetVector, &TargetVector);

        D3DXVECTOR3 Power;
        Power.x = (m_Render_List.m_Base_Effect.m_vPower1.x + m_Render_List.m_Base_Effect.m_vPower2.x +m_Render_List.m_Base_Effect.m_vPower3.x);
        Power.y = (m_Render_List.m_Base_Effect.m_vPower1.y + m_Render_List.m_Base_Effect.m_vPower2.y +m_Render_List.m_Base_Effect.m_vPower3.y);
        Power.z = (m_Render_List.m_Base_Effect.m_vPower1.z + m_Render_List.m_Base_Effect.m_vPower2.z +m_Render_List.m_Base_Effect.m_vPower3.z);

        matFinal = matBillboard;
        

        m_Render_List.m_Effect_Vertex_List[a].m_vPos.x += (TargetVector.x*m_Render_List.m_Base_Effect.m_fSpeed_to_Target + Power.x)*g_fSecondPerFrame;
        m_Render_List.m_Effect_Vertex_List[a].m_vPos.y += (TargetVector.y*m_Render_List.m_Base_Effect.m_fSpeed_to_Target + Power.y)*g_fSecondPerFrame;
        m_Render_List.m_Effect_Vertex_List[a].m_vPos.z += (TargetVector.z*m_Render_List.m_Base_Effect.m_fSpeed_to_Target + Power.z)*g_fSecondPerFrame;

        matFinal._41 += m_Render_List.m_Effect_Vertex_List[a].m_vPos.x;
        matFinal._42 += m_Render_List.m_Effect_Vertex_List[a].m_vPos.y;
        matFinal._43 += m_Render_List.m_Effect_Vertex_List[a].m_vPos.z;
        
        static float temp;
        temp = m_Render_List.m_Effect_Vertex_List[a].m_vPos.x + (TargetVector.x*m_Render_List.m_Base_Effect.m_fSpeed_to_Target+ Power.x)*g_fSecondPerFrame;
        Set_Alpha(m_Render_List.m_Effect_Vertex_List[a].m_Alpha, &m_Plane);
        Get_UV(m_iCut_Num, m_iCut_Num, m_Render_List.m_Effect_Vertex_List[a].m_iTexID, &m_Plane);

        CADevice::m_pImmediate_Device_Context->UpdateSubresource(m_Plane.m_helper.m_pVertexBuffer.Get(), 0, 0, &m_Plane.m_Vertex_List.at(0), 0, 0);
        m_Plane.SetMatrix(&matFinal, &m_pMain_Cam->m_matView, &m_pMain_Cam->m_matProj);

        m_Plane.Render(CADevice::m_pImmediate_Device_Context);

    }
    return true;

}
bool Sample::Release()
{


    return true;
}

Sample::Sample()
{
}


Sample::~Sample()
{
}

void Sample::Get_UV(int cutx, int cuty, int& texnum, TPlaneObject* m_pplane)
{
    float x = 1.0f / cutx;
    float y = 1.0f / cuty;
    if (cutx*cutx  <= texnum)
    {
        m_pplane->m_Vertex_List[0].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(0.0f, 0.0f);
        m_pplane->m_Vertex_List[1].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x, 0.0f);
        m_pplane->m_Vertex_List[2].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x, y);
        m_pplane->m_Vertex_List[3].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(0.0f, y);
        texnum = 0;
    }
    for (int i = 0; i < cuty; i++)
    {
        for (int j = 0; j < cutx; j++)
        {
            if (cutx*i + j == texnum)
            {
                D3DXVECTOR2 temp;
                m_pplane->m_Vertex_List[0].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x*j, y*i);
                m_pplane->m_Vertex_List[1].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x*(j+1), y*i);
                m_pplane->m_Vertex_List[2].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x*(j + 1), y*(i+1));
                m_pplane->m_Vertex_List[3].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x*j, y*(i + 1));
            }
        }
    }
}
void Sample::Set_Alpha(float m_Alpha, TPlaneObject* m_pplane)
{
    m_pplane->m_Vertex_List[0].c.w = m_Alpha;
    m_pplane->m_Vertex_List[1].c.w = m_Alpha;
    m_pplane->m_Vertex_List[2].c.w = m_Alpha;
    m_pplane->m_Vertex_List[3].c.w = m_Alpha;
}

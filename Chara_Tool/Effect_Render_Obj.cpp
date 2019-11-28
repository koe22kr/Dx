#include "stdafx.h"
#include "Effect_Render_Obj.h"
#include "TCamera.h"

void Effect_Render_Obj::SetBlendState(D3D11_BLEND_DESC* pBD)
{
    HRESULT hr;
    if (m_pBlendState) m_pBlendState->Release();

    if (pBD == nullptr)
    {
        ZeroMemory(&m_BlendDesc, sizeof(D3D11_BLEND_DESC));
        m_BlendDesc.AlphaToCoverageEnable = FALSE;
        m_BlendDesc.IndependentBlendEnable = FALSE;
        m_BlendDesc.RenderTarget[0].BlendEnable = TRUE;
        m_BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        m_BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        m_BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

        m_BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        m_BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        m_BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

        m_BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    }
    else if(pBD!= &m_BlendDesc)
    {
        m_BlendDesc = *pBD;
    }

    if (FAILED(hr = CADevice::m_pDevice->CreateBlendState(
        &m_BlendDesc, &m_pBlendState)))
    {
        EM(hr, SetBlendState, Sample);
        return;
    }
    else
    {
        return;

    }
    return;

}
void Effect_Render_Obj::SetRasterizerState(D3D11_RASTERIZER_DESC* pRD)
{
    HRESULT hr;
    if (m_pRasterizerState) m_pRasterizerState->Release();
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
        CADevice::m_pDevice->CreateRasterizerState(&m_RasterizerDesc, &m_pRasterizerState)))
    {
        EM(hr, SetRasterizerState, Sample);
        return;
    }
}
void Effect_Render_Obj::SetSamplerState(D3D11_SAMPLER_DESC* pSD)
{
    HRESULT hr;
    if (m_pSamplerState) m_pSamplerState->Release();

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
        m_SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        m_SamplerDesc.MipLODBias = 0;
    }
    else
    {
        m_SamplerDesc = *pSD;
    }
    if (FAILED(hr = CADevice::m_pDevice->CreateSamplerState(&m_SamplerDesc, &m_pSamplerState)))
    {
        EM(hr, SetSamplerState, Sample);
        return;
    }
}
void Effect_Render_Obj::SetDepthStencilState(D3D11_DEPTH_STENCIL_DESC* pDSD)
{
    HRESULT hr = S_OK;
    if (m_pDepthStencilState) m_pDepthStencilState->Release();

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
////////////////////////////////


HRESULT Effect_Render_Obj::LoadShaderFile(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile)
{
    HRESULT hr = S_OK;
    CADx_Model2::LoadShaderFile(pd3dDevice, pLoadShaderFile);

    m_pFrameVS.Attach(DX::LoadVertexShaderFile(pd3dDevice, pLoadShaderFile, nullptr, "VS_FRAME"));
    Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
    m_pFrameGS.Attach(DX::LoadGeometryShaderFile(pd3dDevice, pLoadShaderFile, pBlob.GetAddressOf(), "GS_FRAME"));

    D3D11_SO_DECLARATION_ENTRY decl[] =
    {
        {0,"DELTATIME", 0, 0, 1, 0},
        {0,"TEXCOORD", 0, 0, 4, 0},
        {0,"POSITION", 0, 0, 3, 0},
        {0,"TEXID", 0, 0, 1, 0},
    {0,"TYPE",0,0,1,0},
        {0,"ALPHA",0,0,1,0},


    };
    UINT elems = sizeof(decl) / sizeof(D3D11_SO_DECLARATION_ENTRY);
    UINT stride[] = { sizeof(Effect_VB) };
   
    hr = pd3dDevice->CreateGeometryShaderWithStreamOutput(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), decl, elems, stride, 1, D3D11_SO_NO_RASTERIZED_STREAM, NULL, m_pGS_Stream_Output.GetAddressOf());

    return hr;

}
HRESULT Effect_Render_Obj::SetInputLayout()
{
    HRESULT hr = S_OK;
    //input layout
    //정점버퍼의 데이터를 정점 쉐이더의 인자값으로 설정
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
       
        {"DELTATIME", 0, DXGI_FORMAT_R32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0  },
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4, D3D11_INPUT_PER_VERTEX_DATA, 0  },
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXID", 0, DXGI_FORMAT_R32_UINT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TYPE", 0, DXGI_FORMAT_R32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"ALPHA", 0, DXGI_FORMAT_R32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0},

    };

    int iNumElement = sizeof(layout) / sizeof(layout[0]);
    m_helper.m_pInputLayout.Attach(
        DX::CreateInputLayout(m_pDevice,
            m_helper.m_pVSBlob->GetBufferSize(),
            m_helper.m_pVSBlob->GetBufferPointer(),
            layout, iNumElement));
    
    return hr;
}

HRESULT Effect_Render_Obj::CreateVertexData()
{
    return S_OK;
}
HRESULT Effect_Render_Obj::CreateIndexData()
{
    return S_OK;

}
HRESULT Effect_Render_Obj::CreateVertexBuffer()
{
   // if (m_Effect_Instance_List.size() <= 0)  return S_OK;
    HRESULT hr = S_OK;

    m_helper.m_iVertexSize = sizeof(Effect_VB);
    m_helper.m_iNumVertex = 1;
    m_helper.m_pVertexBuffer.Attach(
        DX::CreateVertexBuffer(m_pDevice,
            &m_Effect_Vertex_Data, m_helper.m_iNumVertex, m_helper.m_iVertexSize));
    if (m_helper.m_pVertexBuffer.Get() == nullptr)
        return false;
    //////////////////

    ID3D11Buffer* pBuffer = nullptr;
    D3D11_BUFFER_DESC bd;

    bd.ByteWidth = MAX_EFFECT * sizeof(Effect_VB);
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER| D3D11_BIND_STREAM_OUTPUT;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    bd.StructureByteStride = 0;
    
    if (FAILED(hr = m_pDevice->CreateBuffer(
        &bd, NULL, &m_pEffect_SO_Output_buffer)))
    {
        return 0;
    }
    if (FAILED(hr = m_pDevice->CreateBuffer(
        &bd, NULL, &m_pEffect_Draw_buffer)))
    {
        return 0;
    }

    return hr;
}

HRESULT Effect_Render_Obj::CreateConstantBuffer()
{
    //// TODO 수정 필요 할 수가 있음.
    HRESULT hr = S_OK;

    VS_CB2 vc;
    ZeroMemory(&vc, sizeof(VS_CB2));
    vc.matWorld = DirectX::XMMatrixIdentity();
    vc.matView = m_matView;
    vc.matProj = m_matProj;
    vc.etc[0] = 0.0f;

    m_helper.m_pConstantBuffer.Attach(
        DX::CreateConstantBuffer(m_pDevice,
            &vc, 1, sizeof(VS_CB2), false)
    );
    if (m_helper.m_pConstantBuffer.Get() == nullptr)
        return false;

    m_pEffectConstantBuffer.Attach(DX::CreateConstantBuffer(m_pDevice, &m_data.m_Base_CB, 1, sizeof(Effect_CB), false));
    if (m_pEffectConstantBuffer.Get() == nullptr)
        return false;

    return hr;
}

HRESULT Effect_Render_Obj::CreateIndexBuffer()
{
    return S_OK;

}
//HRESULT Effect_Render_Obj::LoadTextures(ID3D11Device* pd3dDevice, const TCHAR* pLoadTextureFile)
//{
//    return S_OK;
//}

Effect_Render_Obj::Effect_Render_Obj()
{
    D3DXMatrixIdentity(&m_matbill);
    m_pSamplerState = NULL;
    m_pRasterizerState = NULL;
    m_pDepthStencilState = NULL;
    m_pBlendState = NULL;
  //  m_iTex = -1;
    m_pImmediateContext = CADevice::m_pImmediate_Device_Context;
    m_bFirst = true;
  //  m_Add_Time = 1.0f;
}
Effect_Render_Obj::~Effect_Render_Obj()
{
}

bool Effect_Render_Obj::InitState(bool bLoad)
{
   // m_data.m_State;
    if (bLoad)
    {
        //D3D11_BLEND_DESC
        //D3D11_BLEND_DESC bd;
        ZeroMemory(&m_BlendDesc, sizeof(D3D11_BLEND_DESC));
        m_BlendDesc.AlphaToCoverageEnable = FALSE;
        m_BlendDesc.IndependentBlendEnable = FALSE;
        m_BlendDesc.RenderTarget[0].BlendEnable = (BOOL)m_data.m_State.blend[0];//1
        m_BlendDesc.RenderTarget[0].SrcBlend = (D3D11_BLEND)m_data.m_State.blend[1];//2
        m_BlendDesc.RenderTarget[0].DestBlend = (D3D11_BLEND)m_data.m_State.blend[2];//3
        m_BlendDesc.RenderTarget[0].BlendOp = (D3D11_BLEND_OP)m_data.m_State.blend[3];//4
        m_BlendDesc.RenderTarget[0].SrcBlendAlpha = (D3D11_BLEND)m_data.m_State.blend[4];//5
        m_BlendDesc.RenderTarget[0].DestBlendAlpha = (D3D11_BLEND)m_data.m_State.blend[5];//6
        m_BlendDesc.RenderTarget[0].BlendOpAlpha = (D3D11_BLEND_OP)m_data.m_State.blend[6];//7
        m_BlendDesc.RenderTarget[0].RenderTargetWriteMask = m_data.m_State.blend[7];//8
        SetBlendState(&m_BlendDesc);
      

        //D3D11_RASTERIZER_DESC
        D3D11_RASTERIZER_DESC rd;
        ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
        rd.DepthClipEnable = TRUE;
        rd.FillMode = (D3D11_FILL_MODE)m_data.m_State.rasterizer[0];
        rd.CullMode = (D3D11_CULL_MODE)m_data.m_State.rasterizer[1];
        rd.MultisampleEnable = TRUE;
        rd.AntialiasedLineEnable = TRUE;
        SetRasterizerState(&rd);

        //D3D11_SAMPLER_DESC
        D3D11_SAMPLER_DESC sd;
        ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
        sd.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)m_data.m_State.sampler[1];
        sd.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)m_data.m_State.sampler[2];
        sd.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)m_data.m_State.sampler[3];
        sd.Filter = (D3D11_FILTER)m_data.m_State.sampler[0];
        sd.MaxLOD = FLT_MAX;
        sd.MinLOD = FLT_MIN;
        sd.MaxAnisotropy = 16;
        sd.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        sd.MipLODBias = 0;
        SetSamplerState(&sd);

        //D3D11_DEPTH_STENCIL_DESC
        D3D11_DEPTH_STENCIL_DESC dd;
        ZeroMemory(&dd, sizeof(D3D11_DEPTH_STENCIL_DESC));
        dd.DepthEnable = (BOOL)m_data.m_State.depthstencil[0];
        dd.DepthFunc = (D3D11_COMPARISON_FUNC)m_data.m_State.depthstencil[2];
        dd.DepthWriteMask = (D3D11_DEPTH_WRITE_MASK)m_data.m_State.depthstencil[1];
        SetDepthStencilState(&dd);


        

    }
    else
    {
        SetSamplerState(nullptr);
        SetDepthStencilState(nullptr);
        SetRasterizerState(nullptr);
        SetBlendState(nullptr);
    }
    
    return true;
}
bool  Effect_Render_Obj::Create(ID3D11Device* pd3dDevice,
    const TCHAR* pLoadShaderFile,
    const TCHAR* pLoadTextureFile, bool bLoad)
{
    
    CADx_Model2::Create(pd3dDevice, pLoadShaderFile, pLoadTextureFile);
    InitState(bLoad);
    return true;
}
bool Effect_Render_Obj::Frame()
{
    if (!m_bRend)
    {
        return false;
    }
    m_cb.etc[0] = g_fSecondPerFrame;
    if (m_helper.m_pConstantBuffer != NULL)
    {
        m_pImmediateContext->UpdateSubresource(
            m_helper.m_pConstantBuffer.Get(),
            0, NULL, &m_cb, 0, 0);
    }
    Update();
    ID3D11Buffer* pBuffer;
    if (m_bFirst)
    {
        pBuffer = m_helper.m_pVertexBuffer.Get();
    }
    else
    {
        pBuffer = m_pEffect_Draw_buffer.Get();
    }

    m_pImmediateContext->UpdateSubresource(m_pEffectConstantBuffer.Get(), 0, NULL, &m_data.m_Base_CB, 0, 0);

    UINT stride[] = {sizeof(Effect_VB) };
    UINT offset[] = { 0 };

    m_pImmediateContext->IASetVertexBuffers(0, 1, &pBuffer, stride, offset);
    m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    m_pImmediateContext->IASetInputLayout(m_helper.m_pInputLayout.Get());
    m_pImmediateContext->GSSetConstantBuffers(0, 1, m_helper.m_pConstantBuffer.GetAddressOf());
    m_pImmediateContext->GSSetConstantBuffers(2, 1, m_pEffectConstantBuffer.GetAddressOf());
    m_pImmediateContext->GSSetShader(m_pGS_Stream_Output.Get(), NULL, 0);
    m_pImmediateContext->VSSetShader(m_pFrameVS.Get(), NULL, 0);
    m_pImmediateContext->PSSetShader(NULL, NULL, 0);
    m_pImmediateContext->SOSetTargets(1, m_pEffect_SO_Output_buffer.GetAddressOf(), offset);

    if (m_bFirst)
    {
        m_pImmediateContext->Draw(1, 0);
        m_bFirst = false;
    }
    else
    {
       ID3D11Query* pQuery;
       D3D11_QUERY_DESC desc;
       desc.Query = D3D11_QUERY_SO_STATISTICS;
       desc.MiscFlags = 0;
       m_pDevice->CreateQuery(&desc, &pQuery);
       
       m_pImmediateContext->Begin(pQuery);
        m_pImmediateContext->DrawAuto();
       m_pImmediateContext->End(pQuery);
       
       D3D11_QUERY_DATA_SO_STATISTICS stat;
       while (S_OK != m_pImmediateContext->GetData(pQuery,
           &stat, pQuery->GetDataSize(), 0));
       pQuery->Release();

    }
    m_pEffect_Draw_buffer.Swap(m_pEffect_SO_Output_buffer);

    pBuffer = NULL;
    m_pImmediateContext->SOSetTargets(1, &pBuffer, offset);

    return true;
}
bool Effect_Render_Obj::Render()
{
    if (!m_bRend)
    {
        return false;
    }

    DX::Set_BState(CADevice::m_pImmediate_Device_Context, m_pBlendState);
    DX::Set_DSState(CADevice::m_pImmediate_Device_Context, m_pDepthStencilState);
    DX::Set_RSState(CADevice::m_pImmediate_Device_Context, m_pRasterizerState);
    DX::Set_SState(CADevice::m_pImmediate_Device_Context, m_pSamplerState);

    
    m_pImmediateContext->GSSetConstantBuffers(0, 1,
        m_helper.m_pConstantBuffer.GetAddressOf());

    m_pImmediateContext->GSSetConstantBuffers(2, 1,
            m_pEffectConstantBuffer.GetAddressOf());

    m_pImmediateContext->PSSetConstantBuffers(2, 1,
        m_pEffectConstantBuffer.GetAddressOf());
    
    if (m_helper.m_pSRV) {

        m_pImmediateContext->PSSetShaderResources(0, 1,
            m_helper.m_pSRV.GetAddressOf());
    }
    // pContext->PSSetShaderResources(1, 1, m_pSRV.GetAddressOf());
    m_pImmediateContext->IASetInputLayout(m_helper.m_pInputLayout.Get());
    if (m_helper.m_pVertexShader) {

        m_pImmediateContext->VSSetShader(m_helper.m_pVertexShader.Get(), NULL, 0);
    }
    if (m_helper.m_pPixelShader) {
        m_pImmediateContext->PSSetShader(m_helper.m_pPixelShader.Get(), NULL, 0);
    }
    if (m_helper.m_pGeometryShader)
    {
        m_pImmediateContext->GSSetShader(m_helper.m_pGeometryShader.Get(), NULL, 0);
    }
    UINT stride = sizeof(Effect_VB);
    UINT offset = 0;
    if (m_pEffect_Draw_buffer)
    {
        m_pImmediateContext->IASetVertexBuffers(0, 1,
            m_pEffect_Draw_buffer.GetAddressOf(),
            &stride, &offset);
    }
   
    m_pImmediateContext->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

   // m_pImmediateContext->Draw(1, 0);
    //{
    //    ID3D11Query* pQuery;
    //    D3D11_QUERY_DESC desc;
    //    desc.Query = D3D11_QUERY_SO_STATISTICS;
    //    desc.MiscFlags = 0;
    //    m_pDevice->CreateQuery(&desc, &pQuery);
    //
    //    m_pImmediateContext->Begin(pQuery);
        m_pImmediateContext->DrawAuto();
    //    m_pImmediateContext->End(pQuery);
    //
    //    D3D11_QUERY_DATA_SO_STATISTICS stat;
    //    while (S_OK != m_pImmediateContext->GetData(pQuery,
    //        &stat, pQuery->GetDataSize(), 0));
    //    pQuery->Release();
    //}
    return true;
}



//
//void Effect_Render_Obj::Update_Buffer()
//{
//   
//    std::vector<Effect_Data>::iterator iter;
//    for (iter= m_Effect_Vertex_List.begin(); iter != m_Effect_Vertex_List.end();)
//    {
//
//
//        iter->m_Delta_Time += g_fSecondPerFrame;
//        if (iter->m_Delta_Time >= 0.1)
//        {
//            iter->m_iTexID++;
//            iter->m_Delta_Time -= 0.1;
//        }
//
//        if (iter->m_fFadeInDeltaTime > 0.0f)
//        {
//            iter->m_fFadeInDeltaTime -= g_fSecondPerFrame;
//            iter->m_Alpha += 1 / iter->m_fFadeInTime*g_fSecondPerFrame;
//            if (iter->m_Alpha > 1.0f)iter->m_Alpha = 1.0f;
//        }
//        else
//        {
//            if (iter->m_Life_Time > 0.0f)
//            {
//                iter->m_Life_Time -= g_fSecondPerFrame;
//            }
//            else
//            {
//                if (iter->m_fFadeOutTime > 0)
//                {
//                    iter->m_fFadeOutDeltaTime -= g_fSecondPerFrame;
//                    iter->m_Alpha -= 1 / iter->m_fFadeOutTime*g_fSecondPerFrame;
//                    if (iter->m_Alpha < 0.0f)iter->m_Alpha = 0.0f;
//                }
//            }
//
//
//            
//            
//        }
//        if (iter->m_fFadeOutTime <= 0 && iter->m_Life_Time <= 0)
//        {
//            iter = m_Effect_Vertex_List.erase(iter);
//        }
//        else
//        {
//            iter++;
//
//        }
//        
//    }
//      //  m_Effect_Instance_List[ibuffer].m_matWorld = matRotation * matTrans;
//        //TODO 추가적인 VB 계산 필요할
//                //D3DXMATRIX matWorld, matTrans, matRotation, matScale;
//        ////D3DXMatrixInverse(&matRotation, NULL, &m_cur_cam->m_matView);
//        //matRotation._41 = 0.0f;
//        //matRotation._42 = 0.0f;
//        //matRotation._43 = 0.0f;
//        //matRotation._44 = 1.0f;
//   // D3D11_MAPPED_SUBRESOURCE sub;
//   // if (SUCCEEDED(CADevice::m_pImmediate_Device_Context->Map(m_pEffect_Instance_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub)))
//   // {
//   //    // memcpy(sub.pData, &m_Effect_Instance_List.at(0), sizeof(Instance_VB)*m_Effect_Instance_List.size());
//   // }
//   // CADevice::m_pImmediate_Device_Context->Unmap(m_pEffect_Instance_buffer, 0);
//}
//
//void Effect_Render_Obj::Add()
//{
//   
//    
//    {
//     //  data.m_Alpha = 1.0f;
//     //  data.m_Color_Filter.x = 1.0f;
//     //  data.m_Color_Filter.y = 1.0f;
//     //  data.m_Color_Filter.z = 1.0f;
//     //  data.m_Color_Filter.w = 1.0f;
//     //  data.m_Normal.x = 0.0f;
//     //  data.m_Normal.y = 1.0f;
//     //  data.m_Normal.z = 0.0f;
//     //  data.m_Pos.x = 0;// randstep(-1.0f, 1.0f);
//     //  data.m_Pos.y = 0;//randstep(0.0f, 0.0f);
//     //  data.m_Pos.z = 0;//randstep(-1.0f, 1.0f);
//     //  //data.m_fFadeOutTime = randstep(1.0f, 3.0f);
//     //  //data.m_vGravity = D3DXVECTOR3(0.0, -9.8f, 0.0f);
//     //  //data.m_fSpeed = randstep(1.0f, 3.0f);
//     //  //data.m_iTexID = 1;
//     //  data.m_Life_Time = 1 + (rand() % 13);
//
//        //data.m_vTargetPos.x = randstep(0.1f, 1.0f);
//        //data.m_vTargetPos.y = randstep(0.1f, 1.0f);
//        //data.m_vTargetPos.z = randstep(0.1f, 1.0f);
//        
//        //data.m_vTargetPos = data.m_vTargetPos - data.m_vPos;
//        //D3DXVec3Normalize(&data.m_vTargetPos, &data.m_vTargetPos);
//        //data.m_vVelocity = data.m_vTargetPos * randstep(1.f, data.m_fSpeed);
//    }
//    else
//    {
//      //  m_Base_Effect.m_vVelocity = D3DXVECTOR3(50 - rand() % 100, 50 - rand() % 100, 50 - rand() % 100);
//      //  m_Base_Effect.m_Life_Time = 1 + (rand() % 13);
//
//      //  D3DXVec3Normalize(&m_Base_Effect.m_vVelocity, &m_Base_Effect.m_vVelocity);
//        data = m_Base_Effect;
//       
//
//    }
//    /////////////////////////////////////////////////
//    data.m_fFadeInDeltaTime = data.m_fFadeInTime;
//    data.m_fFadeOutDeltaTime = data.m_fFadeOutTime;
//    if (data.m_fFadeInTime == 0.0f)
//    {
//        data.m_Alpha = 1;
//    }
//    else
//    {
//        data.m_Alpha = 0;
//    }
//    m_Effect_Vertex_List.push_back(data);
//}
void Effect_Render_Obj::Update()
{
    Set_Move();//m_Base_CB.m_Move_Vector 새팅
    Set_Power();
    Set_CtrlMatrix();
    srand(time(NULL));
    if (fabs(m_data.m_vRandom_Pos_Max.x) > 0.0001)

    {

        m_data.m_Base_CB.m_vrandom.x = ((int)(rand() - m_data.m_vRandom_Pos_Min.x) % (int)m_data.m_vRandom_Pos_Max.x) + m_data.m_vRandom_Pos_Min.x;
    }
    else
    {
        m_data.m_Base_CB.m_vrandom.x = 0;
    }
    if (fabs(m_data.m_vRandom_Pos_Max.y) > 0.0001)
    {
        m_data.m_Base_CB.m_vrandom.y = ((int)(rand() - m_data.m_vRandom_Pos_Min.y) % (int)m_data.m_vRandom_Pos_Max.y) + m_data.m_vRandom_Pos_Min.y;
       
    }
    else
    {
        m_data.m_Base_CB.m_vrandom.y = 0;
    }
    if (fabs(m_data.m_vRandom_Pos_Max.z) > 0.0001)
    {
        m_data.m_Base_CB.m_vrandom.z = ((int)(rand() - m_data.m_vRandom_Pos_Min.z) % (int)m_data.m_vRandom_Pos_Max.z) + m_data.m_vRandom_Pos_Min.z;
    }
    else
    {
        m_data.m_Base_CB.m_vrandom.z = 0;
    }


}
float Effect_Render_Obj::EXP_Product(float a, float b,Radius_exp exp1,float c,float d, Radius_exp exp2,float e)
{
    return a + b * GetExp(c + d * GetExp(e, exp2), exp1);
}
float Effect_Render_Obj::GetExp(float in, Radius_exp exp)
{
    //if (in == 0.0f)
    //{
    //    return 0.0f;
    //}

    switch (exp)
    {
        case COS:
        {
            return cosf(in);
        }break;
        case SIN:
        {
            return sinf(in);
        }break;
        case TAN:
        {
            return tanf(in);
        }break;
        case COS_TIMER:
        {
            return cosf(g_fGameTimer);
        }break;
        case SIN_TIMER:
        {
            return sinf(g_fGameTimer);

        }break;
        case TAN_TIMER:
        {
            return tanf(g_fGameTimer);

        }break;
        case RETURN_ZERO:
        {
            return 0.0f;
        }
        case RETURN_ONE:
        {
            return 1.0f;
        }
        default:
            return 0.0f;
    }
}

void Effect_Render_Obj::Set_Move()
{
    m_data.m_fMove_Radius = EXP_Product(m_data.m_Move_Data_R.a, m_data.m_Move_Data_R.b, m_data.m_Move_Data_R.exp1, m_data.m_Move_Data_R.c, m_data.m_Move_Data_R.d, m_data.m_Move_Data_R.exp2, m_data.m_Move_Data_R.e);
    m_data.m_Base_CB.m_Move_Vector.x = m_data.m_fMove_Radius* EXP_Product(m_data.m_Move_Data_X.a, m_data.m_Move_Data_X.b, m_data.m_Move_Data_X.exp1, m_data.m_Move_Data_X.c, m_data.m_Move_Data_X.d, m_data.m_Move_Data_X.exp2, m_data.m_Move_Data_X.e);
    m_data.m_Base_CB.m_Move_Vector.y = m_data.m_fMove_Radius* EXP_Product(m_data.m_Move_Data_Y.a, m_data.m_Move_Data_Y.b, m_data.m_Move_Data_Y.exp1, m_data.m_Move_Data_Y.c, m_data.m_Move_Data_Y.d, m_data.m_Move_Data_Y.exp2, m_data.m_Move_Data_Y.e);
    m_data.m_Base_CB.m_Move_Vector.z = m_data.m_fMove_Radius* EXP_Product(m_data.m_Move_Data_Z.a, m_data.m_Move_Data_Z.b, m_data.m_Move_Data_Z.exp1, m_data.m_Move_Data_Z.c, m_data.m_Move_Data_Z.d, m_data.m_Move_Data_Z.exp2, m_data.m_Move_Data_Z.e);
}
void Effect_Render_Obj::Set_Power()
{
    m_data.m_Base_CB.TotalPower.x = m_data.m_vPower1.x; //+m_data.m_vPower2.x + m_data.m_vPower3.x;
    m_data.m_Base_CB.TotalPower.y = m_data.m_vPower1.y; //+m_data.m_vPower2.y + m_data.m_vPower3.y;
    m_data.m_Base_CB.TotalPower.z = m_data.m_vPower1.z; //+m_data.m_vPower2.z + m_data.m_vPower3.z;
}
void Effect_Render_Obj::Set_CtrlMatrix()
{
    if (!m_data.m_bUse_billboard)
    {
        D3DXMatrixIdentity(&m_matbill);
    }
    
    //D3DXMatrixInverse(&m_data.m_Base_CB.m_matbill, NULL, &m_matbill);
    D3DXMatrixTranspose(&m_data.m_Base_CB.m_matbill, &m_matbill);
    //D3DXQuaternionRotationMatrix((D3DXQUATERNION*)&m_data.m_Base_CB.m_quatbill, &m_matbill);

    D3DXQuaternionRotationYawPitchRoll((D3DXQUATERNION*)&m_data.m_Base_CB.m_vRot_Quat_perSec,
        D3DXToRadian(m_data.m_to_quat.x),
                                        D3DXToRadian(m_data.m_to_quat.y),
                                        D3DXToRadian(m_data.m_to_quat.z));
    D3DXQuaternionRotationYawPitchRoll((D3DXQUATERNION*)&m_data.m_Base_CB.m_vRotation,
        D3DXToRadian(m_data.m_to_quat_base_rot.x),
        D3DXToRadian(m_data.m_to_quat_base_rot.y),
        D3DXToRadian(m_data.m_to_quat_base_rot.z));


}
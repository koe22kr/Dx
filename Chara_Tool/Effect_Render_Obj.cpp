#include "stdafx.h"
#include "Effect_Render_Obj.h"

bool Effect_Render_Obj::Create_Render_Obj(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile)
{
    m_pDevice = pd3dDevice;
    if (FAILED(LoadShaderFile(pd3dDevice, pLoadShaderFile)))
    {
#ifdef _DEBUG
        MessageBox(NULL, L"Create_Render_Obj_LoadShaderFile_Fail", L"Create_Render_Obj_LoadShaderFile_Fail", S_OK);
#endif // _DEBUG
        return false;
    }
    if (FAILED(SetInputLayout()))
    {
#ifdef _DEBUG
        MessageBox(NULL, L"Create_Render_Obj_SetInputLayout_Fail", L"Create_Render_Obj_SetInputLayout_Fail", S_OK);
#endif // _DEBUG
        return false;
    }
    if (FAILED(CreateConstantBuffer()))
    {
#ifdef _DEBUG
        MessageBox(NULL, L"Create_Render_Obj_CreateConstantBuffer_Fail", L"Create_Render_Obj_CreateConstantBuffer_Fail", S_OK);
#endif // _DEBUG
        return false;
    }
    m_szShader_Name = pLoadShaderFile;
    return true;
}
bool  Effect_Render_Obj::Create(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile, const TCHAR* pLoadTextureFile)
{
    return Create_Render_Obj(pd3dDevice, pLoadShaderFile);
}



HRESULT Effect_Render_Obj::SetInputLayout()
{
    HRESULT hr = S_OK;
    //input layout
    //정점버퍼의 데이터를 정점 쉐이더의 인자값으로 설정
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0  },
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0  },
        {"COLORFILTER", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0  },
        {"ALPHA", 0, DXGI_FORMAT_R32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0} ,
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0  },
        {"LIFETIME", 0, DXGI_FORMAT_R32_FLOAT, 0, 52, D3D11_INPUT_PER_VERTEX_DATA, 0  },
       /* {"TRANSFORM", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1},
        {"TRANSFORM", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1},
        {"TRANSFORM", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1},
        {"TRANSFORM", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1},*/

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

    HRESULT hr = S_OK;
    if (m_Effect_Vertex_List.size() <= 0)  return S_OK;
   // if (m_Effect_Instance_List.size() <= 0)  return S_OK;

    m_helper.m_pVertexBuffer.Attach(
        DX::CreateVertexBuffer(m_pDevice,
            &m_Effect_Vertex_List.at(0), m_Effect_Vertex_List.size(), sizeof(Effect_Data))
    );
    if (m_helper.m_pVertexBuffer.Get() == nullptr)
        return false;
    //////////////////////////////////////////////////////////////////////////////////////////
  /*  D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.ByteWidth = sizeof(Instance_VB) * m_Effect_Instance_List.size();
    
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    sd.pSysMem = &m_Effect_Instance_List.at(0);

    
        if (FAILED(hr = CADevice::m_pDevice->CreateBuffer(
            &bd, &sd,
            &m_pEffect_Instance_buffer)))
        {
            return hr;
        }*/
    /////////////////////////////////////////////////////////////////////////////////////
    return hr;

}
HRESULT Effect_Render_Obj::CreateIndexBuffer()
{
    return S_OK;

}
HRESULT Effect_Render_Obj::LoadTextures(ID3D11Device* pd3dDevice, const TCHAR* pLoadTextureFile)
{
    return S_OK;
}

Effect_Render_Obj::Effect_Render_Obj()
{
    m_bRend = false;
}
Effect_Render_Obj::~Effect_Render_Obj()
{
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
    return hr;
}

void Effect_Render_Obj::Update_Buffer()
{
   
    std::vector<Effect_Data>::iterator iter;
    for (iter= m_Effect_Vertex_List.begin(); iter != m_Effect_Vertex_List.end();)
    {


        iter->m_Delta_Time += g_fSecondPerFrame;
        if (iter->m_Delta_Time >= 0.1)
        {
            iter->m_iTexID++;
            iter->m_Delta_Time -= 0.1;
        }

        if (iter->m_fFadeInDeltaTime > 0.0f)
        {
            iter->m_fFadeInDeltaTime -= g_fSecondPerFrame;
            iter->m_Alpha += 1 / iter->m_fFadeInTime*g_fSecondPerFrame;
            if (iter->m_Alpha > 1.0f)iter->m_Alpha = 1.0f;
        }
        else
        {
            if (iter->m_Life_Time > 0.0f)
            {
                iter->m_Life_Time -= g_fSecondPerFrame;
            }
            else
            {
                if (iter->m_fFadeOutTime > 0)
                {
                    iter->m_fFadeOutDeltaTime -= g_fSecondPerFrame;
                    iter->m_Alpha -= 1 / iter->m_fFadeOutTime*g_fSecondPerFrame;
                    if (iter->m_Alpha < 0.0f)iter->m_Alpha = 0.0f;
                }
            }


            if (iter->m_fFadeOutTime <= 0 && iter->m_Life_Time <= 0)
            {
                iter = m_Effect_Vertex_List.erase(iter);
            }
            
        }
        iter++;
        
    }
      //  m_Effect_Instance_List[ibuffer].m_matWorld = matRotation * matTrans;
        //TODO 추가적인 VB 계산 필요할
        
        //D3DXMATRIX matWorld, matTrans, matRotation, matScale;
        ////D3DXMatrixInverse(&matRotation, NULL, &m_cur_cam->m_matView);
        //matRotation._41 = 0.0f;
        //matRotation._42 = 0.0f;
        //matRotation._43 = 0.0f;
        //matRotation._44 = 1.0f;



   // D3D11_MAPPED_SUBRESOURCE sub;
   // if (SUCCEEDED(CADevice::m_pImmediate_Device_Context->Map(m_pEffect_Instance_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub)))
   // {
   //    // memcpy(sub.pData, &m_Effect_Instance_List.at(0), sizeof(Instance_VB)*m_Effect_Instance_List.size());
   // }
   // CADevice::m_pImmediate_Device_Context->Unmap(m_pEffect_Instance_buffer, 0);
}

void Effect_Render_Obj::Add()
{
    Effect_Data data;
    if (m_bRend)
    {
     //  data.m_Alpha = 1.0f;
     //  data.m_Color_Filter.x = 1.0f;
     //  data.m_Color_Filter.y = 1.0f;
     //  data.m_Color_Filter.z = 1.0f;
     //  data.m_Color_Filter.w = 1.0f;
     //  data.m_Normal.x = 0.0f;
     //  data.m_Normal.y = 1.0f;
     //  data.m_Normal.z = 0.0f;
     //  data.m_Pos.x = 0;// randstep(-1.0f, 1.0f);
     //  data.m_Pos.y = 0;//randstep(0.0f, 0.0f);
     //  data.m_Pos.z = 0;//randstep(-1.0f, 1.0f);
     //  //data.m_fFadeOutTime = randstep(1.0f, 3.0f);
     //  //data.m_vGravity = D3DXVECTOR3(0.0, -9.8f, 0.0f);
     //  //data.m_fSpeed = randstep(1.0f, 3.0f);
     //  //data.m_iTexID = 1;
     //  data.m_Life_Time = 1 + (rand() % 13);

        //data.m_vTargetPos.x = randstep(0.1f, 1.0f);
        //data.m_vTargetPos.y = randstep(0.1f, 1.0f);
        //data.m_vTargetPos.z = randstep(0.1f, 1.0f);
        
        //data.m_vTargetPos = data.m_vTargetPos - data.m_vPos;
        //D3DXVec3Normalize(&data.m_vTargetPos, &data.m_vTargetPos);
        //data.m_vVelocity = data.m_vTargetPos * randstep(1.f, data.m_fSpeed);
    }
    else
    {
      //  m_Base_Effect.m_vVelocity = D3DXVECTOR3(50 - rand() % 100, 50 - rand() % 100, 50 - rand() % 100);
      //  m_Base_Effect.m_Life_Time = 1 + (rand() % 13);

      //  D3DXVec3Normalize(&m_Base_Effect.m_vVelocity, &m_Base_Effect.m_vVelocity);
        data = m_Base_Effect;
       

    }
    /////////////////////////////////////////////////
    data.m_fFadeInDeltaTime = data.m_fFadeInTime;
    data.m_fFadeOutDeltaTime = data.m_fFadeOutTime;
    if (data.m_fFadeInTime == 0.0f)
    {
        data.m_Alpha = 1;
    }
    else
    {
        data.m_Alpha = 0;
    }
    m_Effect_Vertex_List.push_back(data);
}
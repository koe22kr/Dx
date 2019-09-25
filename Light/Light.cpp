#include "Light.h"

using namespace DX;


bool Sample::Init()
{
    m_Debug_Line.Create(CADevice::m_pDevice, L"../../_shader/line.hlsl", nullptr);

    m_cbLight.g_cAmbientMaterial = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

    m_cbLight.g_cDiffuseMaterial = D3DXVECTOR4(1, 1, 1, 1);
    m_cbLight.g_cSpecularMaterial = D3DXVECTOR4(1, 1, 1, 1);


    m_cbLight.g_cAmbientLightColor = D3DXVECTOR4(1, 1, 1, 1);
    m_cbLight.g_cDiffuseLightColor = D3DXVECTOR4(1, 1, 1, 1);
    m_cbLight.g_cSpecularLightColor = D3DXVECTOR4(1, 1, 1, 1);

    ID3D11Buffer* tempcb;

    I_DXHELPER.Create_Const_Buffer(tempcb, &m_cbLight, 1, sizeof(m_cbLight), CADevice::m_pDevice);
    m_pConstantBufferLight.Attach(tempcb);
    CreateResource();
    return true;
}
bool Sample::Render()
{
    angleyaw += g_fSecondPerFrame ;

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

    m_cbLight.g_vEyeDir.x = m_pMain_Cam->m_vLookVector.x;
    m_cbLight.g_vEyeDir.y = m_pMain_Cam->m_vLookVector.y;
    m_cbLight.g_vEyeDir.z = m_pMain_Cam->m_vLookVector.z;
    m_cbLight.g_vEyeDir.w = 0.1f; // 빛의 밝기 강도
    m_cbLight.g_cSpecularMaterial = D3DXVECTOR4(0.5, 0.5, 0.5, 1);

    CADevice::m_pImmediate_Device_Context->VSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());
    CADevice::m_pImmediate_Device_Context->PSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());

    

    D3DXMatrixIdentity(&m_cbLight.g_matInvWorld);
    CADevice::m_pImmediate_Device_Context->UpdateSubresource(m_pConstantBufferLight.Get(), 0, NULL, &m_cbLight, 0, 0);


    return true;
}
bool Sample::DrawDebug()
{
    if (I_Input.KeyCheck('P')==KEY_HOLD)
    {
        // 정점노말 표시
        m_Debug_Line.SetMatrix(NULL, m_pMain_Cam->GetViewMatrix(), m_pMain_Cam->GetProjMatrix());

        D3DXMATRIX invWorld;
        D3DXMatrixIdentity(&invWorld);
        D3DXMatrixInverse(&invWorld, 0, m_pMain_Cam->GetWorldMatrix());
        invWorld._41 = invWorld._42 = invWorld._43 = 0.0f;
        D3DXMatrixTranspose(&invWorld, &invWorld);

        D3DXVECTOR3 vStart, vEnd, vNor, vEye;
        vEye = *m_pMain_Cam->GetLookVector();
        for (UINT row = 0; row < m_Heightmap.m_iNumRows; row += 100)
        {
            for (UINT col = 0; col < m_Heightmap.m_iNumCols; col += 5)
            {
                D3DXVec3TransformCoord(&vStart, (D3DXVECTOR3*)&m_Heightmap.m_Vertex_List2[row*m_Heightmap.m_iNumCols + col].p, &invWorld);
                D3DXVec3TransformNormal(&vNor, (D3DXVECTOR3*)&m_Heightmap.m_Vertex_List2[row*m_Heightmap.m_iNumCols + col].n, &invWorld);
                D3DXVec3Normalize(&vNor, &vNor);
                vEnd = vStart + vNor * 2.0f;
                float fDot = D3DXVec3Dot(&vEye, &vNor);
                if (fDot < 0)
                {
                    vNor.x = vNor.x * 0.5f + 0.5f;
                    vNor.y = vNor.y * 0.5f + 0.5f;
                    vNor.z = vNor.z * 0.5f + 0.5f;
                    m_Debug_Line.Draw_Line(CADevice::m_pImmediate_Device_Context, vStart, vEnd, D3DXVECTOR4(vNor.x, vNor.y, vNor.z, 1.0f));
                }
            }
        }
    }
    return true;

}
bool Sample::Release()
{
    return true;

}

bool Sample::Frame()
{
    DrawDebug();
    float t = g_fSecondPerFrame * D3DX_PI;

    D3DXMATRIX mLightWorld, mTranslate, mRotation;
    D3DXMatrixTranslation(&mTranslate, 100.0f, 100.0f, 0.0f);
    D3DXMatrixRotationY(&mRotation, t*0);
    D3DXMatrixMultiply(&mLightWorld, &mTranslate, &mRotation);

    m_vLightVector.x = mLightWorld._41;
    m_vLightVector.y = mLightWorld._42;
    m_vLightVector.z = mLightWorld._43;

    D3DXVec3Normalize(&m_vLightVector, &m_vLightVector);
    m_vLightVector *= -1.0f;

    return true;
}

//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT Sample::CreateResource()
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


Sample::Sample()
{
}


Sample::~Sample()
{
}

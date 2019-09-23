#include "Light.h"

using namespace DX;


bool Sample::Init()
{
    m_cbLight.g_cAmbientMaterial = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1);
    m_cbLight.g_cDiffuseMaterial = D3DXVECTOR4(1, 1, 1, 1);
    m_cbLight.g_cAmbientLightColor = D3DXVECTOR4(1, 1, 1, 1);
    m_cbLight.g_cDiffuseLightColor = D3DXVECTOR4(1, 1, 1, 1);
    ID3D11Buffer* tempcb;
    I_DXHELPER.Create_Const_Buffer(tempcb, &m_cbLight, 1, sizeof(m_cbLight), CADevice::m_pDevice);
    m_pConstantBufferLight.Attach(tempcb);
    CreateResource();
    return true;
}
bool Sample::Render()
{
    angleyaw += g_fSecondPerFrame * 0.7f;


    D3DXMATRIX matWorld, matScale;
    matWorld._41 = 2.0f;
    matWorld._41 = 2.0f;

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
    D3DXMatrixInverse(&matInvWorld, NULL, &matWorld);
    D3DXMatrixTranspose(&matInvWorld, &matInvWorld);
    D3DXMatrixTranspose(&m_cbLight.g_matInvWorld, &matInvWorld);

    //const updatesubresourece 있던자리

    CADevice::m_pImmediate_Device_Context->VSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());
    CADevice::m_pImmediate_Device_Context->PSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());
    
    //m_shape_Obj.SetMatrix(&matWorld, m_pMain_Cam->GetViewMatrix(), m_pMain_Cam->GetProjMatrix());

    D3DXMatrixIdentity(&m_cbLight.g_matInvWorld);
    CADevice::m_pImmediate_Device_Context->UpdateSubresource(m_pConstantBufferLight.Get(), 0, NULL, &m_cbLight, 0, 0);

    //m_shape_Obj.Render(CADevice::m_pImmediate_Device_Context);

    return true;
}
bool Sample::DrawDebug()
{
    if (I_Input.KeyCheck(DIK_P)==KEY_HOLD)
    {
        // 정점노말 표시
        m_Debug_Line.SetMatrix(NULL, m_pMain_Cam->GetViewMatrix(), m_pMain_Cam->GetProjMatrix());

        D3DXMATRIX invWorld;
        D3DXMatrixIdentity(&invWorld);
        D3DXMatrixInverse(&invWorld, 0, m_pMain_Cam->GetWorldMatrix());
        D3DXMatrixTranspose(&invWorld, &invWorld);
        D3DXVECTOR3 vStart, vEnd, vDir, vEye;
        vEye = *m_pMain_Cam->GetLookVector();
        for (UINT row = 0; row < m_Heightmap.m_iNumRows; row += 5)
        {
            for (UINT col = 0; col < m_Heightmap.m_iNumCols; col += 5)
            {
                D3DXVec3TransformCoord(&vStart, (D3DXVECTOR3*)&m_Heightmap.m_Vertex_List2[row*m_Heightmap.m_iNumCols + col].p, m_pMain_Cam->GetWorldMatrix());
                D3DXVec3TransformNormal(&vDir, (D3DXVECTOR3*)&m_Heightmap.m_Vertex_List2[row*m_Heightmap.m_iNumCols + col].n, &invWorld);
                D3DXVec3Normalize(&vDir, &vDir);
                vEnd = vStart + vDir * 2.0f;
                float fDot = D3DXVec3Dot(&vEye, &vDir);
                if (fDot < 0)
                {
                    vDir.x = vDir.x * 0.5f + 0.5f;
                    vDir.y = vDir.y * 0.5f + 0.5f;
                    vDir.z = vDir.z * 0.5f + 0.5f;
                    m_Debug_Line.Draw_Line(CADevice::m_pImmediate_Device_Context, vStart, vEnd, D3DXVECTOR4(vDir.x, vDir.y, vDir.z, 1.0f));
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
    float t = g_fSecondPerFrame * D3DX_PI;

    D3DXMATRIX mLightWorld, mTranslate, mRotation;
    D3DXMatrixTranslation(&mTranslate, 100.0f, 100.0f, 0.0f);
    D3DXMatrixRotationY(&mRotation, t);
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

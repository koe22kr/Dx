#include "stdafx.h"
#include "Sample.h"

ID3D11DepthStencilState* g_dss;
D3D11_DEPTH_STENCIL_DESC   g_dsd;

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
bool Sample::Init()
{
 /*   m_Render_List.m_Effect_Vertex_List.resize(MAX_EFFECT);
    m_Render_List.Create_Render_Obj(CADevice::m_pDevice,L"effect.hlsl");
    m_Render_List.Add();*/
    m_Plane.Create(CADevice::m_pDevice, L"effect.hlsl", L"../../_data/obj/attack_damage_01.dds");
    HRESULT hr = S_OK;
    //
     D3D11_DEPTH_STENCIL_DESC dsDesc;
        ZeroMemory(&dsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
        dsDesc.DepthEnable = TRUE;
        dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
        if (FAILED(hr = CADevice::m_pDevice->CreateDepthStencilState(&g_dsd, &g_dss)))
        {
            EM(hr, m_pDSSDepth_Less_Equal, CADx_State);
            return false;
        }
        
        CADevice::m_pImmediate_Device_Context->OMSetDepthStencilState(g_dss, 1);

    //

    
    m_Render_List.Add();
    return true;
}
bool Sample::Frame()
{

    m_Render_List.Update_Buffer();
    return true;
}
bool Sample::Render()
{
    static float tTime = 0.0f;
    tTime += g_fSecondPerFrame;
    if (tTime > 0.1f)
    {
        m_Render_List.Add();
        tTime -= 0.1f;
    }

    D3DXMATRIX matRotation;
    D3DXMatrixInverse(&matRotation, NULL,
        &m_pMain_Cam->m_matView);

    
    for (int a = 0; a < m_Render_List.m_Effect_Vertex_List.size(); a++)
    {
        matRotation._41 = m_Render_List.m_Effect_Vertex_List[a].m_Pos.x+= m_Render_List.m_Effect_Vertex_List[a].m_vVelocity.x * g_fSecondPerFrame * 15;
        matRotation._42 = m_Render_List.m_Effect_Vertex_List[a].m_Pos.y+= m_Render_List.m_Effect_Vertex_List[a].m_vVelocity.y * g_fSecondPerFrame * 15;
        matRotation._43 = m_Render_List.m_Effect_Vertex_List[a].m_Pos.z+= m_Render_List.m_Effect_Vertex_List[a].m_vVelocity.z * g_fSecondPerFrame * 15;
        
        
        

        

       // matRotation._41 = m_list[iObj].m_vPos.x;
       // matRotation._42 = m_list[iObj].m_vPos.y;
       // matRotation._43 = m_list[iObj].m_vPos.z;

        Get_UV(m_iCut_Num, m_iCut_Num, m_Render_List.m_Effect_Vertex_List[a].m_iTexID, &m_Plane);
        CADevice::m_pImmediate_Device_Context->UpdateSubresource(m_Plane.m_helper.m_pVertexBuffer.Get(), 0, 0, &m_Plane.m_Vertex_List.at(0),0,0);
        m_Plane.SetMatrix(&matRotation,
            &m_pMain_Cam->m_matView,
            &m_pMain_Cam->m_matProj);

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

void Sample::Get_UV(int cutx, int cuty, int texnum, TPlaneObject* m_pplane)
{
    float x = 1.0f / cutx;
    float y = 1.0f / cuty;
    if (cutx*cutx  <= texnum)
    {
        m_pplane->m_Vertex_List[0].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(0.0f, 0.0f);
        m_pplane->m_Vertex_List[1].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x, 0.0f);
        m_pplane->m_Vertex_List[2].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x, y);
        m_pplane->m_Vertex_List[3].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(0.0f, y);
        
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

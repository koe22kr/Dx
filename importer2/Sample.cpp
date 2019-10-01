#include "Sample.h"

using namespace std;

bool Sample::Init()
{
    m_loader.Load("test.MD");
    m_loader.m_pnct_List = &m_pnct_List;
    m_loader.Create(CADevice::m_pDevice, L"test.hlsl", nullptr);
    wstring temp;
    string atemp;
    //temp. = atemp.c_str();

    m_loader.m_helper.m_iNumIndex = 0;

    return true;
}
bool Sample::Frame()
{

    m_loader.Frame();
    return true;
}
bool Sample::Render()
{

    m_loader.SetMatrix((D3DXMATRIX*)&m_loader.m_matWorld, &m_pMain_Cam->m_matView, &m_pMain_Cam->m_matProj);
    m_loader.Render(CADevice::m_pImmediate_Device_Context);

    return true;
}
bool Sample::Release()
{
    return true;
}/*
HRESULT Sample::CreateVertexData()
{

    m_helper.m_iNumIndex = 0;

    m_Vertex_List = m_pnct_List;
    return 1;
}*/


Sample::Sample()
{
}


Sample::~Sample()
{
}

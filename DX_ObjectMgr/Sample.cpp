#include "Sample.h"

bool Sample::Init()
{
    DX_MGR.Load_Cit(CADevice::m_pDevice, L"../../_data/chara/swat.cit");
    return true;
}
bool Sample::Frame()
{
    return true;
}
bool Sample::Render()
{
    time += g_fSecondPerFrame;
    DX_MGR.Render(CADevice::m_pImmediate_Device_Context, 0, time, 0, 0, nullptr, &m_pMain_Cam->m_matView, &m_pMain_Cam->m_matProj);

    return true;
}
bool Sample::Release()
{
    DX_MGR.Release();
    return true;
}

Sample::Sample()
{
}


Sample::~Sample()
{
}

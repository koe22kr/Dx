#include "Sample.h"

bool Sample::Init()
{
    m_quad.Init(m_pMain_Cam,&m_Heightmap);
    m_quad.Build(0, m_Heightmap.m_iNumCols-1,
        (m_Heightmap.m_iNumRows - 1)*m_Heightmap.m_iNumCols, m_Heightmap.m_iNumRows*m_Heightmap.m_iNumCols-1,
        2, 1.0f);
    return true;
}
bool Sample::Frame()
{
    m_quad.Frame();
    return true;

}
bool Sample::Render()
{
    m_quad.Render(m_Device.m_pImmediate_Device_Context);
    return true;

}
bool Sample::Release()
{
    m_quad.Release();
    return true;

}

Sample::Sample()
{
}


Sample::~Sample()
{
}

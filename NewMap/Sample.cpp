#include "Sample.h"

bool Sample::Init()
{
   /* m_Map.CreateHeightMap(CADevice::m_pDevice, CADevice::m_pImmediate_Device_Context, L"../../_data/map/HEIGHT_GRASSHILL.bmp");
    MapDesc md;
    if (m_Map.m_iNumCols == 0 || m_Map.m_iNumRows == 0)
    {
        m_Map.m_iNumCols = 100;
        m_Map.m_iNumRows = 100;
    }
    md.iNumCols = m_Map.m_iNumCols;
    md.iNumRows = m_Map.m_iNumRows;
    md.fCellDistance = 1;
    md.szShaderFile = L"heightmap.hlsl";
    md.szTextureFile = L"../../_data/map/mounds.jpg";


    if (!m_Map.Load(CADevice::m_pDevice, md))
    {
        return false;
    }*/
    return true;
}
bool Sample::Frame()
{
  //  m_Map.Frame();

    return true;
}
bool Sample::Render()
{
  /*  m_Map.SetMatrix(
        nullptr,
        &m_pMain_Cam->m_matView,
        &m_pMain_Cam->m_matProj);
    m_Map.Render(CADevice::m_pImmediate_Device_Context);    return true;*/
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

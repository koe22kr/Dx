#include "Sample.h"

bool Sample::Init()
{
    m_quad.Init(m_pMain_Cam,&m_Heightmap);
    m_quad.Build(0, m_Heightmap.m_iNumCols-1,
        (m_Heightmap.m_iNumRows - 1)*m_Heightmap.m_iNumCols, m_Heightmap.m_iNumRows*m_Heightmap.m_iNumCols-1,
        6, 1.0f);
    m_line.Create(m_Device.m_pDevice, L"../../_Shader/line.hlsl", nullptr);
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
    Test_Pick();
    return true;

}
bool Sample::Release()
{
    m_quad.Release();
    return true;

}
void Sample::Test_Pick()
{
    if (I_Input.m_dwMouseState[0] == KEY_PUSH)
    {
        m_Select.SetMatrix(nullptr,
            &m_pMain_Cam->m_matView,
            &m_pMain_Cam->m_matProj);
        for (int iNode = 0; iNode <
            m_quad.m_Draw_Node_List.size(); iNode++)
        {
            Tree_Node* pNode = m_quad.m_Draw_Node_List[iNode];
            if (!m_Select.ChkAABBToRay(&pNode->m_BBox))
            {
                continue;
            }
            for (
                int iTri = 0;
                iTri < pNode->m_Index_Data.size();
                iTri += 3)
            {
                DWORD i0, i1, i2;
                i0 = pNode->m_Index_Data[iTri + 0];
                i1 = pNode->m_Index_Data[iTri + 1];
                i2 = pNode->m_Index_Data[iTri + 2];
                D3DXVECTOR3 v0, v1, v2;
                v0 = *(D3DXVECTOR3*)&m_Heightmap.m_PNCTT_Vertex_List[i0].p;
                v1 = *(D3DXVECTOR3*)&m_Heightmap.m_PNCTT_Vertex_List[i1].p;
                v2 = *(D3DXVECTOR3*)&m_Heightmap.m_PNCTT_Vertex_List[i2].p;

                if (m_Select.CheckPick(v0, v1, v2))
                {
                    D3DXMATRIX mat;
                    D3DXMatrixInverse(&mat, NULL, &m_pMain_Cam->m_matView);
                    m_LinePos.x = mat._41 + m_pMain_Cam->m_vLookVector.x*3.0f;
                    m_LinePos.y = mat._42 + m_pMain_Cam->m_vLookVector.y*3.0f;
                    m_LinePos.z = mat._43 + m_pMain_Cam->m_vLookVector.z*3.0f;
                    
                    m_Device.m_pImmediate_Device_Context->GSSetShader(NULL, NULL, 0);
                    
                }
            }
        }
    }
    
    m_line.SetMatrix(nullptr,
        &m_pMain_Cam->m_matView,
        &m_pMain_Cam->m_matProj);
    m_line.Draw_Line(m_Device.m_pImmediate_Device_Context, m_LinePos, D3DXVECTOR3(m_Select.m_vIntersection.x, m_Select.m_vIntersection.y, m_Select.m_vIntersection.z), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
}
Sample::Sample()
{
}


Sample::~Sample()
{
}

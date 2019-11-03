#include "Quad_Tree.h"


bool Quad_Tree::Build(float fMinX, float fMaxX, float fMinY, float fMaxY, float fMinZ, float fMaxZ, int iMaxDepth, float fMinSize)
{
    m_iMax_Depth_Limit = iMaxDepth;
    m_fMinDividSize = fMinSize;
    m_Depth_Node_List.resize(m_iMax_Depth_Limit+1);

    m_pRoot_Node = CreateNode(nullptr, fMinX, fMaxX, fMinY, fMaxY, fMinZ, fMaxZ);
    
    return BuildTree_float(m_pRoot_Node);
}
bool Quad_Tree::Build(DWORD FarL, DWORD FarR, DWORD NearL, DWORD NearR, int iMaxDepth, float fMinSize)
{
    m_dwCols = m_Target_Map->m_iNumCols;
    m_dwRows = m_Target_Map->m_iNumRows;
    m_iMax_Depth_Limit = iMaxDepth;
    m_fMinDividSize = fMinSize;
    m_Depth_Node_List.resize(m_iMax_Depth_Limit+1);

    m_pRoot_Node = CreateNode(nullptr, FarL, FarR, NearL, NearR);
    
    return BuildTree_index(m_pRoot_Node); 
}

Tree_Node*  Quad_Tree::CreateNode(Tree_Node* pParentNode, float fMinX, float fMaxX, float fMinY, float fMaxY, float fMinZ, float fMaxZ)
{
    Tree_Node* pNode = new Tree_Node;
    pNode->m_Child_List.reserve(m_nTree_Child_Num);
    pNode->m_is_Leaf = FALSE;

    pNode->m_BBox.vMax.x = fMaxX;
    pNode->m_BBox.vMax.y = fMaxY;
    pNode->m_BBox.vMax.z = fMaxZ;
    pNode->m_BBox.vMin.x = fMinX;
    pNode->m_BBox.vMin.y = fMinY;
    pNode->m_BBox.vMin.z = fMinZ;
    pNode->m_BBox.vCenter = (pNode->m_BBox.vMax +
        pNode->m_BBox.vMin) / 2;
    pNode->m_BBox.vAxis[0] = D3DXVECTOR3(1, 0, 0);
    pNode->m_BBox.vAxis[1] = D3DXVECTOR3(0, 1, 0);
    pNode->m_BBox.vAxis[2] = D3DXVECTOR3(0, 0, 1);
    pNode->m_BBox.fExtent[0] =
        (pNode->m_BBox.vMax.x - pNode->m_BBox.vMin.x) / 2;
    pNode->m_BBox.fExtent[1] =
        (pNode->m_BBox.vMax.y - pNode->m_BBox.vMin.y) / 2;
    pNode->m_BBox.fExtent[2] =
        (pNode->m_BBox.vMax.z - pNode->m_BBox.vMin.z) / 2;

    pNode->m_nDepth = 0;
    if (pParentNode != nullptr)
    {
        pNode->m_nDepth = pParentNode->m_nDepth + 1;
    }
    m_Depth_Node_List[pNode->m_nDepth].push_back(pNode);
    return pNode;
}


Tree_Node*  Quad_Tree::CreateNode(Tree_Node* pParentNode, DWORD FarL, DWORD FarR, DWORD NearL, DWORD NearR)
{
    Tree_Node* pNode = new Tree_Node;
    pNode->m_Child_List.reserve(4);
    pNode->m_is_Leaf = FALSE;
    pNode->m_Corner_Index_List.push_back((DWORD)FarL);
    pNode->m_Corner_Index_List.push_back((DWORD)FarR);
    pNode->m_Corner_Index_List.push_back((DWORD)NearL);
    pNode->m_Corner_Index_List.push_back((DWORD)NearR);

    

    D3DXVECTOR2 vHeight =
        GetHeightFromNode(
            pNode->m_Corner_Index_List[0],
            pNode->m_Corner_Index_List[1],
            pNode->m_Corner_Index_List[2],
            pNode->m_Corner_Index_List[3]);
    D3DXVECTOR3 v0 = *(D3DXVECTOR3*)&m_Target_Map->m_PNCTT_Vertex_List[pNode->m_Corner_Index_List[0]].p;
    D3DXVECTOR3 v1 = *(D3DXVECTOR3*)&m_Target_Map->m_PNCTT_Vertex_List[pNode->m_Corner_Index_List[3]].p;

    pNode->m_BBox.vMax.x = v1.x;
    pNode->m_BBox.vMax.y = vHeight.y;
    pNode->m_BBox.vMax.z = v0.z;
    pNode->m_BBox.vMin.x = v0.x;
    pNode->m_BBox.vMin.y = vHeight.x;
    pNode->m_BBox.vMin.z = v1.z;
    pNode->m_BBox.vCenter = (pNode->m_BBox.vMax +
        pNode->m_BBox.vMin) / 2;
    pNode->m_BBox.vAxis[0] = D3DXVECTOR3(1, 0, 0);
    pNode->m_BBox.vAxis[1] = D3DXVECTOR3(0, 1, 0);
    pNode->m_BBox.vAxis[2] = D3DXVECTOR3(0, 0, 1);
    pNode->m_BBox.fExtent[0] =
        (pNode->m_BBox.vMax.x - pNode->m_BBox.vMin.x) / 2;
    pNode->m_BBox.fExtent[1] =
        (pNode->m_BBox.vMax.y - pNode->m_BBox.vMin.y) / 2;
    pNode->m_BBox.fExtent[2] =
        (pNode->m_BBox.vMax.z - pNode->m_BBox.vMin.z) / 2;

    pNode->m_nDepth = 0;
    if (pParentNode != nullptr)
    {
        pNode->m_nDepth = pParentNode->m_nDepth + 1;
    }

    m_Depth_Node_List[pNode->m_nDepth].push_back(pNode);
    return pNode;

}

D3DXVECTOR2 Quad_Tree::GetHeightFromNode(DWORD FarL, DWORD FarR, DWORD NearL, DWORD NearR)
{
    float fMin = 99999.0f;
    float fMax = -99999.0f;
    DWORD dwStartRow = FarL / m_Target_Map->m_iNumCols;
    DWORD dwEndRow = NearL / m_Target_Map->m_iNumCols;
    DWORD dwStartCol = FarL % m_Target_Map->m_iNumCols;
    DWORD dwEndCol = NearR % m_Target_Map->m_iNumCols;
    for (DWORD dwRow = dwStartRow;
        dwRow < dwEndRow;
        dwRow++)
    {
        for (DWORD dwCol = dwStartCol;
            dwCol < dwEndCol;
            dwCol++)
        {
            DWORD dwIndex = dwRow * m_Target_Map->m_iNumCols + dwCol;
            if (m_Target_Map->m_PNCTT_Vertex_List[dwIndex].p.y < fMin)
            {
                fMin = m_Target_Map->m_PNCTT_Vertex_List[dwIndex].p.y;
            }
            if (m_Target_Map->m_PNCTT_Vertex_List[dwIndex].p.y > fMax)
            {
                fMax = m_Target_Map->m_PNCTT_Vertex_List[dwIndex].p.y;
            }
        }
    }
    return D3DXVECTOR2(fMin, fMax);
}

bool  Quad_Tree::BuildTree_float(Tree_Node* pNode)
{
    if (SubDivideQuad_float(pNode))
    {
        for (int iNode = 0; iNode < pNode->m_Child_List.size();
            iNode++)
        {
            BuildTree_float(pNode->m_Child_List[iNode]);
        }
    }
    return true;
}
bool  Quad_Tree::BuildTree_index(Tree_Node* pNode)
{
    if (SubDivideQuad_index(pNode))
    {
        for (int iNode = 0; iNode < pNode->m_Child_List.size();
            iNode++)
        {
            BuildTree_index(pNode->m_Child_List[iNode]);
        }
    }
    return true;
}

bool Quad_Tree::SubDivideQuad_float(Tree_Node* pNode)
{
    if (m_iMax_Depth_Limit <= pNode->m_nDepth)
    {
        pNode->m_is_Leaf = TRUE;
        return false;
    }

    float halfx = fabs(pNode->m_BBox.vMax.x - pNode->m_BBox.vMin.x) / 2;
    //float halfy = (pNode->m_BBox.vMax.y - pNode->m_BBox.vMin.y) / 2;
    float halfz = fabs(pNode->m_BBox.vMax.z - pNode->m_BBox.vMin.z) / 2;

    if (m_fMinDividSize >= halfx /*|| m_fMinDividSize >= halfy*/ || m_fMinDividSize >= halfz)
    {
        pNode->m_is_Leaf = TRUE;
        return false;
    }
    
  
    Tree_Node* pChildNode = CreateNode(
        pNode,
        pNode->m_BBox.vMin.x, pNode->m_BBox.vMin.x + halfx,
        pNode->m_BBox.vMin.y, pNode->m_BBox.vMax.y,
        pNode->m_BBox.vMin.z + halfz, pNode->m_BBox.vMax.z);
    pNode->m_Child_List.push_back(pChildNode);

    pChildNode = CreateNode(
        pNode,
        pNode->m_BBox.vMin.x + halfx, pNode->m_BBox.vMax.x,
        pNode->m_BBox.vMin.y, pNode->m_BBox.vMax.y,
        pNode->m_BBox.vMin.z + halfz, pNode->m_BBox.vMax.z);
    pNode->m_Child_List.push_back(pChildNode);
  
     pChildNode = CreateNode(pNode,
        pNode->m_BBox.vMin.x, pNode->m_BBox.vMin.x + halfx,
        pNode->m_BBox.vMin.y, pNode->m_BBox.vMax.y,
        pNode->m_BBox.vMin.z, pNode->m_BBox.vMin.z + halfz);

    pNode->m_Child_List.push_back(pChildNode);

    pChildNode = CreateNode(
        pNode,
        pNode->m_BBox.vMin.x + halfx, pNode->m_BBox.vMax.x,
        pNode->m_BBox.vMin.y, pNode->m_BBox.vMax.y,
        pNode->m_BBox.vMin.z, pNode->m_BBox.vMin.z + halfz);
    pNode->m_Child_List.push_back(pChildNode);

    return true;
}
bool  Quad_Tree::SubDivideQuad_index(Tree_Node* pNode)
{
    if (m_iMax_Depth_Limit <= pNode->m_nDepth)
    {
        Create_Index_Buffer(pNode);
        pNode->m_is_Leaf = TRUE;
        return false;
    }

    float halfx = fabs(pNode->m_BBox.vMax.x - pNode->m_BBox.vMin.x) / 2;
    //float halfy = (pNode->m_BBox.vMax.y - pNode->m_BBox.vMin.y) / 2;
    float halfz = fabs(pNode->m_BBox.vMax.z - pNode->m_BBox.vMin.z) / 2;
    if (m_fMinDividSize >= halfx /*|| m_fMinDividSize >= halfy*/ || m_fMinDividSize >= halfz)
    {
        Create_Index_Buffer(pNode);
        pNode->m_is_Leaf = TRUE;
        return false;
    }
    DWORD center = (pNode->m_Corner_Index_List[0] + pNode->m_Corner_Index_List[3]) / 2;
    DWORD edgetop = (pNode->m_Corner_Index_List[0] + pNode->m_Corner_Index_List[1]) / 2;
    DWORD edgeleft = (pNode->m_Corner_Index_List[0] + pNode->m_Corner_Index_List[2]) / 2;
    DWORD edgeright = (pNode->m_Corner_Index_List[1] + pNode->m_Corner_Index_List[3]) / 2;
    DWORD edgebottom = (pNode->m_Corner_Index_List[2] + pNode->m_Corner_Index_List[3]) / 2;

    Tree_Node* pChildNode = CreateNode(pNode,
        pNode->m_Corner_Index_List[0], edgetop, 
        edgeleft, center);
    pNode->m_Child_List.push_back(pChildNode);

    pChildNode = CreateNode(pNode,
        edgetop, pNode->m_Corner_Index_List[1],
        center, edgeright);
    pNode->m_Child_List.push_back(pChildNode);

    pChildNode = CreateNode(
        pNode,
        edgeleft, center, pNode->m_Corner_Index_List[2], edgebottom);
    pNode->m_Child_List.push_back(pChildNode);

    pChildNode = CreateNode(
        pNode, center, edgeright, edgebottom, pNode->m_Corner_Index_List[3]);
    pNode->m_Child_List.push_back(pChildNode);

    return true;
}
////////////////////////////////////
bool Quad_Tree::CheckRect_xz(Tree_Node* pNode, BASE_OBJ* pObj)
{
    if (pNode->m_BBox.vMin.x <= pObj->m_BBox.vMin.x &&
        pNode->m_BBox.vMax.x >= pObj->m_BBox.vMax.x)
    {
        if (pNode->m_BBox.vMin.z <= pObj->m_BBox.vMin.z &&
            pNode->m_BBox.vMax.z >= pObj->m_BBox.vMax.z)
        {
            return true;
        }
    }
    return false;
}

Tree_Node* Quad_Tree::FindNode(Tree_Node* pNode, BASE_OBJ* pObj)
{
    do {
        for (int iNode = 0; iNode < pNode->m_Child_List.size(); iNode++)
        {
            if (CheckRect_xz(pNode->m_Child_List[iNode], pObj))
            {
                m_Node_Queue.push(pNode->m_Child_List[iNode]);
            }
        }
        if (m_Node_Queue.empty()) break;

        pNode = m_Node_Queue.front();
        m_Node_Queue.pop();

    } while (pNode);
    return pNode;

}

void  Quad_Tree::AddObject(BASE_OBJ* pObj)
{
    if (CheckRect_xz(m_pRoot_Node, pObj))
    {
        Tree_Node* pNode = FindNode(m_pRoot_Node, pObj);
        if (pNode)
        {
            pNode->m_Obj_List.push_back(pObj);
        }
    }
}

void Quad_Tree::Create_Index_Buffer(Tree_Node* pNode)
{
    DWORD startcol = pNode->m_Corner_Index_List[0] % m_dwCols;
    DWORD endcol = pNode->m_Corner_Index_List[1] % m_dwCols;
    DWORD startrow = pNode->m_Corner_Index_List[0] / m_dwCols;
    DWORD endrow = pNode->m_Corner_Index_List[2] / m_dwCols;


    DWORD dwCols = pNode->m_Corner_Index_List[1] - pNode->m_Corner_Index_List[0];
    DWORD dwRows = pNode->m_Corner_Index_List[3] - pNode->m_Corner_Index_List[2];

    pNode->m_Index_Data.resize(dwCols*dwRows * 2 * 3);//mesh= 2face= 6index
    int iIndex = 0;
    for (int irow = startrow; irow < endrow; irow++)
    {

        for (int icol = startcol; icol < endcol; icol++)
        {
            int iNextRow = irow + 1;
            int iNextCol = icol + 1;
            pNode->m_Index_Data[iIndex + 0] = irow * m_dwCols + icol;
            pNode->m_Index_Data[iIndex + 1] = irow * m_dwCols + iNextCol;
            pNode->m_Index_Data[iIndex + 2] = iNextRow * m_dwCols + icol;

            pNode->m_Index_Data[iIndex + 3] = pNode->m_Index_Data[iIndex + 2];
            pNode->m_Index_Data[iIndex + 4] = pNode->m_Index_Data[iIndex + 1];
            pNode->m_Index_Data[iIndex + 5] = iNextRow * m_dwCols + iNextCol;
            iIndex += 6;
        }
    }
    pNode->m_Index_Buffer.Attach(DX::CreateIndexBuffer(m_Target_Map->m_pDevice, 
        &pNode->m_Index_Data.at(0), pNode->m_Index_Data.size(), sizeof(DWORD)));
    
}


void  Quad_Tree::Render(ID3D11DeviceContext* pContext)
{

    m_Target_Map->PreRender(pContext);
    m_Target_Map->SetMatrix(nullptr, &m_pCamera->m_matView, &m_pCamera->m_matProj);

    for (int a = 0; a < m_Draw_Node_List.size(); a++)
    {

        pContext->IASetIndexBuffer(m_Draw_Node_List[a]->m_Index_Buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
        pContext->DrawIndexed(m_Draw_Node_List[a]->m_Index_Data.size(), 0, 0);
    }
}
void  Quad_Tree::Check_Visible_Object(Tree_Node* pNode)
{
    for (int iObj = 0; iObj < pNode->m_Obj_List.size(); iObj++)
    {
        if (m_pCamera->CheckOBBInPlane(&pNode->m_BBox))
        {
            m_Draw_Obj_List.push_back(pNode->m_Obj_List[iObj]);
        }
    }
}
//void Quad_Tree::VisibleNode_Depth(UINT depth, Tree_Node* pNode)
//{
//    if (pNode == nullptr) return;
//    if (pNode->m_nDepth ==depth)
//    {
//        m_Draw_Node_List.push_back(pNode);
//        return;
//    }
//    for (int iNode = 0; iNode < pNode->m_Child_List.size();
//        iNode++)
//    {
//        VisibleNode_leaf(pNode->m_Child_List[iNode]);
//    }
//}

void  Quad_Tree::VisibleNode_leaf(Tree_Node* pNode)
{
    if (pNode == nullptr) return;
    if (pNode->m_is_Leaf)
    {
        m_Draw_Node_List.push_back(pNode);
    }
    for (int iNode = 0; iNode < pNode->m_Child_List.size();
        iNode++)
    {
        VisibleNode_leaf(pNode->m_Child_List[iNode]);
    }
}

void  Quad_Tree::DrawFindNode(Tree_Node* pNode)
{
    DX::T_POSITION t_Pos =
        m_pCamera->CheckPoitionOBBInPlane(&pNode->m_BBox);

    if (t_Pos == DX::P_BACK) return;
    
    /*if (t_Pos == DX::P_FRONT)
    {
        VisibleNode_leaf(pNode);
        return;
    }
    if (t_Pos == DX::P_SPANNING)
    {
        Check_Visible_Object(pNode);
    }*/
    if (t_Pos == DX::P_FRONT|| t_Pos == DX::P_SPANNING)
    {
        VisibleNode_leaf(pNode);
        Check_Visible_Object(pNode);
        return;
    }
    for (int iNode = 0; iNode < pNode->m_Child_List.size();
        iNode++)
    {
        DrawFindNode(pNode->m_Child_List[iNode]);
    }
}


void  Quad_Tree::Frame()
{
    m_Draw_Obj_List.clear();
    m_Draw_Node_List.clear();

    DrawFindNode(m_pRoot_Node);

}
void  Quad_Tree::Init(DX::TCamera* pCamera, DX::CADx_Map* pMap)
{
    m_pCamera = pCamera;
    m_Target_Map = pMap;
}

void Quad_Tree::Release()
{
    m_pRoot_Node->Release();
    delete m_pRoot_Node;
}

Quad_Tree::Quad_Tree()
{
    m_nTree_Child_Num = 4;
}


Quad_Tree::~Quad_Tree()
{
}


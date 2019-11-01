#include "N_Tree.h"

bool N_Tree::Build(float fWidth, float fHeight,
    int iMaxDepth,
    float fMinSize)
{
    m_pRoot_Node = CreateNode(nullptr,
        -fWidth / 2, fWidth / 2,
        -fHeight / 2, fHeight / 2);
    m_iMax_Depth_Limit = iMaxDepth;
    m_fMinDividSize = fMinSize;
    return BuildTree(m_pRoot_Node);
}
Tree_Node*  N_Tree::CreateNode(Tree_Node* pParentNode,
    float fMinX,
    float fMaxX,
    float fMinZ,
    float fMaxZ)
{
    Tree_Node* pNode = new Tree_Node;
    pNode->m_Child_List.reserve(m_nTree_Child_Num);
    pNode->m_is_Leaf = FALSE;

    pNode->m_BBox.vMax.x = fMaxX;
    pNode->m_BBox.vMax.y = 0.0f;
    pNode->m_BBox.vMax.z = fMaxZ;
    pNode->m_BBox.vMin.x = fMinX;
    pNode->m_BBox.vMin.y = 0.0f;
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
    return pNode;
}
void  N_Tree::AddObject(BASE_OBJ* pObj)
{
    if (CheckRect(m_pRoot_Node, pObj))
    {
        Tree_Node* pNode = FindNode(m_pRoot_Node, pObj);
        if (pNode)
        {
            pNode->m_Obj_List.push_back(pObj);
        }
    }
}
bool N_Tree::CheckRect(Tree_Node* pNode, BASE_OBJ* pObj)
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

Tree_Node* N_Tree::FindNode(Tree_Node* pNode, BASE_OBJ* pObj)
{
    do {
        for (int iNode = 0;
            iNode < pNode->m_Child_List.size(); iNode++)
        {
            if (CheckRect(pNode->m_Child_List[iNode], pObj))
            {
                m_Node_Queue.push(pNode->m_Child_List[iNode]);
            }
        }
        if (m_Node_Queue.empty()) break;

        pNode = m_Node_Queue.front();
        m_Node_Queue.pop();

    } while (pNode);
    return pNode;
    D3D11_FILTER_MIN_MAG_MIP_LINEAR

}
//
//D3DXVECTOR2 N_Tree::GetHeightFromNode(DWORD tl, DWORD tr, DWORD bl, DWORD br)
//{
//    float fMin = 99999.0f;
//    float fMax = -99999.0f;
//
//    DWORD dwStartRow = tl / m_dwWidth;
//    DWORD dwEndRow = bl / m_dwWidth;
//    DWORD dwStartCol = tl % m_dwWidth;
//    DWORD dwEndCol = tr % m_dwWidth;
//    for (DWORD dwRow = dwStartRow;
//        dwRow < dwEndRow;
//        dwRow++)
//    {
//        for (DWORD dwCol = dwStartCol;
//            dwCol < dwEndCol;
//            dwCol++)
//        {
//            DWORD dwIndex = dwRow * m_dwWidth + dwCol;
//            if (m_pMap->m_VertexList[dwIndex].p.y < fMin)
//            {
//                fMin = m_pMap->m_VertexList[dwIndex].p.y;
//            }
//            if (m_pMap->m_VertexList[dwIndex].p.y > fMax)
//            {
//                fMax = m_pMap->m_VertexList[dwIndex].p.y;
//            }
//        }
//    }
//    return D3DXVECTOR2(fMin, fMax);
//}

Tree_Node*  N_Tree::CreateNode(Tree_Node* pParenTree_Node, DWORD TL, DWORD TR, DWORD BL, DWORD BR)
{
    Tree_Node* pNode = new Tree_Node;
    pNode->m_Child_List.reserve(4);
    pNode->m_is_Leaf = FALSE;
    pNode->m_Corner_Index_List.push_back((DWORD)TL);
    pNode->m_Corner_Index_List.push_back((DWORD)TR);
    pNode->m_Corner_Index_List.push_back((DWORD)BL);
    pNode->m_Corner_Index_List.push_back((DWORD)BR);

    D3DXVECTOR2 vHeight =
        GetHeightFromNode(
            pNode->m_Corner_Index_List[0],
            pNode->m_Corner_Index_List[1],
            pNode->m_Corner_Index_List[2],
            pNode->m_Corner_Index_List[3]);

    D3DXVECTOR3 v0 = *(D3DXVECTOR3*)&m_pMap->m_Vertex_List[pNode->m_Corner_Index_List[0]].p;
    D3DXVECTOR3 v1 = *(D3DXVECTOR3*)&m_pMap->m_Vertex_List[pNode->m_Corner_Index_List[3]].p;

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
}

bool  N_Tree::BuildTree(Tree_Node* pNode)
{
    if (SubDivideQuad(pNode))
    {
        for (int iNode = 0; iNode < pNode->m_Child_List.size();
            iNode++)
        {
            BuildTree(pNode->m_Child_List[iNode]);
        }
    }
    return true;
}

bool N_Tree::SubDivideQuad(Tree_Node* pNode)
{
    if (m_iMax_Depth_Limit <= pNode->m_nDepth)
    {
        pNode->m_is_Leaf = TRUE;
        return false;
    }
    float fWidthSplit = (pNode->m_BBox.vMax.x - pNode->m_BBox.vMin.x) / 2;
    float fHeightSplit = (pNode->m_BBox.vMax.z - pNode->m_BBox.vMin.z) / 2;
    if (m_fMinDividSize >= fWidthSplit ||
        m_fMinDividSize >= fHeightSplit)
    {
        pNode->m_is_Leaf = TRUE;
        return false;
    }

    Tree_Node* pChildNode = CreateNode(
        pNode,
        pNode->m_BBox.vMin.x,
        pNode->m_BBox.vMin.x + fWidthSplit,
        pNode->m_BBox.vMin.z,
        pNode->m_BBox.vMax.z - fHeightSplit);
    pNode->m_Child_List.push_back(pChildNode);
    pChildNode = CreateNode(
        pNode,
        pNode->m_BBox.vMin.x + fWidthSplit,
        pNode->m_BBox.vMax.x,
        pNode->m_BBox.vMax.z - fHeightSplit,
        pNode->m_BBox.vMax.z);
    pNode->m_Child_List.push_back(pChildNode);

    pChildNode = CreateNode(
        pNode,
        pNode->m_BBox.vMin.x + fWidthSplit,
        pNode->m_BBox.vMax.x,
        pNode->m_BBox.vMin.z,
        pNode->m_BBox.vMax.z - fHeightSplit);
    pNode->m_Child_List.push_back(pChildNode);

    pChildNode = CreateNode(
        pNode,
        pNode->m_BBox.vMin.x,
        pNode->m_BBox.vMin.x + fWidthSplit,
        pNode->m_BBox.vMax.z - fHeightSplit,
        pNode->m_BBox.vMax.z);
    pNode->m_Child_List.push_back(pChildNode);
    return true;
}

void  N_Tree::Render(ID3D11DeviceContext* pContext)
{

}
void  N_Tree::VisibleObject(Tree_Node* pNode)
{
    for (int iObj = 0; iObj < pNode->m_Obj_List.size(); iObj++)
    {
        if (m_pCamera->CheckOBBInPlane(&pNode->m_BBox))
        {
            m_Draw_Obj_List.push_back(pNode->m_Obj_List[iObj]);
        }
    }
}

void  N_Tree::VisibleNode(Tree_Node* pNode)
{
    if (pNode == nullptr) return;
    if (pNode->m_is_Leaf)
    {
        m_Draw_Node_List.push_back(pNode);
    }
    for (int iNode = 0; iNode < pNode->m_Child_List.size();
        iNode++)
    {
        VisibleNode(pNode->m_Child_List[iNode]);
    }
}

void  N_Tree::DrawFindNode(Tree_Node* pNode)
{
    DX::T_POSITION t_Pos =
        m_pCamera->CheckPoitionOBBInPlane(&pNode->m_BBox);

    if (t_Pos == DX::P_BACK) return;

    if (pNode->m_is_Leaf && t_Pos != DX::P_BACK)
    {
        m_Draw_Node_List.push_back(pNode);
        return;
    }
    if (t_Pos == DX::P_FRONT)
    {
        VisibleNode(pNode);
        //m_DrawNodeList.push_back(pNode);
        return;
    }
    if (t_Pos == DX::P_SPANNING)
    {
        VisibleObject(pNode);
    }
    for (int iNode = 0; iNode < pNode->m_Child_List.size();
        iNode++)
    {
        DrawFindNode(pNode->m_Child_List[iNode]);
    }
}


void  N_Tree::Frame()
{
    m_Draw_Obj_List.clear();
    m_Draw_Node_List.clear();

    DrawFindNode(m_pRoot_Node);
    
}
void  N_Tree::Update(DX::TCamera* pCamera)
{
    m_pCamera = pCamera;
}

void N_Tree::Release()
{
    m_pRoot_Node->Release();
    delete m_pRoot_Node;
}

N_Tree::N_Tree()
{
}


N_Tree::~N_Tree()
{
}

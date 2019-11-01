#pragma once
#include "N_Tree.h"

class Quad_Tree :public N_Tree
{
    DWORD m_dwCols;
    DWORD m_dwRows;
    DX::CADx_Map* m_Target_Map;
public:
    bool Build(float fMinX, float fMaxX, float fMinY, float fMaxY, float fMinZ, float fMaxZ, int iMaxDepth = 5, float fMinSize = 10.0f);
    bool Build(DWORD FarL, DWORD FarR, DWORD NearL, DWORD NearR, int iMaxDepth, float fMinSize);
    
    void  AddObject(BASE_OBJ* pModel);

    
    void  Init(DX::TCamera* pCamera, DX::CADx_Map* pMap);


private:
    virtual Tree_Node*  CreateNode(Tree_Node* pParenTree_Node, float fMinX, float fMaxX, float fMinY, float fMaxY, float fMinZ, float fMaxZ);
    virtual Tree_Node*  CreateNode(Tree_Node* pParenTree_Node, DWORD FarL, DWORD FarR, DWORD NearL, DWORD NearR);
    D3DXVECTOR2 GetHeightFromNode(DWORD FarL, DWORD FarR, DWORD NearL, DWORD NearR);
    bool  BuildTree_float(Tree_Node* pNode);
    bool  BuildTree_index(Tree_Node* pNode);

    virtual bool  SubDivideQuad_float(Tree_Node* pNode);
    virtual bool  SubDivideQuad_index(Tree_Node* pNode);
    void Create_Index_Buffer(Tree_Node* pNode);

    //리프노드 찾기
    Tree_Node* FindNode(Tree_Node* pNode, BASE_OBJ* pObj);
    bool   CheckRect_xz(Tree_Node* pNode, BASE_OBJ* pObj);
    
    void  DrawFindNode(Tree_Node* pNode);
    void  Check_Visible_Object(Tree_Node* pNode);
  //  void VisibleNode_Depth(UINT depth, Tree_Node* pNode);//구현만 해놓음
    void  VisibleNode_leaf(Tree_Node* pNode);

public:
    void Frame();
    void Release();
    void Render(ID3D11DeviceContext* pContext);

    Quad_Tree();
    virtual ~Quad_Tree();
};


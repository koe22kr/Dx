#pragma once
#include "Tree_Node.h"
#include <queue>
#include "TCamera.h"
#include "CADx_Map.h"
class N_Tree
{
public:
    UINT m_nTree_Child_Num;
    Tree_Node* m_pRoot_Node;
    UINT m_iMax_Depth_Limit;
    float m_fMinDividSize;
    std::queue<Tree_Node*> m_Node_Queue;
    std::vector<Tree_Node*> m_Node_List;
    std::vector<std::vector<Tree_Node*>> m_Depth_Node_List;

    std::vector<Tree_Node*> m_Draw_Node_List;
    std::vector<BASE_OBJ*> m_Draw_Obj_List;
    
    DX::CADx_Map* m_pMap;
    DX::TCamera* m_pCamera;
public:

    bool Build(float fWidth, float fHeight,
        int   iMaxDepth = 5,
        float fMinSize = 10.0f);
    virtual Tree_Node*  CreateNode(Tree_Node* pParenTree_Node, float fMinX, float fMaxX, float fMinY, float fMaxY);
    virtual Tree_Node*  CreateNode(Tree_Node* pParenTree_Node, DWORD fTL, DWORD fTR, DWORD fBL, DWORD fBR);
  //  D3DXVECTOR2 GetHeightFromNode(DWORD tl, DWORD tr, DWORD bl, DWORD br);
    bool  BuildTree(Tree_Node* pNode);
    virtual bool  SubDivideQuad(Tree_Node* pNode);
    void  AddObject(BASE_OBJ* pModel);
    bool   CheckRect(Tree_Node* pNode, BASE_OBJ* pObj);
    Tree_Node* FindNode(Tree_Node* pNode, BASE_OBJ* pObj);

    void  Update(DX::TCamera* pCamera);
    void  DrawFindNode(Tree_Node* pNode);
    void  VisibleObject(Tree_Node* pNode);
    void  VisibleNode(Tree_Node* pNode);

public:
    void Frame();
    void Release();
    void Render(ID3D11DeviceContext* pContext);

public:
    N_Tree();
    ~N_Tree();
};


#pragma once
#include "Tree_Node.h"
#include <queue>
#include "TCamera.h"
class QuadTree
{
public:
    Tree_Node* m_Root_Node;
    UINT m_iMax_Depth_Limit;
    float m_fMinDividSize;
    std::queue<Tree_Node*> m_Node_Queue;
    std::vector<Tree_Node*> m_Node_List;
    std::vector<std::vector<Tree_Node*>> m_Depth_Node_List;

    std::vector<Tree_Node*> m_Draw_Node_List;
    std::vector<BASE_OBJ*> m_Draw_Obj_List;
    

    DX::TCamera* m_pCamera;
public:

    bool Build(float fWidth, float fHeight,
        int   iMaxDepth = 5,
        float fMinSize = 10.0f);
    virtual Tree_Node*  CreateNode(Tree_Node* pParenTree_Node,
        float fTL,
        float fTR,
        float fBL,
        float fBR);
    bool  BuildTree(Tree_Node* pNode);
    virtual bool  SubDivide(Tree_Node* pNode);
    void  AddObject(BASE_OBJ* pModel);
    bool   CheckRect(Tree_Node* pNode, BASE_OBJ* pObj);
    Tree_Node* FindNode(Tree_Node* pNode, BASE_OBJ* pObj);

    void  Update(DX::TCamera* pCamera);
    void  DrawFindNode(Tree_Node* pNode);
    void  VisibleObject(Tree_Node* pNode);
    void  VisibleNode(Tree_Node* pNode);

public:
    QuadTree();
    ~QuadTree();
};


#pragma once
#include "Tree_Node.h"
#include <queue>
#include "TCamera.h"
#include "CADx_Map.h"

class N_Tree
{
public:
    Tree_Node* m_pRoot_Node;

    //입력필요//////////////////////
    UINT m_nTree_Child_Num;
    UINT m_iMax_Depth_Limit;
    float m_fMinDividSize;  
    ////////////////////////////////
protected:
    std::vector<Tree_Node*> m_Node_List;
    std::vector<std::vector<Tree_Node*>> m_Depth_Node_List;//TODO

    std::vector<Tree_Node*> m_Draw_Node_List;
    std::vector<BASE_OBJ*> m_Draw_Obj_List;
    
    std::queue<Tree_Node*> m_Node_Queue; //자식 탐색용 큐

    DX::TCamera* m_pCamera;
public:
    N_Tree();
    virtual ~N_Tree();
};


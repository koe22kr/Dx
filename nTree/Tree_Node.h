#pragma once
#include "CADx_Model2.h"
#include "CADx_Std.h"

struct BASE_OBJ
{
    //obj 추가시 구현예정.
    DX::T_BOX m_BBox;

};
class Tree_Node
{
public:
    bool m_is_Leaf;
    UINT m_nDepth;
    DX::T_BOX m_BBox;

    std::vector< Tree_Node*> m_Child_List;
    //std::vector< BASE_OBJ*> m_Obj_List;

    std::vector<DWORD> m_Corner_Index_List;
    std::vector<DWORD> m_Index_Data;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_Index_Buffer;
public:
    Tree_Node();
    ~Tree_Node();
};


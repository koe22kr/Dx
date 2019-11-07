#pragma once
#include "khg_Obj_Exp.h"

class khg_Matrix_Exp :public khg_Obj_Exp
{
public:
    std::vector<Box3> box_list; //m_tempMesh_list °¹¼ö¸¸Å­.geo¸é size()==0
    void ExportAnimation(tempMesh& tmesh, FILE* pstream, int index);
    void Set(Interface* mMax) override;
    void AddMaterial(INode* pNode) override;
    bool    Convert() override;
    bool    Export() override;
    khg_Matrix_Exp();
    ~khg_Matrix_Exp();
    //
    static khg_Matrix_Exp* Get()
    {
        static khg_Matrix_Exp instance;
        return &instance;
    }
};

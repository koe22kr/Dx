#pragma once
#include "khg_Obj_Exp.h"
#define NUM_WI_EXPORT 8


class khg_Skin_Exp :public khg_Obj_Exp
{
    std::vector<INode*> m_SkinObjList;
public:
    void GetMesh(INode* pNode, TimeValue time, tempMesh& desc) override;
    bool    Convert() override;
    bool    Export() override;
    void Set(Interface* mMax) override;
    void    AddObject(INode* pNode, TimeValue time);

public:
    void SetBippedInfo(INode* pNode, tempMesh& tMesh);
    Modifier*  FindModifier(INode* pNode, Class_ID classID);
    void ExportPhysiqueData(INode* pNode, Modifier* pModi, tempMesh& tMesh);
    void ExportSkinData(INode* pNode, Modifier* pModi, tempMesh& tMesh);
    int GetFindIndex(INode* node);
    void SetUniqueBuffer(tempMesh& tMesh);
    void SortIWData(Raw_IW_VERTEX& rawwi,IW_VERTEX& outwi);
public:

    khg_Skin_Exp();
    ~khg_Skin_Exp();
    static khg_Skin_Exp* Get()
    {
        static khg_Skin_Exp instance;
        return &instance;
    }
};

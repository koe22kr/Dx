#pragma once
#include "khg_Obj_Exp.h"

struct WI_VERTEX
{
    float i1[4];
    float w1[4];
    float i2[4];
    float w2[4];
};

class khg_Skin_Exp :public khg_Obj_Exp
{

public:
    std::vector<WI_VERTEX> Raw_wi_List;
    std::vector<WI_VERTEX> Sorted_wi_List;// [인덱스] 프린트용WI;
public:
    bool    Convert() override;
    bool    Export() override;
    void  SetUniqueBuffer(tempMesh& tMesh) override;
    
public:
    void SetBippedInfo(INode* pNode, tempMesh& tMesh);
    Modifier*  FindModifier(INode* pNode, Class_ID classID);
    void ExportPhysiqueData(INode* pNode, Modifier*, tempMesh&);
    void ExportSkinData(INode* pNode, Modifier*, tempMesh&);
    int GetFindIndex(INode* node);
public:

    khg_Skin_Exp();
    ~khg_Skin_Exp();
};


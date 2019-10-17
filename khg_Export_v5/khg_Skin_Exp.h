#pragma once
#include "khg_Obj_Exp.h"
#define NUM_WI_EXPORT 8


struct Raw_WI_VERTEX
{
    std::vector<float> i;
    std::vector<float> w; //w[3]¿¡
};
struct WI_VERTEX
{
    float i1[4];
    float i2[4];
    float w1[4];
    float w2[4];
};
class khg_Skin_Exp :public khg_Obj_Exp
{

public:
    std::vector<Raw_WI_VERTEX> m_Raw_wi_List;
public:
    void GetMesh(INode* pNode, TimeValue time, tempMesh& desc) override;
    bool    Convert() override;
    bool    Export() override;
    
public:
    void SetBippedInfo(INode* pNode, tempMesh& tMesh);
    Modifier*  FindModifier(INode* pNode, Class_ID classID);
    void ExportPhysiqueData(INode* pNode, Modifier* pModi, tempMesh& tMesh);
    void ExportSkinData(INode* pNode, Modifier* pModi, tempMesh& tMesh);
    int GetFindIndex(INode* node);

    //
    void ExportIW(int index,FILE* pStream);
    void SortIW(Raw_WI_VERTEX& wi);
public:

    khg_Skin_Exp();
    ~khg_Skin_Exp();
    static khg_Skin_Exp* Get()
    {
        static khg_Skin_Exp instance;
        return &instance;
    }
};


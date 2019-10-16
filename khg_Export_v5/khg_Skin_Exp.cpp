#include "stdafx.h"
#include "khg_Skin_Exp.h"

void khg_Skin_Exp::ExportPhysiqueData(INode* pNode, Modifier*, tempMesh&)
{

}
void khg_Skin_Exp::ExportSkinData(INode* pNode, Modifier*, tempMesh&)
{

}
Modifier*  khg_Skin_Exp::FindModifier(INode* pNode, Class_ID classID)
{

}
void khg_Skin_Exp::SetBippedInfo(INode* pNode, tempMesh& tMesh)
{
    Modifier* phyModi = FindModifier(pNode, Class_ID(PHYSIQUE_CLASS_ID_A, PHYSIQUE_CLASS_ID_B));
    Modifier* skinModi = FindModifier(pNode, SKIN_CLASSID);
    if (phyModi)
    {
        ExportPhysiqueData(pNode, phyModi, tMesh);
        
    }
    if (skinModi)
    {
        ExportSkinData(pNode, skinModi, tMesh);

    }
}

bool    khg_Skin_Exp::Convert()
{
    //std::vector<TBipedVertex> bipedList;
    for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
    {
        INode* pNode = m_ObjList[iObj];
        tempMesh tMesh;
        tMesh.name = FixupName(pNode->GetName());
        INode* pParentNode = pNode->GetParentNode();
        if (pParentNode &&
            // 가상의 부모가 존재
            pParentNode->IsRootNode() == false)
        {
            tMesh.ParentName =
                FixupName(pParentNode->GetName());
        }

        SetBippedInfo(pNode, tMesh);

        // objTM = s*r*t*p * c;
        // GetNodeTM = srt * p;
        /*Matrix3 wtm = pNode->GetNodeTM(m_Interval.Start());
        DumpMatrix3(wtm, tMesh.matWorld);
        Matrix3 invWtm = Inverse(wtm);
        DumpMatrix3(invWtm, tMesh.matInvWorld);*/     // 
#pragma message(TODO("export에서 뼈 좌표로 뽑기."))
        // 메터리얼 정보 얻고 / 저장
        Mtl* pMtl = pNode->GetMtl();
        if (pMtl)

            tMesh.iMtrlID = FindMaterial(pNode);
        if (tMesh.iMtrlID >= 0 &&
            m_MtrlList[tMesh.iMtrlID].subMtrl.size() > 0)
        {
            tMesh.iSubMesh = m_MtrlList[tMesh.iMtrlID].subMtrl.size();
        }
        GetMesh(pNode, tMesh);
        m_tbMeshList.push_back(tMesh);

    }
    return true;
}
bool    khg_Skin_Exp::Export()
{
    return true;
}

khg_Skin_Exp::khg_Skin_Exp()
{
}


khg_Skin_Exp::~khg_Skin_Exp()
{
}

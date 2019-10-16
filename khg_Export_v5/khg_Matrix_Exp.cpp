#include "stdafx.h"
#include "khg_Matrix_Exp.h"

bool    khg_Matrix_Exp::Convert()
{
    //for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
    //{
    //    INode* pNode = m_ObjList[iObj];
    //    tempMesh tMesh;
    //    tMesh.name = FixupName(pNode->GetName());
    //    INode* pParentNode = pNode->GetParentNode();
    //    if (pParentNode &&
    //        // 가상의 부모가 존재
    //        pParentNode->IsRootNode() == false)
    //    {
    //        tMesh.ParentName =
    //            FixupName(pParentNode->GetName());
    //    }
    //    Matrix3 wtm = pNode->GetNodeTM(m_Interval.Start());
    //    DumpMatrix3(wtm, tMesh.matWorld);

    //    // helper || biped
    //    Object* pObj = pNode->GetObjectRef();
    //    Control* pControl = pNode->GetTMController();

    //    tMesh.iType = CLASS_GEOM;
    //    if (pObj && pObj->ClassID()
    //        == Class_ID(BONE_CLASS_ID, 0))
    //    {
    //        tMesh.iType = CLASS_BONE;
    //    }
    //    if (pObj && pObj->ClassID()
    //        == Class_ID(DUMMY_CLASS_ID, 0))
    //    {
    //        tMesh.iType = CLASS_DUMMY;
    //    }
    //    if (pControl && pControl->ClassID()
    //        == BIPBODY_CONTROL_CLASS_ID)
    //    {
    //        tMesh.iType = CLASS_BIPED;
    //    }
    //    if (pControl && pControl->ClassID()
    //        == BIPSLAVE_CONTROL_CLASS_ID)
    //    {
    //        tMesh.iType = CLASS_BIPED;
    //    }

    //    if (tMesh.iType > 0)//GEO 아니면
    //    {
    //        GetMesh(pNode,0, tMesh);
    //    }
    //    GetAnimation(pNode, tMesh);
    //    m_tMeshList.push_back(tMesh);
    //}
    return true;
}
bool    khg_Matrix_Exp::Export()
{

    return true;
}

khg_Matrix_Exp::khg_Matrix_Exp()
{
}


khg_Matrix_Exp::~khg_Matrix_Exp()
{
}

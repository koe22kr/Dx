#include "stdafx.h"
#include "khg_Matrix_Exp.h"


bool    khg_Matrix_Exp::Convert()
{
#pragma message (TODO("GetMesh 조건문 변화있엇음."))
    for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
    {
        box_list.resize(m_ObjList.size());
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
        // helper || biped
        Object* pObj = pNode->GetObjectRef();
        Control* pControl = pNode->GetTMController();

        tMesh.iType = CLASS_GEOM;
        if (pObj && pObj->ClassID()
            == Class_ID(BONE_CLASS_ID, 0))
        {
            tMesh.iType = CLASS_BONE;
        }
        if (pObj && pObj->ClassID()
            == Class_ID(DUMMY_CLASS_ID, 0))
        {
            tMesh.iType = CLASS_DUMMY;
        }
        if (pControl && pControl->ClassID()
            == BIPBODY_CONTROL_CLASS_ID)
        {
            tMesh.iType = CLASS_BIPED;
        }
        if (pControl && pControl->ClassID()
            == BIPSLAVE_CONTROL_CLASS_ID)
        {
            tMesh.iType = CLASS_BIPED;
        }
        
        GetAnimation(pNode, tMesh);
        /*if (tMesh.iType > 0)
        {*/
            pObj->GetDeformBBox(0, box_list[m_tempMesh_List.size()], &pNode->GetObjectTM(0));
        //}
        m_tempMesh_List.push_back(tMesh);
    }
    return true;
}
bool    khg_Matrix_Exp::Export()
{
    Convert();

    FILE* pStream = nullptr;
    _tfopen_s(&pStream, m_filename.c_str(), _T("wt"));
    _ftprintf(pStream, _T("%s %d"), _T("khgExporter_100"), m_ObjList.size());
    _ftprintf(pStream, _T("\n%d %d %d %d"), m_Scene.iFirst_Frame, m_Scene.iLast_Frame, m_Scene.iFrame_Speed, m_Scene.iTick_Per_Frame);

    for (int iObj = 0; iObj < m_tempMesh_List.size(); iObj++)
    {
        _ftprintf(pStream, _T("\n%s %s"),
            m_tempMesh_List[iObj].name,
            m_tempMesh_List[iObj].ParentName);

        //애니메이션 data 출력
        ExportAnimation(m_tempMesh_List[iObj], pStream, iObj);

    }

    fclose(pStream);
    //메시지 박스 하나
    MessageBox(GetActiveWindow(), m_filename.c_str(), L"Succsess", MB_OK);/////////////////////////////////////////
    return true;
}
void khg_Matrix_Exp::ExportAnimation(tempMesh& tmesh, FILE* pstream,int index)
{
    _ftprintf(pstream, _T("\n%s %d %d %d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f"),
        L"AnimationData:",
        (tmesh.bAnimation[0]) ? tmesh.Anim_S.size() : 1,
        (tmesh.bAnimation[1]) ? tmesh.Anim_R.size() : 1,
        (tmesh.bAnimation[2]) ? tmesh.Anim_T.size() : 1,
        box_list[index].pmin.x, box_list[index].pmin.z, box_list[index].pmin.y,
        box_list[index].pmax.x, box_list[index].pmax.z, box_list[index].pmax.y);
    if (tmesh.bAnimation[0])
    {
        for (int iTrack = 0; iTrack < tmesh.Anim_S.size(); iTrack++)
        {
            _ftprintf(pstream, _T("\n%d %d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f"),
                iTrack,
                tmesh.Anim_S[iTrack].i,
                tmesh.Anim_S[iTrack].p.x,
                tmesh.Anim_S[iTrack].p.z,
                tmesh.Anim_S[iTrack].p.y,
                tmesh.Anim_S[iTrack].q.x,
                tmesh.Anim_S[iTrack].q.z,
                tmesh.Anim_S[iTrack].q.y,
                tmesh.Anim_S[iTrack].q.w);
        }
    }
    else
    {
        _ftprintf(pstream, _T("\n%d %d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f"),
            0,
            tmesh.Anim_S[0].i,
            tmesh.Anim_S[0].p.x,
            tmesh.Anim_S[0].p.z,
            tmesh.Anim_S[0].p.y,
            tmesh.Anim_S[0].q.x,
            tmesh.Anim_S[0].q.z,
            tmesh.Anim_S[0].q.y,
            tmesh.Anim_S[0].q.w);
    }
    if (tmesh.bAnimation[1])
    {
        for (int iTrack = 0; iTrack < tmesh.Anim_R.size(); iTrack++)
        {
            _ftprintf(pstream, _T("\n%d %d %10.4f %10.4f %10.4f %10.4f"),
                iTrack,
                tmesh.Anim_R[iTrack].i,
                tmesh.Anim_R[iTrack].q.x,
                tmesh.Anim_R[iTrack].q.z,
                tmesh.Anim_R[iTrack].q.y,
                tmesh.Anim_R[iTrack].q.w);
        }
    }
    else
    {
        _ftprintf(pstream, _T("\n%d %d %10.4f %10.4f %10.4f %10.4f"),
            0,
            tmesh.Anim_R[0].i,
            tmesh.Anim_R[0].q.x,
            tmesh.Anim_R[0].q.z,
            tmesh.Anim_R[0].q.y,
            tmesh.Anim_R[0].q.w);
    }
    if (tmesh.bAnimation[2])
    {
        for (int iTrack = 0; iTrack < tmesh.Anim_T.size(); iTrack++)
        {


            _ftprintf(pstream, _T("\n%d %d %10.4f %10.4f %10.4f"),
                iTrack,
                tmesh.Anim_T[iTrack].i,
                tmesh.Anim_T[iTrack].p.x,
                tmesh.Anim_T[iTrack].p.z,
                tmesh.Anim_T[iTrack].p.y);
        }
    }
    else
    {
        _ftprintf(pstream, _T("\n%d %d %10.4f %10.4f %10.4f"),
            0,
            tmesh.Anim_T[0].i,
            tmesh.Anim_T[0].p.x,
            tmesh.Anim_T[0].p.z,
            tmesh.Anim_T[0].p.y);

    }
}


void khg_Matrix_Exp::Set(Interface* mMax)
{

    if (mMax == nullptr)return;
    if (mMax == m_pMax && m_ObjList.size() != 0)
    {
        m_tempMesh_List.clear();
    }
    else
    {
        m_ObjList.clear();
        m_MaterialList.clear();
        m_MtlInfoList.clear();
        m_tempMesh_List.clear();
        m_Scene.init();
        m_pMax = mMax;
        m_pRootNode = m_pMax->GetRootNode();
        m_Interval = m_pMax->GetAnimRange();
        m_Scene.iFirst_Frame = m_Interval.Start() / GetTicksPerFrame();
        m_Scene.iLast_Frame = m_Interval.End() / GetTicksPerFrame();
        m_Scene.iFrame_Speed = GetFrameRate();
        m_Scene.iTick_Per_Frame = GetTicksPerFrame();
        PreProcess(m_pRootNode, m_Interval.Start());
    }

}
void khg_Matrix_Exp::AddMaterial(INode* pNode)
{
    //PreProcess 에서 호출시 아무것도 안할.
}
khg_Matrix_Exp::khg_Matrix_Exp()
{
}
khg_Matrix_Exp::~khg_Matrix_Exp()
{
}

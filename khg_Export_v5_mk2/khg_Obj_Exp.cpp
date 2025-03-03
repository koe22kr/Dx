#include "stdafx.h"
#include "khg_Obj_Exp.h"

//////////////////////////
bool khg_Obj_Exp::EqualPoint2(Point2 p1, Point2 p2)
{
    if (fabs(p1.x - p2.x) > ALMOST_ZERO)
        return false;
    if (fabs(p1.y - p2.y) > ALMOST_ZERO)
        return false;
    return true;
}
bool khg_Obj_Exp::EqualPoint3(Point3 p1, Point3 p2)
{
    if (fabs(p1.x - p2.x) > ALMOST_ZERO)
        return false;
    if (fabs(p1.y - p2.y) > ALMOST_ZERO)
        return false;
    if (fabs(p1.z - p2.z) > ALMOST_ZERO)
        return false;

    return true;
}
bool khg_Obj_Exp::EqualPoint4(Point4 p1, Point4 p2)
{
    if (fabs(p1.x - p2.x) > ALMOST_ZERO)
        return false;
    if (fabs(p1.y - p2.y) > ALMOST_ZERO)
        return false;
    if (fabs(p1.z - p2.z) > ALMOST_ZERO)
        return false;
    if (fabs(p1.w - p2.w) > ALMOST_ZERO)
        return false;
    return true;
}
void   khg_Obj_Exp::DumpMatrix3(Matrix3& matWorld, D3D_MATRIX& world)
{
    Point3 row;
    row = matWorld.GetRow(0);
    world._11 = row.x;
    world._13 = row.y;
    world._12 = row.z;
    world._14 = 0.0f;
    row = matWorld.GetRow(2);
    world._21 = row.x;
    world._23 = row.y;
    world._22 = row.z;
    world._24 = 0.0f;
    row = matWorld.GetRow(1);
    world._31 = row.x;
    world._33 = row.y;
    world._32 = row.z;
    world._34 = 0.0f;
    row = matWorld.GetRow(3);
    world._41 = row.x;
    world._43 = row.y;
    world._42 = row.z;
    world._44 = 1.0f;
}
void	khg_Obj_Exp::DumpPoint3(Point3& desc, Point3& src)
{
    desc.x = src.x;
    desc.y = src.z;
    desc.z = src.y;
}
TCHAR* khg_Obj_Exp::FixupName(MSTR name)
{
    TCHAR m_tmpBuffer[MAX_PATH] = { 0, };
    memset(m_tmpBuffer, 0, sizeof(TCHAR)*MAX_PATH);

    TCHAR* cPtr;
    _tcscpy_s(m_tmpBuffer, name);
    cPtr = m_tmpBuffer;

    while (*cPtr)
    {
        if (*cPtr == '"')		*cPtr = SINGLE_QUOTE;
        else if (*cPtr == ' ' || *cPtr <= CTL_CHARS)
            *cPtr = _T('_');
        cPtr++;
    }
    return m_tmpBuffer;
#pragma message(TODO("지역변수 반환하는거 시간되면 수정할 방법 생각해보기."))
}
struct AscendingSort
{
    bool operator()(TriList& rpStart, TriList& rpEnd)
    {
        return rpStart.iSubIndex > rpEnd.iSubIndex;
    }
};
static int g_iSearchIndex = 0;
struct IsSameInt // find_to와 같은지 판단해 주는 함수자   
{
    bool operator()(TriList &value)
    {
        return value.iSubIndex == g_iSearchIndex;
    }
};
int khg_Obj_Exp::IsEqulVertexList(PNCT& vertex, VertexList& vList)
{
    for (int iVer = 0; iVer < vList.size(); iVer++)
    {
        if (EqualPoint3(vertex.p, vList[iVer].p) &&
            EqualPoint3(vertex.n, vList[iVer].n) &&
            EqualPoint4(vertex.c, vList[iVer].c) &&
            EqualPoint2(vertex.t, vList[iVer].t))
        {
            return iVer;
        }
    }
    return -1;
}
//////////////////////////
void khg_Obj_Exp::Set( Interface* mMax)
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
void    khg_Obj_Exp::PreProcess(INode* pNode, TimeValue time)
{
    if (!pNode)return;
    AddObject(pNode, time);
    AddMaterial(pNode);

    int iNumChildren = pNode->NumberOfChildren();
    for (int iChild = 0; iChild < iNumChildren; iChild++)
    {
        INode* pChild = pNode->GetChildNode(iChild);
        PreProcess(pChild, time);
    }
}
bool  khg_Obj_Exp::Convert()
{
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
        // objTM = s*r*t*p * c;
        // GetNodeTM = srt * p;
        Matrix3 wtm = pNode->GetNodeTM(0);
        tMesh.matworld_inv = Inverse(wtm);
        DumpMatrix3(wtm, tMesh.matWorld);

        tMesh.iMtrlID = FindMaterial(pNode);  //이전에 addmaterial 해야함.
        if (tMesh.iMtrlID >= 0 &&m_MtlInfoList[tMesh.iMtrlID].subMtrl.size() > 0)
        {
            tMesh.iSubMesh = m_MtlInfoList[tMesh.iMtrlID].subMtrl.size();
        }

        GetMesh(pNode, 0, tMesh);
        GetAnimation(pNode, tMesh);
        m_tempMesh_List.push_back(tMesh);
    }
    return true;
}
void khg_Obj_Exp::GetAnimation(INode* pNode, tempMesh& tMesh)
{
    tMesh.bAnimation[0] = false;
    tMesh.bAnimation[1] = false;
    tMesh.bAnimation[2] = false;
    //0프래임의 값
    TimeValue startframe = m_Interval.Start();
    Matrix3 tm =/* Inverse(pNode->GetNodeTM(startframe)) **/ pNode->GetNodeTM(startframe)*Inverse(pNode->GetParentTM(startframe));
    //자신의tm * 부모 inv tm//원점의 변형tm
    //Matrix3 tm = pNode->GetNodeTM(startframe);
    AffineParts StartAP;
    decomp_affine(tm, &StartAP);

    Point3 Start_RotAxis;
    float Start_RotValue;
    AngAxisFromQ(StartAP.q, &Start_RotValue, Start_RotAxis);

    AnimTrack start_track;
    ZeroMemory(&start_track,sizeof(AnimTrack));
    start_track.i = startframe;
    
    start_track.p = StartAP.t;
    start_track.q = StartAP.q;
    tMesh.Anim_R.push_back(start_track);
    tMesh.Anim_T.push_back(start_track);
    start_track.p = StartAP.k;
    start_track.q = StartAP.u;
    tMesh.Anim_S.push_back(start_track);
    // 
    TimeValue start = m_Interval.Start() + GetTicksPerFrame();
    TimeValue end = m_Interval.End();
    for (TimeValue frame = start; frame <= end; frame += GetTicksPerFrame())
    {
        Matrix3 tm = /*Inverse(pNode->GetNodeTM(startframe)) **/ pNode->GetNodeTM(frame)*Inverse(pNode->GetParentTM(frame));
        //Matrix3 tm =pNode->GetNodeTM(frame);
        AffineParts FrameAP;
        decomp_affine(tm, &FrameAP);

        AnimTrack frame_stack;
        ZeroMemory(&frame_stack, sizeof(AnimTrack));
        frame_stack.i = frame;
        frame_stack.p = FrameAP.t;
        frame_stack.q = FrameAP.q;
        tMesh.Anim_T.push_back(frame_stack);
        tMesh.Anim_R.push_back(frame_stack);
        frame_stack.p = FrameAP.k;
        frame_stack.q = FrameAP.u;
        tMesh.Anim_S.push_back(frame_stack);

        Point3 Frame_RotAxis;
        float Frame_RotValue;
        AngAxisFromQ(FrameAP.q, &Frame_RotValue, Frame_RotAxis);

        if (!tMesh.bAnimation[0]) {
            if (!EqualPoint3(StartAP.k, FrameAP.k))//u도 비교 해야하지 않을까?..
            {
                tMesh.bAnimation[0] = true;
            }
        }

        if (!tMesh.bAnimation[1]) {
            if (!EqualPoint3(Start_RotAxis, Frame_RotAxis))
            {
                tMesh.bAnimation[1] = true;
            }
            else
            {
                if (Frame_RotValue != Frame_RotValue)
                {
                    tMesh.bAnimation[1] = true;
                }
            }
        }

        if (!tMesh.bAnimation[2]) {
            if (!EqualPoint3(StartAP.t, FrameAP.t))
            {
                tMesh.bAnimation[2] = true;
            }
        }

    }
}

void khg_Obj_Exp::AddMaterial(INode* pNode)
{
    Mtl* pMtl = pNode->GetMtl();
    if (pMtl)
    {
        for (int iMtl = 0; iMtl < m_MaterialList.size(); iMtl++)
        {
            if (m_MaterialList[iMtl] == pMtl)
            {
                return;
            }
        }
        m_MaterialList.push_back(pMtl);
        GetMaterial(pNode);
    }
}
void khg_Obj_Exp::GetMaterial(INode* pNode)
{
    Mtl* pRootMtl = pNode->GetMtl();
    MtlInfo mi;
    mi.szName = FixupName(pRootMtl->GetName());
    // sub-material
    int iNumSub = pRootMtl->NumSubMtls();
    if (iNumSub > 0)
    {
        for (int iSub = 0; iSub < iNumSub; iSub++)
        {
            Mtl* pSubMtl = pRootMtl->GetSubMtl(iSub);
            MtlInfo  tSubMtrl;
            tSubMtrl.szName = FixupName(pSubMtl->GetName());
            GetTexture(pSubMtl, tSubMtrl);
            mi.subMtrl.push_back(tSubMtrl);
        }
    }
    else
    {
        GetTexture(pRootMtl, mi);
    }
    m_MtlInfoList.push_back(mi);

    //GetTexture(pRootMtl);
}
int khg_Obj_Exp::FindMaterial(INode* pNode)
{
    Mtl* pMtl = pNode->GetMtl();
    if (pMtl)
    {
        for (int iMtl = 0; iMtl < m_MtlInfoList.size(); iMtl++)
        {
            if (m_MaterialList[iMtl] == pMtl)
            {
                return iMtl;
            }
        }
    }
    return -1;
}
void  khg_Obj_Exp::GetTexture(Mtl* pMtl, MtlInfo& desc)
{
    int iNumMap = pMtl->NumSubTexmaps();
    for (int iSubMap = 0; iSubMap < iNumMap; iSubMap++)
    {
        Texmap* tex = pMtl->GetSubTexmap(iSubMap);
        if (tex)
        {
            if (tex->ClassID() == Class_ID(BMTEX_CLASS_ID, 0X00))
            {
                texInfo ti;
                ti.iMapID = iSubMap;

                TSTR fullName;
                TSTR mapName = ((BitmapTex*)(tex))->GetMapName();
                SplitPathFile(mapName, &fullName, &ti.szName);
                desc.TextureList.push_back(ti);
            }
        }
    }
}
bool khg_Obj_Exp::Export()
{
    Convert();

    FILE* pStream = nullptr;
    _tfopen_s(&pStream, m_filename.c_str(), _T("wt"));
    _ftprintf(pStream, _T("%s"), _T("khgExporter_100"));
    _ftprintf(pStream, _T("\n%d %d %d %d %d %d"),m_Scene.iFirst_Frame, m_Scene.iLast_Frame, m_Scene.iFrame_Speed, m_Scene.iTick_Per_Frame, m_ObjList.size(), m_MtlInfoList.size());
    for (int iMtl = 0; iMtl < m_MtlInfoList.size(); iMtl++)
    {
        

        _ftprintf(pStream, _T("\n%s %d"),
            /*m_MtlInfoList[iMtl].iMapID,*/
            m_MtlInfoList[iMtl].szName,
            m_MtlInfoList[iMtl].subMtrl.size());

        if (m_MtlInfoList[iMtl].subMtrl.size() > 0)
        {
            for (int iSubMtrl = 0; iSubMtrl < m_MtlInfoList[iMtl].subMtrl.size(); iSubMtrl++)
            {
                _ftprintf(pStream, _T("\n%s %d"),
                    m_MtlInfoList[iMtl].subMtrl[iSubMtrl].szName,
                    m_MtlInfoList[iMtl].subMtrl[iSubMtrl].TextureList.size());

                for (int iTex = 0; iTex < m_MtlInfoList[iMtl].subMtrl[iSubMtrl].TextureList.size(); iTex++)
                {
                    _ftprintf(pStream, _T("\n%d %s"),
                        m_MtlInfoList[iMtl].subMtrl[iSubMtrl].TextureList[iTex].iMapID,
                        m_MtlInfoList[iMtl].subMtrl[iSubMtrl].TextureList[iTex].szName);
                }
            }
        }
        else
        {
            _ftprintf(pStream, _T("\n%s %d"),
                L"none",
                m_MtlInfoList[iMtl].TextureList.size()
            );

            for (int iTex = 0; iTex < m_MtlInfoList[iMtl].TextureList.size(); iTex++)
            {
                _ftprintf(pStream, _T("\n%d %s"),
                    m_MtlInfoList[iMtl].TextureList[iTex].iMapID,
                    m_MtlInfoList[iMtl].TextureList[iTex].szName);
            }
        }
    }
    // mesh list
    //INode* pNode = m_ObjList[iMtl];
    //_ftprintf(pStream, _T("\n%s %d %d"), pNode->GetName(), m_FaceInfoList.size(), m_tempMesh_List[iMtl].triList_List.size());

    for (int iObj = 0; iObj < m_tempMesh_List.size(); iObj++)
    {
        _ftprintf(pStream, _T("\n%s %s %d %d %d %d "),
            m_tempMesh_List[iObj].name,
            m_tempMesh_List[iObj].ParentName,
            /*m_tempMesh_List[iObj].iMtrlID,*/
            m_tempMesh_List[iObj].triList_List.size(),
            m_tempMesh_List[iObj].bAnimation[0],
            m_tempMesh_List[iObj].bAnimation[1],
            m_tempMesh_List[iObj].bAnimation[2]

          
        );

        /*_ftprintf(pStream, _T("\n\t%10.4f %10.4f %10.4f %10.4f\n\t%10.4f %10.4f %10.4f %10.4f\n\t%10.4f %10.4f %10.4f %10.4f\n\t%10.4f %10.4f %10.4f %10.4f"),
            m_tempMesh_List[iObj].matWorld._11,
            m_tempMesh_List[iObj].matWorld._12,
            m_tempMesh_List[iObj].matWorld._13,
            m_tempMesh_List[iObj].matWorld._14,

            m_tempMesh_List[iObj].matWorld._21,
            m_tempMesh_List[iObj].matWorld._22,
            m_tempMesh_List[iObj].matWorld._23,
            m_tempMesh_List[iObj].matWorld._24,

            m_tempMesh_List[iObj].matWorld._31,
            m_tempMesh_List[iObj].matWorld._32,
            m_tempMesh_List[iObj].matWorld._33,
            m_tempMesh_List[iObj].matWorld._34,

            m_tempMesh_List[iObj].matWorld._41,
            m_tempMesh_List[iObj].matWorld._42,
            m_tempMesh_List[iObj].matWorld._43,
            m_tempMesh_List[iObj].matWorld._44);*/


        ///
        for (int iSubTri = 0; iSubTri < m_tempMesh_List[iObj].triList_List.size(); iSubTri++)
        {
            VertexList& vList = m_tempMesh_List[iObj].vb[iSubTri];
            _ftprintf(pStream, _T("\nVertex: %d"), vList.size());
            for (int iVer = 0; iVer < vList.size(); iVer++)
            {
                _ftprintf(pStream, _T("\n%10.4f %10.4f %10.4f"),
                    vList[iVer].p.x,
                    vList[iVer].p.y,
                    vList[iVer].p.z);
                _ftprintf(pStream, _T("%10.4f %10.4f %10.4f"),
                    vList[iVer].n.x,
                    vList[iVer].n.y,
                    vList[iVer].n.z);
                _ftprintf(pStream, _T("%10.4f %10.4f %10.4f %10.4f"),
                    vList[iVer].c.x,
                    vList[iVer].c.y,
                    vList[iVer].c.z,
                    vList[iVer].c.w);
                _ftprintf(pStream, _T("%10.4f %10.4f"),
                    vList[iVer].t.x,
                    vList[iVer].t.y);

            }

            IndexList& iList =
                m_tempMesh_List[iObj].ib[iSubTri];
            _ftprintf(pStream, _T("\nIndex: %d"), iList.size());
            for (int iIndex = 0; iIndex < iList.size(); iIndex += 3)
            {
                _ftprintf(pStream, _T("\n%d %d %d"),
                    iList[iIndex + 0],
                    iList[iIndex + 1],
                    iList[iIndex + 2]);
            }
        }
        //애니메이션 data 출력
        ExportAnimation(m_tempMesh_List[iObj], pStream);

    }

    


    fclose(pStream);
    //메시지 박스 하나
    MessageBox(GetActiveWindow(), m_filename.c_str(), L"Succsess", MB_OK);/////////////////////////////////////////
    return true;
}

void khg_Obj_Exp::ExportAnimation(tempMesh& tmesh, FILE* pstream)
{
    _ftprintf(pstream, _T("\n%s %d %d %d"),
        L"AnimationData:",
        (tmesh.bAnimation[0]) ? tmesh.Anim_S.size() : 1,
        (tmesh.bAnimation[1]) ? tmesh.Anim_R.size() : 1,
        (tmesh.bAnimation[2]) ? tmesh.Anim_T.size() : 1);
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

void    khg_Obj_Exp::AddObject(INode* pNode, TimeValue time)
{

    ObjectState os = pNode->EvalWorldState(time);
    if (os.obj)
    {
        if (os.obj->ClassID() == Class_ID(TARGET_CLASS_ID, 0))
        {
            return;
        }

        switch (os.obj->SuperClassID())
        {
        case GEOMOBJECT_CLASS_ID:
        case HELPER_CLASS_ID:
        {
            m_ObjList.push_back(pNode);
        }
        
        default:
            break;
        }
    }

}
bool khg_Obj_Exp::TMNegParity(Matrix3 tm)
{
    Point3 v0 = tm.GetRow(0);
    Point3 v1 = tm.GetRow(1);
    Point3 v2 = tm.GetRow(2);
    Point3 vCross = CrossProd(v0, v1);
    return (DotProd(vCross, v2) < 0.0f) ? true : false;
    return true;
}
void    khg_Obj_Exp::GetMesh(INode* pNode, TimeValue time, tempMesh& desc)
{
    Matrix3 tm = pNode->GetObjTMAfterWSM(time);
    Matrix3 invtm;
    Inverse(invtm, pNode->GetNodeTM(time));
    ///////////////////////1) 트라이엥글 오브젝트[]
    bool deleteit = false;
    TriObject* tri = AddTriangleFromObject(pNode, time, deleteit);
    if (tri == nullptr) return;
    ///////////////////////2) 메쉬 오브젝트
    Mesh* mesh = &tri->GetMesh();
    bool negScale = TMNegParity(tm);
    int v0, v1, v2;
    if (negScale)
    {
        v0 = 2; v1 = 1; v2 = 0;
    }
    else
    {
        v0 = 0; v1 = 1; v2 = 2;
    }

    if (mesh)                                                         //X,Y축이 반대라 0 2 1 순으로 받아서 0 1 2 순서로 넣는다.
    {
        //페이스
        int iFacenum = mesh->numFaces;
        vectorTriList& tri = desc.triList;
        tri.resize(iFacenum);
        desc.triList_List.resize(desc.iSubMesh);


        //DWORD num[3];
        /* int iNumVertex = mesh->getNumVerts();
         m_VertexList.resize(iNumVertex);*/



        for (int iface = 0; iface < iFacenum; iface++)
        {
            
            
            

            //Position//
            int iNumPos = mesh->getNumVerts();
            if (iNumPos > 0)
            {
                
               

                Point3 p3 = mesh->verts[mesh->faces[iface].v[v0]] * tm * invtm;    //tm 곱해주면 그전이 어느 좌표계든 월드로 변환됨// + invtm 곱해서 뼈좌표계로
                DumpPoint3(tri[iface].v[0].p, p3);

                p3 = mesh->verts[mesh->faces[iface].v[v2]] * tm * invtm;
                DumpPoint3(tri[iface].v[1].p, p3);

                p3 = mesh->verts[mesh->faces[iface].v[v1]] * tm * invtm;
                DumpPoint3(tri[iface].v[2].p, p3);
            }
            //Color// 
            int iNumColor = mesh->getNumVertCol();
            tri[iface].v[0].c = Point4(1, 1, 1, 1);
            tri[iface].v[1].c = Point4(1, 1, 1, 1);
            tri[iface].v[2].c = Point4(1, 1, 1, 1);
            if (iNumColor > 0)
            {
               tri[iface].v[0].c = mesh->vertCol[mesh->vcFace[iface].t[v0]];
               tri[iface].v[1].c = mesh->vertCol[mesh->vcFace[iface].t[v2]];
               tri[iface].v[2].c = mesh->vertCol[mesh->vcFace[iface].t[v1]];
            }


            //Texcoord//
            int INumTex = mesh->getNumTVerts();
            if (INumTex > 0)
            {
                Point2 p2 = (Point2)mesh->tVerts[mesh->tvFace[iface].t[v0]];
                tri[iface].v[0].t.x = p2.x;
                tri[iface].v[0].t.y = 1.0f - p2.y;

                p2 = (Point2)mesh->tVerts[mesh->tvFace[iface].t[v2]];
                tri[iface].v[1].t.x = p2.x;
                tri[iface].v[1].t.y = 1.0f - p2.y;
               
                p2 = (Point2)mesh->tVerts[mesh->tvFace[iface].t[v1]];
                tri[iface].v[2].t.x = p2.x;
                tri[iface].v[2].t.y = 1.0f - p2.y;
            }

            //Normal//
            //GetVertexNormal 완전 이해는 어려우면 걍 쓰기.?

            mesh->buildNormals();
            int vert = mesh->faces[iface].getVert(v0);
            RVertex* rVertex = mesh->getRVertPtr(vert);
            Point3 vn = GetVertexNormal(mesh, iface, rVertex);
            DumpPoint3(tri[iface].v[v0].n, vn);

            vert = mesh->faces[iface].getVert(v2);
            rVertex = mesh->getRVertPtr(vert);
            vn = GetVertexNormal(mesh, iface, rVertex);
            DumpPoint3(tri[iface].v[v1].n, vn);

            vert = mesh->faces[iface].getVert(v1);
            rVertex = mesh->getRVertPtr(vert);
            vn = GetVertexNormal(mesh, iface, rVertex);
            DumpPoint3(tri[iface].v[v2].n, vn);

            // sub material index
            tri[iface].iSubIndex =
                mesh->faces[iface].getMatID();
            if (tri[iface].iSubIndex <0/*||desc.iMtrlID <= 0*/ /*|| m_MtlInfoList[desc.iMtrlID].subMtrl.size() > tri[iface].iSubIndex*/)
            {
                tri[iface].iSubIndex = 0;
                tri[iface].v[0].c.w = -1;
                tri[iface].v[1].c.w = -1;
                tri[iface].v[2].c.w = -1;
            }
            else
            {
                //c.w 에 서브마태리얼 삽입
                tri[iface].v[0].c.w = tri[iface].iSubIndex;
                tri[iface].v[1].c.w = tri[iface].iSubIndex;
                tri[iface].v[2].c.w = tri[iface].iSubIndex;
            }
            desc.triList_List[
                tri[iface].iSubIndex].push_back(
                    tri[iface]);

        }
        //vb 만들.
        SetUniqueBuffer(desc);
    }
    if (deleteit) delete tri;
}
void khg_Obj_Exp::SetUniqueBuffer(tempMesh& tMesh)
{
    tMesh.vb.resize(tMesh.triList_List.size());
    tMesh.ib.resize(tMesh.triList_List.size());
    for (int iSub = 0; iSub < tMesh.triList_List.size();
        iSub++)
    {
        for (int iFace = 0; iFace < tMesh.triList_List[iSub].size(); iFace++)
        {
            vectorTriList& triArray = tMesh.triList_List[iSub];
            TriList& tri = triArray[iFace];
            VertexList& vList = tMesh.vb[iSub];
            IndexList& iList = tMesh.ib[iSub];
            for (int iVer = 0; iVer < 3; iVer++)
            {
                int iPos = IsEqulVertexList(tri.v[iVer], vList);
                if (iPos < 0)
                {
                    vList.push_back(tri.v[iVer]);
                    iPos = vList.size() - 1;
                }
                iList.push_back(iPos);
            }
        }
    }
   
}
Point3 khg_Obj_Exp::GetVertexNormal(Mesh* mesh, int iFace, RVertex* rVertex)///////////
{
    Face* face = &mesh->faces[iFace];

    DWORD smGroup = face->smGroup;
    int numNormals = rVertex->rFlags &NORCT_MASK;//Normal count _ mask ?

    Point3 vertexNormal;
    if (rVertex->rFlags& SPECIFIED_NORMAL)   //확정 노말..? 단일? face노말?
    {
        vertexNormal = rVertex->rn.getNormal();
    }
    else if (numNormals && smGroup)
    {
        if (numNormals == 1)
        {
            vertexNormal = rVertex->rn.getNormal();
        }
        else
        {
            for (int i = 0; i < numNormals; i++)
            {
                if (rVertex->ern[i].getSmGroup()&smGroup)
                {
                    vertexNormal = rVertex->ern[i].getNormal();
                }
            }
        }
    }
    else
    {
        vertexNormal = mesh->getFaceNormal(iFace);

    }
    return vertexNormal;
}
TriObject*    khg_Obj_Exp::AddTriangleFromObject(INode* pNode, TimeValue time, bool& 
DeleteIt)
{
    Object* obj = pNode->EvalWorldState(time).obj;
    if (obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0)))
    {
        TriObject* tri = (TriObject*)obj->ConvertToType(time, Class_ID(TRIOBJ_CLASS_ID, 0));
        if (obj != tri) DeleteIt = true;
        return tri;
    }
    return nullptr;
}
TCHAR* khg_Obj_Exp::SaveFileDlg(TCHAR* szExt, TCHAR* szTitle)
{
    TCHAR szFile[MAX_PATH] = { 0, };
    TCHAR szFileTitleFile[MAX_PATH] = { L"skx", };
    static TCHAR *szFilter = {L"Skin_X(*.skx)\0*.skx\0AllFiles(*.*)\0*.*\0"};
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    _tcscpy_s(szFile, _T("*."));
    _tcscat_s(szFile, szExt);
    _tcscat_s(szFile, _T("\0"));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = GetActiveWindow();
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0L;
    ofn.nFilterIndex = 3;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFileTitle = szFileTitleFile;
    ofn.nMaxFileTitle = sizeof(szFileTitleFile);
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = szTitle;
    ofn.Flags = 0L;
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = szExt;
    if (!GetSaveFileName(&ofn))
    {
        return NULL;
    }
    m_filename = szFile;

    return szFile;
}

khg_Obj_Exp::khg_Obj_Exp()
{
}
khg_Obj_Exp::~khg_Obj_Exp()
{
}
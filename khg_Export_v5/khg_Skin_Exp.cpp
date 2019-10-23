#include "stdafx.h"
#include "khg_Skin_Exp.h"
#include <algorithm>

void khg_Skin_Exp::SortRawData(Raw_WI_VERTEX& rawwi, IW_VERTEX& outwi)
{
    //
    std::vector<float> wsorter = rawwi.w;
    int loop = wsorter.size() > 8 ? 8 : wsorter.size();
    std::sort(wsorter.begin(), wsorter.end() - 1, [](float a, float b) {return a > b; });
    for (int i = 0; i < loop; i++)
    {
        for (int j = 0; j < loop; j++)
        {
            
            if (i < 4 && wsorter[i] == rawwi.w[j])
            {
                outwi.w1[i] = rawwi.w[j];
                outwi.i1[i] = rawwi.i[j];
                break;
            }
            else if (i < 8 && wsorter[i] == rawwi.w[j])
            {
                outwi.w2[i-4] = rawwi.w[j];
                outwi.i2[i-4] = rawwi.i[j];
                break;
            }

        }
    }
    outwi.i1[3] = loop;
    
}
int khg_Skin_Exp::GetFindIndex(INode* node)
{
    for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
    {
        if (m_ObjList[iObj] == node)
        {
            return iObj;
        }
    }
    return -1;
}
void khg_Skin_Exp::ExportPhysiqueData(INode* pNode, Modifier* pModi, tempMesh& tMesh)
{
    IPhysiqueExport* pPhyExp = (IPhysiqueExport*)pModi->GetInterface(I_PHYINTERFACE);
    IPhyContextExport* pPhyContext = pPhyExp->GetContextInterface(pNode);
    
    pPhyContext->ConvertToRigid(true);
    pPhyContext->AllowBlending(true);

    int iNumVert = pPhyContext->GetNumberVertices();
    std::vector<Raw_WI_VERTEX> wi_vertexs;
    for (int iVert = 0; iVert < iNumVert; iVert++)
    {
        Raw_WI_VERTEX data;
        IPhyVertexExport* pPhyVertExp = pPhyContext->GetVertexInterface(iVert);
        if (pPhyVertExp)
        {
            int iVertexType = pPhyVertExp->GetVertexType();
            switch (iVertexType)
            {
                case RIGID_NON_BLENDED_TYPE:
                {
                    IPhyRigidVertex* pVertex = (IPhyRigidVertex*)pPhyVertExp;
                    INode* node = pVertex->GetNode();
                    int iIndex = GetFindIndex(node);
                    data.i.push_back(iIndex);
                    data.w.push_back(1.0f);
                }break;
                case RIGID_BLENDED_TYPE:
                {
                    IPhyBlendedRigidVertex* pVertex = (IPhyBlendedRigidVertex*)pPhyVertExp;
                    for (int i=0; i < pVertex->GetNumberNodes(); i++)
                    {
                        INode* node = pVertex->GetNode(i);
                        int iIndex = GetFindIndex(node);
                       
                        data.i.push_back(iIndex);
                        data.w.push_back(pVertex->GetWeight(i));
                    }
                }break;
                default:
                {
                    MessageBox(NULL, L"Physi_Type_is_Not_Found", L"Physi_Type_is_Not_Found", S_OK);
                }break;
            }

        }
        pPhyContext->ReleaseVertexInterface(pPhyVertExp);
        wi_vertexs.push_back(data);

    }
    pPhyExp->ReleaseContextInterface(pPhyContext);
    pModi->ReleaseInterface(I_PHYINTERFACE, pPhyExp);
    tMesh.wi_List.push_back(wi_vertexs);
}
void khg_Skin_Exp::ExportSkinData(INode* pNode, Modifier* pModi, tempMesh& tMesh)
{
    ISkin* skin = (ISkin*)pModi->GetInterface(I_SKIN);
    ISkinContextData* skinData = skin->GetContextInterface(pNode);
    std::vector<Raw_WI_VERTEX> wi_vertexs;

    if (skin && skinData)
    {
        int iNumVertex = skinData->GetNumPoints();
        //m_Raw_wi_List.resize(iNumVertex);
        for (int iVert = 0; iVert < iNumVertex; iVert++)
        {
            Raw_WI_VERTEX data;

            for (int iBone = 0; iBone < skinData->GetNumAssignedBones(iVert); iBone++)
            {
                int iBoneID = skinData->GetAssignedBone(iVert, iBone);
                INode* node = skin->GetBone(iBoneID);
               data.i.push_back(GetFindIndex(node));
               data.w.push_back(skinData->GetBoneWeight(iVert, iBone));
            }
            wi_vertexs.push_back(data);

        }
        tMesh.wi_List.push_back(wi_vertexs);
    }
}
Modifier*  khg_Skin_Exp::FindModifier(INode* pNode, Class_ID classID)
{
    Object* pObj = pNode->GetObjectRef();
    if (pObj)
    {
        while (pObj->SuperClassID() == GEN_DERIVOB_CLASS_ID)
        {
            IDerivedObject* pDerivedObject = (IDerivedObject*)pObj;

            INT ModStackIndex = 0;

            while (ModStackIndex < pDerivedObject->NumModifiers())
            {
                Modifier* pModi = pDerivedObject->GetModifier(ModStackIndex);
                if (pModi->ClassID() == classID)
                {
                    return pModi;
                }
                ModStackIndex++;
            }
            pObj = pDerivedObject->GetObjRef();
        }
    }
    return nullptr;
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
//void khg_Skin_Exp::ExportIW(int index, FILE* pStream)
//{
//    IW_VERTEX IW_VERTEX;
//    ZeroMemory(&IW_VERTEX, sizeof(IW_VERTEX));
//
//    for (int i = 0; i < NUM_WI_EXPORT; i++)
//    {
//
//        if (i < 4 && i < m_Raw_wi_List[index].i.size())
//        {
//            IW_VERTEX.i1[i] = m_Raw_wi_List[index].i[i];
//            IW_VERTEX.w1[i] = m_Raw_wi_List[index].w[i];
//        }
//        else if (i >= 4 && i < m_Raw_wi_List[index].i.size())
//        {
//            IW_VERTEX.i2[i - 4] = m_Raw_wi_List[index].i[i];
//            IW_VERTEX.w2[i - 4] = m_Raw_wi_List[index].w[i];
//        }
//    }
//    IW_VERTEX.w1[3] = m_Raw_wi_List[index].i.size(); //w[3] , w1[3] // 색인용 주석
//
//    _ftprintf(pStream, _T("%10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f"), 
//        IW_VERTEX.i1[0], IW_VERTEX.i1[1], IW_VERTEX.i1[2], IW_VERTEX.i1[3],
//        IW_VERTEX.i2[0], IW_VERTEX.i2[1], IW_VERTEX.i2[2], IW_VERTEX.i2[3],
//        IW_VERTEX.w1[0], IW_VERTEX.w1[1], IW_VERTEX.w1[2], IW_VERTEX.w1[3],
//        IW_VERTEX.w2[0], IW_VERTEX.w2[1], IW_VERTEX.w2[2], IW_VERTEX.w2[3]
//    );
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void    khg_Skin_Exp::GetMesh(INode* pNode, TimeValue time, tempMesh& desc)
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
            // tri[iface].v[n].c.w 에 매터리얼 인덱스 삽입.
            tri[iface].iSubIndex =
                mesh->faces[iface].getMatID();
           
            if (tri[iface].iSubIndex <= 0 || desc.iMtrlID <= 0 )
            {
                tri[iface].iSubIndex = 0;
                tri[iface].v[0].c.w = -1;
                tri[iface].v[1].c.w = -1;
                tri[iface].v[2].c.w = -1;
            }
            else
            {
                //c.w 에 서브마태리얼 인덱스 삽입
                tri[iface].v[0].c.w = tri[iface].iSubIndex;
                tri[iface].v[1].c.w = tri[iface].iSubIndex;
                tri[iface].v[2].c.w = tri[iface].iSubIndex;
            }
            //vertex_index 191016//
            tri[iface].v[0].vertex_index = mesh->faces[iface].v[v0];
            tri[iface].v[1].vertex_index = mesh->faces[iface].v[v2];
            tri[iface].v[2].vertex_index = mesh->faces[iface].v[v1];

            desc.triList_List[tri[iface].iSubIndex].push_back(tri[iface]);
            //

        }
        //vb 만들.
        SetUniqueBuffer(desc);
    }
    if (deleteit) delete tri;
}
bool    khg_Skin_Exp::Convert()
{
    //std::vector<TBipedVertex> bipedList;
    for (int iObj = 0; iObj < m_SkinObjList.size(); iObj++)
    {
        INode* pNode = m_SkinObjList[iObj];
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
        Matrix3 wtm = pNode->GetNodeTM(0);
        //tMesh.matworld_inv = Inverse(wtm);
        DumpMatrix3(wtm, tMesh.matWorld);
        // 메터리얼 정보 얻고 / 저장
        Mtl* pMtl = pNode->GetMtl();
        if (pMtl)
            tMesh.iMtrlID = FindMaterial(pNode);
        if (tMesh.iMtrlID >= 0 &&
            m_MtlInfoList[tMesh.iMtrlID].subMtrl.size() > 0)
        {
            tMesh.iSubMesh = m_MtlInfoList[tMesh.iMtrlID].subMtrl.size();
        }
        GetMesh(pNode,m_Interval.Start(), tMesh);
        //m_Raw_wi_List.push_back(wi);
        //wi.clear();
        m_tempMesh_List.push_back(tMesh);
    }
    return true;
}
bool    khg_Skin_Exp::Export()
{
    Convert();

    FILE* pStream = nullptr;
    _tfopen_s(&pStream, m_filename.c_str(), _T("wt"));
    _ftprintf(pStream, _T("%s "), _T("khgExporter_100"));
    _ftprintf(pStream, _T("\n%d %d %d %d %d %d "), m_SkinObjList.size(), m_MtlInfoList.size(), m_Scene.iFirst_Frame, m_Scene.iLast_Frame, m_Scene.iFrame_Speed, m_Scene.iTick_Per_Frame);
    for (int iMtl = 0; iMtl < m_MtlInfoList.size(); iMtl++)
    {



        _ftprintf(pStream, _T("\n %s %d"),
           /* m_MtlInfoList[iMtl].iMapID,*/
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
    //INode* pNode = m_SkinObjList[iMtl];
    //_ftprintf(pStream, _T("\n%s %d %d"), pNode->GetName(), m_FaceInfoList.size(), m_tempMesh_List[iMtl].triList_List.size());

    for (int iObj = 0; iObj < m_tempMesh_List.size(); iObj++)
    {
        _ftprintf(pStream, _T("\n%s %s %d %d"),
            m_tempMesh_List[iObj].name,
            m_tempMesh_List[iObj].ParentName,
            m_tempMesh_List[iObj].iMtrlID,
            m_tempMesh_List[iObj].triList_List.size()
         
        );

      // _ftprintf(pStream, _T("\n\t%10.4f %10.4f %10.4f %10.4f\n\t%10.4f %10.4f %10.4f %10.4f\n\t%10.4f %10.4f %10.4f %10.4f\n\t%10.4f %10.4f %10.4f %10.4f"),
      //     m_tempMesh_List[iObj].matWorld._11,
      //     m_tempMesh_List[iObj].matWorld._12,
      //     m_tempMesh_List[iObj].matWorld._13,
      //     m_tempMesh_List[iObj].matWorld._14,
      //
      //     m_tempMesh_List[iObj].matWorld._21,
      //     m_tempMesh_List[iObj].matWorld._22,
      //     m_tempMesh_List[iObj].matWorld._23,
      //     m_tempMesh_List[iObj].matWorld._24,
      //
      //     m_tempMesh_List[iObj].matWorld._31,
      //     m_tempMesh_List[iObj].matWorld._32,
      //     m_tempMesh_List[iObj].matWorld._33,
      //     m_tempMesh_List[iObj].matWorld._34,
      //
      //     m_tempMesh_List[iObj].matWorld._41,
      //     m_tempMesh_List[iObj].matWorld._42,
      //     m_tempMesh_List[iObj].matWorld._43,
      //     m_tempMesh_List[iObj].matWorld._44);
      //

        ///
        for (int iSubTri = 0; iSubTri < m_tempMesh_List[iObj].triList_List.size(); iSubTri++)
        {
            VertexList& vList = m_tempMesh_List[iObj].vb[iSubTri];
            IWList& iwList = m_tempMesh_List[iObj].iwb[iSubTri];
          /*  Raw_WI_VERTEX& iwList = m_tempMesh_List[iObj].wi_List[iSubTri];*/
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
                
                if (iwList.size())
                {
                    _ftprintf(pStream, _T(" %d %d %d %d %d %d %d %d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f"),
                        iwList[iVer].i1[0], iwList[iVer].i1[1], iwList[iVer].i1[2], iwList[iVer].i1[3],
                        iwList[iVer].i2[0], iwList[iVer].i2[1], iwList[iVer].i2[2], iwList[iVer].i2[3],
                        iwList[iVer].w1[0], iwList[iVer].w1[1], iwList[iVer].w1[2], iwList[iVer].w1[3],
                        iwList[iVer].w2[0], iwList[iVer].w2[1], iwList[iVer].w2[2], iwList[iVer].w2[3]);
                }
                else
                {
                    _ftprintf(pStream, _T(" 0 0 0 0 0 0 0 0 0.0000     0.0000    0.0000     0.0000     0.0000     0.0000    0.0000     0.0000     "));
                }
                
                
                   //for (int i = 0; i < NUM_WI_EXPORT; i++)
                   //{
                
                   //    if (i < 4 && i < m_Raw_wi_List[index].i.size())
                   //    {
                   //        IW_VERTEX.i1[i] = m_Raw_wi_List[index].i[i];
                   //        IW_VERTEX.w1[i] = m_Raw_wi_List[index].w[i];
                   //    }
                   //    else if (i >= 4 && i < m_Raw_wi_List[index].i.size())
                   //    {
                   //        IW_VERTEX.i2[i - 4] = m_Raw_wi_List[index].i[i];
                   //        IW_VERTEX.w2[i - 4] = m_Raw_wi_List[index].w[i];
                   //    }
                   //}
                   //IW_VERTEX.w1[3] = m_Raw_wi_List[index].i.size(); //w[3] , w1[3] // 색인용 주석
                
                   //_ftprintf(pStream, _T("%10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f%10.4f %10.4f %10.4f %10.4f"), 
                   //    IW_VERTEX.i1[0], IW_VERTEX.i1[1], IW_VERTEX.i1[2], IW_VERTEX.i1[3],
                   //    IW_VERTEX.i2[0], IW_VERTEX.i2[1], IW_VERTEX.i2[2], IW_VERTEX.i2[3],
                   //    IW_VERTEX.w1[0], IW_VERTEX.w1[1], IW_VERTEX.w1[2], IW_VERTEX.w1[3],
                   //    IW_VERTEX.w2[0], IW_VERTEX.w2[1], IW_VERTEX.w2[2], IW_VERTEX.w2[3]
#pragma message(TODO("요 디버깅+ 다시 입력해야함 wi export"))

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
    }

    for (int iobj = 0; iobj < m_ObjList.size(); iobj++)
    {
        D3D_MATRIX matworld;
        DumpMatrix3(m_ObjList[iobj]->GetNodeTM(0), matworld);

       _ftprintf(pStream, _T("\n\t%10.4f %10.4f %10.4f %10.4f\n\t%10.4f %10.4f %10.4f %10.4f\n\t%10.4f %10.4f %10.4f %10.4f\n\t%10.4f %10.4f %10.4f %10.4f"),
           matworld._11,
           matworld._12,
           matworld._13,
           matworld._14,
       
           matworld._21,
           matworld._22,
           matworld._23,
           matworld._24,

           matworld._31,
           matworld._32,
           matworld._33,
           matworld._34,

           matworld._41,
           matworld._42,
           matworld._43,
           matworld._44);
    }
    fclose(pStream);
    //메시지 박스 하나
    MessageBox(GetActiveWindow(), m_filename.c_str(), L"Succsess", MB_OK);/////////////////////////////////////////
    return true;
    return true;
}
void    khg_Skin_Exp::AddObject(INode* pNode, TimeValue time)
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
            m_SkinObjList.push_back(pNode);
        }

        default:
            break;
        }
    }

}
void khg_Skin_Exp::SetUniqueBuffer(tempMesh& tMesh)
{
    tMesh.vb.resize(tMesh.triList_List.size());
    tMesh.ib.resize(tMesh.triList_List.size());
    tMesh.iwb.resize(tMesh.triList_List.size());
    for (int iSub = 0; iSub < tMesh.triList_List.size();
        iSub++)
    {
        for (int iFace = 0; iFace < tMesh.triList_List[iSub].size(); iFace++)
        {
            vectorTriList& triArray = tMesh.triList_List[iSub];
            TriList& tri = triArray[iFace];
            VertexList& vList = tMesh.vb[iSub];
            IndexList& iList = tMesh.ib[iSub];
            //Raw_WI_VERTEX& wilist = tMesh.wi_List[iSub];
            IW_VERTEX iwvertex;
            ZeroMemory(&iwvertex, sizeof(IW_VERTEX));
            for (int iVer = 0; iVer < 3; iVer++)
            {
                int wi_index = 3 * iFace + iVer;
                int iPos = IsEqulVertexList(tri.v[iVer], vList);
                if (iPos < 0)
                {
                    vList.push_back(tri.v[iVer]);
                    if (tMesh.wi_List.size())
                    {
                        SortRawData(tMesh.wi_List[iSub][tri.v[iVer].vertex_index], iwvertex);
                        tMesh.iwb[iSub].push_back(iwvertex);
                    }
                    iPos = vList.size() - 1;
                }
                iList.push_back(iPos);
            }
        }
    }

}




void khg_Skin_Exp::Set(Interface* mMax)
{
    if (mMax == nullptr)return;
    if (mMax == m_pMax && m_SkinObjList.size() != 0)
    {
        m_tempMesh_List.clear();
    }
    else
    {
        m_SkinObjList.clear();
        m_MaterialList.clear();
        m_MtlInfoList.clear();
        m_tempMesh_List.clear();
        m_Scene.init();
        m_pMax = mMax;
        m_Interval = m_pMax->GetAnimRange();
        m_Scene.iFirst_Frame = m_Interval.Start() / GetTicksPerFrame();
        m_Scene.iLast_Frame = m_Interval.End() / GetTicksPerFrame();
        m_Scene.iFrame_Speed = GetFrameRate();
        m_Scene.iTick_Per_Frame = GetTicksPerFrame();

        int iNumSelect = mMax->GetSelNodeCount();
        for (int i = 0; i < iNumSelect; i++)
        {
            INode* m_Skinip = mMax->GetSelNode(i);
            AddObject(m_Skinip, m_Interval.Start());
            AddMaterial(m_Skinip);
        }
    }

}


khg_Skin_Exp::khg_Skin_Exp()
{
}


khg_Skin_Exp::~khg_Skin_Exp()
{
}

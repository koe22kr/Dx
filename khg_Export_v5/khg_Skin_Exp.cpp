#include "stdafx.h"
#include "khg_Skin_Exp.h"
#include <algorithm>

void khg_Skin_Exp::SortIW(Raw_WI_VERTEX& wi)
{
    Raw_WI_VERTEX temp;
    std::vector<float> wsorter = wi.w;
    std::sort(wsorter.begin(), wsorter.end() - 1, [](float a, float b) {return a > b; });
    for (int i = 0; i < wi.i.size; i++)
    {
        for (int j = 0; j < wi.i.size; j++)
        {
            if (wsorter[i] == wi.w[j])
            {
                temp.w[i] = wi.w[j];
                temp.i[i] = wi.i[j];
                break;
            }
        }
    }
    wi = temp;
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
    m_Raw_wi_List.resize(iNumVert);
    for (int iVert = 0; iVert < iNumVert; iVert++)
    {
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
                    m_Raw_wi_List[iVert].i.push_back(iIndex);
                    m_Raw_wi_List[iVert].w.push_back(1.0f);
                }break;
                case RIGID_BLENDED_TYPE:
                {
                    IPhyBlendedRigidVertex* pVertex = (IPhyBlendedRigidVertex*)pPhyVertExp;
                    for (int i=0; i < pVertex->GetNumberNodes(); i++)
                    {
                        INode* node = pVertex->GetNode(i);
                        int iIndex = GetFindIndex(node);
                       
                        m_Raw_wi_List[iVert].i.push_back(iIndex);
                        m_Raw_wi_List[iVert].w.push_back(pVertex->GetWeight(i));
                    }
                }break;
                default:
                {
                    MessageBox(NULL, L"Physi_Type_is_Not_Found", L"Physi_Type_is_Not_Found", S_OK);
                }break;
            }

        }
        pPhyContext->ReleaseVertexInterface(pPhyVertExp);
        SortIW(m_Raw_wi_List[iVert]);//

    }
    pPhyExp->ReleaseContextInterface(pPhyContext);
    pModi->ReleaseInterface(I_PHYINTERFACE, pPhyExp);
}
void khg_Skin_Exp::ExportSkinData(INode* pNode, Modifier* pModi, tempMesh& tMesh)
{
    ISkin* skin = (ISkin*)pModi->GetInterface(I_SKIN);
    ISkinContextData* skinData = skin->GetContextInterface(pNode);
    if (skin && skinData)
    {
        int iNumVertex = skinData->GetNumPoints();
        m_Raw_wi_List.resize(iNumVertex);
        for (int iVert = 0; iVert < iNumVertex; iVert++)
        {
            for (int iBone = 0; iBone < skinData->GetNumAssignedBones(iVert); iBone++)
            {
                int iBoneID = skinData->GetAssignedBone(iVert, iBone);
                INode* node = skin->GetBone(iBoneID);
                m_Raw_wi_List[iVert].i.push_back(GetFindIndex(node));
                m_Raw_wi_List[iVert].w.push_back(skinData->GetBoneWeight(iVert, iBone));
            }
            SortIW(m_Raw_wi_List[iVert]);//

        }

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
void khg_Skin_Exp::ExportIW(int index, FILE* pStream)
{
    WI_VERTEX wi_vertex;
    ZeroMemory(&wi_vertex, sizeof(WI_VERTEX));

    for (int i = 0; i < NUM_WI_EXPORT; i++)
    {

        if (i < 4)
        {
            wi_vertex.i1[i] = m_Raw_wi_List[index].i[i];
            wi_vertex.w1[i] = m_Raw_wi_List[index].w[i];
        }
        else if (i >= 4)
        {
            wi_vertex.i2[i - 4] = m_Raw_wi_List[index].i[i];
            wi_vertex.w2[i - 4] = m_Raw_wi_List[index].w[i];
        }
    }
    wi_vertex.w1[3] = m_Raw_wi_List[index].i.size(); //w[3] , w1[3] // ���ο� �ּ�

    _ftprintf(pStream, _T("%10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f"), wi_vertex.i1[0], wi_vertex.i1[1], wi_vertex.i1[2], wi_vertex.i1[3],
        wi_vertex.i2[0], wi_vertex.i2[1], wi_vertex.i2[2], wi_vertex.i2[3],
        wi_vertex.w1[0], wi_vertex.w1[1], wi_vertex.w1[2], wi_vertex.w1[3],
        wi_vertex.w2[0], wi_vertex.w2[1], wi_vertex.w2[2], wi_vertex.w2[3]
    );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void    khg_Skin_Exp::GetMesh(INode* pNode, TimeValue time, tempMesh& desc)
{
    Matrix3 tm = pNode->GetObjTMAfterWSM(time);
    Matrix3 invtm;
    Inverse(invtm, pNode->GetNodeTM(time));
    ///////////////////////1) Ʈ���̿��� ������Ʈ[]
    bool deleteit = false;
    TriObject* tri = AddTriangleFromObject(pNode, time, deleteit);
    if (tri == nullptr) return;
    ///////////////////////2) �޽� ������Ʈ
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
    if (mesh)                                                         //X,Y���� �ݴ�� 0 2 1 ������ �޾Ƽ� 0 1 2 ������ �ִ´�.
    {
        //���̽�
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
                Point3 p3 = mesh->verts[mesh->faces[iface].v[v0]] * tm * invtm;    //tm �����ָ� ������ ��� ��ǥ��� ����� ��ȯ��// + invtm ���ؼ� ����ǥ���
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
            //GetVertexNormal ���� ���ش� ������ �� ����.?

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
            // tri[iface].v[n].c.w �� ���͸��� �ε��� ����.
            tri[iface].iSubIndex =
                mesh->faces[iface].getMatID();
            if (tri[iface].iSubIndex == 255 || desc.iMtrlID < 0 || m_MtlInfoList[desc.iMtrlID].subMtrl.size() <= 0)//���͸��� ������
            {
                tri[iface].iSubIndex = 0;
                tri[iface].v[0].c.w = -1;
                tri[iface].v[1].c.w = -1;
                tri[iface].v[2].c.w = -1;
            }
            else
            {
                //c.w �� ���긶�¸��� �ε��� ����
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
        //vb ����.
        SetUniqueBuffer(desc);
    }
    if (deleteit) delete tri;
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
            // ������ �θ� ����
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
        DumpMatrix3(invWtm, tMesh.matInvWorld);*/
#pragma message(TODO("GetMesh���� ����ǥ �� �����"))

        
        // ���͸��� ���� ��� / ����
        Mtl* pMtl = pNode->GetMtl();
        if (pMtl)
            tMesh.iMtrlID = FindMaterial(pNode);
        if (tMesh.iMtrlID >= 0 &&
            m_MtlInfoList[tMesh.iMtrlID].subMtrl.size() > 0)
        {
            tMesh.iSubMesh = m_MtlInfoList[tMesh.iMtrlID].subMtrl.size();
        }
        GetMesh(pNode,m_Interval.Start(), tMesh);
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
    _ftprintf(pStream, _T("\n%d %d %d %d %d %d "), m_ObjList.size(), m_MtlInfoList.size(), m_Scene.iFirst_Frame, m_Scene.iLast_Frame, m_Scene.iFrame_Speed, m_Scene.iTick_Per_Frame);
    for (int iMtl = 0; iMtl < m_MtlInfoList.size(); iMtl++)
    {



        _ftprintf(pStream, _T("\n%d %s %d"),
            m_MtlInfoList[iMtl].iMapID,
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
        _ftprintf(pStream, _T("\n%s %s %d %d %d %d %d"),
            m_tempMesh_List[iObj].name,
            m_tempMesh_List[iObj].ParentName,
            m_tempMesh_List[iObj].iMtrlID,
            m_tempMesh_List[iObj].triList_List.size(),
            m_tempMesh_List[iObj].bAnimation[0],
            m_tempMesh_List[iObj].bAnimation[1],
            m_tempMesh_List[iObj].bAnimation[2]
        );

        _ftprintf(pStream, _T("\n\t%10.4f %10.4f %10.4f %10.4f\n\t%10.4f %10.4f %10.4f %10.4f\n\t%10.4f %10.4f %10.4f %10.4f\n\t%10.4f %10.4f %10.4f %10.4f"),
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
            m_tempMesh_List[iObj].matWorld._44);


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
                
                ExportIW(vList[iVer].vertex_index,pStream);
#pragma message(TODO("�� �����"))

            }

            IndexList& iList =
                m_tempMesh_List[iObj].ib[iSubTri];
            _ftprintf(pStream, _T("\nIndexList %d"), iList.size());
            for (int iIndex = 0; iIndex < iList.size(); iIndex += 3)
            {
                _ftprintf(pStream, _T("\n%d %d %d"),
                    iList[iIndex + 0],
                    iList[iIndex + 1],
                    iList[iIndex + 2]);
            }
        }
    }

    fclose(pStream);
    //�޽��� �ڽ� �ϳ�
    MessageBox(GetActiveWindow(), m_filename.c_str(), L"Succsess", MB_OK);/////////////////////////////////////////
    return true;
    return true;
}

khg_Skin_Exp::khg_Skin_Exp()
{
}


khg_Skin_Exp::~khg_Skin_Exp()
{
}

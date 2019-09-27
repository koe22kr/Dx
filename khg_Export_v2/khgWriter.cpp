#include "stdafx.h"
#include "khgWriter.h"

void khgWriter::Set(const TCHAR* name, Interface* mMax)
{
    m_pMax = mMax;
    m_filename = name;
    m_pRootNode = m_pMax->GetRootNode();
    PreProcess(m_pRootNode, m_time);
}
void    khgWriter::PreProcess(INode* pNode, TimeValue time)
{
    if (!pNode)return;
    AddObject(pNode,time);
    int iNumChildren = pNode->NumberOfChildren();
    for (int iChild = 0; iChild < iNumChildren; iChild++)
    {
        INode* pChild = pNode->GetChildNode(iChild);
        PreProcess(pChild, time);
    }
}

void khgWriter::GetMaterial(INode* pNode)
{
    Mtl* pSrcMtl = pNode->GetMtl();
    //���� ���͸��� ���� ���� todo
    GetTexture(pSrcMtl);
}
void  khgWriter::GetTexture(Mtl* pMtl)
{
    int iNumMap = pMtl->NumSubTexmaps();
    for (int iSubMap = 0; iSubMap < iNumMap; iSubMap++)
    {
        Texmap* tex = pMtl->GetSubTexmap(iSubMap);
        if (tex)
        {
            if (tex->ClassID() == Class_ID(BMTEX_CLASS_ID, 0X00))
            {
                MtlInfo tMtl;
                tMtl.iMapID = iSubMap;

                TSTR fullName;
                TSTR mapName = ((BitmapTex*)(tex))->GetMapName();
                SplitPathFile(mapName, &fullName, &tMtl.szName);
                m_MtlInfoList.push_back(tMtl);
            }
        }
    }
}


bool khgWriter::Export()
{
    FILE* pStream;
    _tfopen_s(&pStream,m_filename.c_str(), _T("wt"));
    _ftprintf(pStream, _T("%s %d"), _T("khgExporter 100"),m_ObjList.size());
    for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
    {
        INode* pNode = m_ObjList[iObj];
        GetMesh(pNode,m_time);
       // �� ���͸���~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  todo
        GetMaterial(pNode);
        _ftprintf(pStream, _T("\n%s %d %d"), pNode->GetName(), m_TriList.size(), m_MtlInfoList.size());
        for (int iobj = 0; iobj < m_MtlInfoList.size(); iobj++)
        {
            _ftprintf(pStream, _T("\n%d %s\n%d"),
                m_MtlInfoList[iobj].iMapID,
                m_MtlInfoList[iobj].szName);
        }
        for (int iTri = 0; iTri < m_TriList.size(); iTri++)
        {
            bool finding;

            for (int iVer = 0; iVer < 3; iVer++)
            {
                finding = false;
                //auto iter = m_finder.find(m_TriList[iTri].v[iVer]);
                for (auto iter = m_finder.begin(); iter != m_finder.end(); iter++)
                {
                    if (iter->first->p == m_TriList[iTri].v[iVer].p)
                    {
                        if (iter->first->n == m_TriList[iTri].v[iVer].n)
                        {
                            m_IndexList.push_back(iter->second);
                            finding = true;
                            break;
                        }
                    }
                }
                if (finding)
                {
                    continue;
                }
                //Index//
                    //m_finder.insert(std::make_pair(m_TriList[iTri].v[iVer], m_IndexList.size()));
                m_IndexList.push_back(m_finder.size());
                m_finder[&m_TriList[iTri].v[iVer]] = m_finder.size();
             
                
                /*for (int i = iTri;i<m_TriList.size();i++)
                {
                    for (int j = iVer; j < 3; j++)
                    {
                        if(m_TriList[iTri].v[iVer].p == m_TriList[i].v[j].p)
                    }
                }
                if(m_TriList[iTri].v[iVer].p==)*/

                //���⼭ �ߺ����� �ϰ� �̱�!

                _ftprintf(pStream, _T("\n%10.4f %10.4f %10.4f"),
                    m_TriList[iTri].v[iVer].p.x,
                    m_TriList[iTri].v[iVer].p.y,
                    m_TriList[iTri].v[iVer].p.z);
                _ftprintf(pStream, _T("%10.4f %10.4f %10.4f"),
                    m_TriList[iTri].v[iVer].n.x,
                    m_TriList[iTri].v[iVer].n.y,
                    m_TriList[iTri].v[iVer].n.z);
                _ftprintf(pStream, _T("%10.4f %10.4f %10.4f %10.4f"),
                    m_TriList[iTri].v[iVer].c.x,
                    m_TriList[iTri].v[iVer].c.y,
                    m_TriList[iTri].v[iVer].c.z,
                    m_TriList[iTri].v[iVer].c.w);
                _ftprintf(pStream, _T("%10.4f %10.4f"),
                    m_TriList[iTri].v[iVer].t.x,
                    m_TriList[iTri].v[iVer].t.y);

                

            }
          
        }
        _ftprintf(pStream, _T("\n%3d\n"),m_IndexList.size());
        for (int i = 0; i < m_IndexList.size(); i++)
        {
            _ftprintf(pStream, _T("%3d "), m_IndexList[i]);
        }
    }
    fclose(pStream);
    //�޽��� �ڽ� �ϳ�
    MessageBox(GetActiveWindow(), m_filename.c_str(), L"Succsess", MB_OK);/////////////////////////////////////////
    return true;
}
khgWriter::khgWriter()
{
    m_time = 0;
}

void khgWriter::Setting()
{
    
}



khgWriter::~khgWriter()
{
}
void    khgWriter::AddObject(INode* pNode, TimeValue time)
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
        {
            m_ObjList.push_back(pNode);
        }
        //case HELPER_CLASS_ID:
        default:
            break;
        }
    }

}

bool khgWriter::TMNegParity(Matrix3 tm)
{
    Point3 v0 = tm.GetRow(0);
    Point3 v1 = tm.GetRow(1);
    Point3 v2 = tm.GetRow(2);
    Point3 vCross = CrossProd(v0, v1);
    return (DotProd(vCross, v2) < 0.0f) ? true : false;
return true;
}

void    khgWriter::GetMesh(INode* pNode,TimeValue time)
{
    Matrix3 tm = pNode->GetObjTMAfterWSM(time);
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
    //���̽�
    int iFacenum = mesh->numFaces;
    m_FaceInfoList.resize(iFacenum);
    DWORD num[3];
    for (int iface = 0; iface < iFacenum; iface++)
    {
        m_FaceInfoList[iface].a= mesh->faces[iface].v[0];
        m_FaceInfoList[iface].b = mesh->faces[iface].v[0];
        m_FaceInfoList[iface].c = mesh->faces[iface].v[0];
    }
    
    //���ý� 
    if (mesh)                                                         //X,Y���� �ݴ�� 0 2 1 ������ �޾Ƽ� 0 1 2 ������ �ִ´�.
    {
        int iNumFace = mesh->getNumVerts();
        m_VertexList.resize(iNumFace);

        for (int iVer = 0; iVer < iNumFace; iVer++)
        {
            //�ǻ���de
            /*m_IndexList.push_back(mesh->faces[iVer].v[v0]);
            m_IndexList.push_back(mesh->faces[iVer].v[v2]);
            m_IndexList.push_back(mesh->faces[iVer].v[v1]);

            m_TriList[iVer].v[0].p = ;
            m_TriList[iVer].v[1].p = ;
            m_TriList[iVer].v[2].p = ;*/
            //Point3 p3 = mesh->verts[iVer].;  //tm �����ָ� ������ ��� ��ǥ��� ����� ��ȯ��//

            //
            //Position//
            Point3 p3 = mesh->verts[iVer] * tm;    //tm �����ָ� ������ ��� ��ǥ��� ����� ��ȯ��//
            DumpPoint3(m_VertexList[iVer].p, p3);

            //Color// 
            int iNumColor = mesh->getNumVertCol();
            m_VertexList[iVer].c = Point4(1, 1, 1, 1);

            if (iNumColor > 0)
            {
                m_VertexList[iVer].c = mesh->vertCol[iVer];
               
            }

            //Texcoord//
            int INumTex = mesh->getNumTVerts();
            if (INumTex > 0)
            {
                Point2 p2 = (Point2)mesh->tVerts[iVer];
                m_VertexList[iVer].t.x = p2.x;
                m_VertexList[iVer].t.y = 1.0f - p2.y;
            }

            //Normal//
            //GetVertexNormal ���� ���ش� ������ �� ����.?

            mesh->buildNormals();
            RVertex* rVertex = mesh->getRVertPtr(iVer);

            Point3 vn = GetVertexNormal(mesh, iVer, rVertex);
            DumpPoint3(m_TriList[iVer].v[v0].n, vn);

            

            ////Normal �� �ӽ÷� 1,1,1;
            //m_TriList[iVer].v[0].n = Point3(1, 1, 1);
            //m_TriList[iVer].v[2].n = Point3(1, 1, 1);
            //m_TriList[iVer].v[1].n = Point3(1, 1, 1);
            
            //Index//
            //// �ε���... ��  full vertex �����̶� ������?
            //m_IndexList.push_back(mesh->faces[iVer].v[0]);
            //m_IndexList.push_back(mesh->faces[iVer].v[2]);
            //m_IndexList.push_back(mesh->faces[iVer].v[1]);
            

            //���� ���͸��� �ε���.   todo


        }
        //vb ����.

    }

    if (deleteit) delete tri;
}

Point3 khgWriter::GetVertexNormal(Mesh* mesh, int iFace, RVertex* rVertex)///////////
{
    Face* face = &mesh->faces[iFace];

    DWORD smGroup = face->smGroup;
    int numNormals = rVertex->rFlags &NORCT_MASK;//Normal count _ mask ?

    Point3 vertexNormal;
    if (rVertex->rFlags& SPECIFIED_NORMAL)   //Ȯ�� �븻..? ����? face�븻?
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



TriObject*    khgWriter::AddTriangleFromObject(INode* pNode, TimeValue time, bool& DeleteIt)
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
void	khgWriter::DumpPoint3(Point3& desc, Point3& src)
{
    desc.x = src.x;
    desc.y = src.z;
    desc.z = src.y;
}
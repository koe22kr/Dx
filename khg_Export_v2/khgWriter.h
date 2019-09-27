#pragma once
#include <string>
#include <vector>
#include <map>
struct PNCT
{
    Point3 p;
    Point3 n;
    Point4 c;
    Point2 t;
};
struct FaceInfo
{
    DWORD a;
    DWORD b;
    DWORD c;
};
struct TriList
{
    int iSubIndex;
    PNCT   v[3];
};
struct MtlInfo
{
    int   iMapID;
    TSTR  szName;
    std::vector<MtlInfo> subMtrl;
};
class khgWriter
{
    TimeValue m_time;
    Interface* m_pMax;   //max 인터페이스. dx의 디바이스 이상의 기능;
    std::wstring m_filename;
    INode* m_pRootNode; //트리인데 그래프 형식 이라 보면된다함.
    std::vector<INode*> m_ObjList;
    std::vector<TriList> m_TriList;
    std::vector<MtlInfo> m_MtlInfoList;                             //매터리얼 info인데 오브젝트 정보 들어가있음. 매터리얼 정보도 받아야함.
    std::vector<FaceInfo> m_FaceInfoList;

    
    std::vector<DWORD> m_IndexList;
    std::vector<PNCT> m_VertexList;
    std::map<PNCT*,int> m_finder;
public:
    void    AddObject(INode* pNode, TimeValue time);
    void    GetMesh(INode* pNode, TimeValue time);
    TriObject*    AddTriangleFromObject(INode* pNode,TimeValue time,bool& DeleteIt);
    void    PreProcess(INode* pNode, TimeValue time);
   
    void GetMaterial(INode* pNode);
    void  GetTexture(Mtl* pNode);

    bool TMNegParity( Matrix3 tm);
    void	DumpPoint3(Point3& desc, Point3& src);

    void DumpPoint3_Index(Face& src);
    Point3 GetVertexNormal(Mesh* mesh, int iFace, RVertex* rVertex);
    void Setting();
    void Set(const TCHAR* name, Interface* mMax);
    bool Export();
    khgWriter();
    ~khgWriter();
};


#pragma once
#include "Std.h"

class khg_Obj_Exp :public Exprot_Obj
{
  // std::wstring m_filename;
  // Interval m_Interval;
  // Interface* m_pMax;   //max �������̽�. dx�� ����̽� �̻��� ���;
  // INode* m_pRootNode; //Ʈ���ε� �׷��� ���� �̶� ����ȴ���.
  // Scene m_Scene;
  // std::vector<INode*> m_ObjList;
  // std::vector<Mtl*>    m_MaterialList;//���͸��� ����Ʈ..?
  // std::vector<MtlInfo> m_MtlInfoList; //Mtl* ���� ������
  // std::vector<tempMesh> m_tempMesh_List;
public:
   virtual void Set(Interface* mMax);
    void    PreProcess(INode* pNode, TimeValue time);
   virtual bool    Convert();
   virtual bool    Export();
    virtual void ExportAnimation(tempMesh& tmesh, FILE* pstream);
    void    AddObject(INode* pNode, TimeValue time);
   virtual void    GetMesh(INode* pNode, TimeValue time, tempMesh& desc);
    TriObject*    AddTriangleFromObject(INode* pNode, TimeValue time, bool& DeleteIt);
    //���͸���
   virtual void AddMaterial(INode* pNode);
    void GetMaterial(INode* pNode);
    int   FindMaterial(INode* pNode);
    //
    void  GetTexture(Mtl* pNode, MtlInfo& desc);
    Point3 GetVertexNormal(Mesh* mesh, int iFace, RVertex* rVertex);
    virtual void SetUniqueBuffer(tempMesh& tMesh);
    //
    bool	EqualPoint2(Point2 p1, Point2 p2);
    bool	EqualPoint3(Point3 p1, Point3 p2);
    bool	EqualPoint4(Point4 p1, Point4 p2);
    int IsEqulVertexList(PNCT& vertex, VertexList& vList);
    bool TMNegParity(Matrix3 tm);
    void	DumpPoint3(Point3& desc, Point3& src);
    TCHAR* FixupName(MSTR name);
    void   DumpMatrix3(Matrix3& matWorld, D3D_MATRIX& world);
    //
    void GetAnimation(INode* pNode, tempMesh& tMesh);
    //
    TCHAR* SaveFileDlg(TCHAR* szExt, TCHAR* szTitle);

    khg_Obj_Exp();
    ~khg_Obj_Exp();
    //
    static khg_Obj_Exp* Get()
    {
        static khg_Obj_Exp instance;
        return &instance;
    }
};


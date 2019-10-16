#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define CTL_CHARS		31
#define SINGLE_QUOTE	39 // ( ' )
#define ALMOST_ZERO		1.0e-3f

typedef struct _D3D_MATRIX {
    union {
        struct {
            float        _11, _12, _13, _14;
            float        _21, _22, _23, _24;
            float        _31, _32, _33, _34;
            float        _41, _42, _43, _44;
        };
        float m[4][4];
    };
}D3D_MATRIX, *LPD3D_MATRIX;

struct PNCT
{
    Point3 p;
    Point3 n;
    Point4 c;
    Point2 t;
};
struct FaceInfo
{
    union {
        struct
        {
            int a;
            int b;
            int c;
        };
        int v[3];
    };
};
struct TriList
{
    int iSubIndex;
    PNCT   v[3];
};

struct texInfo
{
    int   iMapID;
    TSTR  szName;
};

struct MtlInfo
{
    //INode* pINode; �߰�?
    int   iMapID;
    TSTR  szName;
    std::vector< texInfo> TextureList;
    std::vector<MtlInfo> subMtrl;
    MtlInfo()
    {
        iMapID = -1;
        szName = L"None";
    }
};
struct AnimTrack
{
    int i;
    Point3 p;
    Quat q;
};
struct Scene
{
    int iFirst_Frame;
    int iLast_Frame;
    int iFrame_Speed;    //30
    int iTick_Per_Frame;  //160
    //�Ʒ� �͵� ����?
    int iNum_Obj;
    int iNum_Mtl;

};
typedef std::vector<TriList>   vectorTriList;
using IndexList = std::vector<DWORD>;
using VertexList = std::vector<PNCT>;
//OBJ �� ���� �ɵ�.
struct tempMesh
{
    bool bAnimation[3];
    std::vector<AnimTrack> Anim_S;
    std::vector<AnimTrack> Anim_R;
    std::vector<AnimTrack> Anim_T;
    INode*  pINode;
    int     iSubMesh; //����Ž� ����
    TSTR    name;//1
    TSTR    ParentName;//1
    Matrix3    wtm;//1
    D3D_MATRIX matWorld;//1
    Matrix3 matworld_inv;
    std::vector<TriList>			triList;
    std::vector<vectorTriList>		triList_List;
    // std::vector<PNCT>	triList;
     //std::vector<FaceInfo>   indexList; //�ε��� �� ���̽�;

    std::vector<VertexList> vb;
    std::vector<IndexList> ib;
    //std::vector<vertexList>   vbList;
    //std::vector<IndexList>    ibList;

    int     iMtrlID;

public:
    int iType;

    tempMesh()
    {
        name = L"none";
        ParentName = L"none";
        iMtrlID = -1;
        iSubMesh = 1;
    }
};

struct Exprot_Obj
{
   static std::wstring m_filename;
   static Interval m_Interval;
   static Interface* m_pMax;   //max �������̽�. dx�� ����̽� �̻��� ���;
   static INode* m_pRootNode; //Ʈ���ε� �׷��� ���� �̶� ����ȴ���.
   static Scene m_Scene;
   static std::vector<INode*> m_ObjList;
   static std::vector<Mtl*>    m_MaterialList;//���͸��� ����Ʈ..?
   static std::vector<MtlInfo> m_MtlInfoList; //Mtl* ���� ������
   static std::vector<tempMesh> m_tempMesh_List;
   Exprot_Obj() {};
};

const enum OBJECTTYPE {
    CLASS_GEOM = 0,
    CLASS_BONE,
    CLASS_DUMMY,
    CLASS_BIPED,
};
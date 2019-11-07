#pragma once
#include "CACore.h"
#include "Effect_Render_Obj.h"

#define MAX_EFFECT 255

#define TOOL ((CCharaToolApp*)AfxGetApp())->m_Tool

//////////////////////////////////////////////////////////
class TPlaneObject : public CADx_Model2
{
public:
    virtual HRESULT CreateVertexData() override;
    virtual HRESULT CreateIndexData() override;
public:
    TPlaneObject();
    virtual ~TPlaneObject();
};
/////////////////////////////////////////////////////////임시 객체

struct Tex_Info
{
    int m_iTex;
    CString m_szName;
     Tex_Info()
    {
         m_iTex = -1;
    }
};
struct Effect_Obj
{
    int m_iTex;
    CString m_szName;
    Effect_Obj()
    {
        m_iTex = -1;
    }
};
class Sample : public CACore
{
public:
    int m_iSel_Tex;
    int m_iSel_Obj;
    int m_iCut_Num = 4; //과제후 편집해야함
public:
    /*std::vector< */Effect_Render_Obj/*>*/ m_Render_List;
    std::vector<Tex_Info> m_Tex_List;//로드된 텍스쳐 정보
    std::vector<Effect_Obj> m_Obj_List; //생성된 오브젝트 [각 오브젝트당 최대 n개 의 이펙트 들]
    //std::vector<Effect_VB> m_Effect_List;  //버텍스 데이터 정보 VB제작용


    TPlaneObject m_Plane;
public://일단 하드로 만들기
    void Get_UV(int cutx,int cuty,int texnum, TPlaneObject* m_pplane);
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
public:
    Sample();
    ~Sample();
};


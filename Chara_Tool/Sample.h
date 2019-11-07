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
/////////////////////////////////////////////////////////�ӽ� ��ü

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
    int m_iCut_Num = 4; //������ �����ؾ���
public:
    /*std::vector< */Effect_Render_Obj/*>*/ m_Render_List;
    std::vector<Tex_Info> m_Tex_List;//�ε�� �ؽ��� ����
    std::vector<Effect_Obj> m_Obj_List; //������ ������Ʈ [�� ������Ʈ�� �ִ� n�� �� ����Ʈ ��]
    //std::vector<Effect_VB> m_Effect_List;  //���ؽ� ������ ���� VB���ۿ�


    TPlaneObject m_Plane;
public://�ϴ� �ϵ�� �����
    void Get_UV(int cutx,int cuty,int texnum, TPlaneObject* m_pplane);
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
public:
    Sample();
    ~Sample();
};


#pragma once
#include "CACore.h"
#include "Effect_Render_Obj.h"



#define TOOL ((CCharaToolApp*)AfxGetApp())->m_Tool
#define FRM ((CMainFrame*)(CMainFrame*)AfxGetMainWnd())

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
   
public:
public:
    CString m_szTeexture_Path = { L"\\..\\..\\_data\\" };
    CString m_szShader_Path = { L"\\..\\..\\_shader\\" };
    CString m_szMain_Shader = { L"effect2.hlsl" };
    bool m_bFirstNewTex = true;
    char m_CurrentDir[MAX_PATH];
    int m_iSel_Tex=0;
    int m_iSel_Obj=0;
    
    float m_fEffect_End_Time = 9999;
    float m_fEffect_delta_Time = 0;

public:
    //Effect_Data m_Cur_Option;
    std::vector< Effect_Render_Obj*> m_Render_List;
    std::vector<Tex_Info> m_Tex_List;//로드된 텍스쳐 정보
   // std::vector<Effect_Obj> m_Obj_List; //생성된 오브젝트 [각 오브젝트당 최대 n개 의 이펙트 들]



public:
    void Copy_Effect_Data(Effect_Data& src, Effect_Render_Obj& dest);
    int Find_Texture(CString* texname);
  //  void Get_UV(int cutx,int cuty,int& texnum, TPlaneObject* m_pplane);
  //  void Set_Alpha(float m_Alpha, TPlaneObject* m_pplane);
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
public:
    void Save();
    void Load();
    Sample();
    ~Sample();
};


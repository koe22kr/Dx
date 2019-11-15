#pragma once
#include "CACore.h"
#include "Effect_Render_Obj.h"



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
    D3D11_BLEND_DESC    m_BlendDesc;
    ID3D11BlendState*	m_pBlendState;

    D3D11_RASTERIZER_DESC m_RasterizerDesc;
    ID3D11RasterizerState*  m_pRasterizerState;

    D3D11_SAMPLER_DESC m_SamplerDesc;
    ID3D11SamplerState*   m_pSamplerState;

    D3D11_DEPTH_STENCIL_DESC m_DepthStencilDesc;
    ID3D11DepthStencilState* m_pDepthStencilState;
public:
    void SetBlendState(D3D11_BLEND_DESC* pBD);
    void SetRasterizerState(D3D11_RASTERIZER_DESC* pRD);
    void SetSamplerState(D3D11_SAMPLER_DESC* pSD);
    void SetDepthStencilState(D3D11_DEPTH_STENCIL_DESC* pDSD);
public:
    int m_iSel_Tex=-1;
    int m_iSel_Obj=-1;
    int m_iCut_Num = 4; //������ �����ؾ���
public:
    Effect_Render_Obj m_Cur_Option;
    /*std::vector<*/ Effect_Render_Obj/*>*/ m_Render_List;
    std::vector<Tex_Info> m_Tex_List;//�ε�� �ؽ��� ����
    std::vector<Effect_Obj> m_Obj_List; //������ ������Ʈ [�� ������Ʈ�� �ִ� n�� �� ����Ʈ ��]
    //std::vector<Effect_Data> m_Effect_List;  //���ؽ� ������ ���� VB���ۿ�


    TPlaneObject m_Plane;
public://�ϴ� �ϵ�� �����
    void Get_UV(int cutx,int cuty,int& texnum, TPlaneObject* m_pplane);
    void Set_Alpha(float m_Alpha, TPlaneObject* m_pplane);
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
public:
    Sample();
    ~Sample();
};


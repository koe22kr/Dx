#pragma once
#include "CADx_Model2.h"

#define MAX_EFFECT 100000
//////////////

struct Effect_VB
{
    float       m_Delta_Time;//���̴����� �Է�/
    D3DXVECTOR4 m_Tex_UV;//���̴����� �Է�///////////////////////////////////////////////////////////////////////TODO
    D3DXVECTOR3 m_Pos;
    UINT			m_iTexID; //���� ���� �ִϸ��̼� ���� ���///////////////////////////////////////////////////////////////////////TODO
    float m_iType;//
    float alpha;
    Effect_VB()
    {
        alpha = 0.0f;
        m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_Tex_UV = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
        m_Delta_Time = 0.0f;
        /*m_fFadeInDeltaTime = 0.0f;
        m_fFadeOutDeltaTime = 0.0f;*/
       // D3DXMatrixIdentity(&m_matbill);
        m_iTexID = 0;
        m_iType = 0;
    }
};
struct Effect_CB
{
    D3DXVECTOR4 m_vColor;
    D3DXVECTOR4 TotalPower; //x y z w==0;//update
    D3DXVECTOR4 m_Move_Vector;//���� �ƴ� ���̰� ����//update
    D3DXVECTOR4 Time_add_life_fadein_fadeout;
    D3DXVECTOR4 m_vTargetPos_wSpeed;
    D3DXVECTOR4 nRand_Loop_cutx_cuty;//����,����_�ִϸ��̼� �ư�
    D3DXMATRIX m_matbill;//update�Լ��� �Է�
    D3DXVECTOR4 etc;//�ִϸ��̼� �ð�[ �ѹ��� �ð�],����Ʈ ����,�� Ÿ��,x;

    D3DXVECTOR4 m_vRot_Quat_perSec;
    D3DXVECTOR4 m_vScale_per_Sec;//w=0;
    D3DXVECTOR4 m_vVel; //w=0;
    D3DXVECTOR4 m_vScale;//w=0;
    D3DXVECTOR4 m_vRotation;//w=0;
    D3DXVECTOR4 m_vPos;//w=0;
    D3DXVECTOR4 m_vrandom;//w=0;

    Effect_CB()
    {
        m_vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
        D3DXMatrixIdentity(&m_matbill);
        m_vScale_per_Sec = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0);
        etc = D3DXVECTOR4(3.0f, 0.0f, 999.0f, 0.0f);
        m_vPos= m_vRotation=m_vRot_Quat_perSec = m_vVel = m_vrandom=m_vTargetPos_wSpeed = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
        nRand_Loop_cutx_cuty = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
        Time_add_life_fadein_fadeout = D3DXVECTOR4(0.1f, 10.0f, 0.0f, 0.0f);
        m_vScale = D3DXVECTOR4(1.0f, 1.0f, 1.0f,0.0f);
    }
};
///////////////////
struct Property
{

};
using namespace DX;

enum Radius_exp
{
    COS = 0 , SIN, TAN,COS_TIMER,SIN_TIMER,TAN_TIMER,RETURN_ZERO,RETURN_ONE,
};


struct Move_Data
{
    float a;
    float b;
    float c;
    float d;
    float e;
    Radius_exp exp1;
    Radius_exp exp2;
    Move_Data()
    {
        a = b = c = d = e = 0.0f;
        exp1 = exp2 = COS;
    }
};
struct Effect_State
{
    int blend[8] = { 1,5,6,1,2,1,1,15 };
    int rasterizer[2] = { 3,1 };
    int sampler[4] = {21,1,1,1};
    int depthstencil[3] = { 1,1,4 };
};
struct Effect_Data
{
    Effect_State m_State;
    //wstring m_szShader_Name;
    Effect_VB m_Base_VB;
    Effect_CB m_Base_CB;

    Move_Data m_Move_Data_X;//Move_Vector �����Set_Move�Լ����� ����
    Move_Data m_Move_Data_Y;//Move_Vector �����Set_Move�Լ����� ����
    Move_Data m_Move_Data_Z;//Move_Vector �����Set_Move�Լ����� ����
    float m_fMove_Radius;   //Move_Vector �����Set_Move�Լ����� ����
    Move_Data m_Move_Data_R;//Move_Vector �����Set_Move�Լ����� ����

    D3DXVECTOR3 m_vRandom_Pos_Min;
    D3DXVECTOR3 m_vRandom_Pos_Max;

    D3DXVECTOR3 m_vPower1;//Total_Power ����� CB//Set_Power���� ����
    D3DXVECTOR3 m_vRandom_Power_Min;//Total_Power ����� CB//Set_Power���� ����
    D3DXVECTOR3 m_vRandom_Power_Max;//Total_Power ����� CB//Set_Power���� ����

         
      

    D3DXVECTOR3 m_to_quat;
    D3DXVECTOR3 m_to_quat_base_rot;
    bool m_bUse_billboard;

    Effect_Data()
    {
        m_fMove_Radius = 0.0f;
        m_vPower1 = m_vRandom_Power_Min = m_vRandom_Power_Max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
      //  
    }
};

//InputLayout �ٸ���� �� �������̽��� ��ӹ޾Ƽ� ������
class Effect_Render_Obj :public DX::CADx_Model2
{
public:
    
    Effect_Data m_data;
    bool m_bFirst;//������ ���� �÷��� (����or ���� ������ ����Ʈ ����)
    bool m_bRend = false;

    int m_iTex;

    CString m_szName;
    CString m_szShader;
    CString m_szTextureName;

    D3DXMATRIX m_matbill;
    ////////////////////////////////////////////////

    Microsoft::WRL::ComPtr < ID3D11VertexShader> m_pFrameVS;
    Microsoft::WRL::ComPtr < ID3D11GeometryShader> m_pFrameGS;
    Microsoft::WRL::ComPtr < ID3D11GeometryShader> m_pGS_Stream_Output;

    Effect_VB m_Effect_Vertex_Data;//       ó�� �Է� VB
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pEffect_SO_Output_buffer;//SO �޾Ƽ� �̰����� DRAW AUTO
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pEffect_Draw_buffer;     //SO �޾Ƽ� �̰����� DRAW AUTO
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pEffectConstantBuffer;

    ////////////////////////////////////////////////////////////
    D3D11_BLEND_DESC    m_BlendDesc;
    ID3D11BlendState*	m_pBlendState;

    D3D11_RASTERIZER_DESC m_RasterizerDesc;
    ID3D11RasterizerState*  m_pRasterizerState;

    D3D11_SAMPLER_DESC m_SamplerDesc;
    ID3D11SamplerState*   m_pSamplerState;

    D3D11_DEPTH_STENCIL_DESC m_DepthStencilDesc;
    ID3D11DepthStencilState* m_pDepthStencilState;
    ////////////////////////////////////////////////////////////
    void SetBlendState(D3D11_BLEND_DESC* pBD);
    void SetRasterizerState(D3D11_RASTERIZER_DESC* pRD);
    void SetSamplerState(D3D11_SAMPLER_DESC* pSD);
    void SetDepthStencilState(D3D11_DEPTH_STENCIL_DESC* pDSD);
    ///////////////////////////////////////////////////////////
    // ������ �Լ�
    virtual HRESULT SetInputLayout()override;
    HRESULT CreateConstantBuffer()override;
    virtual HRESULT CreateVertexBuffer()override;
    HRESULT LoadShaderFile(
        ID3D11Device* pd3dDevice,
        const TCHAR* pLoadShaderFile)override;
   virtual bool  Create(ID3D11Device* pd3dDevice,
        const TCHAR* pLoadShaderFile,
        const TCHAR* pLoadTextureFile)override;
public:
  
private:
    //��ȿȭ �� �Լ�
    virtual HRESULT CreateVertexData()override;
    virtual HRESULT CreateIndexData()override;
    
    virtual HRESULT CreateIndexBuffer()override;
    //
public:

    bool InitState();
    bool Frame();
    bool Render();
public:
    Effect_Render_Obj();
    ~Effect_Render_Obj();


public:
  //  void Update_Buffer();
  //  void Add();
    //a + b * exp1( c + d * exp2( e ));

    void Update();
    float EXP_Product(float a, float b, Radius_exp exp1, float c, float d, Radius_exp exp2, float e);
    float GetExp(float in,Radius_exp exp);
    void Set_Move();
    void Set_Power();
    void Set_CtrlMatrix();
};
//�������̵� �ؼ� �������� ���� Model->Create() ���� �Լ���
//LoadShaderFile
//SetInputLayout

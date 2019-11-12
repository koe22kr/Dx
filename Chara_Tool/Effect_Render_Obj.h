#pragma once
#include "CADx_Model2.h"
#include "TCamera.h"

struct Effect_Data
{
    bool m_bRoop;
    //inputrayout

   // D3DXVECTOR3 m_Normal;
    //D3DXVECTOR4 m_Color_Filter;
    float m_Alpha;
    D3DXVECTOR2 m_Tex_UV;
    float m_Life_Time;
    float m_Delta_Time;
    float		m_fFadeInTime;
    float		m_fFadeOutTime;
    float		m_fFadeInDeltaTime;
    float		m_fFadeOutDeltaTime;


    D3DXVECTOR3 m_vScale;
    D3DXVECTOR3 m_vRotation;
    D3DXVECTOR3 m_vPos;

    D3DXVECTOR3 m_vTargetPos;
    float m_fSpeed_to_Target;
    D3DXVECTOR3 m_vPower1;
    D3DXVECTOR3 m_vPower2;
    D3DXVECTOR3 m_vPower3;

    float m_fRadius;
    int			m_iTexID; //단일 파일 애니메이션 에서 사용중.
    Effect_Data()
    {
        m_Alpha = 0.0f;
        m_Tex_UV = D3DXVECTOR2(0.0f, 0.0f);
        m_Life_Time = 5.0f;
        m_Delta_Time = 0.0f;
        m_fFadeInTime = 0.0f;
        m_fFadeInDeltaTime = 0.0f;
        m_fFadeOutTime = 0.0f;
        m_fFadeOutDeltaTime = 0.0f;
        m_vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
        m_vRotation = D3DXVECTOR3(0.0, 0.0f, 0.0f);
        m_vPos = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
        m_vTargetPos = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
        m_fSpeed_to_Target = 10.0f;
        m_vPower1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_vPower2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_vPower3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        
        
       // m_Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
      //  m_Color_Filter = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
      //  m_Alpha = 1.0f;
       
        m_iTexID = 0;//임시
    }
};
struct Instance_VB
{
    D3DXMATRIX m_matWorld;

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

//InputLayout 다를경우 이 인터페이스를 상속받아서 재정의
class Effect_Render_Obj :public DX::CADx_Model2
{
public:
    bool m_bRend;

public:
   // TCamera* m_cur_cam;
    wstring m_szShader_Name;
    Effect_Data m_Base_Effect;

    D3DXVECTOR3 m_Move_Vector;
    Move_Data m_Move_Data_X;
    Move_Data m_Move_Data_Y;
    Move_Data m_Move_Data_Z;
    float m_fMove_Radius;
    Move_Data m_Move_Data_R;

    float m_Add_Time;
    ////////////////////////////////////////////////현재 미사용
    std::vector< Effect_Data> m_Effect_Vertex_List;
    std::vector<Instance_VB> m_Effect_Instance_List;
    ID3D11Buffer* m_pEffect_Vertex_buffer;
    ID3D11Buffer* m_pEffect_Instance_buffer;
    // 재정의 함수
    virtual HRESULT SetInputLayout()override;
    HRESULT CreateConstantBuffer()override;
    virtual HRESULT CreateVertexBuffer()override;
    bool Create_Render_Obj(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile);
public:
    //Create_Render_Obj로 연계
    bool  Create(ID3D11Device* pd3dDevice,
        const TCHAR* pLoadShaderFile,
        const TCHAR* pLoadTextureFile);
private:
    //무효화 한 함수
    virtual HRESULT CreateVertexData()override;
    virtual HRESULT CreateIndexData()override;
    
    virtual HRESULT CreateIndexBuffer()override;
    virtual HRESULT LoadTextures(
        ID3D11Device* pd3dDevice,
        const TCHAR* pLoadTextureFile)override;
public:

public:
    Effect_Render_Obj();
    ~Effect_Render_Obj();


public:
    void Update_Buffer();
    void Add();
    //a + b * exp1( c + d * exp2( e ));
    float EXP_Product(float a, float b, Radius_exp exp1, float c, float d, Radius_exp exp2, float e);
    float GetExp(float in,Radius_exp exp);
    void Set_Move();

};
//오버라이딩 해서 무시하지 않은 Model->Create() 내부 함수들
//LoadShaderFile
//SetInputLayout

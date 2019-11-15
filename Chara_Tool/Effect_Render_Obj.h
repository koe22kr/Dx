#pragma once
#include "CADx_Model2.h"
#include "TCamera.h"

#define MAX_EFFECT 100000
//////////////

struct Effect_VB
{
    float       m_Delta_Time;
    float		m_fFadeInDeltaTime;
    float		m_fFadeOutDeltaTime;
    
    D3DXVECTOR2 m_Tex_UV;
    D3DXMATRIX m_matControl;//생성후 이동처리 여기에.
    
    int			m_iTexID; //단일 파일 애니메이션 에서 사용중.
    int m_iType;
    Effect_VB()
    {
        m_Tex_UV = D3DXVECTOR2(0.0f, 0.0f);
        m_Delta_Time = 0.0f;
        m_fFadeInDeltaTime = 0.0f;
        m_fFadeOutDeltaTime = 0.0f;
        D3DXMatrixIdentity(&m_matControl);
        m_iTexID = 0;
        m_iType = -1;
    }
};
struct Effect_CB
{
    D3DXVECTOR4 m_vColor;//float m_Alpha;

    //UINT nEffectNum;
 
    D3DXVECTOR4 TotalPower;
    D3DXVECTOR4 m_Move_Vector;//단위 아님 길이값 있음
    D3DXVECTOR4 Time_add_life_fadein_fadeout;
    //float m_Add_Time;
    //float       m_Life_Time;//상수로
    //float		m_fFadeInTime;//상수로
    //float		m_fFadeOutTime;
   

    D3DXVECTOR4 m_vTargetPos_wSpeed;//인스턴트로
 //   float m_fSpeed_to_Target; //
 
    D3DXVECTOR4 nRand_Loop_etc2;
 //UINT m_bRand;
 //UINT m_bLoop;
};
///////////////////

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
    bool m_bFirst;//랜더링 시작 플래그 (적용or 시작 눌러야 이펙트 시작)

public:
    //wstring m_szShader_Name;
    Effect_VB m_Base_VB;
    Effect_CB m_Base_CB;


    Move_Data m_Move_Data_X;//Move_Vector 연산용  CB
    Move_Data m_Move_Data_Y;//Move_Vector 연산용
    Move_Data m_Move_Data_Z;//Move_Vector 연산용
    float m_fMove_Radius;   //Move_Vector 연산용
    Move_Data m_Move_Data_R;//Move_Vector 연산용
 
    D3DXVECTOR3 m_vPower1;//Total_Power 연산용 CB
    D3DXVECTOR3 m_vPower2;//Total_Power 연산용
    D3DXVECTOR3 m_vPower3;//Total_Power 연산용

    D3DXVECTOR3 m_vScale;       //컨트롤 행렬 만들어서 INSTANCEBUFFER에 투척
    D3DXVECTOR3 m_vRotation;    //컨트롤 행렬 만들어서 INSTANCEBUFFER에 투척
    D3DXVECTOR3 m_vPos;         //컨트롤 행렬 만들어서 INSTANCEBUFFER에 투척

    ////////////////////////////////////////////////
    Microsoft::WRL::ComPtr < ID3D11VertexShader> m_pFrameVS;
    Microsoft::WRL::ComPtr < ID3D11GeometryShader> m_pFrameGS;
    Microsoft::WRL::ComPtr < ID3D11GeometryShader> m_pGS_Stream_Output;



    Effect_VB m_Effect_Vertex_Data;//       처음 입력 VB
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pEffect_SO_Output_buffer;//SO 받아서 이것으로 DRAW AUTO
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pEffect_Draw_buffer;     //SO 받아서 이것으로 DRAW AUTO
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_pEffectConstantBuffer;

    ////////////////////////////////////////////////////////////
    
    //
    // 재정의 함수
    virtual HRESULT SetInputLayout()override;
    HRESULT CreateConstantBuffer()override;
    virtual HRESULT CreateVertexBuffer()override;
    HRESULT LoadShaderFile(
        ID3D11Device* pd3dDevice,
        const TCHAR* pLoadShaderFile)override;
public:
  
private:
    //무효화 한 함수
    virtual HRESULT CreateVertexData()override;
    virtual HRESULT CreateIndexData()override;
    
    virtual HRESULT CreateIndexBuffer()override;
 //   virtual HRESULT LoadTextures(
     //   ID3D11Device* pd3dDevice,
   //     const TCHAR* pLoadTextureFile)override;
public:
    bool Frame();
    bool Render();
public:
    Effect_Render_Obj();
    ~Effect_Render_Obj();


public:
  //  void Update_Buffer();
  //  void Add();
    //a + b * exp1( c + d * exp2( e ));
    float EXP_Product(float a, float b, Radius_exp exp1, float c, float d, Radius_exp exp2, float e);
    float GetExp(float in,Radius_exp exp);
   // void Set_Move();

};
//오버라이딩 해서 무시하지 않은 Model->Create() 내부 함수들
//LoadShaderFile
//SetInputLayout

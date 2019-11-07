#pragma once
#include "CADx_Model2.h"
#include "TCamera.h"

struct Effect_VB
{
    //inputrayout
    D3DXVECTOR3 m_Pos;
    D3DXVECTOR3 m_Normal;
    D3DXVECTOR4 m_Color_Filter;
    float m_Alpha;
    D3DXVECTOR2 m_Tex_UV;
    float m_Life_Time;
    float m_Delta_Time;
    D3DXVECTOR3 m_vVelocity;
    //D3DXVECTOR3 m_vGravity;
    D3DXVECTOR3 m_vTargetPos;
    //float		m_fFadeOutTime;
    //float		m_fSpeed;
    int			m_iTexID; //이걸 여기서?..으음...
    Effect_VB()
    {
        m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
        m_Color_Filter = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
        m_Alpha = 1.0f;
        m_Life_Time = 1 + (rand() % 10);
        m_iTexID = 0;//임시
        m_vVelocity = D3DXVECTOR3(50 - rand() % 100, 50 - rand() % 100, 50 - rand() % 100);
        D3DXVec3Normalize(&m_vVelocity, &m_vVelocity);
    }
};
struct Instance_VB
{
    D3DXMATRIX m_matWorld;

};

using namespace DX;
//InputLayout 다를경우 이 인터페이스를 상속받아서 재정의
class Effect_Render_Obj :public DX::CADx_Model2
{
public:
    bool m_bRend;

public:
   // TCamera* m_cur_cam;
    wstring m_szShader_Name;
    Effect_VB m_Base_Effect;
    std::vector< Effect_VB> m_Effect_Vertex_List;
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
};
//오버라이딩 해서 무시하지 않은 Model->Create() 내부 함수들
//LoadShaderFile
//SetInputLayout

#pragma once
#include "CADx_Model2.h"

using namespace DX;
//InputLayout 다를경우 이 인터페이스를 상속받아서 재정의
class Render_Obj :public DX::CADx_Model2
{
public:
    wstring m_szShader_Name;
    bool Create_Render_Obj(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile);
public:
    //Create_Render_Obj로 토스//
    bool  Create(ID3D11Device* pd3dDevice,
        const TCHAR* pLoadShaderFile,
        const TCHAR* pLoadTextureFile);

    virtual HRESULT SetInputLayout()override;
    virtual HRESULT CreateVertexData()override;
    virtual HRESULT CreateIndexData()override;
    virtual HRESULT CreateVertexBuffer()override;
    virtual HRESULT CreateIndexBuffer()override;
    virtual HRESULT LoadTextures(
        ID3D11Device* pd3dDevice,
        const TCHAR* pLoadTextureFile)override;
public:
   
public:
    Render_Obj();
    ~Render_Obj();
};
//오버라이딩 해서 무시하지 않은 Model->Create() 내부 함수들
//LoadShaderFile
//SetInputLayout
//CreateConstantBuffer
#pragma once
#include "CADx_Model2.h"

using namespace DX;
//InputLayout �ٸ���� �� �������̽��� ��ӹ޾Ƽ� ������
class Render_Obj :public DX::CADx_Model2
{
public:
    wstring m_szShader_Name;
    bool Create_Render_Obj(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile);
public:
    //Create_Render_Obj�� �佺//
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
//�������̵� �ؼ� �������� ���� Model->Create() ���� �Լ���
//LoadShaderFile
//SetInputLayout
//CreateConstantBuffer
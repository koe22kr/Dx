#pragma once
#include "CADx_Model2.h"

//InputLayout �ٸ���� �� �������̽��� ��ӹ޾Ƽ� ������

class Render_Obj :public DX::CADx_Model2
{
public:
    wstring m_szShader_Name;

    //���̴� ���� ������
    virtual HRESULT SetInputLayout()override;

    bool Create_Render_Obj(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile);
public:
    //Create_Render_Obj�� ����
    bool  Create(ID3D11Device* pd3dDevice,
        const TCHAR* pLoadShaderFile,
        const TCHAR* pLoadTextureFile);
private:
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

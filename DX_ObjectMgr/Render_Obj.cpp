#include "Render_Obj.h"

bool Render_Obj::Create_Render_Obj(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile)
{
    if (FAILED(LoadShaderFile(pd3dDevice, pLoadShaderFile)))
    {
#ifdef _DEBUG
        MessageBox(NULL, L"Create_Render_Obj_LoadShaderFile_Fail", L"Create_Render_Obj_LoadShaderFile_Fail", S_OK);
#endif // _DEBUG
        return false;
    }
    if (FAILED(SetInputLayout()))
    {
#ifdef _DEBUG
        MessageBox(NULL, L"Create_Render_Obj_SetInputLayout_Fail", L"Create_Render_Obj_SetInputLayout_Fail", S_OK);
#endif // _DEBUG
        return false;
    }
    if (FAILED(CreateConstantBuffer()))
    {
#ifdef _DEBUG
        MessageBox(NULL, L"Create_Render_Obj_CreateConstantBuffer_Fail", L"Create_Render_Obj_CreateConstantBuffer_Fail", S_OK);
#endif // _DEBUG
        return false;
    }
    m_szShader_Name = pLoadShaderFile;
    return true;
}
bool  Render_Obj::Create(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile, const TCHAR* pLoadTextureFile)
{
    return Create_Render_Obj(pd3dDevice, pLoadShaderFile);
}

// HRESULT Render_Obj::SetInputLayout()
//{
//     return S_OK;
//}
 HRESULT Render_Obj::CreateVertexData()
{
     return S_OK;

}
 HRESULT Render_Obj::CreateIndexData()
{
     return S_OK;

}
 HRESULT Render_Obj::CreateVertexBuffer()
 {
     return S_OK;

 }
 HRESULT Render_Obj::CreateIndexBuffer()
 {
     return S_OK;

 }
 HRESULT Render_Obj::LoadTextures(ID3D11Device* pd3dDevice, const TCHAR* pLoadTextureFile)
 {
     return S_OK;
 }
 
Render_Obj::Render_Obj()
{
}
Render_Obj::~Render_Obj()
{
}

#include "Render_Obj.h"

bool Render_Obj::Create_Render_Obj(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile)
{
    m_pDevice = pd3dDevice;
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

 HRESULT Render_Obj::SetInputLayout()
{
     HRESULT hr = S_OK;
     //input layout
     //정점버퍼의 데이터를 정점 쉐이더의 인자값으로 설정
     D3D11_INPUT_ELEMENT_DESC layout[] =
     {
         {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0  },
         {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0  },
         {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0  },
         {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0  },
         {"MAT_INDEX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0} ,
         {"MAT_WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 64, D3D11_INPUT_PER_VERTEX_DATA, 0} 

     };
 
     int iNumElement = sizeof(layout) / sizeof(layout[0]);
     m_helper.m_pInputLayout.Attach(
         DX::CreateInputLayout(m_pDevice,
             m_helper.m_pVSBlob->GetBufferSize(),
             m_helper.m_pVSBlob->GetBufferPointer(),
             layout, iNumElement));

     return hr;
}
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

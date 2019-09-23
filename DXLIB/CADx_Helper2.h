#include "CADevice.h"

#pragma once


namespace DX
{

    HRESULT CompilerShaderFromFile(
        const TCHAR* sFileName,
        LPCSTR szEntryPoint,
        LPCSTR szShaderModel,
        ID3DBlob** ppBlobOut);

    ID3D11VertexShader* LoadVertexShaderFile(
        ID3D11Device* pd3dDevice,
        const void* pShaderFileData,
        ID3DBlob** ppBlobOut = nullptr,
        const char* pFuntionName = 0,
        bool bBinary = false);
    ID3D11PixelShader* LoadPixelShaderFile(
        ID3D11Device* pd3dDevice,
        const void* pShaderFileData,
        ID3DBlob** ppBlobOut = nullptr,
        const char* pFuntionName = 0,
        bool bBinary = false);

    ID3D11InputLayout* CreateInputLayout(
        ID3D11Device* pd3dDevice,
        DWORD dwSize, LPCVOID lpData,
        D3D11_INPUT_ELEMENT_DESC* layout,
        UINT numElements);

    ID3D11Buffer* CreateVertexBuffer(
        ID3D11Device* pd3dDevice,
        void * pData,
        UINT iNumCount,
        UINT iSize,
        bool  bDynamic = false);
    ID3D11Buffer* CreateIndexBuffer(ID3D11Device* pd3dDevice,
        void * pData,
        UINT iNumCount,
        UINT iSize,
        bool  bDynamic = false);
    ID3D11Buffer* CreateConstantBuffer(
        ID3D11Device* pd3dDevice,
        void * pData,
        UINT iNumCount,
        UINT iSize,
        bool  bDynamic = false);

    class CADx_Helper2
    {
    public:
        UINT	m_iNumVertex;
        UINT	m_iNumIndex;
        UINT	m_iVertexSize;
    public:
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBuffer;
        Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;
        Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
        Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShaderMask;
        Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV;
        Microsoft::WRL::ComPtr<ID3DBlob> m_pVSBlob;

    public:
        void PreRender(ID3D11DeviceContext* pContext, UINT iSize=0);
        void PostRender(ID3D11DeviceContext* pContext, UINT iCount=0);
        bool Render(ID3D11DeviceContext* pContext, UINT iCount=0, UINT iSize=0);




    public:
        CADx_Helper2();
        virtual ~CADx_Helper2();
    };

}
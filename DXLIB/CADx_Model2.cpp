#include "CADx_Model2.h"

namespace DX
{


    HRESULT CADx_Model2::LoadShaderFile(
        ID3D11Device* pd3dDevice,
        const TCHAR* pLoadShaderFile)
    {
        HRESULT hr = S_OK;
        m_helper.m_pVertexShader.Attach(
            DX::LoadVertexShaderFile(pd3dDevice,
                pLoadShaderFile,
                m_helper.m_pVSBlob.GetAddressOf()));

        m_helper.m_pPixelShader.Attach(
            DX::LoadPixelShaderFile(pd3dDevice,
                pLoadShaderFile));
        return hr;
    }
    HRESULT CADx_Model2::SetInputLayout() {
        HRESULT hr = S_OK;
        //input layout
        //정점버퍼의 데이터를 정점 쉐이더의 인자값으로 설정
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0  },
            {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0  },
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0  },
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0  },
        };
        int iNumElement = sizeof(layout) / sizeof(layout[0]);
        m_helper.m_pInputLayout.Attach(
            DX::CreateInputLayout(m_pDevice,
                m_helper.m_pVSBlob->GetBufferSize(),
                m_helper.m_pVSBlob->GetBufferPointer(),
                layout, iNumElement));

        return hr;
    }
    HRESULT CADx_Model2::CreateVertexData() {
        HRESULT hr = S_OK;
        return hr;
    }
    HRESULT CADx_Model2::CreateIndexData() {
        HRESULT hr = S_OK;
        return hr;
    }
    HRESULT CADx_Model2::CreateVertexBuffer() {
        HRESULT hr = S_OK;
        m_helper.m_iVertexSize = sizeof(PNCT_VERTEX2);
        m_helper.m_iNumVertex = m_Vertex_List.size();;
        m_helper.m_pVertexBuffer.Attach(
            DX::CreateVertexBuffer(m_pDevice,
                &m_Vertex_List.at(0), m_helper.m_iNumVertex, m_helper.m_iVertexSize)
        );
        if (m_helper.m_pVertexBuffer.Get() == nullptr)
            return false;
        return hr;
    }
    HRESULT CADx_Model2::CreateIndexBuffer()
    {
        if (m_Index_List.size() <= 0) return S_OK;
        m_helper.m_iNumIndex = m_Index_List.size();
        m_helper.m_pIndexBuffer.Attach(
            DX::CreateIndexBuffer(m_pDevice,
                &m_Index_List.at(0), m_helper.m_iNumIndex, sizeof(DWORD))
        );
        if (m_helper.m_pIndexBuffer.Get() == nullptr)
            return false;
        HRESULT hr = S_OK;
        return hr;
    }
    HRESULT CADx_Model2::CreateConstantBuffer()
    {
        HRESULT hr = S_OK;

        VS_CB2 vc;
        ZeroMemory(&vc, sizeof(VS_CB2));
        vc.matWorld = DirectX::XMMatrixIdentity();
        vc.matView = m_matView;
        vc.matProj = m_matProj;
        vc.color[0] = 1.0f;
        vc.etc[0] = 0.0f;

        m_helper.m_pConstantBuffer.Attach(
            DX::CreateConstantBuffer(m_pDevice,
                &vc, 1, sizeof(VS_CB2), false)
        );
        if (m_helper.m_pConstantBuffer.Get() == nullptr)
            return false;
        return hr;
    }
    HRESULT CADx_Model2::LoadTextures(
        ID3D11Device* pd3dDevice,
        const TCHAR* pLoadTextureFile)
    {
        HRESULT hr = S_OK;
        if (pLoadTextureFile == nullptr) return S_OK;
        int iIndex = I_TextureMgr.Load(
            m_pDevice,
            pLoadTextureFile);

        if (iIndex >= 0)
        {
            m_helper.m_pSRV = I_TextureMgr.GetPtr(iIndex)->m_pSRV;
        }

        return hr;
    }
    bool   CADx_Model2::UpdateBuffer()
    {
        return true;
    }
    HRESULT CADx_Model2::CreateResource() {
        HRESULT hr = S_OK;
        return hr;
    }
    void CADx_Model2::SetCollisionData()
    {
        m_tBox.vCenter.x = 0.0f;
        m_tBox.vCenter.y = 0.0f;
        m_tBox.vCenter.z = 0.0f;
        m_tBox.vMin = D3DXVECTOR3(-1, -1, -1);
        m_tBox.vMax = D3DXVECTOR3(1, 1, 1);

        m_tBox.vAxis[0] = D3DXVECTOR3(1, 0, 0);
        m_tBox.vAxis[1] = D3DXVECTOR3(0, 1, 0);
        m_tBox.vAxis[2] = D3DXVECTOR3(0, 0, 1);
        m_tBox.fExtent[0] = 1.0f;
        m_tBox.fExtent[1] = 1.0f;
        m_tBox.fExtent[2] = 1.0f;
        m_tSphere.vCenter = *((DirectX::XMFLOAT3*)(&m_tBox.vCenter));
        DirectX::XMFLOAT3 v;
        v.x = m_tBox.vMax.x - m_tBox.vCenter.x;
        v.y = m_tBox.vMax.y - m_tBox.vCenter.y;
        v.z = m_tBox.vMax.z - m_tBox.vCenter.z;
        m_tSphere.fRadius = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
    }
    bool  CADx_Model2::Init()
    {
        m_matWorld = DirectX::XMMatrixIdentity();
        m_matView = DirectX::XMMatrixIdentity();
        m_matProj = DirectX::XMMatrixIdentity();
       
        return true;
    }
    bool  CADx_Model2::Frame() {
        return true;
    }
    bool  CADx_Model2::Render(ID3D11DeviceContext* pContext)
    {
        float fTime = g_fGameTimer;
        m_cb.color[0] = cosf(fTime);
        m_cb.color[1] = sinf(fTime);
        m_cb.color[2] = 1 - cosf(fTime);
        m_cb.color[3] = 1.0f;
        m_cb.etc[0] = fTime;
        if (m_helper.m_pConstantBuffer != NULL)
        {
            pContext->UpdateSubresource(
                m_helper.m_pConstantBuffer.Get(),
                0, NULL, &m_cb, 0, 0);
        }
        PreRender(pContext);
        PostRender(pContext);
        return true;
    }
    bool  CADx_Model2::PreRender(ID3D11DeviceContext* pContext)
    {
        m_helper.PreRender(pContext,
            m_helper.m_iVertexSize);
        return true;
    }
    bool  CADx_Model2::PostRender(ID3D11DeviceContext* pContext)
    {
        m_helper.PostRender(pContext,
            m_helper.m_iNumIndex);
        return true;
    }
    bool  CADx_Model2::Release() {
        return true;
    }
    bool  CADx_Model2::Create(ID3D11Device* pd3dDevice,
        const TCHAR* pLoadShaderFile,
        const TCHAR* pLoadTextureFile)
    {
        m_pDevice = pd3dDevice;
        if (FAILED(LoadShaderFile(pd3dDevice, pLoadShaderFile)))
        {
            return false;
        }
        if (FAILED(SetInputLayout()))
        {
            return false;
        }
        if (FAILED(CreateVertexData()))
        {
            return false;
        }
        if (FAILED(CreateIndexData()))
        {
            return false;
        }
        if (FAILED(CreateVertexBuffer()))
        {
            return false;
        }
        if (FAILED(CreateIndexBuffer()))
        {
            return false;
        }
        if (FAILED(CreateConstantBuffer()))
        {
            return false;
        }
        if (FAILED(LoadTextures(
            pd3dDevice,
            pLoadTextureFile)))
        {
            return false;
        }
        if (!UpdateBuffer())
        {
            return false;
        }
        if (FAILED(CreateResource()))
        {
            return false;
        }

        SetCollisionData();

        return Init();
    }
    void  CADx_Model2::SetMatrix(DirectX::XMMATRIX* pWorld,
        DirectX::XMMATRIX* pView,
        DirectX::XMMATRIX* pProj)
    {
        if (pWorld != nullptr)
        {
            m_matWorld = *pWorld;
        }
        if (pView != nullptr)
        {
            m_matView = *pView;
        }
        if (pProj != nullptr)
        {
            m_matProj = *pProj;
        }
        m_cb.matWorld = DirectX::XMMatrixTranspose(m_matWorld);
        m_cb.matView = DirectX::XMMatrixTranspose(m_matView);
        m_cb.matProj = DirectX::XMMatrixTranspose(m_matProj);


        DirectX::XMFLOAT4X4 temp;
        DirectX::XMStoreFloat4x4(&temp, m_matWorld);


        m_tBox.vCenter.x = temp._41;
        m_tBox.vCenter.y = temp._42;
        m_tBox.vCenter.z = temp._43;
        m_tSphere.vCenter = *((DirectX::XMFLOAT3*)(&m_tBox.vCenter));
    }
    void  CADx_Model2::SetMatrix(D3DXMATRIX* pWorld,
        D3DXMATRIX* pView,
        D3DXMATRIX* pProj)
    {
        if (pWorld != nullptr)
        {
       
            m_matWorld = *((DirectX::XMMATRIX*)pWorld);
            
        }
        if (pView != nullptr)
        {
            m_matView = *((DirectX::XMMATRIX*)pView);
        }
        if (pProj != nullptr)
        {
            m_matProj = *((DirectX::XMMATRIX*)pProj);
        }
        //요 디버깅
        m_cb.matWorld = DirectX::XMMatrixTranspose(m_matWorld);
        m_cb.matView = DirectX::XMMatrixTranspose(m_matView);
        m_cb.matProj = DirectX::XMMatrixTranspose(m_matProj);


        DirectX::XMFLOAT4X4 temp;
        DirectX::XMStoreFloat4x4(&temp, m_matWorld);


        m_tBox.vCenter.x = temp._41;
        m_tBox.vCenter.y = temp._42;
        m_tBox.vCenter.z = temp._43;
        m_tSphere.vCenter = *((DirectX::XMFLOAT3*)&m_tBox.vCenter);
    }

    CADx_Model2::CADx_Model2()
    {
        m_matWorld = DirectX::XMMatrixIdentity();
        m_matView = DirectX::XMMatrixIdentity();
        m_matProj = DirectX::XMMatrixIdentity();

       
    }
    


    CADx_Model2::~CADx_Model2()
    {
    }

}
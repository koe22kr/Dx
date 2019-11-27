#pragma once
#include "CADx_Helper2.h"
#include "CATexture.h"
#include "CATexture_Mgr.h"
namespace DX
{
    struct PC_VERTEX
    {
        DirectX::XMFLOAT3 p;
        DirectX::XMFLOAT4 c;

        PC_VERTEX() {}
        PC_VERTEX(DirectX::XMFLOAT3		vp,
            DirectX::XMFLOAT4		vc)
        {
            p = vp, c = vc;
        }
    };
    struct PNCT_VERTEX2
    {
        DirectX::XMFLOAT3 p;
        DirectX::XMFLOAT3 n;
        DirectX::XMFLOAT4 c;
        DirectX::XMFLOAT2 t;

        PNCT_VERTEX2() {}
        PNCT_VERTEX2(DirectX::XMFLOAT3		vp,
            DirectX::XMFLOAT3		vn,
            DirectX::XMFLOAT4		vc,
            DirectX::XMFLOAT2     vt)
        {
            p = vp, n = vn, c = vc, t = vt;
        }
    };

    struct PNCTT_VERTEX
    {
        DirectX::XMFLOAT3 p;
        DirectX::XMFLOAT3 n;
        DirectX::XMFLOAT4 c;
        DirectX::XMFLOAT2 t;
        DirectX::XMFLOAT3 tangent;
        DirectX::XMFLOAT3 Normal_Map;
        PNCTT_VERTEX() {}
        PNCTT_VERTEX(DirectX::XMFLOAT3		vp,
            DirectX::XMFLOAT3		vn,
            DirectX::XMFLOAT4		vc,
            DirectX::XMFLOAT2     vt,
            DirectX::XMFLOAT3 vtangent,
            DirectX::XMFLOAT3 vNormal_Map)
        {
            p = vp, n = vn, c = vc, t = vt, tangent = vtangent, Normal_Map = vNormal_Map;
        }
    };
    struct VS_CB2
    {
        DirectX::XMMATRIX matWorld;
        DirectX::XMMATRIX matView;
        DirectX::XMMATRIX matProj;
        float etc[4];
    };
    
    struct T_SPHERE
    {
        DirectX::XMFLOAT3 vCenter;
        float       fRadius;
    };

    class CADx_Model2
    {
    public:
        int m_iIndex;
        DirectX::XMMATRIX m_matWorld;
        DirectX::XMMATRIX m_matView;
        DirectX::XMMATRIX m_matProj;
        VS_CB2      m_cb;
        //T_BOX      m_tBox;
        //T_SPHERE   m_tSphere;

        VS_CONSTANT_BUFFER			m_cbData;


        vector<PNCT_VERTEX2> m_Vertex_List;
        vector<DWORD>		m_Index_List;
        DX::CADx_Helper2		m_helper;
        ID3D11Device*			m_pDevice;
        ID3D11DeviceContext*	m_pImmediateContext;
    protected:
        CATexture*   m_pTexture;
        CATexture*   m_pTextureMask;
    public:
        virtual bool  Init();
        virtual bool  Frame();
        virtual bool  PreRender(ID3D11DeviceContext* pContext);
        virtual bool  Render(ID3D11DeviceContext* pContext);
        virtual bool  PostRender(ID3D11DeviceContext* pContext);
        virtual bool  Release();
       virtual bool  Create(ID3D11Device* pd3dDevice,
            const TCHAR* pLoadShaderFile,
            const TCHAR* pLoadTextureFile);

        virtual HRESULT LoadShaderFile(
            ID3D11Device* pd3dDevice,
            const TCHAR* pLoadShaderFile);
        virtual HRESULT SetInputLayout();
        virtual HRESULT CreateVertexData();
        virtual HRESULT CreateIndexData();
        virtual HRESULT CreateVertexBuffer();
        virtual HRESULT CreateIndexBuffer();
        virtual HRESULT CreateConstantBuffer();
        virtual HRESULT LoadTextures(
            ID3D11Device* pd3dDevice,
            const TCHAR* pLoadTextureFile);
        virtual bool   UpdateBuffer();
        void SetCollisionData();

        virtual void  SetMatrix(DirectX::XMMATRIX* pWorld,
            DirectX::XMMATRIX* pView,
            DirectX::XMMATRIX* pProj);
        virtual void  SetMatrix(D3DXMATRIX* pWorld,
            D3DXMATRIX* pView,
            D3DXMATRIX* pProj);



        CADx_Model2();

        virtual ~CADx_Model2();

    };

}
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
        float color[4];
        float etc[4];
    };
    struct T_BOX
    {
        DirectX::XMFLOAT3 vCenter;
        DirectX::XMFLOAT3 vMin;
        DirectX::XMFLOAT3 vMax;
        DirectX::XMFLOAT3 vAxis[3];
        float       fExtent[3];
    };
    struct T_SPHERE
    {
        DirectX::XMFLOAT3 vCenter;
        float       fRadius;
    };

    class CADx_Model2
    {
    public:



    public:
        DirectX::XMMATRIX m_matWorld;
        DirectX::XMMATRIX m_matView;
        DirectX::XMMATRIX m_matProj;
        VS_CB2      m_cb;
        T_BOX      m_tBox;
        T_SPHERE   m_tSphere;
        vector<PNCT_VERTEX2> m_Vertex_List;
        vector<PNCTT_VERTEX> m_Vertex_List2;
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
        bool  Create(ID3D11Device* pd3dDevice,
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
        virtual HRESULT CreateResource();
        void SetCollisionData();

        virtual void  SetMatrix(DirectX::XMMATRIX* pWorld,
            DirectX::XMMATRIX* pView,
            DirectX::XMMATRIX* pProj);




        CADx_Model2();
        virtual ~CADx_Model2();

    };

}
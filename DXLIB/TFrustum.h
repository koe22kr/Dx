#pragma once
#include "CADx_Std.h"
#include "CADx_Shape.h"
namespace DX
{
    enum T_POSITION
    {
        P_BACK = 0,    // Point is positioned behind plane
        P_FRONT,   // Point is positioned in front of plane	
        P_ONPLANE, // Point is positioned on plane
        P_SPANNING // Point is spanning plane
    };

    class TFrustum
    {
    public:
    public:
        bool		Init();
        bool		Frame();
        bool		PreRender(ID3D11DeviceContext*    pImmediateContext);
        bool		PostRender(ID3D11DeviceContext*    pImmediateContext);
        bool		Render(ID3D11DeviceContext*    pImmediateContext);
        bool		Release();
        bool		ResetDevice();
        bool		ResetResource() { return true; };

    public:
        D3DXMATRIX  m_matViewProj;
        D3DXMATRIX  m_mWorld;
        D3DXMATRIX  m_mView;
        D3DXMATRIX  m_mProj;
        D3DXVECTOR3	m_vFrustum[8];	/// 프러스텀을 구성할 정점 8개
        vector<PNCT_VERTEX> m_VertexList;
        D3DXPLANE	m_DxPlane[6];	/// 프러스텀을 구성하는 6개의 평면
        T_PLANE		m_Plane[6];
        D3DXVECTOR3	m_vNearCenter;
        CADx_Shape_Box*	m_pBoxShape;
        ID3D11Device*		m_pd3dDevice;
       Microsoft::WRL::ComPtr<ID3D11PixelShader>  m_pPixelShader;
    public:
        void	SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
        bool	CreateRenderBox(ID3D11Device*  pd3dDevice, ID3D11DeviceContext*    pImmediateContext);
        bool	CreateFrustum();
        void	ExtractPlanesD3D(T_PLANE* pPlanes, const D3DXMATRIX & comboMatrix);
        BOOL	ClassifyPoint(D3DXVECTOR3* pv);
        BOOL	ClassifySphere(T_SPHERE* pSphere);
        BOOL	CheckOBBInPlane(T_BOX*  pBox);
        T_POSITION CheckPoitionOBBInPlane(T_BOX*  pBox);
    public:
        /// 생성자
        TFrustum();
        virtual ~TFrustum();
    };
}
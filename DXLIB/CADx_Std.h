#pragma once
#include "CAStd.h"
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <D2D1.h>
#include <wrl.h>

#include <d3d11.h>
#include <d3dx11.h> 
#include <dxgi.h>
#include <d3dx10math.h>
#include <D3DCompiler.h>

#include <dinput.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment( lib, "dxguid.lib" )

//#include "dxdiag.h"

#pragma comment( lib, "d3dcompiler.lib" )
#pragma comment( lib, "d2d1.lib")
#pragma comment (lib, "dxgi.lib")

namespace DX
{
#ifdef _DEBUG
#pragma comment (lib, "d3d11.lib")
#pragma comment( lib, "d3dx10d.lib" )	
#pragma comment( lib, "d3dx11d.lib" )	

#define EM(hr,msg,_where) if (FAILED(hr)) MessageBox(NULL, L#msg, L#_where, MB_OK)

#else
#pragma comment (lib, "d3d11.lib")

#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "d3dx11.lib")

#define EM(hr,msg,_where)

#endif // DEBUG

    struct T_PLANE
    {
        float	fA, fB, fC, fD;
        bool	CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2);
        bool	CreatePlane(D3DXVECTOR3 vNormal, D3DXVECTOR3 v0);
        void	Normalize()
        {
            float fMag = sqrt(fA*fA + fB * fB + fC * fC);
            fA = fA / fMag;
            fB = fB / fMag;
            fC = fC / fMag;
            fD = fD / fMag;
        }

    };


    struct VS_CONSTANT_BUFFER
    {
        D3DXMATRIX matWorld;// c0						
        D3DXMATRIX matView;	// c4						
        D3DXMATRIX matProj;	// c8						
        D3DXVECTOR4 Color; // 12
    };


}
struct PNCT_VERTEX
{
    DirectX::XMFLOAT3 p;
    DirectX::XMFLOAT3 n;
    DirectX::XMFLOAT4 c;
    DirectX::XMFLOAT2 t;

    PNCT_VERTEX() {}
    PNCT_VERTEX(DirectX::XMFLOAT3 in_p, DirectX::XMFLOAT3 in_n, DirectX::XMFLOAT4 in_c, DirectX::XMFLOAT2 in_t)
    {
        p = in_p;
        n = in_n;
        c = in_c;
        t = in_t;
    }


};

//////////////////////////////////////////////
// 객체 및 배열 할당과 삭제 및 소멸 매크로
//////////////////////////////////////////////
#ifndef SAFE_ZERO
#define SAFE_ZERO(A)				{ A = 0; }
#endif

#ifndef SAFE_NEW
#define SAFE_NEW(A, B)				{ if (!A) A = new B; }
#endif 

#ifndef SAFE_DEL
#define SAFE_DEL(A)					{ if (A) delete A; (A)=NULL; }
#endif 

#ifndef SAFE_NEW_ARRAY
#define SAFE_NEW_ARRAY(A, B, C)		{ if (!A && C) A = new B[C]; }
#endif 

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(A)		{ if (A) delete [] A; (A)=NULL; }
#endif 

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }
#endif 

#ifndef SAFE_NEW_CLEAR
#define SAFE_NEW_CLEAR( A, B )			{ if (!A) A = new B; if(A) memset( A, 0, sizeof(B) ); };
#endif 

#ifndef SAFE_NEW_ARRAY_CLEAR
#define SAFE_NEW_ARRAY_CLEAR( A, B, C )	{ if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };
#endif

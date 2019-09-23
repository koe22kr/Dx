#pragma once
#include "CADx_Std.h"
#include "CACore.h"
#include "CADevice_Helper.h"
#include "CADx_Helper2.h"
#include "CADx_Shape.h"
using namespace Microsoft::WRL;
using namespace DX;
struct LIGHT_CONSTANT_BUFFER
{
    D3DXMATRIX			g_matInvWorld;
    // Material
    D3DXVECTOR4			g_cAmbientMaterial;
    D3DXVECTOR4			g_cDiffuseMaterial;
    D3DXVECTOR4			g_cSpecularMaterial;
    D3DXVECTOR4			g_cEmissionMaterial;
    // Light
    D3DXVECTOR4			g_cAmbientLightColor;
    D3DXVECTOR4			g_cDiffuseLightColor;
    D3DXVECTOR4			g_cSpecularLightColor;
    D3DXVECTOR4			g_vLightDir; // w = light damping(attenuation) : ����
    D3DXVECTOR4			g_vLightPos; // w = light radius
    D3DXVECTOR4			g_vEyeDir;// w = light intensity : ����
    D3DXVECTOR4			g_vEyePos;// w = light radius	
};

class Sample :public CACore
{
    float angleyaw;
    CADx_Shape m_shape_Obj;
    CADx_Shape_Line m_Debug_Line;
    D3DXVECTOR3		m_vLightVector;
        LIGHT_CONSTANT_BUFFER m_cbLight;
        ComPtr<ID3D11Buffer>	m_pConstantBufferLight;
    public:
        bool		Init();
        bool		Frame();
        bool		Render();
        bool		Release();
        bool		DrawDebug();
        //--------------------------------------------------------------------------------------
        // ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
        //--------------------------------------------------------------------------------------
        HRESULT		CreateResource();
    public:

public:
    Sample();
    virtual ~Sample();
};

WINRUN_DEFAULT
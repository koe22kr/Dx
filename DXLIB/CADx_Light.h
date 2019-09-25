#pragma once
#include "CADx_Std.h"
#include "CADevice_Helper.h"
#include "CADx_Helper2.h"
#include "CADx_Shape.h"
#include "TCamera.h"

class TCamera;

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
        D3DXVECTOR4			g_vLightDir; // w = light damping(attenuation) : °¨¼è
        D3DXVECTOR4			g_vLightPos; // w = light radius
        D3DXVECTOR4			g_vEyeDir;// w = light intensity : °­µµ
        D3DXVECTOR4			g_vEyePos;// w = light radius	
    };



    class CADx_Light
    {
    public:
        float angleyaw;
        DX::CADx_Shape m_shape_Obj;
        DX::CADx_Shape_Line m_Debug_Line;
        D3DXVECTOR3		m_vLightVector;
        LIGHT_CONSTANT_BUFFER m_cbLight;
        Microsoft::WRL::ComPtr<ID3D11Buffer>	m_pConstantBufferLight;
    public:
        bool		Init();
        bool		Frame(DX::TCamera* now_cam);
        bool		Release();
       
        HRESULT		CreateResource();
    public:

        CADx_Light();
        virtual ~CADx_Light();
    };



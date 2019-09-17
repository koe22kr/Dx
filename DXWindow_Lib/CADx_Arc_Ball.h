#include "CADevice.h"

#pragma once

namespace DX
{

    class CADx_Arc_Ball
    {
    public:
        bool m_bDrag;
        DirectX::XMVECTOR m_vBefore_Pt;
        DirectX::XMVECTOR m_vCurrent_Pt;

        int                 m_iWidth;
        int                 m_iHeight;
        float               m_fRadius;
        DirectX::XMFLOAT2   m_vCenter;
        DirectX::XMVECTOR   m_qBefore;
        DirectX::XMVECTOR   m_qNow;
        DirectX::XMMATRIX   m_mRotation;
    public:
        void Init();
        void Set_Window(int width, int height, float radius = 0.9);

        void Move_On(int x, int y);
        void Moving(int x, int y);
        void Move_End(int x, int y);
        DirectX::XMMATRIX Get_Rotation_Matrix();
        DirectX::XMVECTOR Quat_From_Ball_Points(const DirectX::XMVECTOR& vfrom, const DirectX::XMVECTOR& vto);
        DirectX::XMVECTOR Screen_To_Vector(float fscreen_ptx, float fscreen_pty);
    public:
        CADx_Arc_Ball();
        ~CADx_Arc_Ball();
    };


}
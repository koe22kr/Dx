#include "CADevice.h"

#pragma once

namespace DX
{

    class CADx_Arc_Ball
    {
    public:
        bool m_bDrag;
        DirectX::XMVECTOR m_vBefore_Pt;
        DirectX::XMFLOAT2 m_vbefore_xy;
        DirectX::XMVECTOR m_vCurrent_Pt;
        DirectX::XMFLOAT3 m_vAngle;
        float m_fSpeed = 0.01;
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

        void Move_On(float x, float y);
        void Moving(float x, float y);
        void Move_End(float x, float y);
        DirectX::XMMATRIX Get_Rotation_Matrix();
        DirectX::XMVECTOR Get_Quaternion() { return m_qNow; };
        DirectX::XMVECTOR Quat_From_Ball_Points(const DirectX::XMVECTOR& vfrom, const DirectX::XMVECTOR& vto);
        //DirectX::XMVECTOR QuatFromBallPoints(const DirectX::XMVECTOR &vfrom, const DirectX::XMVECTOR vto);
        DirectX::XMVECTOR Screen_To_Vector(float fscreen_ptx, float fscreen_pty);
    public:
        CADx_Arc_Ball();
        ~CADx_Arc_Ball();
    };


}
#include "CADx_Arc_Ball.h"

namespace DX
{



    void CADx_Arc_Ball::Init()
    {
        Set_Window(g_rtClient.right, g_rtClient.bottom);
    }
    void CADx_Arc_Ball::Set_Window(int width, int height, float radius)
    {
        m_iWidth = width;
        m_iHeight = height;
        m_fRadius = radius;
        m_vCenter.x = m_iWidth / 2;
        m_vCenter.y = m_iHeight / 2;
    }

    void CADx_Arc_Ball::Move_On(float x, float y)
    {
        m_bDrag = true;
        m_vbefore_xy.x = x;
        m_vbefore_xy.y = y;
        m_vBefore_Pt = Screen_To_Vector(x, y);
       
       

    }
    void CADx_Arc_Ball::Moving(float x, float y)
    {
        if (m_bDrag)
        {
        
            m_vAngle.x += DirectX::XMConvertToRadians(x - m_vbefore_xy.y)*m_fSpeed;
            m_vAngle.y += DirectX::XMConvertToRadians(y - m_vbefore_xy.x)*m_fSpeed;


            m_vCurrent_Pt = Screen_To_Vector(x, y);
            m_qNow = DirectX::XMQuaternionMultiply(m_qBefore, Quat_From_Ball_Points(m_vBefore_Pt, m_vCurrent_Pt));
            //m_qNow = m_qBefore * Quat_From_Ball_Points(m_vBefore_Pt, m_vCurrent_Pt);


            m_vBefore_Pt = m_vCurrent_Pt;
        }


    }
    void CADx_Arc_Ball::Move_End(float x, float y)
    {
        m_bDrag = false;
    }
    DirectX::XMMATRIX CADx_Arc_Ball::Get_Rotation_Matrix()
    {
        return m_mRotation = DirectX::XMMatrixRotationQuaternion(m_qNow);
    }
    
    DirectX::XMVECTOR CADx_Arc_Ball::Quat_From_Ball_Points(const DirectX::XMVECTOR& vfrom, const DirectX::XMVECTOR& vto)
    {
        DirectX::XMVECTOR dot = DirectX::XMVector3Dot(vfrom, vto);
        DirectX::XMVECTOR cross = DirectX::XMVector3Cross(vfrom, vto);
        DirectX::XMFLOAT4 floatdot;
        XMStoreFloat4(&floatdot, dot);

        DirectX::XMVECTOR ret = cross;
        ret = DirectX::XMVectorSetZ(ret, floatdot.x);
        return ret;
    }
    DirectX::XMVECTOR CADx_Arc_Ball::Screen_To_Vector(float fscreen_ptx, float fscreen_pty)
    {
        // Scale to screen X*X + Y*Y + Z*Z = R * R(���������)\
        // �� ������ : ȭ����� = �� ���а� : ȭ�鼺�а�
        // �� ���а� = ( �� ������ * ȭ�鼺�а� ) / ȭ�����

        float x = -(fscreen_ptx - m_iWidth / 2) / (m_fRadius*m_iWidth / 2);
        float y = (fscreen_pty - m_iHeight / 2) / (m_fRadius*m_iHeight / 2);
        float z = 0.0f;
        // �� z���а� ���� = �� x���а� ���� * �� y���а� ����
        float mag = x * x + y * y;

        // ȭ����̸� �� ������ 1�� �ξ��� ������ 1���� ũ�� ȭ����̱� ������ ����� ������ ��ü�Ѵ�.   <- �� �𸣰�
       // X*X + Y*Y + Z*Z = 1(���������)
        if (mag > 1.0f)
        {
            float scale = 1.0f / sqrtf(mag);
            x *= scale;
            y *= scale;

        }
        else
        {
            z = sqrtf(1.0f - mag);
        }
        DirectX::XMVECTOR ret = DirectX::XMVectorSet(x, y, z, 0);
        return ret;
    }


    CADx_Arc_Ball::CADx_Arc_Ball()
    {
        m_bDrag = false;
        m_qBefore = DirectX::XMQuaternionIdentity();
        m_qNow = DirectX::XMQuaternionIdentity();
        Set_Window(g_rtClient.right, g_rtClient.bottom);
    }


    CADx_Arc_Ball::~CADx_Arc_Ball()
    {
    }
}
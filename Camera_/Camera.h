#pragma once
#include "CADx_Std.h"
#include "CADx_Arc_Ball.h"
#include "CAStd.h"
#include "CADevice_Helper.h"

//DirectX::XMVectorSet();

namespace DX
{
    enum Camera_Type
    {
        Non_Target = 1, Target = 2, Model = 3
    };
    class Camera
    {
    //private:
    public:
        VS_CB m_cb;
        CADevice_Helper m_hDX;
        CADx_Arc_Ball m_Arc_Ball;
        UINT m_uCamera_Type;
        float m_fMin_Radian = 3;
        float m_fMax_Radian = FLT_MAX;
        float m_fRadian;
        //백터
        DirectX::XMVECTOR m_vPos;
        DirectX::XMVECTOR m_vMove_Target_Pos;
        DirectX::XMVECTOR m_vTarget_Look;
        DirectX::XMVECTOR m_vLook;
        DirectX::XMVECTOR m_vUp;
        DirectX::XMVECTOR m_vRight;
        DirectX::XMVECTOR m_vLook_Target_Pos;
        //행렬
        DirectX::XMMATRIX m_Matrix_World;
        //DirectX::XMMATRIX m_Matrix_View_Before;
        DirectX::XMMATRIX m_Matrix_View;
        DirectX::XMMATRIX m_Matrix_Projection;
        DirectX::XMMATRIX Set_World(float x, float y, float z);
        DirectX::XMMATRIX Set_View(DirectX::XMVECTOR pos, DirectX::XMVECTOR target_pos,
            DirectX::XMVECTOR up);
        DirectX::XMMATRIX Set_Projection(float nearPlane, float farPlane, float Fovy, float Aspect);
        // 시야거리
        float m_fNear;
        float m_fFar;
        //카메라 회전
        float m_fFov;//field of view (y[세로]사용)
        float m_Aspect;//종횡비

        float Slerp_Speed;
        DirectX::XMFLOAT3 m_vNow_Angles;
        DirectX::XMFLOAT3 m_vTarget_Angles;
        /* float m_fCamera_Yaw_Angle;
         float m_fCamera_Pitch_Angle;
         float m_fCamera_Roll_Angle;*/

    public:
        void Set_Matrix();

        void Lerp_Frame(float Slerp_Speed = 1.0f);

        void Rotation_No_Lerp(float pitch, float yaw, float roll);
        //카메라 이동
        float m_fSpeed = 10.0f;
        float Real_Speed;
        void Move_Look();
        void Move_Side();
        //void Move_Up();
        void Move_World_Z();
        void Move_World_Y();
        void Move_World_X();
        void Move_World_Rev_Z();
        void Move_World_Rev_Y();
        void Move_World_Rev_X();
        //
        void Zoom(float zoom);
        void Set_Min_Max_Radian(float min, float max);
        //
        Camera* m_pMain_Camera;
        void Non_Target_Camera_Rotation(float yaw, float pitch, float roll);
        //void Target_Camera_Rotation(DirectX::XMVECTOR target);
        //void Model_Camera_Rotation();
        //void Set_Radian();
        void Update();
        bool Set_Camera();    // 해야할.

        bool Init();
        bool Frame();
        //bool Render();
        //bool Release();

    public:
        Camera();
        virtual ~Camera();
    };

}
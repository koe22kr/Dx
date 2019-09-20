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
        DirectX::XMMATRIX m_mModelRot;
        DirectX::XMMATRIX m_mModelLastRot;
        DirectX::XMVECTOR m_vLerpUpVector;
        DirectX::XMMATRIX m_lastRot;

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
        virtual void Rotation();
    public:
        void Set_Matrix();

        void Lerp_Frame(float Slerp_Speed = 1.0f);

        //카메라 이동
        float m_fSpeed = 50.0f;
        float Real_Speed;
       
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
        void Rotation_By_Arc_Ball();
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
    class Debug_Camera :public Camera
    {
    public:
        void Move_Look();
        void Move_Back();
        void Move_Left();
        void Move_Right();
        void Non_Target_Camera_Rotation(float yaw, float pitch, float roll);
        void Rotation_No_Lerp(float pitch, float yaw, float roll);
        DirectX::XMMATRIX Set_View(DirectX::XMVECTOR pos, DirectX::XMVECTOR target_pos, DirectX::XMVECTOR up);
        virtual void Rotation_YPR();


        bool Init();
        bool Frame();
        virtual void Rotation();

        Debug_Camera();
        ~Debug_Camera();

    private:

    };

 

}
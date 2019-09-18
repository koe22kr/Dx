#include "Camera.h"
namespace DX
{


    DirectX::XMMATRIX Camera::Set_World(float x, float y, float z)
    {
        //DirectX::XMFLOAT4 move;
        //m_vPos = DirectX::XMVectorSet(x, y, z, 0);

        m_Matrix_World = DirectX::XMMatrixSet(1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            x, y, z, 1);
        
        return m_Matrix_World;
    }

    DirectX::XMMATRIX Camera::Set_View(DirectX::XMVECTOR pos, DirectX::XMVECTOR target_pos,
        DirectX::XMVECTOR up)
    {
        m_vPos = pos;
        m_vLook_Target_Pos = target_pos;
        m_vUp = up;
        m_Matrix_View = DirectX::XMMatrixLookAtLH(pos, target_pos, up);
        return m_Matrix_View;
    }
    DirectX::XMMATRIX Camera::Set_Projection(float nearPlane, float farPlane, float Fovy, float Aspect)
    {
        m_fNear = nearPlane;
        m_fFar = farPlane;
        m_fFov = Fovy;
        m_Aspect = Aspect;
        m_Matrix_Projection = DirectX::XMMatrixPerspectiveFovLH(Fovy, Aspect, nearPlane, farPlane);
        return m_Matrix_Projection;
    }
    void Camera::Update()
    {
        DirectX::XMFLOAT4X4 viewdata;
        DirectX::XMStoreFloat4x4(&viewdata, m_Matrix_View);

        m_vLook = DirectX::XMVectorSet(viewdata._13, viewdata._23, viewdata._33, 0);
        m_vUp = DirectX::XMVectorSet(viewdata._12, viewdata._22, viewdata._32, 0);
        m_vRight = DirectX::XMVectorSet(viewdata._11, viewdata._21, viewdata._31, 0);
        m_Matrix_View = Set_View(m_vPos, m_vLook_Target_Pos, m_vUp);
        //m_Matrix_World = DirectX::XMMatrixIdentity();

        DirectX::XMVector3Normalize(m_vRight);
        DirectX::XMVector3Normalize(m_vUp);
        DirectX::XMVector3Normalize(m_vLook);
        
        m_cb.matProj = DirectX::XMMatrixTranspose(m_Matrix_Projection);
        m_cb.matView = DirectX::XMMatrixTranspose(m_Matrix_View);
        m_cb.matWorld = DirectX::XMMatrixTranspose(m_Matrix_World);
        m_hDX.Set_Const_Buffer(m_hDX.m_cConst_Buffer.Get(), &m_cb, 0);
        
        
    }
    void Camera::Rotation_No_Lerp(float pitch, float yaw, float roll)
    {
        m_vTarget_Angles.y += yaw;
        m_vTarget_Angles.x += pitch;
        m_vTarget_Angles.z += roll;
        m_Matrix_View = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
        m_Matrix_View = DirectX::XMMatrixInverse(NULL, m_Matrix_View);
        Update();
    }

    void Camera::Non_Target_Camera_Rotation(float yaw, float pitch, float roll)
    {
        m_vTarget_Angles.y += DirectX::XMConvertToRadians(yaw);
        m_vTarget_Angles.x += DirectX::XMConvertToRadians(pitch);
        m_vTarget_Angles.z += DirectX::XMConvertToRadians(roll);


        Lerp_Frame();
        Update();

    }

    void Camera::Lerp_Frame(float Slerp_Speed)
    {
        if (m_uCamera_Type == Non_Target)
        {
            //타켓룩 생성
            DirectX::XMVECTOR Target_Q = DirectX::XMQuaternionRotationRollPitchYaw(m_vTarget_Angles.x, m_vTarget_Angles.y, m_vTarget_Angles.z);

            DirectX::XMMATRIX rotation_matrix = DirectX::XMMatrixRotationQuaternion(Target_Q);

            DirectX::XMVECTOR world_look = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
            m_vTarget_Look = DirectX::XMVector3TransformCoord(world_look, rotation_matrix);

            //m_Matrix_View 생성 (현재의)
            DirectX::XMVECTOR Now_Q = DirectX::XMQuaternionRotationRollPitchYaw(m_vNow_Angles.x, m_vNow_Angles.y, m_vNow_Angles.z);
            DirectX::XMVECTOR slerp_quternion = DirectX::XMQuaternionSlerp(Now_Q, Target_Q, Slerp_Speed);
            DirectX::XMVECTOR Scale = DirectX::XMVectorSplatOne();
            DirectX::XMVECTOR Zero_Center = DirectX::XMVectorZero();
            m_Matrix_View = DirectX::XMMatrixAffineTransformation(Scale, Zero_Center, slerp_quternion, m_vPos);


            //m_Matrix_View = DirectX::XMMatrixInverse(NULL, m_Matrix_View);
        }
        if (m_uCamera_Type == Target)
        {
        }
        if (m_uCamera_Type == Model)
        {

        }


    }

    //void Camera::Target_Camera_Rotation(DirectX::XMVECTOR targetpos)
    //{
    //    Set_Radian();
    //
    //    //DirectX::XMVectorLerp(,)
    //    //m_vTarget_Look = target_pos-m_vPos; * m_vLook
    //    DirectX::XMMATRIX target_matrix = DirectX::XMMatrixLookAtLH(m_vPos, targetpos, m_vUp);
    //   
    //    DirectX::XMVECTOR world_look = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    //    m_vTarget_Look = DirectX::XMVector3TransformCoord(world_look, target_matrix);
    //
    //    DirectX::XMVECTOR lerp_vector = DirectX::XMVectorLerp(m_vLook, m_vTarget_Look, Slerp_Speed); //now look
    //
    //    
    //    DirectX::XMFLOAT4 right;
    //    DirectX::XMVECTOR row_right = DirectX::XMVector3Cross(lerp_vector, m_vUp);
    //    DirectX::XMStoreFloat4(&right, row_right);
    //    
    //    DirectX::XMFLOAT4 up;
    //    DirectX::XMVECTOR row_up;
    //    DirectX::XMStoreFloat4(&up, DirectX::XMVector3Cross(lerp_vector, row_right));
    //
    //    //DirectX::XMVector3Cross(lerp_vector, right);
    //
    //    DirectX::XMFLOAT4 look;
    //    DirectX::XMStoreFloat4(&look, m_vLook);
    //    DirectX::XMFLOAT4 pos;
    //    DirectX::XMStoreFloat4(&pos, m_vPos);
    //
    //    m_Matrix_View = DirectX::XMMatrixSet(right.x, right.y, right.z, right.w, up.x, up.y, up.z, up.w, look.x, look.y, look.z, look.w, pos.x, pos.y, pos.z, pos.w);
    //
    //
    //    //m_vLook = lerp_vector;
    //    //m_vRight = right;
    //    //m_vUp = up;
    //}
    //
    //void Camera::Model_Camera_Rotation()
    //{
    //
    //    Set_Radian();
    //}
    //void Camera::Set_Radian()
    //{
    //    /////
    //    DirectX::XMFLOAT3 fpos;
    //    DirectX::XMStoreFloat3(&fpos, m_vPos);
    //    DirectX::XMFLOAT3 flook;
    //    DirectX::XMStoreFloat3(&flook, m_vLook_Target_Pos);
    //    fpos.x = fpos.x - flook.x;
    //    fpos.y = fpos.y - flook.y;
    //    fpos.z = fpos.z - flook.z;
    //
    //    m_fRadian = sqrtf(fpos.x*fpos.x + fpos.y*fpos.y + fpos.z*fpos.z);
    //    ////
    //    m_fRadian = __min(m_fRadian, m_fMax_Radian);
    //    m_fRadian = __max(m_fRadian, m_fMin_Radian);
    //
    //} 

    void Camera::Zoom(float zoom)
    {
        m_fRadian += zoom;
    }

    void Camera::Move_Look()
    {
        m_Matrix_View += DirectX::XMMatrixTranslationFromVector(
            DirectX::XMVectorScale(m_vLook, m_fSpeed));

        Update();
    }
    void Camera::Move_Side()
    {
        m_Matrix_View += DirectX::XMMatrixTranslationFromVector(
            DirectX::XMVectorScale(m_vRight, m_fSpeed));

        Update();
    }
    //void Camera::Move_Up()
    //{
    //    DirectX::XMMatrixTranslation(0, 0, Real_Speed);
    //}
    void Camera::Move_World_Z()
    {
        DirectX::XMVECTOR z = DirectX::XMVectorSet(0, 0, 0.1, 0);
        m_vPos = DirectX::XMVectorAdd(m_vPos, z);
      //  DirectX::XMMATRIX move = DirectX::XMMatrixSet(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, Real_Speed, 0);
      //  m_Matrix_World += move;
        Update();
    }
    void Camera::Move_World_Y()
    {
        DirectX::XMVECTOR z = DirectX::XMVectorSet(0, 0.1, 0, 0);
        m_vPos = DirectX::XMVectorAdd(m_vPos, z);
       // DirectX::XMMATRIX move = DirectX::XMMatrixSet(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, Real_Speed, 0, 0);
       // m_Matrix_World += move;
        Update();
    }
    void Camera::Move_World_X()
    {
        DirectX::XMVECTOR z = DirectX::XMVectorSet(0.1, 0, 0, 0);
        m_vPos = DirectX::XMVectorAdd(m_vPos, z);
       // DirectX::XMMATRIX move = DirectX::XMMatrixSet(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, Real_Speed, 0, 0, 0);
       // m_Matrix_World += move;
        Update();
    }
    void Camera::Move_World_Rev_Z()
    {
        DirectX::XMVECTOR z = DirectX::XMVectorSet(0, 0, -0.1, 0);
        m_vPos = DirectX::XMVectorAdd(m_vPos, z);
       // DirectX::XMMATRIX move = DirectX::XMMatrixSet(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -Real_Speed, 0);
       // m_Matrix_World += move;
        Update();
    }
    void Camera::Move_World_Rev_Y()
    {
        DirectX::XMVECTOR z = DirectX::XMVectorSet(0, -0.1, 0, 0);
        m_vPos = DirectX::XMVectorAdd(m_vPos, z);
        // DirectX::XMMATRIX move = DirectX::XMMatrixSet(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, Real_Speed, 0, 0);
        // m_Matrix_World += move;
        Update();
    }
    void Camera::Move_World_Rev_X()
    {
        DirectX::XMVECTOR z = DirectX::XMVectorSet(-0.1, 0, 0, 0);
        m_vPos = DirectX::XMVectorAdd(m_vPos, z);
        Update();
    }
    bool Camera::Init()
    {
        m_hDX.Create_Const_Buffer_Self(nullptr,1,sizeof(VS_CB));
        Set_World(0, 0, 0);
        Set_View(m_vPos, m_vLook_Target_Pos, m_vUp);
        Set_Projection(1, 3000, DirectX::XM_PI / 4, ((float)g_rtClient.right / g_rtClient.bottom));
        return true;
    }

    bool Camera::Frame()
    {
        Real_Speed = m_fSpeed * g_fSecondPerFrame;
        Slerp_Speed = g_fSecondPerFrame;

        Update();
        //조작 - > lerf_frame -> update
        return true;
    }

    void Camera::Set_Min_Max_Radian(float min, float max)
    {
        m_fMin_Radian = min;
        m_fMax_Radian = max;
    }

    bool Camera::Set_Camera()
    {
        return true;
    }
    Camera::Camera()
    {
        m_Matrix_World = DirectX::XMMatrixIdentity();
        m_Matrix_View = DirectX::XMMatrixIdentity();
        m_Matrix_Projection = DirectX::XMMatrixIdentity();
        
        m_vPos = DirectX::XMVectorSet(0, -10.0f, -10.0f, 0);
        m_vLook_Target_Pos = DirectX::XMVectorSet(0, 0, 0, 0);
        m_vUp = DirectX::XMVectorSet(0, 1.0f, 0, 0);




    }


    Camera::~Camera()
    {
    }
}
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
        //m_Matrix_World = DirectX::XMMatrixIdentity();

        m_vRight=DirectX::XMVector3Normalize(m_vRight);
        m_vUp=DirectX::XMVector3Normalize(m_vUp);
        m_vLook=DirectX::XMVector3Normalize(m_vLook);
        
        m_cb.matProj = DirectX::XMMatrixTranspose(m_Matrix_Projection);
        m_cb.matView = DirectX::XMMatrixTranspose(m_Matrix_View);
        m_cb.matWorld = DirectX::XMMatrixTranspose(m_Matrix_World);
        m_hDX.Set_Const_Buffer(m_hDX.m_cConst_Buffer.Get(), &m_cb, 0);
        
        m_Matrix_View = Set_View(m_vPos, m_vLook_Target_Pos, m_vUp);
    }
  
    void Camera::Rotation_By_Arc_Ball()
    {
        DirectX::XMVECTOR scale;
        DirectX::XMVECTOR qrot;
        DirectX::XMVECTOR trans;
        DirectX::XMMatrixDecompose(&scale, &qrot, &trans, m_Matrix_View);

        DirectX::XMVECTOR qview;
        qview =DirectX::XMQuaternionMultiply(qrot, m_Arc_Ball.Get_Quaternion());
        //m_Matrix_View = DirectX::XMMatrixAffineTransformation(scale, m_vPos, qview, trans);
        m_Matrix_View = DirectX::XMMatrixRotationQuaternion(qview);
        DirectX::XMFLOAT4X4 f4;
        
        DirectX::XMStoreFloat4x4(&f4, m_Matrix_View);
        DirectX::XMFLOAT3 pos;
        DirectX::XMStoreFloat3(&pos, m_vPos);
        f4._41 = pos.x;
        f4._42 = pos.y;
        f4._43 = pos.z;
        f4._44 = 1.0f;

        m_Matrix_View = DirectX::XMLoadFloat4x4(&f4);

        
    }

  
    //DirectX::XMMATRIX Camera::SetViewMatrix(DirectX::XMVECTOR vPos, DirectX::XMVECTOR vTarget, DirectX::XMVECTOR vUp)
    //{
    //    D3DXMatrixLookAtLH(&m_matView, &m_vCameraPos, &m_vTargetPos, &vUp);

    //    D3DXQUATERNION qRotation;
    //    DirectX::XMVECTOR vTrans, vScale, vAxis;
    //    DirectX::XMMATRIX mInvView;
    //    D3DXQUATERNION q;
    //    float fAngle;
    //    DirectX::XMMatrixDecompose()
    //    if (D3DXMatrixDecompose(&vScale, &qRotation, &vTrans, &m_matView)))
    //    {
    //        D3DXQuaternionNormalize(&qRotation, &qRotation);
    //        D3DXQuaternionToAxisAngle(&qRotation, &vAxis, &fAngle);
    //        // 반드시 정규화 해야 한다.
    //        D3DXVec3Normalize(&vAxis, &vAxis);

    //        q.x = sin(fAngle / 2) * vAxis.x;
    //        q.y = sin(fAngle / 2) * vAxis.y;
    //        q.z = sin(fAngle / 2) * vAxis.z;
    //        q.w = cos(fAngle / 2);
    //    }
    //    D3DXMatrixInverse(&mInvView, NULL, &m_matView);
    //    D3DXVECTOR3* pZBasis = (D3DXVECTOR3*)&mInvView._31;

    //    m_fCameraYawAngle = atan2f(pZBasis->x, pZBasis->z);
    //    float fLen = sqrtf(pZBasis->z * pZBasis->z + pZBasis->x * pZBasis->x);
    //    m_fCameraPitchAngle = -atan2f(pZBasis->y, fLen);

    //    return 	UpdateVector();
    //}
    void Camera::Lerp_Frame(float Slerp_Speed)
    {
        if (m_uCamera_Type == Non_Target)
        {
           
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
    }
    void Camera::Move_World_Y()
    {
        DirectX::XMVECTOR z = DirectX::XMVectorSet(0, 0.1, 0, 0);
        m_vPos = DirectX::XMVectorAdd(m_vPos, z);
       // DirectX::XMMATRIX move = DirectX::XMMatrixSet(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, Real_Speed, 0, 0);
       // m_Matrix_World += move;
    }
    void Camera::Move_World_X()
    {
        DirectX::XMVECTOR z = DirectX::XMVectorSet(0.1, 0, 0, 0);
        m_vPos = DirectX::XMVectorAdd(m_vPos, z);
       // DirectX::XMMATRIX move = DirectX::XMMatrixSet(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, Real_Speed, 0, 0, 0);
       // m_Matrix_World += move;
    }
    void Camera::Move_World_Rev_Z()
    {
        DirectX::XMVECTOR z = DirectX::XMVectorSet(0, 0, -0.1, 0);
        m_vPos = DirectX::XMVectorAdd(m_vPos, z);
       // DirectX::XMMATRIX move = DirectX::XMMatrixSet(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -Real_Speed, 0);
       // m_Matrix_World += move;
    }
    void Camera::Move_World_Rev_Y()
    {
        DirectX::XMVECTOR z = DirectX::XMVectorSet(0, -0.1, 0, 0);
        m_vPos = DirectX::XMVectorAdd(m_vPos, z);
        // DirectX::XMMATRIX move = DirectX::XMMatrixSet(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, Real_Speed, 0, 0);
        // m_Matrix_World += move;
    }
    void Camera::Move_World_Rev_X()
    {
        DirectX::XMVECTOR z = DirectX::XMVectorSet(-0.1, 0, 0, 0);
        m_vPos = DirectX::XMVectorAdd(m_vPos, z);
    }
    bool Camera::Init()
    {
        m_hDX.Create_Const_Buffer_Self(nullptr,1,sizeof(VS_CB));
        Set_World(0, 0, 0);
        Set_View(m_vPos, m_vLook_Target_Pos, m_vUp);
        Set_Projection(1, 3000, DirectX::XM_PI / 4, ((float)g_rtClient.right / g_rtClient.bottom));
        m_Arc_Ball.Init();
        
        return true;
    }

    bool Camera::Frame()
    {
        
        Real_Speed = m_fSpeed * g_fSecondPerFrame;
        Slerp_Speed = g_fSecondPerFrame;
        m_vNow_Angles.x = m_Arc_Ball.m_vAngle.x;
        m_vNow_Angles.y = m_Arc_Ball.m_vAngle.y;
        m_vNow_Angles.z = m_Arc_Ball.m_vAngle.z;

        DirectX::XMMATRIX rotation;
        DirectX::XMVECTOR qrotation = DirectX::XMQuaternionRotationRollPitchYaw(DirectX::XMConvertToRadians(m_vNow_Angles.x), DirectX::XMConvertToRadians(m_vNow_Angles.y), DirectX::XMConvertToRadians(m_vNow_Angles.z));
       
        rotation = DirectX::XMMatrixRotationQuaternion(qrotation);       // Rotation_By_Arc_Ball();
        DirectX::XMFLOAT4X4 temp;
        DirectX::XMStoreFloat4x4(&temp, rotation);
        DirectX::XMFLOAT3 pos;
        DirectX::XMStoreFloat3(&pos, m_vPos);
        temp._41 = pos.x;
        temp._42 = pos.y;
        temp._43 = pos.z;
        m_Matrix_View = DirectX::XMMatrixInverse(NULL, DirectX::XMLoadFloat4x4(&temp));
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
    void Camera::Rotation()
    {
        return;
    }

    Camera::~Camera()
    {
    }


    


    void Debug_Camera::Move_Look()
    {
        /* m_Matrix_View += DirectX::XMMatrixTranslationFromVector(
             DirectX::XMVectorScale(m_vLook, Real_Speed));*/
        m_vPos = DirectX::XMVectorAdd(m_vPos, DirectX::XMVectorScale(m_vLook, Real_Speed));
    }
    void Debug_Camera::Move_Back()
    {
        /* m_Matrix_View += DirectX::XMMatrixTranslationFromVector(wzx
             DirectX::XMVectorScale(m_vLook, -Real_Speed));*/
        m_vPos = DirectX::XMVectorSubtract(m_vPos, DirectX::XMVectorScale(m_vLook, Real_Speed));

    }
    void Debug_Camera::Move_Left()
    {
        //m_Matrix_View += DirectX::XMMatrixTranslationFromVector(
        //    DirectX::XMVectorScale(m_vRight, -Real_Speed));
        m_vPos = DirectX::XMVectorAdd(m_vPos, DirectX::XMVectorScale(m_vRight, -Real_Speed));



    }
    void Debug_Camera::Move_Right()
    {
        /*  m_Matrix_View += DirectX::XMMatrixTranslationFromVector(
              DirectX::XMVectorScale(m_vRight, Real_Speed));*/
        m_vPos = DirectX::XMVectorAdd(m_vPos, DirectX::XMVectorScale(m_vRight, Real_Speed));


    }

    void Debug_Camera::Rotation()
    {
        DirectX::XMMATRIX rot = m_Arc_Ball.Get_Rotation_Matrix();
        rot = DirectX::XMMatrixInverse(NULL, rot);
        if (m_Arc_Ball.m_bDrag)
        {

        }
        m_Arc_Ball.Get_Quaternion();


        DirectX::XMVECTOR world_look, world_up;
        DirectX::XMVECTOR local_look = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
        DirectX::XMVECTOR local_up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        world_look = DirectX::XMVector3TransformCoord(local_look, rot);
        world_up = DirectX::XMVector3TransformCoord(local_up, rot);

        DirectX::XMMATRIX mInvView;
        mInvView = DirectX::XMMatrixInverse(NULL, m_Matrix_View);
        
        DirectX::XMMATRIX mModelLastRotInv;
        mModelLastRotInv = DirectX::XMMatrixInverse(NULL, m_mModelLastRot);

        DirectX::XMMATRIX mModelRot;
        mModelRot = m_Arc_Ball.Get_Rotation_Matrix();
        m_mModelRot = m_Matrix_View * mModelLastRotInv*mModelRot*mInvView;

        m_mModelLastRot = mModelRot;
        m_lastRot = rot;
        DirectX::XMFLOAT4X4 temp;
        DirectX::XMFLOAT4 vtargetpos;
        DirectX::XMStoreFloat4x4(&temp, m_mModelRot);
        DirectX::XMStoreFloat4(&vtargetpos, m_vLook_Target_Pos);
        temp._41 = vtargetpos.x;
        temp._42 = vtargetpos.y;
        temp._43 = vtargetpos.z;
        m_mModelRot = DirectX::XMLoadFloat4x4(&temp);

        m_vPos = DirectX::XMVectorSubtract(m_vLook_Target_Pos, DirectX::XMVectorScale(local_look, 10));
        m_vLerpUpVector = DirectX::XMVectorLerp(world_up, local_up,1);

        m_vUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        rot = DirectX::XMMatrixLookAtLH(m_vPos, m_vLook_Target_Pos, m_vUp);
        //DirectX::XMFLOAT4X4 temp;
        //DirectX::XMStoreFloat4x4(&temp, rot);
        //DirectX::XMFLOAT3 pos;
        //DirectX::XMStoreFloat3(&pos, m_vPos);
        //temp._41 = pos.x;
        //temp._42 = pos.y;
        //temp._43 = pos.z;
        //m_Matrix_View = DirectX::XMLoadFloat4x4(&temp);

       ////////////////////////////////////////////////////////////////



    }
    
    void Debug_Camera::Non_Target_Camera_Rotation(float yaw, float pitch, float roll)
    {
      /*  m_vTarget_Angles.y += DirectX::XMConvertToRadians(yaw);
        m_vTarget_Angles.x += DirectX::XMConvertToRadians(pitch);
        m_vTarget_Angles.z += DirectX::XMConvertToRadians(roll);

        Lerp_Frame();*/
    }

    void Debug_Camera::Rotation_No_Lerp(float pitch, float yaw, float roll)
    {
        /*m_vTarget_Angles.y += yaw;
        m_vTarget_Angles.x += pitch;
        m_vTarget_Angles.z += roll;
        m_Matrix_View = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
        m_Matrix_View = DirectX::XMMatrixInverse(NULL, m_Matrix_View);*/
    }
    bool Debug_Camera::Init()
    {
        return true;
    }
    bool Debug_Camera::Frame()
    {

        Real_Speed = m_fSpeed * g_fSecondPerFrame;
        Slerp_Speed = g_fSecondPerFrame;
        //Rotation_YPR();
        Update();
        return true;
    }
    DirectX::XMMATRIX Debug_Camera::Set_View(DirectX::XMVECTOR pos, DirectX::XMVECTOR target_pos, DirectX::XMVECTOR up)
    {

        // Propogate changes to the member arcball
        DirectX::XMVECTOR quat;
        DirectX::XMMatrixLookAtLH(pos, target_pos, up);
        quat = DirectX::XMQuaternionRotationMatrix(m_Matrix_View);
        m_Arc_Ball.m_qNow = quat;

        // Set the radius according to the distance
        DirectX::XMVECTOR vEyeToPoint;
        vEyeToPoint = DirectX::XMVectorSubtract(target_pos, pos);
        return m_Matrix_View;
    }

    void Debug_Camera::Rotation_YPR()
    {
        DirectX::XMFLOAT2 temp1 = m_Arc_Ball.xy();
        m_vNow_Angles.x += temp1.x*0.1f;
        m_vNow_Angles.y += temp1.y*0.1f;
        DirectX::XMMATRIX temp =DirectX::XMMatrixRotationRollPitchYaw(m_vNow_Angles.x, m_vNow_Angles.y, m_vNow_Angles.z);
        DirectX::XMFLOAT4X4 f44;
        DirectX::XMFLOAT3 pos;
        DirectX::XMStoreFloat4x4(&f44, temp);
        DirectX::XMStoreFloat3(&pos, m_vPos);
        f44._41 = pos.x;
        f44._42 = pos.y;
        f44._43 = pos.z;
        m_Matrix_View = DirectX::XMLoadFloat4x4(&f44);


    }


    Debug_Camera::Debug_Camera()
    {
    }

    Debug_Camera::~Debug_Camera()
    {
    }
}
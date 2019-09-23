#include "TModelViewCamera.h"
#include "CAInput.h"
// 추가
namespace DX
{
    D3DXMATRIX TModelViewCamera::SetViewMatrix(D3DXVECTOR3 vPos, D3DXVECTOR3 vTarget, D3DXVECTOR3 vUp)
    {
        m_vDefaultEye = m_vCameraPos = vPos;
        m_vDefaultLookAt = m_vTargetPos = vTarget;

        // Propogate changes to the member arcball
        D3DXQUATERNION quat;

        D3DXMatrixLookAtLH(&m_matView, &vPos, &vTarget, &vUp);
        D3DXQuaternionRotationMatrix(&quat, &m_matView);
        m_ViewArcBall.SetQuatNow(quat);

        // Set the radius according to the distance
        D3DXVECTOR3 vEyeToPoint;
        D3DXVec3Subtract(&vEyeToPoint, &vTarget, &vPos);
        SetRadius(D3DXVec3Length(&vEyeToPoint));
        return UpdateVector();
    }

    D3DXMATRIX TModelViewCamera::Update()
    {
        if (I_Input.KeyCheck('W') == KEY_HOLD) 	MoveLook( 2 * m_fSpeed);
        if (I_Input.KeyCheck('S') == KEY_HOLD)		MoveLook(- 2.0f* m_fSpeed);
        if (I_Input.KeyCheck('D') == KEY_HOLD)		MoveSide( 2.0f* m_fSpeed);
        if (I_Input.KeyCheck('A') == KEY_HOLD)		MoveSide(- 2.0f* m_fSpeed);
        if (I_Input.KeyCheck('R') == KEY_HOLD)		MoveUp( 2.0f* m_fSpeed);
        if (I_Input.KeyCheck('F') == KEY_HOLD)		MoveUp(- 2.0f* m_fSpeed);

        // Change the radius from the camera to the model based on wheel scrolling
        if (m_nMouseWheelDelta && m_nZoomButtonMask == MOUSE_WHEEL)
            m_fRadius += m_nMouseWheelDelta * m_fRadius * 0.1f / 120.0f;
        m_fRadius = __min(m_fMaxRadius, m_fRadius);
        m_fRadius = __max(m_fMinRadius, m_fRadius);
        m_nMouseWheelDelta = 0;

        //// Get the inverse of the arcball's rotation matrix
        D3DXMATRIX mCameraRot;
        D3DXMatrixInverse(&mCameraRot, NULL, m_ViewArcBall.GetRotationMatrix());

        //// Transform vectors based on camera's rotation matrix
        D3DXVECTOR3 vWorldUp, vWorldAhead;
        D3DXVECTOR3 vLocalUp = D3DXVECTOR3(0, 1, 0);
        D3DXVECTOR3 vLocalAhead = D3DXVECTOR3(0, 0, 1);
        D3DXVec3TransformCoord(&vWorldUp, &vLocalUp, &mCameraRot);
        D3DXVec3TransformCoord(&vWorldAhead, &vLocalAhead, &mCameraRot);

        // Update the eye point based on a radius away from the lookAt position
        m_vCameraPos = m_vTargetPos - vWorldAhead * m_fRadius;

        // Update the view matrix
        D3DXMatrixLookAtLH(&m_matView, &m_vCameraPos, &m_vTargetPos, &vWorldUp);

        D3DXMATRIX mInvView;
        D3DXMatrixInverse(&mInvView, NULL, &m_matView);
        mInvView._41 = mInvView._42 = mInvView._43 = 0;

        D3DXMATRIX mModelLastRotInv;
        D3DXMatrixInverse(&mModelLastRotInv, NULL, &m_mModelLastRot);

        D3DXMATRIX mModelRot;
        mModelRot = *m_WorldArcBall.GetRotationMatrix();
        // 뷰 공간에서 준 회전, (월드에서의 회전 준것이 아니다. )
        // 누적 : m_mModelRot, mModelLastRotInv, mModelRot
        // m_mModelRot은 카메라 좌표계에서 지정한 회전행렬이다.
        m_mModelRot = m_mModelRot * m_matView * mModelLastRotInv * mModelRot * mInvView;

        m_mCameraRotLast = mCameraRot;
        m_mModelLastRot = mModelRot;

        // Translate the rotation matrix to the same position as the lookAt position
        m_mModelRot._41 = m_vTargetPos.x;
        m_mModelRot._42 = m_vTargetPos.y;
        m_mModelRot._43 = m_vTargetPos.z;

        // Translate world matrix so its at the center of the model
        D3DXMATRIX mTrans;
        D3DXMatrixTranslation(&mTrans, -m_vModelCenter.x, -m_vModelCenter.y, -m_vModelCenter.z);
        m_matWorld = mTrans * m_mModelRot;

        return UpdateVector();
    }
    void TModelViewCamera::MoveLook(float fValue)
    {
        m_vTargetPos += m_vLookVector * fValue;
    }
    void TModelViewCamera::MoveSide(float fValue)
    {
        m_vTargetPos += m_vRightVector * fValue;
    }
    void TModelViewCamera::MoveUp(float fValue)
    {
        m_vTargetPos += m_vUpVector * fValue;
    }


    TModelViewCamera::TModelViewCamera()
    {
        m_fRadius = 5.0f;
        m_fDefaultRadius = 5.0f;
        m_fMinRadius = 1.0f;
        m_fMaxRadius = FLT_MAX;

        m_vModelCenter = D3DXVECTOR3(0, 0, 0);

        m_nRotateModelButtonMask = MOUSE_LEFT_BUTTON;
        m_nZoomButtonMask = MOUSE_WHEEL;
        m_nRotateCameraButtonMask = MOUSE_RIGHT_BUTTON;
    }
    TModelViewCamera::~TModelViewCamera()
    {
    }

}
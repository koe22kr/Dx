#include "TBackViewCamera.h"
#include "CAInput.h"
// �߰�
namespace DX
{
    D3DXMATRIX TBackViewCamera::SetViewMatrix(D3DXVECTOR3 vPos, D3DXVECTOR3 vTarget, D3DXVECTOR3 vUp)
    {
        m_vDefaultEye = m_vCameraPos = vPos;
        m_vDefaultLookAt = m_vTargetPos = vTarget;

        m_vCameraDestination = m_vCameraPos;

        // Propogate changes to the member arcball
        D3DXQUATERNION quat;
        //D3DXMATRIXA16 mRotation;

        D3DXMatrixLookAtLH(&m_matView, &vPos, &vTarget, &vUp);
        D3DXQuaternionRotationMatrix(&quat, &m_matView);
        m_ViewArcBall.SetQuatNow(quat);

        // Set the radius according to the distance
        D3DXVECTOR3 vEyeToPoint;
        D3DXVec3Subtract(&vEyeToPoint, &vTarget, &vPos);
        SetRadius(D3DXVec3Length(&vEyeToPoint));
        return UpdateVector();
    }

    D3DXMATRIX TBackViewCamera::Update()
    {
        
        if (I_Input.KeyCheck('W') == KEY_HOLD) 	MoveLook( 2.0f*m_fSpeed);
        if (I_Input.KeyCheck('S') == KEY_HOLD)		MoveLook(- 2.0f*m_fSpeed);
        if (I_Input.KeyCheck('D') == KEY_HOLD)		MoveSide(  2.0f*m_fSpeed);
        if (I_Input.KeyCheck('A') == KEY_HOLD)		MoveSide(- 2.0f*m_fSpeed);
        if (I_Input.KeyCheck('Q') == KEY_HOLD)		MoveUp(2.0f*m_fSpeed);
        if (I_Input.KeyCheck('E') == KEY_HOLD)		MoveUp(- 2.0f*m_fSpeed);

        // Change the radius from the camera to the model based on wheel scrolling
        if (m_nMouseWheelDelta && m_nZoomButtonMask == MOUSE_WHEEL)
        {
            m_fPrevRadius = m_fRadius;
            m_fRadius += m_nMouseWheelDelta * m_fRadius * 0.1f / 120.0f;
        }
        m_fRadius = __min(m_fMaxRadius, m_fRadius);
        m_fRadius = __max(m_fMinRadius, m_fRadius);


        //// Get the inverse of the arcball's rotation matrix
        D3DXMATRIX mCameraRot;
        D3DXMatrixInverse(&mCameraRot, NULL, m_ViewArcBall.GetRotationMatrix());
        
        //// Transform vectors based on camera's rotation matrix
        D3DXVECTOR3 vWorldUp, vWorldAhead;
        D3DXVECTOR3 vLocalUp = D3DXVECTOR3(0, 1, 0);
        D3DXVECTOR3 vLocalAhead = D3DXVECTOR3(0, 0, 1);
        D3DXVec3TransformCoord(&vWorldUp, &vLocalUp, &mCameraRot);
        D3DXVec3Normalize(&vWorldUp, &vWorldUp);
        D3DXVec3TransformCoord(&vWorldAhead, &vLocalAhead, &mCameraRot);


        // ī�޶� ȸ���� ����Ǹ� ��ǥ ��ġ�� �����Ѵ�.
        if (m_ViewArcBall.m_bDrag)
        {
            m_vCameraDestination = m_vCameraPos = m_vTargetPos - vWorldAhead * m_fRadius;
        }
        if (I_Input.KeyCheck('W')==KEY_HOLD|| I_Input.KeyCheck('S') == KEY_HOLD || I_Input.KeyCheck('A') == KEY_HOLD || I_Input.KeyCheck('D') == KEY_HOLD || I_Input.KeyCheck('R') == KEY_HOLD || I_Input.KeyCheck('F') == KEY_HOLD)
        {
            m_vCameraDestination = m_vCameraPos = m_vTargetPos - vWorldAhead * m_fRadius;

        }
        //// ī�޶��� �ޱ��� ���������� �����Ѵ�.
        //D3DXVec3Lerp(&m_vLerpUpVector, &vWorldUp, &vLocalUp, 1);

        // ���� �̵��������� ����Ͽ� ��ǥ��ġ�� �����Ѵ�.
        if (m_nMouseWheelDelta)
        {
            D3DXVECTOR3 vTmp;
            D3DXVec3Normalize(&vTmp, &(m_vCameraPos - m_vTargetPos));
            m_vCameraDestination += (vTmp * (m_fRadius - m_fPrevRadius));
        }

        //// õõ�� ������� ī�޶�.	///
        //D3DXVec3Lerp(&m_vCameraPos,
        //    &m_vCameraPos,
        //    &m_vCameraDestination, 1);

        /*if (!m_ViewArcBall.m_bDrag)
        {
            SetViewMatrix(m_vCameraPos, m_vTargetPos, vWorldUp);
        }*/


        //  �¿� �յڸ� �����δ�.
        //else
        //{/	
        //	D3DXMatrixLookAtLH(&m_matView, &m_vCameraPos, &m_vTargetPos, &vWorldUp);
        //}
        D3DXMatrixLookAtLH(&m_matView, &m_vCameraPos, &m_vTargetPos, &vWorldUp);

        D3DXMATRIX mInvView;
        D3DXMatrixInverse(&mInvView, NULL, &m_matView);
        mInvView._41 = mInvView._42 = mInvView._43 = 0;

        D3DXMATRIX mModelLastRotInv;
        D3DXMatrixInverse(&mModelLastRotInv, NULL, &m_mModelLastRot);

        //�� �������� arcballȸ���� ���氪�� �����Ѵ�.
        D3DXMATRIX mModelRot;
        mModelRot = *m_WorldArcBall.GetRotationMatrix();
        //m_mModelRot *= m_matView * mModelLastRotInv * mModelRot * mInvView;
        m_mModelRot = m_mModelRot * m_matView * mModelLastRotInv * mModelRot * mInvView;

        m_mCameraRotLast = mCameraRot;
        m_mModelLastRot = mModelRot;

        // ȸ�� ����� lookAt ��ġ�� ������ ��ġ�� ��ȯ�Ѵ�.
        /*m_mModelRot._41 = m_vTargetPos.x;
        m_mModelRot._42 = m_vTargetPos.y;
        m_mModelRot._43 = m_vTargetPos.z;*/
        m_mModelRot._41 = m_vCameraPos.x;
        m_mModelRot._42 = m_vCameraPos.y;
        m_mModelRot._43 = m_vCameraPos.z;
        m_mModelRot._44 = 1.0f;
        // ���� �߽ɿ��� ������� ��ȯ�Ѵ�.
        D3DXMATRIX mTrans;
        D3DXMatrixTranslation(&mTrans, -m_vModelCenter.x, -m_vModelCenter.y, -m_vModelCenter.z);
        m_matWorld = mTrans * m_mModelRot;

        m_vObjectVector[0].x = m_matWorld._11;
        m_vObjectVector[0].y = m_matWorld._21;
        m_vObjectVector[0].z = m_matWorld._31;
        m_vObjectVector[1].x = m_matWorld._12;
        m_vObjectVector[1].y = m_matWorld._22;
        m_vObjectVector[1].z = m_matWorld._32;
        m_vObjectVector[2].x = m_matWorld._13;
        m_vObjectVector[2].y = m_matWorld._23;
        m_vObjectVector[2].z = m_matWorld._33;

        // ���콺 �ٰ� �ʱ�ȭ
        m_nMouseWheelDelta = 0;
        m_fPrevRadius = m_fRadius;
        return UpdateVector();
    }
    void TBackViewCamera::MoveSide(float fValue)
    {
        m_vTargetPos += m_vRightVector * fValue*2 * g_fSecondPerFrame;
        MovementTarget(fValue, m_vObjectVector[0]);

    }
    void TBackViewCamera::MoveUp(float fValue)
    {
        m_vTargetPos += m_vUpVector * fValue* 2 * g_fSecondPerFrame;
        MovementTarget(fValue, m_vObjectVector[1]);
    }
    void TBackViewCamera::MoveLook(float fValue)
    {
        m_vTargetPos += m_vLookVector * fValue*2 * g_fSecondPerFrame;
        MovementTarget(fValue, m_vObjectVector[2]);

    }
    //�̵������� + or - �� �Ǵ��Ͽ� �̵������� ������ �����Ѵ�.
    float TBackViewCamera::GetDecideDirection(float fValue)
    {
        float fDecideDirection = -m_vOffsetDistance.z;
        if (fValue < 0) fDecideDirection = m_vOffsetDistance.z;
        return fDecideDirection;
    }
    void TBackViewCamera::MovementTarget(float fValue, D3DXVECTOR3 vDirection)
    {
      //  m_vTargetPos += vDirection * fValue*g_fSecondPerFrame;
        m_vCameraDestination = m_vTargetPos + (vDirection * GetDecideDirection(fValue));
        m_vCameraDestination.y += m_vTargetPos.y + m_vOffsetDistance.y;
        SetMatrix(&m_matWorld, &m_matView, &m_matProj);
    }
    void TBackViewCamera::SetOffsetDistance(float fDistX, float fDistY, float fDistZ)
    {
        m_vOffsetDistance.x = fDistX;
        m_vOffsetDistance.y = fDistY;
        m_vOffsetDistance.z = fDistZ;
    }


    TBackViewCamera::TBackViewCamera()
    {
        m_fRadius = 5.0f;
        m_fDefaultRadius = 5.0f;
        m_fMinRadius = 1.0f;
        m_fMaxRadius = FLT_MAX;

        m_vLerpUpVector = D3DXVECTOR3(0, 1, 0);
        SetOffsetDistance(0.0f, 5.0f, 15.0f);

        m_vModelCenter = D3DXVECTOR3(0, 0, 0);
        m_nRotateModelButtonMask = MOUSE_LEFT_BUTTON;
        m_nZoomButtonMask = MOUSE_WHEEL;
        m_nRotateCameraButtonMask = MOUSE_RIGHT_BUTTON;
    }
    TBackViewCamera::~TBackViewCamera()
    {
    }

}
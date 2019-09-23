#pragma once
#include "TCamera.h"
namespace DX
{
    class TBackViewCamera : public TCamera
    {
    public:
        D3DXVECTOR3			m_vOffsetDistance;		// 오브젝트의 위치에서 각 방향으로 떨어져 있는 거리 
        D3DXVECTOR3			m_vLerpUpVector;
        //--------------------------------------------------------------------------------------
        // 카메라 위치 정보 
        //--------------------------------------------------------------------------------------
        void				MoveLook(float fValue);
        void				MoveSide(float fValue);
        void				MoveUp(float fValue);
        //--------------------------------------------------------------------------------------
        //이동방향의 + or - 를 판단하여 이동벡터의 방향을 결정한다.
        //--------------------------------------------------------------------------------------
        float				GetDecideDirection(float fValue);
        //--------------------------------------------------------------------------------------
        //오브젝트(타켓위치)의 방향벡터를 기준으로 이동.
        //--------------------------------------------------------------------------------------
        void				MovementTarget(float fValue, D3DXVECTOR3 vDirection);
        //--------------------------------------------------------------------------------------
        //오브젝트(타켓위치)위치에서 떨어져야 할 거리 적용
        //--------------------------------------------------------------------------------------
        void				SetOffsetDistance(float fDistX, float fDistY, float fDistZ);
        //--------------------------------------------------------------------------------------
        // 오일러 각에 따른 뷰 행렬 계산 
        //--------------------------------------------------------------------------------------
        virtual D3DXMATRIX			Update();

        //--------------------------------------------------------------------------------------
        // 카메라 보간이동의 목표지점.
        //--------------------------------------------------------------------------------------
        // 추가
        D3DXVECTOR3			m_vCameraDestination;
        // 모델의 월드 변환 행렬의 방향벡터
        D3DXVECTOR3			m_vObjectVector[3];
        float				m_fPrevRadius;

    public:

        //--------------------------------------------------------------------------------------
        // 뷰 행렬 계산  
        //--------------------------------------------------------------------------------------
        D3DXMATRIX			SetViewMatrix(D3DXVECTOR3 vPos, D3DXVECTOR3 vTarget, D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f));

    public:
        TBackViewCamera(void);
        virtual ~TBackViewCamera(void);
    };
}
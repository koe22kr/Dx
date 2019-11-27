#pragma once
#include "Quad_Tree.h"

struct Ray
{
    D3DXVECTOR3 vOrigin;
    D3DXVECTOR3 vDirection;
};

class Pick
{
public:
    D3DXMATRIX m_matWorld;
    D3DXMATRIX m_matView;
    D3DXMATRIX m_matProj;
    Ray      m_Ray;
    D3DXVECTOR3 m_vIntersection;
public:
    void  Update();
    void SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
    bool  IntersectTriangle(D3DXVECTOR3& vOrig, D3DXVECTOR3& vDir, 
                            D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2, float* t, float* u, float* v);
    bool CheckPick(D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2);

    bool ChkOBBToRay(DX::T_BOX* pBox);
    bool ChkAABBToRay(DX::T_BOX* pBox);
public:
    Pick();
    ~Pick();
};


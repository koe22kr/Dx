#include "Pick.h"


bool Pick::ChkAABBToRay(DX::T_BOX* pBox)
{
    Ray* pRay = &m_Ray;
    float t_min = 0;
    float t_max = 999999.0f;
    for (int i = 0; i < 3; i++)
    {
        // 축에 평행할 경우
        if (abs(pRay->vDirection[i]) < 0.0001f)
        {
            if (pRay->vOrigin[i] < pBox->vMin[i] || pRay->vOrigin[i] > pBox->vMax[i])
                return false;
        }
        else
        {
            float denom = 1.0f / pRay->vDirection[i];
            float t1 = (pBox->vMin[i] - pRay->vOrigin[i]) * denom;
            float t2 = (pBox->vMax[i] - pRay->vOrigin[i]) * denom;
            if (t1 > t2)
            {
                swap(t1, t2);
            }
            t_min = max(t_min, t1);
            t_max = min(t_max, t2);
            if (t_min > t_max)
                return false;
        }
    }
    return true;
}
bool Pick::ChkOBBToRay(DX::T_BOX* pBox)
{
    Ray* pRay = &m_Ray;
    float t_min = -999999.0f;
    float t_max = 999999.0f;
    float  f[3], absf[3], s[3], abss[3];

    D3DXVECTOR3 vR = pRay->vOrigin - pBox->vCenter;

    for (int v = 0; v < 3; v++)
    {
        f[v] = D3DXVec3Dot(&pBox->vAxis[v], &pRay->vDirection);
        s[v] = D3DXVec3Dot(&pBox->vAxis[v], &vR);
        absf[v] = fabs(f[v]);
        abss[v] = fabs(s[v]);

        if (abss[v] > pBox->fExtent[v] && s[v] * f[v] >= 0.0f)//방향검사
            return false;

        float t1 = (-s[v] - pBox->fExtent[v]) / f[v];
        float t2 = (-s[v] + pBox->fExtent[v]) / f[v];
        if (t1 > t2)
        {
            swap(t1, t2);
        }
        t_min = max(t_min, t1);
        t_max = min(t_max, t2);
        if (t_min > t_max)
            return false;
    }
    /////////////////삼중적 사용해서 분리축
    float  fCross[3], fRhs;
    D3DXVECTOR3 vDxR;
    D3DXVec3Cross(&vDxR, &pRay->vDirection, &vR);
    // D X pBox->vAxis[0]  분리축
    fCross[0] = fabs(D3DXVec3Dot(&vDxR, &pBox->vAxis[0]));
    float fAxis2 = pBox->fExtent[1] * absf[2];
    float fAxis1 = pBox->fExtent[2] * absf[1];
    fRhs = fAxis2 + fAxis1;
    if (fCross[0] > fRhs)
    {
        return false;
    }
    // D x pBox->vAxis[1]  분리축
    fCross[1] = fabs(D3DXVec3Dot(&vDxR, &pBox->vAxis[1]));
    fRhs = pBox->fExtent[0] * absf[2] + pBox->fExtent[2] * absf[0];
    if (fCross[1] > fRhs)
    {
        return false;
    }
    // D x pBox->vAxis[2]  분리축
    fCross[2] = fabs(D3DXVec3Dot(&vDxR, &pBox->vAxis[2]));
    fRhs = pBox->fExtent[0] * absf[1] + pBox->fExtent[1] * absf[0];
    if (fCross[2] > fRhs)
    {
        return false;
    }
    return true;
}
void Pick::SetMatrix(D3DXMATRIX* matWorld,
    D3DXMATRIX* matView,
    D3DXMATRIX* matProj)
{
    D3DXMatrixIdentity(&m_matWorld);
    if (matWorld != nullptr)
    {
        m_matWorld = *matWorld;
    }
    if (matView != nullptr)m_matView = *matView;
    if (matProj != nullptr)m_matProj = *matProj;

    Update();
}
void  Pick::Update()
{
    POINT ptCursor;
    GetCursorPos(&ptCursor);
    ScreenToClient(g_hWnd, &ptCursor);

    D3DXVECTOR3 v;
    v.x = ((2.0f* ptCursor.x) / g_rtClient.right) - 1;
    v.x = v.x / m_matProj._11;
    v.y = -(((2.0f* ptCursor.y) / g_rtClient.bottom) - 1);
    v.y = v.y / m_matProj._22;
    v.z = 1.0f;

    D3DXMATRIX matInvWV = m_matWorld * m_matView;
    D3DXMatrixInverse(&matInvWV, NULL, &matInvWV);

    m_Ray.vOrigin = D3DXVECTOR3(0, 0, 0);
    m_Ray.vDirection = D3DXVECTOR3(v.x, v.y, v.z);

    D3DXVec3TransformCoord(&m_Ray.vOrigin, &m_Ray.vOrigin, &matInvWV);
    D3DXVec3TransformNormal(&m_Ray.vDirection, &m_Ray.vDirection, &matInvWV);
    D3DXVec3Normalize(&m_Ray.vDirection, &m_Ray.vDirection);
}
bool  Pick::IntersectTriangle(
    D3DXVECTOR3& vOrig, D3DXVECTOR3& vDir,
    D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2,
    float* t, float* u, float* v)
{
    D3DXVECTOR3 edge1 = v1 - v0;
    D3DXVECTOR3 edge2 = v2 - v0;
    D3DXVECTOR3 pvec, tvec, qvec;
    D3DXVec3Cross(&pvec, &vDir, &edge2);
    float det = D3DXVec3Dot(&edge1, &pvec);
    if (det > 0)
    {
        tvec = vOrig - v0;
    }
    else
    {
        tvec = v0 - vOrig;
        det = -det;
    }
    if (det < 0.00001f) return false;
    *u = D3DXVec3Dot(&tvec, &pvec);
    if (*u <0.0f || *u > det)
    {
        return false;
    }

    D3DXVec3Cross(&qvec, &tvec, &edge1);
    *v = D3DXVec3Dot(&vDir, &qvec);
    if (*v <0.0f || *u + *v > det)
    {
        return false;
    }

    *t = D3DXVec3Dot(&edge2, &qvec);
    float fInvDet = 1.0f / det;
    *t *= fInvDet;
    *u *= fInvDet;
    *v *= fInvDet;
    return true;
}
bool Pick::CheckPick(D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2)
{
    float t, u, v;
    if (IntersectTriangle(m_Ray.vOrigin,
        m_Ray.vDirection,
        v0, v1, v2, &t, &u, &v))
    {
        m_vIntersection = m_Ray.vOrigin + m_Ray.vDirection*t;
        return true;
    }
    return false;
}

Pick::Pick()
{
}


Pick::~Pick()
{
}

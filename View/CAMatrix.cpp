#include "CAMatrix.h"




CAMatrix CAMatrix::ObjectLookAt(
    Vector3& Eye,
    Vector3& At,
    Vector3& Up)
{
    CAMatrix mat;
    Vector3 vLook = (At - Eye).Normal();
    Vector3 vRight = (vLook ^ Up).Normal();
    Vector3 vUp = (vRight ^ vLook).Normal();
    mat._11 = vRight.x;
    mat._12 = vRight.y;
    mat._13 = vRight.z;
    mat._21 = vUp.x;
    mat._22 = vUp.y;
    mat._23 = vUp.z;
    mat._31 = vLook.x;
    mat._32 = vLook.y;
    mat._33 = vLook.z;
    return mat;
}

CAMatrix CAMatrix::ViewLookAt(
    Vector3& Eye,
    Vector3& At,
    Vector3& Up)
{
    CAMatrix mat;
    return mat;
}

void CAMatrix::Translation(const Vector3& v)
{
    _41 = v.x;
    _42 = v.y;
    _43 = v.z;
}
void CAMatrix::Scale(const Vector3& v)
{
    _11 = _11 * v.x;
    _21 = _21 * v.x;
    _31 = _31 * v.x;
    
    _12 = _12 * v.y;
    _22 = _22 * v.y;
    _32 = _32 * v.y;

    _13 = _13 * v.z;
    _23 = _23 * v.z;
    _33 = _33 * v.z;
}
void CAMatrix::XRotate(float fRadian)
{
    float fCos = (float)cos(fRadian);
    float fSin = (float)sin(fRadian);
    _22 = fCos;		_23 = fSin;
    _32 = -fSin;	_33 = fCos;
};
void CAMatrix::YRotate(float fRadian)
{
    float fCos = (float)cos(fRadian);
    float fSin = (float)sin(fRadian);
    _11 = fCos;		_13 = -fSin;
    _31 = fSin;	_33 = fCos;
}
void CAMatrix::ZRotate(float fRadian)
{
    float fCos = (float)cos(fRadian);
    float fSin = (float)sin(fRadian);
    _11 = fCos;		_12 = fSin;
    _21 = -fSin;	_22 = fCos;
}
CAMatrix CAMatrix::TRanspose()
{
    CAMatrix mat;
    mat._11 = _11; mat._12 = _21; mat._13 = _31; mat._14 = _41;
    mat._21 = _12; mat._22 = _22; mat._23 = _32; mat._24 = _42;
    mat._31 = _13; mat._32 = _23; mat._33 = _33; mat._34 = _43;
    mat._41 = _14; mat._42 = _24; mat._43 = _34; mat._44 = _44;
    return mat;
}
#pragma once
#include <math.h>


//CADX namespace\\

#define MY_VECTOR_EPSILON (0.001f)
#define MY_PI ((float)3.141592654)
#define DegreeToRadian(degree) (degree*(MY_PI/180.0f))
#define RadianToDegree(radian) (radian*(180/MY_PI))
struct float2
{
    union
    {
        struct { float x; float y; };
        float f[2];
    };
};
struct float3
{
    union
    {
        struct { float x; float y; float z; };
        float f[3];
    };
};
struct float4
{
    union
    {
        struct { float x; float y; float z; float w; };
        float f[4];
    };
};


class Vector2 : public float2
{
public:
    Vector2();
    Vector2(const Vector2& v);
    Vector2(float fx, float fy);
    ~Vector2();
};
class Vector4 : public float4
{
public:
    Vector4();
    Vector4(const Vector4& v);
    Vector4(float fx, float fy, float fz, float fw);
    ~Vector4();
};
class Vector3 : public float3
{
public:
    Vector3 operator + (Vector3 const & v);
    Vector3 operator - (Vector3 const & v);
    Vector3 operator * (float const & fScala);
    Vector3 operator / (float const & fScala);
    float   operator | (Vector3 const &v);
    Vector3 operator ^ (Vector3 const &v);
    bool    operator == (Vector3 const &v);
public:
    float   Length();
    float   LengthSquared();
    Vector3 Normal();
    float   Angle(Vector3& v);
public:
    Vector3();
    Vector3(const Vector3& v);
    Vector3(float fx, float fy, float fz);
    ~Vector3();
};
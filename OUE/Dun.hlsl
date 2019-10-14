Texture2D g_txDiffuse : register(t0);
Texture2D g_txFilter : register(t1);
SamplerState s0 : register(s0);

//////////////////////////////////////////////////////////////////////////////////////////////
cbuffer cb0 : register(b0)
{
    matrix g_matWorld: packoffset(c0);// 상수레지스터
    matrix g_matView : packoffset(c4);
    matrix g_matProj : packoffset(c8);
    float4 g_Color : packoffset(c12);
    float  g_fTime : packoffset(c13.x);
};
///////////////////////////////////////////////////////////////////////////////
cbuffer cb1: register(b1)
{
    matrix				g_matWorldInverse: packoffset(c0);
    float4				g_AmbientMaterial: packoffset(c4);
    float4				g_DiffuseMaterial: packoffset(c5);
    float4				g_cSpecularMaterial: packoffset(c6);
    float4				g_cEmissionMaterial: packoffset(c7);
    float4				g_AmbientLightColor : packoffset(c8);
    float4				g_DiffuseLightColor: packoffset(c9);
    float4				g_cSpecularLightColor: packoffset(c10);
    float3				g_vLightDir : packoffset(c11);
    float			    g_fDamping : packoffset(c11.w);
    float3				g_vLightPos : packoffset(c12);
    float			    g_fRadius : packoffset(c12.w);
    float3				g_vEyeDir : packoffset(c13);
    float			    g_fIntensity : packoffset(c13.w);
    float3				g_vEyePos : packoffset(c14);
    float			    g_fEyeRadius : packoffset(c14.w);
};
////////////////////////////////////////////////////////////////////////////////////////////
struct VS_INPUT
{
    float3 p : POSITION;
    float4 n : NORMAL;
    float4 c : COLOR;
    float2 t : TEXCOORD;
};
struct VS_OUTPUT
{
    float4 p : SV_POSITION;
    float3 n : NORMAL;
    float4 c : COLOR0;
    float2 t : TEXCOORD0;
    float4 v : TEXCOORD1;
};
////////////////////////////////////////////////////////////////////////////////////////////////
float4 Diffuse(float3 vNormal)
{
    float fIntensity = max(0, dot(vNormal, normalize(-g_vLightDir)));
    float4 diffuse = g_AmbientMaterial * g_AmbientLightColor +
        (g_DiffuseMaterial * g_DiffuseLightColor * fIntensity);
    return diffuse;
}
////////////////////////////////////////////////////////////////////////////////////////////////
float4 Specular(float3 vNormal)
{
    // Specular Lighting
    float  fPower = 0.0f;

    // float3 R = reflect(g_vLightDir, vNormal);
    // fPower = pow(saturate(dot(R, -g_vEyeDir)), 30);

    float3 vHalf = normalize(-g_vLightDir + -g_vEyeDir);
    fPower = pow(saturate(dot(vNormal, vHalf)), 50.0f);
    float4 specular = g_cSpecularMaterial * g_cSpecularLightColor * fPower;
    //float4 specular = float4(fPower, fPower, fPower,1.0f);
    return max(0, specular);
}
////////////////////////////////////////////////////////////////////////////////////////////////
VS_OUTPUT VS(VS_INPUT vIn)
{

    VS_OUTPUT vOut = (VS_OUTPUT)0;
    vOut.v = mul(float4(vIn.p, 1.0f), g_matWorld); //vWorld
    vOut.p = mul(vOut.v, g_matView);
    vOut.p = mul(vOut.p, g_matProj);

   // vOut.n = normalize(mul(vIn.n, (float3x3)g_matWorldInverse));
    vOut.t = vIn.t;

    vOut.c.x = dot(vOut.n, normalize(-g_vLightDir));
    vOut.c.y = dot(vOut.n, normalize(-g_vLightDir));// vIn.c * g_MeshColor;
    vOut.c.z = dot(vOut.n, normalize(-g_vLightDir));
    vOut.c.w = 1.0f;
    return vOut;
}


float4 PS(VS_OUTPUT vIn) : SV_Target
{/*
    float fIntensity = min(0, dot(vIn.n, normalize(-g_vLightDir)));
 float4 filter = g_txFilter.Sample(s0 , float2(0.5f, 0.5 + (0.5f*fIntensity)));
 filter = vIn.c*(Diffuse(vIn.n) + Specular(vIn.n))*filter;
return g_txDiffuse.Sample(s0, vIn.t)*filter;*/
    return float4(vIn.c.w,vIn.c.w,vIn.c.w,vIn.c.w);
}
//float temp = min(1,(Diffuse(vIn.n) + Specular(vIn.n)));

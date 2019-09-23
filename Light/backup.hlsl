//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D g_txDiffuse: register (t0);
SamplerState s0: register (s0);
cbuffer cb0: register(b0)
{
    matrix	g_matWorld		: packoffset(c0);
    matrix	g_matView		: packoffset(c4);
    matrix	g_matProj		: packoffset(c8);
    float4  g_MeshColor     : packoffset(c12);
};
//--------------------------------------------------------------------------------------
//Lighting Variables 1�� ���.
//--------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float3 p : POSITION;
    float3 n : NORMAL;
    float4 c : COLOR;
    float2 t : TEXCOORD;
};
struct VS_OUTPUT
{
    float4 p : SV_POSITION;
    float3 n : NORMAL;
    float4 c : COLOR0;
    float2 t : TEXCOORD0;
    float4 d : TEXCOORD1;
};
////--------------------------------------------------------------------------------------
//// Pixel Shader
////--------------------------------------------------------------------------------------
//float4 Diffuse(float3 vNormal)
//{
//    float fIntensity = max(0, dot(vNormal, normalize(-g_vLightDir)));
//    float4 diffuse = g_AmbientMaterial * g_AmbientLightColor +
//        (g_DiffuseMaterial * g_DiffuseLightColor * fIntensity);
//    return diffuse;
//}
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT vIn)
{
    VS_OUTPUT vOut = (VS_OUTPUT)0;
    vOut.p = mul(float4(vIn.p, 1.0f), g_matWorld);
    vOut.p = mul(vOut.p, g_matView);
    vOut.p = mul(vOut.p, g_matProj);

    //  vOut.n = normalize(mul(vIn.n, (float3x3)g_matWorldInverse));

    vOut.t = vIn.t /** 10*/;
    // vOut.c.x = dot(vOut.n, normalize(-g_vLightDir));
    // vOut.c.y = dot(vOut.n, normalize(-g_vLightDir));// vIn.c * g_MeshColor;
    // vOut.c.z = dot(vOut.n, normalize(-g_vLightDir));
    // vOut.c.w = 1.0f;
    return vOut;
}


float4 PS(VS_OUTPUT vIn) : SV_Target
{
    float4 vTexColor = g_txDiffuse.Sample(s0, vIn.t);
    // float4 vFinalColor = vTexColor * Diffuse(vIn.n) * vIn.c;
    // vTexColor.a = 1.0f;
     return vTexColor;
}

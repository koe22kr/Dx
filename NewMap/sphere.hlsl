TextureCube g_txDiffuse : register(t0);
SamplerState s0 : register(s0);

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
    float4 n : NORMAL;
    float4 c : COLOR0;
    float2 t : TEXCOORD0;
    float4 vTexLight :TANGENT;
};

cbuffer cb0 : register(b0)
{
    matrix g_matWorld: packoffset(c0);// 상수레지스터
    matrix g_matView : packoffset(c4);
    matrix g_matProj : packoffset(c8);
    float4 g_Color : packoffset(c12);
    float  g_fTime : packoffset(c13.x);
};
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT pOut = (VS_OUTPUT)0;

    pOut.p = mul(float4(input.p, 1.0f), g_matWorld);// local * g_matWorld;
    pOut.p = mul(pOut.p, g_matView);// world * g_matView;
    pOut.p = mul(pOut.p, g_matProj);// view * g_matWorld;	
    float3x3 tbn;
    pOut.t = input.t;
    pOut.n = input.n;




    //float4 vColor = float4(fDot, fDot, fDot, 1.0f);
    pOut.c = input.c;//vColor;// input.c;

    return pOut;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    float sa = sin(g_fTime);
    float4 color = g_txDiffuse.Sample(s0, -input.n);
    //float3 Normal = normalize(float3(input.n) * 2 - 1);

    return color;
}

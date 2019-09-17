Texture2D g_txDiffuse : register(t0);
SamplerState s0 : register(s0);

cbuffer cb0
{
    matrix	g_mat_World	: packoffset(c0);
    matrix	g_mat_View		: packoffset(c4);
    matrix	g_mat_Proj		: packoffset(c8);
    float4  g_Mesh_Color     : packoffset(c12);
    float4  g_etc           : packoffset(c13);
};

struct VS_INPUT
{
    float3 p : POSITION;
    float3 n : NORMAL;
    float4 c : COLOR;
    float2 t : TEXCOORD;
};
struct VS_OUTPUT
{
    float4 P  : SV_Position;
    float3 n : NORMAL;
    float4 c : COLOR0;
    float2 t : TEXCOORD0;
};



VS_OUTPUT VS(VS_INPUT input)
{

    VS_OUTPUT OP;
    OP.p = mul(float4(input.p, 1.0f), g_mat_World);
    OP.P = mul(OP.p, g_mat_View);
    OP.P = mul(OP.p, g_mat_Proj);
    OP.n = input.n;
    OP.c = input.c;
    OP.t = input.t;

    return OP;
}
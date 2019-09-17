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

struct VS_OUTPUT
{
    float4 P  : SV_Position;
    float3 n : NORMAL;
    float4 c : COLOR0;
    float2 t : TEXCOORD0;
};



//////


float4 PS(VS_OUTPUT input) : SV_TARGET
{
    float4 color = g_txDiffuse.Sample(s0,input.t);
    //float4 color = float4(1, 0, 1, 1);
    return color;
}

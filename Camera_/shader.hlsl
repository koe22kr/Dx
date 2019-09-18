Texture2D g_txDiffuse : register(t0);
Texture2D g_txMask : register(t1);
SamplerState s0 : register(s0);

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
    // world
    pOut.p = mul(float4(input.p, 1.0f), g_matWorld);// local * g_matWorld;
    pOut.p = mul(pOut.p, g_matView);// world * g_matView;
    pOut.p = mul(pOut.p, g_matProj);// view * g_matWorld;	
    pOut.t = input.t;
    pOut.n = input.n;

   /* float3 vLight = float3(0.0f, -1.0f, 0.0f) * -1.0f;
    float fDot = max(0.0f, dot(vLight, input.n));
    float4 vColor = float4(fDot, fDot, fDot, 1.0f);
   */ pOut.c =  input.c;

    return pOut;
}
//VS_OUTPUT VSRotation(VS_INPUT input)
//{
//	VS_OUTPUT pOut = (VS_OUTPUT)0;
//	pOut.p = float4(input.p,1.0f);
//	pOut.p.x = input.p.x * cos(g_fTime) -input.p.y * sin(g_fTime);
//	pOut.p.y = input.p.x * sin(g_fTime) +input.p.y * cos(g_fTime);
//	pOut.p.z = 1.0f;	
//	pOut.t = input.t;
//	return pOut;
//}


float4 PS(VS_OUTPUT input) : SV_TARGET
{
    /*float3 vLight = float3(0.0f, -1.0f, 0.0f) * -1.0f;
    float fDot = max(0.0f, dot(vLight, input.n));
    float4 vColor = float4(fDot, fDot, fDot,1.0f);
    float4 color = vColor * g_txDiffuse.Sample(s0, input.t);*/// *input.c;
    //float4 color = g_txDiffuse.Sample(s0, input.t)*input.c;
    return g_txDiffuse.Sample(s0, input.t);
}
float4 PS_Color(VS_OUTPUT input) : SV_TARGET
{
    float4 color = input.c;
    return color;
}
//
//float4 PSMask(in float4 p : POSITION,
//	in float2 t : TEXCOORD0) : SV_TARGET
//{
//	float4 color = g_txDiffuse.Sample(s0 , t);
//	float4 alpha = g_txMask.Sample(s0, t);
//	if (alpha.r==1.0f && alpha.g == 1.0f && alpha.b)
//		discard;
//	return color;
//}
//float4 PSBlend(in float4 p : POSITION,
//	in float2 t : TEXCOORD0) : SV_TARGET
//{
//	float4 colorA = g_txDiffuse.Sample(s0 , t);
//	float4 colorB = g_txMask.Sample(s0, t);
//
//	float alpha = 1.0f;
//	if (colorB.r == 1.0f && colorB.g == 1.0f && colorB.b == 1.0f)
//		alpha = 0.0f;
//	float4 color = colorA * (1.0f- alpha)  +  colorB * alpha;
//	return color;
//}
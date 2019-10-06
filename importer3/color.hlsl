//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer cb0: register(b0)
{
    matrix	g_matWorld		: packoffset(c0);
    matrix	g_matView		: packoffset(c4);
    matrix	g_matProj		: packoffset(c8);
    float4  g_MeshColor     : packoffset(c12);
    float  g_fTime : packoffset(c13.x);

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
    float4 p : SV_POSITION;
    float3 n : NORMAL;
    float4 c : COLOR0;
    float2 t : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT vIn)
{

    VS_OUTPUT vOut = (VS_OUTPUT)0;
    vOut.p = float4(vIn.p, 1.0f);
    vOut.p.x = (vIn.p.x);
    vOut.p.y = (vIn.p.y);
    vOut.p.z = (vIn.p.z);
    // vOut.p.w = 1.0f;



    vOut.p = mul(vOut.p, g_matWorld); //vWorld
    vOut.p = mul(vOut.p, g_matView);
    vOut.p = mul(vOut.p, g_matProj);
    //vOut.t = vIn.t;
    ////vOut.c = vIn.c;
    //vOut.c.w = 1.0f;

    //vOut.p = float4(vIn.p,1.0f);
   //vOut.p.x = vOut.p.x + 10;
   //vOut.p.z = vOut.p.z + 10;
    vOut.n = vIn.n;
    vOut.c = vIn.c;
    vOut.t = vIn.t;
    return vOut;
}


float4 PS(VS_OUTPUT vIn) : SV_Target
{
  vIn.c.w = 0.3f;
    return vIn.c;
     
}

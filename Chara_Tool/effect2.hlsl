Texture2D g_txDiffuse : register(t0);
Texture2D g_txMask : register(t1);
SamplerState s0 : register(s0);

struct VB
{
    float deltime : DELTATIME;
    float fadein_deltime : FADEINDELTATIME;
    float fadeout_deltime : FADEOUTDELTATIME;
    float2 t : TEXCOORD;
    float4x4 matctrl : MATCTRL;
    float texid : TEXID;
    float type : TYPE;
};
struct PS_INPUT
{

  //  float deltime : DELTATIME;
  //  float fadein_deltime : FADEINDELTATIME;
  //  float fadeout_deltime : FADEOUTDELTATIME;
    float4 p :SV_POSITION;
    float3 n :NORMAL;
    float4 c :COLOR0;
    float2 t : TEXCOORD0;
   // float4x4 matctrl : MATCTRL;
  //  float texid : TEXID;
   // float type : TYPE;

    

};


cbuffer cb0 : register(b0)
{
    matrix g_matWorld: packoffset(c0);// »ó¼ö·¹Áö½ºÅÍ
    matrix g_matView : packoffset(c4);
    matrix g_matProj : packoffset(c8);
   // float4 g_Color : packoffset(c12);
    float  g_fTime : packoffset(c12.x);
};

cbuffer cb2 : register(b2)
{  
    float4 g_vColor : packoffset(c0);
    float4 g_vPower : packoffset(c1);
    float4 g_vMoveVec : packoffset(c2);
    float4 g_vtime : packoffset(c3);
    float4 g_vtarget_speed :packoffset(c4);
    float4 g_vRand_Loop_etc2 :packoffset(c5);


};



VB VS_FRAME(VB input)
{
    return input;
}

//void GSGenericHandler(VS_INPUT input,
//    inout PointStream<VS_INPUT> vOut)
//{
//    input.p += input.vel * g_fTime;
//    input.vel += g_vGravity.xyz * g_fTime;
//    input.fTimer -= g_fTime;
//    vOut.Append(input);
//}
//
void GSLauncherHandler(VB input,
    inout PointStream<VB> vOut)
{
   // if (input.deltime <= g_fLifetime)
   // {
      //  input.deltime += g_fTime;
        vOut.Append(input);
       
   //        VS_INPUT output;
   //        output.p = input.p + input.vel * g_fTime;
   //        output.vel = input.vel;
   //        output.vel.x += cos(g_vGravity.w * 10000)*10.0f;
   //        output.vel.z += sin(g_vGravity.w * 10000)*-10.0f;
   //        output.fTimer = 5.0f;
   //        output.type = PT_SHELL;
   //        vOut.Append(output);
   //   
   //
   //}
   //else
   //{
   //    input.fTimer -= g_fTime;
   //    vOut.Append(input);
   //}

}
//void GSShellHandler(VS_INPUT input,
//    inout PointStream<VS_INPUT> vOut)
//{
//    if (input.fTimer <= 0)
//    {
//        // 2Â÷ ÆøÆÈ
//    }
//    else
//    {
//        GSGenericHandler(input, vOut);
//    }
//
//}
[maxvertexcount(4)]
void GS_FRAME(
    in point VB vIn[1],
    inout PointStream<VB> vOut)
{
   // if (vIn[0].type == PT_LAUNCHER)
   // {
        GSLauncherHandler(vIn[0], vOut);
   // }
   // else if (vIn[0].type == PT_SHELL)
   // {
   //     GSShellHandler(vIn[0], vOut);
   // }
}

//
VB VS(VB input)
{
    return input;
}

[maxvertexcount(4)]
void GS(in point VB vIn[1],
    inout TriangleStream<PS_INPUT> vOut)
{
    const float4 g_positions[4] =
    {
        float4(-10.0f, 10.0f, 0.0f,1.0f),
        float4(10.0f, 10.0f, 0.0f,1.0f),
        float4(-10.00f, -10.0f, 0.0f,1.0f),
        float4(10.0f, -10.0f, 0.0f,1.0f),
    };
    const float4 g_color[4] =
    {
        float4(1.0f, 1.0f, 1.0f,1.0f),
        float4(1.0f, 1.0f, 1.0f,1.0f),
        float4(1.0f, 1.0f, 1.0f,1.0f),
        float4(1.0f, 1.0f, 1.0f,1.0f),
    };
    const float2 g_texcoords[4] =
    {
        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(0.0f, 1.0f),
        float2(1.0f, 1.0f),
    };
    PS_INPUT vertex = (PS_INPUT)0;
    for (int i = 0; i < 4; i++)
    {
        vertex.p = g_positions[i];
        vertex.p = mul(vertex.p, vIn[0].matctrl);
        vertex.p = mul(vertex.p, g_matView);
        vertex.p = mul(vertex.p, g_matProj);
        vertex.n = float3(0, 0, -1);
        vertex.c = g_color[i];
        vertex.t = g_texcoords[i];
        vOut.Append(vertex);
    }
    vOut.RestartStrip();
}

float4 PS(PS_INPUT input) : SV_TARGET
{
    /*float3 vLight = float3(0.0f, -1.0f, 0.0f) * -1.0f;
    float fDot = max(0.0f, dot(vLight, input.n));
    float4 vColor = float4(fDot, fDot, fDot,1.0f);
    float4 color = vColor * g_txDiffuse.Sample(s0, input.t);*/// *input.c;
    //float4 color = g_txDiffuse.Sample(s0, input.t)*input.c;
    return g_txDiffuse.Sample(s0, input.t);
}

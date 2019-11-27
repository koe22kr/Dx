Texture2D g_txDiffuse : register(t0);
Texture2D g_txMask : register(t1);
SamplerState s0 : register(s0);

struct VB
{
    float deltime : DELTATIME;
    float4 texuv : TEXCOORD;
    float3 pos: POSITION;
    uint texid : TEXID;
    float type : TYPE;
    float alpha : ALPHA;
    //알파값 추가
    
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
    matrix g_matWorld: packoffset(c0);// 상수레지스터
    matrix g_matView : packoffset(c4);
    matrix g_matProj : packoffset(c8);
    float  g_SecPerFrame : packoffset(c12.x);//x=secperframe//y=gametimer//
    float  g_GameTimer : packoffset(c12.y);
};
cbuffer cb2 : register(b2)
{  
    float4 g_vColor : packoffset(c0);
    float4 g_vPower : packoffset(c1);//x y z ,w==0
    float4 g_vMoveVec : packoffset(c2);//x y z ,w==0
    float4 g_vtime : packoffset(c3);//add_life_fadein_fadeout
    float4 g_vtarget_speed :packoffset(c4); //targetPos.xyz, speed.w;
    float4 g_vRand_Loop_cutx_cuty :packoffset(c5);
    matrix g_matCtrl :packoffset(c6);
    float4 etc4 : packoffset(c10);//애니메이션 한바퀴 시간x,
};

#define EFFECT_BASE 0
#define EFFECT_OBJ 1

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

float2x4 GetUV(VB input)
{
    float2x4 uv = float2x4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    uint cutx = g_vRand_Loop_cutx_cuty.z;
    uint cuty = g_vRand_Loop_cutx_cuty.w;
    float x = 1.0f / cutx;
    float y = 1.0f / cuty;
    
    if ((cutx*cutx <= input.texid && g_vRand_Loop_cutx_cuty.y > 1)|| g_vRand_Loop_cutx_cuty.z < 2 && g_vRand_Loop_cutx_cuty.y < 2)
    {
        uv._11 = 0.0f;
        uv._12 = 0.0f;

        uv._13 = x;
        uv._14 = 0.0f;

      

        uv._21 = 0.0f;
        uv._22 = y;

        uv._23 = x;
        uv._24 = y;
        return uv;
        input.texid = 0;
    }
    else
    {
        for (uint i = 0; i < cuty; i++)
        {
            for (uint j = 0; j < cutx; j++)
            {
                if (cutx*i + j == input.texid)
                {
                    uv._11 = x * j;
                    uv._12 = y * i;

                    uv._13 = x * (j + 1);
                    uv._14 = y * i;

                    uv._21 = x * j;
                    uv._22 = y * (i + 1);

                    uv._23 = x * (j + 1);
                    uv._24 = y * (i + 1);

                    
                    return uv;
                }
            }
        }
    }
    return uv;
}

void GSObjHandler(VB input,
    inout PointStream<VB> vOut)
{
    float3 POWER;
    POWER = g_vPower.xyz;
    POWER += g_vMoveVec.xyz;
    POWER += ((normalize(g_vtarget_speed.xyz - input.pos))*g_vtarget_speed.w);
    POWER *= g_SecPerFrame;
    input.pos += POWER;
    vOut.Append(input);
}

[maxvertexcount(90)]
void GS_FRAME(
    in point VB input[1],
    inout PointStream<VB> vOut)
{
   // vOut.Append(input[0]);

   // switch (input[0].type)
        if (input[0].type == EFFECT_BASE)
        {
            input[0].deltime += g_SecPerFrame;
            


            if (input[0].deltime > g_vtime.x)
            {
                input[0].deltime -= g_vtime.x;
                vOut.Append(input[0]);
               
               
                
                VB obj = input[0];
                obj.type = EFFECT_OBJ;
                obj.deltime = 0.0f;

                GSObjHandler(obj, vOut);

                vOut.Append(obj);
            }
            else
            {
                vOut.Append(input[0]);
            }
        
        }
        if (input[0].type == EFFECT_OBJ)
        {
            if (g_vRand_Loop_cutx_cuty.y > 0)
            {
                float deltaanim = input[0].deltime;
                while (etc4.x < deltaanim)
                {
                    deltaanim -= etc4.x;
                }
                input[0].texid = (uint)((deltaanim / etc4.x) *g_vRand_Loop_cutx_cuty.z*g_vRand_Loop_cutx_cuty.w);
            }
            else
            {
                input[0].texid = (uint)((input[0].deltime / etc4.x) *g_vRand_Loop_cutx_cuty.z*g_vRand_Loop_cutx_cuty.w);
                input[0].texid = min(input[0].texid, g_vRand_Loop_cutx_cuty.z*g_vRand_Loop_cutx_cuty.w);
            }

            input[0].deltime += g_SecPerFrame;
            if (input[0].deltime < g_vtime.y)
            {//생존//레이아웃의 알파값 추가해야함//add_life_fadein_fadeout
                if (input[0].deltime < g_vtime.z)
                {//페이드 인
                 //알파값 조정
                    input[0].alpha = input[0].deltime / g_vtime.z;
                    GSObjHandler(input[0], vOut);
                }
                else if (input[0].deltime < g_vtime.y - g_vtime.w)
                {//생존
                    input[0].alpha = 1.0f;
                    GSObjHandler(input[0], vOut);
                }
                else
                {//페이드 아웃
                    //알파값 조정
                    input[0].alpha =  (g_vtime.y- input[0].deltime) / g_vtime.w;

                    GSObjHandler(input[0], vOut);
                }
            }
            else
            {//사망

            }


        }
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

    float2x4 uv = GetUV(vIn[0]);
    float2 uvlist[4] =
    {
        float2(uv._11,uv._12),
        float2(uv._13,uv._14),
        float2(uv._21,uv._22),
        float2(uv._23,uv._24),
    };
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
   /* const float2 g_texcoords[4] =
    {
        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(0.0f, 1.0f),
        float2(1.0f, 1.0f),
    };*/
    PS_INPUT vertex;
    for (int i = 0; i < 4; i++)
    {
        vertex.p = float4(vIn[0].pos.xyz,1.0f) +g_positions[i];
       // vertex.p = g_positions[i];
        vertex.p = mul(vertex.p, g_matCtrl);
        vertex.p = mul(vertex.p, g_matView);
        vertex.p = mul(vertex.p, g_matProj);
        vertex.n = float3(0, 0, -1);
        vertex.c = g_color[i];
        vertex.c.w = vIn[0].alpha;
        vertex.t = uvlist[i];
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
    return g_txDiffuse.Sample(s0, input.t)*(input.c.w-0.1);

}

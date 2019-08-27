cbuffer cb0
{
    float4 Color     : packoffset(c0);
    float fTime : packoffset(c1.x);
    
};

struct VS_OUTPUT
{
    float4 Position  : SV_Position;
    float4 Diffuse  : COLOR0;

};


VS_OUTPUT VS(float3 p : POSITION,float4 t : TEX)
{
    VS_OUTPUT OP;
    

    float3 vPos = p * fTime;
    OP.Position.x = p.x
    OP.Position.y = p.y
    OP.Position.z = p.z
    OP.Position.w = 1.0f;
    OP.Diffuse = t;


    return OP;
}
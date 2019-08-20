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


VS_OUTPUT VS(float3 p : POSITION)
{
    VS_OUTPUT OP;
    

    float3 vPos = p * fTime;
    OP.Position.x = (vPos.x*((cos(( fTime))) - vPos.y*(sin(( fTime))))) + fTime * 2 - 1;
    OP.Position.y = (vPos.x*(sin(( fTime))) + vPos.y*(cos(( fTime)))) + fTime * 2 - 1;
    OP.Position.z = 1.0f;
    OP.Position.w = 1.0f;
    OP.Diffuse = Color;


    return OP;
}
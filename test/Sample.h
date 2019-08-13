#pragma once
#include "CACore.h"
#include "dxdiag.h"
#define MAX_CONST_BUFFER 100
#include <d3dx10math.h>
#include <DirectXPackedVector.h>

#pragma comment(lib,"d3dx10.lib")

struct FLOAT3
{
    float x;
    float y;
    float z;
};
struct CONST_BUFFER_F8
{
    D3DXVECTOR4  vColor;
    float x;
    float y;
    float z;
    float w;

};

class Sample :public CACore
{
public:
    float ftime = 0;
    ID3D11Buffer* m_pVertex_Buffer;
    ID3D11Buffer* m_pIndex_Buffer;
    ID3D11Buffer* m_pConst_Buffer;
    DWORD m_Const_Buffer_Data[MAX_CONST_BUFFER];

    ID3D11InputLayout* m_pInput_Layout;
    ID3D11VertexShader* m_pVertex_Shader;
    ID3D11PixelShader* m_pPixel_Shader;


    bool Create_Vertex_Buffer();
    bool Create_Vertex_Buffer2();
    bool Create_Index_Buffer();
    bool Create_Const_Buffer();
    bool Load_Shader_And_Input_Layout();
    bool Load_Shader_And_Input_Layout2();
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    Sample();
    virtual ~Sample();
};
//test
WINRUN_DEFAULT
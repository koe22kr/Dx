#pragma once
#include "CACore.h"
#include "CAMatrix.h"


class Sample:public CACore
{

public:
    D3DXMATRIX m_matWorld;
    D3DXMATRIX m_matView;
    D3DXMATRIX m_matProj;

    ID3D11Buffer* m_pVertex_Buffer;
    ID3D11Buffer* m_pIndex_Buffer;
    ID3D11Buffer* m_pConst_Buffer;
    
    ID3D11PixelShader* m_pPixel_Shader;
    ID3D11VertexShader* m_pVertex_Shader;
    void first();
public:
    Sample();
    ~Sample();
};

WINRUN_DEFAULT
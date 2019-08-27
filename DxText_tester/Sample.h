#pragma once
#include "CACore.h"

class Sample :public CACore
{
public:
    ID3D11Buffer* m_pVertex_Buffer;
    ID3D11Buffer* m_pVertex_Buffer2;

    ID3D11Buffer* m_pIndex_Buffer;
    ID3D11Buffer* m_pIndex_Buffer2;

    ID3D11Buffer* m_pConst_Buffer;

    ID3D11VertexShader* m_pVertex_Shader;

    ID3D11PixelShader* m_pPixel_Shader;
    ID3D11PixelShader* m_pPixel_Shader2;
    ID3D11InputLayout* m_pInput_Layout;

    ID3D11ShaderResourceView* m_pSRV;

    CADeviceMgr* m_pDevice_Mgr;
    bool Test();
    void Test_Frame();
    bool Init();
    bool Frame();
    bool Render();
    Sample();
    virtual ~Sample();

};

WINRUN_DEFAULT
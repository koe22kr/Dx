#pragma once
#include "CACore.h"
#include "Quad_Tree.h"
#include "Pick.h"
class Sample :public CACore
{
public:
    Quad_Tree m_quad;
    DX::CADx_Shape_Line m_line;
    D3DXVECTOR3 m_LinePos;
    bool Init() override;
    bool Frame()override;
    bool Render()override;
    bool Release()override;
    Pick m_Select;
    void Test_Pick();
    Sample();
    ~Sample();
};

WINRUN_DEFAULT

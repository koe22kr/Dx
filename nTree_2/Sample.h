#pragma once
#include "CACore.h"
#include "Quad_Tree.h"
class Sample :public CACore
{
public:
    Quad_Tree m_quad;
    bool Init() override;
    bool Frame()override;
    bool Render()override;
    bool Release()override;

    Sample();
    ~Sample();
};

WINRUN_DEFAULT

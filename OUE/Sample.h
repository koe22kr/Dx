#pragma once
#include "CACore.h"
#include "Dun.h"
class Sample :public CACore
{
public:
    Dun m_Dun;
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

    Sample();
    ~Sample();
};

WINRUN_DEFAULT

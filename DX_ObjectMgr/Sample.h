#pragma once
#include "CACore.h"
#include "ObjectMgr.h"

class Sample :public CACore
{
public:
    ObjectMgr DX_MGR;
public:
    float time;
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
public:
    Sample();
    ~Sample();
};

WINRUN_DEFAULT

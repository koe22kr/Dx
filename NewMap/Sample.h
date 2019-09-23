#pragma once
//#include "Map.h"
#include "CACore.h"
using namespace DX;
class Sample : public CACore
{
public:
 //   HeightMap m_Map;
    bool Init(); 
    bool Frame();
    bool Render();
    bool Release();
    Sample();
    ~Sample();
};

WINRUN_DEFAULT


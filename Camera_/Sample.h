#pragma once
#include "CAShape.h"
#include "CACore.h"
#include "Camera.h"
using namespace DX;
class Sample : public CACore
{
public:
    CAShape_Box box;
    Camera Cam;
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    Sample();
    ~Sample();
};

WINRUN_DEFAULT
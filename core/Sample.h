#include "CACore.h"

#pragma once

class Sample :public CACore
{
public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    Sample();
    ~Sample();

private:

};

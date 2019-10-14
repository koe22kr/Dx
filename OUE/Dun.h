#pragma once
#include "CADx_Model2.h"
#include "Void_Box.h"
#include "CACore.h"
#include "Std.h"

class Dun
{
public:
    
    Void_Box Cubes[18][32];
    
    void Render();
    void Frame();
public:
    void Dungeon_Make();
    
public:
    Dun();
    virtual ~Dun();
};


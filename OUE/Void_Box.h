#pragma once
#include "CADx_Model2.h"
#include "Std.h"
class Void_Box : public DX::CADx_Model2
{
public:
    HRESULT CreateVertexData();
    HRESULT CreateIndexData();
    bool CreateBox(WINT pos);
    Void_Box();
    virtual ~Void_Box();
};

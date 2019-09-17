#pragma once
#include "CACore.h"
#include "CAMatrix.h"


class Sample:public CACore
{

public:
  

    ID3D11Buffer* m_pVertex_Buffer;
    ID3D11Buffer* m_pIndex_Buffer;
    ID3D11Buffer* m_pConst_Buffer;
    
   
    void first();
public:
    Sample();
    ~Sample();
};

WINRUN_DEFAULT
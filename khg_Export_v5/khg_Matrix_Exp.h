#pragma once
#include "khg_Obj_Exp.h"


class khg_Matrix_Exp :public khg_Obj_Exp
{
public:
    bool    Convert() override;
    bool    Export() override;
    khg_Matrix_Exp();
    ~khg_Matrix_Exp();
    //
    static khg_Matrix_Exp* Get()
    {
        static khg_Matrix_Exp instance;
        return &instance;
    }
};


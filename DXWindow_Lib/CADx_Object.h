#include "CADx_Model.h"
#pragma once
namespace DX
{

    struct CAObj_Info
    {
         WFLOAT Init_Pos;
         //Info ~~~~
         
    };

    class CADx_Object :public CADx_Model
    {
        //Obj Info//
    public:
        CADx_Object();
        ~CADx_Object();
    };

}
#pragma once
#include "CADx_Model.h"
namespace DX
{
    class CAShape :public CADx_Model
    {
    public:
        virtual bool Create_Vertex_Index_Const_Data() = 0;

    public:
        CAShape();
        ~CAShape();
    };

    class CAShape_Line : public CADx_Model
    {
    public:
        bool Create_Debug_Coordinate(float x = 0, float y = 0, float z = 0);
        virtual bool PostRender(ID3D11DeviceContext* pContext);

    public:
        CAShape_Line();
        ~CAShape_Line();
    };

    class CAShape_Box : public CADx_Model
    {
    public:
        virtual bool Create_Vertex_Index_Const_Data();
    public:
        CAShape_Box();
        ~CAShape_Box();

    private:

    };

}

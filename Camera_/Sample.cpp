#include "Sample.h"


bool Sample::Init()
{
    box.Create_Vertex_Index_Const_Data();

    box.Create(L"VS.vsh", L"PS.psh", "PS", "VS", L"../../_data/sky/ft.bmp", 1, 800, 600, true);
    return true;
}
bool Sample::Frame()
{
    box.m_HDX.Set_Const_Buffer_Self(&box.m_Const_List[0], 0);
    return true;
}
bool Sample::Render()
{
    box.Render();
    return true;
}
bool Sample::Release()
{
    return true;
}
Sample::Sample()
{
}


Sample::~Sample()
{
}

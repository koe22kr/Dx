#include "Sample.h"

bool Sample::Init()
{
    m_Dun.Dungeon_Make();
    return true;
}
bool Sample::Frame()
{
    m_Dun.Frame();
    return true;

}
bool Sample::Render()
{
    m_Dun.Render();
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

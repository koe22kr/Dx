#include "Dun.h"


void Dun::Dungeon_Make()
{
    for (int h = 0; h < DUN_HEIGHT; h++)
    {
        for (int w = 0; w < DUN_WIDTH; w++)
        {
            Cubes[h][w].CreateBox(WINT(h * 8, w * 8));
            Cubes[h][w].Create(CADevice::m_pDevice, L"Dun.hlsl", L"lightmap.bmp");
            
        }
    }
    
}
void Dun::Render()
{
    for (int h = 0; h < DUN_HEIGHT; h++)
    {
        for (int w = 0; w < DUN_WIDTH; w++)
        {
            Cubes[h][w].SetMatrix(nullptr, (DirectX::XMMATRIX*)&CACore::m_pMain_Cam->m_matView, (DirectX::XMMATRIX*)&CACore::m_pMain_Cam->m_matProj);
            Cubes[h][w].Render(CADevice::m_pImmediate_Device_Context);
           
        }
    }

}
void Dun::Frame()
{

}

Dun::Dun()
{
}


Dun::~Dun()
{
}

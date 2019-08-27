#pragma once
#include "CADevice.h"

class CATexture
{
public:
    std::wstring m_File_Path;
    std::wstring m_File_Name;
    bool m_Index_Draw_Flag;
    int m_Draw_Count;
    int m_Start_Vertex_Location;
    int m_Start_Index_Location;
    bool Draw_Flag;
    void Set_Draw_Flag(bool flag) { Draw_Flag = flag; }; //ÇÊ¼ö
    void Set_Start_Location(int draw_count, int vertex_location, int index_location = 0);
    ID3D11ShaderResourceView* m_pSRV;
    bool Draw(ID3D11DeviceContext* pContext);
public:
    CATexture();
    ~CATexture();
};


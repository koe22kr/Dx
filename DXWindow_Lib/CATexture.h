#pragma once
#include "CADevice.h"

class CATexture
{
public:
    UINT m_Index;
    std::wstring m_File_Full_Path;

    //std::wstring m_File_Name;
    bool m_Index_Draw_Flag;
    int m_Draw_Count;
    int m_Start_Vertex_Location;
    int m_Start_Index_Location;
    bool Draw_Flag;
    void Set_Draw_Flag(bool flag) { Draw_Flag = flag; }; //ÇÊ¼ö
    void Set_Index_Draw_Flag(bool flag) { m_Index_Draw_Flag = flag; };
    void Set_Draw_OPT(int draw_count, int vertex_location=0, int index_location = 0);
    ID3D11ShaderResourceView* m_pSRV;
    bool Draw(ID3D11DeviceContext* pContext);
    bool release() { m_pSRV->Release(); };
public:
    CATexture();
    virtual ~CATexture();
};


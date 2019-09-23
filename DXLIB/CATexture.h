#pragma once
#include "CADevice.h"

class CATexture
{
public://2
    T_STR	 m_szPath;
    T_STR	 m_szName;
    int		 m_iIndex;
    float    m_fScale;

    bool    Apply(ID3D11DeviceContext* pContext, UINT iSlot = 0);
    bool Load(ID3D11Device* pDevice,
        std::wstring filename);
    bool Render() { return true; };

public://2
    ID3D11ShaderResourceView* m_pSRV;

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
    bool Draw(ID3D11DeviceContext* pContext);
    bool Release() { if (m_pSRV) { m_pSRV->Release(); m_pSRV = NULL; return true; } };
public:
    CATexture();
    virtual ~CATexture();
};


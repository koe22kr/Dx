#pragma once
#include "CADx_Shape.h"
#include <iostream>
#include <fstream>
#include "CADx_Model2.h"
#include <vector>
#include <string>

struct Material
{
    string material_name;
    int imaterial_size;
    int imaterial_index;
    string texturefilename;
    int SRV_Index;
};
class Load_Shape : public DX::CADx_Shape_Box
{
public:
    int m_Render_Count;
    int m_Texture_Count;
    std::vector<DX::PNCT_VERTEX2>* m_pnct_List;
    std::map<UINT, wstring> m_filename_map;
    std::vector< Material> m_Material_List;
    std::vector< vector<DX::PNCT_VERTEX2>> m_VertexList_List;
    std::vector<vector<DWORD>> m_IndexList_List;
    //m_Index_List;
    void Load(const char* maxconvertfile);

    std::vector<DX::PNCT_VERTEX2> tester;

public:
    ////////////////
#ifdef Use_Origin



#else


HRESULT CreateVertexData();
HRESULT CreateIndexData();
HRESULT LoadTextures(
    ID3D11Device* pd3dDevice,
    const TCHAR* pLoadTextureFile);
bool PostRender(
    ID3D11DeviceContext* pContext, UINT iCount = 0);
virtual bool  PostRender(ID3D11DeviceContext* pContext);
void LoadTextureIndex(const TCHAR* pLoadTextureFile);
bool Costom_LoadTexture();

#endif // DEBUG

    Load_Shape();
    virtual ~Load_Shape();
};


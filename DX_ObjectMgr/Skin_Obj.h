#pragma once
#include "CADx_Shape.h"
#include "CADx_Model2.h"
#include <iostream>
#include <fstream>

struct Texture_Info
{
    wstring texture_filename;
};
struct Material_Info
{
    string material_name;
    int material_index;
    
    int submaterial_size;
    vector<Material_Info> sub_material_info_list;

    int texture_size;
    vector<Texture_Info> texture_info_list;
    
    //std::vector<std::vector< DX::CADx_Model2>>   m_obj_mtl_List;
};
struct Object_Info
{
    string obj_name;
    string parent_name;
    int SRV_Index;
   
};
struct Sorted_Vertex_by_Texture
{
    std::vector<DX::PNCT_VERTEX2>     m_Vertex_List;
    std::vector<DWORD>           m_Index_List;
    ID3D11ShaderResourceView*    m_pSRV;
};

class Skin_Obj /*: public DX::CADx_Model2*/
{
public:
    int m_iShader_index;
    int m_iMatobj_index;
    std::vector<wstring> m_Tex_filename_list;
    std::vector<Material_Info> m_Material_Info;
    std::vector<Object_Info>               m_Obj_Info_List;

    std::vector<std::vector< Sorted_Vertex_by_Texture >>   m_obj_mtl_List;
public:

    void Skin_Load(const char* skxconvertfile, const TCHAR* texpath);
public:
    Skin_Obj();
    ~Skin_Obj();
};


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
struct PNCTI4W4
{
    DirectX::XMFLOAT3 p;
    DirectX::XMFLOAT3 n;
    DirectX::XMFLOAT4 c;
    DirectX::XMFLOAT2 t;
    UINT i[4];
    DirectX::XMFLOAT4 w;
    
};
struct Sorted_Vertex_by_Texture
{
    std::vector<PNCTI4W4>     m_Vertex_List;
    std::vector<DWORD>           m_Index_List;
    ID3D11ShaderResourceView*    m_pSRV;
    ID3D11Buffer* VB;
    ID3D11Buffer* IB;
    Sorted_Vertex_by_Texture()
    {
        m_pSRV = NULL;
        VB = NULL;
        IB = NULL;
    }
    ~Sorted_Vertex_by_Texture()
    {
      /*  if (VB)
        {
            VB->Release();
        }
        if (IB)
        {
            IB->Release();
        }*/
        //skin 
    }
};

class Skin_Obj
{
public:
    int m_iShader_index;
    int m_iMat_index;
    std::vector<wstring>         m_Tex_filename_list;
    std::vector<Material_Info>   m_Material_Info;
    std::vector<Object_Info>     m_Obj_Info_List;
    std::vector<D3DXMATRIX>      m_matinv_World_List;
    ID3D11Buffer*                m_pmatinv_World_Buffer;
    ID3D11ShaderResourceView*    m_pinv_World_SRV;

    std::vector<std::vector< Sorted_Vertex_by_Texture >>   m_obj_mtl_List;
public:
    void Release();
    int Get_Render_Obj_index();
    int Get_Mat_index();
    int Get_obj_size();
    int Get_mtl_size(int iobj);
    Sorted_Vertex_by_Texture* Get(int iobj, int imtl);
    void Skin_Load(const char* skxconvertfile, const TCHAR* texpath, ID3D11Device* pDevice);
public:
    Skin_Obj();
    ~Skin_Obj();
};


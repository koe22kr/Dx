#pragma once
#include "CADx_Shape.h"
#include <iostream>
#include <fstream>
#include "CADx_Model2.h"
#include <vector>
#include <string>


struct Texture_Info
{
    wstring texture_filename;

};
struct Material_Info
{
    string material_name;
    //int material_index;
    int submaterial_size;
    int texture_size;
    
    vector< Texture_Info> texture_info_list;
    vector<Material_Info> sub_material_info_list;
    
};

struct Animation_Info
{
    D3DMATRIX mAnim_Tran;
    D3DMATRIX mAnim_Rot;
    D3DMATRIX mAnim_Scal;
    D3DXVECTOR3 vTran;
    D3DXQUATERNION vRot;
    D3DXVECTOR3 vScale;

};
struct Object_Info
{
    
};

//단일 랜더링 오브잭트화 하자.
class Load_Shape : public DX::CADx_Model2                       
{
public:
    int m_my_material_index;
    int SRV_Index;
    std::vector<std::vector< Load_Shape>> m_obj_mtl_List;
    std::vector<wstring> m_filename_list;
    //std::vector<DX::PNCT_VERTEX2>* m_pnct_List;
//    std::map< wstring, DWORD> m_filename_index_map;
    Material_Info m_Material_Info;
    
    void Load(const char* maxconvertfile);

    void  LoaderCreate(ID3D11Device* pd3dDevice,
        const TCHAR* pLoadShaderFile,
        const TCHAR* pLoadTextureFile);
    void  LoaderSetMatrix(D3DXMATRIX* pWorld,
        D3DXMATRIX* pView,
        D3DXMATRIX* pProj);
    void  LoaderRender(ID3D11DeviceContext* pContext);
public:
    ////////////////
#ifdef Use_Origin



#else


HRESULT CreateVertexData();
HRESULT CreateIndexData();
HRESULT LoadTextures(
    ID3D11Device* pd3dDevice,
    const TCHAR* pLoadTextureFile);
//bool PostRender(
//    ID3D11DeviceContext* pContext, UINT iCount = 0);
//virtual bool  PostRender(ID3D11DeviceContext* pContext);
void LoadTextureIndex(const TCHAR* pLoadTextureFile);
bool Costom_LoadTexture();

#endif // DEBUG

    Load_Shape();
    virtual ~Load_Shape();
};


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
struct AnimTrack
{
    int i;
    D3DXVECTOR3 p;
    D3DXQUATERNION q;
};
struct Scene
{
    int iFirst_Frame;
    int iLast_Frame;
    int iFrame_Speed;    //30
    int iTick_Per_Frame;  //160
    ////아래 것들 쓸모?
    //int iNum_Obj;
    //int iNum_Mtl;
    Scene()
    {
        iFirst_Frame = 0;
        iLast_Frame = 0;
        iFrame_Speed = 0;
        iTick_Per_Frame = 0;
    }

};

struct Animation_Info
{
    D3DXMATRIX  m_matCalculation;
    D3DXMATRIX mat_world;
    D3DXMATRIX mat_world_inv;
    D3DXMATRIX mAnim_Tran;
    D3DXMATRIX mAnim_Rot;
    D3DXMATRIX mAnim_Scal;
    D3DXVECTOR3 vTran;
    D3DXQUATERNION vRot;
    D3DXVECTOR3 vScale;

    bool bAnimation[3];
    std::vector<AnimTrack> Anim_S;
    std::vector<AnimTrack> Anim_R;
    std::vector<AnimTrack> Anim_T;
};
struct Object_Info
{
    string obj_name;
    string parent_name;
    int parent_index;
    Object_Info()
    {
        parent_index = -1;
    }
};

//단일 랜더링 오브잭트화 하자.
class Load_Shape : public DX::CADx_Model2                       
{
public:
    float m_fElapseTick;
    Scene m_Scene;
    int m_my_material_index;
    int SRV_Index;
    std::vector< Object_Info>               m_obj_info_List;
    std::vector<Animation_Info>             m_obj_anim_List;
    std::vector<std::vector< Load_Shape>>   m_obj_mtl_List;
    std::vector<wstring> m_Tex_filename_list;
    //std::vector<DX::PNCT_VERTEX2>* m_pnct_List;
//    std::map< wstring, DWORD> m_filename_index_map;
    Material_Info m_Material_Info;
    bool Frame();
    void Interpolate(int obj_index, bool have_parent, float tick);
    bool GetAnimationTrack(float fElapseTime, std::vector<AnimTrack>& trackList, AnimTrack& StartTrack, AnimTrack& EndTrack);
    void Load(const char* maxconvertfile);
    int find_my_parents(int index);
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


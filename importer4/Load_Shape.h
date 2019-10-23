#pragma once
#include "CADx_Shape.h"
#include <iostream>
#include <fstream>
#include "CADx_Model2.h"
#include <vector>
#include <string>


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

    vector<Texture_Info> texture_info_list;
    vector<Material_Info> sub_material_info_list;

};
struct Animation_Info
{
   // D3DXMATRIX  m_matCalculation;
   // D3DXMATRIX mat_world;       //현 버전에서는 사용하지 않지만. 버전에 따라 필요할 수 있?
   // D3DXMATRIX mat_world_inv;   //현 버전에서는 사용하지 않지만. 버전에 따라 필요할 수 있?
    D3DXMATRIX mAnim_Tran;
    D3DXMATRIX mAnim_Rot;
    D3DXMATRIX mAnim_Scal;
    //D3DXVECTOR3 vTran;
    //D3DXQUATERNION vRot;
    //D3DXVECTOR3 vScale;
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
    int m_my_material_index;
    int SRV_Index;
    Object_Info()
    {
        parent_index = -1;
    }
};

class Load_Shape
{
private:
    float m_fElapseTick;
    Scene m_Scene;
    std::vector<Object_Info>               m_obj_info_List;
    std::vector<Animation_Info>             m_obj_anim_List;
    std::vector<std::vector< DX::CADx_Model2>>   m_obj_mtl_List;

    std::vector<wstring> m_Tex_filename_list;
    std::vector<Material_Info> m_Material_Info;
public:
    void Skin_Load(const char* maxconvertfile,const TCHAR* texpath);
public:
    bool Frame();
    void Interpolate(int obj_index, bool have_parent, float tick);
    bool GetAnimationTrack(float fElapseTime, std::vector<AnimTrack>& trackList, AnimTrack& StartTrack, AnimTrack& EndTrack);
    int find_my_parents(int index);
public:
    void  LoaderCreate(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile, const TCHAR* pLoadTextureFile);
    void  LoaderSetMatrix(D3DXMATRIX* pView, D3DXMATRIX* pProj);
    void  LoaderRender(ID3D11DeviceContext* pContext);
public:
    //HRESULT CreateVertexData();
    //HRESULT CreateIndexData();
    Load_Shape();
    virtual ~Load_Shape();
};


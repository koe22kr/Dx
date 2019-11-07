#pragma once
#include "CADx_Shape.h"
#include "CADx_Model2.h"
#include <iostream>
#include <fstream>

struct Scene
{
    int iFirst_Frame;
    int iLast_Frame;
    int iFrame_Speed;    //30
    int iTick_Per_Frame;  //160
    ////�Ʒ� �͵� ����?
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

struct AnimTrack
{
    int i;
    D3DXVECTOR3 p;
    D3DXQUATERNION q;
};

struct Animation_Info
{
    std::string obj_name;
    std::string parent_name;
    DX::T_BOX mBox;
    // D3DXMATRIX  m_matCalculation;
    // D3DXMATRIX mat_world;       //�� ���������� ������� ������. ������ ���� �ʿ��� �� ��?
    // D3DXMATRIX mat_world_inv;   //�� ���������� ������� ������. ������ ���� �ʿ��� �� ��?
    std::vector<D3DXMATRIX> mat_Final_Anim_list;//SRT ��� �� NodeTM ������ ����... �ϴ� �̰� ����ϴ� �Լ� �����.
    //D3DXVECTOR3 vTran;
    //D3DXQUATERNION vRot;
    //D3DXVECTOR3 vScale;
    std::vector<AnimTrack> Anim_S;
    std::vector<AnimTrack> Anim_R;
    std::vector<AnimTrack> Anim_T;
};

class Mat_Obj
{
public:
    string m_szMat_File;
    Scene m_Scene;
    std::vector<Animation_Info>             m_anim_obj_List;
    std::vector<D3DXMATRIX> m_cur_mat;
    ID3D11Buffer* m_Cur_Mat_Buffer;
    ID3D11ShaderResourceView* m_Cur_Mat_SRV;
    std::vector < std::vector<D3DXMATRIX>> m_mat_test;

public:
    void Release();
    void Find_curMat(float& elapsetime, int startframe,int lastframe);
    void Mat_Load(const char* mtxconvertfile, ID3D11Device* pDevice);
    void Update_Render_Mat(ID3D11DeviceContext* pContext);
    void Interpolate();

public:

public:
    Mat_Obj();
    ~Mat_Obj();
};


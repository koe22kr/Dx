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
    bool bAnimation[3];
    std::vector<AnimTrack> Anim_S;
    std::vector<AnimTrack> Anim_R;
    std::vector<AnimTrack> Anim_T;
};

class Mat_Obj
{
public:
    float m_fElapseTick;
    Scene m_Scene;
    std::vector<Animation_Info>             m_anim_obj_List;
    std::vector<D3DXMATRIX> m_cur_mat;
public:
    void Find_curMat(float& elapsetime, int startframe,int lastframe);
    void Mat_Load(const char* mtxconvertfile);
public:

public:
    Mat_Obj();
    ~Mat_Obj();
};


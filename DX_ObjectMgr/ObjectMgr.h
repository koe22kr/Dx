#pragma once
//#include <iostream>
//#include <fstream>
#include "Skin_Obj.h"
#include "Mat_Obj.h"
#include "Render_Obj.h"

//
//struct Render_Obj
//{
//
//    //�̰� classȭ ���� ���.
//    //+ �̰� ���̴��� ���� �̰ɷ� ����.
//    //���� �����ϱ� �� ����.
//};

class ObjectMgr
{
private:
    int Load_Render_Obj(ID3D11Device* pDevice, const TCHAR* shader_file_name);
    int Load_Mat(const char* mat_file_name);
    void Load_Skin(const char* skin_file_name, int shader_index, int mat_index);

public:
    wstring texture_path=L"../../_data/obj";
    std::vector <Mat_Obj>  m_Mat_List;
    std::vector <Skin_Obj> m_Skin_List;//shader index �ɹ����� �߰��� �ε��� �޶� ���� size()����
    std::vector<Render_Obj> m_Render_Obj_List;

public:
    void Load_Cit(ID3D11Device* pDevice,const TCHAR* cit_file_name);
   

public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
public:

    ObjectMgr();
    ~ObjectMgr();
};


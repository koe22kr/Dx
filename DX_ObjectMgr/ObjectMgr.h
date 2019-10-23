#pragma once
//#include <iostream>
//#include <fstream>
#include "Skin_Obj.h"
#include "Mat_Obj.h"

struct Render_Obj
{

    //�̰� classȭ ���� ���.
    //+ �̰� ���̴��� ���� �̰ɷ� ����.
    //���� �����ϱ� �� ����.
};

class ObjectMgr
{
public:
    wstring texture_path=L"../../_data/obj";
    std::vector <Mat_Obj>  m_Mat_List;
    std::vector <Skin_Obj> m_Skin_List;//shader index �ɹ����� �߰��� �ε��� �޶� ���� size()����
    std::vector<Render_Obj> m_Render_Obj_List;

public:
    void Load_Cit(const TCHAR* cit_file_name);
    void Load_Render_Obj(const TCHAR* shader_file_name);
    void Load_Mat(const char* mat_file_name);
    void Load_Skin(const char* skin_file_name, int shader_index);

public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
public:

    ObjectMgr();
    ~ObjectMgr();
};


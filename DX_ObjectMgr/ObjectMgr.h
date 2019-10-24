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
//    //이걸 class화 할지 고민.
//    //+ 이걸 쉐이더당 만들어서 이걸로 랜더.
//    //따로 관리하기 로 하자.
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
    std::vector <Skin_Obj> m_Skin_List;//shader index 맴버변수 추가후 인덱스 달때 숫자 size()부터
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


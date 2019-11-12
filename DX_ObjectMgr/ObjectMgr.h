#pragma once
#include "Skin_Obj.h"
#include "Mat_Obj.h"
#include "Render_Obj.h"


class ObjectMgr
{
private:
    int Load_Render_Obj(ID3D11Device* pDevice, const TCHAR* shader_file_name);
    int Load_Mat(const char* mat_file_name, ID3D11Device* pDevice);
    void Load_Skin(const char* skin_file_name, int shader_index, int mat_index, ID3D11Device* pDevice);
public:
    wstring texture_path=L"../../_data/obj/";

    std::vector <Mat_Obj>  m_Mat_List;

    std::vector <Skin_Obj> m_Skin_List;

    std::vector<Render_Obj> m_Render_Obj_List;
public:
    void Load_Cit(ID3D11Device* pDevice,const TCHAR* cit_file_name);
    void Render(ID3D11DeviceContext* pContext, int iskin, float& elapsetime, int startframe, int lastframe, D3DXMATRIX* matworld, D3DXMATRIX* matview, D3DXMATRIX* matproj);
  /*  bool Init();
    bool Frame();
    bool Render();
    bool Release();*/
public:

    ObjectMgr();
    ~ObjectMgr();
};

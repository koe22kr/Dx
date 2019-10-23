#include "ObjectMgr.h"
void ObjectMgr::Load_Render_Obj(const TCHAR* shader_file_name)
{
#pragma message(TODO("구현해야함 여기 중요"))

}
void ObjectMgr::Load_Mat(const char* mat_file_name)
{
    Mat_Obj temp_mat;
    temp_mat.Mat_Load(mat_file_name);

#pragma message(TODO("이걸로 끝? 디버깅 필요"))

}
void ObjectMgr::Load_Skin(const char* skin_file_name,int shader_index)
{
    Skin_Obj temp_skin;
    temp_skin.Skin_Load(skin_file_name, texture_path.c_str());

    temp_skin.m_iMatobj_index = m_Mat_List.size() - 1; //최초 mat, 혹은 -1 ==-1일 경우 바인드 랜더
#pragma message(TODO("temp_skin.m_iMatobj_index  ==-1일 경우 바인드 랜더"))
    temp_skin.m_iShader_index = shader_index;
    
}
void ObjectMgr::Load_Cit(const TCHAR* cit_file_name)
{
    char dummy[MAX_PATH] = {0};
    int chara_count;

    char chara_name[50] = { 0 };
    int using_shader_count;
    ifstream in(cit_file_name);
    string shader_file;
    string mat_file;
    
    int total_parts_count = 0;
    int parts_count = 0;
    string parts_file;
    int using_shader_index;
    in >> dummy >> chara_count;
    for (int ichara = 0; ichara < chara_count; ichara++)
    {
        int shader_index_offset = m_Render_Obj_List.size();//이전에 넣은 갯수
        in >> dummy >> chara_name >> using_shader_count;
        for (int ishader = 0; ishader < using_shader_count; ishader++)
        {
            wstring wstr;
            in >> dummy >> shader_file;
            wstr.assign(shader_file.begin(), shader_file.end());
            Load_Render_Obj(wstr.c_str());
        }
        
        in >> dummy >> mat_file;
        Load_Mat(mat_file.c_str());

        in >> dummy >> total_parts_count;
        for (int itotal = 0; itotal < total_parts_count; itotal++)
        {
            in >> dummy >> parts_count;
            for (int iparts = 0; iparts < parts_count; iparts++)
            {
                in >> dummy >> parts_file>> using_shader_index;
                Load_Skin(parts_file.c_str(), shader_index_offset + using_shader_index);

            }
        }
    }

}

bool ObjectMgr::Init()
{
    return true;
}
bool ObjectMgr::Frame()
{
    return true;
}
bool ObjectMgr::Render()
{
    return true;
}
bool ObjectMgr::Release()
{
    return true;
}

ObjectMgr::ObjectMgr()
{
}


ObjectMgr::~ObjectMgr()
{
}

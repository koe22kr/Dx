#include "Mat_Obj.h"

void Mat_Obj::Mat_Load(const char* mtxconvertfile)
{
    int dummy;
    string dummy_str;

    string key;
    int iObj_Size;
    int iMainMtl_Size = 0;
    int iMain_Material_Index = 0;
    string Material_Name;
    int iSub_Material_Size;
    int iUse_Material_Size;
    string filename;

    wstring wfilename;
    //wstring texpath = L"../../_data/obj/";
    ifstream in(mtxconvertfile);

    in >> key >> iObj_Size;
    in >> m_Scene.iFirst_Frame >> m_Scene.iLast_Frame >> m_Scene.iFrame_Speed >> m_Scene.iTick_Per_Frame;
    if (m_Scene.iLast_Frame != 0)
    {
        m_anim_obj_List.resize(iObj_Size);
    }

    for (int imain = 0; imain < iObj_Size; imain++)
    {

        in >> m_anim_obj_List[imain].obj_name;
        in >> m_anim_obj_List[imain].parent_name;

        int sizeS, sizeR, sizeT;
        AnimTrack s_track, r_track, t_track;
        in >> dummy_str >> sizeS >> sizeR >> sizeT;
        in >> m_anim_obj_List[imain].mBox.vMin.x >> m_anim_obj_List[imain].mBox.vMin.y >> m_anim_obj_List[imain].mBox.vMin.z;
        in >> m_anim_obj_List[imain].mBox.vMax.x >> m_anim_obj_List[imain].mBox.vMax.y >> m_anim_obj_List[imain].mBox.vMax.z;
        if (m_anim_obj_List[imain].bAnimation[0])
        {
            for (int iS = 0; iS < sizeS; iS++)
            {
                in >> dummy >> s_track.i >> s_track.p.x >> s_track.p.y >> s_track.p.z >> s_track.q.x >> s_track.q.y >> s_track.q.z >> s_track.q.w;
                m_anim_obj_List[imain].Anim_S.push_back(s_track);
            }
        }
        else
        {
            in >> dummy >> s_track.i >> s_track.p.x >> s_track.p.y >> s_track.p.z >> s_track.q.x >> s_track.q.y >> s_track.q.z >> s_track.q.w;
            m_anim_obj_List[imain].Anim_S.push_back(s_track);
        }
        if (m_anim_obj_List[imain].bAnimation[1])
        {
            for (int iR = 0; iR < sizeR; iR++)
            {
                in >> dummy >> r_track.i >> r_track.q.x >> r_track.q.y >> r_track.q.z >> r_track.q.w;
                m_anim_obj_List[imain].Anim_R.push_back(r_track);
            }
        }
        else
        {
            in >> dummy >> r_track.i >> r_track.q.x >> r_track.q.y >> r_track.q.z >> r_track.q.w;
            m_anim_obj_List[imain].Anim_R.push_back(r_track);
        }
        if (m_anim_obj_List[imain].bAnimation[2])
        {
            for (int iT = 0; iT < sizeT; iT++)
            {
                in >> dummy >> t_track.i >> t_track.p.x >> t_track.p.y >> t_track.p.z;
                m_anim_obj_List[imain].Anim_T.push_back(t_track);
            }
        }
        else
        {
            in >> dummy >> t_track.i >> t_track.p.x >> t_track.p.y >> t_track.p.z;
            m_anim_obj_List[imain].Anim_T.push_back(t_track);
        }
    }
    m_cur_mat.resize(iObj_Size);
    m_szMat_File = mtxconvertfile;
}
void Mat_Obj::Find_curMat(float& elapsetime, int startframe, int lastframe)
{
    int curframe = (int)(elapsetime * m_Scene.iFrame_Speed);
    while  (curframe > lastframe)
    {
        elapsetime = 0;
        curframe -= lastframe;
    }
    for (int i = 0; i < m_cur_mat.size(); i++)
    {
        if (m_anim_obj_List[i].mat_Final_Anim_list.size() == 1)
        {
            m_cur_mat[i] = m_anim_obj_List[i].mat_Final_Anim_list[0];
        }
        else
        {
            m_cur_mat[i] = m_anim_obj_List[i].mat_Final_Anim_list[curframe];
        }
    }

}

Mat_Obj::Mat_Obj()
{
}


Mat_Obj::~Mat_Obj()
{
}

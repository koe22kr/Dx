#include "Load_Shape.h"

//HRESULT Load_Shape::CreateVertexData()
//{
//    return S_OK;
//};
//HRESULT Load_Shape::CreateIndexData()
//{
//    return S_OK;
//}
int Load_Shape::find_my_parents(int index)
{
    for (int i = 0; i < index; i++)
    {
        if (m_obj_info_List[i].obj_name == m_obj_info_List[index].parent_name)
        {
            m_obj_info_List[index].parent_index = i;
            return i;
        }
    }
    return -1;
}
bool Load_Shape::Frame()
{
    m_fElapseTick += 1.0f* g_fSecondPerFrame * m_Scene.iFrame_Speed * m_Scene.iTick_Per_Frame;
    int fEndTick = m_Scene.iLast_Frame* m_Scene.iTick_Per_Frame;
    if (m_fElapseTick >= fEndTick)
    {
        m_fElapseTick = 0.0f;
    }

    D3DXMATRIX matParent;
    D3DXMatrixIdentity(&matParent);
    for (int iObj = 0; iObj < m_obj_info_List.size(); iObj++)
    {

        if (m_obj_info_List[iObj].parent_index >= 0)
        {
            Interpolate(iObj,
                true,
                m_fElapseTick);
        }
        else
        {
            Interpolate(iObj,
                false,
                m_fElapseTick);
        }
    }

    return true;
}
void Load_Shape::Interpolate(int obj_index, bool have_parent, float tick)
{
    Animation_Info* target = &m_obj_anim_List[obj_index];


    D3DXMatrixIdentity(&target->m_matCalculation);
    AnimTrack StartTrack, EndTrack;
    D3DXQUATERNION qRotatin;
    D3DXVECTOR3 vTrans;
    //R
    if (target->Anim_R.size() > 1)
    {
        GetAnimationTrack(tick, target->Anim_R, StartTrack, EndTrack);
        float t = (tick - StartTrack.i) / (EndTrack.i - StartTrack.i);
        D3DXQuaternionSlerp(&qRotatin, &StartTrack.q, &EndTrack.q, t);
    }
    else
    {
        qRotatin = target->Anim_R[0].q;
    }
    D3DXMatrixRotationQuaternion(&target->mAnim_Rot, &qRotatin);

    //S
    if (target->Anim_S.size() > 1)
    {
        if (GetAnimationTrack(tick, target->Anim_S, StartTrack, EndTrack))
        {
            float t = (tick - StartTrack.i) / (EndTrack.i - StartTrack.i);
            D3DXQuaternionSlerp(&qRotatin, &StartTrack.q, &EndTrack.q, t);
            D3DXVec3Lerp(&vTrans, &StartTrack.p, &EndTrack.p, t);
        }
        D3DXMATRIX matScaleVector;
        D3DXMATRIX matScaleRotation, matScaleRotInverse;
        D3DXMatrixScaling(&matScaleVector, vTrans.x, vTrans.y, vTrans.z);
        D3DXMatrixRotationQuaternion(&matScaleRotation, &qRotatin);
        D3DXMatrixInverse(&matScaleRotInverse, NULL, &matScaleRotation);
        target->mAnim_Scal = matScaleRotInverse * matScaleVector * matScaleRotation;
    }
    else
    {
        D3DXMATRIX matScaleVector;
        D3DXMATRIX matScaleRotation, matScaleRotInverse;
        D3DXMatrixScaling(&matScaleVector, target->Anim_S[0].p.x, target->Anim_S[0].p.y, target->Anim_S[0].p.z);
        D3DXMatrixRotationQuaternion(&matScaleRotation, &target->Anim_S[0].q);
        D3DXMatrixInverse(&matScaleRotInverse, NULL, &matScaleRotation);
        target->mAnim_Scal = matScaleRotInverse * matScaleVector * matScaleRotation;
    }

    //T
    if (target->Anim_T.size() > 1)
    {
        if (GetAnimationTrack(
            tick, target->Anim_T, StartTrack, EndTrack))
        {
            float t = (tick - StartTrack.i) / (EndTrack.i - StartTrack.i);
            D3DXVec3Lerp(&vTrans, &StartTrack.p, &EndTrack.p, t);
        }
        D3DXMatrixTranslation(&target->mAnim_Tran, vTrans.x, vTrans.y, vTrans.z);
    }
    else
    {
        target->mAnim_Tran._41 = target->Anim_T[0].p.x;
        target->mAnim_Tran._42 = target->Anim_T[0].p.y;
        target->mAnim_Tran._43 = target->Anim_T[0].p.z;

    }

    D3DXMATRIX matAnim;
    matAnim = target->mAnim_Scal*target->mAnim_Rot;
    matAnim._41 = target->mAnim_Tran._41;
    matAnim._42 = target->mAnim_Tran._42;
    matAnim._43 = target->mAnim_Tran._43;
    //target->m_matCalculation = target->mAnim_Scal;
    //if (m_obj_info_List[obj_index].parent_index != -1)
    //{
    //    target->m_matCalculation = matAnim; /** m_obj_anim_List[m_obj_info_List[obj_index].parent_index].m_matCalculation;*/
    //    //#pragma message(TODO("need a branch 2type "))
    //}
    //else
    //{
        //#pragma message(TODO("need a branch 2type "))
    target->m_matCalculation = matAnim;// *m_obj_anim_List[obj_index].mat_world;
    //}



}
bool Load_Shape::GetAnimationTrack(float fElapseTime, std::vector<AnimTrack>& trackList, AnimTrack& StartTrack, AnimTrack& EndTrack)
{
    for (auto& track : trackList)
    {
        if (track.i > fElapseTime)
        {
            EndTrack = track;
            break;
        }
        StartTrack = track;
    }
    return true;
}
void Load_Shape::Skin_Load(const char* maxconvertfile, const TCHAR* texpath)
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
    ifstream in(maxconvertfile);

    in >> key >> iObj_Size >> iMainMtl_Size;
    m_Material_Info.resize(iMainMtl_Size);
    in >> m_Scene.iFirst_Frame >> m_Scene.iLast_Frame >> m_Scene.iFrame_Speed >> m_Scene.iTick_Per_Frame;
    if (m_Scene.iLast_Frame != 0)
    {
        m_obj_anim_List.resize(iObj_Size);

    }
    in >> iMain_Material_Index >> Material_Name >> iSub_Material_Size;

    m_obj_mtl_List.resize(iObj_Size);
    m_obj_info_List.resize(iObj_Size);

    if (iSub_Material_Size == 0)
    {
        m_Material_Info.resize(1);
        Material_Info mtl;
        Texture_Info tex;
        in >> mtl.material_name >> mtl.texture_size;
        in >> dummy >> filename;
        wfilename.assign(filename.begin(), filename.end());
        m_Tex_filename_list.push_back(wfilename);
        tex.texture_filename = wfilename;
        mtl.texture_info_list.push_back(tex);
        m_Material_Info[0].sub_material_info_list.push_back(mtl);
    }
    else
    {
        Material_Info mtl;
        for (int m = 0; m < iMainMtl_Size; m++)
        {
            for (int s = 0; s < iSub_Material_Size; s++)
            {


                Texture_Info tex;
                in >> mtl.material_name >> mtl.texture_size;
                for (int t = 0; t < mtl.texture_size; t++)
                {

                    in >> dummy >> filename;
                    wfilename.assign(filename.begin(), filename.end());
                    m_Tex_filename_list.push_back(wfilename);

                    tex.texture_filename = wfilename;
                    mtl.texture_info_list.push_back(tex);
                }
                m_Material_Info[m].sub_material_info_list.push_back(mtl);
            }
            m_Material_Info[m].material_name = Material_Name;
            m_Material_Info[m].submaterial_size = iSub_Material_Size;
            if (iMainMtl_Size > m + 1)
            {
                in >> iMain_Material_Index >> Material_Name >> iSub_Material_Size;
            }
        }
    }


    for (int imain = 0; imain < iObj_Size; imain++)
    {

        in >> m_obj_info_List[imain].obj_name;
        in >> m_obj_info_List[imain].parent_name;
        in >> dummy;
        in >> iUse_Material_Size;
        in >> m_obj_anim_List[imain].bAnimation[0] >> m_obj_anim_List[imain].bAnimation[1] >> m_obj_anim_List[imain].bAnimation[2];
        m_obj_mtl_List[imain].resize(iUse_Material_Size + 1);

        find_my_parents(imain);

      //  D3DXMATRIX matworld;
      //  in >> matworld._11 >> matworld._12 >> matworld._13 >> matworld._14;
      //  in >> matworld._21 >> matworld._22 >> matworld._23 >> matworld._24;
      //  in >> matworld._31 >> matworld._32 >> matworld._33 >> matworld._34;
      //  in >> matworld._41 >> matworld._42 >> matworld._43 >> matworld._44;
      //  D3DXMatrixInverse(&m_obj_anim_List[imain].mat_world_inv, NULL, &matworld);
      //  m_obj_anim_List[imain].mat_world = matworld;

        for (int isub_mtl = 0; isub_mtl < iUse_Material_Size; isub_mtl++)
        {

            bool have_mesh = true;
            int vertex_size;
            in >> dummy_str >> vertex_size;


            for (int ivertex = 0; ivertex < vertex_size; ivertex++)
            {
                DX::PNCT_VERTEX2 temp;
                in >> temp.p.x >> temp.p.y >> temp.p.z;
                in >> temp.n.x >> temp.n.y >> temp.n.z;
                in >> temp.c.x >> temp.c.y >> temp.c.z >> temp.c.w;
                in >> temp.t.x >> temp.t.y;

                if (temp.c.w != -1)
                {
                    m_obj_mtl_List[imain][isub_mtl].m_Vertex_List.push_back(temp);
                    have_mesh = true;
                }
                else
                {
                    m_obj_mtl_List[imain][iUse_Material_Size].m_Vertex_List.push_back(temp);
                    have_mesh = false;

                }

            }
            int index_size;
            in >> dummy_str >> index_size;
            for (int iindex = 0; iindex < index_size; iindex++)
            {
                DWORD index;
                in >> index;
                if (have_mesh)
                {
                    m_obj_mtl_List[imain][isub_mtl].m_Index_List.push_back(index);
                }
                else
                {
                    m_obj_mtl_List[imain][iUse_Material_Size].m_Index_List.push_back(index);
                }
            }

            if (m_obj_mtl_List[imain][isub_mtl].m_Vertex_List.size() > 0 &&
                m_obj_mtl_List[imain][isub_mtl].m_Vertex_List[0].c.w != -1)
            {
                //SRV
                m_obj_info_List[imain].m_my_material_index = (int)m_obj_mtl_List[imain][isub_mtl].m_Vertex_List[0].c.w;
                m_obj_info_List[imain].SRV_Index = I_TextureMgr.Load(CADevice::m_pDevice, texpath + m_Tex_filename_list[m_obj_info_List[imain].m_my_material_index]);
                m_obj_mtl_List[imain][isub_mtl].m_helper.m_pSRV = I_TextureMgr.GetPtr(m_obj_info_List[imain].SRV_Index)->m_pSRV;
            }

        }//isub_mtl end
/*
        int sizeS, sizeR, sizeT;
        AnimTrack s_track, r_track, t_track;
        in >> dummy_str >> sizeS >> sizeR >> sizeT;
        if (m_obj_anim_List[imain].bAnimation[0])
        {
            for (int iS = 0; iS < sizeS; iS++)
            {
                in >> dummy >> s_track.i >> s_track.p.x >> s_track.p.y >> s_track.p.z >> s_track.q.x >> s_track.q.y >> s_track.q.z >> s_track.q.w;
                m_obj_anim_List[imain].Anim_S.push_back(s_track);
            }
        }
        else
        {
            in >> dummy >> s_track.i >> s_track.p.x >> s_track.p.y >> s_track.p.z >> s_track.q.x >> s_track.q.y >> s_track.q.z >> s_track.q.w;
            m_obj_anim_List[imain].Anim_S.push_back(s_track);
        }
        if (m_obj_anim_List[imain].bAnimation[1])
        {
            for (int iR = 0; iR < sizeR; iR++)
            {
                in >> dummy >> r_track.i >> r_track.q.x >> r_track.q.y >> r_track.q.z >> r_track.q.w;
                m_obj_anim_List[imain].Anim_R.push_back(r_track);
            }
        }
        else
        {
            in >> dummy >> r_track.i >> r_track.q.x >> r_track.q.y >> r_track.q.z >> r_track.q.w;
            m_obj_anim_List[imain].Anim_R.push_back(r_track);
        }
        if (m_obj_anim_List[imain].bAnimation[2])
        {
            for (int iT = 0; iT < sizeT; iT++)
            {
                in >> dummy >> t_track.i >> t_track.p.x >> t_track.p.y >> t_track.p.z;
                m_obj_anim_List[imain].Anim_T.push_back(t_track);
            }
        }
        else
        {
            in >> dummy >> t_track.i >> t_track.p.x >> t_track.p.y >> t_track.p.z;
            m_obj_anim_List[imain].Anim_T.push_back(t_track);
        }*/
    }

}
Load_Shape::Load_Shape()
{
}
Load_Shape::~Load_Shape()
{
}

void  Load_Shape::LoaderSetMatrix(D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
    for (auto j = 0; j < m_obj_mtl_List.size(); j++)
    {

        for (int i = 0; i < m_obj_mtl_List[j].size(); i++)
        {
           // m_obj_mtl_List[j][i].SetMatrix(&m_obj_anim_List[j].m_matCalculation, pView, pProj);
        }
    }
}
void  Load_Shape::LoaderCreate(ID3D11Device* pd3dDevice, const TCHAR* pLoadShaderFile, const TCHAR* pLoadTextureFile)
{
    for (auto j = 0; j < m_obj_mtl_List.size(); j++)
    {
        for (int i = 0; i < m_obj_mtl_List[j].size(); i++)
        {
           
            if (i != m_obj_mtl_List[j].size() - 1)
            {
                //쉐이더 나누게 되면 여기서 멤버로 쉐이더 이름 가지고 그걸로 로드?
                m_obj_mtl_List[j][i].Create(pd3dDevice, pLoadShaderFile, pLoadTextureFile);
            }
            else
            {
                m_obj_mtl_List[j][i].Create(pd3dDevice, L"color.hlsl", pLoadTextureFile);
            }
        }
    }
}
void  Load_Shape::LoaderRender(ID3D11DeviceContext* pContext, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
    for (auto j = 0; j < m_obj_mtl_List.size(); j++)
    {
        for (int i = 0; i < m_obj_mtl_List[j].size(); i++)
        {
            m_obj_mtl_List[j][i].SetMatrix(&m_obj_anim_List[j].m_matCalculation, pView, pProj);
            m_obj_mtl_List[j][i].Render(pContext);
        }
    }

} 
//pContext->PSSetShaderResources(0, 1, m_helper.m_pSRV.GetAddressOf());
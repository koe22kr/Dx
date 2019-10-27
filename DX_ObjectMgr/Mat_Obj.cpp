#include "Mat_Obj.h"

void Mat_Obj::Mat_Load(const char* mtxconvertfile, ID3D11Device* pDevice)
{
    int dummy;
    string dummy_str;

    string key;
    int iObj_Size;
    int iMainMtl_Size = 0;
    //int iMain_Material_Index = 0;
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
       // if (sizeS > 1)
        {
            for (int iS = 0; iS < sizeS; iS++)
            {
                in >> dummy >> s_track.i >> s_track.p.x >> s_track.p.y >> s_track.p.z >> s_track.q.x >> s_track.q.y >> s_track.q.z >> s_track.q.w;
                m_anim_obj_List[imain].Anim_S.push_back(s_track);
            }
        }
       /* else
        {
            in >> dummy >> s_track.i >> s_track.p.x >> s_track.p.y >> s_track.p.z >> s_track.q.x >> s_track.q.y >> s_track.q.z >> s_track.q.w;
            m_anim_obj_List[imain].Anim_S.push_back(s_track);
        }*/
       // if (sizeR > 1)
        {
            for (int iR = 0; iR < sizeR; iR++)
            {
                in >> dummy >> r_track.i >> r_track.q.x >> r_track.q.y >> r_track.q.z >> r_track.q.w;
                m_anim_obj_List[imain].Anim_R.push_back(r_track);
            }
        }
       /* else
        {
            in >> dummy >> r_track.i >> r_track.q.x >> r_track.q.y >> r_track.q.z >> r_track.q.w;
            m_anim_obj_List[imain].Anim_R.push_back(r_track);
        }*/
        //if (sizeT >1)
        {
            for (int iT = 0; iT < sizeT; iT++)
            {
                in >> dummy >> t_track.i >> t_track.p.x >> t_track.p.y >> t_track.p.z;
                m_anim_obj_List[imain].Anim_T.push_back(t_track);
            }
        }
        /*else
        {
            in >> dummy >> t_track.i >> t_track.p.x >> t_track.p.y >> t_track.p.z;
            m_anim_obj_List[imain].Anim_T.push_back(t_track);
        }*/
    }
    m_cur_mat.resize(iObj_Size);
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    bd.ByteWidth = iObj_Size * sizeof(D3DXMATRIX);
    bd.Usage = D3D11_USAGE_DEFAULT;
    pDevice->CreateBuffer(&bd, NULL, &m_Cur_Mat_Buffer);

    D3D11_SHADER_RESOURCE_VIEW_DESC vd;
    ZeroMemory(&vd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    vd.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    vd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
    vd.Buffer.ElementOffset = 0;
    vd.Buffer.ElementWidth = iObj_Size * 4; //RGBA32 *4 = MAT
    pDevice->CreateShaderResourceView(m_Cur_Mat_Buffer, &vd, &m_Cur_Mat_SRV);

    m_szMat_File = mtxconvertfile;
    
}
void Mat_Obj::Interpolate()
{
    for (int iobj = 0; iobj < m_anim_obj_List.size(); iobj++)
    {
        Animation_Info* target = &m_anim_obj_List[iobj];
       
        for (int iframe = m_Scene.iFirst_Frame; iframe < m_Scene.iLast_Frame; iframe++)
        {
            D3DXMATRIX mat;
            D3DXMatrixIdentity(&mat);

            D3DXMATRIX Rot;
            D3DXMATRIX Scale;
            D3DXMATRIX Tran;
            D3DXMatrixIdentity(&Tran);
            if (target->Anim_R.size() > 1)
            {
                D3DXMatrixRotationQuaternion(&Rot, &target->Anim_R[iframe].q);
            }
            else
            {
                D3DXMatrixRotationQuaternion(&Rot, &target->Anim_R[0].q);
            }

            if (target->Anim_S.size() > 1)
            {
                D3DXMATRIX matScaleVector;
                D3DXMATRIX matScaleRotation, matScaleRotInverse;
                D3DXMatrixScaling(&matScaleVector, target->Anim_S[iframe].p.x, target->Anim_S[iframe].p.y, target->Anim_S[iframe].p.z);
                D3DXMatrixRotationQuaternion(&matScaleRotation, &target->Anim_S[iframe].q);
                D3DXMatrixInverse(&matScaleRotInverse, NULL, &matScaleRotation);
                Scale = matScaleRotInverse * matScaleVector * matScaleRotation;
            }
            else
            {
                D3DXMATRIX matScaleVector;
                D3DXMATRIX matScaleRotation, matScaleRotInverse;
                D3DXMatrixScaling(&matScaleVector, target->Anim_S[0].p.x, target->Anim_S[0].p.y, target->Anim_S[0].p.z);
                D3DXMatrixRotationQuaternion(&matScaleRotation, &target->Anim_S[0].q);
                D3DXMatrixInverse(&matScaleRotInverse, NULL, &matScaleRotation);
                Scale = matScaleRotInverse * matScaleVector * matScaleRotation;
            }
            if (target->Anim_T.size() > 1)
            {
               Tran._41 = target->Anim_T[iframe].p.x;
               Tran._42 = target->Anim_T[iframe].p.y;
               Tran._43 = target->Anim_T[iframe].p.z;
            }
            else
            {
                Tran._41 = target->Anim_T[0].p.x;
                Tran._42 = target->Anim_T[0].p.y;
                Tran._43 = target->Anim_T[0].p.z;
            }

            mat = Scale * Rot;
            mat._41 = Tran._41;
            mat._42 = Tran._42;
            mat._43 = Tran._43;
            m_anim_obj_List[iobj].mat_Final_Anim_list.push_back(mat);
        }

    }
}

void Mat_Obj::Find_curMat(float& elapsetime, int startframe, int lastframe)
{
    int curframe = (int)(elapsetime * m_Scene.iFrame_Speed);
    while  (curframe >= lastframe)
    {
        elapsetime = 0;
        curframe -= lastframe;
    }
    for (int i = 0; i < m_cur_mat.size(); i++)
    {
        if (m_anim_obj_List[i].mat_Final_Anim_list.size() == 1)
        {
            m_cur_mat[i] = m_anim_obj_List[i].mat_Final_Anim_list[0];
            //
        }
        else
        {
            m_cur_mat[i] = m_anim_obj_List[i].mat_Final_Anim_list[curframe];
            //
        }
    }
    

}

void Mat_Obj::Update_Render_Mat(ID3D11DeviceContext* pContext)
{
    pContext->UpdateSubresource(m_Cur_Mat_Buffer, 0, NULL, &m_cur_mat.at(0), 0, 0);
    
}

void Mat_Obj::Release()
{
    if (m_Cur_Mat_Buffer)
    {
        m_Cur_Mat_Buffer->Release();
    }
    if (m_Cur_Mat_SRV)
    {
        m_Cur_Mat_SRV->Release();
    }
}

Mat_Obj::Mat_Obj()
{
    m_Cur_Mat_Buffer = NULL;
    m_Cur_Mat_SRV = NULL;
}


Mat_Obj::~Mat_Obj()
{
}

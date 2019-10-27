#include "Skin_Obj.h"

int Skin_Obj::Get_obj_size()
{
    return m_obj_mtl_List.size();
}
int Skin_Obj::Get_mtl_size(int iobj)
{
    return m_obj_mtl_List[iobj].size();
}

int Skin_Obj::Get_Render_Obj_index()
{
    return m_iShader_index;
}
int Skin_Obj::Get_Mat_index()
{
    return m_iMat_index;
}
Sorted_Vertex_by_Texture* Skin_Obj::Get(int iobj, int imtl)
{
    return &m_obj_mtl_List[iobj][imtl];
}

//
//void Skin_Obj::Render(ID3D11DeviceContext* pContext)
//{
//    m_obj_mtl_List
//}

void Skin_Obj::Skin_Load(const char* maxconvertfile, const TCHAR* texpath, ID3D11Device* pDevice)
{
    int dummy;
    float dummyfloat;
    string dummy_str;

    string key;
    int iObj_Size;
    int iMainMtl_Size = 0;
   /* int iMain_Material_Index = 0;*/
    string Material_Name;
    int iSub_Material_Size;
    int iUse_Material_Size;
    string filename;

    wstring wfilename;
    //wstring texpath = L"../../_data/obj/";
    ifstream in(maxconvertfile);

    in >> key >> iObj_Size >> iMainMtl_Size;
    m_Material_Info.resize(iMainMtl_Size);
    in /*>> iMain_Material_Index*/ >> Material_Name >> iSub_Material_Size;

    m_obj_mtl_List.resize(iObj_Size);
    m_Obj_Info_List.resize(iObj_Size);

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
                in /*>> iMain_Material_Index*/ >> Material_Name >> iSub_Material_Size;
            }
        }
    }


    for (int iobj = 0; iobj < iObj_Size; iobj++)
    {

        in >> m_Obj_Info_List[iobj].obj_name;
        in >> m_Obj_Info_List[iobj].parent_name;
        in >> dummy;
        in >> iUse_Material_Size;
        m_obj_mtl_List[iobj].resize(iUse_Material_Size + 1);


        for (int isub_mtl = 0; isub_mtl < iUse_Material_Size; isub_mtl++)
        {

            bool have_mesh = true;
            int vertex_size;
            in >> dummy_str >> vertex_size;


            for (int ivertex = 0; ivertex < vertex_size; ivertex++)
            {
                PNCTI4W4 temp;
                //ZeroMemory(&temp, sizeof(temp));
                in >> temp.p.x >> temp.p.y >> temp.p.z;
                in >> temp.n.x >> temp.n.y >> temp.n.z;
                in >> temp.c.x >> temp.c.y >> temp.c.z >> temp.c.w;
                in >> temp.t.x >> temp.t.y;
                in >> temp.i.x >> temp.i.y >> temp.i.z >> temp.i.w;
                in >> dummy >> dummy >> dummy >> dummy;
                in >> temp.w.x >> temp.w.y >> temp.w.z >> temp.w.w;
                in >> dummyfloat >> dummyfloat >> dummyfloat >> dummyfloat;



                if (temp.c.w != -1)
                {
                    m_obj_mtl_List[iobj][isub_mtl].m_Vertex_List.push_back(temp);
                    have_mesh = true;
                }
                else
                {
                    m_obj_mtl_List[iobj][iUse_Material_Size].m_Vertex_List.push_back(temp);
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
                    m_obj_mtl_List[iobj][isub_mtl].m_Index_List.push_back(index);
                }
                else
                {
                    m_obj_mtl_List[iobj][iUse_Material_Size].m_Index_List.push_back(index);
                }
            }

            if (m_obj_mtl_List[iobj][isub_mtl].m_Vertex_List.size() > 0)
            {
                HRESULT hr;
                //VB IB
                D3D11_BUFFER_DESC bd;
                ZeroMemory(&bd, sizeof(bd));
                bd.ByteWidth = sizeof(PNCTI4W4)*m_obj_mtl_List[iobj][isub_mtl].m_Vertex_List.size();
                bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                bd.CPUAccessFlags = 0;
                bd.Usage = D3D11_USAGE_DEFAULT;
                D3D11_SUBRESOURCE_DATA sd;
                ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
                sd.pSysMem = &m_obj_mtl_List[iobj][isub_mtl].m_Vertex_List.at(0);
                if (FAILED(hr = pDevice->CreateBuffer(&bd, &sd, &m_obj_mtl_List[iobj][isub_mtl].VB)))
                {
                    MessageBox(NULL, L"Skin_obj_VB_fail", L"Skin_obj_VB_fail", S_OK);
                }

                bd.ByteWidth = sizeof(DWORD)*m_obj_mtl_List[iobj][isub_mtl].m_Index_List.size();
                bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
                sd.pSysMem = &m_obj_mtl_List[iobj][isub_mtl].m_Index_List.at(0);
                if (FAILED(hr = pDevice->CreateBuffer(&bd, &sd, &m_obj_mtl_List[iobj][isub_mtl].IB)))
                {
                    MessageBox(NULL, L"Skin_obj_IB_fail", L"Skin_obj_IB_fail", S_OK);
                }
                if (m_obj_mtl_List[iobj][isub_mtl].m_Vertex_List[0].c.w != -1)
                {
                    //SRV
                    int texture_index = (int)m_obj_mtl_List[iobj][isub_mtl].m_Vertex_List[0].c.w;
                    m_Obj_Info_List[iobj].SRV_Index = I_TextureMgr.Load(CADevice::m_pDevice, texpath + m_Tex_filename_list[texture_index]);
                    m_obj_mtl_List[iobj][isub_mtl].m_pSRV = I_TextureMgr.GetPtr(m_Obj_Info_List[iobj].SRV_Index)->m_pSRV;
                }

                
            }

        }//isub_mtl end
    }
//    pDevice->CreateBuffer(,NULL,)
}


Skin_Obj::Skin_Obj()
{
}


Skin_Obj::~Skin_Obj()
{
}

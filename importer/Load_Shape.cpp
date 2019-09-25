#include "Load_Shape.h"

HRESULT Load_Shape::CreateVertexData()
{

    return S_OK;
};
HRESULT Load_Shape::CreateIndexData()
{
    m_helper.m_iNumIndex = m_Index_List.size();
    return S_OK;
    
}

void Load_Shape::Load(const char* maxconvertfile)
{
    string name;

    string obj;

    int iNumFace = 0;
    int iNumTexture = 0;
    int iNumVertexinFace = 2;
    int iNumTexture_Index = 0;
    int iNumIndex = 0;
    int iIndex_data = 0;
    string filename;
    wstring wfilename;

    ifstream in(maxconvertfile);

    getline(in, name);
    in >> obj;
    in >> iNumFace;
    in >> iNumTexture;
    for (int i = 0; i < iNumTexture; i++)
    {
        in >> iNumTexture_Index;
        in >> filename;
        wfilename.assign(filename.begin(), filename.end());
        m_filename_map[iNumTexture_Index] = wfilename;

        filename.clear();
        iNumTexture_Index = 0;
    }

    DX::PNCT_VERTEX2 temp;
    for (int i = 0; i < iNumFace*iNumVertexinFace; i++)
    {
        in >> temp.p.x >> temp.p.y >> temp.p.z;
        in >> temp.n.x >> temp.n.y >> temp.n.z;
        in >> temp.c.x >> temp.c.y >> temp.c.z >> temp.c.w;
        in >> temp.t.x >> temp.t.y;

        //find if temp -    m_pnct_list;
        m_Vertex_List.push_back(temp);


    }
    in >> iNumIndex;
   
    for (int a = 0; a < iNumIndex; a++)
    {
        in >> iIndex_data;
        m_Index_List.push_back(iIndex_data);
    }
    getline(in, name);
    in.close();
    int a = 0;
    //return &m_pnct_List;
}
Load_Shape::Load_Shape()
{
}


Load_Shape::~Load_Shape()
{
}

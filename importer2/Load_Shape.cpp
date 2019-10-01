#include "Load_Shape.h"

HRESULT Load_Shape::CreateVertexData()
{

    return S_OK;
};
HRESULT Load_Shape::CreateIndexData()
{
    //m_helper.m_iNumIndex = m_Index_List.size();
    return S_OK;
    
}
void Load_Shape::Load(const char* maxconvertfile)
{
    string name;
    int iMain_Material_Num = 0;
    string Main_Material_name;
    UINT nNum_Sub_Material;
    

    string obj;
    string parent;
    int dummy;
    UINT nobj_material_size;
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
    in >> iMain_Material_Num >> Main_Material_name >> nNum_Sub_Material;

    for (int i = 0; i < nNum_Sub_Material; i++)
    {
        Material mtl;
        in >> mtl.material_name >> mtl.imaterial_size >> mtl.imaterial_index >> mtl.texturefilename;
        m_Material_List.push_back(mtl);
    }
    in >> obj;
    in >> parent;
    in >> dummy;
    in >> nobj_material_size;
    
    DirectX::XMFLOAT4X4 matworld;
    in >> matworld._11 >> matworld._12 >> matworld._13 >> matworld._14;
    in >> matworld._21 >> matworld._22 >> matworld._23 >> matworld._24;
    in >> matworld._31 >> matworld._32 >> matworld._33 >> matworld._34;
    in >> matworld._41 >> matworld._42 >> matworld._43 >> matworld._44;
    m_matWorld = DirectX::XMLoadFloat4x4(&matworld);
    string dummy_str;
    int vertex_size;
    int index_size;
    m_VertexList_List.resize(nobj_material_size);
    m_IndexList_List.resize(nobj_material_size);
    for (int counter = 0; counter < nobj_material_size; counter++)
    {
        in >> dummy_str >> vertex_size;
        
        for (int ivertex = 0; ivertex < vertex_size; ivertex++)
        {
            DX::PNCT_VERTEX2 temp;
            in >> temp.p.x >> temp.p.y >> temp.p.z;
            in >> temp.n.x >> temp.n.y >> temp.n.z;
            in >> temp.c.x >> temp.c.y >> temp.c.z >> temp.c.w;
            in >> temp.t.x >> temp.t.y;
            m_VertexList_List[counter].push_back(temp);
        }
        in >> dummy_str >> index_size;
        for (int iindex = 0; iindex < index_size; iindex++)
        {
            DWORD index;
           /* for(int i=0;i<3;i++)
            {*/
                in >> index;
                m_IndexList_List[counter].push_back(index);
            //}
            
            
        }
    }

    //Debug 원시 데이터//
    in >> dummy_str;
    for (int ivertex = 0; ivertex < 12473; ivertex++)
    {
        DX::PNCT_VERTEX2 temp;
        in >> temp.p.x >> temp.p.y >> temp.p.z;
        in >> temp.n.x >> temp.n.y >> temp.n.z;
        in >> temp.c.x >> temp.c.y >> temp.c.z >> temp.c.w;
        in >> temp.t.x >> temp.t.y;
        tester.push_back(temp);
    }

   

#ifdef Use_Origin
    m_helper.m_iNumIndex = 0;
    m_Vertex_List = tester;

#else
    m_Index_List = m_IndexList_List[0];
    m_Vertex_List = m_VertexList_List[0];
    m_Texture_Count = m_Render_Count = nobj_material_size;

#endif // DEBUG
    //in >> iNumFace;
    //in >> iNumTexture;
    //for (int i = 0; i < iNumTexture; i++)
    //{
    //    in >> iNumTexture_Index;
    //    in >> filename;
    //    wfilename.assign(filename.begin(), filename.end());
    //    m_filename_map[iNumTexture_Index] = wfilename;
    //
    //    filename.clear();
    //    iNumTexture_Index = 0;
    //}

    //DX::PNCT_VERTEX2 temp;
    //for (int i = 0; i < iNumFace; i++)
    //{
    //    in >> temp.p.x >> temp.p.y >> temp.p.z;
    //    in >> temp.n.x >> temp.n.y >> temp.n.z;
    //    in >> temp.c.x >> temp.c.y >> temp.c.z >> temp.c.w;
    //    in >> temp.t.x >> temp.t.y;

    //    //find if temp -    m_pnct_list;
    //    m_Vertex_List.push_back(temp);


    //}
    //in >> iNumIndex;
   
    //for (int a = 0; a < iNumIndex; a++)
    //{
    //    in >> iIndex_data;
    //    m_Index_List.push_back(iIndex_data);
    //}
    //getline(in, name);
    //in.close();
    //int a = 0;
    //return &m_pnct_List;
}
Load_Shape::Load_Shape()
{
}


Load_Shape::~Load_Shape()
{
}

#ifdef Use_Origin


#else


bool Load_Shape::PostRender(
    ID3D11DeviceContext* pContext, UINT iCount)
{
    for (int i = 0; i < m_Render_Count; i++)
    {

        if (m_Material_List[i].SRV_Index >= 0)
        {
            m_helper.m_pSRV = I_TextureMgr.GetPtr(m_Material_List[i].SRV_Index)->m_pSRV;
        }
        pContext->PSSetShaderResources(0, 1, m_helper.m_pSRV.GetAddressOf());
        //PSSetShaderResources

        pContext->UpdateSubresource(
            m_helper.m_pIndexBuffer.Get(),
            0, NULL, &m_IndexList_List[i], 0, 0);
        pContext->UpdateSubresource(
            m_helper.m_pVertexBuffer.Get(),
            0, NULL, &m_VertexList_List[i].at(0), 0, 0);

        if (iCount == 0) iCount = m_IndexList_List[i].size();
        if (iCount != 0)
            pContext->DrawIndexed(iCount, i, 0);
        else
            pContext->Draw(m_VertexList_List[i].size(), 0);
    }
    return true;
}

bool Load_Shape::PostRender(
    ID3D11DeviceContext* pContext)
{
    for (int i = 0; i < m_Render_Count; i++)
    {
        if (m_Material_List[i].SRV_Index >= 0)
        {
            m_helper.m_pSRV = I_TextureMgr.GetPtr(m_Material_List[i].SRV_Index)->m_pSRV;
        }
        pContext->PSSetShaderResources(0, 1, m_helper.m_pSRV.GetAddressOf());
        //PSSetShaderResources

        /*pContext->UpdateSubresource(
            m_helper.m_pIndexBuffer.Get(),
            0, NULL, &m_IndexList_List[i].at(0), 0, 0);
        pContext->UpdateSubresource(
            m_helper.m_pVertexBuffer.Get(),
            0, NULL, &m_VertexList_List[i].at(0), 0, 0);*/
        


        int iCount = m_IndexList_List[i].size();
        if (iCount != 0)
            pContext->DrawIndexed(iCount, i, 0);
        else
            pContext->Draw(m_VertexList_List[i].size(), 0);
    }
    return true;
}
void Load_Shape::LoadTextureIndex(const TCHAR* pLoadTextureFile)
{
    if (pLoadTextureFile == nullptr) return;
    int iIndex = I_TextureMgr.Load(
        m_pDevice,
        pLoadTextureFile);
    if (iIndex >= 0)
    {
        m_helper.m_pSRV = I_TextureMgr.GetPtr(iIndex)->m_pSRV;
    }

}
HRESULT Load_Shape::LoadTextures(ID3D11Device* pd3dDevice, const TCHAR* pLoadTextureFile)
{
    Costom_LoadTexture();

    return S_OK;


}
bool Load_Shape::Costom_LoadTexture()
{
    for (int i = 0; i < m_Material_List.size(); i++)
    {
        wstring wfilename;
        wfilename.assign(m_Material_List[i].texturefilename.begin(), m_Material_List[i].texturefilename.end());

        m_Material_List[i].SRV_Index = I_TextureMgr.Load(
            m_pDevice,
            wfilename);

        //if (m_Material_List[i].SRV_Index >= 0)
        //{
        //    m_helper.m_pSRV = I_TextureMgr.GetPtr(m_Material_List[i].SRV_Index)->m_pSRV;
        //}

    }

    return true;
}

#endif // Use_Origin

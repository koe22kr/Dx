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
    string key;
    int iObj_Size;
    string name;
    int iMain_Material_Num = 0;
  //  string Main_Material_name;
    UINT nNum_Sub_Material;
    int use_material_size;
    string obj;
    string parent;
    int dummy;
    string dummy_str;
    int vertex_size;
    //UINT obj_size;
    int iNumFace = 0;
    int iNumTexture = 0;
    int iNumVertexinFace = 2;
    int iNumTexture_Index = 0;
    int iNumIndex = 0;
    int iIndex_data = 0;
    wstring wfilename;
    
    ifstream in(maxconvertfile);

    in >> key >> iObj_Size;
    
    
        in >> iMain_Material_Num >> m_Material_Info.material_name >> nNum_Sub_Material;
        m_Material_Info.submaterial_size = nNum_Sub_Material;
        m_obj_mtl_List.resize(iObj_Size);
        for (int i = 0; i < nNum_Sub_Material; i++)
        {

                Material_Info mtl;
                Texture_Info tex;
                in >> mtl.material_name >> mtl.texture_size;
                for (int j = 0; j < mtl.texture_size; j++)
                {
                    string filename;

                    in >> dummy >> filename;
                    wfilename.assign(filename.begin(), filename.end());
                    m_filename_list.push_back(wfilename);
                   // m_filename_index_map.insert( make_pair(wfilename, I_TextureMgr.Load(m_pDevice, wfilename)));

                    tex.texture_filename = wfilename;
                   mtl.texture_info_list.push_back(tex);
                }
                m_Material_Info.sub_material_info_list.push_back(mtl);
        }
        for (int imain = 0; imain < iObj_Size; imain++)
        {

            in >> obj;
            in >> parent;
            in >> dummy;
            in >> use_material_size;
            m_obj_mtl_List[imain].resize(use_material_size + 1);

            DirectX::XMFLOAT4X4 matworld;
            in >> matworld._11 >> matworld._12 >> matworld._13 >> matworld._14;
            in >> matworld._21 >> matworld._22 >> matworld._23 >> matworld._24;
            in >> matworld._31 >> matworld._32 >> matworld._33 >> matworld._34;
            in >> matworld._41 >> matworld._42 >> matworld._43 >> matworld._44;

            for (int isub_mtl = 0; isub_mtl < use_material_size; isub_mtl++)
            {
                m_obj_mtl_List[imain][isub_mtl].m_matWorld = DirectX::XMLoadFloat4x4(&matworld);


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
                            m_obj_mtl_List[imain][use_material_size].m_Vertex_List.push_back(temp);
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
                            m_obj_mtl_List[imain][use_material_size].m_Index_List.push_back(index);

                        }
                    }
                   

                    if (m_obj_mtl_List[imain][isub_mtl].m_Vertex_List.size()>0&&
                        m_obj_mtl_List[imain][isub_mtl].m_Vertex_List[0].c.w != -1)
                    {


                        m_obj_mtl_List[imain][isub_mtl].m_my_material_index = m_obj_mtl_List[imain][isub_mtl].m_Vertex_List[0].c.w;
                        m_obj_mtl_List[imain][isub_mtl].SRV_Index = I_TextureMgr.Load(CADevice::m_pDevice, m_filename_list[m_obj_mtl_List[imain][isub_mtl].m_my_material_index]);
                        m_obj_mtl_List[imain][isub_mtl].m_helper.m_pSRV = I_TextureMgr.GetPtr(m_obj_mtl_List[imain][isub_mtl].SRV_Index)->m_pSRV;
                    }

                //수정필
               
            }
    }
    //애니 추가.
    

}
Load_Shape::Load_Shape()
{
}


Load_Shape::~Load_Shape()
{
}

void  Load_Shape::LoaderCreate(ID3D11Device* pd3dDevice,
    const TCHAR* pLoadShaderFile,
    const TCHAR* pLoadTextureFile)
{
    for (auto j = 0; j < m_obj_mtl_List.size(); j++)
    {
        for (int i = 0; i < m_obj_mtl_List[j].size(); i++)
        {

            if (i != m_obj_mtl_List[j].size()-1)
            {
                //쉐이더 나누게 되면 여기서 멤버로 쉐이더 이름 가지고 그걸로 로드?
                m_obj_mtl_List[j][i].Create(pd3dDevice, pLoadShaderFile, pLoadTextureFile);
            }
            else
            {
                m_obj_mtl_List[j][i].Create(pd3dDevice,L"color.hlsl", pLoadTextureFile);

            }
        }

    }
}
void  Load_Shape::LoaderSetMatrix(D3DXMATRIX* pWorld,
    D3DXMATRIX* pView,
    D3DXMATRIX* pProj)
{
   for (auto j = 0; j < m_obj_mtl_List.size(); j++)
   {
       for (int i = 0; i < m_obj_mtl_List[j].size(); i++)
       {
           //쉐이더 나누게 되면 여기서 멤버로 쉐이더 이름 가지고 그걸로 로드?
   
          // m_obj_mtl_List[j][i].m_cb.matWorld = m_matWorld;
           m_obj_mtl_List[j][i].SetMatrix((D3DXMATRIX*)&m_obj_mtl_List[j][i].m_matWorld, pView, pProj);
   
       }
   }
}
void  Load_Shape::LoaderRender(ID3D11DeviceContext* pContext)
{
    for (auto j =0; j<m_obj_mtl_List.size();j++)
    {

        for (int i = 0; i < m_obj_mtl_List[j].size(); i++)
        {
          
            //pContext->PSSetShaderResources(0, 1, m_helper.m_pSRV.GetAddressOf());

            //쉐이더 나누게 되면 여기서 멤버로 쉐이더 이름 가지고 그걸로 로드?
            m_obj_mtl_List[j][i].Render(pContext);

        }
    }

}
//bool Load_Shape::PostRender(
//    ID3D11DeviceContext* pContext, UINT iCount)
//{
//    {
//
//        if (m_Material_Info[i].SRV_Index >= 0)
//        {
//            m_helper.m_pSRV = I_TextureMgr.GetPtr(m_Material_Info[i].SRV_Index)->m_pSRV;
//        }
//        pContext->PSSetShaderResources(0, 1, m_helper.m_pSRV.GetAddressOf());
//        //PSSetShaderResources
//
//        pContext->UpdateSubresource(
//            m_helper.m_pIndexBuffer.Get(),
//            0, NULL, &m_IndexList_List[i], 0, 0);
//        pContext->UpdateSubresource(
//            m_helper.m_pVertexBuffer.Get(),
//            0, NULL, &m_VertexList_List[i].at(0), 0, 0);
//
//        if (iCount == 0) iCount = m_IndexList_List[i].size();
//        if (iCount != 0)
//            pContext->DrawIndexed(iCount, 0, 0);
//        else
//            pContext->Draw(m_VertexList_List[i].size(), 0);
//    }
//    return true;
//}
//
//bool Load_Shape::PostRender(
//    ID3D11DeviceContext* pContext)
//{
//    {
//        if (m_Material_Info[i].SRV_Index >= 0)
//        {
//            m_helper.m_pSRV = I_TextureMgr.GetPtr(m_Material_Info[i].SRV_Index)->m_pSRV;
//        }
//        pContext->PSSetShaderResources(0, 1, m_helper.m_pSRV.GetAddressOf());
//      
//
//
//        int iCount = m_IndexList_List[i].size();
//        if (iCount != 0)
//            pContext->DrawIndexed(iCount, 0, 0);
//        else
//            pContext->Draw(m_VertexList_List[i].size(), 0);
//    }
//    return true;
//}
void Load_Shape::LoadTextureIndex(const TCHAR* pLoadTextureFile)
{
    if (pLoadTextureFile == nullptr) return;
    int iIndex = I_TextureMgr.Load(
        CADevice::m_pDevice,
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
   //for (int i = 0; i < m_Material_Info.size(); i++)
   //{
   //    for (int j = 0; j < m_Material_Info[i].texture_info_list.size(); j++)
   //    {
   //      
   //
   //     /*   m_Material_Info[i].texture_info_list[j].SRV_Index = I_TextureMgr.Load(
   //            m_pDevice,
   //            m_Material_Info[i].texture_info_list[j].texture_filename.c_str());*/
   //    }
        //if (m_Material_Info[i].SRV_Index >= 0)
        //{
        //    m_helper.m_pSRV = I_TextureMgr.GetPtr(m_Material_Info[i].SRV_Index)->m_pSRV;
        //}

    //}

    return true;
}


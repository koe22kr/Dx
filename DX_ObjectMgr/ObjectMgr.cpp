#include "ObjectMgr.h"

void ObjectMgr::Render(ID3D11DeviceContext* pContext,int iskin,float& elapsetime, int startframe, int lastframe, D3DXMATRIX* matworld, D3DXMATRIX* matview, D3DXMATRIX* matproj)
{
    
    //for (int iskin = 0; iskin < m_Skin_List.size(); iskin++)//이건 모두다 render
    {
        Render_Obj* pRO = &m_Render_Obj_List[m_Skin_List[iskin].Get_Render_Obj_index()];
        pRO->m_cb.etc[0] = 0;
        pRO->m_cb.etc[1] = 0;
        pRO->m_cb.etc[2] = 0;
        pRO->m_cb.etc[3] = 0;
        pRO->SetMatrix(matworld, matview, matproj);
        pContext->UpdateSubresource(pRO->m_helper.m_pConstantBuffer.Get(), 0, NULL, &pRO->m_cb, 0, 0);
        Mat_Obj* pMO = &m_Mat_List[m_Skin_List[iskin].Get_Mat_index()];
        pMO->Find_curMat(elapsetime, startframe, lastframe);
        pMO->Update_Render_Mat(pContext);//상수버퍼 set은 여기서
        //pContext->VSSetConstantBuffers(2,1,&pMO->m_Cur_Mat_Buffer);
        //pContext->VSSetShaderResources(2, 1, &pMO->m_Cur_Mat_SRV);
        for (int iobj = 0; iobj < m_Skin_List[iskin].Get_obj_size(); iobj++)
        {
            for (int imtl = 0; imtl < m_Skin_List[iskin].m_obj_mtl_List[iobj].size(); imtl++)
            {
                if (m_Skin_List[iskin].m_obj_mtl_List[iobj][imtl].m_Index_List.size() > 0)
                {
                    pContext->IASetInputLayout(pRO->m_helper.m_pInputLayout.Get());
                    UINT offset = 0;
                    UINT stride = sizeof(m_Skin_List[iskin].m_obj_mtl_List[iobj][imtl].m_Vertex_List[0]);
                    pContext->IASetVertexBuffers(0, 1, &m_Skin_List[iskin].m_obj_mtl_List[iobj][imtl].VB, &stride, &offset);
                    pContext->IASetIndexBuffer(m_Skin_List[iskin].m_obj_mtl_List[iobj][imtl].IB, DXGI_FORMAT_R32_UINT, 0);
                    pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                    pContext->VSSetShader(pRO->m_helper.m_pVertexShader.Get(), NULL, 0);
                    pContext->PSSetShader(pRO->m_helper.m_pPixelShader.Get(), NULL, 0);
                    pContext->PSSetShaderResources(0, 1, &m_Skin_List[iskin].m_obj_mtl_List[iobj][imtl].m_pSRV);
                    int a = m_Skin_List[iskin].m_obj_mtl_List[iobj][imtl].m_Index_List.size();
                    //pContext->Draw(m_Skin_List[iskin].m_obj_mtl_List[iobj][imtl].m_Vertex_List.size(), 0);
                    pContext->DrawIndexed(a, 0, 0);
                }
            }
        }
    }
}


int ObjectMgr::Load_Render_Obj(ID3D11Device* pDevice,const TCHAR* shader_file_name)
{
    
    for (int iobj = 0; iobj < m_Render_Obj_List.size(); iobj++)
    {
        if (m_Render_Obj_List[iobj].m_szShader_Name == shader_file_name)
        {
            return iobj;
        }
    }
    Render_Obj temp_obj;
    if (temp_obj.Create_Render_Obj(pDevice, shader_file_name))
    {
        m_Render_Obj_List.push_back(temp_obj);
        
        return m_Render_Obj_List.size() - 1;
    }
#ifdef _DEBUG
    MessageBox(NULL, L"Load_Render_Obj_Fail", L"Load_Render_Obj_Fail", S_OK);
#endif // _DEBUG

    return -1;
}

int ObjectMgr::Load_Mat(const char* mat_file_name, ID3D11Device* pDevice)
{
    for (int iobj = 0; iobj < m_Mat_List.size(); iobj++)
    {
        if (m_Mat_List[iobj].m_szMat_File == mat_file_name)
        {
            return iobj;
        }
    }
    Mat_Obj temp_mat;
    temp_mat.Mat_Load(mat_file_name, pDevice);
    temp_mat.Interpolate();
    m_Mat_List.push_back(temp_mat);
    return m_Mat_List.size() - 1;
#pragma message(TODO("이걸로 끝? 디버깅 필요"))
}

void ObjectMgr::Load_Skin(const char* skin_file_name,int shader_index,int mat_index, ID3D11Device* pDevice)
{
    Skin_Obj temp_skin;
    temp_skin.Skin_Load(skin_file_name, texture_path.c_str(), pDevice);
    temp_skin.m_iMat_index = mat_index; //최초 mat, 혹은 -1 ==-1일 경우 바인드 랜더
#pragma message(TODO("temp_skin.m_iMat_index  ==-1일 경우 바인드포즈 랜더"))
    m_Skin_List.push_back(temp_skin);
    temp_skin.m_iShader_index = shader_index;
    
}

void ObjectMgr::Load_Cit(ID3D11Device* pDevice, const TCHAR* cit_file_name)
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
            Load_Render_Obj(pDevice, wstr.c_str());
        }
        
        in >> dummy >> mat_file;
        int imat = -1;
        if (mat_file != "null")
        {
            imat = Load_Mat(mat_file.c_str(), pDevice);
        }
        

        in >> dummy >> total_parts_count;
        for (int itotal = 0; itotal < total_parts_count; itotal++)
        {
            in >> dummy >> parts_count;
            for (int iparts = 0; iparts < parts_count; iparts++)
            {
                in >> dummy >> dummy >> parts_file >> using_shader_index;
                Load_Skin(parts_file.c_str(), shader_index_offset + using_shader_index, imat, pDevice);
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

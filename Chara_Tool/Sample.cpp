#include "stdafx.h"
#include "Sample.h"
#include "MainFrm.h"
#define _CRT_SECURE_NO_WARNINGS

void Sample::Copy_Effect_Data(Effect_Data& src, Effect_Render_Obj& dest)
{

    dest.m_data.m_Base_VB = src.m_Base_VB;
    dest.m_data.m_Base_CB = src.m_Base_CB;

    dest.m_data.m_Move_Data_X = src.m_Move_Data_X;
    dest.m_data.m_Move_Data_Y = src.m_Move_Data_Y;
    dest.m_data.m_Move_Data_Z = src.m_Move_Data_Z;
    dest.m_data.m_fMove_Radius = src.m_fMove_Radius;
    dest.m_data.m_Move_Data_R = src.m_Move_Data_R;
    dest.m_data.m_vPower1 = src.m_vPower1;
   // dest.m_data.m_vPower2 = src.m_vPower2;
   // dest.m_data.m_vPower3 = src.m_vPower3;
    //dest.m_data.m_vScale = src.m_vScale;
    //dest.m_data.m_vRotation = src.m_vRotation;
    //dest.m_data.m_vPos = src.m_vPos;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////

bool Sample::Init()
{
  //  Effect_Render_Obj* obj = new Effect_Render_Obj;
  //  m_Render_List.push_back(obj);
  //  m_Tex_List.resize(1);
  ////  Copy_Effect_Data(m_Cur_Option,m_Render_List[0]);
  //  m_Render_List[0]->Create(m_Device.m_pDevice, L"D:\\DIR\\_Shader\\effect2.hlsl", L"..\\..\\_data\\obj\\attack_damage_01.dds");
  //  
  //  m_Tex_List[0].m_szName = L"D:/DIR/_data/obj/attack_damage_01.dds";
  //  m_Tex_List[0].m_iTex = m_Render_List[0]->m_iIndex;
  //  m_Render_List[0]->m_iTex = 0;
  //  m_Render_List[0]->m_szName = L"Default";
  //  m_Render_List[0]->m_data.m_Base_CB.nRand_Loop_cutx_cuty.z = 4;
  //  m_Render_List[0]->m_data.m_Base_CB.nRand_Loop_cutx_cuty.w = 4;
  //  m_Render_List[0]->m_data.m_Base_CB.nRand_Loop_cutx_cuty.y = 1;
  //  m_Render_List[0]->m_data.m_Base_CB.etc.x = 3;
  //  m_Render_List[0]->m_bRend = true;
    
    GetCurrentDirectoryA(MAX_PATH, m_CurrentDir);
  //  char temp[] = { "\\" };
  //  strcat_s(m_CurrentDir, temp);
    return true;
}
bool Sample::Frame()
{
    D3DXMATRIX matbil;
    D3DXMatrixInverse(&matbil, NULL, &m_pMain_Cam->m_matView);
    matbil._41 = 0;
    matbil._42 = 0;
    matbil._43 = 0;

    m_fEffect_delta_Time += g_fSecondPerFrame;

    while (m_fEffect_delta_Time > m_fEffect_End_Time)
    {
        m_fEffect_delta_Time = 0;
        for (int i = 0; i < m_Render_List.size(); i++)
        {
            m_Render_List[i]->m_bFirst = true;
        }
        /*FRM->m_wndProperties.m_pSrcBlend->SetValue(COleVariant((double)0));*/
        //FRM->m_wndProperties.Custom_Update_Property(0, FRM->m_wndProperties.m_pSrcBlend);
    }
    for (int iobj = 0; iobj < m_Render_List.size(); iobj++)
    {
        m_Render_List[iobj]->m_matbill = matbil;
        m_Render_List[iobj]->m_cb.etc[1] = m_fEffect_delta_Time;
        //m_fEffect_delta_Time
        m_Render_List[iobj]->Frame();
    }
  
    return true;
}
bool Sample::Render()
{
  
    for (int iobj = 0; iobj < m_Render_List.size(); iobj++)
    {
        m_Render_List[iobj]->SetMatrix(nullptr, &m_pMain_Cam->m_matView, &m_pMain_Cam->m_matProj);
        m_Render_List[iobj]->Render();
    }
    
    // 복수 오브젝트시 함수화
 // D3DXMATRIX matBillboard, Scale, Rot,Trans,matFinal;
 // D3DXMatrixIdentity(&matBillboard);
 // D3DXMatrixIdentity(&Scale);
 // D3DXMatrixIdentity(&Rot);
 //
 // D3DXMatrixInverse(&matBillboard, NULL,
 //     &m_pMain_Cam->m_matView);
 // matBillboard._41 = 0.0f;
 // matBillboard._42 = 0.0f;
 // matBillboard._43 = 0.0f;
 // D3DXMatrixScaling(&Scale, m_Render_List.m_vScale.x, m_Render_List.m_vScale.y, m_Render_List.m_vScale.z);
 // D3DXMatrixRotationYawPitchRoll(&Rot, D3DXToRadian(m_Render_List.m_vRotation.y), D3DXToRadian(m_Render_List.m_vRotation.x), D3DXToRadian(m_Render_List.m_vRotation.z));
 // 
 // D3DXMatrixTranslation(&Trans, m_Render_List.m_vPos.x, m_Render_List.m_vPos.y, m_Render_List.m_vPos.z);
 //
 // m_Render_List.Set_Move();
 //
 // matBillboard = Scale * Rot * Trans * matBillboard;
    //
   // for (int a = 0; a < m_Render_List.m_Effect_Vertex_List.size(); a++)
    {
      
       //D3DXVECTOR3 TargetVector;
       //TargetVector.x = (m_Render_List.m_Base_CB.m_vTargetPos.x - m_Render_List.m_Effect_Vertex_List[a].m_vPos.x);
       //TargetVector.y = (m_Render_List.m_Base_Effect.m_vTargetPos.y - m_Render_List.m_Effect_Vertex_List[a].m_vPos.y);
       //TargetVector.z = (m_Render_List.m_Base_Effect.m_vTargetPos.z - m_Render_List.m_Effect_Vertex_List[a].m_vPos.z);
       //D3DXVec3Normalize(&TargetVector, &TargetVector);
       //
       //D3DXVECTOR3 Power;//TOTAL_POWER로 대체
       //Power.x = (m_Render_List.m_Base_Effect.m_vPower1.x + m_Render_List.m_Base_Effect.m_vPower2.x +m_Render_List.m_Base_Effect.m_vPower3.x);
       //Power.y = (m_Render_List.m_Base_Effect.m_vPower1.y + m_Render_List.m_Base_Effect.m_vPower2.y +m_Render_List.m_Base_Effect.m_vPower3.y);
       //Power.z = (m_Render_List.m_Base_Effect.m_vPower1.z + m_Render_List.m_Base_Effect.m_vPower2.z +m_Render_List.m_Base_Effect.m_vPower3.z);
       //
       //matFinal = matBillboard;
       //
       //
       //m_Render_List.m_Effect_Vertex_List[a].m_vPos.x += (TargetVector.x*m_Render_List.m_Base_Effect.m_fSpeed_to_Target + Power.x + m_Render_List.m_Move_Vector.x)*g_fSecondPerFrame;
       //m_Render_List.m_Effect_Vertex_List[a].m_vPos.y += (TargetVector.y*m_Render_List.m_Base_Effect.m_fSpeed_to_Target + Power.y + m_Render_List.m_Move_Vector.y)*g_fSecondPerFrame;
       //m_Render_List.m_Effect_Vertex_List[a].m_vPos.z += (TargetVector.z*m_Render_List.m_Base_Effect.m_fSpeed_to_Target + Power.z + m_Render_List.m_Move_Vector.z)*g_fSecondPerFrame;
       //
       //matFinal._41 += m_Render_List.m_Effect_Vertex_List[a].m_vPos.x;
       //matFinal._42 += m_Render_List.m_Effect_Vertex_List[a].m_vPos.y;
       //matFinal._43 += m_Render_List.m_Effect_Vertex_List[a].m_vPos.z;
       //
       //static float temp;
       //temp = m_Render_List.m_Effect_Vertex_List[a].m_vPos.x + (TargetVector.x*m_Render_List.m_Base_Effect.m_fSpeed_to_Target+ Power.x)*g_fSecondPerFrame;
       //Set_Alpha(m_Render_List.m_Effect_Vertex_List[a].m_Alpha, &m_Plane);
       //Get_UV(m_iCut_Num, m_iCut_Num, m_Render_List.m_Effect_Vertex_List[a].m_iTexID, &m_Plane);
       //
       //CADevice::m_pImmediate_Device_Context->UpdateSubresource(m_Plane.m_helper.m_pVertexBuffer.Get(), 0, 0, &m_Plane.m_Vertex_List.at(0), 0, 0);
       //m_Plane.SetMatrix(&matFinal, &m_pMain_Cam->m_matView, &m_pMain_Cam->m_matProj);
       //
       //m_Plane.Render(CADevice::m_pImmediate_Device_Context);
    }
    return true;

}
bool Sample::Release()
{


    return true;
}

Sample::Sample()
{
}


Sample::~Sample()
{
}

//void Sample::Get_UV(int cutx, int cuty, int& texnum, TPlaneObject* m_pplane)
//{
//    float x = 1.0f / cutx;
//    float y = 1.0f / cuty;
//    if (cutx*cutx  <= texnum)
//    {
//        m_pplane->m_Vertex_List[0].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(0.0f, 0.0f);
//        m_pplane->m_Vertex_List[1].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x, 0.0f);
//        m_pplane->m_Vertex_List[2].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x, y);
//        m_pplane->m_Vertex_List[3].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(0.0f, y);
//        texnum = 0;
//    }
//    for (int i = 0; i < cuty; i++)
//    {
//        for (int j = 0; j < cutx; j++)
//        {
//            if (cutx*i + j == texnum)
//            {
//                D3DXVECTOR2 temp;
//                m_pplane->m_Vertex_List[0].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x*j, y*i);
//                m_pplane->m_Vertex_List[1].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x*(j+1), y*i);
//                m_pplane->m_Vertex_List[2].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x*(j + 1), y*(i+1));
//                m_pplane->m_Vertex_List[3].t = *(DirectX::XMFLOAT2*)&D3DXVECTOR2(x*j, y*(i + 1));
//            }
//        }
//    }
//}
//void Sample::Set_Alpha(float m_Alpha, TPlaneObject* m_pplane)
//{
//    m_pplane->m_Vertex_List[0].c.w = m_Alpha;
//    m_pplane->m_Vertex_List[1].c.w = m_Alpha;
//    m_pplane->m_Vertex_List[2].c.w = m_Alpha;
//    m_pplane->m_Vertex_List[3].c.w = m_Alpha;
//}
void Sample::Save()
{

    TCHAR szFile[MAX_PATH] = { 0, };
    TCHAR szFileTitleFile[MAX_PATH] = { L"skx", };
    static TCHAR *szFilter = { L"KHG_EFFECT_TOOL(*.ket)\0*.ket\0AllFiles(*.*)\0*.*\0" };
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    _tcscpy_s(szFile, _T("*."));
    _tcscat_s(szFile, _T("ket"));
    _tcscat_s(szFile, _T("\0"));

    ofn.lStructSize = sizeof(OPENFILENAME);

    CString path;
    path = m_CurrentDir;
    ofn.lpstrInitialDir = path;
    ofn.hwndOwner = GetActiveWindow();
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0L;
    ofn.nFilterIndex = 3;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFileTitle = szFileTitleFile;
    ofn.nMaxFileTitle = sizeof(szFileTitleFile);
    ofn.lpstrTitle = L"저장하기";
    ofn.Flags = 0L;
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = _T("ket");
    if (!GetSaveFileName(&ofn))
    {
        return;
    }
    std::wstring szFilename = szFile;
    ///////////////////////////////////
    FILE* Filestream = nullptr;
    _tfopen_s(&Filestream, szFilename.c_str(), _T("wt"));
    
    _ftprintf(Filestream, _T("%s\n"), _T("KHG_EFFECT_TOOL_V100"));// , m_Tex_List.size(), m_Render_List.size());
    _ftprintf(Filestream, _T("%d\n"), m_Tex_List.size());
    _ftprintf(Filestream, _T("%d\n"), m_Render_List.size());

    for (int i = 0; i < m_Tex_List.size(); i++)
    {
        _ftprintf(Filestream, _T("%s\n"), m_Tex_List[i].m_szName.GetString());
        //로드시는 이거 읽어서 Texture_mgr 에서 로드 해서 id받아야함.
    }
    for (int ieffect = 0; ieffect < m_Render_List.size(); ieffect++)
    {
        _ftprintf(Filestream, _T("%s\n"), m_Render_List[ieffect]->m_szName.GetString());
        _ftprintf(Filestream, _T("%s\n"), m_Render_List[ieffect]->m_szShader.GetString());
        _ftprintf(Filestream, _T("%s\n"), m_Render_List[ieffect]->m_szTextureName.GetString());
        fwrite(&m_Render_List[ieffect]->m_data, sizeof(Effect_Data), 1, Filestream);
        _ftprintf(Filestream, _T("\n"));
    }
        
    fclose(Filestream);

}
void Sample::Load()
{
    TCHAR szFile[MAX_PATH] = { 0, };
    TCHAR szFileTitleFile[MAX_PATH] = { L"skx", };
    static TCHAR *szFilter = { L"KHG_EFFECT_TOOL(*.ket)\0*.ket\0AllFiles(*.*)\0*.*\0" };
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    _tcscpy_s(szFile, _T("*."));
    _tcscat_s(szFile, _T("ket"));
    _tcscat_s(szFile, _T("\0"));

    
    ofn.lStructSize = sizeof(OPENFILENAME);
    
    ofn.hwndOwner = GetActiveWindow();
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0L;
    ofn.nFilterIndex = 3;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFileTitle = szFileTitleFile;
    ofn.nMaxFileTitle = sizeof(szFileTitleFile);
    ofn.lpstrTitle = L"저장하기";
    ofn.Flags = 0L;
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = _T("ket");
    CString path;
    path = m_CurrentDir;
    ofn.lpstrInitialDir = path;
    if (!GetOpenFileName(&ofn))
    {
        return;
    }
    std::wstring szFilename = szFile;
    FILE* Filestream = nullptr;

    _tfopen_s(&Filestream, szFilename.c_str(), L"r");
    
    int texnum = 0;
    int objnum = 0;
    char data[4];
    char dummy[100];
    fgets(dummy, 100, Filestream);
    texnum = fgetc(Filestream)-48;// 인티저로 하드코딩 변환.
    fgetc(Filestream);
    objnum = fgetc(Filestream)-48;
    fgetc(Filestream);
    //fgets(data, sizeof(int), Filestream);

    for (int itex = 0; itex < texnum; itex++)
    {
        Tex_Info info;
        char texname[100];
        char texname2[100];

        fgets(texname, 100, Filestream);//wstr 변환 되는지 확인
        strncpy_s(texname2, texname, strlen(texname) - 1);
        //strcpy_s(texname2, strlen(texname) - 2, texname);
        info.m_szName = texname2;
        CString name;
        name = m_CurrentDir;
        name += m_szTeexture_Path;
        name += texname2;
        info.m_iTex = I_TextureMgr.Load(CADevice::m_pDevice, name.GetBuffer());
        m_Tex_List.push_back(info);
    }
    for (int iobj = 0; iobj < objnum; iobj++)
    {
        Effect_Render_Obj* obj= new Effect_Render_Obj;

        char mem[sizeof(Effect_Data)+2];
        char string[100];
        char string2[100];
        CString shadername;
        char* error = fgets(string, 100, Filestream);
        int eof = feof(Filestream);
        strncpy_s(string2, string, strlen(string) - 1);
        obj->m_szName = string2;
        int errno;
        error = fgets(string, 100, Filestream);
        strncpy_s(string2, string, strlen(string) - 1);
        char tester[100] = { 0 };
        
        

        shadername += m_CurrentDir;
        shadername += m_szShader_Path;
        shadername += string2;
      //  strcpy_s(tester, m_CurrentDir);
      //  strcpy_s(tester, m_szShader_Path);
      //  strcat_s(tester, string2);
        obj->m_szShader = string2;
        //shadername = tester;
        error=fgets(string, 100, Filestream);
        strncpy_s(string2, string, strlen(string) - 1);
        obj->m_szTextureName = string2;
        obj->Create(CADevice::m_pDevice, shadername, nullptr,true);
        error=  fgets(mem, sizeof(Effect_Data)+2, Filestream);
        //error=fgets(string, 2, Filestream);
    
        memcpy(&obj->m_data, mem, sizeof(Effect_Data));
        m_Render_List.push_back(obj);
        int srvid = Find_Texture(&obj->m_szTextureName);
        if (srvid > -1)
        {
            obj->m_helper.m_pSRV.Attach(I_TextureMgr.GetPtr(m_Tex_List[srvid].m_iTex)->m_pSRV);
            obj->m_bRend = true;

        }
        else
        {
            MessageBox(NULL, L"NOT FIND TEXTURE", obj->m_szTextureName.GetBuffer(), S_OK);
            obj->m_bRend = false;

        }

    }
    fclose(Filestream);


}
int Sample::Find_Texture(CString* texname)
{
    if(m_Tex_List.size()<1)
    {
        return -1;
    }
    int index = 0;
    for (auto iter : m_Tex_List)
    {
        if (iter.m_szName == *texname)
        {
            return index;
        }
        index++;
    }
    return -1;
}

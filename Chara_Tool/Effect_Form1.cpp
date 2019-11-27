// Effect_Form1.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chara_Tool.h"
#include "Effect_Form1.h"
#include "afxdialogex.h"
#include "MainFrm.h"
//#include "Effect_Form2.h"
// Effect_Form1 대화 상자

IMPLEMENT_DYNAMIC(Effect_Form1, CFormView)

Effect_Form1::Effect_Form1()
	: CFormView(IDD_Effect_Form1)
{

}

Effect_Form1::~Effect_Form1()
{
}

void Effect_Form1::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
}

Effect_Form1* Effect_Form1::CreateOne(CWnd* pParent)
{
    Effect_Form1* one = new Effect_Form1;
    one->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 800), pParent, 0, NULL);
    return one;
}

BEGIN_MESSAGE_MAP(Effect_Form1, CFormView)
    ON_BN_CLICKED(ID_NEW_OBJ, &Effect_Form1::OnBnClickedNewObj)
    ON_LBN_SELCHANGE(IDC_OBJ_LIST, &Effect_Form1::OnLbnSelchangeObjList)
    ON_BN_CLICKED(ID_NEW_TEXTURE, &Effect_Form1::OnBnClickedNewTexture)
    ON_LBN_SELCHANGE(IDC_TEXTURE_LIST, &Effect_Form1::OnLbnSelchangeTextureList)
    //ON_BN_CLICKED(IDC_UPDATE_BUTTON, &Effect_Form1::OnBnClickedUpdateButton)
//    ON_WM_ACTIVATE()
    ON_WM_MOUSEACTIVATE()
//    ON_WM_MENUSELECT()
//    ON_COMMAND(ID_OPEN, &Effect_Form1::OnOpen)
ON_BN_CLICKED(IDC_SELECT_TEXTURE, &Effect_Form1::OnBnClickedSelectTexture)
ON_BN_CLICKED(IDC_SAVE, &Effect_Form1::OnBnClickedSave)
ON_BN_CLICKED(IDC_LOAD, &Effect_Form1::OnBnClickedLoad)
ON_BN_CLICKED(IDC_BACK_COLOR, &Effect_Form1::OnBnClickedBackColor)
ON_BN_CLICKED(ID_NAME_MODY, &Effect_Form1::OnBnClickedNameMody)
END_MESSAGE_MAP()


// Effect_Form1 메시지 처리기


void Effect_Form1::OnBnClickedNewObj()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    
    Effect_Render_Obj* newobj = new Effect_Render_Obj;
    CString shader;
    shader = TOOL.m_CurrentDir;

    shader += TOOL.m_szShader_Path;
    shader += TOOL.m_szMain_Shader;
    newobj->m_szShader = TOOL.m_szMain_Shader;
    newobj->Create(TOOL.m_Device.m_pDevice, shader.GetBuffer(), nullptr);

    GetDlgItemTextW(IDC_OBJ_NAME_EDIT, newobj->m_szName);

    TOOL.m_Render_List.push_back(newobj);

    SendDlgItemMessageW(IDC_OBJ_LIST, LB_RESETCONTENT, 0, 0);

    for (int i = 0; i<TOOL.m_Render_List.size(); i++)
    {
        SendDlgItemMessageW(IDC_OBJ_LIST, LB_ADDSTRING, 0, (LPARAM)TOOL.m_Render_List[i]->m_szName.GetBuffer());

    }





}

void Effect_Form1::OnLbnSelchangeObjList()
{
    int i = SendDlgItemMessageW(IDC_OBJ_LIST, LB_GETCURSEL, 0, 0);
    TOOL.m_iSel_Obj = i;
    
    FRM->m_wndProperties.Update_Property_List();
    ((CMainFrame*)AfxGetMainWnd())->m_Effect_Pane2.m_Form2->UpdateData(FALSE);
  //      TOOL.m_Cur_Option = TOOL.m_Render_List[TOOL.m_iSel_Obj];

  //  AfxMessageBox(pApp->m_Tool.m_Obj_List[i].m_szName);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void Effect_Form1::OnBnClickedNewTexture()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString path;
    path = TOOL.m_CurrentDir;
    //path += L"..\\..\\";
   // wcscat_s(PATH, L"\\..\\..\\");
    
    CString filename;
    CFileDialog dlg(
        TRUE, L"dds", NULL,
        OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
        L"dds Files(*.dds)|*.dds|All Files(*.*)|*.*|", this
    );
    dlg.m_ofn.lpstrInitialDir = path;
    
    if (dlg.DoModal() == IDOK)
    {
        Tex_Info tex;
        filename = dlg.GetFileName();

        tex.m_szName += filename;
        //AfxMessageBox(selFileName);
        CCharaToolApp* pApp = (CCharaToolApp*)AfxGetApp();
        CString name;
        name = TOOL.m_CurrentDir;
        name += TOOL.m_szTeexture_Path + filename;
        tex.m_iTex = I_TextureMgr.Load(CADevice::m_pDevice, name.GetBuffer());
        if (tex.m_iTex > -1)
        {
            TOOL.m_Tex_List.push_back(tex);
        }
        //TODO Tex_LIST에 추가해야함
        SendDlgItemMessageW(IDC_TEXTURE_LIST, LB_RESETCONTENT, 0, 0);
        
        for (int i = 0; i<TOOL.m_Tex_List.size(); i++)
        {
            SendDlgItemMessageW(IDC_TEXTURE_LIST, LB_ADDSTRING, 0, (LPARAM)TOOL.m_Tex_List[i].m_szName.GetBuffer());

        }
    }

}


void Effect_Form1::OnLbnSelchangeTextureList()
{
    CCharaToolApp* pApp = (CCharaToolApp*)AfxGetApp();

    int i = SendDlgItemMessageW(IDC_TEXTURE_LIST, LB_GETCURSEL, 0, 0);
    if(i< TOOL.m_Tex_List.size())
    TOOL.m_iSel_Tex = i;
    
    //FRM->m_Effect_Pane2.m_Form2->UpdateData(false);
  //  AfxMessageBox(pApp->m_Tool.m_Tex_List[i].m_szName);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


//void Effect_Form1::OnBnClickedUpdateButton()
//{
//    if (TOOL.m_iSel_Tex != -1)
//    {
//        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_iTex = TOOL.m_iSel_Tex;
//    }
//    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}



int Effect_Form1::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    SendDlgItemMessageW(IDC_TEXTURE_LIST, LB_RESETCONTENT, 0, 0);

    for (int i = 0; i < TOOL.m_Tex_List.size(); i++)
    {
        SendDlgItemMessageW(IDC_TEXTURE_LIST, LB_ADDSTRING, 0, (LPARAM)TOOL.m_Tex_List[i].m_szName.GetBuffer());
    }
    SendDlgItemMessageW(IDC_OBJ_LIST, LB_RESETCONTENT, 0, 0);

    for (int i = 0; i < TOOL.m_Render_List.size(); i++)
    {
        SendDlgItemMessageW(IDC_OBJ_LIST, LB_ADDSTRING, 0, (LPARAM)TOOL.m_Render_List[i]->m_szName.GetBuffer());
    }
    

    //((CMainFrame*)AfxGetMainWnd())->m_wndProperties.m_wndPropList.UpdateData(false);
    return CFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}



void Effect_Form1::OnBnClickedSelectTexture()
{
    if (TOOL.m_iSel_Tex < TOOL.m_Tex_List.size() && TOOL.m_iSel_Tex>-1)
    {
        if (TOOL.m_iSel_Obj < TOOL.m_Render_List.size() && TOOL.m_iSel_Obj>-1)
        {
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_helper.m_pSRV.Detach();
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_helper.m_pSRV.Attach(I_TextureMgr.GetPtr(TOOL.m_Tex_List[TOOL.m_iSel_Tex].m_iTex)->m_pSRV);
            
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_iTex = TOOL.m_iSel_Tex;

            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_szTextureName = TOOL.m_Tex_List[TOOL.m_iSel_Tex].m_szName;

        }
    }
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form1::OnBnClickedSave()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    TOOL.Save();
}


void Effect_Form1::OnBnClickedLoad()
{
    TOOL.Load();
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form1::OnBnClickedBackColor()
{
    CString selCol;
    CColorDialog dlg(RGB(0, 0, 0), CC_FULLOPEN);
    if (dlg.DoModal() == IDOK)
    {
        COLORREF color = dlg.GetColor();
        selCol.Format(L"%u,%u,%u",
            GetRValue(color),
            GetGValue(color),
            GetBValue(color));
        //AfxMessageBox(selCol);
        
        CADevice::m_ClearColor[0] = GetRValue(color) / 255.0f;
        CADevice::m_ClearColor[1] = GetGValue(color) / 255.0f;
        CADevice::m_ClearColor[2] = GetBValue(color) / 255.0f;
        CADevice::m_ClearColor[3] = 1.0f;
        
    }
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form1::OnBnClickedNameMody()
{
    if (TOOL.m_iSel_Obj < TOOL.m_Render_List.size())
    {
        GetDlgItemTextW(IDC_OBJ_NAME_EDIT, TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_szName);
       
        SendDlgItemMessageW(IDC_OBJ_LIST, LB_RESETCONTENT, 0, 0);

        for (int i = 0; i < TOOL.m_Render_List.size(); i++)
        {
            SendDlgItemMessageW(IDC_OBJ_LIST, LB_ADDSTRING, 0, (LPARAM)TOOL.m_Render_List[i]->m_szName.GetBuffer());

        }
    }
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

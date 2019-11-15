// Effect_Form1.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chara_Tool.h"
#include "Effect_Form1.h"
#include "afxdialogex.h"


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
    ON_BN_CLICKED(IDC_UPDATE_BUTTON, &Effect_Form1::OnBnClickedUpdateButton)
END_MESSAGE_MAP()


// Effect_Form1 메시지 처리기


void Effect_Form1::OnBnClickedNewObj()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    Effect_Obj obj;
    GetDlgItemTextW(IDC_OBJ_NAME_EDIT, obj.m_szName);
    SendDlgItemMessageW(IDC_OBJ_LIST, LB_ADDSTRING, 0, (LPARAM)obj.m_szName.GetBuffer());

    CCharaToolApp* pApp = (CCharaToolApp*)AfxGetApp();
    TOOL.m_Obj_List.push_back(obj);
}

void Effect_Form1::OnLbnSelchangeObjList()
{
    int i = SendDlgItemMessageW(IDC_OBJ_LIST, LB_GETCURSEL, 0, 0);
    TOOL.m_iSel_Obj = i;

  //      TOOL.m_Cur_Option = TOOL.m_Render_List[TOOL.m_iSel_Obj];

  //  AfxMessageBox(pApp->m_Tool.m_Obj_List[i].m_szName);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void Effect_Form1::OnBnClickedNewTexture()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    CString filename;
    CFileDialog dlg(
        TRUE, L"dds", NULL,
        OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
        L"dds Files(*.dds)|*.dds|All Files(*.*)|*.*|", this
    );

    if (dlg.DoModal() == IDOK)
    {
        Tex_Info tex;
        filename = dlg.GetPathName();

        tex.m_szName += dlg.GetFileName();
        //AfxMessageBox(selFileName);
        CCharaToolApp* pApp = (CCharaToolApp*)AfxGetApp();

        tex.m_iTex = I_TextureMgr.Load(CADevice::m_pDevice, filename.GetBuffer());
        if (tex.m_iTex > -1)
        {
            TOOL.m_Tex_List.push_back(tex);
        }
        //TODO Tex_LIST에 추가해야함
        SendDlgItemMessageW(IDC_TEXTURE_LIST, LB_ADDSTRING, 0, (LPARAM)tex.m_szName.GetBuffer());
    }

}


void Effect_Form1::OnLbnSelchangeTextureList()
{
    CCharaToolApp* pApp = (CCharaToolApp*)AfxGetApp();

    int i = SendDlgItemMessageW(IDC_TEXTURE_LIST, LB_GETCURSEL, 0, 0);

    TOOL.m_iSel_Tex = i;

  //  AfxMessageBox(pApp->m_Tool.m_Tex_List[i].m_szName);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form1::OnBnClickedUpdateButton()
{
    if (TOOL.m_iSel_Tex != -1)
    {
        TOOL.m_Obj_List[TOOL.m_iSel_Obj].m_iTex = TOOL.m_iSel_Tex;
    }
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

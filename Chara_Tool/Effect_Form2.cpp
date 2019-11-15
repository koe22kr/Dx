// Effect_Form2.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chara_Tool.h"
#include "Effect_Form2.h"
#include "afxdialogex.h"


// Effect_Form2 대화 상자

IMPLEMENT_DYNAMIC(Effect_Form2, CFormView)

Effect_Form2::Effect_Form2()
	: CFormView(IDD_Effect_Form2)
{

}

Effect_Form2::~Effect_Form2()
{
}

void Effect_Form2::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    Effect_Render_Obj& data = TOOL.m_Cur_Option;
    DDX_Text(pDX, IDC_SCALE_X, data.m_vScale.x);
    DDX_Text(pDX, IDC_SCALE_Y, data.m_vScale.y);
    DDX_Text(pDX, IDC_SCALE_Z, data.m_vScale.z);
    DDX_Text(pDX, IDC_ROTATION_X, data.m_vRotation.x);
    DDX_Text(pDX, IDC_ROTATION_Y, data.m_vRotation.y);
    DDX_Text(pDX, IDC_ROTATION_Z, data.m_vRotation.z);
    DDX_Text(pDX, IDC_TRANS_X, data.m_vPos.x);
    DDX_Text(pDX, IDC_TRANS_Y, data.m_vPos.y);
    DDX_Text(pDX, IDC_TRANS_Z, data.m_vPos.z);
    
    DDX_Text(pDX, IDC_TARGET_X, data.m_Base_CB.m_vTargetPos_wSpeed.x);
    DDX_Text(pDX, IDC_TARGET_Y, data.m_Base_CB.m_vTargetPos_wSpeed.y);
    DDX_Text(pDX, IDC_TARGET_Z, data.m_Base_CB.m_vTargetPos_wSpeed.z);
    DDX_Text(pDX, IDC_SPEED, data.m_Base_CB.m_vTargetPos_wSpeed.w);


    DDX_Text(pDX, IDC_POWER1_X, data.m_vPower1.x);
    DDX_Text(pDX, IDC_POWER1_Y, data.m_vPower1.y);
    DDX_Text(pDX, IDC_POWER1_Z, data.m_vPower1.z);

    DDX_Text(pDX, IDC_POWER2_X, data.m_vPower2.x);
    DDX_Text(pDX, IDC_POWER2_Y, data.m_vPower2.y);
    DDX_Text(pDX, IDC_POWER2_Z, data.m_vPower2.z);

    DDX_Text(pDX, IDC_POWER3_X, data.m_vPower3.x);
    DDX_Text(pDX, IDC_POWER3_Y, data.m_vPower3.y);
    DDX_Text(pDX, IDC_POWER3_Z, data.m_vPower3.z);

    DDX_Text(pDX, IDC_FADEIN_TIME, data.m_Base_CB.Time_add_life_fadein_fadeout.z);
    DDX_Text(pDX, IDC_FADEOUT_TIME, data.m_Base_CB.Time_add_life_fadein_fadeout.w);

    DDX_Text(pDX, IDC_MOVE_X_A, TOOL.m_Cur_Option.m_Move_Data_X.a);
    DDX_Text(pDX, IDC_MOVE_X_B, TOOL.m_Cur_Option.m_Move_Data_X.b);
    DDX_Text(pDX, IDC_MOVE_X_C, TOOL.m_Cur_Option.m_Move_Data_X.c);
    DDX_Text(pDX, IDC_MOVE_X_D, TOOL.m_Cur_Option.m_Move_Data_X.d);
    DDX_Text(pDX, IDC_MOVE_X_E, TOOL.m_Cur_Option.m_Move_Data_X.e);
  //  DDX_Text(pDX, IDC_MOVE_X_EXP1, *(UINT*)&TOOL.m_Render_List.m_Move_Data_X.exp1);
  //  DDX_Text(pDX, IDC_MOVE_X_EXP2, *(UINT*)&TOOL.m_Render_List.m_Move_Data_X.exp2);

    DDX_Text(pDX, IDC_MOVE_Y_A, TOOL.m_Cur_Option.m_Move_Data_Y.a);
    DDX_Text(pDX, IDC_MOVE_Y_B, TOOL.m_Cur_Option.m_Move_Data_Y.b);
    DDX_Text(pDX, IDC_MOVE_Y_C, TOOL.m_Cur_Option.m_Move_Data_Y.c);
    DDX_Text(pDX, IDC_MOVE_Y_D, TOOL.m_Cur_Option.m_Move_Data_Y.d);
    DDX_Text(pDX, IDC_MOVE_Y_E, TOOL.m_Cur_Option.m_Move_Data_Y.e);
 //   DDX_Text(pDX, IDC_MOVE_Y_EXP1, *(UINT*)&TOOL.m_Render_List.m_Move_Data_Y.exp1);
 //   DDX_Text(pDX, IDC_MOVE_Y_EXP2, *(UINT*)&TOOL.m_Render_List.m_Move_Data_Y.exp2);

    DDX_Text(pDX, IDC_MOVE_Z_A, TOOL.m_Cur_Option.m_Move_Data_Z.a);
    DDX_Text(pDX, IDC_MOVE_Z_B, TOOL.m_Cur_Option.m_Move_Data_Z.b);
    DDX_Text(pDX, IDC_MOVE_Z_C, TOOL.m_Cur_Option.m_Move_Data_Z.c);
    DDX_Text(pDX, IDC_MOVE_Z_D, TOOL.m_Cur_Option.m_Move_Data_Z.d);
    DDX_Text(pDX, IDC_MOVE_Z_E, TOOL.m_Cur_Option.m_Move_Data_Z.e);
  //  DDX_Text(pDX, IDC_MOVE_Z_EXP1, *(UINT*)&TOOL.m_Render_List.m_Move_Data_Z.exp1);
  //  DDX_Text(pDX, IDC_MOVE_Z_EXP2, *(UINT*)&TOOL.m_Render_List.m_Move_Data_Z.exp2);

    DDX_Text(pDX, IDC_MOVE_R_A, TOOL.m_Cur_Option.m_Move_Data_R.a);
    DDX_Text(pDX, IDC_MOVE_R_B, TOOL.m_Cur_Option.m_Move_Data_R.b);
    DDX_Text(pDX, IDC_MOVE_R_C, TOOL.m_Cur_Option.m_Move_Data_R.c);
    DDX_Text(pDX, IDC_MOVE_R_D, TOOL.m_Cur_Option.m_Move_Data_R.d);
    DDX_Text(pDX, IDC_MOVE_R_E, TOOL.m_Cur_Option.m_Move_Data_R.e);
   // DDX_Text(pDX, IDC_MOVE_R_EXP1, *(UINT*)&TOOL.m_Render_List.m_Move_Data_R.exp1);
   // DDX_Text(pDX, IDC_MOVE_R_EXP2, *(UINT*)&TOOL.m_Render_List.m_Move_Data_R.exp2);

    DDX_Text(pDX, IDC_ADD_TIME, TOOL.m_Cur_Option.m_Base_CB.Time_add_life_fadein_fadeout.x);


    DDX_Text(pDX, IDC_LIFE_TIME, data.m_Base_CB.Time_add_life_fadein_fadeout.y);

}

Effect_Form2* Effect_Form2::CreateOne(CWnd* pParent)
{
    Effect_Form2* one = new Effect_Form2;
    one->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 800), pParent, 0, NULL);
    return one;
}

BEGIN_MESSAGE_MAP(Effect_Form2, CFormView)
    ON_BN_CLICKED(IDC_FORM2_UPDATE, &Effect_Form2::OnBnClickedForm2Update)
//    ON_WM_CREATE()
ON_CBN_SELCHANGE(IDC_MOVE_X_EXP1, &Effect_Form2::OnCbnSelchangeMoveXExp1)
ON_CBN_SELCHANGE(IDC_MOVE_X_EXP2, &Effect_Form2::OnCbnSelchangeMoveXExp2)
ON_CBN_SELCHANGE(IDC_MOVE_Y_EXP1, &Effect_Form2::OnCbnSelchangeMoveYExp1)
ON_CBN_SELCHANGE(IDC_MOVE_Y_EXP2, &Effect_Form2::OnCbnSelchangeMoveYExp2)
ON_CBN_SELCHANGE(IDC_MOVE_Z_EXP1, &Effect_Form2::OnCbnSelchangeMoveZExp1)
ON_CBN_SELCHANGE(IDC_MOVE_Z_EXP2, &Effect_Form2::OnCbnSelchangeMoveZExp2)
ON_CBN_SELCHANGE(IDC_MOVE_R_EXP1, &Effect_Form2::OnCbnSelchangeMoveRExp1)
ON_CBN_SELCHANGE(IDC_MOVE_R_EXP2, &Effect_Form2::OnCbnSelchangeMoveRExp2)
END_MESSAGE_MAP()


// Effect_Form2 메시지 처리기


void Effect_Form2::OnBnClickedForm2Update()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    UpdateData(TRUE);
   // if (TOOL.m_iSel_Obj != -1 && TOOL.m_Render_List.size() > 0)
   // {
   //     TOOL.m_Render_List[TOOL.m_iSel_Obj] = TOOL.m_Cur_Option;
//
   // }

}


//int Effect_Form2::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//    if (CFormView::OnCreate(lpCreateStruct) == -1)
//        return -1;
//
//    // TODO:  여기에 특수화된 작성 코드를 추가합니다.
//
//
//    UpdateData(FALSE);
//
//    return 0;
//}


void Effect_Form2::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();
    UpdateData(FALSE);
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}




void Effect_Form2::OnCbnSelchangeMoveXExp1()
{
    int i = SendDlgItemMessageW(IDC_MOVE_X_EXP1, CB_GETCURSEL, 0, 0);
    TOOL.m_Cur_Option.m_Move_Data_X.exp1 = (Radius_exp)i;
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveXExp2()
{
    int i = SendDlgItemMessageW(IDC_MOVE_X_EXP2, CB_GETCURSEL, 0, 0);
    TOOL.m_Cur_Option.m_Move_Data_X.exp2 = (Radius_exp)i;
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveYExp1()
{
    int i = SendDlgItemMessageW(IDC_MOVE_Y_EXP1, CB_GETCURSEL, 0, 0);
    TOOL.m_Cur_Option.m_Move_Data_Y.exp1 = (Radius_exp)i;
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveYExp2()
{
    int i = SendDlgItemMessageW(IDC_MOVE_Y_EXP2, CB_GETCURSEL, 0, 0);
    TOOL.m_Cur_Option.m_Move_Data_Y.exp2 = (Radius_exp)i;
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveZExp1()
{
    int i = SendDlgItemMessageW(IDC_MOVE_Z_EXP1, CB_GETCURSEL, 0, 0);
    TOOL.m_Cur_Option.m_Move_Data_Z.exp1 = (Radius_exp)i;
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveZExp2()
{
    int i = SendDlgItemMessageW(IDC_MOVE_Z_EXP2, CB_GETCURSEL, 0, 0);
    TOOL.m_Cur_Option.m_Move_Data_Z.exp2 = (Radius_exp)i;
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveRExp1()
{
    int i = SendDlgItemMessageW(IDC_MOVE_R_EXP1, CB_GETCURSEL, 0, 0);
    TOOL.m_Cur_Option.m_Move_Data_R.exp1 = (Radius_exp)i;
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveRExp2()
{
    int i = SendDlgItemMessageW(IDC_MOVE_R_EXP2, CB_GETCURSEL, 0, 0);
    TOOL.m_Cur_Option.m_Move_Data_R.exp2 = (Radius_exp)i;
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

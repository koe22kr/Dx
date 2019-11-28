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
    , bAnimLoop(FALSE)
{

}

Effect_Form2::~Effect_Form2()
{
}

void Effect_Form2::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    if (TOOL.m_Render_List.size() > TOOL.m_iSel_Obj)
    {

        Effect_Data& data = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data;
        DDX_Text(pDX, IDC_SCALE_X, data.m_Base_CB.m_vScale.x);
        DDX_Text(pDX, IDC_SCALE_Y, data.m_Base_CB.m_vScale.y);
        DDX_Text(pDX, IDC_SCALE_Z, data.m_Base_CB.m_vScale.z);
        DDX_Text(pDX, IDC_ROTATION_X, data.m_to_quat_base_rot.x);
        DDX_Text(pDX, IDC_ROTATION_Y, data.m_to_quat_base_rot.y);
        DDX_Text(pDX, IDC_ROTATION_Z, data.m_to_quat_base_rot.z);
        DDX_Text(pDX, IDC_TRANS_X, data.m_Base_CB.m_vPos.x);
        DDX_Text(pDX, IDC_TRANS_Y, data.m_Base_CB.m_vPos.y);
        DDX_Text(pDX, IDC_TRANS_Z, data.m_Base_CB.m_vPos.z);

        ////////////점진 스케일 회전 가속도//
        DDX_Text(pDX, IDC_SCALE_X2, data.m_Base_CB.m_vScale_per_Sec.x);
        DDX_Text(pDX, IDC_SCALE_Y2, data.m_Base_CB.m_vScale_per_Sec.y);
        DDX_Text(pDX, IDC_SCALE_Z2, data.m_Base_CB.m_vScale_per_Sec.z);
        DDX_Text(pDX, IDC_ROTATION_X2, data.m_to_quat.x);
        DDX_Text(pDX, IDC_ROTATION_Y2, data.m_to_quat.y);
        DDX_Text(pDX, IDC_ROTATION_Z2, data.m_to_quat.z);
        DDX_Text(pDX, IDC_TRANS_X2, data.m_Base_CB.m_vVel.x);
        DDX_Text(pDX, IDC_TRANS_Y2, data.m_Base_CB.m_vVel.y);
        DDX_Text(pDX, IDC_TRANS_Z2, data.m_Base_CB.m_vVel.z);
        //////////

        DDX_Text(pDX, IDC_TARGET_X, data.m_Base_CB.m_vTargetPos_wSpeed.x);
        DDX_Text(pDX, IDC_TARGET_Y, data.m_Base_CB.m_vTargetPos_wSpeed.y);
        DDX_Text(pDX, IDC_TARGET_Z, data.m_Base_CB.m_vTargetPos_wSpeed.z);
        DDX_Text(pDX, IDC_SPEED, data.m_Base_CB.m_vTargetPos_wSpeed.w);

        DDX_Text(pDX, IDC_RANDOM_POS_MIN_X, data.m_vRandom_Pos_Min.x);
        DDX_Text(pDX, IDC_RANDOM_POS_MIN_Y, data.m_vRandom_Pos_Min.y);
        DDX_Text(pDX, IDC_RANDOM_POS_MIN_Z, data.m_vRandom_Pos_Min.z);

        DDX_Text(pDX, IDC_RANDOM_POS_MAX_X, data.m_vRandom_Pos_Max.x);
        DDX_Text(pDX, IDC_RANDOM_POS_MAX_Y, data.m_vRandom_Pos_Max.y);
        DDX_Text(pDX, IDC_RANDOM_POS_MAX_Z, data.m_vRandom_Pos_Max.z);
        //
        DDX_Text(pDX, IDC_POWER_X, data.m_vPower1.x);
        DDX_Text(pDX, IDC_POWER_Y, data.m_vPower1.y);
        DDX_Text(pDX, IDC_POWER_Z, data.m_vPower1.z);

        //DDX_Text(pDX, IDC_POWER2_X, data.m_vPower2.x);
        //DDX_Text(pDX, IDC_POWER2_Y, data.m_vPower2.y);
        //DDX_Text(pDX, IDC_POWER2_Z, data.m_vPower2.z);
        //
        //DDX_Text(pDX, IDC_POWER3_X, data.m_vPower3.x);
        //DDX_Text(pDX, IDC_POWER3_Y, data.m_vPower3.y);
        //DDX_Text(pDX, IDC_POWER3_Z, data.m_vPower3.z);
        //수정해야함 191125

        DDX_Text(pDX, IDC_MOVE_X_A, data.m_Move_Data_X.a);
        DDX_Text(pDX, IDC_MOVE_X_B, data.m_Move_Data_X.b);
        DDX_Text(pDX, IDC_MOVE_X_C, data.m_Move_Data_X.c);
        DDX_Text(pDX, IDC_MOVE_X_D, data.m_Move_Data_X.d);
        DDX_Text(pDX, IDC_MOVE_X_E, data.m_Move_Data_X.e);
        //  DDX_Text(pDX, IDC_MOVE_X_EXP1, *(UINT*)&TOOL.m_Render_List.m_Move_Data_X.exp1);
        //  DDX_Text(pDX, IDC_MOVE_X_EXP2, *(UINT*)&TOOL.m_Render_List.m_Move_Data_X.exp2);

        DDX_Text(pDX, IDC_MOVE_Y_A, data.m_Move_Data_Y.a);
        DDX_Text(pDX, IDC_MOVE_Y_B, data.m_Move_Data_Y.b);
        DDX_Text(pDX, IDC_MOVE_Y_C, data.m_Move_Data_Y.c);
        DDX_Text(pDX, IDC_MOVE_Y_D, data.m_Move_Data_Y.d);
        DDX_Text(pDX, IDC_MOVE_Y_E, data.m_Move_Data_Y.e);
        //   DDX_Text(pDX, IDC_MOVE_Y_EXP1, *(UINT*)&TOOL.m_Render_List.m_Move_Data_Y.exp1);
        //   DDX_Text(pDX, IDC_MOVE_Y_EXP2, *(UINT*)&TOOL.m_Render_List.m_Move_Data_Y.exp2);

        DDX_Text(pDX, IDC_MOVE_Z_A, data.m_Move_Data_Z.a);
        DDX_Text(pDX, IDC_MOVE_Z_B, data.m_Move_Data_Z.b);
        DDX_Text(pDX, IDC_MOVE_Z_C, data.m_Move_Data_Z.c);
        DDX_Text(pDX, IDC_MOVE_Z_D, data.m_Move_Data_Z.d);
        DDX_Text(pDX, IDC_MOVE_Z_E, data.m_Move_Data_Z.e);
        //  DDX_Text(pDX, IDC_MOVE_Z_EXP1, *(UINT*)&TOOL.m_Render_List.m_Move_Data_Z.exp1);
        //  DDX_Text(pDX, IDC_MOVE_Z_EXP2, *(UINT*)&TOOL.m_Render_List.m_Move_Data_Z.exp2);

        DDX_Text(pDX, IDC_MOVE_R_A, data.m_Move_Data_R.a);
        DDX_Text(pDX, IDC_MOVE_R_B, data.m_Move_Data_R.b);
        DDX_Text(pDX, IDC_MOVE_R_C, data.m_Move_Data_R.c);
        DDX_Text(pDX, IDC_MOVE_R_D, data.m_Move_Data_R.d);
        DDX_Text(pDX, IDC_MOVE_R_E, data.m_Move_Data_R.e);
        // DDX_Text(pDX, IDC_MOVE_R_EXP1, *(UINT*)&TOOL.m_Render_List.m_Move_Data_R.exp1);
        // DDX_Text(pDX, IDC_MOVE_R_EXP2, *(UINT*)&TOOL.m_Render_List.m_Move_Data_R.exp2);

        DDX_Text(pDX, IDC_ADD_TIME, data.m_Base_CB.Time_add_life_fadein_fadeout.x);
        if (!data.m_Base_CB.Time_add_life_fadein_fadeout.x>0)
        {
            data.m_Base_CB.Time_add_life_fadein_fadeout.x = 0.0001f;
        }
        DDX_Text(pDX, IDC_LIFE_TIME, data.m_Base_CB.Time_add_life_fadein_fadeout.y);
        DDX_Text(pDX, IDC_FADEIN_TIME, data.m_Base_CB.Time_add_life_fadein_fadeout.z);
        DDX_Text(pDX, IDC_FADEOUT_TIME, data.m_Base_CB.Time_add_life_fadein_fadeout.w);

        //DDX_OCBool(pDX, IDC_BLOOP, IDC_BLOOP, bAnimLoop);
        
        /*DDX_Text(pDX, IDC_BLOOP, data.m_Base_CB.nRand_Loop_cutx_cuty.y);*/
        DDX_Text(pDX, IDC_ANIM_TIME, data.m_Base_CB.etc.x);
        DDX_Text(pDX, IDC_ANIM_CUT_X, data.m_Base_CB.nRand_Loop_cutx_cuty.z);
        DDX_Text(pDX, IDC_ANIM_CUT_Y, data.m_Base_CB.nRand_Loop_cutx_cuty.w);

        DDX_Text(pDX, IDC_EFFECT_TIME, TOOL.m_fEffect_End_Time);
        DDX_Text(pDX, IDC_START_TIME, data.m_Base_CB.etc.y);
        DDX_Text(pDX, IDC_END_TIME, data.m_Base_CB.etc.z);
        
        if (pDX->m_bSaveAndValidate)
        {
            DDX_Check(pDX, IDC_BLOOP, bAnimLoop);
            data.m_Base_CB.nRand_Loop_cutx_cuty.y = bAnimLoop;
        }
        else
        {
            bAnimLoop = data.m_Base_CB.nRand_Loop_cutx_cuty.y;
            DDX_Check(pDX, IDC_BLOOP, bAnimLoop);
            
        }

        if (pDX->m_bSaveAndValidate)
        {
            DDX_Check(pDX, IDC_BBILL, bUseBillboard);
            data.m_bUse_billboard = bUseBillboard;
        }
        else
        {
            bUseBillboard = data.m_bUse_billboard;
            DDX_Check(pDX, IDC_BBILL, bUseBillboard);
        }
        DDX_Text(pDX, IDC_ALPHA, data.m_Base_CB.m_vColor.w);

    }
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
ON_WM_MOUSEACTIVATE()
ON_BN_CLICKED(IDC_ON, &Effect_Form2::OnBnClickedOn)
ON_BN_CLICKED(IDC_OFF, &Effect_Form2::OnBnClickedOff)
ON_BN_CLICKED(IDC_BLOOP, &Effect_Form2::OnBnClickedBloop)
ON_BN_CLICKED(IDC_BBILL, &Effect_Form2::OnBnClickedBbill)
ON_BN_CLICKED(IDC_FILTER_COLOR, &Effect_Form2::OnBnClickedFilterColor)
END_MESSAGE_MAP()


// Effect_Form2 메시지 처리기


void Effect_Form2::OnBnClickedForm2Update()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    UpdateData(TRUE);
 
    UpdateData(FALSE);
}


void Effect_Form2::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}




void Effect_Form2::OnCbnSelchangeMoveXExp1()
{
    int i = SendDlgItemMessageW(IDC_MOVE_X_EXP1, CB_GETCURSEL, 0, 0);
    if (TOOL.m_Render_List.size() > TOOL.m_iSel_Obj)
    {
           TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_Move_Data_X.exp1 = (Radius_exp)i;

    }
 //   TOOL.m_Cur_Option.m_Move_Data_X.exp1 = (Radius_exp)i;
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveXExp2()
{
    int i = SendDlgItemMessageW(IDC_MOVE_X_EXP2, CB_GETCURSEL, 0, 0);
    if (TOOL.m_Render_List.size() > TOOL.m_iSel_Obj)
    {
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_Move_Data_X.exp2 = (Radius_exp)i;

    }
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveYExp1()
{
    int i = SendDlgItemMessageW(IDC_MOVE_Y_EXP1, CB_GETCURSEL, 0, 0);
    if (TOOL.m_Render_List.size() > TOOL.m_iSel_Obj)
    {
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_Move_Data_Y.exp1 = (Radius_exp)i;

    }
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveYExp2()
{
    int i = SendDlgItemMessageW(IDC_MOVE_Y_EXP2, CB_GETCURSEL, 0, 0);
    if (TOOL.m_Render_List.size() > TOOL.m_iSel_Obj)
    {
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_Move_Data_Y.exp2 = (Radius_exp)i;
    }

    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveZExp1()
{
    int i = SendDlgItemMessageW(IDC_MOVE_Z_EXP1, CB_GETCURSEL, 0, 0);
    if (TOOL.m_Render_List.size() > TOOL.m_iSel_Obj)
    {
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_Move_Data_Z.exp1 = (Radius_exp)i;
    }
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveZExp2()
{
    int i = SendDlgItemMessageW(IDC_MOVE_Z_EXP2, CB_GETCURSEL, 0, 0);
    if (TOOL.m_Render_List.size() > TOOL.m_iSel_Obj)
    {
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_Move_Data_Z.exp2 = (Radius_exp)i;
    }
   // TOOL.m_Cur_Option.m_Move_Data_Z.exp2 = (Radius_exp)i;
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveRExp1()
{
    int i = SendDlgItemMessageW(IDC_MOVE_R_EXP1, CB_GETCURSEL, 0, 0);
    if (TOOL.m_Render_List.size() > TOOL.m_iSel_Obj)
    {
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_Move_Data_R.exp1 = (Radius_exp)i;
    }
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnCbnSelchangeMoveRExp2()
{
    int i = SendDlgItemMessageW(IDC_MOVE_R_EXP2, CB_GETCURSEL, 0, 0);
    if (TOOL.m_Render_List.size() > TOOL.m_iSel_Obj)
    {
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_Move_Data_R.exp2 = (Radius_exp)i;
    }
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


int Effect_Form2::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

    return CFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void Effect_Form2::OnBnClickedOn()
{
    if (TOOL.m_Render_List.size() > TOOL.m_iSel_Obj)
    {
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_bRend = true;

    }
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnBnClickedOff()
{
    if (TOOL.m_Render_List.size() > TOOL.m_iSel_Obj)
    {
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_bRend = false;

    }
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnBnClickedBloop()
{
    bAnimLoop = !bAnimLoop;
   
    UpdateData(true);
   
    //// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnBnClickedBbill()
{
    bUseBillboard = !bUseBillboard;
    UpdateData(true);
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Effect_Form2::OnBnClickedFilterColor()
{
    if (TOOL.m_Render_List.size() > TOOL.m_iSel_Obj)
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
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_Base_CB.m_vColor[0] = GetRValue(color) / 255.0f;
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_Base_CB.m_vColor[1] = GetGValue(color) / 255.0f;
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_Base_CB.m_vColor[2] = GetBValue(color) / 255.0f;
            //TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_Base_CB.m_vColor[3] = 1.0f;

        }
    }
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

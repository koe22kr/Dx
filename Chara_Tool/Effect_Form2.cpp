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
    Effect_Data& data = TOOL.m_Render_List.m_Base_Effect;
    DDX_Text(pDX, IDC_SCALE_X, data.m_vScale.x);
    DDX_Text(pDX, IDC_SCALE_Y, data.m_vScale.y);
    DDX_Text(pDX, IDC_SCALE_Z, data.m_vScale.z);
    DDX_Text(pDX, IDC_ROTATION_X, data.m_vRotation.x);
    DDX_Text(pDX, IDC_ROTATION_Y, data.m_vRotation.y);
    DDX_Text(pDX, IDC_ROTATION_Z, data.m_vRotation.z);
    DDX_Text(pDX, IDC_TRANS_X, data.m_vPos.x);
    DDX_Text(pDX, IDC_TRANS_Y, data.m_vPos.y);
    DDX_Text(pDX, IDC_TRANS_Z, data.m_vPos.z);
    
    DDX_Text(pDX, IDC_TARGET_X, data.m_vTargetPos.x);
    DDX_Text(pDX, IDC_TARGET_Y, data.m_vTargetPos.y);
    DDX_Text(pDX, IDC_TARGET_Z, data.m_vTargetPos.z);
    DDX_Text(pDX, IDC_SPEED, data.m_fSpeed_to_Target);


    DDX_Text(pDX, IDC_POWER1_X, data.m_vPower1.x);
    DDX_Text(pDX, IDC_POWER1_Y, data.m_vPower1.y);
    DDX_Text(pDX, IDC_POWER1_Z, data.m_vPower1.z);

    DDX_Text(pDX, IDC_POWER2_X, data.m_vPower2.x);
    DDX_Text(pDX, IDC_POWER2_Y, data.m_vPower2.y);
    DDX_Text(pDX, IDC_POWER2_Z, data.m_vPower2.z);

    DDX_Text(pDX, IDC_POWER3_X, data.m_vPower3.x);
    DDX_Text(pDX, IDC_POWER3_Y, data.m_vPower3.y);
    DDX_Text(pDX, IDC_POWER3_Z, data.m_vPower3.z);

    DDX_Text(pDX, IDC_FADEIN_TIME, data.m_fFadeInTime);
    DDX_Text(pDX, IDC_FADEOUT_TIME, data.m_fFadeOutTime);

    DDX_Text(pDX, IDC_LIFE_TIME, data.m_Life_Time);



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
END_MESSAGE_MAP()


// Effect_Form2 메시지 처리기


void Effect_Form2::OnBnClickedForm2Update()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    UpdateData(TRUE);

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

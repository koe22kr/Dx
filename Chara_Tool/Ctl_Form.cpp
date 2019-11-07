// Ctl_Form.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chara_Tool.h"
#include "Ctl_Form.h"
#include "afxdialogex.h"


// Ctl_Form 대화 상자

IMPLEMENT_DYNAMIC(Ctl_Form, CFormView)

Ctl_Form::Ctl_Form()
	: CFormView(IDD_Ctl_Form)
{

}

Ctl_Form::~Ctl_Form()
{

}

Ctl_Form* Ctl_Form::CreateOne(CWnd* pParent)
{
    Ctl_Form* one = new Ctl_Form;
    one->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 800), pParent, 0, NULL);
    return one;
}

void Ctl_Form::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Ctl_Form, CFormView)
END_MESSAGE_MAP()


// Ctl_Form 메시지 처리기

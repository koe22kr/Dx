#pragma once


// Ctl_Form 대화 상자

class Ctl_Form : public CFormView
{
	DECLARE_DYNAMIC(Ctl_Form)

public:
	Ctl_Form();   // 표준 생성자입니다.
	virtual ~Ctl_Form();
    static Ctl_Form* CreateOne(CWnd* pParent);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Ctl_Form };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
    
	DECLARE_MESSAGE_MAP()
};

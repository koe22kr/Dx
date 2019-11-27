#pragma once


// Effect_Form2 대화 상자

class Effect_Form2 : public CFormView
{
	DECLARE_DYNAMIC(Effect_Form2)

public:
	Effect_Form2();   // 표준 생성자입니다.
	virtual ~Effect_Form2();
    static Effect_Form2* CreateOne(CWnd* pParent);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Effect_Form2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedForm2Update();
//    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    virtual void OnInitialUpdate();
    afx_msg void OnCbnSelchangeMoveXExp1();
    afx_msg void OnCbnSelchangeMoveXExp2();
    afx_msg void OnCbnSelchangeMoveYExp1();
    afx_msg void OnCbnSelchangeMoveYExp2();
    afx_msg void OnCbnSelchangeMoveZExp1();
    afx_msg void OnCbnSelchangeMoveZExp2();
    afx_msg void OnCbnSelchangeMoveRExp1();
    afx_msg void OnCbnSelchangeMoveRExp2();
    afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
    afx_msg void OnBnClickedOn();
    afx_msg void OnBnClickedOff();
    afx_msg void OnBnClickedBloop();
    BOOL bAnimLoop;
    afx_msg void OnBnClickedBbill();
    BOOL bUseBillboard;
    afx_msg void OnBnClickedFilterColor();
};

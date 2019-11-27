#pragma once


// Effect_Form1 대화 상자

class Effect_Form1 : public CFormView
{
	DECLARE_DYNAMIC(Effect_Form1)

public:
	Effect_Form1();   // 표준 생성자입니다.
	virtual ~Effect_Form1();
    static Effect_Form1* CreateOne(CWnd* pParent);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Effect_Form1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedNewObj();
    afx_msg void OnLbnSelchangeObjList();
    afx_msg void OnBnClickedNewTexture();
    afx_msg void OnLbnSelchangeTextureList();
   // afx_msg void OnBnClickedUpdateButton();
    afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
    afx_msg void OnBnClickedSelectTexture();
    afx_msg void OnBnClickedSave();
    afx_msg void OnBnClickedLoad();
    afx_msg void OnBnClickedBackColor();
    afx_msg void OnBnClickedNameMody();
};

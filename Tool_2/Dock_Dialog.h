#pragma once


// Dock_Dialog 대화 상자

class Dock_Dialog : public CFormView
{
	DECLARE_DYNAMIC(Dock_Dialog)

public:
	Dock_Dialog();   // 표준 생성자입니다.
	virtual ~Dock_Dialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dock_Dialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};

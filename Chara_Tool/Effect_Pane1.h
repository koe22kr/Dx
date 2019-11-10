#pragma once

#include "Effect_Form1.h"
// Effect_Pane1

class Effect_Pane1 : public CDockablePane
{
	DECLARE_DYNAMIC(Effect_Pane1)

public:
	Effect_Pane1();
	virtual ~Effect_Pane1();
    Effect_Form1* m_Form1;
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};



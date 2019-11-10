#pragma once

#include "Effect_Form2.h"

// Effect_Pane2

class Effect_Pane2 : public CDockablePane
{
	DECLARE_DYNAMIC(Effect_Pane2)

public:
	Effect_Pane2();
	virtual ~Effect_Pane2();
    Effect_Form2* m_Form2;

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};



#pragma once

#include "Ctl_Form.h"
// Ctl_Pane

class Ctl_Pane : public CDockablePane
{
	DECLARE_DYNAMIC(Ctl_Pane)

public:
	Ctl_Pane();
	virtual ~Ctl_Pane();
    Ctl_Form* m_Form;
protected:
	DECLARE_MESSAGE_MAP()
public:

    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};



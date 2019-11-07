// Ctl_Pane.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chara_Tool.h"
#include "Ctl_Pane.h"


// Ctl_Pane

IMPLEMENT_DYNAMIC(Ctl_Pane, CDockablePane)

Ctl_Pane::Ctl_Pane()
{

}

Ctl_Pane::~Ctl_Pane()
{
}


BEGIN_MESSAGE_MAP(Ctl_Pane, CDockablePane)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



// Ctl_Pane 메시지 처리기





int Ctl_Pane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDockablePane::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  여기에 특수화된 작성 코드를 추가합니다.
    m_Form = Ctl_Form::CreateOne(this);
    return 0;
}


void Ctl_Pane::OnSize(UINT nType, int cx, int cy)
{
    CDockablePane::OnSize(nType, cx, cy);

    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
    if (m_Form)
    {
        m_Form->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
    }
}


int Ctl_Pane::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    CFrameWnd* pParentFrame = GetParentFrame();
    if (pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame))
    {
        return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);

    }
    return MA_NOACTIVATE;
}

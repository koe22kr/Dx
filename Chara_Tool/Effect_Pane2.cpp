// Effect_Pane2.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chara_Tool.h"
#include "Effect_Pane2.h"


// Effect_Pane2

IMPLEMENT_DYNAMIC(Effect_Pane2, CDockablePane)

Effect_Pane2::Effect_Pane2()
{

}

Effect_Pane2::~Effect_Pane2()
{
}


BEGIN_MESSAGE_MAP(Effect_Pane2, CDockablePane)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



// Effect_Pane2 메시지 처리기




int Effect_Pane2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDockablePane::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  여기에 특수화된 작성 코드를 추가합니다.
    m_Form2 = Effect_Form2::CreateOne(this);
    return 0;
}


void Effect_Pane2::OnSize(UINT nType, int cx, int cy)
{
    CDockablePane::OnSize(nType, cx, cy);
    if (m_Form2)
    {
        m_Form2->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
    }
    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


int Effect_Pane2::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    CFrameWnd* pParentFrame = GetParentFrame();
    if (pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame))
    {
        return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
    }
    return MA_NOACTIVATE;
}

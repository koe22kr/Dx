
// Chara_ToolView.cpp: CCharaToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Chara_Tool.h"
#endif

#include "Chara_ToolDoc.h"
#include "Chara_ToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCharaToolView

IMPLEMENT_DYNCREATE(CCharaToolView, CView)

BEGIN_MESSAGE_MAP(CCharaToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCharaToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CCharaToolView 생성/소멸

CCharaToolView::CCharaToolView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CCharaToolView::~CCharaToolView()
{
}

BOOL CCharaToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCharaToolView 그리기

void CCharaToolView::OnDraw(CDC* /*pDC*/)
{
	CCharaToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CCharaToolView 인쇄


void CCharaToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCharaToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCharaToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCharaToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CCharaToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CCharaToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCharaToolView 진단

#ifdef _DEBUG
void CCharaToolView::AssertValid() const
{
	CView::AssertValid();
}

void CCharaToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCharaToolDoc* CCharaToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCharaToolDoc)));
	return (CCharaToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CCharaToolView 메시지 처리기


LRESULT CCharaToolView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    CCharaToolApp* pApp = (CCharaToolApp*)AfxGetApp();
    HWND hWnd = pApp->m_Tool.m_hWnd;

    pApp->m_Tool.MsgProc(hWnd, message, wParam, lParam);
    return CView::WindowProc(message, wParam, lParam);
}


void CCharaToolView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);
    CCharaToolApp* pApp = (CCharaToolApp*)AfxGetApp();
    pApp->m_Tool.m_Device.Resize(cx, cy);
    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


// Tool_1View.h: CTool1View 클래스의 인터페이스
//

#pragma once


class CTool1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CTool1View() noexcept;
	DECLARE_DYNCREATE(CTool1View)

// 특성입니다.
public:
	CTool1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CTool1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Tool_1View.cpp의 디버그 버전
inline CTool1Doc* CTool1View::GetDocument() const
   { return reinterpret_cast<CTool1Doc*>(m_pDocument); }
#endif


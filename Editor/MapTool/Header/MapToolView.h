
// MapToolView.h : CMapToolView 클래스의 인터페이스
//

#pragma once

#include "MapToolDoc.h"
#include "MainMapTool.h"
#include "Object.h"

class CMapToolView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMapToolView();
	DECLARE_DYNCREATE(CMapToolView)

// 특성입니다.
public:
	CMapToolDoc* GetDocument() const;

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
	virtual ~CMapToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

// add function
public:
	virtual void OnInitialUpdate();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

// add valuable
protected:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	SP(CMainMapTool) m_spMainMapTool = nullptr;

	class CToolMenuView* m_pMenuView;
};

#ifndef _DEBUG  // MapToolView.cpp의 디버그 버전
inline CMapToolDoc* CMapToolView::GetDocument() const
   { return reinterpret_cast<CMapToolDoc*>(m_pDocument); }
#endif



// 3DEditorView.h : CMy3DEditorView Ŭ������ �������̽�
//

#pragma once

#include "3DEditorDoc.h"
#include "MainEditor.h"

#include "Object.h"

BEGIN(Engine)
class CGameObject;
END

class CMy3DEditorView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy3DEditorView();
	DECLARE_DYNCREATE(CMy3DEditorView)

// Ư���Դϴ�.
public:
	CMy3DEditorDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMy3DEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

protected:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	SP(CMainEditor) m_spMainEditor = nullptr;

	class CInspectorView* m_pInspectorView;
};

#ifndef _DEBUG  // 3DEditorView.cpp�� ����� ����
inline CMy3DEditorDoc* CMy3DEditorView::GetDocument() const
   { return reinterpret_cast<CMy3DEditorDoc*>(m_pDocument); }
#endif

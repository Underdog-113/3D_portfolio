
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once

class CMainFrame : public CFrameWnd
{
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

// add function
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// add  valuable
protected:
	GETTOR(CSplitterWnd, m_mainSplitter, {}, MainSplitter);

	class CMy3DEditorView* m_pEditorView = nullptr;
	class CHierarchyView* m_pHierarchyView = nullptr;
};




// 3DEditorView.cpp : CMy3DEditorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "3DEditor.h"
#endif

#include "3DEditorDoc.h"
#include "3DEditorView.h"
#include "DeviceManager.h"
#include "InspectorView.h"

#include "DataStore.h"
#include "MeshStore.h"
#include "TextureStore.h"
#include "MathHelper.h"

#include "WndApp.h"
#include "FRC.h"
#include "MainFrm.h"
#include "MainEditor.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "Layer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy3DEditorView
IMPLEMENT_DYNCREATE(CMy3DEditorView, CView)

BEGIN_MESSAGE_MAP(CMy3DEditorView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

//HWND g_hWnd;

CMy3DEditorView::CMy3DEditorView()
{
}

CMy3DEditorView::~CMy3DEditorView()
{
	m_spMainEditor->OnDestroy();
	m_spMainEditor.reset();

	Engine::CWndApp::GetInstance()->DestroyInstance();
	Engine::CFRC::GetInstance()->DestroyInstance();
	Engine::CDataStore::GetInstance()->DestroyInstance();
	Engine::CMeshStore::GetInstance()->DestroyInstance();
	Engine::CTextureStore::GetInstance()->DestroyInstance();
	Engine::CDeviceManager::GetInstance()->DestroyInstance();
	GET_MATH->DestroyInstance();
}

BOOL CMy3DEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy3DEditorView �׸���
void CMy3DEditorView::OnDraw(CDC* /*pDC*/)
{
	CMy3DEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	
	if (Engine::CFRC::GetInstance()->FrameLock())
	{
		m_spMainEditor->FixedUpdate();
		m_spMainEditor->Update();
		m_spMainEditor->LateUpdate();

		m_spMainEditor->PreRender();
		m_spMainEditor->Render();
		m_spMainEditor->PostRender();
	}
}

// CMy3DEditorView �μ�
BOOL CMy3DEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy3DEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy3DEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

// CMy3DEditorView ����
#ifdef _DEBUG
void CMy3DEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DEditorDoc* CMy3DEditorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DEditorDoc)));
	return (CMy3DEditorDoc*)m_pDocument;
}
#endif //_DEBUG

// CMy3DEditorView �޽��� ó����
void CMy3DEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

#pragma region SubEnginesAwake
	Engine::CDataStore::GetInstance()->Awake();
	Engine::CDataStore::GetInstance()->InitDataMap((_uint)EDataID::NumOfDataID);
	Engine::CDataStore::GetInstance()->AddDataSection(L"Player", (_uint)EDataID::Player);
	Engine::CDataStore::GetInstance()->AddDataSection(L"Scene", (_uint)EDataID::Scene);
	Engine::CDataStore::GetInstance()->AddDataSection(L"Camera", (_uint)EDataID::Camera);

	Engine::CFRC::GetInstance()->Awake();
	Engine::CWndApp::GetInstance()->Awake();
	Engine::CDeviceManager::GetInstance()->Awake();
	Engine::CTextureStore::GetInstance()->Awake();
	Engine::CMeshStore::GetInstance()->Awake();
#pragma endregion

#pragma region SubEnginesStart
	Engine::CDataStore::GetInstance()->Start();
	Engine::CWndApp::GetInstance()->SetHWnd(m_hWnd);
	Engine::CWndApp::GetInstance()->SetWndWidth(VIEWCX);
	Engine::CWndApp::GetInstance()->SetWndHeight(VIEWCY);
	Engine::CDeviceManager::GetInstance()->Start();
	Engine::CFRC::GetInstance()->Start();
	Engine::CTextureStore::GetInstance()->Start();
	Engine::CMeshStore::GetInstance()->Start();
#pragma endregion

	m_spMainEditor = CMainEditor::Create();

	m_spMainEditor->Awake();
	m_spMainEditor->Start();

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());

	RECT rcMainRect = {};
	pMain->GetWindowRect(&rcMainRect);

	::SetRect(&rcMainRect, 0, 0, rcMainRect.right - rcMainRect.left, rcMainRect.bottom - rcMainRect.top);

	RECT rcView = {};
	GetClientRect(&rcView);
	int iGapX = rcMainRect.right - rcView.right;
	int iGapY = rcMainRect.bottom - rcView.bottom;

	pMain->SetWindowPos(nullptr, 0, 0, VIEWCX + 400 + iGapX, VIEWCY + iGapY, SWP_NOZORDER | SWP_NOMOVE);

	SetTimer(0, 0, nullptr);

	m_pInspectorView = dynamic_cast<CInspectorView*>(pMain->m_mainSplitter.GetPane(0, 1));
}

void CMy3DEditorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	InvalidateRect(nullptr, FALSE);
	CView::OnTimer(nIDEvent);
}

void CMy3DEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CView::OnLButtonDown(nFlags, point);
}

void CMy3DEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);
}

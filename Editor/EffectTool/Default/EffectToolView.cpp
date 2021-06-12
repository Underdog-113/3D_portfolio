
// EffectToolView.cpp : CEffectToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "EffectTool.h"
#endif

#include "EffectToolDoc.h"
#include "EffectToolView.h"
#include "Inspector.h"
#include "DeviceManager.h"

#include "DataStore.h"
#include "MeshStore.h"
#include "TextureStore.h"
#include "MathHelper.h"

#include "WndApp.h"
#include "FRC.h"
#include "MainFrm.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "Layer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEffectToolView

IMPLEMENT_DYNCREATE(CEffectToolView, CView)

BEGIN_MESSAGE_MAP(CEffectToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CEffectToolView 생성/소멸

CEffectToolView::CEffectToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CEffectToolView::~CEffectToolView()
{
	Engine::CWndApp::GetInstance()->DestroyInstance();
	Engine::CFRC::GetInstance()->DestroyInstance();
	Engine::CDeviceManager::GetInstance()->DestroyInstance();
	GET_MATH->DestroyInstance();
}

BOOL CEffectToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}
// CEffectToolView 그리기

void CEffectToolView::OnDraw(CDC* /*pDC*/)
{
	CEffectToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	if (Engine::CFRC::GetInstance()->FrameLock())
	{
		m_spMainEffectTool->FixedUpdate();
		m_spMainEffectTool->Update();
		m_spMainEffectTool->LateUpdate();

		m_spMainEffectTool->PreRender();
		m_spMainEffectTool->Render();
		m_spMainEffectTool->PostRender();
	}
}


// CEffectToolView 인쇄

BOOL CEffectToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CEffectToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CEffectToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CEffectToolView 진단

#ifdef _DEBUG
void CEffectToolView::AssertValid() const
{
	CView::AssertValid();
}

void CEffectToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEffectToolDoc* CEffectToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEffectToolDoc)));
	return (CEffectToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CEffectToolView 메시지 처리기


void CEffectToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
#pragma region SubEnginesAwake
	Engine::CFRC::GetInstance()->Awake();
	Engine::CWndApp::GetInstance()->Awake();
	Engine::CDeviceManager::GetInstance()->Awake();
#pragma endregion

#pragma region SubEnginesStart
	Engine::CWndApp::GetInstance()->SetHWnd(m_hWnd);
	Engine::CWndApp::GetInstance()->SetWndWidth(VIEWCX);
	Engine::CWndApp::GetInstance()->SetWndHeight(VIEWCY);
	Engine::CDeviceManager::GetInstance()->Start();
	Engine::CFRC::GetInstance()->Start();
#pragma endregion

	m_spMainEffectTool = CMainEditor::Create();

	m_spMainEffectTool->Awake();
	m_spMainEffectTool->Start();

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

	m_pInspectorView = dynamic_cast<CInspector*>(pMain->GetMainSplitter().GetPane(0, 1));

}


void CEffectToolView::OnTimer(UINT_PTR nIDEvent)
{
	InvalidateRect(nullptr, FALSE);

	CView::OnTimer(nIDEvent);
}

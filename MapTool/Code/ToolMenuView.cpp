// ToolMenuView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "ToolMenuView.h"

#include "MainFrm.h"
#include "MapToolView.h"
#include "EditorScene.h"
#include "Object.h"

// CToolMenuView

IMPLEMENT_DYNCREATE(CToolMenuView, CFormView)

CToolMenuView::CToolMenuView()
	: CFormView(IDD_TOOLMENUVIEW)
{

}

CToolMenuView::~CToolMenuView()
{
}

void CToolMenuView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_posX);
	DDX_Control(pDX, IDC_EDIT2, m_posY);
	DDX_Control(pDX, IDC_EDIT3, m_posZ);

	DDX_Control(pDX, IDC_EDIT4, m_rotX);
	DDX_Control(pDX, IDC_EDIT8, m_rotY);
	DDX_Control(pDX, IDC_EDIT5, m_rotZ);

	DDX_Control(pDX, IDC_EDIT6, m_scaleX);
	DDX_Control(pDX, IDC_EDIT9, m_scaleY);
	DDX_Control(pDX, IDC_EDIT7, m_scaleZ);

	DDX_Control(pDX, IDC_SPIN1, m_spinPosX);
	DDX_Control(pDX, IDC_SPIN4, m_spinPosY);
	DDX_Control(pDX, IDC_SPIN7, m_spinPosZ);

	DDX_Control(pDX, IDC_SPIN2, m_spinRotX);
	DDX_Control(pDX, IDC_SPIN5, m_spinRotY);
	DDX_Control(pDX, IDC_SPIN8, m_spinRotZ);

	DDX_Control(pDX, IDC_SPIN3, m_spinScaleX);
	DDX_Control(pDX, IDC_SPIN6, m_spinScaleY);
	DDX_Control(pDX, IDC_SPIN9, m_spinScaleZ);

	//DDX_Control(pDX, IDC_TREE1, m_Tree);
	//DDX_Control(pDX, IDC_LIST2, m_TreeList);
}

BEGIN_MESSAGE_MAP(CToolMenuView, CFormView)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CToolMenuView::OnPosX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, &CToolMenuView::OnPosY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN7, &CToolMenuView::OnPosZ)

	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CToolMenuView::OnRotX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, &CToolMenuView::OnRotY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN8, &CToolMenuView::OnRotZ)

	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CToolMenuView::OnScaleX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, &CToolMenuView::OnScaleY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN9, &CToolMenuView::OnScaleZ)
END_MESSAGE_MAP()


// CToolMenuView 진단입니다.

#ifdef _DEBUG
void CToolMenuView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CToolMenuView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CToolMenuView 메시지 처리기입니다.

void CToolMenuView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//HTREEITEM hRoot[2];
	//HTREEITEM hDynamicMeshChild[4];
	//HTREEITEM hStaticMeshChild[1];

	//hRoot[0] = m_Tree.InsertItem(L"DynamicMesh", 0, 1, TVI_ROOT, TVI_FIRST);
	//hDynamicMeshChild[0] = m_Tree.InsertItem(L"Player", 1, 1, hRoot[0], TVI_FIRST);
	//hDynamicMeshChild[1] = m_Tree.InsertItem(L"Boss", 1, 1, hRoot[0], TVI_LAST);
	//hDynamicMeshChild[2] = m_Tree.InsertItem(L"Monster", 1, 1, hRoot[0], TVI_LAST);
	//hDynamicMeshChild[3] = m_Tree.InsertItem(L"DynamicObject", 1, 1, hRoot[0], TVI_LAST);

	//hRoot[1] = m_Tree.InsertItem(L"StaticMesh", 0, 1, TVI_ROOT, TVI_LAST);
	//hStaticMeshChild[0] = m_Tree.InsertItem(L"StaticObject", 1, 1, hRoot[1], TVI_FIRST);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_posX.SetWindowTextW(_T("0.00"));
	m_posY.SetWindowTextW(_T("0.00"));
	m_posZ.SetWindowTextW(_T("0.00"));

	m_rotX.SetWindowTextW(_T("0.00"));
	m_rotY.SetWindowTextW(_T("0.00"));
	m_rotZ.SetWindowTextW(_T("0.00"));

	m_scaleX.SetWindowTextW(_T("0.00"));
	m_scaleY.SetWindowTextW(_T("0.00"));
	m_scaleZ.SetWindowTextW(_T("0.00"));

	m_valueMin = -9999;
	m_valueMax = 9999;

	m_spinPosX.SetRange(m_valueMin, m_valueMax);
	m_spinPosX.SetPos(0);
	m_spinPosY.SetRange(m_valueMin, m_valueMax);
	m_spinPosY.SetPos(0);
	m_spinPosZ.SetRange(m_valueMin, m_valueMax);
	m_spinPosZ.SetPos(0);

	m_spinRotX.SetRange(m_valueMin, m_valueMax);
	m_spinRotX.SetPos(0);
	m_spinRotY.SetRange(m_valueMin, m_valueMax);
	m_spinRotY.SetPos(0);
	m_spinRotZ.SetRange(m_valueMin, m_valueMax);
	m_spinRotZ.SetPos(0);

	m_spinScaleX.SetRange(m_valueMin, m_valueMax);
	m_spinScaleX.SetPos(0);
	m_spinScaleY.SetRange(m_valueMin, m_valueMax);
	m_spinScaleY.SetPos(0);
	m_spinScaleZ.SetRange(m_valueMin, m_valueMax);
	m_spinScaleZ.SetPos(0);
}

void CToolMenuView::Update(void)
{
}

void CToolMenuView::OnPosX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();
	pCurObj->GetTransform()->SetPositionX(GetEditControlData(&m_posX, pNMUpDown));

	*pResult = 0;
}


void CToolMenuView::OnPosY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();
	pCurObj->GetTransform()->SetPositionY(GetEditControlData(&m_posY, pNMUpDown));

	*pResult = 0;
}


void CToolMenuView::OnPosZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();
	pCurObj->GetTransform()->SetPositionZ(GetEditControlData(&m_posZ, pNMUpDown));

	*pResult = 0;
}


void CToolMenuView::OnRotX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();
	pCurObj->GetTransform()->SetRotationX(GetEditControlData(&m_rotX, pNMUpDown));

	*pResult = 0;
}


void CToolMenuView::OnRotY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();
	pCurObj->GetTransform()->SetRotationY(GetEditControlData(&m_rotY, pNMUpDown));

	*pResult = 0;
}


void CToolMenuView::OnRotZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();
	pCurObj->GetTransform()->SetRotationZ(GetEditControlData(&m_rotZ, pNMUpDown));

	*pResult = 0;
}


void CToolMenuView::OnScaleX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();
	pCurObj->GetTransform()->SetSizeX(GetEditControlData(&m_scaleX, pNMUpDown));

	*pResult = 0;
}


void CToolMenuView::OnScaleY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();
	pCurObj->GetTransform()->SetSizeY(GetEditControlData(&m_scaleY, pNMUpDown));

	*pResult = 0;
}


void CToolMenuView::OnScaleZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();
	pCurObj->GetTransform()->SetSizeZ(GetEditControlData(&m_scaleZ, pNMUpDown));

	*pResult = 0;
}

void CToolMenuView::SpinBtn(LPNMUPDOWN pNMUpDown, CEdit* pBtn, _float fVal)
{
	// 값 = 현재값 + 증/감
	_float nValue = fVal + (float)((pNMUpDown->iDelta) / 10.f);

	if ((m_valueMin <= nValue) && (m_valueMax >= nValue))
	{
		CString cstrValue;
		cstrValue.Format(_T("%.8f"), nValue);
		pBtn->SetWindowTextW(cstrValue);
	}
}

_float CToolMenuView::GetEditControlData(CEdit* pEdit, LPNMUPDOWN pNMUpDown)
{
	CString cstrValue;
	pEdit->GetWindowTextW(cstrValue);

	_float value = (_float)_tstof(cstrValue);
	SpinBtn(pNMUpDown, pEdit, value);

	return value;
}

void CToolMenuView::SetPosition(_float3 vPos)
{
	CString cstrValue;
	cstrValue.Format(_T("%.8f"), vPos.x);
	m_posX.SetWindowTextW(cstrValue);

	cstrValue.Format(_T("%.8f"), vPos.y);
	m_posY.SetWindowTextW(cstrValue);
	m_spinPosY.SetPos((_int)vPos.y);

	cstrValue.Format(_T("%.8f"), vPos.z);
	m_posZ.SetWindowTextW(cstrValue);
	m_spinPosZ.SetPos((_int)vPos.z);
}

void CToolMenuView::SetRotation(_float3 vRot)
{
	CString cstrValue;
	cstrValue.Format(_T("%.8f"), vRot.x);
	m_rotX.SetWindowTextW(cstrValue);
	m_spinRotX.SetPos((_int)vRot.x);

	cstrValue.Format(_T("%.8f"), vRot.y);
	m_rotY.SetWindowTextW(cstrValue);
	m_spinRotY.SetPos((_int)vRot.y);

	cstrValue.Format(_T("%.8f"), vRot.z);
	m_rotZ.SetWindowTextW(cstrValue);
	m_spinRotZ.SetPos((_int)vRot.z);
}

void CToolMenuView::SetScale(_float3 vScale)
{
	CString cstrValue;
	cstrValue.Format(_T("%.8f"), vScale.x);
	m_scaleX.SetWindowTextW(cstrValue);
	m_spinScaleX.SetPos((_int)vScale.x);

	cstrValue.Format(_T("%.8f"), vScale.y);
	m_scaleY.SetWindowTextW(cstrValue);
	m_spinScaleY.SetPos((_int)vScale.y);

	cstrValue.Format(_T("%.8f"), vScale.z);
	m_scaleZ.SetWindowTextW(cstrValue);
	m_spinScaleZ.SetPos((_int)vScale.z);
}
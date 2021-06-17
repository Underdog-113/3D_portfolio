// ToolMenuView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "ToolMenuView.h"

#include "MainFrm.h"
#include "MapToolView.h"
#include "EditorScene.h"
#include "Object.h"
#include "Layer.h"
#include "MeshData.h"

#include "AabbCollider.h"
#include "RayCollider.h"

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

	DDX_Control(pDX, IDC_TREE3, m_tree);
	DDX_Control(pDX, IDC_LIST2, m_meshTreeList);
	DDX_Control(pDX, IDC_LIST4, m_textureTreeList);
	DDX_Control(pDX, IDC_EDIT11, m_curObjName);
	DDX_Control(pDX, IDC_EDIT10, m_saveFileName);
	DDX_Control(pDX, IDC_CHECK5, m_initTexture);
	DDX_Control(pDX, IDC_COMBO4, m_layerID);
	DDX_Control(pDX, IDC_CHECK1, m_showAllCol);

	DDX_Control(pDX, IDC_RADIO1, m_colType[0]);
	DDX_Control(pDX, IDC_RADIO2, m_colType[1]);
	DDX_Control(pDX, IDC_RADIO3, m_colType[2]);
	DDX_Control(pDX, IDC_COMBO5, m_colliderID);
	DDX_Control(pDX, IDC_EDIT14, m_aabbSize);
	DDX_Control(pDX, IDC_EDIT15, m_aabbOffset);
	DDX_Control(pDX, IDC_BUTTON11, m_addColC);
	DDX_Control(pDX, IDC_COMBO6, m_aabbCnt);
	DDX_Control(pDX, IDC_CHECK6, m_selectedAABBCol);
	DDX_Control(pDX, IDC_EDIT17, m_rayOffSet);
	DDX_Control(pDX, IDC_EDIT16, m_rayDir);
	DDX_Control(pDX, IDC_EDIT18, m_rayLen);
	DDX_Control(pDX, IDC_COMBO8, m_rayType);
	DDX_Control(pDX, IDC_COMBO7, m_rayCnt);
	DDX_Control(pDX, IDC_CHECK7, m_selectedRayCol);
	DDX_Control(pDX, IDC_CHECK3, m_renderAlpha);
	DDX_Control(pDX, IDC_LIST1, m_objList);
	DDX_Control(pDX, IDC_CHECK9, m_curObjNameChk);
	DDX_Control(pDX, IDC_EDIT19, m_obbOffset);
	DDX_Control(pDX, IDC_EDIT20, m_obbSize);
	DDX_Control(pDX, IDC_COMBO9, m_obbCnt);
	DDX_Control(pDX, IDC_CHECK8, m_selectedObbCol);
	DDX_Control(pDX, IDC_CHECK2, m_showObjectChk);
	DDX_Control(pDX, IDC_COMBO1, m_loadFileName);
	DDX_Control(pDX, IDC_EDIT21, m_obbRotOffset);
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

	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE3, &CToolMenuView::OnTvnSelchangedTree)
	ON_LBN_SELCHANGE(IDC_LIST2, &CToolMenuView::OnLbnSelchangeMeshList)
	ON_BN_CLICKED(IDC_BUTTON5, &CToolMenuView::OnBnClickedPositionBtn)
	ON_BN_CLICKED(IDC_BUTTON6, &CToolMenuView::OnBnClickedRotationBtn)
	ON_BN_CLICKED(IDC_BUTTON7, &CToolMenuView::OnBnClickedScaleBtn)
	ON_LBN_SELCHANGE(IDC_LIST4, &CToolMenuView::OnLbnSelchangeTextureList)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CToolMenuView::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BUTTON3, &CToolMenuView::OnBnClickedCreatePrefBtn)
	ON_BN_CLICKED(IDC_BUTTON16, &CToolMenuView::OnBnClickedCreateMesh)
	ON_BN_CLICKED(IDC_CHECK9, &CToolMenuView::OnBnClickedCurObjectNameChk)
	ON_BN_CLICKED(IDC_CHECK2, &CToolMenuView::OnBnClickedShowObjectChk)

	/* save & load */
	ON_BN_CLICKED(IDC_BUTTON1, &CToolMenuView::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CToolMenuView::OnBnClickedLoadBtn)

	/* collision */
	ON_BN_CLICKED(IDC_BUTTON11, &CToolMenuView::OnBnClickedAddCollisionCBtn)


	/* ray */
	ON_BN_CLICKED(IDC_BUTTON13, &CToolMenuView::OnBnClickedCreateRayColliderBtn)
	ON_BN_CLICKED(IDC_BUTTON15, &CToolMenuView::OnBnClickedModifyRayColBtn)
	ON_BN_CLICKED(IDC_BUTTON14, &CToolMenuView::OnBnClickedDelRayColliderBtn)
	ON_BN_CLICKED(IDC_CHECK7, &CToolMenuView::OnBnClickedSelectedRayCol)
	ON_CBN_SELCHANGE(IDC_COMBO7, &CToolMenuView::OnCbnSelchangeRayList)

	/* aabb */
	ON_BN_CLICKED(IDC_BUTTON4, &CToolMenuView::OnBnClickedCreateAABBColliderBtn)
	ON_BN_CLICKED(IDC_BUTTON12, &CToolMenuView::OnBnClickedModifyAABBColBtn)
	ON_BN_CLICKED(IDC_BUTTON10, &CToolMenuView::OnBnClickedDelAABBColliderBtn)
	ON_BN_CLICKED(IDC_CHECK6, &CToolMenuView::OnBnClickedSelectedAABBCol)
	ON_CBN_SELCHANGE(IDC_COMBO6, &CToolMenuView::OnCbnSelchangeAABBList)

	/* obb */
	ON_BN_CLICKED(IDC_BUTTON17, &CToolMenuView::OnBnClickedCreateObbColliderBtn)
	ON_BN_CLICKED(IDC_BUTTON19, &CToolMenuView::OnBnClickedModifyObbColBtn)
	ON_BN_CLICKED(IDC_BUTTON18, &CToolMenuView::OnBnClickedDelObbColliderBtn)
	ON_BN_CLICKED(IDC_CHECK8, &CToolMenuView::OnBnClickedSelectedObbCol)
	ON_CBN_SELCHANGE(IDC_COMBO9, &CToolMenuView::OnCbnSelchangeObbList)

	/* obj list */
	ON_BN_CLICKED(IDC_BUTTON20, &CToolMenuView::OnBnClickedDelObjectWithObjList)
	ON_LBN_SELCHANGE(IDC_LIST1, &CToolMenuView::OnLbnSelchangeObjectList)

	/* .. */

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
	HTREEITEM root[4]; // mesh, texture, collider, prefab, stage
	HTREEITEM dynamicMeshChild[3];
	HTREEITEM staticMeshChild[8];
	HTREEITEM textureChild[17];
	HTREEITEM prefabChild[4];

	root[0] = m_tree.InsertItem(L"Dynamic", 0, 1, TVI_ROOT, TVI_FIRST);
	dynamicMeshChild[0] = m_tree.InsertItem(L"Player", 1, 1, root[0], TVI_FIRST);
	dynamicMeshChild[1] = m_tree.InsertItem(L"Monster", 1, 1, root[0], TVI_FIRST);
	dynamicMeshChild[2] = m_tree.InsertItem(L"Object", 1, 1, root[0], TVI_FIRST);

	root[1] = m_tree.InsertItem(L"Static", 0, 1, TVI_ROOT, TVI_LAST);
	staticMeshChild[0] = m_tree.InsertItem(L"Map", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[1] = m_tree.InsertItem(L"MainMenu", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[2] = m_tree.InsertItem(L"CatPaw", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[3] = m_tree.InsertItem(L"Weapon_Kiana", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[4] = m_tree.InsertItem(L"Weapon_Monster", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[5] = m_tree.InsertItem(L"Weapon_Sakura", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[6] = m_tree.InsertItem(L"Weapon_Theresa", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[7] = m_tree.InsertItem(L"Static", 1, 1, root[1], TVI_FIRST);

	root[2] = m_tree.InsertItem(L"Texture", 0, 1, TVI_ROOT, TVI_LAST);
	// Player texture
	textureChild[0] = m_tree.InsertItem(L"Kiana_Body", 1, 1, root[2], TVI_FIRST);
	textureChild[1] = m_tree.InsertItem(L"Kiana_CatPaw", 1, 1, root[2], TVI_FIRST);
	textureChild[2] = m_tree.InsertItem(L"Kiana_Weapon_1", 1, 1, root[2], TVI_FIRST);
	textureChild[3] = m_tree.InsertItem(L"Kiana_Weapon_2", 1, 1, root[2], TVI_FIRST);
	textureChild[4] = m_tree.InsertItem(L"Sakura_Body", 1, 1, root[2], TVI_FIRST);
	textureChild[5] = m_tree.InsertItem(L"Sakura_Weapon", 1, 1, root[2], TVI_FIRST);
	textureChild[6] = m_tree.InsertItem(L"Theresa_Body", 1, 1, root[2], TVI_FIRST);
	textureChild[7] = m_tree.InsertItem(L"Theresa_Weapon", 1, 1, root[2], TVI_FIRST);
	// Boss, Monster texture
	textureChild[8] = m_tree.InsertItem(L"Bronya", 1, 1, root[2], TVI_FIRST);
	textureChild[9] = m_tree.InsertItem(L"Ganesha", 1, 1, root[2], TVI_FIRST);
	textureChild[10] = m_tree.InsertItem(L"Axe_Body", 1, 1, root[2], TVI_FIRST);
	textureChild[11] = m_tree.InsertItem(L"Lancer_Body", 1, 1, root[2], TVI_FIRST);
	textureChild[12] = m_tree.InsertItem(L"Ninza_Body", 1, 1, root[2], TVI_FIRST);
	textureChild[13] = m_tree.InsertItem(L"Ninza_Weapon", 1, 1, root[2], TVI_FIRST);
	textureChild[14] = m_tree.InsertItem(L"Robot_Body", 1, 1, root[2], TVI_FIRST);
	textureChild[15] = m_tree.InsertItem(L"Scout_Body", 1, 1, root[2], TVI_FIRST);
	textureChild[16] = m_tree.InsertItem(L"Spider_Body", 1, 1, root[2], TVI_FIRST);

	root[3] = m_tree.InsertItem(L"Prefab", 0, 1, TVI_ROOT, TVI_LAST);
	prefabChild[0] = m_tree.InsertItem(L"Player", 1, 1, root[3], TVI_FIRST);
	prefabChild[1] = m_tree.InsertItem(L"Monster", 1, 1, root[3], TVI_FIRST);
	prefabChild[2] = m_tree.InsertItem(L"DynamicObject", 1, 1, root[3], TVI_FIRST);
	prefabChild[3] = m_tree.InsertItem(L"StaticObject", 1, 1, root[3], TVI_FIRST);


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

	m_initTexture.EnableWindow(false);
	m_showAllCol.EnableWindow(false);
	m_colType[0].EnableWindow(false);
	m_colType[1].EnableWindow(false);
	m_colType[2].EnableWindow(false);
	m_selectedAABBCol.EnableWindow(false);
	m_selectedRayCol.EnableWindow(false);
	m_selectedObbCol.EnableWindow(false);

	m_layerID.AddString(L"Player");
	m_layerID.AddString(L"Enemy");
	m_layerID.AddString(L"Map");

	m_colliderID.AddString(L"Floor");
	m_colliderID.AddString(L"Wall");
	m_colliderID.AddString(L"Player");
	m_colliderID.AddString(L"Enemy");
	m_colliderID.AddString(L"Trigger");

	m_rayType.AddString(L"ALL_INF"); // 앞뒤로 무한하게 쏨 (직선)
	m_rayType.AddString(L"LIMITED"); // 선분
	m_rayType.AddString(L"NEGATIVE_INF"); // 레이 반대방향으로만 무한
	m_rayType.AddString(L"POSITIVE_INF"); // 시작지점부터 레이 방향으로만 무한

	m_renderAlpha.SetCheck(0);

	//std::wstring wstr = (*Engine::GET_CUR_SCENE->GetLayers()[(_int)ELayerID::Map]->GetGameObjects().begin())->GetName();
	//m_objList.AddString(wstr.c_str());
}

void CToolMenuView::Update(void)
{
}

void CToolMenuView::OnPosX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	CString cstrVal;

	if (m_selectedAABBCol)
	{
		m_aabbCnt.GetLBText(m_aabbCnt.GetCurSel(), cstrVal);
		std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
		_int idx = WstrToInt(wstr);

		_float3 pos = static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetOffset();

		pos.x = GetEditControlData(&m_posX, pNMUpDown);

		static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetOffsetOrigin(pos);
	}
	else if (m_selectedObbCol)
	{
		m_obbCnt.GetLBText(m_obbCnt.GetCurSel(), cstrVal);
		std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
		_int idx = WstrToInt(wstr);

		_float3 pos = static_cast<Engine::CObbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetOffset();

		pos.x = GetEditControlData(&m_posX, pNMUpDown);

		static_cast<Engine::CObbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetOffsetOrigin(pos);
	}
	else
		pCurObj->GetTransform()->SetPositionX(GetEditControlData(&m_posX, pNMUpDown));

	*pResult = 0;
}


void CToolMenuView::OnPosY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	CString cstrVal;

	if (m_selectedAABBCol)
	{
		m_aabbCnt.GetLBText(m_aabbCnt.GetCurSel(), cstrVal);
		std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
		_int idx = WstrToInt(wstr);

		_float3 pos = static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetOffset();

		pos.y = GetEditControlData(&m_posY, pNMUpDown);

		static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetOffsetOrigin(pos);
	}
	else
		pCurObj->GetTransform()->SetPositionY(GetEditControlData(&m_posY, pNMUpDown));

	*pResult = 0;
}


void CToolMenuView::OnPosZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	CString cstrVal;

	if (m_selectedAABBCol)
	{
		m_aabbCnt.GetLBText(m_aabbCnt.GetCurSel(), cstrVal);
		std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
		_int idx = WstrToInt(wstr);

		_float3 pos = static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetOffset();

		pos.z = GetEditControlData(&m_posZ, pNMUpDown);

		static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetOffsetOrigin(pos);
	}
	else
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

void CToolMenuView::OnTvnSelchangedTree(NMHDR * pNMHDR, LRESULT * pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	HTREEITEM hItemCur;
	CString curItemParentName;

	hItemCur = pNMTreeView->itemNew.hItem;
	curItemParentName = m_tree.GetItemText(m_tree.GetParentItem(hItemCur));
	m_curTreeItem = m_tree.GetItemText(hItemCur);

	if (L"Dynamic" == curItemParentName)
	{
		SetChangeMeshList(L"Player");
		SetChangeMeshList(L"Monster");
		SetChangeMeshList(L"DynamicObject");
		SetChangeMeshList(L"StaticObject");
	}
	else if (L"Static" == curItemParentName)
	{
		SetChangeMeshList(L"Map");
		SetChangeMeshList(L"MainMenu");
		SetChangeMeshList(L"Static");
		SetChangeMeshList(L"CatPaw");
		SetChangeMeshList(L"Weapon_Kiana");
		SetChangeMeshList(L"Weapon_Sakura");
		SetChangeMeshList(L"Weapon_Theresa");
	}
	else if (L"Texture" == curItemParentName)
	{
		SetChangeTextureList(L"Kiana_Body");
		SetChangeTextureList(L"Kiana_CatPaw");
		SetChangeTextureList(L"Kiana_Weapon_1");
		SetChangeTextureList(L"Kiana_Weapon_2");
		SetChangeTextureList(L"Sakura_Body");
		SetChangeTextureList(L"Sakura_Weapon");
		SetChangeTextureList(L"Theresa_Body");
		SetChangeTextureList(L"Theresa_Weapon");

		SetChangeTextureList(L"Bronya");
		SetChangeTextureList(L"Ganesha");
		SetChangeTextureList(L"Axe_Body");
		SetChangeTextureList(L"Lancer_Body");
		SetChangeTextureList(L"Ninza_Body");
		SetChangeTextureList(L"Ninza_Weapon");
		SetChangeTextureList(L"Robot_Body");
		SetChangeTextureList(L"Scout_Body");
		SetChangeTextureList(L"Spider_Body");
	}
	else if (L"Prefab" == curItemParentName)
	{
		//
	}
}

void CToolMenuView::OnLbnSelchangeMeshList()
{
	m_meshTreeList.GetText(m_meshTreeList.GetCurSel(), m_curSelFileName);
	m_initTexture.SetCheck(1); // inittexture 체크 박스 체크

	std::wcout << m_curSelFileName.GetString() << std::endl;
	
	Engine::CMeshData* pMD = Engine::GET_CUR_SCENE->GetMeshStore()->GetMeshData(m_curSelFileName.GetString());

	if (pMD->GetTexList().size() != 0)
		m_initTexture.EnableWindow(0);
	else
		m_initTexture.EnableWindow(1);
}

void CToolMenuView::OnLbnSelchangeTextureList()
{
	m_initTexture.SetCheck(0);
	m_textureTreeList.GetText(m_textureTreeList.GetCurSel(), m_curSelTextureFileName);
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

void CToolMenuView::SetChangeMeshList(std::wstring sectionKey)
{
	if (sectionKey.c_str() == m_curTreeItem)
	{
		m_meshTreeList.ResetContent(); // 리스트박스 모든 내용 삭제

		std::vector<std::wstring> vMeshListWithSectionKey;

		Engine::GET_CUR_SCENE->GetMeshStore()->FindMeshesInSection(sectionKey, vMeshListWithSectionKey);

		for (auto& meshKey : vMeshListWithSectionKey)
			m_meshTreeList.AddString(meshKey.c_str());
	}
}

void CToolMenuView::SetChangeTextureList(std::wstring sectionKey)
{
	if (sectionKey.c_str() == m_curTreeItem)
	{
		m_textureTreeList.ResetContent(); // 리스트박스 모든 내용 삭제

		std::vector<std::wstring> vTextureListWithSectionKey;

		Engine::GET_CUR_SCENE->GetTextureStore()->FindTexturesInSection(sectionKey, vTextureListWithSectionKey);

		for (auto& texKey : vTextureListWithSectionKey)
			m_textureTreeList.AddString(texKey.c_str());
	}
}

void CToolMenuView::DataParsing(ELayerID layerID, std::wofstream* ofsSave)
{
	Engine::CLayer* layer = Engine::GET_CUR_SCENE->GetLayers()[(_int)layerID];
	auto& vObjs = layer->GetGameObjects();

	if (vObjs.empty())
		return;

	for (_int i = 0; i < vObjs.size(); ++i)
	{
		if ((layerID == ELayerID::Map) && (L"Cube0" == vObjs[i]->GetName()))
			continue;

		if (0 == i)
			(*ofsSave) << "numOf" << vObjs[0]->GetObjectKey() << '=' << vObjs.size() << "\n\n";

		std::wstring name = vObjs[i]->GetName();

		(*ofsSave) << name << "_static=" << vObjs[i]->GetIsStatic() << "\n";
		(*ofsSave) << name << "_layerID=" << vObjs[i]->GetLayerID() << "\n";
		(*ofsSave) << name << "_meshKey=" << vObjs[i]->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]->GetMeshKey() << '\n';
		(*ofsSave) << name << "_initTex=" << vObjs[i]->GetComponent<Engine::CMeshC>()->GetInitTex() << '\n';
		(*ofsSave) << name << "_renderID=" << vObjs[i]->GetComponent<Engine::CGraphicsC>()->GetRenderID() << '\n';
		(*ofsSave) << name << "_scale=" << vObjs[i]->GetTransform()->GetSize().x << ',' << vObjs[i]->GetTransform()->GetSize().y << ',' << vObjs[i]->GetTransform()->GetSize().z << '\n';
		(*ofsSave) << name << "_rotation=" << vObjs[i]->GetTransform()->GetRotation().x << ',' << vObjs[i]->GetTransform()->GetRotation().y << ',' << vObjs[i]->GetTransform()->GetRotation().z << '\n';
		(*ofsSave) << name << "_position=" << vObjs[i]->GetTransform()->GetPosition().x << ',' << vObjs[i]->GetTransform()->GetPosition().y << ',' << vObjs[i]->GetTransform()->GetPosition().z << '\n';

		if (nullptr == vObjs[i]->GetComponent<Engine::CCollisionC>())
			continue;

		//삭제대기	(*ofsSave) << name << "_colliderID=" << vObjs[i]->GetComponent<Engine::CCollisionC>()->GetCollisionID() << '\n';
		auto& vCols = vObjs[i]->GetComponent<Engine::CCollisionC>()->GetColliders();
		auto& col = vCols.begin();

		_int index = 0;
		for (; col != vCols.end(); ++col)
		{
			_float len = {};
			_float3 dir = {};
			_float3 size = {};
			_float3 rotOffset = {};
			_float3 up = {};
			_float3 forward = {};

			(*ofsSave) << name << "_collider_" << index << "_collisionID=" << (*col)->GetCollisionID() << '\n';
			(*ofsSave) << name << "_collider_" << index << "_type=" << (*col)->GetColliderType() << '\n';
			(*ofsSave) << name << "_collider_" << index << "_offset=" << (*col)->GetOffset().x << ',' << (*col)->GetOffset().y << ',' << (*col)->GetOffset().z << '\n';

			switch ((*col)->GetColliderType())
			{
			case 1: // ray
				dir = static_cast<Engine::CRayCollider*>((*col).get())->GetDirection();
				(*ofsSave) << name << "_collider_" << index << "_direction=" << dir.x << ',' << dir.y << ',' << dir.z << '\n';

				len = static_cast<Engine::CRayCollider*>((*col).get())->GetLength();
				(*ofsSave) << name << "_collider_" << index << "_length=" << len << '\n';
				break;
			case 3: // aabb
				size = static_cast<Engine::CAabbCollider*>((*col).get())->GetSize();
				(*ofsSave) << name << "_collider_" << index << "_size=" << size.x << ',' << size.y << ',' << size.z << '\n';
				break;
			case 4: // obb
				size = static_cast<Engine::CObbCollider*>((*col).get())->GetSize();
				(*ofsSave) << name << "_collider_" << index << "_size=" << size.x << ',' << size.y << ',' << size.z << '\n';

				rotOffset = static_cast<Engine::CObbCollider*>((*col).get())->GetRotOffset();
				(*ofsSave) << name << "_collider_" << index << "_rotOffset=" << rotOffset.x << ',' << rotOffset.y << ',' << rotOffset.z << '\n';
				break;
			}
			++index;
		}
	}

	(*ofsSave) << '\n';
}

void CToolMenuView::ParsingDecoObject(std::wofstream * ofsSave)
{
	Engine::CLayer* layer = Engine::GET_CUR_SCENE->GetLayers()[(_int)ELayerID::Map];
	

	_int numOfDecoObject = 0;
	for (auto& object : layer->GetGameObjects())
	{
		if (object->GetComponent<Engine::CCollisionC>())
			continue;

		(*ofsSave) << numOfDecoObject << L"_position="
			<< object->GetTransform()->GetPosition().x << ','
			<< object->GetTransform()->GetPosition().y << ','
			<< object->GetTransform()->GetPosition().z << '\n';

		(*ofsSave) << numOfDecoObject << L"_rotation="
			<< object->GetTransform()->GetRotation().x << ','
			<< object->GetTransform()->GetRotation().y << ','
			<< object->GetTransform()->GetRotation().z << '\n';

		(*ofsSave) << numOfDecoObject << L"_size="
			<< object->GetTransform()->GetSize().x << ','
			<< object->GetTransform()->GetSize().y << ','
			<< object->GetTransform()->GetSize().z << '\n';

		SP(Engine::CMeshC) spMesh = object->GetComponent<Engine::CMeshC>();

		std::wstring isInitTex = L"true";
		if (spMesh->GetMeshDatas()[0]->GetTexList()[0] == L"NoTexture")
			isInitTex = L"false";

		(*ofsSave) << numOfDecoObject << L"_initMesh=" << isInitTex << L'\n';

		(*ofsSave) << numOfDecoObject << L"_numOfMeshData=" << spMesh->GetMeshDatas().size() << L'\n';
		for (_int i = 0; i < spMesh->GetMeshDatas().size(); ++i)
		{
			(*ofsSave) << numOfDecoObject << L"_meshKey" << i << L'=' << spMesh->GetMeshDatas()[i]->GetMeshKey() << L'\n';
		}

		SP(Engine::CTextureC) spTexture = object->GetComponent<Engine::CTextureC>();
		(*ofsSave) << numOfDecoObject << L"_numOfTexSet=" << spTexture->GetTexData().size() << L'\n';
		for (_int i = 0; i < spTexture->GetTexData().size(); ++i)
		{
			(*ofsSave) << numOfDecoObject << L"_numOfTex" << i << L'=' << spTexture->GetTexData()[i].size() << L'\n';
			for (_int j = 0; j < spTexture->GetTexData()[i].size(); ++j)
			{
				(*ofsSave) << numOfDecoObject << L"_textureKey" << i << L'_' << j << L'=' << spTexture->GetTexData()[i][j]->textureKey << L'\n';
			}
		}

		(*ofsSave) << numOfDecoObject << L"_renderID=" << object->GetComponent<Engine::CGraphicsC>()->GetRenderID() << L"\n\n";
		++numOfDecoObject;
	}

	(*ofsSave) << L"numOfDecoObject=" << numOfDecoObject;
}

void CToolMenuView::ParsingMapObject(std::wofstream * ofsSave)
{
	Engine::CLayer* layer = Engine::GET_CUR_SCENE->GetLayers()[(_int)ELayerID::Map];


	_int numOfMapObject = 0;
	for (auto& object : layer->GetGameObjects())
	{
		if (object->GetComponent<Engine::CCollisionC>() == nullptr)
			continue;

		(*ofsSave) << numOfMapObject << L"_position="
			<< object->GetTransform()->GetPosition().x << ','
			<< object->GetTransform()->GetPosition().y << ','
			<< object->GetTransform()->GetPosition().z << '\n';

		(*ofsSave) << numOfMapObject << L"_rotation="
			<< object->GetTransform()->GetRotation().x << ','
			<< object->GetTransform()->GetRotation().y << ','
			<< object->GetTransform()->GetRotation().z << '\n';

		(*ofsSave) << numOfMapObject << L"_size="
			<< object->GetTransform()->GetSize().x << ','
			<< object->GetTransform()->GetSize().y << ','
			<< object->GetTransform()->GetSize().z << '\n';

		SP(Engine::CMeshC) spMesh = object->GetComponent<Engine::CMeshC>();

		std::wstring isInitTex = L"true";
		if (spMesh->GetMeshDatas()[0]->GetTexList()[0] == L"NoTexture")
			isInitTex = L"false";

		(*ofsSave) << numOfMapObject << L"_initMesh=" << isInitTex << L'\n';

		(*ofsSave) << numOfMapObject << L"_numOfMeshData=" << spMesh->GetMeshDatas().size() << L'\n';
		for (_int i = 0; i < spMesh->GetMeshDatas().size(); ++i)
		{
			(*ofsSave) << numOfMapObject << L"_meshKey" << i << L'=' << spMesh->GetMeshDatas()[i]->GetMeshKey() << L'\n';
		}

		SP(Engine::CTextureC) spTexture = object->GetComponent<Engine::CTextureC>();
		(*ofsSave) << numOfMapObject << L"_numOfTexSet=" << spTexture->GetTexData().size() << L'\n';
		for (_int i = 0; i < spTexture->GetTexData().size(); ++i)
		{
			//나중에 수정
			_int count = 0;
			for (auto& iter = spTexture->GetTexData()[i].begin(); iter != spTexture->GetTexData()[i].end(); ++iter)
			{
				if(*iter == nullptr)
					count++;
			}
			(*ofsSave) << numOfMapObject << L"_numOfTex" << i << L'=' << spTexture->GetTexData()[i].size() - count << L'\n';
			for (_int j = 0; j < spTexture->GetTexData()[i].size() - count; ++j)
			{
				(*ofsSave) << numOfMapObject << L"_textureKey" << i << L'_' << j << L'=' << spTexture->GetTexData()[i][j]->textureKey << L'\n';
			}
		}

		(*ofsSave) << numOfMapObject << L"_renderID=" << object->GetComponent<Engine::CGraphicsC>()->GetRenderID() << L"\n\n";

		SP(Engine::CCollisionC) spCollision = object->GetComponent<Engine::CCollisionC>();
		(*ofsSave) << numOfMapObject << L"_numOfCollider=" << spCollision->GetColliders().size() << L'\n';

		for (_int i = 0; i < spCollision->GetColliders().size(); ++i)
		{
			SP(Engine::CCollider) spCollider = spCollision->GetColliders()[i];
			_int type = spCollider->GetColliderType();
			_int collisionID = spCollider->GetCollisionID();

			(*ofsSave) << numOfMapObject << L"_colliderCollisionID" << std::to_wstring(i) << L'=' << collisionID << L'\n';
			(*ofsSave) << numOfMapObject << L"_colliderType" << std::to_wstring(i) << L'=' << type << L'\n';
			(*ofsSave) << numOfMapObject << L"_colliderOffset" << std::to_wstring(i) << L'='
					   << spCollider->GetOffset().x << L','
					   << spCollider->GetOffset().y << L','
					   << spCollider->GetOffset().z << L'\n';

			switch (type)
			{
			case (_int)Engine::EColliderType::Point:
			{
				SP(Engine::CPointCollider) spPointCollider =
					std::dynamic_pointer_cast<Engine::CPointCollider>(spCollider);

				//왜만들었누?
				break;
			}
			case (_int)Engine::EColliderType::Ray:
			{
				SP(Engine::CRayCollider) spRayCollider =
					std::dynamic_pointer_cast<Engine::CRayCollider>(spCollider);

				//나중에 터지면 한다~
				break;
			}
			case (_int)Engine::EColliderType::Sphere:
			{
				SP(Engine::CSphereCollider) spSphereCollider =
					std::dynamic_pointer_cast<Engine::CSphereCollider>(spCollider);

				(*ofsSave) << numOfMapObject << L"_colliderRadius" << std::to_wstring(i) << L'='
						   << spSphereCollider->GetRadius() << L'\n';
				break;
			}
			case (_int)Engine::EColliderType::AABB:
			{
				SP(Engine::CAabbCollider) spAabbCollider =
					std::dynamic_pointer_cast<Engine::CAabbCollider>(spCollider);

				(*ofsSave) << numOfMapObject << L"_colliderSize" << std::to_wstring(i) << L'='
						   << spAabbCollider->GetSize().x << ','
						   << spAabbCollider->GetSize().y << ','
						   << spAabbCollider->GetSize().z << L'\n';
				break;
			}
			case (_int)Engine::EColliderType::OBB:
			{
				SP(Engine::CObbCollider) spObbCollider =
					std::dynamic_pointer_cast<Engine::CObbCollider>(spCollider);

				(*ofsSave) << numOfMapObject << L"_colliderSize" << std::to_wstring(i) << L'='
						   << spObbCollider->GetSize().x << ','
						   << spObbCollider->GetSize().y << ','
						   << spObbCollider->GetSize().z << L'\n';

				(*ofsSave) << numOfMapObject << L"_colliderRotOffset" << std::to_wstring(i) << L'='
						   << spObbCollider->GetRotOffset().x << ','
						   << spObbCollider->GetRotOffset().y << ','
						   << spObbCollider->GetRotOffset().z << L'\n';
				break;
			}
			default:
				break;
			}

		}

		++numOfMapObject;
	}

	(*ofsSave) << L"numOfMapObject=" << numOfMapObject;
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

void CToolMenuView::OnBnClickedPositionBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	CString x, y, z;
	m_posX.GetWindowTextW(x);
	m_posY.GetWindowTextW(y);
	m_posZ.GetWindowTextW(z);

	pCurObj->GetTransform()->SetPosition((_float)_tstof(x), (_float)_tstof(y), (_float)_tstof(z));
}

void CToolMenuView::OnBnClickedRotationBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	CString x, y, z;
	m_rotX.GetWindowTextW(x);
	m_rotY.GetWindowTextW(y);
	m_rotZ.GetWindowTextW(z);

	pCurObj->GetTransform()->SetRotation((_float)_tstof(x), (_float)_tstof(y), (_float)_tstof(z));
}

void CToolMenuView::OnBnClickedScaleBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	CString x, y, z;
	m_scaleX.GetWindowTextW(x);
	m_scaleY.GetWindowTextW(y);
	m_scaleZ.GetWindowTextW(z);

	pCurObj->GetTransform()->SetSize((_float)_tstof(x), (_float)_tstof(y), (_float)_tstof(z));
}

void CToolMenuView::OnBnClickedSaveBtn()
{
	CString fileName;
	m_saveFileName.GetWindowTextW(fileName);

	std::string filePath = "../../../Data/EditorScene/";
	std::wofstream ofsSave(filePath.data() + CStrToStr(fileName) +  ".ini");
	std::wofstream ofsDeco(filePath.data() + std::string("mapDecoration") + ".ini");
	std::wofstream ofsMap(filePath.data() + std::string("mapMapObject") + ".ini");

	if (ofsSave.is_open())
	{
		DataParsing(ELayerID::Player, &ofsSave);
		DataParsing(ELayerID::Enemy, &ofsSave);
		DataParsing(ELayerID::Map, &ofsSave);
		ParsingDecoObject(&ofsDeco);
		ParsingMapObject(&ofsMap);

		AfxMessageBox(L"Save Success | ObjectListView.cpp");
	}
	else AfxMessageBox(L"Save Failed | ObjectListView.cpp");

	ofsSave.close();
	ofsDeco.close();
	ofsMap.close();
}

void CToolMenuView::OnBnClickedLoadBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	auto& objectFactory = Engine::GET_CUR_SCENE->GetObjectFactory();

	// 이미 툴에 오브젝트가 존재한다면 모두 제거 (cube0, camera0 제외)
	auto& layer = Engine::GET_CUR_SCENE->GetLayers().begin();

	for (; layer != Engine::GET_CUR_SCENE->GetLayers().end(); ++layer)
	{
		auto& obj = (*layer)->GetGameObjects().begin();

		for (; obj != (*layer)->GetGameObjects().end(); ++obj)
		{
			if (L"Camera0" == (*obj)->GetName())
				continue;

			(*obj)->SetDeleteThis(true);
		}
	}

	// 데이터 파일 불러오기
	std::string strLine = "";
	CString fileName;
	m_loadFileName.GetWindowTextW(fileName);
	std::string filePath = "../../../Data/EditorScene/" + CStrToStr(fileName) + ".ini";
	std::ifstream ifsLoad(filePath.data());
	
	_float vPos = 0.f;
	_float vRot = 0.f;

	std::wstring protoObjectKey;
	_bool isStatic;
	_int layerID;
	std::wstring meshKey;
	_bool initTex;
	_int renderID;
	_float3 position;
	_float3 scale;
	_float3 rotation;
	_int colID; // collider
	_float3 offset; // collider
	_float3 size; // collider
	_float3 rotOffset; // collider
	_int shaderID;

	SP(Engine::CObject) spObject = nullptr;

	while (!ifsLoad.eof())
	{
		_tchar* dataTag = nullptr;
		_tchar* dataValue = nullptr;

		std::getline(ifsLoad, strLine);

		if ("" == strLine)
			continue;

		std::vector<std::string> vStr = split(strLine, '=');

		if (!dataValue && !dataTag)
		{
			std::wstring wstr = Engine::StrToWStr(vStr[1]);
			dataValue = _wcsdup(wstr.c_str());
		}

		if (!wcscmp(L"numOfEmptyObject", _wcsdup(Engine::StrToWStr(vStr[0]).c_str())))
			continue;

		std::vector<std::string> vStrTag = split(vStr[0], '_');

		std::wstring wstr = Engine::StrToWStr(vStrTag[1]);
		dataTag = _wcsdup(wstr.c_str());

		if (!wcscmp(L"static", dataTag))
		{
			isStatic = WstrToBool(dataValue);
			continue;
		}
		else if (!wcscmp(L"layerID", dataTag))
		{ 
			layerID = WstrToInt(dataValue);
			spObject = objectFactory->AddClone(L"EmptyObject", isStatic, layerID, Engine::StrToWStr(vStrTag[0]));
			spObject->SetLayerID(layerID);
			m_objList.AddString(spObject->GetName().c_str());
			continue;
		}
		else if (!wcscmp(L"shaderKey", dataTag))
		{
			shaderID = WstrToInt(dataValue);
			spObject->AddComponent<Engine::CShaderC>()->AddShader(shaderID);
			delete dataTag;
			delete dataValue;
			continue;
		}
		else if (!wcscmp(L"meshKey", dataTag))
		{
			meshKey = dataValue;
			spObject->AddComponent<Engine::CMeshC>()->AddMeshData(meshKey);
			continue;
		}
		else if (!wcscmp(L"initTex", dataTag))
		{
			initTex =  WstrToBool(dataValue);
			spObject->GetComponent<Engine::CMeshC>()->SetInitTex(initTex);
			

			if (L"Cube" != spObject->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]->GetMeshKey())
				spObject->AddComponent<Engine::CTextureC>();
			else
				spObject->AddComponent<Engine::CTextureC>()->AddTexture(L"Castle_wall", 0);

			spObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
			continue;
		}
		else if (!wcscmp(L"renderID", dataTag))
		{
			renderID = WstrToInt(dataValue);
			spObject->AddComponent<Engine::CGraphicsC>()->SetRenderID(renderID);
			spObject->GetComponent<Engine::CGraphicsC>()->SetColorReverse(false);
			continue;
		}
		else if (!wcscmp(L"scale", dataTag))
		{
			vStr = split(vStr[1], ',');
			scale = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };
			spObject->GetTransform()->SetSize(scale);
			continue;
		}
		else if (!wcscmp(L"rotation", dataTag))
		{
			vStr = split(vStr[1], ',');
			rotation = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };
			spObject->GetTransform()->SetRotation(rotation);
			continue;
		}
		else if (!wcscmp(L"position", dataTag))
		{
			vStr = split(vStr[1], ',');
			position = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };
			spObject->GetTransform()->SetPosition(position);
			continue;
		}
		else if (!wcscmp(L"collider", dataTag))
		{
			if (nullptr == spObject->GetComponent<Engine::CCollisionC>())
			{
				spObject->AddComponent<Engine::CCollisionC>();
				spObject->AddComponent<Engine::CDebugC>();
			}

			std::wstring wstr = Engine::StrToWStr(vStrTag[3]);
			if (L"collisionID" == wstr)
				colID = WstrToInt(dataValue);

			std::getline(ifsLoad, strLine);
			vStr = split(strLine, '=');
			vStrTag = split(vStr[0], '_');
			std::wstring type = Engine::StrToWStr(vStrTag[3]);

			_int index = StrToInt(vStr[1]);

			if (L"type" == type)
			{
				switch (index)
				{
				case 1: // ray
					break;
				case 3: // aabb
				{
					/* offset */
					std::getline(ifsLoad, strLine);
					vStr = split(strLine, '=');
					vStr = split(vStr[1], ',');
					offset = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };

					/* size */
					std::getline(ifsLoad, strLine);
					vStr = split(strLine, '=');
					vStr = split(vStr[1], ',');
					size = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };

					spObject->GetComponent<Engine::CCollisionC>()->AddCollider(Engine::CAabbCollider::Create(colID, size, offset));
					size_t colIdx = spObject->GetComponent<Engine::CCollisionC>()->GetColliders().size() - 1;
					m_aabbCnt.AddString(SizeToCStr(colIdx));
				}
					break;
				case 4: // obb
				{
					/* offset */
					std::getline(ifsLoad, strLine);
					vStr = split(strLine, '=');
					vStr = split(vStr[1], ',');
					offset = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };

					/* size */
					std::getline(ifsLoad, strLine);
					vStr = split(strLine, '=');
					vStr = split(vStr[1], ',');
					size = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };

					/* rotOffset */
					std::getline(ifsLoad, strLine);
					vStr = split(strLine, '=');
					vStr = split(vStr[1], ',');
					rotOffset = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };

					spObject->GetComponent<Engine::CCollisionC>()->AddCollider(Engine::CObbCollider::Create(colID, size, offset, rotOffset));
					size_t colIdx = spObject->GetComponent<Engine::CCollisionC>()->GetColliders().size() - 1;
					m_obbCnt.AddString(SizeToCStr(colIdx));
					break;
				}
				}
			}
		}
	}

	AfxMessageBox(L"Load Success | ObjectListView.cpp");
}

void CToolMenuView::OnCbnSelchangeCombo4()
{
	//m_culSelLayerID = (_int)m_layerID.GetCurSel();
}

void CToolMenuView::OnBnClickedCreatePrefBtn()
{

}

void CToolMenuView::OnBnClickedCreateAABBColliderBtn()
{
	Engine::CObject* curObj = static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (nullptr == curObj)
		return;

	if (1 == m_colType[0].GetCheck())
	{
		CString cstrSize, cstrOffset;
		m_aabbSize.GetWindowTextW(cstrSize);
		m_aabbOffset.GetWindowTextW(cstrOffset);

		std::string str = CStrToStr(cstrSize);
		std::vector<std::string> vStrSize = split(str, ',');

		_float3 size = _float3(
			WstrToFloat(Engine::StrToWStr(vStrSize[0])),
			WstrToFloat(Engine::StrToWStr(vStrSize[1])),
			WstrToFloat(Engine::StrToWStr(vStrSize[2]))
		);

		str = CStrToStr(cstrOffset);
		std::vector<std::string> vStrOffset = split(str, ',');

		_float3 offset = _float3(
			WstrToFloat(Engine::StrToWStr(vStrOffset[0])),
			WstrToFloat(Engine::StrToWStr(vStrOffset[1])),
			WstrToFloat(Engine::StrToWStr(vStrOffset[2]))
		);

		//툴에서 만들어 : 만듬
		//콜리젼 아이디 기입하는 부분에서 콜리젼 아이디 받기
		CString cstrIdx;
		ECollisionID collisionID;
		m_colliderID.GetWindowTextW(cstrIdx);

		if (L"" == cstrIdx)
			return;
		else if (L"Floor" == cstrIdx)
			collisionID = ECollisionID::Floor;
		else if (L"Wall" == cstrIdx)
			collisionID = ECollisionID::Wall;
		else if (L"Player" == cstrIdx)
			collisionID = ECollisionID::Player;
		else if (L"Enemy" == cstrIdx)
			collisionID = ECollisionID::Enemy;
		else if (L"Trigger" == cstrIdx)
			collisionID = ECollisionID::Trigger;

		curObj->GetComponent<Engine::CCollisionC>()->AddCollider(Engine::CAabbCollider::Create((_int)collisionID, size, offset));

		size_t idx = curObj->GetComponent<Engine::CCollisionC>()->GetColliders().size() - 1;

		m_aabbCnt.AddString(SizeToCStr(idx));

		std::cout << "add aabb collider" << std::endl;
	}
}

void CToolMenuView::OnBnClickedCreateObbColliderBtn()
{
	Engine::CObject* curObj = static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (nullptr == curObj)
		return;

	if (1 == m_colType[2].GetCheck())
	{
		CString cstrOffset, cstrSize, cstrRotOffset;
		m_obbOffset.GetWindowTextW(cstrOffset);
		m_obbSize.GetWindowTextW(cstrSize);
		m_obbRotOffset.GetWindowTextW(cstrRotOffset);

		/* offset */
		std::string str = CStrToStr(cstrOffset);
		std::vector<std::string> vStrOffset = split(str, ',');

		_float3 offset = _float3(
			WstrToFloat(Engine::StrToWStr(vStrOffset[0])),
			WstrToFloat(Engine::StrToWStr(vStrOffset[1])),
			WstrToFloat(Engine::StrToWStr(vStrOffset[2]))
		);

		/* size */
		str = CStrToStr(cstrSize);
		std::vector<std::string> vStrSize = split(str, ',');

		_float3 size = _float3(
			WstrToFloat(Engine::StrToWStr(vStrSize[0])),
			WstrToFloat(Engine::StrToWStr(vStrSize[1])),
			WstrToFloat(Engine::StrToWStr(vStrSize[2]))
		);

		/* rotOffset */
		str = CStrToStr(cstrRotOffset);
		std::vector<std::string> vStrRotOffset = split(str, ',');

		_float3 rotOffset = _float3(
			WstrToFloat(Engine::StrToWStr(vStrRotOffset[0])),
			WstrToFloat(Engine::StrToWStr(vStrRotOffset[1])),
			WstrToFloat(Engine::StrToWStr(vStrRotOffset[2]))
		);

		CString cstrIdx;
		ECollisionID collisionID;
		m_colliderID.GetWindowTextW(cstrIdx);
		
		if (L"" == cstrIdx)
			return;
		else if (L"Floor" == cstrIdx)
			collisionID = ECollisionID::Floor;
		else if (L"Wall" == cstrIdx)
			collisionID = ECollisionID::Wall;
		else if (L"Player" == cstrIdx)
			collisionID = ECollisionID::Player;
		else if (L"Enemy" == cstrIdx)
			collisionID = ECollisionID::Enemy;
		else if (L"Trigger" == cstrIdx)
			collisionID = ECollisionID::Trigger;

		curObj->GetComponent<Engine::CCollisionC>()->AddCollider(Engine::CObbCollider::Create((_int)collisionID, size, offset, rotOffset));

		size_t idx = curObj->GetComponent<Engine::CCollisionC>()->GetColliders().size() - 1;

		m_obbCnt.AddString(SizeToCStr(idx));

		std::cout << "add obb collider" << std::endl;
	}
}

void CToolMenuView::OnBnClickedCreateRayColliderBtn()
{
	Engine::CObject* curObj = static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (nullptr == curObj)
		return;

	if (1 == m_colType[1].GetCheck())
	{
		CString cstrOffset, cstrDir, cstrLen;
		m_rayOffSet.GetWindowTextW(cstrOffset);
		m_rayDir.GetWindowTextW(cstrDir);
		m_rayLen.GetWindowTextW(cstrLen);

		std::string str = CStrToStr(cstrOffset);
		std::vector<std::string> vStrSize = split(str, ',');

		_float3 offset = _float3(
			WstrToFloat(Engine::StrToWStr(vStrSize[0])),
			WstrToFloat(Engine::StrToWStr(vStrSize[1])),
			WstrToFloat(Engine::StrToWStr(vStrSize[2]))
		);

		str = CStrToStr(cstrDir);
		vStrSize = split(str, ',');

		_float3 dir = _float3(
			WstrToFloat(Engine::StrToWStr(vStrSize[0])),
			WstrToFloat(Engine::StrToWStr(vStrSize[1])),
			WstrToFloat(Engine::StrToWStr(vStrSize[2]))
		);

		str = CStrToStr(cstrLen);
		_float len = StrToFloat(str);

		Engine::ERayType rayType;
		CString cstrVal;
		m_rayType.GetLBText(m_rayType.GetCurSel(), cstrVal);
		std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));

		if (L"ALL_INF" == wstr)
			rayType = Engine::ERayType::ALL_INF;
		else if (L"LIMITED" == wstr)
			rayType = Engine::ERayType::LIMITED;
		else if (L"NEGATIVE_INF" == wstr)
			rayType = Engine::ERayType::NEGATIVE_INF;
		else if (L"POSITIVE_INF" == wstr)
			rayType = Engine::ERayType::POSITIVE_INF;

		//툴에서 만들어
		//아이디 줘야해요
		CString cstrIdx;
		ECollisionID collisionID;
		m_colliderID.GetWindowTextW(cstrIdx);

		if (L"" == cstrIdx)
			return;
		else if (L"Floor" == cstrIdx)
			collisionID = ECollisionID::Floor;
		else if (L"Wall" == cstrIdx)
			collisionID = ECollisionID::Wall;
		else if (L"Player" == cstrIdx)
			collisionID = ECollisionID::Player;
		else if (L"Enemy" == cstrIdx)
			collisionID = ECollisionID::Enemy;
		else if (L"Trigger" == cstrIdx)
			collisionID = ECollisionID::Trigger;

		curObj->GetComponent<Engine::CCollisionC>()->AddCollider(Engine::CRayCollider::Create((_int)collisionID, offset, dir, len, rayType));

		size_t idx = curObj->GetComponent<Engine::CCollisionC>()->GetColliders().size() - 1;

		m_rayCnt.AddString(SizeToCStr(idx));

		std::cout << "add ray collider" << std::endl;
	}
}


void CToolMenuView::OnBnClickedAddCollisionCBtn()
{
	Engine::CObject* curObj = static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (nullptr == curObj)
		return;

	CString cstrVal;
	std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
	_int colID = 0;

	//if (L"" == wstr)
	//	return;
	//else if (L"Floor" == wstr)
	//	colID = (_int)ECollisionID::Floor;
	//else if (L"Wall" == wstr)
	//	colID = (_int)ECollisionID::Wall;
	//else if (L"Player" == wstr)
	//	colID = (_int)ECollisionID::Player;
	//else if (L"Enemy" == wstr)
	//	colID = (_int)ECollisionID::Enemy;
	//else if (L"Trigger" == wstr)
	//	colID = (_int)ECollisionID::Trigger;

	curObj->AddComponent<Engine::CCollisionC>();
	curObj->AddComponent<Engine::CDebugC>();

	m_colType[0].EnableWindow(true);
	m_colType[1].EnableWindow(true);
	m_colType[2].EnableWindow(true);
	m_showAllCol.EnableWindow(true);
	m_addColC.EnableWindow(false);
}

void CToolMenuView::OnBnClickedDelAABBColliderBtn()
{
	Engine::CObject* curObj = static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (nullptr == curObj)
		return;

	CString cstrVal;
	m_aabbCnt.GetLBText(m_aabbCnt.GetCurSel(), cstrVal);
	std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
	_int idx = WstrToInt(wstr);
	
	curObj->GetComponent<Engine::CCollisionC>()->DeleteCollider(idx);

	m_selectedAABBCol.EnableWindow(false);
	m_selectedAABBCol.SetCheck(0);

	// reset data in combobox
	m_aabbCnt.ResetContent();

	_int index = 0;

	auto& vCol = curObj->GetComponent<Engine::CCollisionC>()->GetColliders();
	auto& col = vCol.begin();

	for (; col != vCol.end(); ++col)
	{
		if (3 == (*col)->GetColliderType())
			m_aabbCnt.AddString(IntToCStr(index));
		++index;
	}
}

void CToolMenuView::OnBnClickedDelRayColliderBtn()
{
	Engine::CObject* curObj = static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (nullptr == curObj)
		return;

	CString cstrVal;
	m_rayCnt.GetLBText(m_rayCnt.GetCurSel(), cstrVal);
	std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
	_int idx = WstrToInt(wstr);

	curObj->GetComponent<Engine::CCollisionC>()->DeleteCollider(idx);

	m_selectedRayCol.EnableWindow(false);
	m_selectedRayCol.SetCheck(0);

	// reset data in combobox
	m_rayCnt.ResetContent();

	_int index = 0;

	auto& vCol = curObj->GetComponent<Engine::CCollisionC>()->GetColliders();
	auto& col = vCol.begin();

	for (; col != vCol.end(); ++col)
	{
		if (1 == (*col)->GetColliderType())
			m_rayCnt.AddString(IntToCStr(index));
		++index;
	}
}

void CToolMenuView::OnBnClickedDelObbColliderBtn()
{
	Engine::CObject* curObj = static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (nullptr == curObj)
		return;

	CString cstrVal;
	m_obbCnt.GetLBText(m_obbCnt.GetCurSel(), cstrVal);
	std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
	_int idx = WstrToInt(wstr);

	curObj->GetComponent<Engine::CCollisionC>()->DeleteCollider(idx);

	m_selectedObbCol.EnableWindow(false);
	m_selectedObbCol.SetCheck(0);

	// reset data in combobox
	m_obbCnt.ResetContent();

	_int index = 0;

	auto& vCol = curObj->GetComponent<Engine::CCollisionC>()->GetColliders();
	auto& col = vCol.begin();

	for (; col != vCol.end(); ++col)
	{
		if (1 == (*col)->GetColliderType())
			m_obbCnt.AddString(IntToCStr(index));
		++index;
	}
}

void CToolMenuView::OnCbnSelchangeAABBList()
{
	std::cout << m_aabbCnt.GetCurSel() << std::endl;
	m_selectedAABBCol.EnableWindow(true);
	m_selectedAABBCol.SetCheck(1);

	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (nullptr == pCurObj)
		return;

	CString cstrVal;
	m_aabbCnt.GetLBText(m_aabbCnt.GetCurSel(), cstrVal);
	std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
	_int idx = WstrToInt(wstr);

	_int colID = static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetCollisionID();
	_float3 size = static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetSize();
	_float3 offset = static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetOffset();

	std::wstring wstrSize = DeleteCharInWstr(FloatToWStr(size.x), '0') + L"," + 
							DeleteCharInWstr(FloatToWStr(size.y), '0') + L"," + 
							DeleteCharInWstr(FloatToWStr(size.z), '0');

	std::wstring wstrOffset = DeleteCharInWstr(FloatToWStr(offset.x), '0') + L"," +
							  DeleteCharInWstr(FloatToWStr(offset.y), '0') + L"," +
							  DeleteCharInWstr(FloatToWStr(offset.z), '0');

	m_aabbSize.SetWindowTextW(wstrSize.c_str());
	m_aabbOffset.SetWindowTextW(wstrOffset.c_str());

	switch (colID)
	{
	case 3:
		m_colliderID.SetCurSel(0);
		break;
	case 4:
		m_colliderID.SetCurSel(1);
		break;
	case 5:
		m_colliderID.SetCurSel(2);
		break;
	case 6:
		m_colliderID.SetCurSel(3);
		break;
	case 7:
		m_colliderID.SetCurSel(4);
		break;
	}

	
}

void CToolMenuView::OnCbnSelchangeRayList()
{
	std::cout << m_rayCnt.GetCurSel() << std::endl;
	m_selectedRayCol.EnableWindow(true);
	m_selectedRayCol.SetCheck(1);

	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (nullptr == pCurObj)
		return;

	CString cstrVal;
	m_rayCnt.GetLBText(m_rayCnt.GetCurSel(), cstrVal);
	std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
	_int idx = WstrToInt(wstr);

	_int colID = static_cast<Engine::CRayCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetCollisionID();
	_float3 offset = static_cast<Engine::CRayCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetOffset();
	_float3 dir = static_cast<Engine::CRayCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetDirection();
	_float len = static_cast<Engine::CRayCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetLength();
	Engine::ERayType type = static_cast<Engine::CRayCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetRayType();

	std::wstring wstrOffset = DeleteCharInWstr(FloatToWStr(offset.x), '0') + L"," +
		DeleteCharInWstr(FloatToWStr(offset.y), '0') + L"," +
		DeleteCharInWstr(FloatToWStr(offset.z), '0');

	std::wstring wstrDir = DeleteCharInWstr(FloatToWStr(dir.x), '0') + L"," +
		DeleteCharInWstr(FloatToWStr(dir.y), '0') + L"," +
		DeleteCharInWstr(FloatToWStr(dir.z), '0');

	std::wstring wstrLen = DeleteCharInWstr(FloatToWStr(len), '0');

	m_rayOffSet.SetWindowTextW(wstrOffset.c_str());
	m_rayDir.SetWindowTextW(wstrDir.c_str());
	m_rayLen.SetWindowTextW(wstrLen.c_str());
	m_rayType.SetCurSel((_int)type);

	switch (colID)
	{
	case 3:
		m_colliderID.SetCurSel(0);
		break;
	case 4:
		m_colliderID.SetCurSel(1);
		break;
	case 5:
		m_colliderID.SetCurSel(2);
		break;
	case 6:
		m_colliderID.SetCurSel(3);
		break;
	case 7:
		m_colliderID.SetCurSel(4);
		break;
	}
}

void CToolMenuView::OnCbnSelchangeObbList()
{
	std::cout << m_obbCnt.GetCurSel() << std::endl;
	m_selectedObbCol.EnableWindow(true);
	m_selectedObbCol.SetCheck(1);

	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (nullptr == pCurObj)
		return;

	CString cstrVal;
	m_obbCnt.GetLBText(m_obbCnt.GetCurSel(), cstrVal);
	std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
	_int idx = WstrToInt(wstr);

	_int colID = static_cast<Engine::CObbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetCollisionID();
	_float3 offset = static_cast<Engine::CObbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetOffset();
	_float3 size = static_cast<Engine::CObbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetSize();
	_float3 rotOffset = static_cast<Engine::CObbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->GetRotOffset();

	std::wstring wstrOffset = DeleteCharInWstr(FloatToWStr(offset.x), '0') + L"," +
		DeleteCharInWstr(FloatToWStr(offset.y), '0') + L"," +
		DeleteCharInWstr(FloatToWStr(offset.z), '0');

	std::wstring wstrSize = DeleteCharInWstr(FloatToWStr(size.x), '0') + L"," +
		DeleteCharInWstr(FloatToWStr(size.y), '0') + L"," +
		DeleteCharInWstr(FloatToWStr(size.z), '0');

	std::wstring wstrRotOffset = DeleteCharInWstr(FloatToWStr(rotOffset.x), '0') + L"," +
		DeleteCharInWstr(FloatToWStr(rotOffset.y), '0') + L"," +
		DeleteCharInWstr(FloatToWStr(rotOffset.z), '0');

	m_obbOffset.SetWindowTextW(wstrOffset.c_str());
	m_obbSize.SetWindowTextW(wstrSize.c_str());
	m_obbRotOffset.SetWindowTextW(wstrRotOffset.c_str());

	switch (colID)
	{
	case 3:
		m_colliderID.SetCurSel(0);
		break;
	case 4:
		m_colliderID.SetCurSel(1);
		break;
	case 5:
		m_colliderID.SetCurSel(2);
		break;
	case 6:
		m_colliderID.SetCurSel(3);
		break;
	case 7:
		m_colliderID.SetCurSel(4);
		break;
	}
}

void CToolMenuView::OnBnClickedSelectedAABBCol()
{
	m_aabbCnt.SetCurSel(-1);
	m_selectedAABBCol.SetCheck(0);
	m_selectedAABBCol.EnableWindow(false);
}

void CToolMenuView::OnBnClickedSelectedRayCol()
{
	m_rayCnt.SetCurSel(-1);
	m_selectedRayCol.SetCheck(0);
	m_selectedRayCol.EnableWindow(false);
}

void CToolMenuView::OnBnClickedSelectedObbCol()
{
	m_obbCnt.SetCurSel(-1);
	m_selectedRayCol.SetCheck(0);
	m_selectedRayCol.EnableWindow(false);
}

void CToolMenuView::OnBnClickedModifyAABBColBtn()
{
	CString cstrVal;
	m_aabbCnt.GetLBText(m_aabbCnt.GetCurSel(), cstrVal);
	std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
	_int idx = WstrToInt(wstr);

	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (1 == m_colType[0].GetCheck())
	{
		CString cstrSize, cstrOffset;
		m_aabbSize.GetWindowTextW(cstrSize);
		m_aabbOffset.GetWindowTextW(cstrOffset);

		std::string str = CStrToStr(cstrSize);
		std::vector<std::string> vStrSize = split(str, ',');

		_float3 size = _float3(
			WstrToFloat(Engine::StrToWStr(vStrSize[0])),
			WstrToFloat(Engine::StrToWStr(vStrSize[1])),
			WstrToFloat(Engine::StrToWStr(vStrSize[2]))
		);

		str = CStrToStr(cstrOffset);
		std::vector<std::string> vStrOffset = split(str, ',');

		_float3 offset = _float3(
			WstrToFloat(Engine::StrToWStr(vStrOffset[0])),
			WstrToFloat(Engine::StrToWStr(vStrOffset[1])),
			WstrToFloat(Engine::StrToWStr(vStrOffset[2]))
		);

		CString cstrIdx;
		ECollisionID collisionID;
		m_colliderID.GetWindowTextW(cstrIdx);

		if (L"" == cstrIdx)
			return;
		else if (L"Floor" == cstrIdx)
			collisionID = ECollisionID::Floor;
		else if (L"Wall" == cstrIdx)
			collisionID = ECollisionID::Wall;
		else if (L"Player" == cstrIdx)
			collisionID = ECollisionID::Player;
		else if (L"Enemy" == cstrIdx)
			collisionID = ECollisionID::Enemy;
		else if (L"Trigger" == cstrIdx)
			collisionID = ECollisionID::Trigger;


		static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetCollisionID((_int)collisionID);
		static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetOffsetOrigin(offset);
		static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetOffset(offset);
		static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetSize(size);
		static_cast<Engine::CAabbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetHalfSize(size * 0.5f);

		std::cout << "modify aabb collider" << std::endl;
	}
}

void CToolMenuView::OnBnClickedModifyObbColBtn()
{
	CString cstrVal;
	m_obbCnt.GetLBText(m_obbCnt.GetCurSel(), cstrVal);
	std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
	_int idx = WstrToInt(wstr);

	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (1 == m_colType[2].GetCheck())
	{
		CString cstrOffset, cstrSize, cstrRotOffset;
		m_obbOffset.GetWindowTextW(cstrOffset);
		m_obbSize.GetWindowTextW(cstrSize);
		m_obbRotOffset.GetWindowTextW(cstrRotOffset);

		/* offset */
		std::string str = CStrToStr(cstrOffset);
		std::vector<std::string> vStrOffset = split(str, ',');

		_float3 offset = _float3(
			WstrToFloat(Engine::StrToWStr(vStrOffset[0])),
			WstrToFloat(Engine::StrToWStr(vStrOffset[1])),
			WstrToFloat(Engine::StrToWStr(vStrOffset[2]))
		);

		/* size */
		str = CStrToStr(cstrSize);
		std::vector<std::string> vStrSize = split(str, ',');

		_float3 size = _float3(
			WstrToFloat(Engine::StrToWStr(vStrSize[0])),
			WstrToFloat(Engine::StrToWStr(vStrSize[1])),
			WstrToFloat(Engine::StrToWStr(vStrSize[2]))
		);

		/* rotOffset */
		str = CStrToStr(cstrRotOffset);
		std::vector<std::string> vStrRotOffset = split(str, ',');

		_float3 rotOffset = _float3(
			WstrToFloat(Engine::StrToWStr(vStrRotOffset[0])),
			WstrToFloat(Engine::StrToWStr(vStrRotOffset[1])),
			WstrToFloat(Engine::StrToWStr(vStrRotOffset[2]))
		);

		CString cstrIdx;
		ECollisionID collisionID;
		m_colliderID.GetWindowTextW(cstrIdx);

		if (L"" == cstrIdx)
			return;
		else if (L"Floor" == cstrIdx)
			collisionID = ECollisionID::Floor;
		else if (L"Wall" == cstrIdx)
			collisionID = ECollisionID::Wall;
		else if (L"Player" == cstrIdx)
			collisionID = ECollisionID::Player;
		else if (L"Enemy" == cstrIdx)
			collisionID = ECollisionID::Enemy;
		else if (L"Trigger" == cstrIdx)
			collisionID = ECollisionID::Trigger;


		static_cast<Engine::CObbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetCollisionID((_int)collisionID);


		static_cast<Engine::CObbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetOffsetOrigin(offset);

		static_cast<Engine::CObbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetSize(size);
		static_cast<Engine::CObbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetHalfSize(size * 0.5f);

		static_cast<Engine::CObbCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetRotOffset(rotOffset);

		std::cout << "modify obb collider" << std::endl;
	}
}

void CToolMenuView::OnBnClickedModifyRayColBtn()
{
	CString cstrVal;
	m_rayCnt.GetLBText(m_rayCnt.GetCurSel(), cstrVal);
	std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrVal));
	_int idx = WstrToInt(wstr);

	Engine::CObject* pCurObj = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj();

	if (1 == m_colType[1].GetCheck())
	{
		CString cstrOffset, cstrDir, cstrLen, cstrType;
		m_rayOffSet.GetWindowTextW(cstrOffset);
		m_rayDir.GetWindowTextW(cstrDir);
		m_rayLen.GetWindowTextW(cstrLen);
		m_rayType.GetWindowTextW(cstrType);

		/* offset */
		std::string str = CStrToStr(cstrOffset);
		std::vector<std::string> vStrOffset = split(str, ',');

		_float3 offset = _float3(
			WstrToFloat(Engine::StrToWStr(vStrOffset[0])),
			WstrToFloat(Engine::StrToWStr(vStrOffset[1])),
			WstrToFloat(Engine::StrToWStr(vStrOffset[2]))
		);

		/* dir */
		str = CStrToStr(cstrDir);
		std::vector<std::string> vStrDir = split(str, ',');

		_float3 dir = _float3(
			WstrToFloat(Engine::StrToWStr(vStrDir[0])),
			WstrToFloat(Engine::StrToWStr(vStrDir[1])),
			WstrToFloat(Engine::StrToWStr(vStrDir[2]))
		);

		/* len */
		str = CStrToStr(cstrLen);
		_float length = WstrToFloat(Engine::StrToWStr(str));

		/* type */
		std::wstring wstr = Engine::StrToWStr(CStrToStr(cstrType));
		Engine::ERayType rayType;

		if (L"ALL_INF" == wstr)
			rayType = Engine::ERayType::ALL_INF;
		else if (L"LIMITED" == wstr)
			rayType = Engine::ERayType::LIMITED;
		else if (L"NEGATIVE_INF" == wstr)
			rayType = Engine::ERayType::NEGATIVE_INF;
		else if (L"POSITIVE_INF" == wstr)
			rayType = Engine::ERayType::POSITIVE_INF;

		static_cast<Engine::CRayCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetOffsetOrigin(offset);
		static_cast<Engine::CRayCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetOffset(offset);

		static_cast<Engine::CRayCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetDirectionOrigin(dir);
		static_cast<Engine::CRayCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetDirection(dir);

		static_cast<Engine::CRayCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetLength(length);
		static_cast<Engine::CRayCollider*>(pCurObj->GetComponent<Engine::CCollisionC>()->GetColliders()[idx].get())->SetRayType(rayType);

		std::cout << "modify ray collider" << std::endl;
	}
}

void CToolMenuView::OnBnClickedCreateMesh()
{
	CString cstr;
	std::wstring wstr;
	ELayerID curLayerID = ELayerID::NumOfLayerID;
	m_layerID.GetLBText(m_layerID.GetCurSel(), cstr);

	if ("Player" == cstr)
		curLayerID = ELayerID::Player;
	else if ("Enemy" == cstr)
		curLayerID = ELayerID::Enemy;
	else if ("Map" == cstr)
		curLayerID = ELayerID::Map;

	m_curObjName.GetWindowTextW(cstr);
	wstr = CStrToWStr(cstr);

	static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->CreateObject(true, curLayerID, wstr);
}

void CToolMenuView::OnLbnSelchangeObjectList()
{
	_int index = m_objList.GetCurSel(); // 리스트에서 선택한 오브젝트의 리스트에서의 인덱스 번호
	CString str;
	std::wstring wstr;

	for (_int i = (_int)ELayerID::Player; i < (_int)ELayerID::Camera; ++i) // player, enemy search
	{
		auto& vObjs = Engine::GET_CUR_SCENE->GetLayers()[i]->GetGameObjects();
		auto& obj = vObjs.begin();

		for (; obj != vObjs.end(); ++obj)
		{
			m_objList.GetText(index, str);
			wstr = Engine::StrToWStr(CStrToStr(str));
			if (wstr == (*obj)->GetName())
			{
				if (nullptr != static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj())
					static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj()->GetComponent<Engine::CGraphicsC>()->SetColorReverse(false);

				static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->SetCurSelObj(obj->get());
				static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj()->GetComponent<Engine::CGraphicsC>()->SetColorReverse(true);
				m_curObjNameChk.SetCheck(1);
				m_curObjName.SetWindowTextW((*obj)->GetName().c_str());
				std::cout << "Target Found in Object List" << std::endl;

				if (nullptr != static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj()->GetComponent<Engine::CCollisionC>())
				{
					m_colType[0].EnableWindow(true);
					m_colType[1].EnableWindow(true);
					m_colType[2].EnableWindow(true);
					m_showAllCol.EnableWindow(true);
					m_addColC.EnableWindow(false);
				}
				else
				{
					m_colType[0].EnableWindow(false);
					m_colType[1].EnableWindow(false);
					m_colType[2].EnableWindow(false);
					m_showAllCol.EnableWindow(false);
					m_addColC.EnableWindow(true);
				}

				// collision cnt reset
				m_aabbCnt.ResetContent();
				if (nullptr != (*obj)->GetComponent<Engine::CCollisionC>())
				{
					_int idx = 0;

					auto& vCol = (*obj)->GetComponent<Engine::CCollisionC>()->GetColliders();
					auto& col = vCol.begin();

					for (; col != vCol.end(); ++col)
					{
						if (3 == (*col)->GetColliderType())
						{
							m_aabbCnt.AddString(IntToCStr(idx));
						}
						++idx;
					}
				}
				return;
			}
		}
	}
	std::cout << "Target not found in Object List" << std::endl;
}

void CToolMenuView::OnBnClickedCurObjectNameChk()
{
	switch (m_curObjNameChk.GetCheck())
	{
	case 0:
		static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj()->GetComponent<Engine::CGraphicsC>()->SetColorReverse(false);
		static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->SetCurSelObj(nullptr);
		m_curObjName.SetWindowTextW(L"");
		break;
	case 1:
		break;
	}
}

void CToolMenuView::OnBnClickedDelObjectWithObjList()
{
	_int index = m_objList.GetCurSel();
	CString str;
	std::wstring wstr;

	for (_int i = (_int)ELayerID::Player; i < (_int)ELayerID::Camera; ++i) // player, enemy search
	{
		auto& vObjs = Engine::GET_CUR_SCENE->GetLayers()[i]->GetGameObjects();
		auto& obj = vObjs.begin();

		for (; obj != vObjs.end(); ++obj)
		{
			m_objList.GetText(index, str);
			wstr = Engine::StrToWStr(CStrToStr(str));
			if (wstr == (*obj)->GetName())
			{
				static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->GetCurSelObj()->GetComponent<Engine::CGraphicsC>()->SetColorReverse(false);
				static_cast<CEditorScene*>(Engine::GET_CUR_SCENE)->SetCurSelObj(nullptr);
				m_curObjNameChk.SetCheck(0);
				m_curObjName.SetWindowTextW(L"");
				(*obj)->SetDeleteThis(true);

				std::cout << "Target delete" << std::endl;
				m_objList.DeleteString(index);
				return;
			}
		}
	}
}

void CToolMenuView::OnBnClickedShowObjectChk()
{
	
}

//{
//int numOfEmptyObject;
//GET_VALUE(static, ID, key, L"numOfEmptyObject", numOfEmptyObject);
//
//for (int i = 0; i < numOfEmptyObject; ++i)
//{
//	_bool isStatic;
//	GET_VALUE(staic, ID, KEY, EmptyObject + std::to_wstring(i) + L"_static", isStatic);
//
//	SP(EmptyObject) spEmptyObject =
//		ADD_CLONE(al; skdfjal; dkf);
//
//
//}
//}

//툴에서 만들어
//OBB저장하는거랑 OBB불러오는거
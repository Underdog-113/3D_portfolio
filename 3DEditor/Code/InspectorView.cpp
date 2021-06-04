// ../Code/InspectorView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "InspectorView.h"
#include "MainFrm.h"
#include "3DEditor.h"
#include "3DEditorView.h"

#include "EditorScene.h"
#include "Player.h"
#include "Object.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CInspectorView

IMPLEMENT_DYNCREATE(CInspectorView, CFormView)

CInspectorView::CInspectorView()
	: CFormView(IDD_INSPECTORVIEW)
{

}

CInspectorView::~CInspectorView()
{
}

void CInspectorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, m_fPosX);
	DDX_Control(pDX, IDC_EDIT2, m_fPosY);
	DDX_Control(pDX, IDC_EDIT4, m_fPosZ);
	DDX_Control(pDX, IDC_EDIT6, m_fRotX);
	DDX_Control(pDX, IDC_EDIT5, m_fRotY);
	DDX_Control(pDX, IDC_EDIT7, m_fRotZ);
	DDX_Control(pDX, IDC_EDIT9, m_fScaleX);
	DDX_Control(pDX, IDC_EDIT8, m_fScaleY);
	DDX_Control(pDX, IDC_EDIT10, m_fScaleZ);
	DDX_Control(pDX, IDC_SPIN1, m_btnPosX);
	DDX_Control(pDX, IDC_SPIN4, m_btnPosY);
	DDX_Control(pDX, IDC_SPIN7, m_btnPosZ);
	DDX_Control(pDX, IDC_SPIN2, m_btnRotX);
	DDX_Control(pDX, IDC_SPIN5, m_btnRotY);
	DDX_Control(pDX, IDC_SPIN8, m_btnRotZ);
	DDX_Control(pDX, IDC_SPIN3, m_btnScaleX);
	DDX_Control(pDX, IDC_SPIN6, m_btnScaleY);
	DDX_Control(pDX, IDC_SPIN9, m_btnScaleZ);
	DDX_Control(pDX, IDC_RADIO1, m_arrObject[0]);
	DDX_Control(pDX, IDC_RADIO2, m_arrObject[1]);
	DDX_Control(pDX, IDC_RADIO3, m_arrObject[2]);
	DDX_Control(pDX, IDC_RADIO4, m_arrCreateWay[0]);
	DDX_Control(pDX, IDC_RADIO5, m_arrCreateWay[1]);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	DDX_Control(pDX, IDC_LIST2, m_TreeList);
}

BEGIN_MESSAGE_MAP(CInspectorView, CFormView)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CInspectorView::OnPosX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, &CInspectorView::OnPosY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN7, &CInspectorView::OnPosZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CInspectorView::OnRotX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, &CInspectorView::OnRotY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN8, &CInspectorView::OnRotZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CInspectorView::OnScaleX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, &CInspectorView::OnScaleY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN9, &CInspectorView::OnScaleZ)
	ON_BN_CLICKED(IDC_RADIO2, &CInspectorView::OnBnClickedObjectRadio)
	ON_BN_CLICKED(IDC_RADIO1, &CInspectorView::OnBnClickedBlock)
	ON_BN_CLICKED(IDC_RADIO3, &CInspectorView::OnBnClickedNavi)
	ON_BN_CLICKED(IDC_BUTTON1, &CInspectorView::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CInspectorView::OnBnClickedLoadBtn)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CInspectorView::OnTvnSelchangedTree)
	ON_LBN_SELCHANGE(IDC_LIST2, &CInspectorView::OnLbnSelchangeMeshList)
END_MESSAGE_MAP()


// CInspectorView 진단입니다.

void CInspectorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	HTREEITEM hRoot[2];
	HTREEITEM hDynamicMeshChild[4];
	HTREEITEM hStaticMeshChild[1];

	hRoot[0] = m_Tree.InsertItem(L"DynamicMesh", 0, 1, TVI_ROOT, TVI_FIRST);
	hDynamicMeshChild[0] = m_Tree.InsertItem(L"Player", 1, 1, hRoot[0], TVI_FIRST);
	hDynamicMeshChild[1] = m_Tree.InsertItem(L"Boss", 1, 1, hRoot[0], TVI_LAST);
	hDynamicMeshChild[2] = m_Tree.InsertItem(L"Monster", 1, 1, hRoot[0], TVI_LAST);
	hDynamicMeshChild[3] = m_Tree.InsertItem(L"DynamicObject", 1, 1, hRoot[0], TVI_LAST);

	hRoot[1] = m_Tree.InsertItem(L"StaticMesh", 0, 1, TVI_ROOT, TVI_LAST);
	hStaticMeshChild[0] = m_Tree.InsertItem(L"StaticObject", 1, 1, hRoot[1], TVI_FIRST);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_fPosX.SetWindowTextW(_T("0.00"));
	m_fPosY.SetWindowTextW(_T("0.00"));
	m_fPosZ.SetWindowTextW(_T("0.00"));

	m_fRotX.SetWindowTextW(_T("0.00"));
	m_fRotY.SetWindowTextW(_T("0.00"));
	m_fRotZ.SetWindowTextW(_T("0.00"));

	m_fScaleX.SetWindowTextW(_T("0.00"));
	m_fScaleY.SetWindowTextW(_T("0.00"));
	m_fScaleZ.SetWindowTextW(_T("0.00"));

	m_fPosMin = m_fRotMin = m_fScaleMin = -9999.f;
	m_fPosMax = m_fRotMax = m_fScaleMax = 9999.f;

	m_btnPosX.SetRange(m_fPosMin, m_fPosMax);
	m_btnPosX.SetPos(0.f);
	m_btnPosY.SetRange(m_fPosMin, m_fPosMax);
	m_btnPosY.SetPos(0.f);
	m_btnPosZ.SetRange(m_fPosMin, m_fPosMax);
	m_btnPosZ.SetPos(0.f);

	m_btnRotX.SetRange(m_fPosMin, m_fPosMax);
	m_btnRotX.SetPos(0.f);
	m_btnRotY.SetRange(m_fPosMin, m_fPosMax);
	m_btnRotY.SetPos(0.f);
	m_btnRotZ.SetRange(m_fPosMin, m_fPosMax);
	m_btnRotZ.SetPos(0.f);

	m_btnScaleX.SetRange(m_fPosMin, m_fPosMax);
	m_btnScaleX.SetPos(0.f);
	m_btnScaleY.SetRange(m_fPosMin, m_fPosMax);
	m_btnScaleY.SetPos(0.f);
	m_btnScaleZ.SetRange(m_fPosMin, m_fPosMax);
	m_btnScaleZ.SetPos(0.f);
}

void CInspectorView::Update(void)
{
}

void CInspectorView::SpinBtn(LPNMUPDOWN pNMUpDown, CEdit* pBtn, Engine::_float fVal)
{
	// 값 = 현재값 + 증/감
	_float nValue = fVal + (float)((pNMUpDown->iDelta) / 100.f);

	if ((m_fPosMin <= nValue) && (m_fPosMax >= nValue))
	{
		CString cstrValue;
		cstrValue.Format(_T("%.2f"), nValue);
		pBtn->SetWindowTextW(cstrValue);
	}
}

void CInspectorView::SetPosition(Engine::_float3 vPos)
{
	CString cstrValue;
	cstrValue.Format(_T("%.2f"), vPos.x);
	m_fPosX.SetWindowTextW(cstrValue);
	m_btnPosX.SetPos(vPos.x);

	cstrValue.Format(_T("%.2f"), vPos.y);
	m_fPosY.SetWindowTextW(cstrValue);
	m_btnPosY.SetPos(vPos.y);

	cstrValue.Format(_T("%.2f"), vPos.z);
	m_fPosZ.SetWindowTextW(cstrValue);
	m_btnPosZ.SetPos(vPos.z);
}

void CInspectorView::SetRotation(Engine::_float3 vRot)
{
	CString cstrValue;
	cstrValue.Format(_T("%.2f"), vRot.x);
	m_fRotX.SetWindowTextW(cstrValue);
	m_btnRotX.SetPos(vRot.x);

	cstrValue.Format(_T("%.2f"), vRot.y);
	m_fRotY.SetWindowTextW(cstrValue);
	m_btnRotY.SetPos(vRot.y);

	cstrValue.Format(_T("%.2f"), vRot.z);
	m_fRotZ.SetWindowTextW(cstrValue);
	m_btnRotZ.SetPos(vRot.z);
}

void CInspectorView::SetScale(Engine::_float3 vScale)
{
	CString cstrValue;
	cstrValue.Format(_T("%.2f"), vScale.x);
	m_fScaleX.SetWindowTextW(cstrValue);
	m_btnScaleX.SetPos(vScale.x);

	cstrValue.Format(_T("%.2f"), vScale.y);
	m_fScaleY.SetWindowTextW(cstrValue);
	m_btnScaleY.SetPos(vScale.y);

	cstrValue.Format(_T("%.2f"), vScale.z);
	m_fScaleZ.SetWindowTextW(cstrValue);
	m_btnScaleZ.SetPos(vScale.z);
}

#ifdef _DEBUG
void CInspectorView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInspectorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CInspectorView 메시지 처리기입니다.
void CInspectorView::OnPosX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstrValue;
	m_fPosX.GetWindowTextW(cstrValue);
	SpinBtn(pNMUpDown, &m_fPosX, _tstof(cstrValue));

	*pResult = 0;
}

void CInspectorView::OnPosY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstrValue;
	m_fPosY.GetWindowTextW(cstrValue);
	SpinBtn(pNMUpDown, &m_fPosY, _tstof(cstrValue));

	*pResult = 0;
}

void CInspectorView::OnPosZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstrValue;
	m_fPosZ.GetWindowTextW(cstrValue);
	SpinBtn(pNMUpDown, &m_fPosZ, _tstof(cstrValue));

	*pResult = 0;
}

void CInspectorView::OnRotX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstrValue;
	m_fRotX.GetWindowTextW(cstrValue);
	SpinBtn(pNMUpDown, &m_fRotX, _tstof(cstrValue));

	*pResult = 0;
}

void CInspectorView::OnRotY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstrValue;
	m_fRotY.GetWindowTextW(cstrValue);
	SpinBtn(pNMUpDown, &m_fRotY, _tstof(cstrValue));

	*pResult = 0;
}

void CInspectorView::OnRotZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstrValue;
	m_fRotZ.GetWindowTextW(cstrValue);
	SpinBtn(pNMUpDown, &m_fRotZ, _tstof(cstrValue));

	*pResult = 0;
}

void CInspectorView::OnScaleX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstrValue;
	m_fScaleX.GetWindowTextW(cstrValue);
	SpinBtn(pNMUpDown, &m_fScaleX, _tstof(cstrValue));

	*pResult = 0;
}

void CInspectorView::OnScaleY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstrValue;
	m_fScaleY.GetWindowTextW(cstrValue);
	SpinBtn(pNMUpDown, &m_fScaleY, _tstof(cstrValue));

	*pResult = 0;
}

void CInspectorView::OnScaleZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstrValue;
	m_fScaleZ.GetWindowTextW(cstrValue);
	SpinBtn(pNMUpDown, &m_fScaleZ, _tstof(cstrValue));

	*pResult = 0;
}

void CInspectorView::OnBnClickedObjectRadio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_arrCreateWay[0].EnableWindow(false);
	m_arrCreateWay[0].SetCheck(false);
	m_arrCreateWay[1].EnableWindow(false);
	m_arrCreateWay[1].SetCheck(false);
}

void CInspectorView::OnBnClickedBlock()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_arrCreateWay[0].EnableWindow(true);
	m_arrCreateWay[1].EnableWindow(true);
}

void CInspectorView::OnBnClickedNavi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//m_arrCreateWay[0].EnableWindow(false);
	//m_arrCreateWay[0].SetCheck(false);
	//m_arrCreateWay[1].EnableWindow(false);
	//m_arrCreateWay[1].SetCheck(false);
}

void CInspectorView::OnBnClickedSaveBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::string filePath = "../../Data/Save.txt";
	std::wofstream ofsSave(filePath.data());

	//if (ofsSave.is_open())
	//{
	//	const auto& mapObjects = Engine::CManagement::GetInstance()->Get_CurScene()->Get_MapObject(L"GameLogic");
	//	
	//	for (auto& iter = mapObjects->begin(); iter != mapObjects->end(); ++iter)
	//	{
	//		CGameObject* obj = iter->second;

	//		if (L"TestCamera" == obj->Get_ObjTag())
	//			continue;

	//		ofsSave << "ObjectType=" << obj->Get_ObjType() << "\n";
	//		ofsSave << "ObjectTag=" << obj->Get_ObjTag() << "\n";

	//		_vec3 vObj = {};
	//		Engine::CTransform* pObjTransformCom = static_cast<Engine::CTransform*>(obj->Get_Component(L"Com_Transform", ID_DYNAMIC));
	//		
	//		pObjTransformCom->Get_Info(INFO::INFO_POS, &vObj);
	//		ofsSave << "Position=";
	//		ofsSave << vObj.x << "/";
	//		ofsSave << vObj.y << "/";
	//		ofsSave << vObj.z << "\n";

	//		//vObj = pObjTransformCom->Get_Scale();
	//		//ofsSave << "Scale=";
	//		//ofsSave << vObj.x << "/";
	//		//ofsSave << vObj.y << "/";
	//		//ofsSave << vObj.z << "\n\n";

	//		//ofsSave << "Rotation=";
	//	}

	//	AfxMessageBox(L"Save Success | ObjectListView.cpp");
	//}
	//else AfxMessageBox(L"Save Failed | ObjectListView.cpp");
}

void CInspectorView::OnBnClickedLoadBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//const auto& mapObjects = Engine::CManagement::GetInstance()->Get_CurScene()->Get_MapObject(L"GameLogic");

	//// 이미 툴에 오브젝트가 존재한다면 모두 제거
	//if (!mapObjects->empty())
	//{
	//	auto& iter = mapObjects->begin();

	//	for (; iter != mapObjects->end();)
	//	{
	//		if (L"TestCamera" == iter->second->Get_ObjTag())
	//		{
	//			++iter;
	//			continue;
	//		}

	//		iter = mapObjects->erase(iter);
	//	}

	//	if (mapObjects->empty())
	//	{
	//		std::cout << "obj empty" << std::endl;
	//	}
	//}

	//std::string strLine = "";
	//std::string filePath = "../../Data/Save.txt";
	//std::ifstream ifsLoad(filePath.data());
	//_tchar* objTag = nullptr;
	//_tchar* objType = nullptr;
	//_vec3 vPos, vRot;

	//while (!ifsLoad.eof())
	//{
	//	std::getline(ifsLoad, strLine);

	//	if ("" == strLine)
	//	{
	//		continue;
	//	}

	//	vector<std::string> vStr = split(strLine, '=');

	//	if (!objType)
	//	{
	//		std::wstring wstr = Engine::StrToWStr(vStr[1]);
	//		objType = _wcsdup(wstr.c_str());
	//		continue;
	//	}
	//	else if (!objTag)
	//	{
	//		std::wstring wstr = Engine::StrToWStr(vStr[1]);
	//		objTag = _wcsdup(wstr.c_str());
	//		continue;
	//	}
	//	
	//	CGameObject* pGameObject = nullptr;

	//	if (!wcscmp(L"Player", objType))
	//	{
	//		pGameObject = CPlayer::Create(*static_cast<CEditorScene*>(Engine::CManagement::GetInstance()->Get_CurScene())->Get_GraphicDev());
	//		NULL_CHECK_RETURN(pGameObject, );

	//		vStr = split(vStr[1], '/');
	//		vPos = { std::stof(vStr[0]), std::stof(vStr[1]), std::stof(vStr[2]) };

	//		static_cast<CPlayer*>(pGameObject)->Set_Pos(vPos);
	//	}
	//	else if (!wcscmp(L"Monster", objType))
	//	{
	//		_tchar pProtoTag[MAX_PATH] = L"Proto_";
	//		lstrcat(pProtoTag, objTag);

	//		pGameObject = CMonster::Create(*static_cast<CEditorScene*>(Engine::CManagement::GetInstance()->Get_CurScene())->Get_GraphicDev(), pProtoTag);
	//		NULL_CHECK_RETURN(pGameObject, );

	//		vStr = split(vStr[1], '/');
	//		vPos = { std::stof(vStr[0]), std::stof(vStr[1]), std::stof(vStr[2]) };

	//		static_cast<CMonster*>(pGameObject)->Set_Pos(vPos);
	//	}
	//	else if (!wcscmp(L"StaticObject", objType))
	//	{
	//		_tchar pProtoTag[MAX_PATH] = L"Proto_";
	//		lstrcat(pProtoTag, objTag);

	//		pGameObject = CEditorStaticObject::Create(*static_cast<CEditorScene*>(Engine::CManagement::GetInstance()->Get_CurScene())->Get_GraphicDev(), pProtoTag);
	//		NULL_CHECK_RETURN(pGameObject, );

	//		vStr = split(vStr[1], '/');
	//		vPos = { std::stof(vStr[0]), std::stof(vStr[1]), std::stof(vStr[2]) };

	//		static_cast<CEditorStaticObject*>(pGameObject)->Set_Pos(vPos);

	//		if (!wcscmp(L"Out_Door", objTag))
	//			static_cast<CTransform*>(pGameObject->Get_Component(L"Com_Transform", ID_DYNAMIC))->Rotation(ROTATION::ROT_Y, -10.1f);
	//	}

	//	if (E_FAIL == (*static_cast<CEditorScene*>(Engine::CManagement::GetInstance()->Get_CurScene())->Get_MapLayer()->find(L"GameLogic")->second).Add_GameObject(objTag, pGameObject))
	//	{
	//		Safe_Release(pGameObject);
	//		cout << "오브젝트 생성 실패" << endl;
	//	}
	//	
	//	cout << "Create!" << endl;
	//	objTag = nullptr;
	//	objType = nullptr;
	//}
	//AfxMessageBox(L"Load Success | ObjectListView.cpp");
}

void CInspectorView::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	//HTREEITEM hItemCur;

	//hItemCur = pNMTreeView->itemNew.hItem;
	//m_curTreeItem = m_Tree.GetItemText(hItemCur);

	//m_TreeList.ResetContent(); // 리스트박스 모든 내용 삭제

	//if (L"Boss" == m_curTreeItem)
	//{
	//	m_curSelPath = L"\\Bin\\Resource\\Mesh\\DynamicMesh\\Boss";
	//	m_curObj = L"Boss";
	//}
	//else if (L"Player" == m_curTreeItem)
	//{
	//	m_curSelPath = L"\\Bin\\Resource\\Mesh\\DynamicMesh\\Player";
	//	m_curObj = L"Player";
	//}
	//else if (L"Monster" == m_curTreeItem)
	//{
	//	m_curSelPath = L"\\Bin\\Resource\\Mesh\\DynamicMesh\\Monster";
	//	m_curObj = L"Monster";
	//}
	//else if (L"DynamicObject" == m_curTreeItem)
	//{
	//	m_curSelPath = L"\\Bin\\Resource\\Mesh\\DynamicMesh\\Object";
	//	m_curObj = L"DynamicObject";
	//}
	//else if (L"StaticObject" == m_curTreeItem)
	//{
	//	m_curSelPath = L"\\Bin\\Resource\\Mesh\\StaticMesh\\Object";
	//	m_curObj = L"StaticObject";
	//}

	//Set_List_Path((TCHAR*)(LPCTSTR)m_curSelPath);
}

void CInspectorView::Set_List_Path(TCHAR * path, _bool bCheck)
{
	TCHAR szPath[MAX_PATH] = L"";

	if (!bCheck)
	{
		GetCurrentDirectory(MAX_PATH, szPath);
		PathRemoveFileSpec(szPath);
	}
	
	lstrcat(szPath, path);
	lstrcat(szPath, L"\\*.*");

	CFileFind ff;
	BOOL bFound = ff.FindFile(szPath);
	CString fileName;

	while (bFound)
	{
		bFound = ff.FindNextFile();

		if (ff.IsDots()) continue;
		if (ff.IsDirectory())
			Set_List_Path((TCHAR*)(LPCTSTR)ff.GetFilePath(), TRUE);
		else
		{
			CString _fileName = ff.GetFileName();
			fileName = ff.GetFileTitle();
			m_TreeList.AddString(_fileName);
		}
	}
}

void CInspectorView::OnLbnSelchangeMeshList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());

	//m_TreeList.GetText(m_TreeList.GetCurSel(), m_curSelFileName);

	//wcout << m_curSelFileName.GetString() << endl;
}
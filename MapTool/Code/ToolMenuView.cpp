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
	ON_BN_CLICKED(IDC_BUTTON1, &CToolMenuView::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CToolMenuView::OnBnClickedLoadBtn)
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
	HTREEITEM staticMeshChild[7];
	HTREEITEM textureChild[17];
	HTREEITEM prefabChild[4];

	root[0] = m_tree.InsertItem(L"Dynamic", 0, 1, TVI_ROOT, TVI_FIRST);
	dynamicMeshChild[0] = m_tree.InsertItem(L"Player", 1, 1, root[0], TVI_FIRST);
	dynamicMeshChild[1] = m_tree.InsertItem(L"Monster", 1, 1, root[0], TVI_FIRST);
	dynamicMeshChild[2] = m_tree.InsertItem(L"Object", 1, 1, root[0], TVI_FIRST);

	root[1] = m_tree.InsertItem(L"Static", 0, 1, TVI_ROOT, TVI_LAST);
	staticMeshChild[0] = m_tree.InsertItem(L"Map", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[1] = m_tree.InsertItem(L"CatPaw", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[2] = m_tree.InsertItem(L"Weapon_Kiana", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[3] = m_tree.InsertItem(L"Weapon_Monster", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[4] = m_tree.InsertItem(L"Weapon_Sakura", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[5] = m_tree.InsertItem(L"Weapon_Theresa", 1, 1, root[1], TVI_FIRST);
	staticMeshChild[6] = m_tree.InsertItem(L"Static", 1, 1, root[1], TVI_FIRST);

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
	std::wcout << m_curSelFileName.GetString() << std::endl;
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

void CToolMenuView::ReadFile(ELayerID layerID, std::wofstream* ofsSave)
{
	Engine::CLayer* layer = Engine::GET_CUR_SCENE->GetLayers()[(_int)layerID];
	auto& playerObjs = layer->GetGameObjects();

	if (playerObjs.empty())
		return;

	for (_int i = 0; i < playerObjs.size(); ++i)
	{
		if ((layerID == ELayerID::Map) && (L"Cube0" == playerObjs[i]->GetName()))
			continue;

		if (0 == i)
			(*ofsSave) << "numOf" << playerObjs[0]->GetObjectKey() << '=' << playerObjs.size() << "\n\n";

		std::wstring name = playerObjs[i]->GetName();

		(*ofsSave) << name << "_static=" << playerObjs[i]->GetIsStatic() << "\n";
		(*ofsSave) << name << "_layerID=" << playerObjs[i]->GetLayerID() << "\n";
		(*ofsSave) << name << "_meshKey=" << playerObjs[i]->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]->GetMeshKey() << '\n';
		(*ofsSave) << name << "_initTex=" << playerObjs[i]->GetComponent<Engine::CMeshC>()->GetInitTex() << '\n';
		(*ofsSave) << name << "_renderID=" << playerObjs[i]->GetComponent<Engine::CGraphicsC>()->GetRenderID() << '\n';
		(*ofsSave) << name << "_scale=" << playerObjs[i]->GetTransform()->GetSize().x << ',' << playerObjs[i]->GetTransform()->GetSize().y << ',' << playerObjs[i]->GetTransform()->GetSize().z << '\n';
		(*ofsSave) << name << "_rotation=" << playerObjs[i]->GetTransform()->GetRotation().x << ',' << playerObjs[i]->GetTransform()->GetRotation().y << ',' << playerObjs[i]->GetTransform()->GetRotation().z << '\n';
		(*ofsSave) << name << "_position=" << playerObjs[i]->GetTransform()->GetPosition().x << ',' << playerObjs[i]->GetTransform()->GetPosition().y << ',' << playerObjs[i]->GetTransform()->GetPosition().z << '\n';
		//ofsSave << "collisionID=" << '\n';
	}

	(*ofsSave) << '\n';
}

_float CToolMenuView::GetEditControlData(CEdit* pEdit, LPNMUPDOWN pNMUpDown)
{
	CString cstrValue;
	pEdit->GetWindowTextW(cstrValue);

	_float value = (_float)_tstof(cstrValue);
	SpinBtn(pNMUpDown, pEdit, value);

	return value;
}

std::vector<std::string> CToolMenuView::split(std::string input, char delimiter)
{
	std::vector<std::string> answer;
	std::stringstream ss(input);
	std::string temp;

	while (getline(ss, temp, delimiter))
		answer.push_back(temp);

	return answer;
}

_bool CToolMenuView::WstrToBool(std::wstring wstr)
{
	_bool b = WstrToInt(wstr) == 1 ? true : false;

	return b;
}

_int CToolMenuView::WstrToInt(std::wstring wstr)
{
	return std::stoi(wstr);
}

_float CToolMenuView::StrToFloat(std::string str)
{
	return std::stof(str);
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//std::string filePath = "../../Resource/Data/EditorScene/save.txt";
	std::string filePath = "../../Data/EditorScene/save.txt";
	std::wofstream ofsSave(filePath.data());

	if (ofsSave.is_open())
	{
		ReadFile(ELayerID::Player, &ofsSave);
		ReadFile(ELayerID::Enemy, &ofsSave);
		ReadFile(ELayerID::Map, &ofsSave);

		//auto& layer = Engine::GET_CUR_SCENE->GetLayers().begin();

		//for (; layer != Engine::GET_CUR_SCENE->GetLayers().end(); ++layer)
		//{
		//	if ((*layer)->GetGameObjects().empty())
		//		continue;

		//	auto& obj = (*layer)->GetGameObjects().begin();

		//	if (L"Camera0" != (*obj)->GetName())
		//		ofsSave << "numOf" << (*obj)->GetObjectKey() << "=" << (*layer)->GetGameObjects().size() - 1 << "\n\n";

		//	for (; obj != (*layer)->GetGameObjects().end(); ++obj)
		//	{
		//		if (L"Camera0" == (*obj)->GetName() || L"Cube0" == (*obj)->GetName())
		//			continue;
		//		
		//		std::wstring name = (*obj)->GetName();

		//		ofsSave << name << "_static=" << (*obj)->GetIsStatic() << "\n";
		//		ofsSave << name << "_layerID=" << (*obj)->GetLayerID() << "\n";
		//		ofsSave << name << "_meshKey=" << (*obj)->GetComponent<Engine::CMeshC>()->GetMeshDatas()[0]->GetMeshKey() << '\n';
		//		ofsSave << name << "_initTex=" << (*obj)->GetComponent<Engine::CMeshC>()->GetInitTex() << '\n';
		//		ofsSave << name << "_renderID=" << (*obj)->GetComponent<Engine::CGraphicsC>()->GetRenderID() << '\n';
		//		ofsSave << name << "_scale=" << (*obj)->GetTransform()->GetSize().x << ',' << (*obj)->GetTransform()->GetSize().y << ',' << (*obj)->GetTransform()->GetSize().z << '\n';
		//		ofsSave << name << "_rotation=" << (*obj)->GetTransform()->GetRotation().x << ',' << (*obj)->GetTransform()->GetRotation().y << ',' << (*obj)->GetTransform()->GetRotation().z << '\n';
		//		ofsSave << name << "_position=" << (*obj)->GetTransform()->GetPosition().x << ',' << (*obj)->GetTransform()->GetPosition().y << ',' << (*obj)->GetTransform()->GetPosition().z << '\n';
		//		//ofsSave << "collisionID=" << '\n';
		//	}
		//}

		AfxMessageBox(L"Save Success | ObjectListView.cpp");
	}
	else AfxMessageBox(L"Save Failed | ObjectListView.cpp");
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
			if (L"Camera0" == (*obj)->GetName() || L"Cube0" == (*obj)->GetName())
				continue;

			(*obj)->SetDeleteThis(true);
		}
	}

	// 데이터 파일 불러오기
	std::string strLine = "";
	std::string filePath = "../../Data/EditorScene/Save.txt";
	std::ifstream ifsLoad(filePath.data());
	
	_float vPos = 0.f;
	_float vRot = 0.f;

	std::wstring protoObjectKey;
	_bool isStatic;
	_int layerID;
	std::wstring name;
	std::wstring meshKey;
	_bool initTex;
	_int renderID;
	_float3 position;
	_float3 scale;
	_float3 rotation;

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
			//std::wstring wstr = Engine::StrToWStr(vStr[0]);
			//dataTag = _wcsdup(wstr.c_str());

			std::wstring wstr = Engine::StrToWStr(vStr[1]);
			dataValue = _wcsdup(wstr.c_str());
		}

		if (!wcscmp(L"numOfEmptyObject", _wcsdup(Engine::StrToWStr(vStr[0]).c_str())))
			continue;

		std::vector<std::string> vStrTag = split(vStr[0], '_');

		std::wstring wstr = Engine::StrToWStr(vStrTag[1]);
		dataTag = _wcsdup(wstr.c_str());

		//if (!wcscmp(L"protoObjectKey", dataTag))
		//{
		//	protoObjectKey = dataValue;
		//	continue;
		//}
		if (!wcscmp(L"static", dataTag))
		{
			isStatic = WstrToBool(dataValue);
			continue;
		}
		else if (!wcscmp(L"layerID", dataTag))
		{
			layerID = WstrToInt(dataValue);
			continue;
		}
		//else if (!wcscmp(L"name", dataTag))
		//{
		//	// todo: 지정안했을 때 자동 지정 되는 이름은 저장하면 안됨
		//	name = dataValue;
		//	continue;
		//}
		else if (!wcscmp(L"meshKey", dataTag))
		{
			meshKey = dataValue;
			continue;
		}
		else if (!wcscmp(L"initTex", dataTag))
		{
			initTex =  WstrToBool(dataValue);
			continue;
		}
		else if (!wcscmp(L"renderID", dataTag))
		{
			renderID = WstrToInt(dataValue);
			continue;
		}
		else if (!wcscmp(L"scale", dataTag))
		{
			vStr = split(vStr[1], ',');
			scale = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };
			continue;
		}
		else if (!wcscmp(L"rotation", dataTag))
		{
			vStr = split(vStr[1], ',');
			rotation = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };
			continue;
		}
		else if (!wcscmp(L"position", dataTag))
		{
			vStr = split(vStr[1], ',');
			position = { StrToFloat(vStr[0]), StrToFloat(vStr[1]), StrToFloat(vStr[2]) };
		}

		SP(Engine::CObject) spObject
			= objectFactory->AddClone(L"EmptyObject", isStatic, layerID, name);

		spObject->AddComponent<Engine::CMeshC>()->AddMeshData(meshKey);
		spObject->GetComponent<Engine::CMeshC>()->SetInitTex(initTex);
		spObject->AddComponent<Engine::CGraphicsC>()->SetRenderID(renderID);
		spObject->AddComponent<Engine::CTextureC>();
		spObject->AddComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshShader);
		spObject->GetTransform()->SetSize(scale);
		spObject->GetTransform()->SetPosition(position);
		spObject->GetTransform()->SetRotation(rotation);
	}

	AfxMessageBox(L"Load Success | ObjectListView.cpp");
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
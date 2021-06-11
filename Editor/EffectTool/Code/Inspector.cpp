// ../Code/Inspector.cpp : ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ô´Ï´ï¿½.
//

#include "stdafx.h"
#include "EffectTool.h"
#include "../Header/Inspector.h"
#include "MeshEffect.h"
#include "Object.h"
#include "Layer.h"

// CInspector`

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CInspector, CFormView)

CInspector::CInspector()
	: CFormView(IDD_INSPECTOR)
{

}

CInspector::~CInspector()
{
}

void CInspector::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btnEffectList);
	DDX_Control(pDX, IDC_BUTTON2, m_btnEffectType);
	DDX_Control(pDX, IDC_BUTTON3, m_btnTextureType);
	DDX_Control(pDX, IDC_BUTTON4, m_btnFunction);
	DDX_Control(pDX, IDC_BUTTON5, m_btnEffectSetting);
	DDX_Control(pDX, IDC_BUTTON6, m_btn_SelectMode);
	DDX_Control(pDX, IDC_BUTTON7, m_btnOption);
	DDX_Control(pDX, IDC_BUTTON8, m_btn_Position);
	DDX_Control(pDX, IDC_BUTTON9, m_btn_Rotation);
	DDX_Control(pDX, IDC_BUTTON10, m_btn_Scale);
	DDX_Control(pDX, IDC_BUTTON11, m_btnStartTime);
	DDX_Control(pDX, IDC_BUTTON12, m_btnEndTime);
	DDX_Control(pDX, IDC_BUTTON13, m_btn_Repeat);
	DDX_Control(pDX, IDC_BUTTON14, m_btnModePos);
	DDX_Control(pDX, IDC_BUTTON15, m_btnModeRot);
	DDX_Control(pDX, IDC_BUTTON16, m_btnModeScale);
	DDX_Control(pDX, IDC_BUTTON17, m_btnTransform);
	DDX_Control(pDX, IDC_BUTTON18, m_btnEdit);
	DDX_Control(pDX, IDC_BUTTON19, m_btnFadeIn);
	DDX_Control(pDX, IDC_BUTTON20, m_btnFadeOut);
	DDX_Control(pDX, IDC_BUTTON21, m_btnUVSprite);
	DDX_Control(pDX, IDC_BUTTON22, m_btnUVAnimation);
	DDX_Control(pDX, IDC_BUTTON23, m_btnOptionPos);
	DDX_Control(pDX, IDC_BUTTON24, m_btnOptionRot);
	DDX_Control(pDX, IDC_BUTTON25, m_btnOptionScale);
	DDX_Control(pDX, IDC_BUTTON26, m_btnOptionFadeIn);
	DDX_Control(pDX, IDC_BUTTON27, m_btnOptionFadeOut);
	DDX_Control(pDX, IDC_BUTTON28, m_btnOptionUVSp);
	DDX_Control(pDX, IDC_BUTTON29, m_btnOptionUVAnim);
	DDX_Control(pDX, IDC_BUTTON30, m_btnAction);
	DDX_Control(pDX, IDC_MFCBUTTON6, m_btnStart);
	DDX_Control(pDX, IDC_MFCBUTTON7, m_btnPause);
	DDX_Control(pDX, IDC_MFCBUTTON8, m_btnStop);
	DDX_Control(pDX, IDC_MFCBUTTON9, m_btnSave);
	DDX_Control(pDX, IDC_MFCBUTTON10, m_btnLoad);
	DDX_Control(pDX, IDC_MFCBUTTON4, m_btnTexture);
	DDX_Control(pDX, IDC_MFCBUTTON5, m_btnAlphaMask);
	DDX_Control(pDX, IDC_MFCBUTTON3, m_btnSoftEffect);
	DDX_Control(pDX, IDC_MFCBUTTON2, m_btnMeshEffect);
	DDX_Control(pDX, IDC_BUTTON31, m_btnLoop);
	DDX_Control(pDX, IDC_BUTTON32, m_btnBillboard);
	DDX_Control(pDX, IDC_MFCBUTTON1, m_btnListDelete);
	DDX_Control(pDX, IDC_BUTTON33, m_btnPosX);
	DDX_Control(pDX, IDC_BUTTON34, m_btnPosY);
	DDX_Control(pDX, IDC_BUTTON35, m_btnPosZ);
	DDX_Control(pDX, IDC_BUTTON36, m_btnRotX);
	DDX_Control(pDX, IDC_BUTTON38, m_btnRotY);
	DDX_Control(pDX, IDC_BUTTON37, m_btnRotZ);
	DDX_Control(pDX, IDC_BUTTON39, m_btnScaleX);
	DDX_Control(pDX, IDC_BUTTON41, m_btnScaleY);
	DDX_Control(pDX, IDC_BUTTON40, m_btnScaleZ);
	DDX_Control(pDX, IDC_BUTTON42, m_btnAlphaWidth);
	DDX_Control(pDX, IDC_BUTTON43, m_btnAlphaHeight);
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
}

void CInspector::EditButtonStyle()
{
	m_btnEffectList.LoadBitmaps(IDB_BITMAP_EFFECTLIST);
	m_btnEffectList.SizeToContent();

	m_btnEffectType.LoadBitmaps(IDB_BITMAP_EFFECTTYPE);
	m_btnEffectType.SizeToContent();

	m_btnTextureType.LoadBitmaps(IDB_BITMAP_TEXTRUETYPE);
	m_btnTextureType.SizeToContent();

	m_btnFunction.LoadBitmaps(IDB_BITMAP_FUNCTION);
	m_btnFunction.SizeToContent();

	m_btnEffectSetting.LoadBitmaps(IDB_BITMAP_EFFECTSETTING);
	m_btnEffectSetting.SizeToContent();

	m_btn_SelectMode.LoadBitmaps(IDB_BITMAP_SELECTMODE);
	m_btn_SelectMode.SizeToContent();

	m_btnOption.LoadBitmaps(IDB_BITMAP_OPTION);
	m_btnOption.SizeToContent();

	m_btn_Position.LoadBitmaps(IDB_BITMAP_POSITION);
	m_btn_Position.SizeToContent();

	m_btn_Rotation.LoadBitmaps(IDB_BITMAP_ROTATION);
	m_btn_Rotation.SizeToContent();

	m_btn_Scale.LoadBitmaps(IDB_BITMAP_SCALE);
	m_btn_Scale.SizeToContent();

	m_btnStartTime.LoadBitmaps(IDB_BITMAP_STARTTIME);
	m_btnStartTime.SizeToContent();

	m_btnEndTime.LoadBitmaps(IDB_BITMAP_ENDTIME);
	m_btnEndTime.SizeToContent();

	m_btn_Repeat.LoadBitmaps(IDB_BITMAP_REPEAT);
	m_btn_Repeat.SizeToContent();

	m_btnModePos.LoadBitmaps(IDB_BITMAP_POSITION);
	m_btnModePos.SizeToContent();

	m_btnModeRot.LoadBitmaps(IDB_BITMAP_ROTATION);
	m_btnModeRot.SizeToContent();

	m_btnModeScale.LoadBitmaps(IDB_BITMAP_SCALE);
	m_btnModeScale.SizeToContent();

	m_btnTransform.LoadBitmaps(IDB_BITMAP_TRANSFORM);
	m_btnTransform.SizeToContent();

	m_btnEdit.LoadBitmaps(IDB_BITMAP_EDIT);
	m_btnEdit.SizeToContent();

	m_btnFadeIn.LoadBitmaps(IDB_BITMAP_FADEIN);
	m_btnFadeIn.SizeToContent();

	m_btnFadeOut.LoadBitmaps(IDB_BITMAP_FADEOUT);
	m_btnFadeOut.SizeToContent();

	m_btnUVSprite.LoadBitmaps(IDB_BITMAP_UVSPRITE);
	m_btnUVSprite.SizeToContent();

	m_btnUVAnimation.LoadBitmaps(IDB_BITMAP_UVANIMATION);
	m_btnUVAnimation.SizeToContent();

	m_btnOptionPos.LoadBitmaps(IDB_BITMAP_POSITION);
	m_btnOptionPos.SizeToContent();

	m_btnOptionRot.LoadBitmaps(IDB_BITMAP_ROTATION);
	m_btnOptionRot.SizeToContent();

	m_btnOptionScale.LoadBitmaps(IDB_BITMAP_SCALE);
	m_btnOptionScale.SizeToContent();

	m_btnOptionFadeIn.LoadBitmaps(IDB_BITMAP_FADEIN);
	m_btnOptionFadeIn.SizeToContent();

	m_btnOptionFadeOut.LoadBitmaps(IDB_BITMAP_FADEOUT);
	m_btnOptionFadeOut.SizeToContent();

	m_btnOptionUVSp.LoadBitmaps(IDB_BITMAP_UVSPRITE);
	m_btnOptionUVSp.SizeToContent();

	m_btnOptionUVAnim.LoadBitmaps(IDB_BITMAP_UVANIMATION);
	m_btnOptionUVAnim.SizeToContent();

	m_btnAction.LoadBitmaps(IDB_BITMAP_ACTION);
	m_btnAction.SizeToContent();

	m_btnLoop.LoadBitmaps(IDB_BITMAP_LOOP);
	m_btnLoop.SizeToContent();

	m_btnBillboard.LoadBitmaps(IDB_BITMAP_BILLBOARD);
	m_btnBillboard.SizeToContent();

	// Setting
	m_btnPosX.LoadBitmaps(IDB_BITMAP_X);
	m_btnPosX.SizeToContent();

	m_btnPosY.LoadBitmaps(IDB_BITMAP_Y);
	m_btnPosY.SizeToContent();

	m_btnPosZ.LoadBitmaps(IDB_BITMAP_Z);
	m_btnPosZ.SizeToContent();

	m_btnRotX.LoadBitmaps(IDB_BITMAP_X);
	m_btnRotX.SizeToContent();

	m_btnRotY.LoadBitmaps(IDB_BITMAP_Y);
	m_btnRotY.SizeToContent();

	m_btnRotZ.LoadBitmaps(IDB_BITMAP_Z);
	m_btnRotZ.SizeToContent();

	m_btnScaleX.LoadBitmaps(IDB_BITMAP_X);
	m_btnScaleX.SizeToContent();

	m_btnScaleY.LoadBitmaps(IDB_BITMAP_Y);
	m_btnScaleY.SizeToContent();

	m_btnScaleZ.LoadBitmaps(IDB_BITMAP_Z);
	m_btnScaleZ.SizeToContent();

	m_btnAlphaWidth.LoadBitmaps(IDB_BITMAP_WIDTH);
	m_btnAlphaWidth.SizeToContent();

	m_btnAlphaHeight.LoadBitmaps(IDB_BITMAP_HEIGHT);
	m_btnAlphaHeight.SizeToContent();

	// Event Button

	m_btnStart.EnableWindowsTheming(FALSE);
	m_btnStart.SetFaceColor(RGB(50, 50, 50));
	m_btnStart.SetTextColor(RGB(255, 255, 255));

	m_btnPause.EnableWindowsTheming(FALSE);
	m_btnPause.SetFaceColor(RGB(50, 50, 50));
	m_btnPause.SetTextColor(RGB(255, 255, 255));

	m_btnStop.EnableWindowsTheming(FALSE);
	m_btnStop.SetFaceColor(RGB(50, 50, 50));
	m_btnStop.SetTextColor(RGB(255, 255, 255));

	m_btnSave.EnableWindowsTheming(FALSE);
	m_btnSave.SetFaceColor(RGB(50, 50, 50));
	m_btnSave.SetTextColor(RGB(255, 255, 255));

	m_btnLoad.EnableWindowsTheming(FALSE);
	m_btnLoad.SetFaceColor(RGB(50, 50, 50));
	m_btnLoad.SetTextColor(RGB(255, 255, 255));

	m_btnTexture.EnableWindowsTheming(FALSE);
	m_btnTexture.SetFaceColor(RGB(50, 50, 50));
	m_btnTexture.SetTextColor(RGB(255, 255, 255));

	m_btnAlphaMask.EnableWindowsTheming(FALSE);
	m_btnAlphaMask.SetFaceColor(RGB(50, 50, 50));
	m_btnAlphaMask.SetTextColor(RGB(255, 255, 255));

	m_btnSoftEffect.EnableWindowsTheming(FALSE);
	m_btnSoftEffect.SetFaceColor(RGB(50, 50, 50));
	m_btnSoftEffect.SetTextColor(RGB(255, 255, 255));

	m_btnMeshEffect.EnableWindowsTheming(FALSE);
	m_btnMeshEffect.SetFaceColor(RGB(50, 50, 50));
	m_btnMeshEffect.SetTextColor(RGB(255, 255, 255));

	m_btnListDelete.EnableWindowsTheming(FALSE);
	m_btnListDelete.SetFaceColor(RGB(50, 50, 50));
	m_btnListDelete.SetTextColor(RGB(255, 255, 255));
}

BEGIN_MESSAGE_MAP(CInspector, CFormView)
	ON_WM_PAINT()
	ON_WM_PAINT()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CInspector::OnTvnSelchangedEffectList)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CInspector::OnBnClickedDeleteEffectList)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CInspector::OnBnClickedMeshEffect)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CInspector::OnBnClickedSoftEffect)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CInspector::OnBnClickedTexture)
	ON_BN_CLICKED(IDC_MFCBUTTON5, &CInspector::OnBnClickedAlphaMask)
END_MESSAGE_MAP()


// CInspector ï¿½ï¿½ï¿½ï¿½ï¿½Ô´Ï´ï¿½.

#ifdef _DEBUG
void CInspector::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInspector::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInspector ï¿½Þ½ï¿½ï¿½ï¿½ Ã³ï¿½ï¿½ï¿½ï¿½ï¿½Ô´Ï´ï¿½.

void CInspector::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_hBitmap = LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_MAIN_BG));
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bitmap);
	EditButtonStyle();
	///////////////////////////////////////////////////

	m_hEffect = m_TreeCtrl.InsertItem(L"Effect", 0, 1, TVI_ROOT, TVI_LAST);
}

void CInspector::OnPaint()
{
		CPaintDC dc(this); // device context for painting
						   // TODO: ï¿½ï¿½ï¿½â¿¡ ï¿½Þ½ï¿½ï¿½ï¿½ Ã³ï¿½ï¿½ï¿½ï¿½ ï¿½Úµå¸¦ ï¿½ß°ï¿½ï¿½Õ´Ï´ï¿½.
						   // ï¿½×¸ï¿½ï¿½ï¿½ ï¿½Þ½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ø¼ï¿½ï¿½ï¿½ CFormView::OnPaint()ï¿½ï¿½(ï¿½ï¿½) È£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ê½Ã¿ï¿½.

		CRect rect;
		GetWindowRect(&rect); // ï¿½ï¿½Å©ï¿½ï¿½ï¿½ï¿½ È£È¯ï¿½Ç´ï¿½ DCï¿½ï¿½ï¿½ï¿½.
		HDC hMemDC = CreateCompatibleDC(dc); SetStretchBltMode(hMemDC, HALFTONE); // È£È¯DCï¿½ï¿½ ï¿½ï¿½Æ®ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½.
		SelectObject(hMemDC, m_hBitmap); // ï¿½Þ¸ï¿½ï¿½ï¿½ DCï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Å©ï¿½ï¿½ DCï¿½ï¿½ ï¿½Ì¹ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		StretchBlt(dc, 0, 0, rect.Width(), rect.Height(), hMemDC, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
		// ï¿½Þ¸ï¿½ï¿½ï¿½ DCï¿½ï¿½ï¿½ï¿½
		DeleteDC(hMemDC);

}

void CInspector::OnTvnSelchangedEffectList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;
}


void CInspector::OnBnClickedDeleteEffectList()
{
	m_TreeCtrl.DeleteAllItems();
	
	Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->ClearLayer();

	m_hEffect = m_TreeCtrl.InsertItem(L"Effect", 0, 1, TVI_ROOT, TVI_LAST);
}


void CInspector::OnBnClickedMeshEffect()
{
	CString str = _T("X Files(*.x) |*.x|"); // x ÆÄÀÏ Ç¥½Ã

	LPWSTR lpwstr = _SOLUTIONDIR L"Resource\\Mesh\\EffectToolScene\\Static\\MeshEffect";

	CFileDialog dlg(TRUE, _T("*.x"), NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, str);

	dlg.m_ofn.lpstrInitialDir = lpwstr;

	// IDOK = OK button is pressed in the dialog
	if (dlg.DoModal() == IDOK)
	{
		CString strFilePath = dlg.GetPathName();

		strFilePath = strFilePath.Right(strFilePath.GetLength() - strFilePath.ReverseFind('\\') - 1);

		m_hMeshEffectItem = m_TreeCtrl.InsertItem(strFilePath, 1, 1, m_hEffect, TVI_LAST);

		Add_MeshEffect(strFilePath);

		InvalidateRect(false);

	}
}


void CInspector::OnBnClickedSoftEffect()
{
	CString str = _T("png Files(*.png) |*.png|"); // png ÆÄÀÏ Ç¥½Ã
	LPWSTR lpwstr = _SOLUTIONDIR L"Resource\\Mesh\\EffectToolScene\\Static\\SoftEffect\\";
	CFileDialog dlg(TRUE, _T("*.png"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	dlg.m_ofn.lpstrInitialDir = lpwstr;

	if (dlg.DoModal() == IDOK)
	{

		CString strFilePath = dlg.GetPathName();

		strFilePath = strFilePath.Right(strFilePath.GetLength() - strFilePath.ReverseFind('\\') - 1);

		m_hSoftEffectItem = m_TreeCtrl.InsertItem(strFilePath, 1, 1, m_hEffect, TVI_LAST);

		Add_SoftEffect(strFilePath);

		InvalidateRect(false);
	}
}

void CInspector::OnBnClickedTexture()
{
	CString str = _T("png Files(*.png) |*.png|"); // png ÆÄÀÏ Ç¥½Ã
	LPWSTR lpwstr = _SOLUTIONDIR L"Resource\\Mesh\\EffectToolScene\\Static\\";
	CFileDialog dlg(TRUE, _T("*.png"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	dlg.m_ofn.lpstrInitialDir = lpwstr;

	if (dlg.DoModal() == IDOK)
	{

		CString strFilePath = dlg.GetPathName();

		strFilePath = strFilePath.Right(strFilePath.GetLength() - strFilePath.ReverseFind('\\') - 1);

		Add_Texture(strFilePath);

		InvalidateRect(false);
	}
}


void CInspector::OnBnClickedAlphaMask()
{
	CString str = _T("png Files(*.png) |*.png|"); // png ÆÄÀÏ Ç¥½Ã
	LPWSTR lpwstr = _SOLUTIONDIR L"Resource\\Mesh\\EffectToolScene\\Static\\";

	CFileDialog dlg(TRUE, _T("*.png"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	dlg.m_ofn.lpstrInitialDir = lpwstr;

	if (dlg.DoModal() == IDOK)
	{
		CString strFilePath = dlg.GetPathName();

		strFilePath = strFilePath.Right(strFilePath.GetLength() - strFilePath.ReverseFind('\\') - 1);

		Add_AlphaMask(strFilePath);

		InvalidateRect(false);
	}
}

void CInspector::Add_MeshEffect(CString ObjectName)
{
	SP(Engine::CObject) spMeshEffect
		= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MeshEffect", false, (_int)Engine::ELayerID::Effect, L"Effect0");
	spMeshEffect->GetComponent<Engine::CMeshC>()->AddMeshData(Engine::RemoveExtension(ObjectName.operator LPCWSTR()));
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)ERenderID::AlphaBlend);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"DefaultMeshTex");
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::WaterShader);
}

void CInspector::Add_SoftEffect(CString ObjectName)
{
}

void CInspector::Add_Texture(CString TextureKey)
{
	for (auto& obj : Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects())
	{
		SP(Engine::CTextureC) spTexture = obj->GetComponent<Engine::CTextureC>();
		obj->GetComponent<Engine::CShader>()->GetEffect()->SetTexture("g_NormalMap", spTexture->GetTexData()[spTexture->GetMeshIndex()][1]->pTexture);
	}

}

void CInspector::Add_AlphaMask(CString TextureKey)
{
}

CString CInspector::InitFilePath(CString _filePath)
{
	_TCHAR PathName[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, PathName);
	PathRemoveFileSpec(PathName);
	PathRemoveFileSpec(PathName);
	PathRemoveFileSpec(PathName);
	lstrcat(PathName, _filePath);

	return PathName;
}
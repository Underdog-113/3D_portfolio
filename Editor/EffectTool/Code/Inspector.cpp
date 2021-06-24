#include "stdafx.h"
#include "EffectTool.h"
#include "../Header/Inspector.h"
#include "MeshEffect.h"
#include "Object.h"
#include "Layer.h"
#include "SoftEffect.h"
// CInspector

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CInspector, CFormView)

CInspector::CInspector()
	: CFormView(IDD_INSPECTOR)
{
	m_ObjectTag = L"";
	m_iSelectObjectNum = -1;
	m_fSpeed = 0.1f;
	m_fAnimSpeed = 1.f;
	m_iRepeatCnt = 0;
	m_isPlayAnim = false;
	m_vSavePos.z = 2.f;
	m_eActionState = STATE_END;
	m_fAlphaWidth = 0.f;
	m_fAlphaHeight = 0.f;
	m_iTilingX = 1;
	m_iTilingY = 1;
}

CInspector::~CInspector()
{
}

void CInspector::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_bmp_EffectList);
	DDX_Control(pDX, IDC_BUTTON2, m_bmp_EffectType);
	DDX_Control(pDX, IDC_BUTTON3, m_bmp_TextureType);
	DDX_Control(pDX, IDC_BUTTON4, m_bmp_Function);
	DDX_Control(pDX, IDC_BUTTON5, m_bmp_EffectSetting);
	DDX_Control(pDX, IDC_BUTTON6, m_bmp_SelectMode);
	DDX_Control(pDX, IDC_BUTTON7, m_bmp_Option);
	DDX_Control(pDX, IDC_BUTTON8, m_bmp_Position);
	DDX_Control(pDX, IDC_BUTTON9, m_bmp_Rotation);
	DDX_Control(pDX, IDC_BUTTON10, m_bmp_Scale);
	DDX_Control(pDX, IDC_BUTTON11, m_bmp_StartTime);
	DDX_Control(pDX, IDC_BUTTON12, m_bmp_EndTime);
	DDX_Control(pDX, IDC_BUTTON13, m_bmp_Repeat);
	DDX_Control(pDX, IDC_BUTTON14, m_bmp_ModePos);
	DDX_Control(pDX, IDC_BUTTON15, m_bmp_ModeRot);
	DDX_Control(pDX, IDC_BUTTON16, m_bmp_ModeScale);
	DDX_Control(pDX, IDC_BUTTON17, m_bmp_Transform);
	DDX_Control(pDX, IDC_BUTTON18, m_bmp_Edit);
	DDX_Control(pDX, IDC_BUTTON19, m_bmp_FadeIn);
	DDX_Control(pDX, IDC_BUTTON20, m_bmp_FadeOut);
	DDX_Control(pDX, IDC_BUTTON21, m_bmp_UVSprite);
	DDX_Control(pDX, IDC_BUTTON22, m_bmp_UVAnimation);
	DDX_Control(pDX, IDC_BUTTON23, m_bmp_OptionPos);
	DDX_Control(pDX, IDC_BUTTON24, m_bmp_OptionRot);
	DDX_Control(pDX, IDC_BUTTON25, m_bmp_OptionScale);
	DDX_Control(pDX, IDC_BUTTON26, m_bmp_OptionFadeIn);
	DDX_Control(pDX, IDC_BUTTON27, m_bmp_OptionFadeOut);
	DDX_Control(pDX, IDC_BUTTON28, m_bmp_OptionUVSp);
	DDX_Control(pDX, IDC_BUTTON29, m_bmp_OptionUVAnim);
	DDX_Control(pDX, IDC_BUTTON30, m_bmp_Action);
	DDX_Control(pDX, IDC_MFCBUTTON6, m_btnStart);
	DDX_Control(pDX, IDC_MFCBUTTON7, m_btnPause);
	DDX_Control(pDX, IDC_MFCBUTTON8, m_btnStop);
	DDX_Control(pDX, IDC_MFCBUTTON9, m_btnSave);
	DDX_Control(pDX, IDC_MFCBUTTON10, m_btnLoad);
	DDX_Control(pDX, IDC_MFCBUTTON4, m_btnTexture);
	DDX_Control(pDX, IDC_MFCBUTTON5, m_btnAlphaMask);
	DDX_Control(pDX, IDC_MFCBUTTON3, m_btnSoftEffect);
	DDX_Control(pDX, IDC_MFCBUTTON2, m_btnMeshEffect);
	DDX_Control(pDX, IDC_BUTTON31, m_bmp_Loop);
	DDX_Control(pDX, IDC_BUTTON32, m_bmp_Billboard);
	DDX_Control(pDX, IDC_MFCBUTTON1, m_btnListDelete);
	DDX_Control(pDX, IDC_BUTTON33, m_bmp_PosX);
	DDX_Control(pDX, IDC_BUTTON34, m_bmp_PosY);
	DDX_Control(pDX, IDC_BUTTON35, m_bmp_PosZ);
	DDX_Control(pDX, IDC_BUTTON36, m_bmp_RotX);
	DDX_Control(pDX, IDC_BUTTON38, m_bmp_RotY);
	DDX_Control(pDX, IDC_BUTTON37, m_bmp_RotZ);
	DDX_Control(pDX, IDC_BUTTON39, m_bmp_ScaleX);
	DDX_Control(pDX, IDC_BUTTON41, m_bmp_ScaleY);
	DDX_Control(pDX, IDC_BUTTON40, m_bmp_ScaleZ);
	DDX_Control(pDX, IDC_BUTTON42, m_bmp_AlphaWidth);
	DDX_Control(pDX, IDC_BUTTON43, m_bmp_AlphaHeight);
	DDX_Control(pDX, IDC_EDIT1, m_edPosX);
	DDX_Control(pDX, IDC_EDIT4, m_edPosY);
	DDX_Control(pDX, IDC_EDIT7, m_edPosZ);
	DDX_Control(pDX, IDC_EDIT2, m_edRotX);
	DDX_Control(pDX, IDC_EDIT5, m_edRotY);
	DDX_Control(pDX, IDC_EDIT8, m_edRotZ);
	DDX_Control(pDX, IDC_EDIT3, m_edScaleX);
	DDX_Control(pDX, IDC_EDIT6, m_edScaleY);
	DDX_Control(pDX, IDC_EDIT9, m_edScaleZ);
	DDX_Control(pDX, IDC_EDIT12, m_edStartTime);
	DDX_Control(pDX, IDC_EDIT13, m_edEndTIme);
	DDX_Control(pDX, IDC_EDIT14, m_edRepeat);
	DDX_Control(pDX, IDC_EDIT10, m_edAlphaWidth);
	DDX_Control(pDX, IDC_EDIT11, m_edAlphaHeight);
	DDX_Control(pDX, IDC_CHECK1, m_btnLoop);
	DDX_Control(pDX, IDC_CHECK2, m_btnBillboard);
	DDX_Control(pDX, IDC_CHECK5, m_btnOptionPos);
	DDX_Control(pDX, IDC_CHECK4, m_btnOptionRot);
	DDX_Control(pDX, IDC_CHECK3, m_btnOptionScale);
	DDX_Control(pDX, IDC_CHECK7, m_btnOptionFadeIn);
	DDX_Control(pDX, IDC_CHECK6, m_btnOptionFadeOut);
	DDX_Control(pDX, IDC_CHECK9, m_btnOptionUVSprite);
	DDX_Control(pDX, IDC_CHECK8, m_btnOptionUVAnim);
	DDX_Control(pDX, IDC_RADIO1, m_btnModeTransform);
	DDX_Control(pDX, IDC_RADIO2, m_btnModeEdit);
	DDX_Control(pDX, IDC_RADIO3, m_btnModePosition);
	DDX_Control(pDX, IDC_RADIO4, m_btnModeRotation);
	DDX_Control(pDX, IDC_RADIO5, m_btnModeFadeIn);
	DDX_Control(pDX, IDC_RADIO6, m_btnModeFadeOut);
	DDX_Control(pDX, IDC_RADIO7, m_btnModeUVSprite);
	DDX_Control(pDX, IDC_RADIO8, m_btnModeUVAnim);
	DDX_Control(pDX, IDC_RADIO9, m_btnModeScale);
	DDX_Control(pDX, IDC_SPIN1, m_spinPosX);
	DDX_Control(pDX, IDC_SPIN4, m_spinPosY);
	DDX_Control(pDX, IDC_SPIN7, m_spinPosZ);
	DDX_Control(pDX, IDC_SPIN10, m_spinAlphaWidth);
	DDX_Control(pDX, IDC_SPIN11, m_spinAlphaHeigth);
	DDX_Control(pDX, IDC_SPIN3, m_spinScaleX);
	DDX_Control(pDX, IDC_SPIN6, m_spinScaleY);
	DDX_Control(pDX, IDC_SPIN9, m_spinScaleZ);
	DDX_Control(pDX, IDC_BUTTON44, m_bmp_Speed);
	DDX_Control(pDX, IDC_BUTTON45, m_bmpAnimSpeed);
	DDX_Control(pDX, IDC_LIST1, m_EffectListBox);
	DDX_Control(pDX, IDC_BUTTON46, m_bmpTilingXTitle);
	DDX_Control(pDX, IDC_BUTTON47, m_bmpTilingX);
	DDX_Control(pDX, IDC_BUTTON48, m_bmpTilingY);
	DDX_Control(pDX, IDC_EDIT17, m_edTilingX);
	DDX_Control(pDX, IDC_EDIT18, m_edTilingY);
	DDX_Control(pDX, IDC_SPIN15, m_spinTilingX);
	DDX_Control(pDX, IDC_SPIN16, m_spinTilingY);
	DDX_Control(pDX, IDC_BUTTON49, m_bmpIndexX);
	DDX_Control(pDX, IDC_BUTTON50, m_bmpIndexY);
	DDX_Control(pDX, IDC_BUTTON51, m_bmpTilingYTitle);
	DDX_Control(pDX, IDC_CHECK10, m_btnTestButton);
}

void CInspector::EditButtonStyle()
{
	m_bmp_EffectList.LoadBitmaps(IDB_BITMAP_EFFECTLIST);
	m_bmp_EffectList.SizeToContent();

	m_bmp_EffectType.LoadBitmaps(IDB_BITMAP_EFFECTTYPE);
	m_bmp_EffectType.SizeToContent();

	m_bmp_TextureType.LoadBitmaps(IDB_BITMAP_TEXTRUETYPE);
	m_bmp_TextureType.SizeToContent();

	m_bmp_Function.LoadBitmaps(IDB_BITMAP_FUNCTION);
	m_bmp_Function.SizeToContent();

	m_bmp_EffectSetting.LoadBitmaps(IDB_BITMAP_EFFECTSETTING);
	m_bmp_EffectSetting.SizeToContent();

	m_bmp_SelectMode.LoadBitmaps(IDB_BITMAP_SELECTMODE);
	m_bmp_SelectMode.SizeToContent();

	m_bmp_Option.LoadBitmaps(IDB_BITMAP_OPTION);
	m_bmp_Option.SizeToContent();

	m_bmp_Position.LoadBitmaps(IDB_BITMAP_POSITION);
	m_bmp_Position.SizeToContent();

	m_bmp_Rotation.LoadBitmaps(IDB_BITMAP_ROTATION);
	m_bmp_Rotation.SizeToContent();

	m_bmp_Scale.LoadBitmaps(IDB_BITMAP_SCALE);
	m_bmp_Scale.SizeToContent();

	m_bmp_StartTime.LoadBitmaps(IDB_BITMAP_STARTTIME);
	m_bmp_StartTime.SizeToContent();

	m_bmp_EndTime.LoadBitmaps(IDB_BITMAP_ENDTIME);
	m_bmp_EndTime.SizeToContent();

	m_bmp_Repeat.LoadBitmaps(IDB_BITMAP_REPEAT);
	m_bmp_Repeat.SizeToContent();

	m_bmp_ModePos.LoadBitmaps(IDB_BITMAP_POSITION);
	m_bmp_ModePos.SizeToContent();

	m_bmp_ModeRot.LoadBitmaps(IDB_BITMAP_ROTATION);
	m_bmp_ModeRot.SizeToContent();

	m_bmp_ModeScale.LoadBitmaps(IDB_BITMAP_SCALE);
	m_bmp_ModeScale.SizeToContent();

	m_bmp_Transform.LoadBitmaps(IDB_BITMAP_TRANSFORM);
	m_bmp_Transform.SizeToContent();

	m_bmp_Edit.LoadBitmaps(IDB_BITMAP_EDIT);
	m_bmp_Edit.SizeToContent();

	m_bmp_FadeIn.LoadBitmaps(IDB_BITMAP_FADEIN);
	m_bmp_FadeIn.SizeToContent();

	m_bmp_FadeOut.LoadBitmaps(IDB_BITMAP_FADEOUT);
	m_bmp_FadeOut.SizeToContent();

	m_bmp_UVSprite.LoadBitmaps(IDB_BITMAP_UVSPRITE);
	m_bmp_UVSprite.SizeToContent();

	m_bmp_UVAnimation.LoadBitmaps(IDB_BITMAP_UVANIMATION);
	m_bmp_UVAnimation.SizeToContent();

	m_bmp_OptionPos.LoadBitmaps(IDB_BITMAP_POSITION);
	m_bmp_OptionPos.SizeToContent();

	m_bmp_OptionRot.LoadBitmaps(IDB_BITMAP_ROTATION);
	m_bmp_OptionRot.SizeToContent();

	m_bmp_OptionScale.LoadBitmaps(IDB_BITMAP_SCALE);
	m_bmp_OptionScale.SizeToContent();

	m_bmp_OptionFadeIn.LoadBitmaps(IDB_BITMAP_FADEIN);
	m_bmp_OptionFadeIn.SizeToContent();

	m_bmp_OptionFadeOut.LoadBitmaps(IDB_BITMAP_FADEOUT);
	m_bmp_OptionFadeOut.SizeToContent();

	m_bmp_OptionUVSp.LoadBitmaps(IDB_BITMAP_UVSPRITE);
	m_bmp_OptionUVSp.SizeToContent();

	m_bmp_OptionUVAnim.LoadBitmaps(IDB_BITMAP_UVANIMATION);
	m_bmp_OptionUVAnim.SizeToContent();

	m_bmp_Action.LoadBitmaps(IDB_BITMAP_ACTION);
	m_bmp_Action.SizeToContent();

	m_bmp_Loop.LoadBitmaps(IDB_BITMAP_LOOP);
	m_bmp_Loop.SizeToContent();

	m_bmp_Billboard.LoadBitmaps(IDB_BITMAP_BILLBOARD);
	m_bmp_Billboard.SizeToContent();

	// Setting
	m_bmp_PosX.LoadBitmaps(IDB_BITMAP_X);
	m_bmp_PosX.SizeToContent();

	m_bmp_PosY.LoadBitmaps(IDB_BITMAP_Y);
	m_bmp_PosY.SizeToContent();

	m_bmp_PosZ.LoadBitmaps(IDB_BITMAP_Z);
	m_bmp_PosZ.SizeToContent();

	m_bmp_RotX.LoadBitmaps(IDB_BITMAP_X);
	m_bmp_RotX.SizeToContent();

	m_bmp_RotY.LoadBitmaps(IDB_BITMAP_Y);
	m_bmp_RotY.SizeToContent();

	m_bmp_RotZ.LoadBitmaps(IDB_BITMAP_Z);
	m_bmp_RotZ.SizeToContent();

	m_bmp_ScaleX.LoadBitmaps(IDB_BITMAP_X);
	m_bmp_ScaleX.SizeToContent();

	m_bmp_ScaleY.LoadBitmaps(IDB_BITMAP_Y);
	m_bmp_ScaleY.SizeToContent();

	m_bmp_ScaleZ.LoadBitmaps(IDB_BITMAP_Z);
	m_bmp_ScaleZ.SizeToContent();

	m_bmp_AlphaWidth.LoadBitmaps(IDB_BITMAP_MAXINDEXX);
	m_bmp_AlphaWidth.SizeToContent();

	m_bmp_AlphaHeight.LoadBitmaps(IDB_BITMAP_MAXINDEXY);
	m_bmp_AlphaHeight.SizeToContent();

	m_bmp_Speed.LoadBitmaps(IDB_BITMAP_SPEED);
	m_bmp_Speed.SizeToContent();

	m_bmpAnimSpeed.LoadBitmaps(IDB_BITMAP_ANIMSPEED);
	m_bmpAnimSpeed.SizeToContent();

	m_bmpTilingXTitle.LoadBitmaps(IDB_BITMAP_TILING_X);
	m_bmpTilingXTitle.SizeToContent();

	m_bmpTilingYTitle.LoadBitmaps(IDB_BITMAP_TILING_Y);
	m_bmpTilingYTitle.SizeToContent();

	m_bmpTilingX.LoadBitmaps(IDB_BITMAP_X);
	m_bmpTilingX.SizeToContent();

	m_bmpTilingY.LoadBitmaps(IDB_BITMAP_Y);
	m_bmpTilingY.SizeToContent();

	m_bmpIndexX.LoadBitmaps(IDB_BITMAP_X);
	m_bmpIndexX.SizeToContent();

	m_bmpIndexY.LoadBitmaps(IDB_BITMAP_Y);
	m_bmpIndexY.SizeToContent();

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
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CInspector::OnBnClickedDeleteEffectList)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CInspector::OnBnClickedMeshEffect)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CInspector::OnBnClickedSoftEffect)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CInspector::OnBnClickedTexture)
	ON_BN_CLICKED(IDC_MFCBUTTON5, &CInspector::OnBnClickedAlphaMask)
	ON_BN_CLICKED(IDC_MFCBUTTON6, &CInspector::OnBnClickedAnimPlay)
	ON_BN_CLICKED(IDC_MFCBUTTON7, &CInspector::OnBnClickedAnimPause)
	ON_BN_CLICKED(IDC_MFCBUTTON8, &CInspector::OnBnClickedAnimStop)
	ON_BN_CLICKED(IDC_MFCBUTTON9, &CInspector::OnBnClickedSave)
	ON_BN_CLICKED(IDC_MFCBUTTON10, &CInspector::OnBnClickedLoad)
	ON_EN_CHANGE(IDC_EDIT1, &CInspector::OnEnChangeEditPosX)
	ON_EN_CHANGE(IDC_EDIT4, &CInspector::OnEnChangeEditPosY)
	ON_EN_CHANGE(IDC_EDIT7, &CInspector::OnEnChangeEditPosZ)
	ON_EN_CHANGE(IDC_EDIT2, &CInspector::OnEnChangeEditRotX)
	ON_EN_CHANGE(IDC_EDIT5, &CInspector::OnEnChangeEditRotY)
	ON_EN_CHANGE(IDC_EDIT8, &CInspector::OnEnChangeEditRotZ)
	ON_EN_CHANGE(IDC_EDIT3, &CInspector::OnEnChangeEditScaleX)
	ON_EN_CHANGE(IDC_EDIT6, &CInspector::OnEnChangeEditScaleY)
	ON_EN_CHANGE(IDC_EDIT9, &CInspector::OnEnChangeEditScaleZ)
	ON_EN_CHANGE(IDC_EDIT12, &CInspector::OnEnChangeEditStartTime)
	ON_EN_CHANGE(IDC_EDIT13, &CInspector::OnEnChangeEditEndTime)
	ON_EN_CHANGE(IDC_EDIT14, &CInspector::OnEnChangeEditRepeat)
	ON_EN_CHANGE(IDC_EDIT10, &CInspector::OnEnChangeEditAlphaWidth)
	ON_EN_CHANGE(IDC_EDIT11, &CInspector::OnEnChangeEditAlphaHeight)
	ON_WM_TIMER()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CInspector::OnDeltaposSpinPosX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, &CInspector::OnDeltaposSpinPosY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN7, &CInspector::OnDeltaposSpinPosZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CInspector::OnDeltaposSpinScaleX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, &CInspector::OnDeltaposSpinScaleY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN9, &CInspector::OnDeltaposSpinScaleZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN12, &CInspector::OnDeltaposSpinStartTime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN13, &CInspector::OnDeltaposSpinEndTime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN14, &CInspector::OnDeltaposSpinRepeat)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN10, &CInspector::OnDeltaposSpinAlphaWidth)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN11, &CInspector::OnDeltaposSpinAlphaHeight)
	ON_EN_CHANGE(IDC_EDIT15, &CInspector::OnEnChangeEditSpeed)
	ON_EN_CHANGE(IDC_EDIT16, &CInspector::OnEnChangeEditAnimSpeed)
	ON_LBN_SELCHANGE(IDC_LIST1, &CInspector::OnLbnSelchangeEffectList)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN15, &CInspector::OnDeltaposSpinTilingX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN16, &CInspector::OnDeltaposSpinTilingY)
END_MESSAGE_MAP()


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

void CInspector::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_hBitmap = LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_MAIN_BG));
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bitmap);
	EditButtonStyle();
}

void CInspector::OnPaint()
{
		CPaintDC dc(this); // device context for painting
		CRect rect;
		GetWindowRect(&rect);
		HDC hMemDC = CreateCompatibleDC(dc); SetStretchBltMode(hMemDC, HALFTONE);
		SelectObject(hMemDC, m_hBitmap);
		StretchBlt(dc, 0, 0, rect.Width(), rect.Height(), hMemDC, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
		DeleteDC(hMemDC);

}

void CInspector::OnLbnSelchangeEffectList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	_int index = m_EffectListBox.GetCurSel();

	m_iSelectObjectNum = index;

}


void CInspector::OnBnClickedDeleteEffectList()
{
	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];
	spObject->SetDeleteThis(true);
	spObject.reset();

	m_EffectListBox.DeleteString(m_iSelectObjectNum);
	m_btnModeTransform.SetCheck(false);
	m_btnModeEdit.SetCheck(false);
}


void CInspector::OnBnClickedMeshEffect()
{
	CString str = _T("X Files(*.x) |*.x|"); // x ���� ǥ��

	LPWSTR lpwstr = _SOLUTIONDIR L"Resource\\Mesh\\EffectToolScene\\";

	CFileDialog dlg(TRUE, _T("*.x"), NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, str);

	dlg.m_ofn.lpstrInitialDir = lpwstr;

	// IDOK = OK button is pressed in the dialog
	if (dlg.DoModal() == IDOK)
	{
		CString strFilePath = dlg.GetPathName();

		strFilePath = strFilePath.Right(strFilePath.GetLength() - strFilePath.ReverseFind('\\') - 1);

		m_EffectListBox.AddString(strFilePath);

		Add_MeshEffect(strFilePath);

		InvalidateRect(false);

	}
}


void CInspector::OnBnClickedSoftEffect()
{
	CString str = _T("png Files(*.png) |*.png|"); // png ���� ǥ��
	LPWSTR lpwstr = _SOLUTIONDIR L"Resource\\Texture\\EffectToolScene\\Effect\\SoftEffect\\";
	CFileDialog dlg(TRUE, _T("*.png"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	dlg.m_ofn.lpstrInitialDir = lpwstr;

	if (dlg.DoModal() == IDOK)
	{

		CString strFilePath = dlg.GetPathName();

		strFilePath = strFilePath.Right(strFilePath.GetLength() - strFilePath.ReverseFind('\\') - 1);

		m_EffectListBox.AddString(strFilePath);

		Add_SoftEffect(strFilePath);

		InvalidateRect(false);
	}
}

void CInspector::OnBnClickedTexture()
{
	CString str = _T("png Files(*.png) |*.png|"); // png ���� ǥ��
	LPWSTR lpwstr = _SOLUTIONDIR L"Resource\\Texture\\EffectToolScene\\Effect\\";

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
	CString str = _T("png Files(*.png) |*.png|"); // png ���� ǥ��
	LPWSTR lpwstr = _SOLUTIONDIR L"Resource\\Texture\\EffectToolScene\\Effect\\";

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
	if (ObjectName == L"KianaTest.X")
	{
		SP(Engine::CObject) spMeshEffect
			= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"AttackRange_Editor", false, (_int)Engine::ELayerID::Effect, L"MeshEffect0");
		spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(Engine::RemoveExtension(ObjectName.operator LPCWSTR()));
		spMeshEffect->GetComponent<Engine::CMeshC>()->SetisEffectMesh(true);
		spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"DefaultMeshTex");
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"DefaultMeshTex", 1);
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"DefaultMeshTex", 2);
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"DefaultMeshTex", 3);
		spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::AttackRangeShader);
	}
	else
	{
		SP(Engine::CObject) spMeshEffect
			= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"AttackTrail", false, (_int)Engine::ELayerID::Effect, L"MeshEffect0");
		spMeshEffect->GetComponent<Engine::CMeshC>()->SetMeshData(Engine::RemoveExtension(ObjectName.operator LPCWSTR()));
		spMeshEffect->GetComponent<Engine::CMeshC>()->SetisEffectMesh(true);
		spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"DefaultMeshTex");
		spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"DefaultMeshTex");
		spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::MeshTrailShader);
	}

}

void CInspector::Add_SoftEffect(CString ObjectName)
{
	SP(Engine::CObject) spSoftEffect
		= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"SoftEffect", false);
	spSoftEffect->GetComponent<Engine::CGraphicsC>();
	spSoftEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"DefaultMeshTex");
	spSoftEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
}

void CInspector::Add_Texture(CString TextureKey)
{
	if (m_iSelectObjectNum > -1)
	{
		SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

		if (spObject != nullptr)
		{
			SP(Engine::CTextureC) spTexture = spObject->GetComponent<Engine::CTextureC>();

			spTexture->ChangeTexture(Engine::RemoveExtension(TextureKey.operator LPCWSTR()), 0, 0);
		}
	}
}

void CInspector::Add_AlphaMask(CString TextureKey)
{
	if (m_iSelectObjectNum > -1)
	{
		SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

		if (spObject != nullptr)
		{
			SP(Engine::CTextureC) spTexture = spObject->GetComponent<Engine::CTextureC>();

			spTexture->ChangeTexture(Engine::RemoveExtension(TextureKey.operator LPCWSTR()), 0, 1);
		}
	}
}

void CInspector::FunctionUpdate()
{
	
	//if (m_iSelectObjectNum > -1)
	//{
	//	SP(Engine::CObject) spObject2 = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[0];
	//	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	//	if (Engine::IMKEY_PRESS(KEY_UP))
	//	{
	//		spObject2->GetComponent<Engine::CTransformC>()->AddRotationY(D3DXToRadian(1.f));
	//	}
	//	if (Engine::IMKEY_PRESS(KEY_DOWN))
	//	{
	//		spObject2->GetComponent<Engine::CTransformC>()->AddRotationY(D3DXToRadian(-1.f));
	//	}


	//	if (m_btnTestButton.GetCheck())
	//	{
	//		if (spObject == nullptr)
	//		{
	//			MessageBox(L"spObject is Not Found / CInspector", NULL);
	//			ABORT;
	//		}

	//		spObject->GetComponent<Engine::CTransformC>()->SetRotationY(spObject2->GetComponent<Engine::CTransformC>()->GetRotation().y);
	//		/*_mat rot;
	//		D3DXMatrixRotationAxis(&rot, &UP_VECTOR, spObject2->GetComponent<Engine::CTransformC>()->GetRotation().y);
	//		_float3 newForward;
	//		D3DXVec3TransformNormal(&newForward, &spObject->GetTransform()->GetForward(), &rot);
	//		spObject->GetTransform()->SetForward(newForward);*/

	//		CString str;
	//		_float fY = spObject->GetComponent<Engine::CTransformC>()->GetRotation().y;
	//		str.Format(L"%f", fY);
	//		m_edRotY.SetWindowTextW(str.GetString());

	//		m_vSaveRot.x = fY;
	//	}
	//}
	
}

void CInspector::OptionUpdate()
{
	if(m_iSelectObjectNum < 0)
	{
		m_btnOptionPos.EnableWindow(false);
		m_btnOptionRot.EnableWindow(false);
		m_btnOptionScale.EnableWindow(false);
		m_btnOptionFadeIn.EnableWindow(false);
		m_btnOptionFadeOut.EnableWindow(false);
		m_btnOptionUVSprite.EnableWindow(false);
		m_btnOptionUVAnim.EnableWindow(false);

	}
	else
	{
		m_btnOptionPos.EnableWindow(true);
		m_btnOptionRot.EnableWindow(true);
		m_btnOptionScale.EnableWindow(true);
		m_btnOptionFadeIn.EnableWindow(true);
		m_btnOptionFadeOut.EnableWindow(true);
		m_btnOptionUVSprite.EnableWindow(true);
		m_btnOptionUVAnim.EnableWindow(true);
	}



}

void CInspector::ModeUpdate()
{
	if (m_btnOptionPos.GetCheck())
	{
		m_btnModePosition.EnableWindow(true);
	}
	else
	{
		m_btnModePosition.SetCheck(false);
		m_btnModePosition.EnableWindow(false);
	}

	if (m_btnOptionRot.GetCheck())
	{
		m_btnModeRotation.EnableWindow(true);
	}
	else
	{
		m_btnModeRotation.SetCheck(false);
		m_btnModeRotation.EnableWindow(false);
	}

	if (m_btnOptionScale.GetCheck())
	{
		m_btnModeScale.EnableWindow(true);
	}
	else
	{
		m_btnModeScale.SetCheck(false);
		m_btnModeScale.EnableWindow(false);
	}

	if (m_btnOptionFadeIn.GetCheck())
	{
		m_btnModeFadeIn.EnableWindow(true);
	}
	else
	{
		m_btnModeFadeIn.SetCheck(false);
		m_btnModeFadeIn.EnableWindow(false);
	}

	if (m_btnOptionFadeOut.GetCheck())
	{
		m_btnModeFadeOut.EnableWindow(true);
	}
	else
	{
		m_btnModeFadeOut.SetCheck(false);
		m_btnModeFadeOut.EnableWindow(false);
	}

	if (m_btnOptionUVSprite.GetCheck())
	{
		m_btnModeUVSprite.EnableWindow(true);
	}
	else
	{
		m_btnModeUVSprite.SetCheck(false);
		m_btnModeUVSprite.EnableWindow(false);
	}

	if (m_btnOptionUVAnim.GetCheck())
	{
		m_btnModeUVAnim.EnableWindow(true);
	}
	else
	{
		m_btnModeUVAnim.SetCheck(false);
		m_btnModeUVAnim.EnableWindow(false);
	}
	if (m_iSelectObjectNum < 0)
	{
		m_btnModeTransform.EnableWindow(false);
		m_btnModeEdit.EnableWindow(false);
	}
	else
	{
		m_btnModeTransform.EnableWindow(true);
		m_btnModeEdit.EnableWindow(true);
	}
	if (m_btnOptionUVSprite.GetCheck())
	{
		m_btnModeUVSprite.EnableWindow(true);
	}
	else
	{
		m_btnModeUVSprite.EnableWindow(false);
	}
}

void CInspector::SettingUpdate()
{
#pragma region Setting
	if (m_btnModePosition.GetCheck())
	{
		m_edPosX.ShowWindow(true);
		m_spinPosX.ShowWindow(true);

		m_edPosY.ShowWindow(true);
		m_spinPosY.ShowWindow(true);

		m_edPosZ.ShowWindow(true);
		m_spinPosZ.ShowWindow(true);

		m_edRotX.ShowWindow(false);
		m_edRotY.ShowWindow(false);
		m_edRotZ.ShowWindow(false);

		m_edScaleX.ShowWindow(false);
		m_spinScaleX.ShowWindow(false);

		m_edScaleY.ShowWindow(false);
		m_spinScaleY.ShowWindow(false);

		m_edScaleZ.ShowWindow(false);
		m_spinScaleZ.ShowWindow(false);
	}
	else if (m_btnModeRotation.GetCheck())
	{
		m_edPosX.ShowWindow(false);
		m_spinPosX.ShowWindow(false);

		m_edPosY.ShowWindow(false);
		m_spinPosY.ShowWindow(false);

		m_edPosZ.ShowWindow(false);
		m_spinPosZ.ShowWindow(false);

		m_edRotX.ShowWindow(true);
		m_edRotY.ShowWindow(true);
		m_edRotZ.ShowWindow(true);

		m_edScaleX.ShowWindow(false);
		m_spinScaleX.ShowWindow(false);

		m_edScaleY.ShowWindow(false);
		m_spinScaleY.ShowWindow(false);

		m_edScaleZ.ShowWindow(false);
		m_spinScaleZ.ShowWindow(false);
	}
	else if (m_btnModeScale.GetCheck())
	{
		m_edPosX.ShowWindow(false);
		m_spinPosX.ShowWindow(false);

		m_edPosY.ShowWindow(false);
		m_spinPosY.ShowWindow(false);

		m_edPosZ.ShowWindow(false);
		m_spinPosZ.ShowWindow(false);

		m_edRotX.ShowWindow(false);
		m_edRotY.ShowWindow(false);
		m_edRotZ.ShowWindow(false);

		m_edScaleX.ShowWindow(true);
		m_spinScaleX.ShowWindow(true);

		m_edScaleY.ShowWindow(true);
		m_spinScaleY.ShowWindow(true);

		m_edScaleZ.ShowWindow(true);
		m_spinScaleZ.ShowWindow(true);
	}
	else if (m_btnModeTransform.GetCheck() || m_btnModeEdit.GetCheck())
	{
		m_edPosX.ShowWindow(true);
		m_spinPosX.ShowWindow(true);

		m_edPosY.ShowWindow(true);
		m_spinPosY.ShowWindow(true);

		m_edPosZ.ShowWindow(true);
		m_spinPosZ.ShowWindow(true);

		m_edRotX.ShowWindow(true);
		m_edRotY.ShowWindow(true);
		m_edRotZ.ShowWindow(true);

		m_edScaleX.ShowWindow(true);
		m_spinScaleX.ShowWindow(true);

		m_edScaleY.ShowWindow(true);
		m_spinScaleY.ShowWindow(true);

		m_edScaleZ.ShowWindow(true);
		m_spinScaleZ.ShowWindow(true);
	}
	else
	{
		m_edPosX.ShowWindow(false);
		m_spinPosX.ShowWindow(false);

		m_edPosY.ShowWindow(false);
		m_spinPosY.ShowWindow(false);

		m_edPosZ.ShowWindow(false);
		m_spinPosZ.ShowWindow(false);

		m_edRotX.ShowWindow(false);
		m_edRotY.ShowWindow(false);
		m_edRotZ.ShowWindow(false);

		m_edScaleX.ShowWindow(false);
		m_spinScaleX.ShowWindow(false);

		m_edScaleY.ShowWindow(false);
		m_spinScaleY.ShowWindow(false);

		m_edScaleZ.ShowWindow(false);
		m_spinScaleZ.ShowWindow(false);
	}

	if (m_btnModeUVSprite.GetCheck())
	{
		m_edAlphaWidth.ShowWindow(true);
		m_spinAlphaWidth.ShowWindow(true);
		m_edAlphaHeight.ShowWindow(true);
		m_spinAlphaHeigth.ShowWindow(true);
	}
	else
	{
		m_edAlphaWidth.ShowWindow(false);
		m_spinAlphaWidth.ShowWindow(false);
		m_edAlphaHeight.ShowWindow(false);
		m_spinAlphaHeigth.ShowWindow(false);
	}

	if (m_btnModeUVSprite.GetCheck())
	{
		m_edTilingX.ShowWindow(true);
		m_edTilingY.ShowWindow(true);
		m_spinTilingX.ShowWindow(true);
		m_spinTilingY.ShowWindow(true);
	}
	else
	{
		m_edTilingX.ShowWindow(false);
		m_edTilingY.ShowWindow(false);
		m_spinTilingX.ShowWindow(false);
		m_spinTilingY.ShowWindow(false);
	}
#pragma endregion

}

void CInspector::ActionUpdate()
{
	if (m_eActionState == STATE_END)
		return;

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	switch (m_eActionState)
	{
	case CInspector::PLAY:
		if (m_iRepeatCnt < m_iRepeat || m_btnLoop.GetCheck())
		{
			if (!m_isPlayAnim)
			{
				m_isPlayAnim = true;
			}
			m_fStartTime += GET_DT;

			AnimTransformUpdate(spObject);

			if (m_fStartTime >= m_fEndTime)
			{
				spObject->GetComponent<Engine::CTransformC>()->SetPosition(_float3(0.f, 0.f, 2.f));
				spObject->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0.f, 0.f, 0.f));
				spObject->GetComponent<Engine::CTransformC>()->SetSize(m_vSaveScale);
				m_fStartTime = 0.f;
				m_isPlayAnim = false;
				m_iRepeatCnt++;
			}
		}
		else if (m_iRepeatCnt >= m_iRepeat)
		{
			m_eActionState = STOP;
		}
		break;
	case CInspector::PAUSE:
		break;
	case CInspector::STOP:
		if (spObject == nullptr)
		{
			return;
		}
		if (m_isPlayAnim)
		{
			spObject->GetComponent<Engine::CTransformC>()->SetPosition(_float3(0.f, 0.f, 2.f));
			spObject->GetComponent<Engine::CTransformC>()->SetRotation(_float3(0.f, 0.f, 0.f));
			spObject->GetComponent<Engine::CTransformC>()->SetSize(m_vSaveScale);
		}
		m_fStartTime = 0.f;
		m_iRepeatCnt = 0;
		m_isPlayAnim = false;
		break;
	default:
		break;
	}
}

void CInspector::AnimTransformUpdate(SP(Engine::CObject) spObject)
{
	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}

	if (spObject->GetComponent<Engine::CTransformC>()->GetPosition().x <= m_vSavePos.x)
	{
		spObject->GetComponent<Engine::CTransformC>()->AddPositionX(m_fAnimSpeed * GET_DT);
	}
	if (spObject->GetComponent<Engine::CTransformC>()->GetPosition().y <= m_vSavePos.y)
	{
		spObject->GetComponent<Engine::CTransformC>()->AddPositionY(m_fAnimSpeed * GET_DT);
	}
	if (spObject->GetComponent<Engine::CTransformC>()->GetPosition().z <= m_vSavePos.z)
	{
		spObject->GetComponent<Engine::CTransformC>()->AddPositionZ(m_fAnimSpeed * GET_DT);
	}
	if (spObject->GetComponent<Engine::CTransformC>()->GetRotation().x <= m_vSaveRot.x)
	{
		spObject->GetComponent<Engine::CTransformC>()->AddRotationX(m_fAnimSpeed * GET_DT);
	}
	if (spObject->GetComponent<Engine::CTransformC>()->GetRotation().y <= m_vSaveRot.y)
	{
		spObject->GetComponent<Engine::CTransformC>()->AddRotationY(m_fAnimSpeed * GET_DT);
	}
	if (spObject->GetComponent<Engine::CTransformC>()->GetRotation().z <= m_vSaveRot.z)
	{
		spObject->GetComponent<Engine::CTransformC>()->AddRotationZ(m_fAnimSpeed * GET_DT);
	}
	if (spObject->GetComponent<Engine::CTransformC>()->GetSize().x <= m_vSaveScale.x)
	{
		spObject->GetComponent<Engine::CTransformC>()->AddSizeX(m_fAnimSpeed * GET_DT);
	}
	if (spObject->GetComponent<Engine::CTransformC>()->GetSize().y <= m_vSaveScale.y)
	{
		spObject->GetComponent<Engine::CTransformC>()->AddSizeY(m_fAnimSpeed * GET_DT);
	}
	if (spObject->GetComponent<Engine::CTransformC>()->GetSize().z <= m_vSaveScale.z)
	{
		spObject->GetComponent<Engine::CTransformC>()->AddSizeZ(m_fAnimSpeed * GET_DT);
	}
}

void CInspector::OnBnClickedAnimPlay()
{
	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	m_eActionState = PLAY;
	SP(CSoftEffect) pSoftEffect = std::dynamic_pointer_cast<CSoftEffect>(spObject);

	if(pSoftEffect != nullptr)
		pSoftEffect->SetAnimisPlay(ACTION_STATE::PLAY);
}

void CInspector::OnBnClickedAnimPause()
{
	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
		return;

	m_eActionState = PAUSE;
	SP(CSoftEffect) pSoftEffect = std::dynamic_pointer_cast<CSoftEffect>(spObject);

	if(pSoftEffect != nullptr)
		pSoftEffect->SetAnimisPlay(ACTION_STATE::PAUSE);

}

void CInspector::OnBnClickedAnimStop()
{
	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
		return;

	m_eActionState = STOP;
	SP(CSoftEffect) pSoftEffect = std::dynamic_pointer_cast<CSoftEffect>(spObject);

	if (pSoftEffect != nullptr)
	{
		pSoftEffect->SetTilingX(0);
		pSoftEffect->SetTilingY(0);
	}
}

void CInspector::OnBnClickedSave()
{
	// Mesh Effect or Soft Effect Save
	// Soft Effect					Mesh Effect
	// name							name
	// Texture						Texture
	// Tiling						Shader
	// MaxIndex						Animation

	CString str = _T("txt Files(*.txt) |*.txt|"); // png ���� ǥ��
	LPWSTR lpwstr = _SOLUTIONDIR L"Data\\";

	CFileDialog dlg(TRUE, _T("*.txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	dlg.m_ofn.lpstrInitialDir = lpwstr;

	if (dlg.DoModal() == IDOK)
	{
		std::wstring filePath = _SOLUTIONDIR L"Data\\Save.txt";
		std::wofstream ofsSave(filePath.data());

		if (ofsSave.is_open())
		{
			if (m_EffectListBox.GetCount() > 0)
			{
				for (_int i = 0; i < m_EffectListBox.GetCount(); ++i)
				{
					SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[i];
					SP(Engine::CTextureC) spTexture = spObject->GetComponent<Engine::CTextureC>();

					//Name
					//ofsSave << spObject->
					//std::wstring str = m_EffectListBox.FindString(i, );

					//Texture
					/*D3DMATERIAL9* pMtrl = &spObject->GetComponent<Engine::CGraphicsC>()->m_mtrl;

					size_t _dwMaterials = spObject->GetComponent<Engine::CGraphicsC>()->GetMesh()->GetMeshDatas().size();

					for (_uint j = 0; j < spTexture->GetTexIndex(); ++j)
					{
						ofsSave << spTexture->GetTexData()[spTexture->GetMeshIndex()][i]->pTexture;
					}
*/
					//Transoform
					ofsSave << spObject->GetComponent<Engine::CTransformC>()->GetPosition().x;
					ofsSave << spObject->GetComponent<Engine::CTransformC>()->GetPosition().y;
					ofsSave << spObject->GetComponent<Engine::CTransformC>()->GetPosition().z;
					ofsSave << spObject->GetComponent<Engine::CTransformC>()->GetRotation().x;
					ofsSave << spObject->GetComponent<Engine::CTransformC>()->GetRotation().y;
					ofsSave << spObject->GetComponent<Engine::CTransformC>()->GetRotation().z;
					ofsSave << spObject->GetComponent<Engine::CTransformC>()->GetSize().x;
					ofsSave << spObject->GetComponent<Engine::CTransformC>()->GetSize().y;
					ofsSave << spObject->GetComponent<Engine::CTransformC>()->GetSize().z;


				}
			}
		}



		//SaveData();
		InvalidateRect(false);
	}


}

void CInspector::OnBnClickedLoad()
{
	// Mesh Effect or Soft Effect Load



}

void CInspector::OnEnChangeEditPosX()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT1, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());


	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}

	spObject->GetComponent<Engine::CTransformC>()->SetPositionX(fResizeValue);
	m_vSavePos.x = fResizeValue;

}


void CInspector::OnEnChangeEditPosY()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT4, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());


	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}

	spObject->GetComponent<Engine::CTransformC>()->SetPositionY(fResizeValue);
	m_vSavePos.y = fResizeValue;

}


void CInspector::OnEnChangeEditPosZ()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT7, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}

	spObject->GetComponent<Engine::CTransformC>()->SetPositionZ(fResizeValue);
	m_vSavePos.z = fResizeValue;

}


void CInspector::OnEnChangeEditRotX()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT2, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}

	spObject->GetComponent<Engine::CTransformC>()->SetRotationX(D3DXToRadian(fResizeValue));
	m_vSaveRot.x = D3DXToRadian(fResizeValue);

}


void CInspector::OnEnChangeEditRotY()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT5, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}

	spObject->GetComponent<Engine::CTransformC>()->SetRotationY(fResizeValue);
	m_vSaveRot.y = fResizeValue;

}


void CInspector::OnEnChangeEditRotZ()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT8, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}

	spObject->GetComponent<Engine::CTransformC>()->SetRotationZ(D3DXToRadian(fResizeValue));
	m_vSaveRot.z = D3DXToRadian(fResizeValue);

}


void CInspector::OnEnChangeEditScaleX()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT3, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}

	spObject->GetComponent<Engine::CTransformC>()->SetSizeX(fResizeValue);
	m_vSaveScale.x = fResizeValue;
}


void CInspector::OnEnChangeEditScaleY()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT6, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}

	spObject->GetComponent<Engine::CTransformC>()->SetSizeY(fResizeValue);
	m_vSaveScale.y = fResizeValue;
}


void CInspector::OnEnChangeEditScaleZ()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT9, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}

	spObject->GetComponent<Engine::CTransformC>()->SetSizeZ(fResizeValue);
	m_vSaveScale.z = fResizeValue;
}


void CInspector::OnEnChangeEditStartTime()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT12, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());

	m_fStartTime = fResizeValue;
}


void CInspector::OnEnChangeEditEndTime()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT13, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());

	m_fEndTime = fResizeValue;
}


void CInspector::OnEnChangeEditRepeat()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT14, _strValue);
	_int iResizeValue = 0;
	iResizeValue = (_int)_wtoi(_strValue.GetString());

	m_iRepeat = iResizeValue;
}


void CInspector::OnEnChangeEditAlphaWidth()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT10, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());

	m_fAlphaWidth = fResizeValue;
}


void CInspector::OnEnChangeEditAlphaHeight()
{
	CString _strValue;
	GetDlgItemText(IDC_EDIT11, _strValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(_strValue.GetString());

	m_fAlphaHeight = fResizeValue;
}

void CInspector::OnDeltaposSpinPosX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);


	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}
	spObject->GetComponent<Engine::CTransformC>()->AddPositionX(pNMUpDown->iDelta * -m_fSpeed);

	UpdateData(true);
	CString str;
	_float fX = spObject->GetComponent<Engine::CTransformC>()->GetPosition().x;
	str.Format(L"%f", fX);
	m_edPosX.SetWindowTextW(str.GetString());

	m_vSavePos.x = fX;
	UpdateData(false);

	*pResult = 0;
}


void CInspector::OnDeltaposSpinPosY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}
	spObject->GetComponent<Engine::CTransformC>()->AddPositionY(pNMUpDown->iDelta * -m_fSpeed);

	UpdateData(true);
	CString str;
	_float fY = spObject->GetComponent<Engine::CTransformC>()->GetPosition().y;
	str.Format(L"%f", fY);
	m_edPosY.SetWindowTextW(str.GetString());

	m_vSavePos.y = fY;
	UpdateData(false);

	*pResult = 0;
}


void CInspector::OnDeltaposSpinPosZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}
	spObject->GetComponent<Engine::CTransformC>()->AddPositionZ(pNMUpDown->iDelta * -m_fSpeed);

	UpdateData(true);
	CString str;
	_float fZ = spObject->GetComponent<Engine::CTransformC>()->GetPosition().z;
	str.Format(L"%f", fZ);
	m_edPosZ.SetWindowTextW(str.GetString());

	m_vSavePos.z = fZ;
	UpdateData(false);

	*pResult = 0;
}

void CInspector::OnDeltaposSpinScaleX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}
	spObject->GetComponent<Engine::CTransformC>()->AddSizeX(pNMUpDown->iDelta * -m_fSpeed);

	UpdateData(true);
	CString str;
	_float fX = spObject->GetComponent<Engine::CTransformC>()->GetSize().x;
	str.Format(L"%f", fX);
	m_edScaleX.SetWindowTextW(str.GetString());

	m_vSaveScale.x = fX;
	UpdateData(false);

	*pResult = 0;
}


void CInspector::OnDeltaposSpinScaleY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}
	spObject->GetComponent<Engine::CTransformC>()->AddSizeY(pNMUpDown->iDelta * -m_fSpeed);

	UpdateData(true);
	CString str;
	_float fY = spObject->GetComponent<Engine::CTransformC>()->GetSize().y;
	str.Format(L"%f", fY);
	m_edScaleY.SetWindowTextW(str.GetString());

	m_vSaveScale.y = fY;
	UpdateData(false);

	*pResult = 0;
}


void CInspector::OnDeltaposSpinScaleZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
	{
		MessageBox(L"spObject is Not Found / CInspector", NULL);
		ABORT;
	}
	spObject->GetComponent<Engine::CTransformC>()->AddSizeZ(pNMUpDown->iDelta * -m_fSpeed);

	UpdateData(true);
	CString str;
	_float fZ = spObject->GetComponent<Engine::CTransformC>()->GetSize().z;
	str.Format(L"%f", fZ);
	m_edScaleZ.SetWindowTextW(str.GetString());

	m_vSaveScale.z = fZ;

	UpdateData(false);

	*pResult = 0;
}


void CInspector::OnDeltaposSpinStartTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	*pResult = 0;
}


void CInspector::OnDeltaposSpinEndTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	*pResult = 0;
}


void CInspector::OnDeltaposSpinRepeat(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	*pResult = 0;
}


void CInspector::OnDeltaposSpinAlphaWidth(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	m_fAlphaWidth += pNMUpDown->iDelta * -1.f;

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
		return;

	SP(CSoftEffect) pSoftEffect = std::dynamic_pointer_cast<CSoftEffect>(spObject);
	pSoftEffect->SetAlphaWIdth(m_fAlphaWidth);

	UpdateData(true);

	CString str;
	str.Format(L"%f", m_fAlphaWidth);
	m_edAlphaWidth.SetWindowTextW(str.GetString());

	UpdateData(false);

	*pResult = 0;
}


void CInspector::OnDeltaposSpinAlphaHeight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	m_fAlphaHeight += pNMUpDown->iDelta * -1.f;

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
		return;

	SP(CSoftEffect) pSoftEffect = std::dynamic_pointer_cast<CSoftEffect>(spObject);
	pSoftEffect->SetAlphaHeight(m_fAlphaHeight);

	UpdateData(true);
	CString str;
	str.Format(L"%f", m_fAlphaHeight);
	m_edAlphaHeight.SetWindowTextW(str.GetString());

	UpdateData(false);

	*pResult = 0;
}

void CInspector::OnEnChangeEditSpeed()
{
	CString strResizeValue;
	GetDlgItemText(IDC_EDIT15, strResizeValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(strResizeValue.GetString());

	m_fSpeed = fResizeValue;
}

void CInspector::OnEnChangeEditAnimSpeed()
{
	CString strResizeValue;
	GetDlgItemText(IDC_EDIT16, strResizeValue);
	_float fResizeValue = 0.f;
	fResizeValue = (_float)_wtof(strResizeValue.GetString());

	m_fAnimSpeed = fResizeValue;
}

void CInspector::OnDeltaposSpinTilingX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	m_iTilingX += pNMUpDown->iDelta * -1;

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
		return;

	SP(CSoftEffect) pSoftEffect = std::dynamic_pointer_cast<CSoftEffect>(spObject);
	pSoftEffect->SetmaxXIndex(m_iTilingX);

	UpdateData(true);

	CString str;
	str.Format(L"%d", m_iTilingX);
	m_edTilingX.SetWindowTextW(str.GetString());

	UpdateData(false);
	*pResult = 0;
}


void CInspector::OnDeltaposSpinTilingY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	m_iTilingY += pNMUpDown->iDelta * -1;

	SP(Engine::CObject) spObject = Engine::GET_CUR_SCENE->GetLayers()[(_int)Engine::ELayerID::Effect]->GetGameObjects()[m_iSelectObjectNum];

	if (spObject == nullptr)
		return;

	SP(CSoftEffect) pSoftEffect = std::dynamic_pointer_cast<CSoftEffect>(spObject);
	pSoftEffect->SetmaxYIndex(m_iTilingY);

	UpdateData(true);

	CString str;
	str.Format(L"%d", m_iTilingY);
	m_edTilingY.SetWindowTextW(str.GetString());

	UpdateData(false);
	*pResult = 0;
}

void CInspector::SaveData(std::wstring Objectkey, SP(Engine::CObject) spObject)
{
}

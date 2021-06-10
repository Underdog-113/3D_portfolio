// ../Code/Inspector.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EffectTool.h"
#include "../Header/Inspector.h"


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
END_MESSAGE_MAP()


// CInspector 진단입니다.

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


// CInspector 메시지 처리기입니다.

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
						   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
						   // 그리기 메시지에 대해서는 CFormView::OnPaint()을(를) 호출하지 마십시오.

		CRect rect;
		GetWindowRect(&rect); // 스크린과 호환되는 DC생성. 
		HDC hMemDC = CreateCompatibleDC(dc); SetStretchBltMode(hMemDC, HALFTONE); // 호환DC에 비트맵을 선정.
		SelectObject(hMemDC, m_hBitmap); // 메모리 DC에서 스크린 DC로 이미지 복사 
		StretchBlt(dc, 0, 0, rect.Width(), rect.Height(), hMemDC, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
		// 메모리 DC삭제
		DeleteDC(hMemDC);

}

void CInspector::OnTvnSelchangedEffectList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;
}


void CInspector::OnBnClickedDeleteEffectList()
{

}


void CInspector::OnBnClickedMeshEffect()
{
	CString str = _T("X Files(*.x) |*.x|"); // x 파일 표시
	
	CFileDialog dlg(TRUE, _T("*.x"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strFilePath = dlg.GetPathName();

		strFilePath = strFilePath.Right(strFilePath.GetLength() - strFilePath.ReverseFind('\\') - 1);

		m_hMeshEffectItem = m_TreeCtrl.InsertItem(strFilePath, 1, 1, m_hEffect, TVI_LAST);

		InvalidateRect(false);

	}
}


void CInspector::OnBnClickedSoftEffect()
{
	CString str = _T("png Files(*.png) |*.png|"); // png 파일 표시

	CFileDialog dlg(TRUE, _T("*.png"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{

		CString strFilePath = dlg.GetPathName();

		strFilePath = strFilePath.Right(strFilePath.GetLength() - strFilePath.ReverseFind('\\') - 1);

		m_hSoftEffectItem = m_TreeCtrl.InsertItem(strFilePath, 1, 1, m_hEffect, TVI_LAST);
		
		InvalidateRect(false);
	}
}


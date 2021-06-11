#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "afxcmn.h"



// CInspector 폼 뷰입니다.

class CInspector : public CFormView
{
	DECLARE_DYNCREATE(CInspector)

protected:
	CInspector();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CInspector();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSPECTOR };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	void EditButtonStyle();

private:
	HBITMAP m_hBitmap;
	BITMAP  m_bitmap;
	HTREEITEM m_hSoftEffectItem;
	HTREEITEM m_hMeshEffectItem;
	HTREEITEM m_hEffect;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
#pragma region EditButtonName
	CBitmapButton m_btnEffectList;
	CBitmapButton m_btnEffectType;
	CBitmapButton m_btnTextureType;
	CBitmapButton m_btnFunction;
	CBitmapButton m_btnEffectSetting;
	CBitmapButton m_btn_SelectMode;
	CBitmapButton m_btnOption;
	CBitmapButton m_btn_Position;
	CBitmapButton m_btn_Rotation;
	CBitmapButton m_btn_Scale;
	CBitmapButton m_btnStartTime;
	CBitmapButton m_btnEndTime;
	CBitmapButton m_btn_Repeat;
	CBitmapButton m_btnLoop;
	CBitmapButton m_btnBillboard;

	// Mode
	CBitmapButton m_btnModePos;
	CBitmapButton m_btnModeRot;
	CBitmapButton m_btnModeScale;
	CBitmapButton m_btnTransform;
	CBitmapButton m_btnEdit;
	CBitmapButton m_btnFadeIn;
	CBitmapButton m_btnFadeOut;
	CBitmapButton m_btnUVSprite;
	CBitmapButton m_btnUVAnimation;

	// Option
	CBitmapButton m_btnOptionPos;
	CBitmapButton m_btnOptionRot;
	CBitmapButton m_btnOptionScale;
	CBitmapButton m_btnOptionFadeIn;
	CBitmapButton m_btnOptionFadeOut;
	CBitmapButton m_btnOptionUVSp;
	CBitmapButton m_btnOptionUVAnim;
	CBitmapButton m_btnAction;

	// Setting
	CBitmapButton m_btnPosX;
	CBitmapButton m_btnPosY;
	CBitmapButton m_btnPosZ;
	CBitmapButton m_btnRotX;
	CBitmapButton m_btnRotY;
	CBitmapButton m_btnRotZ;
	CBitmapButton m_btnScaleX;
	CBitmapButton m_btnScaleY;
	CBitmapButton m_btnScaleZ;
	CBitmapButton m_btnAlphaWidth;
	CBitmapButton m_btnAlphaHeight;
#pragma endregion

#pragma region EventButtonName

	CMFCButton m_btnStart;
	CMFCButton m_btnPause;
	CMFCButton m_btnStop;
	CMFCButton m_btnSave;
	CMFCButton m_btnLoad;
	CMFCButton m_btnTexture;
	CMFCButton m_btnAlphaMask;
	CMFCButton m_btnSoftEffect;
	CMFCButton m_btnMeshEffect;
	CMFCButton m_btnListDelete;

#pragma endregion
	CTreeCtrl m_TreeCtrl;
	
	afx_msg void OnTvnSelchangedEffectList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDeleteEffectList();
	afx_msg void OnBnClickedMeshEffect();
	afx_msg void OnBnClickedSoftEffect();
	afx_msg void OnBnClickedTexture();
	afx_msg void OnBnClickedAlphaMask();

private:
	void Add_MeshEffect(CString ObjectName);
	void Add_SoftEffect(CString ObjectName);
	void Add_Texture(CString TextureKey);
	void Add_AlphaMask(CString TextureKey);

private:
	CString InitFilePath(CString _filePath);

};



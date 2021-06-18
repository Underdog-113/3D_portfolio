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
public:
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();

#pragma region EditButtonName
	CBitmapButton m_bmp_EffectList;
	CBitmapButton m_bmp_EffectType;
	CBitmapButton m_bmp_TextureType;
	CBitmapButton m_bmp_Function;
	CBitmapButton m_bmp_EffectSetting;
	CBitmapButton m_bmp_SelectMode;
	CBitmapButton m_bmp_Option;
	CBitmapButton m_bmp_Position;
	CBitmapButton m_bmp_Rotation;
	CBitmapButton m_bmp_Scale;
	CBitmapButton m_bmp_StartTime;
	CBitmapButton m_bmp_EndTime;
	CBitmapButton m_bmp_Repeat;
	CBitmapButton m_bmp_Loop;
	CBitmapButton m_bmp_Billboard;

	// Mode
	CBitmapButton m_bmp_ModePos;
	CBitmapButton m_bmp_ModeRot;
	CBitmapButton m_bmp_ModeScale;
	CBitmapButton m_bmp_Transform;
	CBitmapButton m_bmp_Edit;
	CBitmapButton m_bmp_FadeIn;
	CBitmapButton m_bmp_FadeOut;
	CBitmapButton m_bmp_UVSprite;
	CBitmapButton m_bmp_UVAnimation;

	// Option
	CBitmapButton m_bmp_OptionPos;
	CBitmapButton m_bmp_OptionRot;
	CBitmapButton m_bmp_OptionScale;
	CBitmapButton m_bmp_OptionFadeIn;
	CBitmapButton m_bmp_OptionFadeOut;
	CBitmapButton m_bmp_OptionUVSp;
	CBitmapButton m_bmp_OptionUVAnim;
	CBitmapButton m_bmp_Action;

	// Setting
	CBitmapButton m_bmp_PosX;
	CBitmapButton m_bmp_PosY;
	CBitmapButton m_bmp_PosZ;
	CBitmapButton m_bmp_RotX;
	CBitmapButton m_bmp_RotY;
	CBitmapButton m_bmp_RotZ;
	CBitmapButton m_bmp_ScaleX;
	CBitmapButton m_bmp_ScaleY;
	CBitmapButton m_bmp_ScaleZ;
	CBitmapButton m_bmp_AlphaWidth;
	CBitmapButton m_bmp_AlphaHeight;
	CBitmapButton m_bmp_Speed;
	CBitmapButton m_bmpAnimSpeed;

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

public:
	void FunctionUpdate();
	void OptionUpdate();
	void ModeUpdate();
	void SettingUpdate();
	void ActionUpdate();

private:
	void AnimTransformUpdate(SP(Engine::CObject) spObject);

private:
#pragma region EventFunc
	afx_msg void OnBnClickedAnimPlay();
	afx_msg void OnBnClickedAnimPause();
	afx_msg void OnBnClickedAnimStop();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnEnChangeEditPosX();
	afx_msg void OnEnChangeEditPosY();
	afx_msg void OnEnChangeEditPosZ();
	afx_msg void OnEnChangeEditRotX();
	afx_msg void OnEnChangeEditRotY();
	afx_msg void OnEnChangeEditRotZ();
	afx_msg void OnEnChangeEditScaleX();
	afx_msg void OnEnChangeEditScaleY();
	afx_msg void OnEnChangeEditScaleZ();
	afx_msg void OnEnChangeEditStartTime();
	afx_msg void OnEnChangeEditEndTime();
	afx_msg void OnEnChangeEditRepeat();
	afx_msg void OnEnChangeEditAlphaWidth();
	afx_msg void OnEnChangeEditAlphaHeight();
	afx_msg void OnDeltaposSpinPosX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPosY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPosZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinRotX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinRotY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinRotZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinScaleX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinScaleY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinScaleZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinStartTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinEndTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinRepeat(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinAlphaWidth(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinAlphaHeight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditSpeed();
	afx_msg void OnEnChangeEditAnimSpeed();

#pragma endregion

#pragma region EventVariable	
	CEdit m_edPosX;
	CEdit m_edPosY;
	CEdit m_edPosZ;
	CEdit m_edRotX;
	CEdit m_edRotY;
	CEdit m_edRotZ;
	CEdit m_edScaleX;
	CEdit m_edScaleY;
	CEdit m_edScaleZ;
	CEdit m_edStartTime;
	CEdit m_edEndTIme;
	CEdit m_edRepeat;
	CEdit m_edAlphaWidth;
	CEdit m_edAlphaHeight;
#pragma endregion

#pragma  region EventButton
	CButton m_btnLoop;
	CButton m_btnBillboard;
	CButton m_btnOptionPos;
	CButton m_btnOptionRot;
	CButton m_btnOptionScale;
	CButton m_btnOptionFadeIn;
	CButton m_btnOptionFadeOut;
	CButton m_btnOptionUVSprite;
	CButton m_btnOptionUVAnim;
	CButton m_btnModeTransform;
	CButton m_btnModeEdit;
	CButton m_btnModePosition;
	CButton m_btnModeRotation;
	CButton m_btnModeScale;
	CButton m_btnModeFadeIn;
	CButton m_btnModeFadeOut;
	CButton m_btnModeUVSprite;
	CButton m_btnModeUVAnim;

#pragma endregion

#pragma region SpinCtrl
public:
	CSpinButtonCtrl m_spinPosX;
	CSpinButtonCtrl m_spinPosY;
	CSpinButtonCtrl m_spinPosZ;
	CSpinButtonCtrl m_spinRotX;
	CSpinButtonCtrl m_spinRotY;
	CSpinButtonCtrl m_spinRotZ;
	CSpinButtonCtrl m_spinAlphaWidth;
	CSpinButtonCtrl m_spinAlphaHeigth;
	CSpinButtonCtrl m_spinScaleX;
	CSpinButtonCtrl m_spinScaleY;
	CSpinButtonCtrl m_spinScaleZ;
#pragma endregion

private:
	enum ACTION_STATE { PLAY, PAUSE, STOP, STATE_END };
	
private:
	CString m_ObjectTag;
	_int m_iSelectObjectNum;
	_int m_iRepeat;
	_int m_iRepeatCnt;

	_float m_fSpeed;
	_float m_fAnimSpeed;
	_float m_fStartTime;
	_float m_fEndTime;
	GETTOR(_float, m_fAlphaWidth, 0.f, AlphaWidth)
	GETTOR(_float, m_fAlphaHeight, 0.f, AlphaHeight)

	_bool m_isPlayAnim;

	_float3 m_vSavePos;
	_float3 m_vSaveRot;
	_float3 m_vSaveScale;
	ACTION_STATE m_eActionState;
public:
	afx_msg void OnLbnSelchangeEffectList();
	CListBox m_EffectListBox;
};



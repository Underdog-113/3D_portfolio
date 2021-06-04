#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CInspectorView 폼 뷰입니다.

class CInspectorView : public CFormView
{
	DECLARE_DYNCREATE(CInspectorView)

protected:
	CInspectorView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CInspectorView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSPECTORVIEW };
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
public:
	virtual void OnInitialUpdate();
	void Update(void);

public:
	void SetPosition(Engine::_float3 vPos);
	void SetRotation(Engine::_float3 vRot);
	void SetScale(Engine::_float3 vScale);

private:
	void SpinBtn(LPNMUPDOWN ppNMUpDown, CEdit* pBtn, Engine::_float fVal);

public:
	CEdit m_fPosX;
	CEdit m_fPosY;
	CEdit m_fPosZ;
	CEdit m_fRotX;
	CEdit m_fRotY;
	CEdit m_fRotZ;
	CEdit m_fScaleX;
	CEdit m_fScaleY;
	CEdit m_fScaleZ;
	CSpinButtonCtrl m_btnPosX;
	CSpinButtonCtrl m_btnPosY;
	CSpinButtonCtrl m_btnPosZ;
	CSpinButtonCtrl m_btnRotX;
	CSpinButtonCtrl m_btnRotY;
	CSpinButtonCtrl m_btnRotZ;
	CSpinButtonCtrl m_btnScaleX;
	CSpinButtonCtrl m_btnScaleY;
	CSpinButtonCtrl m_btnScaleZ;
	afx_msg void OnPosX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPosY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPosZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRotX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRotY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRotZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnScaleX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnScaleY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnScaleZ(NMHDR *pNMHDR, LRESULT *pResult);

private:
	_float m_fPosMin = 0.f;
	_float m_fPosMax = 0.f;
	_float m_fRotMin = 0.f;
	_float m_fRotMax = 0.f;
	_float m_fScaleMin = 0.f;
	_float m_fScaleMax = 0.f;
public:
	CButton m_arrCreateWay[2];
	CButton m_arrObject[3];
	afx_msg void OnBnClickedObjectRadio();
	afx_msg void OnBnClickedBlock();
	afx_msg void OnBnClickedNavi();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedLoadBtn();

public:
	CListBox m_TreeList;
	CTreeCtrl m_Tree;
	CString m_curTreeItem; // 트리에서 클릭한 아이템
	CString m_curSelPath; // 리스트에서 선택한 메쉬의 경로
	CString m_curSelFileName;
	CString m_curObj;

	void Set_List_Path(TCHAR * path, _bool bCheck = FALSE);
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnSelchangeMeshList();
};

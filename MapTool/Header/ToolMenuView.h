#pragma once
#include "afxwin.h"



// CToolMenuView �� ���Դϴ�.

class CToolMenuView : public CFormView
{
	DECLARE_DYNCREATE(CToolMenuView)

protected:
	CToolMenuView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CToolMenuView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLMENUVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

// add function
public:
	virtual void OnInitialUpdate();
	void Update(void);

	void SetPosition(Engine::_float3 vPos);
	void SetRotation(Engine::_float3 vRot);
	void SetScale(Engine::_float3 vScale);
	void SpinBtn(LPNMUPDOWN ppNMUpDown, CEdit* pBtn, Engine::_float fVal);
	void SetChangeList(std::wstring sectionKey);

	afx_msg void OnPosX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPosY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPosZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRotX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRotY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRotZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnScaleX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnScaleY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnScaleZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedMeshTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnSelchangeMeshList();

private:
	_float GetEditControlData(CEdit* pEdit, LPNMUPDOWN pNMUpDown);

// add valuable
protected:
	CEdit m_posX;
	CEdit m_posY;
	CEdit m_posZ;

	CEdit m_rotX;
	CEdit m_rotY;
	CEdit m_rotZ;

	CEdit m_scaleX;
	CEdit m_scaleY;
	CEdit m_scaleZ;

	CSpinButtonCtrl m_spinPosX;
	CSpinButtonCtrl m_spinPosY;
	CSpinButtonCtrl m_spinPosZ;

	CSpinButtonCtrl m_spinRotX;
	CSpinButtonCtrl m_spinRotY;
	CSpinButtonCtrl m_spinRotZ;

	CSpinButtonCtrl m_spinScaleX;
	CSpinButtonCtrl m_spinScaleY;
	CSpinButtonCtrl m_spinScaleZ;

	short m_valueMin = 0;
	short m_valueMax = 0;

	CTreeCtrl m_meshTree;
	CListBox m_meshTreeList;

	CString m_curTreeItem; // Ʈ������ Ŭ���� ������
	
	CString m_curSelPath; // ����Ʈ���� ������ �޽��� ���
	CString m_curObj;

	GETTOR(CString, m_curSelFileName, L"", CurSelFileName);

public:
//	afx_msg void OnBnClickedObjectRadio();
//	afx_msg void OnBnClickedBlock();
//	afx_msg void OnBnClickedNavi();
//	afx_msg void OnBnClickedSaveBtn();
//	afx_msg void OnBnClickedLoadBtn();
//
//public:
//	//CListBox m_TreeList;
//	//CTreeCtrl m_Tree;
//	//CString m_curTreeItem; // Ʈ������ Ŭ���� ������
//	//CString m_curSelPath; // ����Ʈ���� ������ �޽��� ���
//	//CString m_curSelFileName;
//	//CString m_curObj;
//
//	void Set_List_Path(TCHAR * path, _bool bCheck = FALSE);
//	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLbnSelchangeMeshList();
public:
	
};



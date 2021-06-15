#pragma once
#include "afxwin.h"



// CToolMenuView 폼 뷰입니다.

class CToolMenuView : public CFormView
{
	DECLARE_DYNCREATE(CToolMenuView)

protected:
	CToolMenuView();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

// add function
public:
	virtual void OnInitialUpdate();
	void Update(void);

	void SetPosition(Engine::_float3 vPos);
	void SetRotation(Engine::_float3 vRot);
	void SetScale(Engine::_float3 vScale);
	void SpinBtn(LPNMUPDOWN ppNMUpDown, CEdit* pBtn, Engine::_float fVal);
	void SetChangeMeshList(std::wstring sectionKey);
	void SetChangeTextureList(std::wstring sectionKey);
	void DataParsing(ELayerID layerID, std::wofstream* ofsSave);

	afx_msg void OnPosX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPosY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPosZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRotX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRotY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRotZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnScaleX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnScaleY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnScaleZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnSelchangeMeshList();
	afx_msg void OnLbnSelchangeTextureList();
	afx_msg void OnBnClickedPositionBtn();
	afx_msg void OnBnClickedRotationBtn();
	afx_msg void OnBnClickedScaleBtn();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedLoadBtn();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnBnClickedCreatePrefBtn();
	afx_msg void OnBnClickedCreateAABBColliderBtn();
	afx_msg void OnBnClickedAddCollisionCBtn();
	afx_msg void OnBnClickedDelAABBColliderBtn();
	afx_msg void OnCbnSelchangeAABBList();
	afx_msg void OnBnClickedSelectedAABBCol();
	afx_msg void OnBnClickedModifyAABBColBtn();
	afx_msg void OnBnClickedCreateRayColliderBtn();
	afx_msg void OnBnClickedDelRayColliderBtn();
	afx_msg void OnCbnSelchangeRayList();
	afx_msg void OnBnClickedSelectedRayCol();
	afx_msg void OnBnClickedModifyRayColBtn();
	afx_msg void OnBnClickedCreateMesh();
	afx_msg void OnLbnSelchangeObjectList();
	afx_msg void OnBnClickedCurObjectNameChk();
	afx_msg void OnBnClickedSelectedObbCol();

private:
	_float GetEditControlData(CEdit* pEdit, LPNMUPDOWN pNMUpDown);

// add valuable
public:
	CButton m_initTexture; // inittexture checkbox
	CButton m_showAllCol; // show All Collision
	CButton m_colType[3]; // 0: aabb, 1: ray, 2: obb
	CButton m_addColC; // 콜리전 컴포넌트 추가

	// aabb
	CButton m_selectedAABBCol; // check cur selected aabb col
	CEdit m_aabbOffset; // aabb collider offset
	CEdit m_aabbSize; // aabb collider size
	CComboBox m_aabbCnt; // cur aabb collision cnt

	// ray
	CButton m_selectedRayCol; // check cur selected ray col
	CEdit m_rayOffSet;
	CEdit m_rayLen;
	CEdit m_rayDir;
	CComboBox m_rayType; // ray col type
	CComboBox m_rayCnt; // cur ray collision cnt

	// obb
	CEdit m_obbOffset;
	CEdit m_obbSize;
	CComboBox m_obbCnt;
	CButton m_selectedObbCol;

	CEdit m_curObjName; // cur selected object name
	CButton m_curObjNameChk;

	CComboBox m_layerID; // mesh layer id
	CComboBox m_colliderID; // collider id

	CListBox m_objList;
	CButton m_renderAlpha; // alpha rendering on/off
	
	_int m_curSelLayerID; // cur selected layer id

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

	CTreeCtrl m_tree;
	CListBox m_meshTreeList;
	CListBox m_textureTreeList;

	CEdit m_saveFileName;
	CString m_curTreeItem; // 트리에서 클릭한 아이템
	
	GETTOR(CString, m_curSelFileName, L"", CurSelFileName);
	GETTOR(CString, m_curSelTextureFileName, L"", CurSelTextureFileName);
public:
	
	afx_msg void OnCbnSelchangeObbList();
	afx_msg void OnBnClickedCreateObbColliderBtn();
	afx_msg void OnBnClickedModifyObbColBtn();
	afx_msg void OnBnClickedDelObbColliderBtn();
	afx_msg void OnBnClickedDelObjectWithObjList();
	CButton m_showObjectChk;
	afx_msg void OnBnClickedShowObjectChk();
	CComboBox m_loadFileName;
	CEdit m_obbRotOffset;
};

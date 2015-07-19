// WeightDlg.h : header file
//

#if !defined(AFX_WEIGHTDLG_H__56D4B0C6_DC15_4B46_8696_E868E66A4144__INCLUDED_)
#define AFX_WEIGHTDLG_H__56D4B0C6_DC15_4B46_8696_E868E66A4144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\DialogClasses\header\FormulaDialog.h"
#include "..\..\ExternClasses\header\BtnST.h"
#include "..\..\CustomColorDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CWeightDlg dialog

class CWeightDlg : public CDialog
{
// Construction
public:
	CWeightDlg(CWnd* pParent = NULL);	// standard constructor
	~CWeightDlg();
	CFormulaDialog* pFormulaDialog;
// Dialog Data
	//{{AFX_DATA(CWeightDlg)
	enum { IDD = IDD_MAIN_DIALOG };
	CStatic	m_StatusStatic;
	CButtonST	m_FetchStuffButton;
	CButtonST	m_QueryButton;
	CButtonST	m_FormulaWeighButton;
	CButtonST	m_WeighFreeButton;
	CButtonST	m_FetchRecordButton;
	CButtonST	m_StatisticButton;
	CButtonST	m_OtherSettingsButton;
	CButtonST	m_UserManagementButton;
	CButtonST	m_PowerOffButton;
	CButtonST	m_MaterialManagementButton;
	CButtonST	m_FormulaManagementButton;
	CButtonST	m_ChangePasswordButton;
	//}}AFX_DATA

	CBrush   m_brBk;//在public中定义  

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWeightDlg)
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	HICON m_hIcon;
protected:
	void initButtons();
// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(CWeightDlg)
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPowerOff();
	afx_msg void OnFormulaManagement();
	afx_msg void OnUsermanagement();
	afx_msg void OnMaterialmanagementButton();
	afx_msg void OnOthersettingsbutton();
	afx_msg void OnStatisticButton();
	afx_msg void OnQueryButton();
	afx_msg void OnWightstartButton();
	afx_msg void OnChangepasswordButton();
	afx_msg void OnFetchrecord();
	afx_msg void OnWeighfreeButton();
	afx_msg void OnFetchstuffButton();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEIGHTDLG_H__56D4B0C6_DC15_4B46_8696_E868E66A4144__INCLUDED_)


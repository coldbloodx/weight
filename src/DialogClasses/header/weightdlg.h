#if !defined(AFX_WEIGHTDLG_H__56D4B0C6_DC15_4B46_8696_E868E66A4144__INCLUDED_)
#define AFX_WEIGHTDLG_H__56D4B0C6_DC15_4B46_8696_E868E66A4144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "FormulaDialog.h"


class CWeightDlg : public CDialog
{

public:
	CWeightDlg(CWnd* pParent = NULL);	
	~CWeightDlg();
	CFormulaDialog* pFormulaDialog;

	enum { IDD = IDD_MAIN_DIALOG };
	CStatic	m_StatusStatic;
	CButton	m_FetchStuffButton;
	CButton	m_QueryButton;
	CButton	m_FormulaWeighButton;
	CButton	m_WeighFreeButton;
	CButton	m_StatisticButton;
	CButton	m_OtherSettingsButton;
	CButton	m_UserManagementButton;
	CButton	m_PowerOffButton;
	CButton	m_MaterialManagementButton;
	CButton	m_FormulaManagementButton;
	CButton	m_ChangePasswordButton;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	HICON m_hIcon;
protected:

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void showstatus(CStatic& rstatic);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();



    afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPowerOff();
	afx_msg void OnFormulaManagement();
	afx_msg void OnUsermanagement();
	afx_msg void OnMaterialmanagementButton();
	afx_msg void OnQueryButton();
	afx_msg void OnWightstartButton();
	afx_msg void OnChangepasswordButton();
	afx_msg void OnWeighfreeButton();
	afx_msg void OnFetchstuffButton();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOthersettingsbutton();
};

#endif 


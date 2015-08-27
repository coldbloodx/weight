#pragma once
#include "afxwin.h"

// CWeighManagementDialog dialog

class CMainSettings : public CDialog
{
	DECLARE_DYNAMIC(CMainSettings)

public:
	CMainSettings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMainSettings();

// Dialog Data
	enum { IDD = IDD_WEIGHMANAGEMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_MaterialManagement;
	CButton m_FormulaManagement;
	CButton m_Query;
	CButton m_Statistic;
    CButton m_goBackButton;
    CButton m_barcodeManagement;
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedGoBack();
    afx_msg void OnBnClickedBarcodeManagement();
    afx_msg void OnPaint();
};

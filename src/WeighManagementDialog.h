#pragma once
#include "afxwin.h"
#include "ExternClasses/header/BtnST.h"


// CWeighManagementDialog dialog

class CWeighManagementDialog : public CDialog
{
	DECLARE_DYNAMIC(CWeighManagementDialog)

public:
	CWeighManagementDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWeighManagementDialog();

// Dialog Data
	enum { IDD = IDD_WEIGHMANAGEMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButtonST m_MaterialManagement;
	CButtonST m_FormulaManagement;
	CButtonST m_Query;
	CButtonST m_Statistic;
	afx_msg void OnBnClickedButton4();
	CButtonST m_goBackButton;
	CBrush   m_brBk;//在public中定义  

	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};

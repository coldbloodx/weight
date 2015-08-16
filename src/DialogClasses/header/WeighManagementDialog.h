#pragma once
#include "afxwin.h"



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
	CButton m_MaterialManagement;
	CButton m_FormulaManagement;
	CButton m_Query;
	CButton m_Statistic;
	afx_msg void OnBnClickedButton4();
	CButton m_goBackButton;
	CBrush   m_brBk;//在public中定义  

	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
    afx_msg void OnPaint();
};

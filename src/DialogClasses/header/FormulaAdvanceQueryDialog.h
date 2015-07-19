#if !defined(AFX_FORMULAADVANCEQUERYDIALOG_H__6CDF9CC7_97B8_438F_9B54_8907F19C9524__INCLUDED_)
#define AFX_FORMULAADVANCEQUERYDIALOG_H__6CDF9CC7_97B8_438F_9B54_8907F19C9524__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormulaAdvanceQueryDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormulaAdvanceQueryDialog dialog

#include "..\..\ExternClasses\header\BtnST.h"
#include "..\..\CustomColorDialog.h"

class CFormulaAdvanceQueryDialog : public CDialog
{
// Construction
public:
	CFormulaAdvanceQueryDialog(CWnd* pParent = NULL);   // standard constructor
	~CFormulaAdvanceQueryDialog();
// Dialog Data
	//{{AFX_DATA(CFormulaAdvanceQueryDialog)
	enum { IDD = IDD_FORMULAADVANCEQUERY_DIALOG };
	//CStatic	m_StatusStatic;
	//}}AFX_DATA
	CButtonST	m_ButtonOK;
	CEdit	m_FormulaEdit;
	CComboBox	m_UserCombo;
	CComboBox	m_FormulaCombo;
	CComboBox	m_DateCombo;
	CComboBox	m_AmountCombo;
	CEdit	m_UserEdit;
	CButton	m_SumCheck;
	CDateTimeCtrl	m_DateSecond;
	CDateTimeCtrl	m_DateFirst;
	CEdit	m_AmountSecondEdit;
	CEdit	m_AmountFirstEdit;
	CString sqlState;
	bool	needAnd;
	CBrush   m_brBk;//在public中定义  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormulaAdvanceQueryDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFormulaAdvanceQueryDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeUserCombo();
	afx_msg void OnSelchangeFormulaCombo();
	afx_msg void OnSelchangeAmountCombo();
	afx_msg void OnSelchangeDateCombo();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMULAADVANCEQUERYDIALOG_H__6CDF9CC7_97B8_438F_9B54_8907F19C9524__INCLUDED_)

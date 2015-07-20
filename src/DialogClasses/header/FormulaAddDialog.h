#if !defined(AFX_FORMULAADDDIALOG_H__1149F050_DB11_4C28_A7AB_CD981B3F57BB__INCLUDED_)
#define AFX_FORMULAADDDIALOG_H__1149F050_DB11_4C28_A7AB_CD981B3F57BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormulaAddDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormulaAddDialog dialog

#include "..\..\CustomColorDialog.h"

class CFormulaAddDialog : public CDialog
{
// Construction
public:
	CFormulaAddDialog(CWnd* pParent = NULL);   // standard constructor
	~CFormulaAddDialog();

// Dialog Data
	//{{AFX_DATA(CFormulaAddDialog)
	enum { IDD = IDD_FORMULAADD_DIALOG };
	//CStatic	m_StatusStatic;
	//}}AFX_DATA

	CBrush   m_brBk;//在public中定义  

	CButton m_ButtonOK;
	CButton m_ButtonCancel;
	CStatic	m_PercentageSecond;
	CStatic	m_MaterialSecond;
	CEdit	m_FormulaName;
	CEdit	m_FormulaID;
	std::vector<CButton*> buttonVector;
	int materialCount;
	CComboBox testCombox;
	CStatic   testStatic;
	CEdit     testEdit;
	std::vector<CComboBox* > comboboxVector;
	std::vector<CEdit *> editVector;
	std::vector<CString> materialVector;

	void queryMaterials();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormulaAddDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFormulaAddDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMULAADDDIALOG_H__1149F050_DB11_4C28_A7AB_CD981B3F57BB__INCLUDED_)

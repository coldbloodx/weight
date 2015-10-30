#if !defined(AFX_FORMULASELECTDIALOG_H__164FB553_66E0_4ED1_8D8B_AE3A4B569385__INCLUDED_)
#define AFX_FORMULASELECTDIALOG_H__164FB553_66E0_4ED1_8D8B_AE3A4B569385__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormulaSelectDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormulaSelectDialog dialog


#include "afxwin.h"
class CFormulaSelectDialog : public CDialog
{
// Construction
public:
	CFormulaSelectDialog(CWnd* pParent = NULL);   // standard constructor
	~CFormulaSelectDialog();
// Dialog Data
	//{{AFX_DATA(CFormulaSelectDialog)
	enum { IDD = IDD_FORMULASELECT_DIALOG };

	//}}AFX_DATA
	CEdit	m_Weigh;
	CComboBox	m_FormulaIDCombo;
	CComboBox	m_FormulaSelect;
	CButton	m_ButtonOK;
	CButton	m_ButtonCancel;
	CButton	m_Button9;
	CButton	m_Button8;
	CButton	m_Button7;
	CButton	m_Button6;
	CButton	m_Button5;
	CButton	m_Button4;
	CButton	m_Button3;
	CButton	m_Button2;
	CButton	m_Button1;
	CButton	m_Button0;
	CButton	m_ButtonComma;
	CButton	m_ButtonBack;
	int m_FocusedID;
	CBrush   m_brBk;//在public中定义  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormulaSelectDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFormulaSelectDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeFormulaselectCombo();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton0();
	afx_msg void OnButtonComma();
	afx_msg void OnButtonBack();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CButton m_GoBack;
	afx_msg void OnBnClickedGoback();
};


#endif 

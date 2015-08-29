#if !defined(AFX_FETCHRECORDSADVANCEQUERYDIALOG_H__6CFC0C5D_9B66_4A6B_81A4_E8AD737EF54E__INCLUDED_)
#define AFX_FETCHRECORDSADVANCEQUERYDIALOG_H__6CFC0C5D_9B66_4A6B_81A4_E8AD737EF54E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FetchRecordsAdvanceQueryDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFetchRecordsAdvanceQueryDialog dialog

class CFetchRecordsAdvanceQueryDialog : public CDialog
{
	// Construction
public:
	CFetchRecordsAdvanceQueryDialog(CWnd* pParent = NULL);   // standard constructor
	~CFetchRecordsAdvanceQueryDialog();
	// Dialog Data
	//{{AFX_DATA(CFetchRecordsAdvanceQueryDialog)
	enum { IDD = IDD_FETCHRECORDADVANCEQUERY_DIALOG };

	//}}AFX_DATA
	int    m_FocusedID;
	//CStatic	m_StatusStatic;
	CButton	m_ButtonOK;
	CEdit	m_UserEdit;
	CEdit	m_FormulaEdit;
	CEdit	m_AmountFirstEdit;
	CEdit	m_AmountSecondEdit;
	CComboBox	m_UserCombo;
	CComboBox	m_FormulaCombo;
	CComboBox	m_AmountCombo;
	CComboBox	m_DateCombo;
	CDateTimeCtrl	m_DateFirst;
	CDateTimeCtrl	m_DateSecond;
	CButton	m_SumCheck;
	CFont* m_Font;
	CString sqlState;
	BOOL needAnd;
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
	CButton	m_CommaButton;
	CButton	m_BackButton;
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFetchRecordsAdvanceQueryDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	CBrush   m_brBk;//在public中定义  
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CFetchRecordsAdvanceQueryDialog)
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
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDateCombo();
	afx_msg void OnSelchangeAmountCombo();
	
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg virtual void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FETCHRECORDSADVANCEQUERYDIALOG_H__6CFC0C5D_9B66_4A6B_81A4_E8AD737EF54E__INCLUDED_)

#if !defined(AFX_FETCHAMOUNTINPUTDIALOG_H__6B8A08A9_9867_4D34_95F0_EB015B61C73A__INCLUDED_)
#define AFX_FETCHAMOUNTINPUTDIALOG_H__6B8A08A9_9867_4D34_95F0_EB015B61C73A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FetchAmountInputDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFetchAmountInputDialog dialog

#include "afxwin.h"

class CFetchAmountInputDialog : public CDialog
{
// Construction
public:
	CFetchAmountInputDialog(CWnd* pParent = NULL);   // standard constructor
	~CFetchAmountInputDialog();
// Dialog Data
	//{{AFX_DATA(CFetchAmountInputDialog)
	enum { IDD = IDD_FETCHAMOUNTINTPUT_DIALOG };
	CButton	m_PrintCheck;
	//CStatic	m_StatusStatic;
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
	CEdit	m_FetchAmount;
	CBrush   m_brBk;//在public中定义   
	//}}AFX_DATA
	std::vector<CButton*> buttonVector;
	std::vector<CString> printVector;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFetchAmountInputDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFetchAmountInputDialog)
	virtual void OnOK();
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
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedGoback();
	CButton m_GoBack;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FETCHAMOUNTINPUTDIALOG_H__6B8A08A9_9867_4D34_95F0_EB015B61C73A__INCLUDED_)

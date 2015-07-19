#if !defined(AFX_LOGINDIALOG_H__48E2A30D_CA8A_473A_B72D_3B59A020044A__INCLUDED_)
#define AFX_LOGINDIALOG_H__48E2A30D_CA8A_473A_B72D_3B59A020044A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDialog.h : header file
//

#include "..\..\ExternClasses\header\BtnST.h"
/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog

class CLoginDialog : public CDialog
{
// Construction
public:
	CLoginDialog(CWnd* pParent = NULL);   // standard constructor
	~CLoginDialog();
// Dialog Data
	//{{AFX_DATA(CLoginDialog)
	enum { IDD = IDD_LOGIN_DIALOG };
	CButtonST	m_ButtonOK;
	CButtonST	m_ButtonCancel;
	CButtonST	m_Button9;
	CButtonST	m_Button8;
	CButtonST	m_Button7;
	CButtonST	m_Button6;
	CButtonST	m_Button5;
	CButtonST	m_Button4;
	CButtonST	m_Button3;
	CButtonST	m_Button2;
	CButtonST	m_Button1;
	CButtonST	m_Button0;
	CButtonST	m_ButtonComma;
	CButtonST	m_ButonBack;
	CEdit	m_Password;
	CEdit	m_UserName;
	//}}AFX_DATA
	int		tryTimes;
	std::vector<CButtonST*> buttonVector;
	CBrush   m_brBk;//在public中定义   
	int    m_FocusedID;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CLoginDialog)
	virtual void OnCancel();
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDIALOG_H__48E2A30D_CA8A_473A_B72D_3B59A020044A__INCLUDED_)

#if !defined(AFX_USERMANAGEDIALOG_H__CD2D6C0D_84E3_48AD_9C68_C547975D9FC9__INCLUDED_)
#define AFX_USERMANAGEDIALOG_H__CD2D6C0D_84E3_48AD_9C68_C547975D9FC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserManageDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserManageDialog dialog
#include "..\..\ExternClasses\header\BtnST.h"
#include "..\..\CustomColorDialog.h"
#include "afxwin.h"
class CUserManageDialog : public CCustomColorDialog
{
// Construction
public:
	CUserManageDialog(CWnd* pParent = NULL);   // standard constructor
	~CUserManageDialog();
	void initList();
// Dialog Data
	//{{AFX_DATA(CUserManageDialog)
	enum { IDD = IDD_USERMANAGEMENT_DIALOG };
	CStatic	m_StatusStatic;
	CButtonST	m_ButtonOK;
	CButtonST	m_Del;
	CButtonST	m_Add;
	CListCtrl	m_UserList;
	//}}AFX_DATA
	
CBrush   m_brBk;//��public�ж���  


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserManageDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void initListHeader();

	// Generated message map functions
	//{{AFX_MSG(CUserManageDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnUseradd();
	afx_msg void OnUserdel();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBack();
	CButtonST m_Back;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERMANAGEDIALOG_H__CD2D6C0D_84E3_48AD_9C68_C547975D9FC9__INCLUDED_)

#if !defined(AFX_USERADDDIALOG_H__6F9CE3AE_6EE3_4514_BEC0_5845304735AA__INCLUDED_)
#define AFX_USERADDDIALOG_H__6F9CE3AE_6EE3_4514_BEC0_5845304735AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserAddDialog.h : header file
//
#include "UserManageDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CUserAddDialog dialog

#include "..\..\ExternClasses\header\BtnST.h"
#include "..\..\CustomColorDialog.h"
class CUserAddDialog : public CDialog
{
// Construction
public:
	CUserAddDialog(CWnd* pParent = NULL);   // standard constructor
	~CUserAddDialog();
	CUserManageDialog* m_UserManagementWindow;
// Dialog Data
	//{{AFX_DATA(CUserAddDialog)
	enum { IDD = IDD_USERADD_DIALOG };
	CButtonST	m_ButtonOK;
	CButtonST	m_ButtonCancel;
	CComboBox	m_UserRight;
	CEdit	m_UserName;
	CEdit	m_UserID;
	//}}AFX_DATA
	CBrush   m_brBk;//在public中定义  

	std::vector<CButtonST*> buttonVector;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserAddDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserAddDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERADDDIALOG_H__6F9CE3AE_6EE3_4514_BEC0_5845304735AA__INCLUDED_)

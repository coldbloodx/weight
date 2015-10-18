#if !defined(AFX_USERMANAGEDIALOG_H__CD2D6C0D_84E3_48AD_9C68_C547975D9FC9__INCLUDED_)
#define AFX_USERMANAGEDIALOG_H__CD2D6C0D_84E3_48AD_9C68_C547975D9FC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserManageDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserManageDialog dialog


#include "afxwin.h"
class CUserManageDialog : public CDialog
{

public:
	CUserManageDialog(CWnd* pParent = NULL);   // standard constructor
	~CUserManageDialog();
	void initList();
	enum { IDD = IDD_USERMANAGEMENT_DIALOG };
	CStatic	m_StatusStatic;
	CButton	m_ButtonOK;
	CButton	m_Del;
	CButton	m_Add;
	CListCtrl	m_UserList;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	void initListHeader();
	virtual BOOL OnInitDialog();
	afx_msg void OnUseradd();
	afx_msg void OnUserdel();
	DECLARE_MESSAGE_MAP()
};

#endif

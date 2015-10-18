#if !defined(AFX_USERADDDIALOG_H__6F9CE3AE_6EE3_4514_BEC0_5845304735AA__INCLUDED_)
#define AFX_USERADDDIALOG_H__6F9CE3AE_6EE3_4514_BEC0_5845304735AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "UserManageDialog.h"

class CUserAddDialog : public CDialog
{

public:
	CUserAddDialog(CWnd* pParent = NULL); 
	~CUserAddDialog();
	CUserManageDialog* m_UserManagementWindow;

	enum { IDD = IDD_USERADD_DIALOG };
	CButton	m_ButtonOK;
	CButton	m_ButtonCancel;
	CComboBox	m_UserRight;
	CEdit	m_UserName;
	CEdit	m_UserID;

	std::vector<CButton*> buttonVector;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

protected:
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

#endif 

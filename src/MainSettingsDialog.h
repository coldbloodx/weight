#pragma once
#include "afxwin.h"
#include "ExternClasses/header/BtnST.h"


// CMainSettingsDialog dialog

class CMainSettingsDialog : public CDialog
{
	DECLARE_DYNAMIC(CMainSettingsDialog)

public:
	CMainSettingsDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMainSettingsDialog();
	CBrush   m_brBk;//在public中定义  
// Dialog Data
	enum { IDD = IDD_MAINSETTINGSDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButtonST m_goBackButton;
	CButtonST m_ChangeNameButton;
	CButtonST m_OtherSettingsButton;
	CButtonST m_UserManagement;
	CButtonST m_ChangePassword;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
};

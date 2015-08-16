#pragma once
#include "afxwin.h"



// CMainSettingsDialog dialog

class CBasicSettingsDialog : public CDialog
{
	DECLARE_DYNAMIC(CBasicSettingsDialog)

public:
	CBasicSettingsDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBasicSettingsDialog();
	CBrush   m_brBk;//在public中定义  
// Dialog Data
	enum { IDD = IDD_BASIC_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_goBackButton;
	CButton m_ChangeNameButton;
	CButton m_OtherSettingsButton;
	CButton m_UserManagement;
	CButton m_ChangePassword;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
    afx_msg void OnPaint();
};

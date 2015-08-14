#if !defined(AFX_OTHERSETTINGSDIALOG_H__127C1BBE_934A_49FB_9654_9A05AFFD0175__INCLUDED_)
#define AFX_OTHERSETTINGSDIALOG_H__127C1BBE_934A_49FB_9654_9A05AFFD0175__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OtherSettingsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COtherSettingsDialog dialog


#include "afxwin.h"

class COtherSettingsDialog : public CDialog
{
// Construction
public:
	COtherSettingsDialog(CWnd* pParent = NULL);   // standard constructor
	~COtherSettingsDialog();
// Dialog Data
	//{{AFX_DATA(COtherSettingsDialog)
	enum { IDD = IDD_SETTINGS_DIALOG };
	CButton	m_ButtonOK;
	CButton	m_ButtonCancel;
	CButton	m_Restore;
	CButton	m_Backup;
	CComboBox	m_Com2Rate;
	CComboBox	m_Com1Rate;
	CString oldFileName;
	CString fileName;
	CString filePath;
	//}}AFX_DATA
CBrush   m_brBk;//在public中定义  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COtherSettingsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COtherSettingsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBackupdatabase();
	afx_msg void OnRestoredatabase();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHERSETTINGSDIALOG_H__127C1BBE_934A_49FB_9654_9A05AFFD0175__INCLUDED_)

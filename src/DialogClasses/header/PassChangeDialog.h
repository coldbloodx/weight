#if !defined(AFX_PASSCHANGEDIALOG_H__0082592D_6762_4EBB_AFB0_86516DF84C9D__INCLUDED_)
#define AFX_PASSCHANGEDIALOG_H__0082592D_6762_4EBB_AFB0_86516DF84C9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PassChangeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPassChangeDialog dialog

#include "..\..\CustomColorDialog.h"
#include "afxwin.h"

class CPassChangeDialog : public CCustomColorDialog
{
// Construction
public:
	CPassChangeDialog(CWnd* pParent = NULL);   // standard constructor
	~CPassChangeDialog();
// Dialog Data
	//{{AFX_DATA(CPassChangeDialog)
	enum { IDD = IDD_PASSCHANGE_DIALOG };
	CButton	m_ButtonOK;
	CButton	m_ButtonCancel;
	CEdit	m_OriginalPassEdit;
	CEdit	m_NewPassEdit;
	CEdit	m_NewPassConfirmEdit;
	//}}AFX_DATA
	std::vector<CButton*> buttonVector;
CBrush   m_brBk;//在public中定义 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassChangeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPassChangeDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBack();
	CButton m_Back;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSCHANGEDIALOG_H__0082592D_6762_4EBB_AFB0_86516DF84C9D__INCLUDED_)

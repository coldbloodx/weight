#if !defined(AFX_FETCHRECORDDIALOG_H__2ACCC87A_D89B_4566_9BAD_831DB3C55CCF__INCLUDED_)
#define AFX_FETCHRECORDDIALOG_H__2ACCC87A_D89B_4566_9BAD_831DB3C55CCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FetchRecordDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFetchRecordDialog dialog
#include "..\..\ExternClasses\header\BtnST.h"
#include "..\..\CustomColorDialog.h"


class CFetchRecordDialog : public CDialog
{
// Construction
public:
	CFetchRecordDialog(CWnd* pParent = NULL);   // standard constructor
	~CFetchRecordDialog();
	void initListHeader();
	void initList();
// Dialog Data
	//{{AFX_DATA(CFetchRecordDialog)
	enum { IDD = IDD_FETCHRECORD_DIALOG };

	//}}AFX_DATA
	CStatic	m_StatusStatic;
	CButtonST	m_ButtonOK;
	CButtonST	m_QueryButton;
	CButtonST	m_PrintButton;
	CButtonST	m_ClearButton;
	CButtonST	m_AllButton;
	CButtonST	m_ButtonAdvanceQuery;
	CEdit	m_Keyword;
	CComboBox	m_Index;
	CListCtrl	m_FetchRecordList;
	CBrush   m_brBk;//在public中定义  
	
	std::vector<CString> headerVector;
	std::vector<CString> headerList;
	std::vector<CString> valueList;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFetchRecordDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFetchRecordDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnPrintButton();
	afx_msg void OnFetchrecordclearButton();
	afx_msg void OnQueryButton();
	afx_msg void OnAdvancequeryButton();
	afx_msg void OnAllButton();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FETCHRECORDDIALOG_H__2ACCC87A_D89B_4566_9BAD_831DB3C55CCF__INCLUDED_)

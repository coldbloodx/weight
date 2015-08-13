#include "afxwin.h"
#if !defined(AFX_FREEWEIGHTDIALOG_H__FE5C39E4_F2C4_49F7_96D5_612B2A759BE0__INCLUDED_)
#define AFX_FREEWEIGHTDIALOG_H__FE5C39E4_F2C4_49F7_96D5_612B2A759BE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FreeWeightDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFreeWeightDialog dialog


class CFreeWeightDialog : public CDialog
{
// Construction
public:
	CFreeWeightDialog(CWnd* pParent = NULL);   // standard constructor
	~CFreeWeightDialog();
// Dialog Data
	//{{AFX_DATA(CFreeWeightDialog)
	enum { IDD = IDD_FREEWEIGHT_DIALOG };
	//CStatic	m_StatusStatic;
	CStatic	m_Com2DataStatic;
	CStatic	m_Com1DataStatic;
    CStatic fwBig;
    CStatic fwSmall;
    CStatic fwLabel;
	CButton	m_ButtonOK;
	//}}AFX_DATA
	int com1;
	int com2;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFreeWeightDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
CBrush   m_brBk;//在public中定义  
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFreeWeightDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnDestroy();


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FREEWEIGHTDIALOG_H__FE5C39E4_F2C4_49F7_96D5_612B2A759BE0__INCLUDED_)

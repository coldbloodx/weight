#if !defined(AFX_MATERIALMANAGEMENTDIALOG_H__2F86AEC9_59F6_4C07_9E03_85DB7926B3A2__INCLUDED_)
#define AFX_MATERIALMANAGEMENTDIALOG_H__2F86AEC9_59F6_4C07_9E03_85DB7926B3A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaterialManagementDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaterialManagementDialog dialog
#include "..\..\CustomColorDialog.h"
#include "afxwin.h"

class CMaterialManagementDialog : public CDialog
{
// Construction
public:
	CMaterialManagementDialog(CWnd* pParent = NULL);   // standard constructor
	~CMaterialManagementDialog();
	void initList();
// Dialog Data
	//{{AFX_DATA(CMaterialManagementDialog)
	enum { IDD = IDD_MATERIALMANAGEMENT_DIALOG };
	CStatic	m_StatusStatic;
	CButton	m_ButtonOK;
	CButton	m_Del;
	CButton	m_Add;
	CListCtrl	m_MaterialList;
	//}}AFX_DATA

	std::vector<CButton*> buttonVector;
	CBrush m_brBk;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaterialManagementDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

private:
	void initListHeader();

protected:

	// Generated message map functions
	//{{AFX_MSG(CMaterialManagementDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnMaterialadd();
	afx_msg void OnMaterialdel();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	CButton m_BatchNumberChange;
	afx_msg void OnBnClickedBatchnumberchange();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALMANAGEMENTDIALOG_H__2F86AEC9_59F6_4C07_9E03_85DB7926B3A2__INCLUDED_)

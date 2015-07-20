#if !defined(AFX_MATERIALADDDIALGO_H__9E557333_7815_4E8D_A686_06B7296A29C3__INCLUDED_)
#define AFX_MATERIALADDDIALGO_H__9E557333_7815_4E8D_A686_06B7296A29C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MaterialManagementDialog.h"
#include "..\..\CustomColorDialog.h"
// MaterialAddDialgo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaterialAddDialog dialog
#include "afxwin.h"


class CMaterialAddDialog : public CDialog
{
// Construction
public:
	CMaterialAddDialog(CWnd* pParent = NULL);   // standard constructor
	~CMaterialAddDialog();
// Dialog Data
	//{{AFX_DATA(CMaterialAddDialog)
	enum { IDD = IDD_MATERIALADD_DIALOG };
	CButton	m_ButtonOK;
	CButton	m_ButtonCancel;
	CEdit	m_MaterialName;
	CEdit	m_MaterialID;
	CMaterialManagementDialog* m_MaterialManageWindow;
	//}}AFX_DATA
	CBrush   m_brBk;//在public中定义  

	std::vector<CButton*> buttonVector;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaterialAddDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMaterialAddDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_BatchNumber;
	CEdit m_Manufacture;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALADDDIALGO_H__9E557333_7815_4E8D_A686_06B7296A29C3__INCLUDED_)

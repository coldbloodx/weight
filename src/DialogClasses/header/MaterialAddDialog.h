#if !defined(AFX_MATERIALADDDIALGO_H__9E557333_7815_4E8D_A686_06B7296A29C3__INCLUDED_)
#define AFX_MATERIALADDDIALGO_H__9E557333_7815_4E8D_A686_06B7296A29C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MaterialManagementDialog.h"

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

	enum { IDD = IDD_MATERIALADD_DIALOG };
	CButton	m_ButtonOK;
	CButton	m_ButtonCancel;
	CEdit	m_MaterialName;
	CEdit	m_MaterialID;
	CMaterialManagementDialog* m_MaterialManageWindow; 

	std::vector<CButton*> buttonVector;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
protected:


	virtual void OnOK();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_BatchNumber;
	CEdit m_Manufacture;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALADDDIALGO_H__9E557333_7815_4E8D_A686_06B7296A29C3__INCLUDED_)

#if !defined(AFX_QUERYDIALOG_H__1FC7BE5C_33CD_4A72_B380_4E72A5EB79B1__INCLUDED_)
#define AFX_QUERYDIALOG_H__1FC7BE5C_33CD_4A72_B380_4E72A5EB79B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryDialog dialog


class CQueryDialog : public CDialog
{
// Construction
public:
	CQueryDialog(CWnd* pParent = NULL);   // standard constructor
	~CQueryDialog();
	void initUserListHeader();
	void refreshUserList();

	void initFormulaListHeader();
	void refreshFormulaList();

	void initMaterialListHeader();
	void refreshMaterialList();

	void clearResultList();

// Dialog Data
	//{{AFX_DATA(CQueryDialog)
	enum { IDD = IDD_QUERY_DIALOG };
	CStatic	m_StatusStatic;
	CButton	m_ButtonCancel;
	CButton	m_Clear;
	CButton	m_Query;
	CListCtrl	m_ResultList;
	CEdit	m_Keyword;
	CComboBox	m_QueryIndex;
	CComboBox	m_QueryTable;
	//}}AFX_DATA

	std::vector<CButton*> buttonVector;

CBrush   m_brBk;//在public中定义  

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	


	// Generated message map functions
	//{{AFX_MSG(CQueryDialog)
	afx_msg void OnQuery();
	afx_msg void OnSelchangeQuerytableCombo();
	afx_msg void OnClearresultButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYDIALOG_H__1FC7BE5C_33CD_4A72_B380_4E72A5EB79B1__INCLUDED_)

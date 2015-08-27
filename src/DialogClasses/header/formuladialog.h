#if !defined(AFX_FORMULADIALOG_H__9ED02DD4_FFFD_4302_B88B_17B8C2391AB0__INCLUDED_)
#define AFX_FORMULADIALOG_H__9ED02DD4_FFFD_4302_B88B_17B8C2391AB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormulaDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormulaDialog dialog


class CFormulaDialog : public CDialog
{
// Construction
public:
	CFormulaDialog(CWnd* pParent = NULL);   // standard constructor
	~CFormulaDialog();
// Dialog Data
	//{{AFX_DATA(CFormulaDialog)
	enum { IDD = IDD_FORMULAMANAGEMENT_DIALOG };
	CStatic	m_StatusStatic;
	//}}AFX_DATA
	CListCtrl	m_FormulaListCtrl;
	std::vector<CButton*> buttonVector;
	CButton	m_ButtonOK;
	CButton*	m_FetchButton;
	CButton*	m_FormulaDel;
	CButton*	m_FormulaAdd;

	unsigned char	m_From;
public:
	void initListHeader();
	void initList();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormulaDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFormulaDialog)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFormulaAdd();
	afx_msg void OnFormulaDel();
	afx_msg	void OnFormulaFetch();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMULADIALOG_H__9ED02DD4_FFFD_4302_B88B_17B8C2391AB0__INCLUDED_)

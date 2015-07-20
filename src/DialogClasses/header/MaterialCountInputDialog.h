#if !defined(AFX_MATERIALCOUNTINPUTDIALOG_H__2D931014_2574_4968_A613_EC3068D9F2D8__INCLUDED_)
#define AFX_MATERIALCOUNTINPUTDIALOG_H__2D931014_2574_4968_A613_EC3068D9F2D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaterialCountInputDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaterialCountInputDialog dialog

class CMaterialCountInputDialog : public CDialog
{
// Construction
public:
	CMaterialCountInputDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMaterialCountInputDialog)
	enum { IDD = IDD_MATERIALCOUNTINPUT_DIALOG };
	CButton	m_ButtonCancel;
	CButton	m_ButtonOK;
	CEdit	m_MaterialCount;
	//}}AFX_DATA
	CBrush   m_brBk;//在public中定义  

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaterialCountInputDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMaterialCountInputDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALCOUNTINPUTDIALOG_H__2D931014_2574_4968_A613_EC3068D9F2D8__INCLUDED_)

#if !defined(AFX_STATISTICDIALOG_H__E5D75204_E142_4755_9008_1B709EE17E23__INCLUDED_)
#define AFX_STATISTICDIALOG_H__E5D75204_E142_4755_9008_1B709EE17E23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatisticDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatisticDialog dialog



class CStatisticDialog : public CDialog
{
// Construction
public:
	CStatisticDialog(CWnd* pParent = NULL);   // standard constructor
	~CStatisticDialog();
	void initListHeader();
	void refreshList();
// Dialog Data
	//{{AFX_DATA(CStatisticDialog)
	enum { IDD = IDD_STATISTIC_DIALOG };
	//CStatic	m_StatusStatic;
	CButton	m_ButtonOK;
	CButton	m_Query;
	CButton	m_Detail;
	CButton	m_Clear;
	CButton	m_All;
	CButton	m_Advance;
	CEdit	m_Keyword;
	CComboBox	m_Index;
	CListCtrl	m_StatisticList;
	//}}AFX_DATA

	CBrush   m_brBk;//在public中定义  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatisticDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatisticDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDetailrecordButton();
	afx_msg void OnClearButton();
	afx_msg void OnAllButton();
	afx_msg void OnQueryButton();
	afx_msg void OnAdvancequeryButton();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATISTICDIALOG_H__E5D75204_E142_4755_9008_1B709EE17E23__INCLUDED_)

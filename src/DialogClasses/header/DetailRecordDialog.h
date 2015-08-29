#if !defined(AFX_DETAILRECORDDIALOG_H__427478F7_7FAB_45B1_81B4_C01F17B5ACFB__INCLUDED_)
#define AFX_DETAILRECORDDIALOG_H__427478F7_7FAB_45B1_81B4_C01F17B5ACFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DetailRecordDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDetailRecordDialog dialog


class CDetailRecordDialog : public CDialog
{
// Construction
public:
	CDetailRecordDialog(CWnd* pParent = NULL);   // standard constructor
	~CDetailRecordDialog();

// Dialog Data
	//{{AFX_DATA(CDetailRecordDialog)
	enum { IDD = IDD_DETAILSRECORD_DIALOG };

	//}}AFX_DATA
	
	CStatic	m_StatusStatic;
	CButton m_ButtonOK;
	CStatic	m_Date;
	CStatic	m_FormulaID;
	CStatic	m_FormulaName;
	CStatic	m_Time;
	CStatic	m_UserName;
	CStatic	m_UserID;
	CButton	m_Print;
	std::vector<CStatic*> materialNameVector;
	std::vector<CStatic*> batchNumberVector;

	void divideMaterialInfo(std::string& materialInfo, std::string& materialName, std::string& batchNumber);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDetailRecordDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDetailRecordDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DETAILRECORDDIALOG_H__427478F7_7FAB_45B1_81B4_C01F17B5ACFB__INCLUDED_)

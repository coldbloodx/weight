#if !defined(AFX_FORMULAWEIGHDIALOG_H__89671AE4_8C16_45F8_B048_A8309DB1B28D__INCLUDED_)
#define AFX_FORMULAWEIGHDIALOG_H__89671AE4_8C16_45F8_B048_A8309DB1B28D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormulaWeighDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormulaWeighDialog dialog
#include "..\..\ExternClasses\header\BtnST.h"
#include "..\..\CustomColorDialog.h"
#include "afxwin.h"

class CFormulaWeighDialog : public CDialog
{
// Construction
public:
	CFormulaWeighDialog(CWnd* pParent = NULL);   // standard constructor
	~CFormulaWeighDialog();

	std::vector<CStatic*> materialNameVector;
	std::vector<CStatic*> materialWeighVector;
	std::vector<CButtonST*> sepWeightButtonVector;
	std::vector<CEdit*>	  batchNumberEditVector;
	std::vector<CEdit*>	  lineNumberEditVector;

	std::vector<CStatic*> weighedFlagVector;
	double totalWeigh;
	//CStatic m_StatusStatic;
	int m_FocusedID;
	std::vector<CString> lineNumberOld;
	std::vector<CString> manufactures;

	void refreshWeighedFlag();
	bool isWeighFinished();
// Dialog Data
	//{{AFX_DATA(CFormulaWeighDialog)
	enum { IDD = IDD_FORMULAWEIGH_DIALOG };
	CButtonST	m_ButtonOK;
	CButtonST	m_ButtonCancel;
	CButtonST	m_Button9;
	CButtonST	m_Button8;
	CButtonST	m_Button7;
	CButtonST	m_Button6;
	CButtonST	m_Button5;
	CButtonST	m_Button4;
	CButtonST	m_Button3;
	CButtonST	m_Button2;
	CButtonST	m_Button1;
	CButtonST	m_Button0;
	CButtonST	m_ButtonComma;
	CButtonST	m_ButtonBack;
	CStatic		m_MissionStatic;
	//}}AFX_DATA
	CBrush 	  m_brBk;   
	std::vector<CString> printVector;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormulaWeighDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFormulaWeighDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton0();
	afx_msg void OnButtonComma();
	afx_msg void OnButtonBack();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
	CButtonST m_buttonGoBack;
	afx_msg void OnBnClickedButtongoback();
	CStatic m_WeightStatic;
	CButton m_PrintCheck;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMULAWEIGHDIALOG_H__89671AE4_8C16_45F8_B048_A8309DB1B28D__INCLUDED_)

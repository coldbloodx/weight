#if !defined(AFX_WEIGHPERPACKDIALOG_H__899C4D47_5488_4ACC_A476_7EEB7762284D__INCLUDED_)
#define AFX_WEIGHPERPACKDIALOG_H__899C4D47_5488_4ACC_A476_7EEB7762284D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WeighPerPackDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWeighPerPackDialog dialog

#include "..\..\CustomColorDialog.h"
#include "afxwin.h"
class CWeighPerPackDialog : public CDialog
{
// Construction
public:
	CWeighPerPackDialog(CWnd* pParent = NULL);   // standard constructor
	~CWeighPerPackDialog();
// Dialog Data
	//{{AFX_DATA(CWeighPerPackDialog)
	enum { IDD = IDD_WEIGHPERPACK_DIALOG };
	//CStatic	m_StatusStatic;
	CButton	m_ButtonOK;
	CButton	m_ButtonCancel;
	CButton	m_Button9;
	CButton	m_Button8;
	CButton	m_Button7;
	CButton	m_Button6;
	CButton	m_Button5;
	CButton	m_Button4;
	CButton	m_Button3;
	CButton	m_Button2;
	CButton	m_Button1;
	CButton	m_Button0;
	CButton	m_ButtonComma;
	CButton	m_ButtonBack;
	CEdit	m_WeighPerPack;
	//}}AFX_DATA
	CBrush   m_brBk;//��public�ж���
	int m_FocusedID;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWeighPerPackDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWeighPerPackDialog)
	virtual void OnOK();
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
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_GrossWeight;
	CButton m_GoBack;
	afx_msg void OnBnClickedGobackbutton();
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEIGHPERPACKDIALOG_H__899C4D47_5488_4ACC_A476_7EEB7762284D__INCLUDED_)

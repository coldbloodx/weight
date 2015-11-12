#if !defined(AFX_FORMULAWEIGHDIALOG_H__89671AE4_8C16_45F8_B048_A8309DB1B28D__INCLUDED_)
#define AFX_FORMULAWEIGHDIALOG_H__89671AE4_8C16_45F8_B048_A8309DB1B28D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormulaWeighDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormulaWeighDialog dialog

#include "afxwin.h"

class CFormulaWeighDialog : public CDialog
{
// Construction
public:
	CFormulaWeighDialog(CWnd* pParent = NULL);   // standard constructor
	~CFormulaWeighDialog();

	std::vector<CStatic*> materialNameVector;
	std::vector<CStatic*> materialWeighVector;
	std::vector<CButton*> sepWeightButtonVector;
	std::vector<CEdit*>	  batchNumberEditVector;
	std::vector<CEdit*>	  lineNumberEditVector;
    std::vector<CButton*> skipCheckBoxVector;


	std::vector<CString> dbmname;
	std::vector<CString> dbmweigh;

	std::vector<CStatic*> weighedFlagVector;
	double totalWeigh;
	//CStatic m_StatusStatic;
	int focusId;
	std::vector<CString> lineNumberOld;
	std::vector<CString> manufactures;

	void refreshWeighedFlag();
	bool isWeighFinished();

	enum { IDD = IDD_FORMULAWEIGH_DIALOG };
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
	CStatic	m_MissionStatic;
	std::vector<CString> printVector;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

protected:

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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CStatic m_WeightStatic;
	CButton m_PrintCheck;
	CEdit editFBNumber;
	CStatic skipStatic;
	CStatic sRatio;
	CStatic sRealWeight;
};
#endif
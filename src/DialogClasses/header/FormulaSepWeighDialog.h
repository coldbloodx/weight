#if !defined(AFX_FORMULASEPWEIGHDIALOG_H__E7613D61_3C91_40DA_907D_2F98A13C3588__INCLUDED_)
#define AFX_FORMULASEPWEIGHDIALOG_H__E7613D61_3C91_40DA_907D_2F98A13C3588__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormulaSepWeighDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormulaSepWeighDialog dialog



#include "afxwin.h"

class CFormulaSepWeighDialog : public CDialog
{
// Construction
public:
	CFormulaSepWeighDialog(CWnd* pParent = NULL);   // standard constructor
	~CFormulaSepWeighDialog();
	CString materialWeigh;
	CString materialName;
// Dialog Data
	//{{AFX_DATA(CFormulaSepWeighDialog)

	//}}AFX_DATA

	enum { IDD = IDD_FORMULASEPWEIGH_DIALOG };
	CButton	m_ButtonDivide;
	//CButton	m_ButtonWeigh;
	CButton	m_ButtonOK;
	// //大称读数按钮
	CButton m_PriButton;
	// //小称读数按钮
	CButton m_SecButton;
	CButton m_CancalButton;

	CListBox m_Com1DisplayList;
	CListBox m_Com2DisplayList;

	CStatic	m_Com2Value;
	CStatic	m_Com1Value;

	CStatic	m_MaterialTotal;
	CStatic	m_PackNeeded;
	CStatic	m_WeightPerPack;
	CStatic	m_MaterialName;
	CStatic	m_FormulaWeigh;
	CStatic	m_FormulaName;
	CStatic m_StatusStatic;
	CStatic m_IsMultiTimeNeeded;
	CStatic m_AlreadyWeighed;
	CStatic m_WeighNeeded;
	CStatic m_IsMultiPackNeeded;
	CStatic m_PackWeight;
	CStatic m_RestNeeded;
	CButton ckMaterialPrint;

	bool bIsMultiPackFlag;
	bool bIsGrossedFlag;

	double dFormulaWeight;
	double dMaterialWeight;
	double dWeightNeeded;
	double dPackWeight;
	double dNetWeight;
	double dRestWeight;	
	double dAlreadyWeighed;
	
	int iTotalPacks;

	int com1;
	int com2;


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	virtual void OnOK();
	virtual BOOL OnInitDialog();


	afx_msg void OnTimer(UINT nIDEvent);

	afx_msg void OnDivideButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedPributton();
	afx_msg void OnBnClickedSecbutton();
	afx_msg void OnBnClickedCancel();

public:
		void updateMultiTimes();

};


#endif 

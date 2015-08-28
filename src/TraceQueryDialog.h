#pragma once
#include "afxwin.h"


// CTraceQueryDialog dialog

class CTraceQueryDialog : public CDialog
{
	DECLARE_DYNAMIC(CTraceQueryDialog)

public:
	CTraceQueryDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTraceQueryDialog();

// Dialog Data
	enum { IDD = IDD_TRACE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton4();
    CButton btnWorkOut;
    CButton btnMaterialAmount;
    CButton btnProductAmount;
    CButton btnTraceQuery;
    CButton btnOK;
    CButton btnCancel;
};

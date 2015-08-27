#pragma once
#include "afxcmn.h"


// CBarcodeManagemengDlg dialog

class CBarcodeManagemengDlg : public CDialog
{
	DECLARE_DYNAMIC(CBarcodeManagemengDlg)

public:
	CBarcodeManagemengDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBarcodeManagemengDlg();

// Dialog Data
	enum { IDD = IDD_BARCODE_MANAGEMENT };
    virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton10();
    afx_msg void OnBnClickedButton11();
    afx_msg void OnBnClickedButton1();
    CListCtrl resultlist;
};

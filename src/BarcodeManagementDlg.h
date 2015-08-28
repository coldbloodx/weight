#pragma once
#include "afxcmn.h"


// CBarcodeManagemengDlg dialog

class CBarcodeManagementDlg : public CDialog
{
	DECLARE_DYNAMIC(CBarcodeManagementDlg)

public:
	CBarcodeManagementDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBarcodeManagementDlg();

// Dialog Data
	enum { IDD = IDD_BARCODE_MANAGEMENT };
    virtual BOOL OnInitDialog();

	void initlistctrl();
    void initlistheader();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton10();
    afx_msg void OnBnClickedButton11();
    afx_msg void OnBnClickedButton1();
    CListCtrl resultlist;
};

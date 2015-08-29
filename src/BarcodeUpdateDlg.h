#pragma once
#include "afxwin.h"


// CBarcodemanagementDlg dialog

class CBarcodeUpdateDlg : public CDialog
{
	DECLARE_DYNAMIC(CBarcodeUpdateDlg)

public:
	CBarcodeUpdateDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBarcodeUpdateDlg();

// Dialog Data
	enum { IDD = IDD_BARCODE_UPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CButton m_ButtonOK;
	CButton m_ButtonCancel;
	BOOL bAddFlag;
	CEdit barcode;
	CEdit manufacture;
	CString origbarcode;
    CString barcodeid;
};
#pragma once

#pragma once


#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CProductTraceDlg dialog

class CProductTraceDlg : public CDialog
{
	DECLARE_DYNAMIC(CProductTraceDlg)

public:
	CProductTraceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProductTraceDlg();

// Dialog Data
	enum { IDD = IDD_PRODUCT_TRACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CComboBox cbxProductBatch;
    CListCtrl listProduct;
    CListCtrl listMaterial;
    afx_msg void OnBnClickedOk();
    afx_msg BOOL OnInitDialog();
    afx_msg void OnNMClickProductList(NMHDR *pNMHDR, LRESULT *pResult);

    void updatemlist();

    afx_msg void OnNMDblclkProductList(NMHDR *pNMHDR, LRESULT *pResult);
};

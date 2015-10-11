#pragma once


// CQueryCondDialog dialog

#include "constants.h"
#include "afxwin.h"
#include "afxdtctl.h"
class CQueryCondDialog : public CDialog
{
	DECLARE_DYNAMIC(CQueryCondDialog)

public:
	CQueryCondDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CQueryCondDialog();
    QUERYTYPE qtype;
	TIMESECTION getTimeSection(CString timeSection);

// Dialog Data
	enum { IDD = IDD_QUERYCOND_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    CButton btnOK;
    CButton btnCancel;
    CStatic lbQueryLabel;
    CComboBox cboTimeSetion;
    CDateTimeCtrl dateStart;
    CDateTimeCtrl dateEnd;
    CComboBox cboQueryItem;
    afx_msg void OnBnClickedOk();
	CStatic sCaution;
};

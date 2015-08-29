#pragma once


// CQueryResultDialog dialog
#include "constants.h"
#include "afxcmn.h"
#include "afxwin.h"
class CQueryResultDialog : public CDialog
{
	DECLARE_DYNAMIC(CQueryResultDialog)

public:
	CQueryResultDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CQueryResultDialog();
    
	CString key;
	
	QUERYTYPE qtype;
	TIMESECTION timetype;

	
	CTime timeStart;
	CTime timeEnd;

// Dialog Data
	enum { IDD = IDD_QUERY_RESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    CListCtrl ctlResultList;
    CButton btnCancel;
};

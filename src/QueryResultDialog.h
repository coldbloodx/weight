#pragma once


// CQueryResultDialog dialog
#include "constants.h"
class CQueryResultDialog : public CDialog
{
	DECLARE_DYNAMIC(CQueryResultDialog)

public:
	CQueryResultDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CQueryResultDialog();
    QUERYTYPE qtype;

// Dialog Data
	enum { IDD = IDD_QUERY_RESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

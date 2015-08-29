// QueryResultDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "QueryResultDialog.h"
#include "uiFunctions.h"
#include "helperclass.h"


// CQueryResultDialog dialog

IMPLEMENT_DYNAMIC(CQueryResultDialog, CDialog)

CQueryResultDialog::CQueryResultDialog(CWnd* pParent /*=NULL*/)
: CDialog(CQueryResultDialog::IDD, pParent)
{

}

CQueryResultDialog::~CQueryResultDialog()
{
}

void CQueryResultDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ctlResultList);
	DDX_Control(pDX, IDCANCEL, btnCancel);
}


BEGIN_MESSAGE_MAP(CQueryResultDialog, CDialog)
END_MESSAGE_MAP()

BOOL CQueryResultDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	uiFunctions::setdlgsize(this, &btnCancel);

	unsigned long startsecs = HelperFunctions::time2gmt(timeStart);
	unsigned long endsecs = HelperFunctions::time2gmt(timeEnd);

	CString starttimestr;
	CString endtimestr;

	CString timesqlstr;

	switch(timetype)
	{
	case TTYPE_BEFORE:
		timesqlstr = " gmt <= " + starttimestr;	
		break;

	case TTYPE_AFTER:
		timesqlstr = " gmt >= " + starttimestr;
		break;

	case TTYPE_BETWEEN:
		timesqlstr = " gmt >= " + starttimestr + " and gmt <= " + endtimestr;
		break;

	case TTYPE_BEYOND:
		timesqlstr = " gmt <= " + starttimestr + " and gmt >= " + endtimestr;
		break;
	}

	CString sql;
	vector<CString> headervec;

	switch(qtype)
	{
	case QTYPE_USERWORKOUT:
		{
			sql.Format("select username, formulaname, amount, date, time from weight where username = '%s' and %s", key, timesqlstr);
			CString headerarray[5] = {"username", "formulaname", "amount", "date", "time"};
			headervec.assign(headerarray, headerarray + 5);	
		}

		break;

	case QTYPE_MATERIAMOUNT:
		{
			sql.Format("select * from materials where materialname = '%s' and %s", key, timesqlstr);
		}

		break;

	case QTYPE_PRODUCTAMOUNT:
		{
			sql.Format("select username, formulaname, amount, date, time from weight where formulaname = '%s' and %s", key, timesqlstr);
			CString headerarray[5] = {"username", "formulaname", "amount", "date", "time"};
			headervec.assign(headerarray, headerarray + 5);	
		}
		break;

	}

	return TRUE;
}


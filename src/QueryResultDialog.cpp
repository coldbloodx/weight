// QueryResultDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "QueryResultDialog.h"
#include "uiFunctions.h"
#include "helperclass.h"
#include "DBptr.h"


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
	uiutils::setdlgsize(this, &btnCancel);

	unsigned long startsecs = utils::time2gmt(timeStart);
	unsigned long endsecs = utils::time2gmt(timeEnd);

	CString timesqlstr;

	switch(timetype)
	{
	case TTYPE_BEFORE:
		timesqlstr.Format(" gmt <= %ld ", startsecs);
		break;

	case TTYPE_AFTER:

		timesqlstr.Format(" gmt >= %ld ", startsecs);
		break;

	case TTYPE_BETWEEN:
		timesqlstr.Format(" gmt >= %ld and gmt <= %ld", startsecs, endsecs);
		break;

	case TTYPE_BEYOND:
		timesqlstr.Format("gmt <= %ld or gmt >= %ld", startsecs, endsecs);
		break;
	}

	CString sql;
	vector<CString> headervec;

	switch(qtype)
	{
	case QTYPE_USERWORKOUT:
		{
			sql.Format("select username, formulaname, amount, odate, otime from weight where username = '%s' and %s", key, timesqlstr);
			CString headerarray[5] = {"用户名", "配方名称", "数量", "日期", "时间"};
			headervec.assign(headerarray, headerarray + 5);	
		}

		break;

	case QTYPE_MATERIAMOUNT:
		{
			sql.Format("select  materialname, materialbatchnumber, formulaname, formula_batch_number, operatorname, amount, operate_date, operate_time from materialrecords where materialname = '%s' and %s", key, timesqlstr);
            CString headerarray [8] = {"材料名称", "材料批号", "配方名称", "配方批号", "用户名", "数量", "日期", "时间"};
            headervec.assign(headerarray, headerarray + 8);
		}

		break;

	case QTYPE_PRODUCTAMOUNT:
		{
			sql.Format("select username, formulaname, amount, odate, otime from weight where formulaname = '%s' and %s", key, timesqlstr);
			CString headerarray[5] = {"用户名", "配方名称", "数量", "日期", "时间"};
			headervec.assign(headerarray, headerarray + 5);	
		}
		break;

	}

    uiutils::initlistheader(headervec, ctlResultList);

	_RecordsetPtr dbptr = SQLExecutor::getInstancePtr()->execquery(sql);

	uiutils::updatelist(dbptr, ctlResultList, headervec);
	return TRUE;
}


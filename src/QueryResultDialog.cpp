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
	DDX_Control(pDX, IDC_STATIC_SUM, sSum);
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
	vector<CString> headercol;

	CString csSum;

	switch(qtype)
	{
	case QTYPE_USERWORKOUT:
		{
			csSum = "员工工作总量：";
			if(key.IsEmpty())
			{
				sql.Format("select username, formulaname, amount, odate, otime from weight where %s order by gmt desc", timesqlstr);
			}
			else
			{
				sql.Format("select username, formulaname, amount, odate, otime from weight where username = '%s' and %s order by gmt desc", key, timesqlstr);
			}
			CString headerarray[5] = {"用户名", "配方名称", "数量", "日期", "时间"};
			headervec.assign(headerarray, headerarray + 5);	
			CString cols[5] = {"username", "formulaname", "amount", "odate", "otime"};
			headercol.assign(cols, cols + 5);

		}

		break;

	case QTYPE_MATERIAMOUNT:
		{
			csSum = "材料总用量：";
			if(key.IsEmpty())
			{
				sql.Format("select  materialname, materialbatchnumber, formulaname, formula_batch_number, operatorname, amount, operate_date, operate_time from materialrecords where %s order by gmt desc", timesqlstr);

			}
			else
			{
				sql.Format("select  materialname, materialbatchnumber, formulaname, formula_batch_number, operatorname, amount, operate_date, operate_time from materialrecords where materialname = '%s' and %s order by gmt desc", key, timesqlstr);
			}
			CString headerarray [8] = {"材料名称", "材料批号", "配方名称", "配方批号", "用户名", "数量", "日期", "时间"};
			headervec.assign(headerarray, headerarray + 8);
			CString cols[8] = {"materialname", "materialbatchnumber", "formulaname", "formula_batch_number", 
				"operatorname", "amount", "operate_date", "operate_time"};
			headercol.assign(cols, cols + 8);
		}

		break;

	case QTYPE_PRODUCTAMOUNT:
		{
			csSum = "产品总产量：";
			if(key.IsEmpty())
			{
				sql.Format("select username, formulaname, amount, odate, otime from weight where %s order by gmt desc", timesqlstr);
			}
			else
			{
				sql.Format("select username, formulaname, amount, odate, otime from weight where formulaname = '%s' and %s order by gmt desc", key, timesqlstr);
			}
			CString headerarray[5] = {"用户名", "配方名称", "数量", "日期", "时间"};
			headervec.assign(headerarray, headerarray + 5);	
			CString cols[5] = {"username", "formulaname", "amount", "odate", "otime"};
			headercol.assign(cols, cols + 5);
		}
		break;

	}

	uiutils::initlistheader(headervec, ctlResultList);

	_RecordsetPtr dbptr = SQLExecutor::getInstancePtr()->execquery(sql);

	if(!dbptr->adoEOF)
	{
		uiutils::updatelist(dbptr, ctlResultList, headercol);

		double sum = utils::sumdbcol(dbptr, "amount");

		sSum.SetWindowText(csSum + utils::double2cstr(sum));
	}
	else
	{
		sSum.SetWindowText(csSum + utils::double2cstr(0.0));
	}
	return TRUE;
}


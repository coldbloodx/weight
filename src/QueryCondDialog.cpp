// QueryCondDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "QueryCondDialog.h"
#include "uiFunctions.h"
#include "helperclass.h"
#include "DBptr.h"
#include "QueryResultDialog.h"


// CQueryCondDialog dialog

IMPLEMENT_DYNAMIC(CQueryCondDialog, CDialog)

BEGIN_MESSAGE_MAP(CQueryCondDialog, CDialog)
    ON_BN_CLICKED(IDOK, &CQueryCondDialog::OnBnClickedOk)
END_MESSAGE_MAP()

CQueryCondDialog::CQueryCondDialog(CWnd* pParent /*=NULL*/)
: CDialog(CQueryCondDialog::IDD, pParent){}

CQueryCondDialog::~CQueryCondDialog(){}

void CQueryCondDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDOK, btnOK);
    DDX_Control(pDX, IDCANCEL, btnCancel);
    DDX_Control(pDX, IDC_QUERY_LABEL, lbQueryLabel);
    DDX_Control(pDX, IDC_TIMESECTION_COMBO, cboTimeSetion);
    DDX_Control(pDX, IDC_DATE_START, dateStart);
    DDX_Control(pDX, IDC_DATE_END, dateEnd);
    DDX_Control(pDX, IDC_QUERY_ITEM, cboQueryItem);
}

BOOL CQueryCondDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    uiutils::setdlgsize(this, &btnCancel, &btnOK);

    CString sql;

    switch(qtype)
    {
    case QTYPE_USERWORKOUT:
        this->SetWindowText("工作量查询");
        lbQueryLabel.SetWindowText("员工姓名:");
		sql = "select name from users;";
        break;
    case QTYPE_MATERIAMOUNT:
        this->SetWindowText("材料用量查询");
        lbQueryLabel.SetWindowText("材料名:");
		sql = "select name from materials;";
        break;
    case QTYPE_PRODUCTAMOUNT:
        this->SetWindowText("成品总量查询");
        lbQueryLabel.SetWindowText("配方名称：");
		sql = "select name from formulas;";
        break;

    default:
        AfxMessageBox("请选择查询选项");
        return TRUE;
        break;
    }

    //set time to before
    cboTimeSetion.SetCurSel(0);

    _RecordsetPtr dbptr = SQLExecutor::getInstancePtr()->execquery(sql);

    uiutils::fillcombo(dbptr, cboQueryItem, CString("name"));

    if(cboQueryItem.GetCount())
    {
        cboQueryItem.SetCurSel(0);
    }

    return TRUE;
}

void CQueryCondDialog::OnBnClickedOk()
{
	// get query type
    CQueryResultDialog resultDlg;
    resultDlg.qtype = this->qtype;


	// get query key
	CString key;
	cboQueryItem.GetWindowText(key);
	resultDlg.key = key;

	// get time section type
	CString timesection;
	cboTimeSetion.GetWindowText(timesection);
	TIMESECTION ttype = this->getTimeSection(timesection);
	resultDlg.timetype = ttype;

	// get start time and end time
	CTime tStartTime;
	CTime tEndTime;
	dateStart.GetTime(tStartTime);
	dateEnd.GetTime(tEndTime);

	resultDlg.timeStart = tStartTime;
	resultDlg.timeEnd = tEndTime;

    resultDlg.DoModal();
    OnOK();
}


TIMESECTION CQueryCondDialog::getTimeSection(CString timeSection)
{
	if (timeSection == "之前")
	{
		return TTYPE_BEFORE;
	} 
	else if (timeSection == "之后")
	{
		return TTYPE_AFTER;
	}
	else if (timeSection == "之间")
	{
		return TTYPE_BETWEEN;
	}
	else if (timeSection == "两端")
	{
		return TTYPE_BEYOND;
	}
	else
	{
		return TTYPE_END;
	}
}
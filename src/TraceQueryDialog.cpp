// TraceQueryDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "TraceQueryDialog.h"
#include "uiFunctions.h"
#include "QueryCondDialog.h"
#include "ProductTraceDlg.h"
#include "constants.h"
#include "helperclass.h"
#include "dbptr.h"
#include <odbcinst.h>


IMPLEMENT_DYNAMIC(CTraceQueryDialog, CDialog)

CTraceQueryDialog::CTraceQueryDialog(CWnd* pParent /*=NULL*/)
: CDialog(CTraceQueryDialog::IDD, pParent)
{

}

CTraceQueryDialog::~CTraceQueryDialog()
{
}

void CTraceQueryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, btnWorkOut);
	DDX_Control(pDX, IDC_BUTTON2, btnMaterialAmount);
	DDX_Control(pDX, IDC_BUTTON3, btnProductAmount);
	DDX_Control(pDX, IDC_BUTTON4, btnTraceQuery);
	DDX_Control(pDX, IDOK, btnOK);
	DDX_Control(pDX, IDCANCEL, btnCancel);
	DDX_Control(pDX, IDC_BUTTON5, btnExport);
}


BEGIN_MESSAGE_MAP(CTraceQueryDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CTraceQueryDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTraceQueryDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTraceQueryDialog::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTraceQueryDialog::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTraceQueryDialog::OnBnClickedButton5)
END_MESSAGE_MAP()

//工作量统计

void CTraceQueryDialog::OnBnClickedButton1()
{
	CQueryCondDialog conddlg;
	conddlg.qtype = QTYPE_USERWORKOUT;
	conddlg.DoModal();
}

//物料使用统计
void CTraceQueryDialog::OnBnClickedButton2()
{
	CQueryCondDialog conddlg;
	conddlg.qtype = QTYPE_MATERIAMOUNT;
	conddlg.DoModal();
}

//成品数量统计
void CTraceQueryDialog::OnBnClickedButton3()
{
	CQueryCondDialog conddlg;
	conddlg.qtype = QTYPE_PRODUCTAMOUNT;
	conddlg.DoModal();
}

//追溯查询
void CTraceQueryDialog::OnBnClickedButton4()
{
	//not done yet
	CProductTraceDlg pdlg;
	pdlg.DoModal();
}


BOOL CTraceQueryDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CButton* btnarray[6] = {&btnWorkOut, &btnMaterialAmount, &btnProductAmount, 
		&btnTraceQuery, &btnExport, &btnCancel};
	uiutils::init2rowbtns(btnarray, 6);
	btnOK.ShowWindow(FALSE);
	uiutils::setdlgsize(this);

	return TRUE;
}

void CTraceQueryDialog::OnBnClickedButton5()
{
	CString timestamp = utils::gettimestamp();
	CString defaultname = "record" + timestamp;
	CFileDialog savedlg(FALSE, "xls", defaultname, OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST, 
		"excel文件 (*.xls)");
	if (savedlg.DoModal() != IDOK)
	{
		return;
	}
	CString filename = savedlg.GetPathName();

	// sql
	CString asqlarray[3] = {"select formulaid, formulaname, username, amount, odate, otime, fbatchnumber from weight" ,
		"select formulaid, formulaname, operatorname, amount, odate, otime from fetchrecords",
		"select materialname, materialbatchnumber, formulaid, formulaname, operatorname, amount, operate_date, operate_time from materialrecords"};

	// xheaders
	CString weighheaders[7] = { "配方id","配方名称", "用户名", "数量", "日期", "时间", "产品批号"};
	CString fetchheaders[6] = { "配方id","配方名称", "用户名", "数量", "日期", "时间"};
	CString materialheaders[8] ={ "材料名称", "材料批号", "配方id", "配方名称", "用户名", "数量", "日期", "时间"};

	vector<CString> weighheadervec(weighheaders, weighheaders+7);
	vector<CString> fetchhheadervec(fetchheaders, fetchheaders+6);
	vector<CString> materialheadervec(materialheaders, materialheaders+8);

	vector< vector<CString> > xheaders ;
	xheaders.push_back(weighheadervec);
	xheaders.push_back(fetchhheadervec);
	xheaders.push_back(materialheadervec);

	// aheaders
	CString aweightheaders[7] = {"formulaid", "formulaname", "username", "amount", "odate", "otime", "fbatchnumber"};
	CString afetchheaders[6] = {"formulaid", "formulaname", "operatorname", "amount", "odate", "otime"};
	CString amaterialheaders[8] = {"materialname", "materialbatchnumber", "formulaid", "formulaname", "operatorname",
			"amount", "operate_date", "operate_time"};

	vector<CString> aweightheadervec(aweightheaders, aweightheaders + 7);
	vector<CString> afetchheadervec(afetchheaders, afetchheaders + 6);
	vector<CString> amaterialheadervec(amaterialheaders, amaterialheaders + 8);

	vector< vector<CString> > aheaders;
	aheaders.push_back(aweightheadervec);
	aheaders.push_back(afetchheadervec);
	aheaders.push_back(amaterialheadervec);

	// table name
	CString atablenamearray[3] = {"weight", "fetchrecords", "materialrecords"};
	CString xtablenamearray[3] = {"称量纪录", "领取记录", "材料记录"}; 

	//create exceldb
	CDatabase database;
	CString xdriver = "MICROSOFT EXCEL DRIVER (*.XLS)"; // Excel安装驱动

	CString xsql;
	xsql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",xdriver, filename, filename);

	// create excel file
	if( database.OpenEx(xsql,CDatabase::noOdbcDialog) )
	{

		for(int i = 0; i < 3; ++i)
		{
			_RecordsetPtr dbptr = SQLExecutor::getInstancePtr()->execquery(asqlarray[i]);

			// create excel work sheet
			xsql = getSheetSchemaStr(xheaders[i], xtablenamearray[i]);//可以用中文表示序号，姓名，年龄等
			database.ExecuteSQL(xsql);

			dbptr2sheet(dbptr, database, aheaders[i], xheaders[i], xtablenamearray[i]);
		}
	}

	// close excel file
	database.Close();

}

void CTraceQueryDialog::dbptr2sheet(_RecordsetPtr &dbptr, CDatabase& database, vector<CString>& aheaders,
									vector<CString>& xheaders, CString xtable)
{
	try
	{
		CString keys = joinvec(xheaders, ", ");
		while(!dbptr->adoEOF)
		{
			CString xsql;
			vector<CString> record;
			for (size_t i = 0; i < aheaders.size(); ++i )
			{
				_variant_t vcol = dbptr->GetCollect(_variant_t(aheaders[i]));
				CString col;
				//取出某个字段的数据
				if (vcol.vt != VT_NULL)
				{
					col = (LPCTSTR)(_bstr_t)vcol;
					record.push_back(col);
				}
				else
				{
					record.push_back(" ");
				}
			}
			CString values = joinvec(record, "' , '");
			xsql.Format("insert into %s ( %s ) values ( '%s')", xtable, keys, values);
			database.ExecuteSQL(xsql);
			dbptr->MoveNext();
		}
	}
	catch (_com_error& e)
	{
		throw e;
	}
	return;
}

CString CTraceQueryDialog::joinvec( vector<CString> &vec, CString token )
{
	CString ret;
	for (size_t i = 0; i < vec.size(); ++i )
	{
		ret += vec[i];
		if( i == vec.size() - 1 )
		{
			break;
		}
		ret += token;
	}	return ret;
}

CString CTraceQueryDialog::getSheetSchemaStr(vector<CString> headers, CString sheetname)
{
	CString ret, headerstr;
	headerstr = joinvec(headers, " text , ");
	headerstr += " text";
	ret.Format("create table %s ( %s )", sheetname, headerstr); 
	
	return ret;
}
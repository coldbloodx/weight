// FetchRecordDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "FetchRecordDialog.h"
#include "FetchRecordsAdvanceQueryDialog.h"
#include "HelperClass.h"
#include "DBConnector.h"
#include "RecordSetPointer.h"
#include "uiFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFetchRecordDialog dialog


CFetchRecordDialog::CFetchRecordDialog(CWnd* pParent /*=NULL*/)
: CDialog(CFetchRecordDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFetchRecordDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFetchRecordDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFetchRecordDialog)
	//DDX_Control(pDX, IDC_STATUS_STATIC2, m_StatusStatic);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_QUERY_BUTTON, m_QueryButton);
	DDX_Control(pDX, IDC_PRINT_BUTTON, m_PrintButton);
	DDX_Control(pDX, IDC_FETCHRECORDCLEAR_BUTTON, m_ClearButton);
	DDX_Control(pDX, IDC_ALL_BUTTON, m_AllButton);
	DDX_Control(pDX, IDC_ADVANCEQUERY_BUTTON, m_ButtonAdvanceQuery);
	DDX_Control(pDX, IDC_KEYWORD_EDIT, m_Keyword);
	DDX_Control(pDX, IDC_INDEX_COMBO, m_Index);
	DDX_Control(pDX, IDC_FETCHRECORD_LIST, m_FetchRecordList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFetchRecordDialog, CDialog)
//{{AFX_MSG_MAP(CFetchRecordDialog)
	ON_BN_CLICKED(IDC_PRINT_BUTTON, OnPrintButton)
	ON_BN_CLICKED(IDC_FETCHRECORDCLEAR_BUTTON, OnFetchrecordclearButton)
	ON_BN_CLICKED(IDC_QUERY_BUTTON, OnQueryButton)
	ON_BN_CLICKED(IDC_ADVANCEQUERY_BUTTON, OnAdvancequeryButton)
	ON_BN_CLICKED(IDC_ALL_BUTTON, OnAllButton)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFetchRecordDialog message handlers

BOOL CFetchRecordDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initListHeader();
	initList();
	
	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_FETCHRECORD);//载入图片   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();   
	

	CRect wndRect((1024 - 960) / 2, (768 - 583) / 2, (1024 - 960) / 2 + 960, (768 - 583) / 2 + 595 );
	this->MoveWindow(wndRect);

	CRect queryRect(283, 467, 376, 505);
	m_QueryButton.MoveWindow(queryRect);

	CRect advanceRect(417, 467, 510, 505);
	m_ButtonAdvanceQuery.MoveWindow(advanceRect);

	CRect backRect(170, 462, 257, 484);
	m_ButtonOK.MoveWindow(backRect);

	CRect clearRect(552, 467, 644, 505);
	m_ClearButton.MoveWindow(clearRect);

	CRect printRect(819, 467, 913, 505);
	m_PrintButton.MoveWindow(printRect);

	CRect allRect(684, 467, 778, 505);
	m_AllButton.MoveWindow(allRect);

	CRect listRect(256, 103, 924, 463);
	m_FetchRecordList.MoveWindow(listRect);


	CButton* buttonArray[6] = {&m_ButtonAdvanceQuery, &m_ClearButton, &m_AllButton, &m_QueryButton, &m_PrintButton, &m_ButtonOK};
	
	std::vector<CButton*> buttonVector(buttonArray, buttonArray + 6);

    uiFunctions::setdlgsize(this);
	
	//HelperFunctions::showStatus(m_StatusStatic);
	SetTimer(1000,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CFetchRecordDialog::initList()
{
	m_FetchRecordList.DeleteAllItems();
	
	CString sqlState = "SELECT * FROM FETCHRECORDS";

	//init recordset pointer
	SQLExecutor::getInstanceRef().setDatabaseConnection(DBConnector::getInstanceRef().getdbcon());
	SQLExecutor::getInstanceRef().setSqlState(sqlState);

	//exec SQL state
	try
	{
		SQLExecutor::getInstanceRef().execSQL() ;
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	//get the result data set
	_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().getRecordPtr();

	CString headerArray[8] = {"ID", "FORMULAID", "FORMULANAME", "OPERATORID", "OPERATORNAME", "AMOUNT","DATE", "TIME" };
	headerList.assign(headerArray, headerArray + 8);

	uiFunctions::updateList(m_pRecordset, m_FetchRecordList, headerList);

	return;
}

void CFetchRecordDialog::initListHeader()
{	
	CString headerArray[8] = {"流水编号","配方编号", "配方名称","用户编号","用户姓名","领取数量","操作日期","操作时间"};

	headerVector.assign(headerArray, headerArray+8);
	for (size_t i = 0; i < headerVector.size(); ++i)
	{
		m_FetchRecordList.InsertColumn(i,headerVector[i], 0, 160);
	}
}

void CFetchRecordDialog::OnPrintButton() 
{
	// TODO: Add your control notification handler code here
	if (m_FetchRecordList.GetFirstSelectedItemPosition() == NULL)
	{
		AfxMessageBox("请在领取列表中选中要打印的领取记录！");
		return;
	}

	POSITION pos = m_FetchRecordList.GetFirstSelectedItemPosition() -1 ;

	CString ID = m_FetchRecordList.GetItemText(((int)pos), 0);


	CString sqlState = "SELECT * FROM FETCHRECORDS WHERE ID = " + ID;

	//init recordset pointer
	SQLExecutor::getInstanceRef().setDatabaseConnection(DBConnector::getInstanceRef().getdbcon());
	SQLExecutor::getInstanceRef().setSqlState(sqlState);

	//exec SQL state
	try
	{
		SQLExecutor::getInstanceRef().execSQL() ;
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
		return;
	}
	
	_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().getRecordPtr();
	
	HelperFunctions::updateRecordValueVector(m_pRecordset, valueList, headerList);

	//打印两张领料记录
	HelperFunctions::printVector(CString("成品领取记录"), headerVector, valueList);
	HelperFunctions::printVector(CString("成品领取记录"), headerVector, valueList);

	valueList.clear();
	return;
}

void CFetchRecordDialog::OnFetchrecordclearButton() 
{
	// TODO: Add your control notification handler code here
	m_FetchRecordList.DeleteAllItems();
	
}

void CFetchRecordDialog::OnQueryButton() 
{
	// TODO: Add your control notification handler code here
		CString index, keyword;

	m_Index.GetWindowText(index);
	m_Keyword.GetWindowText(keyword);

	if (index.IsEmpty() || keyword.IsEmpty())
	{
		AfxMessageBox("索引或者关键字不能为空");
		return;
	}

	m_FetchRecordList.DeleteAllItems();
	
	CString fieldName;		

	if (index == "配方编号")
	{
		fieldName = "FORMULAID";
	}
	if (index == "配方名称")
	{
		fieldName = "FORMULANAME";
	}
	if (index == "人员编号" )
	{
		fieldName = "OPERATORID";
	}
	if (index == "人员名称")
	{
		fieldName = "OPERATORNAME";
	}

	CString sqlState("SELECT ID, FORMULAID, FORMULANAME, OPERATORID, OPERATORNAME, AMOUNT, DATE, TIME FROM FETCHRECORDS WHERE ") ;
	sqlState += fieldName ;

	if (index == "配方编号" || index == "人员编号" )
	{
		sqlState +=  " = " + keyword;
	}
	else if (index == "人员名称" || index == "配方名称")
	{
		sqlState +=  " = '" + keyword + "'";
	}
	else
	{
		sqlState += "datediff(\"d\", '"+keyword+"',DATE)";
	}

	//init recordset pointer
	SQLExecutor::getInstanceRef().setDatabaseConnection(DBConnector::getInstanceRef().getdbcon());
	SQLExecutor::getInstanceRef().setSqlState(sqlState);

	//exec SQL state
	try
	{
		SQLExecutor::getInstanceRef().execSQL() ;
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
		return;
	}
	
	//get the result data set
	_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().getRecordPtr();


	CString headerArray[8] = {"ID", "FORMULAID", "FORMULANAME", "OPERATORID", "OPERATORNAME", "AMOUNT","DATE", "TIME" };
	std::vector<CString> headerList(headerArray, headerArray + 8);

	uiFunctions::updateList(m_pRecordset, m_FetchRecordList, headerList);
}

void CFetchRecordDialog::OnAdvancequeryButton() 
{
	// TODO: Add your control notification handler code here
	CFetchRecordsAdvanceQueryDialog fetchRecordsAdvanceQueryDialog;
	SingletonHelper::getInstance()->setPtrData((void*)this);
	fetchRecordsAdvanceQueryDialog.DoModal();
}

void CFetchRecordDialog::OnAllButton() 
{
	// TODO: Add your control notification handler code here
	initList();
}


CFetchRecordDialog::~CFetchRecordDialog()
{

}

void CFetchRecordDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}

HBRUSH CFetchRecordDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if   (pWnd == this)   
	{   
		return m_brBk;   
	}   
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

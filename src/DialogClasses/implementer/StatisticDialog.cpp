// StatisticDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "StatisticDialog.h"
#include "DetailRecordDialog.h"
#include "FormulaAdvanceQueryDialog.h"
#include "HelperClass.h"
#include "DBConnector.h"
#include "DBptr.h"
#include "uiFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatisticDialog dialog


CStatisticDialog::CStatisticDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStatisticDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatisticDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStatisticDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatisticDialog)
	//DDX_Control(pDX, IDC_STATUS_STATIC, m_StatusStatic);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_QUERY_BUTTON, m_Query);
	DDX_Control(pDX, IDC_DETAILRECORD_BUTTON, m_Detail);
	DDX_Control(pDX, IDC_CLEAR_BUTTON, m_Clear);
	DDX_Control(pDX, IDC_ALL_BUTTON, m_All);
	DDX_Control(pDX, IDC_ADVANCEQUERY_BUTTON, m_Advance);
	DDX_Control(pDX, IDC_KEYWORD_EDIT, m_Keyword);
	DDX_Control(pDX, IDC_INDEX_COMBO, m_Index);
	DDX_Control(pDX, IDC_STATISTIC_LIST, m_StatisticList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStatisticDialog, CDialog)
	//{{AFX_MSG_MAP(CStatisticDialog)
	ON_BN_CLICKED(IDC_DETAILRECORD_BUTTON, OnDetailrecordButton)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, OnClearButton)
	ON_BN_CLICKED(IDC_ALL_BUTTON, OnAllButton)
	ON_BN_CLICKED(IDC_QUERY_BUTTON, OnQueryButton)
	ON_BN_CLICKED(IDC_ADVANCEQUERY_BUTTON, OnAdvancequeryButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatisticDialog message handlers

BOOL CStatisticDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//HelperFunctions::showStatus(m_StatusStatic);
	initListHeader();
	refreshList();

	CButton* buttonArray[6] = {&m_Clear,&m_ButtonOK,&m_Query,&m_Advance,&m_All,&m_Detail};
	std::vector<CButton*> buttonVector(buttonArray, buttonArray+6);

	uiutils::setdlgsize(this, &m_ButtonOK);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatisticDialog::initListHeader()
{

	std::string headerArray[] = {"���","�䷽���","�䷽����","��Ա���","��Ա����","����","��������","����ʱ��","��ע"};

	std::vector<std::string> headerList(headerArray, headerArray + 9);
	for (int i = 0; i< (int)headerList.size(); ++i)
	{
		m_StatisticList.InsertColumn(i,headerList[i].c_str(), 0, 80);
	}
}

void CStatisticDialog::refreshList()
{
	m_StatisticList.DeleteAllItems();

	//init recordset pointer
	SQLExecutor::getInstanceRef().setSqlState(CString("SELECT * FROM WEIGHT"));

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

	CString headerArray[9] = {"ID", "FORMULAID", "FORMULANAME", "USERID","USERNAME", "AMOUNT", "DATE", "TIME", "COMMENT"};
	std::vector<CString> headerList(headerArray, headerArray + 9);
	uiutils::updatelist(m_pRecordset, m_StatisticList, headerList);
}

void CStatisticDialog::OnDetailrecordButton() 
{
	// TODO: Add your control notification handler code here
	CDetailRecordDialog detailRecordDialog;
	if (m_StatisticList.GetFirstSelectedItemPosition() == NULL)
	{
		AfxMessageBox("��ѡ��Ҫ�鿴�ļ�¼��ID");
		return;
	}
	
	POSITION pos = m_StatisticList.GetFirstSelectedItemPosition() -1 ;
	CString ID = m_StatisticList.GetItemText((int)pos, 0);

	SingletonHelper::getInstance()->setRecordID(ID);
	detailRecordDialog.DoModal();
}

void CStatisticDialog::OnClearButton() 
{
	// TODO: Add your control notification handler code here
	m_StatisticList.DeleteAllItems();
}

void CStatisticDialog::OnAllButton() 
{
	// TODO: Add your control notification handler code here
	refreshList();
}

CStatisticDialog::~CStatisticDialog()
{

}

void CStatisticDialog::OnQueryButton() 
{
	// TODO: Add your control notification handler code here
	CString index, keyword;

	m_Index.GetWindowText(index);
	m_Keyword.GetWindowText(keyword);

	if (index.IsEmpty() || keyword.IsEmpty())
	{
		AfxMessageBox("�������߹ؼ��ֲ���Ϊ��");
		return;
	}

	m_StatisticList.DeleteAllItems();
	
	CString fieldName;		

	if (index == "�䷽���")
	{
		fieldName = "FORMULAID";
	}
	if (index == "�䷽����")
	{
		fieldName = "FORMULANAME";
	}
	if (index == "��Ա���" )
	{
		fieldName = "USERID";
	}
	if (index == "��Ա����")
	{
		fieldName = "USERNAME";
	}

	CString sqlState("SELECT ID, FORMULAID, FORMULANAME, USERID, USERNAME, AMOUNT, DATE, TIME, COMMENT FROM WEIGHT WHERE ") ;
	sqlState += fieldName ;

	if (index == "�䷽���" || index == "��Ա���" )
	{
		sqlState +=  " = " + keyword;
	}
	else if (index == "��Ա����" || index == "�䷽����")
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
	
	CString headerArray[9] = {"ID", "FORMULAID", "FORMULANAME", "USERID","USERNAME", "AMOUNT", "DATE", "TIME", "COMMENT"};
	std::vector<CString> headerList(headerArray, headerArray + 9);
	uiutils::updatelist(m_pRecordset, m_StatisticList, headerList);
}

void CStatisticDialog::OnAdvancequeryButton() 
{
	// TODO: Add your control notification handler code here
	CFormulaAdvanceQueryDialog formulaAdvanceQueryDialog;
	SingletonHelper::getInstance()->setPtrData((void*)this);
	formulaAdvanceQueryDialog.DoModal();
}

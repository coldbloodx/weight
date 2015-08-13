// QueryDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\QueryDialog.h"
#include "..\..\OtherClasses\HelperClass.h"
#include "..\..\OtherClasses\DatabaseConnector.h"
#include "..\..\OtherClasses\RecordSetPointer.h"
#include "..\..\OtherClasses\uiFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryDialog dialog


CQueryDialog::CQueryDialog(CWnd* pParent /*=NULL*/)
	: CDialog()
{
	//{{AFX_DATA_INIT(CQueryDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CQueryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryDialog)
	DDX_Control(pDX, IDC_STATUS_STATIC, m_StatusStatic);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_CLEARRESULT_BUTTON, m_Clear);
	DDX_Control(pDX, ID_QUERY, m_Query);
	DDX_Control(pDX, IDC_RESULT_LIST, m_ResultList);
	DDX_Control(pDX, IDC_KEYWORD_EDIT, m_Keyword);
	DDX_Control(pDX, IDC_QUERYINDEX_COMBO, m_QueryIndex);
	DDX_Control(pDX, IDC_QUERYTABLE_COMBO, m_QueryTable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQueryDialog, CDialog)
	//{{AFX_MSG_MAP(CQueryDialog)
	ON_BN_CLICKED(ID_QUERY, OnQuery)
	ON_CBN_SELCHANGE(IDC_QUERYTABLE_COMBO, OnSelchangeQuerytableCombo)
	ON_BN_CLICKED(IDC_CLEARRESULT_BUTTON, OnClearresultButton)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryDialog message handlers



void CQueryDialog::OnQuery() 
{
	// TODO: Add your control notification handler code here
	CString tableName, indexName, keyWord;

	m_QueryTable.GetWindowText(tableName);
	m_QueryIndex.GetWindowText(indexName);
	m_Keyword.GetWindowText(keyWord);

	clearResultList();

	if (tableName.IsEmpty() || indexName.IsEmpty() || keyWord.IsEmpty())
	{
		AfxMessageBox("请检查输入，表名，索引，关键字不能为空");
		return;
	}


	switch(SingletonHelper::getInstance()->getIntData())
	{
	case 0:
		{
			initMaterialListHeader();
			refreshMaterialList();
		}
		break;

	case 1:
		{
			initFormulaListHeader();
			refreshFormulaList();
		}
		break;

	case 2:
		{
			initUserListHeader();
			refreshUserList();
		}
		break;
		
	default:
		break;
	}
}

void CQueryDialog::OnSelchangeQuerytableCombo() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	int curSelection = m_QueryTable.GetCurSel();
	CString tempString;
	switch (curSelection)
	{
	case 0:
		{
			tempString = "MATERIALS";
			SingletonHelper::getInstance()->setTableName(tempString);
			SingletonHelper::getInstance()->setIntData(0);
			m_QueryIndex.ResetContent();
			m_QueryIndex.AddString("材料编号");
			m_QueryIndex.AddString("材料名称");
			m_QueryIndex.AddString("材料批号");
			m_QueryIndex.SetCurSel(0);
			
		}
		break;
	case 1:
		{
			tempString = "FORMULAS";
			SingletonHelper::getInstance()->setTableName(tempString);
			SingletonHelper::getInstance()->setIntData(1);
			m_QueryIndex.ResetContent();
			m_QueryIndex.AddString("配方编号");
			m_QueryIndex.AddString("配方名称");
			m_QueryIndex.AddString("配方项目");
			m_QueryIndex.SetCurSel(0);
		}
		break;
	case 2:
		{
			tempString = "USERS";
			SingletonHelper::getInstance()->setTableName(tempString);
			SingletonHelper::getInstance()->setIntData(2);
			m_QueryIndex.ResetContent();
			m_QueryIndex.AddString("用户编号");
			m_QueryIndex.AddString("用户名");
			m_QueryIndex.AddString("用户权限");
			m_QueryIndex.SetCurSel(0);
		}
		break;
	default:
		break;
	}
}

void CQueryDialog::initUserListHeader()
{
	std::vector<std::string> headerList;
	headerList.push_back("人员编号");
	headerList.push_back("人员姓名");
	headerList.push_back("权限");
	for (int i = 0; i< (int)headerList.size(); ++i)
	{
		m_ResultList.InsertColumn(i,headerList[i].c_str(), 0, 160);
	}
}

void CQueryDialog::refreshUserList()
{
	CString indexName;
	CString keyWord;

	CString sqlState("SELECT * FROM USERS WHERE " );

	CString fieldName;

	if (indexName == "用户编号")
	{
		fieldName = "ID = ";
	}

	if (indexName == "人员姓名")
	{
		fieldName = "NAME = ";
	}

	if (indexName == "权限" )
	{
		fieldName = "RIGHT =";
	}

	sqlState += fieldName;
	if (indexName == "用户编号")
	{
		sqlState += keyWord.GetBuffer(0);
	}
	else
	{
		sqlState += "'" + keyWord + "'";
	}

	//init recordset pointer
	RecordSetPointer::getInstanceRef().setSqlState(sqlState);

	//exec SQL state
	try
	{
		RecordSetPointer::getInstanceRef().execSQL() ;
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	//get the result data set
	_RecordsetPtr& m_pRecordset = RecordSetPointer::getInstanceRef().getRecordPtr();
	
	CString headerArray[3] ={"ID", "NAME", "RIGHT"};
	
	std::vector<CString> headerList(headerArray, headerArray + 3);
	uiFunctions::updateList(m_pRecordset, m_ResultList, headerList);
}

void CQueryDialog::initFormulaListHeader()
{
	std::vector<std::string> headerList;
	headerList.push_back("配方编号");
	headerList.push_back("配方名称");
	headerList.push_back("配方内容");
	for (int i = 0; i< (int)headerList.size(); ++i)
	{
		m_ResultList.InsertColumn(i,headerList[i].c_str(), 0, 160);
	}
}

void CQueryDialog::refreshFormulaList()
{

	CString indexName, keyWord;

	m_QueryIndex.GetWindowText(indexName);
	m_Keyword.GetWindowText(keyWord);

	CString sqlState("SELECT * FROM FORMULAS WHERE " );

	CString fieldName;

	if (indexName == "配方编号")
	{
		fieldName = "ID = ";
	}

	if (indexName == "配方名称")
	{
		fieldName = "NAME = ";
	}


	sqlState += fieldName;
	if (indexName == "配方编号")
	{
		sqlState += keyWord.GetBuffer(0);
	}
	else
	{
		sqlState += "'" + keyWord + "'";
	}

	//init recordset pointer
	RecordSetPointer::getInstanceRef().setSqlState(sqlState);


	//exec SQL state
	try
	{
		RecordSetPointer::getInstanceRef().execSQL() ;
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	//get the result data set
	_RecordsetPtr& m_pRecordset = RecordSetPointer::getInstanceRef().getRecordPtr();

	CString headerArray[3] ={"ID", "NAME", "MATERIAL"};
	std::vector<CString> headerList(headerArray, headerArray + 3);
	uiFunctions::updateList(m_pRecordset, m_ResultList, headerList);
}

void CQueryDialog::initMaterialListHeader()
{
	std::vector<std::string> headerList;
	headerList.push_back("材料编号");
	headerList.push_back("材料名称");
	for (int i = 0; i< (int)headerList.size(); ++i)
	{
		m_ResultList.InsertColumn(i,headerList[i].c_str(), 0, 160);
	}
}

void CQueryDialog::refreshMaterialList()
{
	CString indexName;
	CString keyWord;
	
	m_QueryIndex.GetWindowText(indexName);
	m_Keyword.GetWindowText(keyWord);

	CString sqlState("SELECT * FROM MATERIALS WHERE ");

	CString fieldName;

	if (indexName == "材料编号")
	{
		fieldName = "ID = ";
	}

	if (indexName == "材料名称")
	{
		fieldName = "NAME = ";
	}

	sqlState += fieldName;
	if (indexName == "材料编号")
	{
		sqlState += keyWord.GetBuffer(0);
	}
	else
	{
		sqlState += "'" + keyWord + "'";
	}

	//init recordset pointer
	RecordSetPointer::getInstanceRef().setSqlState(sqlState);

	//exec SQL state
	try
	{
		RecordSetPointer::getInstanceRef().execSQL() ;
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	//get the result data set
	_RecordsetPtr& m_pRecordset = RecordSetPointer::getInstanceRef().getRecordPtr();
	
	CString headerArray[2] ={"ID", "NAME"};
	std::vector<CString> headerList(headerArray, headerArray + 2);
	uiFunctions::updateList(m_pRecordset, m_ResultList, headerList);
}

void CQueryDialog::clearResultList()
{
	m_ResultList.DeleteAllItems();
	int	iCount   =   m_ResultList.GetHeaderCtrl()->GetItemCount();   
	for(int i = 0; i < iCount; i++)   
	{   
		m_ResultList.DeleteColumn(0);   
	}
	for(int j = 0; j < iCount; j++)   
	{   
		m_ResultList.GetHeaderCtrl()->DeleteItem(0);   
	}  
}

void CQueryDialog::OnClearresultButton() 
{
	// TODO: Add your control notification handler code here
	m_Keyword.SetWindowText("");
	clearResultList();
}

BOOL CQueryDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	HelperFunctions::showStatus(m_StatusStatic);
	// TODO: Add extra initialization here
	//load background
	CBitmap   bmp;   

    uiFunctions::setdlgsize(this);

	CRect backRect(170, 455, 260, 480);
	m_ButtonCancel.MoveWindow(backRect);


	CRect clearRect(740, 460, 870, 500);
	m_Clear.MoveWindow(clearRect);


	CRect queryRect(530, 460, 660, 500);
	m_Query.MoveWindow(queryRect);


	CRect listRect(260, 100, 920, 455);
	m_ResultList.MoveWindow(listRect);



	//buttonVector.push_back(&m_Query);
	//buttonVector.push_back(&m_ButtonCancel);
	//buttonVector.push_back(&m_Clear);
	//for(size_t i = 0; i < buttonVector.size(); ++i)
	//{
	//	HelperFunctions::setButtonStyle(*buttonVector[i], RGB(55,71,158), SingletonHelper::getInstance()->simSong20);
	//}
	//
	SetTimer(1000,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CQueryDialog::~CQueryDialog()
{

}

void CQueryDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}


HBRUSH CQueryDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if   (pWnd == this)   
	{   
		return m_brBk;   
	}   
	if   (nCtlColor   ==   CTLCOLOR_STATIC)   
	{     
		pDC->SetBkMode(TRANSPARENT);	//透明   
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	}   

	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

// QueryDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "QueryDialog.h"
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
// CQueryDialog dialog


CQueryDialog::CQueryDialog(CWnd* pParent /*=NULL*/)
: CDialog(CQueryDialog::IDD ,pParent)
{
}


void CQueryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_CLEARRESULT_BUTTON, m_Clear);
	DDX_Control(pDX, ID_QUERY, m_Query);
	DDX_Control(pDX, IDC_RESULT_LIST, m_ResultList);
	DDX_Control(pDX, IDC_KEYWORD_EDIT, m_Keyword);
	DDX_Control(pDX, IDC_QUERYINDEX_COMBO, m_QueryIndex);
	DDX_Control(pDX, IDC_QUERYTABLE_COMBO, m_QueryTable);
}


BEGIN_MESSAGE_MAP(CQueryDialog, CDialog)
	ON_BN_CLICKED(ID_QUERY, OnQuery)
	ON_CBN_SELCHANGE(IDC_QUERYTABLE_COMBO, OnSelchangeQuerytableCombo)
	ON_BN_CLICKED(IDC_CLEARRESULT_BUTTON, OnClearresultButton)
END_MESSAGE_MAP()


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
		AfxMessageBox("�������룬�������������ؼ��ֲ���Ϊ��");
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
	int curSelection = m_QueryTable.GetCurSel();
	CString tempString;
	switch (curSelection)
	{
	case 0:
		{

			SingletonHelper::getInstance()->setIntData(0);
			m_QueryIndex.ResetContent();
			m_QueryIndex.AddString("���ϱ��");
			m_QueryIndex.AddString("��������");
			m_QueryIndex.AddString("��������");
			m_QueryIndex.SetCurSel(0);
			
		}
		break;
	case 1:
		{

			SingletonHelper::getInstance()->setIntData(1);
			m_QueryIndex.ResetContent();
			m_QueryIndex.AddString("�䷽���");
			m_QueryIndex.AddString("�䷽����");
			m_QueryIndex.AddString("�䷽��Ŀ");
			m_QueryIndex.SetCurSel(0);
		}
		break;
	case 2:
		{
			SingletonHelper::getInstance()->setIntData(2);
			m_QueryIndex.ResetContent();
			m_QueryIndex.AddString("�û����");
			m_QueryIndex.AddString("�û���");
			m_QueryIndex.AddString("�û�Ȩ��");
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
	headerList.push_back("��Ա���");
	headerList.push_back("��Ա����");
	headerList.push_back("Ȩ��");
	for (int i = 0; i< (int)headerList.size(); ++i)
	{
		m_ResultList.InsertColumn(i,headerList[i].c_str(), 0, 160);
	}
}

void CQueryDialog::refreshUserList()
{
	CString indexName;
	CString keyWord;

	CString sql("select * from users where " );

	CString csQueryCond;

	if (indexName == "�û����")
	{
		csQueryCond.Format("id = %s", keyWord.GetBuffer(0));
	}

	if (indexName == "��Ա����")
	{
		csQueryCond.Format("name = '%s'", keyWord);
	}

	if (indexName == "Ȩ��" )
	{
		csQueryCond.Format("permision = '%s'", keyWord);
	}
	sql += csQueryCond;

	//get the result data set
	_RecordsetPtr& dbptr = SQLExecutor::getInstanceRef().execquery(sql);
	
	CString headerArray[3] ={"id", "name", "permission"};
	
	std::vector<CString> headerList(headerArray, headerArray + 3);
	uiutils::updatelist(dbptr, m_ResultList, headerList);
}

void CQueryDialog::initFormulaListHeader()
{
	std::vector<std::string> headerList;
	headerList.push_back("�䷽���");
	headerList.push_back("�䷽����");
	headerList.push_back("�䷽����");
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

	CString sql("select * from formulas where " );

	CString csQueryCond;

	if (indexName == "�䷽���")
	{
		csQueryCond.Format("ID = %s", keyWord.GetBuffer(0));
	}

	if (indexName == "�䷽����")
	{
		csQueryCond.Format("NAME = '%s'", keyWord);
	}

	sql += csQueryCond;
	
	//get the result data set
	_RecordsetPtr& dbptr = SQLExecutor::getInstanceRef().execquery(sql);

	CString headerArray[3] ={"ID", "NAME", "MATERIAL"};
	std::vector<CString> headerList(headerArray, headerArray + 3);
	uiutils::updatelist(dbptr, m_ResultList, headerList);
}

void CQueryDialog::initMaterialListHeader()
{
	std::vector<std::string> headerList;
	headerList.push_back("���ϱ��");
	headerList.push_back("��������");
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

	CString sql("select * from materials where ");

	CString csQueryCond;

	if (indexName == "���ϱ��")
	{
		csQueryCond.Format(" ID = %s ", keyWord.GetBuffer(0));
	}

	if (indexName == "��������")
	{
		csQueryCond.Format("NAME = '%s' ", keyWord);
	}

	sql += csQueryCond;

	//get the result data set
	_RecordsetPtr& dbptr = SQLExecutor::getInstanceRef().execquery(sql);
	
	CString headerArray[2] ={"ID", "NAME"};
	std::vector<CString> headerList(headerArray, headerArray + 2);
	uiutils::updatelist(dbptr, m_ResultList, headerList);
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
	uiutils::setdlgsize(this, &m_ButtonCancel);
	return TRUE;
}

CQueryDialog::~CQueryDialog()
{

}



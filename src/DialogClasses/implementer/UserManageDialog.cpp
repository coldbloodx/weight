// UserManageDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "UserManageDialog.h"
#include <string>
#include <vector>
#include "UserAddDialog.h"
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
// CUserManageDialog dialog


CUserManageDialog::CUserManageDialog(CWnd* pParent /*=NULL*/)
:CDialog(CUserManageDialog::IDD, pParent)
{
}


void CUserManageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserManageDialog)
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_USERDEL, m_Del);
	DDX_Control(pDX, IDC_USERADD, m_Add);
	DDX_Control(pDX, IDC_USERLIST, m_UserList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserManageDialog, CDialog)
	//{{AFX_MSG_MAP(CUserManageDialog)
	ON_BN_CLICKED(IDC_USERADD, OnUseradd)
	ON_BN_CLICKED(IDC_USERDEL, OnUserdel)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserManageDialog message handlers

CUserManageDialog::~CUserManageDialog()
{

}


BOOL CUserManageDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	initListHeader();
	initList();
	
	uiFunctions::setdlgsize(this, &m_ButtonOK);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CUserManageDialog::initList()
{
	SQLExecutor::getInstanceRef().setSqlState(CString("SELECT * FROM USERS"));

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

	CString headerArray[3] = {"ID", "NAME", "RIGHT"};
	std::vector<CString> headerList(headerArray, headerArray+3);

	try
	{
		uiFunctions::updateList(m_pRecordset, m_UserList, headerList);
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
	}

}

void CUserManageDialog::initListHeader()
{
	std::string headerArray[3] = {"人员编号","人员姓名","权限"};
	std::vector<std::string> headerList(headerArray, headerArray+3);
	for (size_t i = 0; i< headerList.size(); ++i)
	{
		m_UserList.InsertColumn(i,headerList[i].c_str(), 0, 160);
	}
}


void CUserManageDialog::OnUseradd() 
{
	// TODO: Add your control notification handler code here
	CUserAddDialog userAddDialog;
	userAddDialog.m_UserManagementWindow = this;
	userAddDialog.DoModal();
}

void CUserManageDialog::OnUserdel() 
{
	// TODO: Add your control notification handler code here
	if (m_UserList.GetFirstSelectedItemPosition() == NULL)
	{
		AfxMessageBox("请在人员表中选中要删除的ID！");
		return;
	}
	
	POSITION pos = m_UserList.GetFirstSelectedItemPosition() -1 ;

	CString ID = m_UserList.GetItemText(((int)pos), 0);

	if (ID == "1001")
	{
		AfxMessageBox("管理员帐户，不可以删除！");
		return;
	}

	CString sqlState("SELECT * FROM USERS");
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

	try
	{
		m_pRecordset->MoveFirst();
		m_pRecordset->Move((int)pos);
		m_pRecordset->Delete(adAffectCurrent);
		m_pRecordset->Update();	
	}
	catch (_com_error  &e)
	{
		AfxMessageBox(e.Description());
		return;
	}
	
	m_UserList.DeleteAllItems();
	initList();
}

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
#include "DBptr.h"
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
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_USERDEL, m_Del);
	DDX_Control(pDX, IDC_USERADD, m_Add);
	DDX_Control(pDX, IDC_USERLIST, m_UserList);
}


BEGIN_MESSAGE_MAP(CUserManageDialog, CDialog)
	ON_BN_CLICKED(IDC_USERADD, OnUseradd)
	ON_BN_CLICKED(IDC_USERDEL, OnUserdel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserManageDialog message handlers

CUserManageDialog::~CUserManageDialog()
{

}


BOOL CUserManageDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	initListHeader();
	initList();
	
	uiutils::setdlgsize(this, &m_ButtonOK);
	return TRUE;
}

void CUserManageDialog::initList()
{

	_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().execquery("select * from users");

	CString headerArray[3] = {"id", "name", "permission"};
	std::vector<CString> headerList(headerArray, headerArray+3);

	try
	{
		uiutils::updatelist(m_pRecordset, m_UserList, headerList);
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
	}

}

void CUserManageDialog::initListHeader()
{
	std::string headerArray[3] = {"��Ա���","��Ա����","Ȩ��"};
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
		AfxMessageBox("������Ա����ѡ��Ҫɾ����ID��");
		return;
	}
	
	POSITION pos = m_UserList.GetFirstSelectedItemPosition() -1 ;

	CString userid = m_UserList.GetItemText(((int)pos), 0);

	if (userid == "1001")
	{
		AfxMessageBox("����Ա�ʻ���������ɾ����");
		return;
	}

	CString sql;
	sql.Format("delete from users where id = %s ", userid);
	SQLExecutor::getInstanceRef().execquery(sql);

	m_UserList.DeleteAllItems();
	initList();
}

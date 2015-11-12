// UserAddDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "UserAddDialog.h"
#include "UserManageDialog.h"
#include "HelperClass.h"
#include "uiFunctions.h"
#include "DBConnector.h"
#include "DBptr.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CUserAddDialog::CUserAddDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CUserAddDialog::IDD, pParent)
{
}


void CUserAddDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_USERRIGHT_DROPDOWN, m_UserRight);
	DDX_Control(pDX, IDC_USERNAME_EDIT, m_UserName);
	DDX_Control(pDX, IDC_USERID_EDIT, m_UserID);
}

CUserAddDialog::~CUserAddDialog(){}

BEGIN_MESSAGE_MAP(CUserAddDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CUserAddDialog::OnBnClickedOk)
END_MESSAGE_MAP()

void CUserAddDialog::OnOK() 
{
	CString userID, userName, perm;
	
	m_UserID.GetWindowText(userID);
	m_UserName.GetWindowText(userName);
	m_UserRight.GetWindowText(perm);

	if (userID.IsEmpty() || userName.IsEmpty() || perm.IsEmpty())
	{
		CString msg("人员编号，人员姓名，人员权限为必填选项！");
		AfxMessageBox(msg);
		return;
	}
	
	CString sql;
	sql.Format("insert into [users] ([id], [name], [password], [permission]) values(%s, '%s', %s, '%s'); ", 
		userID, userName, "123456", perm);

	SQLExecutor::getInstanceRef().execquery(sql);

	m_UserManagementWindow->m_UserList.DeleteAllItems();
	m_UserManagementWindow->initList();

	CDialog::OnOK();
}

BOOL CUserAddDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	uiutils::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);
	return TRUE; 
}

void CUserAddDialog::OnBnClickedOk()
{
	OnOK();
}
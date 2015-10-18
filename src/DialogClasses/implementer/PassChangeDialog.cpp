// PassChangeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "PassChangeDialog.h"
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
// CPassChangeDialog dialog


CPassChangeDialog::CPassChangeDialog(CWnd* pParent /*=NULL*/)
: CDialog(CPassChangeDialog::IDD, pParent){}

CPassChangeDialog::~CPassChangeDialog(){}

void CPassChangeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_ORIGINALPASS_EDIT, m_OriginalPassEdit);
	DDX_Control(pDX, IDC_NEWPASS_EDIT, m_NewPassEdit);
	DDX_Control(pDX, IDC_NEWPASSCONFIRM_EDIT, m_NewPassConfirmEdit);
}


BEGIN_MESSAGE_MAP(CPassChangeDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPassChangeDialog::OnBnClickedOk)
END_MESSAGE_MAP()

void CPassChangeDialog::OnOK() 
{
	CString originalPass, newPass, confirmPass;

	m_OriginalPassEdit.GetWindowText(originalPass);
	m_NewPassEdit.GetWindowText(newPass);
	m_NewPassConfirmEdit.GetWindowText(confirmPass);

	if (SingletonHelper::getInstance()->getUserPass() != originalPass)
	{
		AfxMessageBox("旧密码错误，请重新输入");
		return;
	}

	if (originalPass.IsEmpty() || newPass.IsEmpty() || confirmPass.IsEmpty())
	{
		AfxMessageBox("请检查您的输入！");
		return;
	}

	if (newPass != confirmPass)
	{
		AfxMessageBox("请确认输入新密码的一致性！");
		return;
	}

	CString sqlState;
	sqlState.Format("update [users] set [password] = '%s' where [id] = %s; ", 
		confirmPass,  SingletonHelper::getInstance()->getUserID());
	
	SQLExecutor::getInstanceRef().execquery(sqlState);

	SingletonHelper::getInstance()->setUserPass(confirmPass);

	CDialog::OnOK();
}

BOOL CPassChangeDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	uiutils::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);
	return TRUE;
}

void CPassChangeDialog::OnBnClickedOk()
{
	OnOK();
}


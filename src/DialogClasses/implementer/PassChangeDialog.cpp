// PassChangeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "PassChangeDialog.h"
#include "HelperClass.h"
#include "DatabaseConnector.h"
#include "RecordSetPointer.h"
#include "uiFunctions.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPassChangeDialog dialog


CPassChangeDialog::CPassChangeDialog(CWnd* pParent /*=NULL*/)
: CDialog(CPassChangeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPassChangeDialog)
	//}}AFX_DATA_INIT
}

CPassChangeDialog::~CPassChangeDialog()
{

}

void CPassChangeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPassChangeDialog)
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_ORIGINALPASS_EDIT, m_OriginalPassEdit);
	DDX_Control(pDX, IDC_NEWPASS_EDIT, m_NewPassEdit);
	DDX_Control(pDX, IDC_NEWPASSCONFIRM_EDIT, m_NewPassConfirmEdit);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CPassChangeDialog, CDialog)
	//{{AFX_MSG_MAP(CPassChangeDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CPassChangeDialog::OnBnClickedOk)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPassChangeDialog message handlers

void CPassChangeDialog::OnOK() 
{
	// TODO: Add extra validation here
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

	CString sqlState("UPDATE USERS SET PASSWORDS = '");
	sqlState += confirmPass +"' WHERE ID = " + SingletonHelper::getInstance()->getUserID();

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

	SingletonHelper::getInstance()->setUserPass(confirmPass);

	CDialog::OnOK();
}

BOOL CPassChangeDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	


	uiFunctions::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPassChangeDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}


// MainSettingsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "BasicSettingsDialog.h"
#include "OtherSettingsDialog.h"
#include "UserManageDialog.h"

#include "PassChangeDialog.h"
#include "changeManufactureNameDialog.h"
#include "helperclass.h"
#include "uifunctions.h"

// CMainSettingsDialog dialog

IMPLEMENT_DYNAMIC(CBasicSettingsDialog, CDialog)

CBasicSettingsDialog::CBasicSettingsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBasicSettingsDialog::IDD, pParent)
{

}

CBasicSettingsDialog::~CBasicSettingsDialog()
{
}

void CBasicSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_goBackButton);
	DDX_Control(pDX, IDC_BUTTON3, m_ChangeNameButton);
	DDX_Control(pDX, IDC_BUTTON1, m_OtherSettingsButton);
	DDX_Control(pDX, IDC_BUTTON2, m_UserManagement);
	DDX_Control(pDX, IDC_BUTTON4, m_ChangePassword);
}


BEGIN_MESSAGE_MAP(CBasicSettingsDialog, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CBasicSettingsDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBasicSettingsDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CBasicSettingsDialog::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CBasicSettingsDialog::OnBnClickedButton3)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CMainSettingsDialog message handlers

BOOL CBasicSettingsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();


	CButton* btnarray[5] = {&m_OtherSettingsButton,&m_UserManagement,&m_ChangeNameButton,
		&m_ChangePassword, &m_goBackButton};
	uiutils::init2rowbtns(btnarray, 5);
    uiutils::setdlgsize(this);
	return TRUE; 
}

void CBasicSettingsDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	COtherSettingsDialog otherSettingsDialog;
	otherSettingsDialog.DoModal();
}

void CBasicSettingsDialog::OnBnClickedButton2()
{
	CUserManageDialog userManageDialog;
	userManageDialog.DoModal();
}

void CBasicSettingsDialog::OnBnClickedButton4()
{
	CPassChangeDialog passChangeDialog;
	passChangeDialog.DoModal();
}

void CBasicSettingsDialog::OnBnClickedButton3()
{
	ChangeManufactureNameDialog changeDialog;
	changeDialog.DoModal();
}

void CBasicSettingsDialog::OnPaint()
{
    uiutils::drawDlgBg(this, IDB_MAINPAGE);
}

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

	// TODO:  Add extra initialization here
	int left = 200;
	int top = 160;
	int width = 490 - 200;
	int height = 340 - 160;
	int horiSpacer = 535 - 490;
	int vertSpacer = 365 - 340;

	CButton* buttonArray[4] = {&m_OtherSettingsButton,&m_UserManagement,&m_ChangeNameButton,&m_ChangePassword};
	std::vector<CButton*> buttonVector(buttonArray, buttonArray + 4);


	for (size_t i = 0; i < buttonVector.size(); ++i)
	{
		CRect startRect(left, top, left + width, top + height);
		buttonVector[i]->MoveWindow(startRect, TRUE);

		if (((i + 1) % 2) == 0)
		{
			left = 200;
			top = startRect.bottom + vertSpacer;
		}
		else
		{
			left = startRect.right + horiSpacer;
		}
	}

	//make the dialog fullscreen
	CRect rectBack(382, 578, 643, 640);
	m_goBackButton.MoveWindow(rectBack);

    uiFunctions::setdlgsize(this);  

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CBasicSettingsDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	COtherSettingsDialog otherSettingsDialog;
	otherSettingsDialog.DoModal();
}



void CBasicSettingsDialog::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CUserManageDialog userManageDialog;
	userManageDialog.DoModal();
}

void CBasicSettingsDialog::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CPassChangeDialog passChangeDialog;
	passChangeDialog.DoModal();
}

void CBasicSettingsDialog::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	ChangeManufactureNameDialog changeDialog;
	changeDialog.DoModal();
}

void CBasicSettingsDialog::OnPaint()
{
    uiFunctions::drawDlgBg(this, IDB_MAINPAGE);
}

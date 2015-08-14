// MainSettingsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "MainSettingsDialog.h"
#include "DialogClasses/header/OtherSettingsDialog.h"
#include "DialogClasses/header/UserManageDialog.h"

#include "DialogClasses/header/PassChangeDialog.h"
#include "changeManufactureNameDialog.h"
#include "OtherClasses/helperclass.h"
#include "OtherClasses/uifunctions.h"

// CMainSettingsDialog dialog

IMPLEMENT_DYNAMIC(CMainSettingsDialog, CDialog)

CMainSettingsDialog::CMainSettingsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMainSettingsDialog::IDD, pParent)
{

}

CMainSettingsDialog::~CMainSettingsDialog()
{
}

void CMainSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_goBackButton);
	DDX_Control(pDX, IDC_BUTTON3, m_ChangeNameButton);
	DDX_Control(pDX, IDC_BUTTON1, m_OtherSettingsButton);
	DDX_Control(pDX, IDC_BUTTON2, m_UserManagement);
	DDX_Control(pDX, IDC_BUTTON4, m_ChangePassword);
}


BEGIN_MESSAGE_MAP(CMainSettingsDialog, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CMainSettingsDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainSettingsDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CMainSettingsDialog::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainSettingsDialog::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMainSettingsDialog message handlers

HBRUSH CMainSettingsDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if   (pWnd == this)   
	{   
		return m_brBk;   
	}  

	return hbr;
	// TODO:  Return a different brush if the default is not desired
}

BOOL CMainSettingsDialog::OnInitDialog()
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
    uiFunctions::setdlgsize(this);  

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMainSettingsDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	COtherSettingsDialog otherSettingsDialog;
	otherSettingsDialog.DoModal();
}



void CMainSettingsDialog::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CUserManageDialog userManageDialog;
	userManageDialog.DoModal();
}



void CMainSettingsDialog::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CPassChangeDialog passChangeDialog;
	passChangeDialog.DoModal();
}

void CMainSettingsDialog::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	ChangeManufactureNameDialog changeDialog;
	changeDialog.DoModal();
}

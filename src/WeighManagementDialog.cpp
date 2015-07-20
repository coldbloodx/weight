// WeighManagementDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "WeighManagementDialog.h"
#include "DialogClasses/header/formuladialog.h"
#include "DialogClasses/header/StatisticDialog.h"
#include "DialogClasses/header/QueryDialog.h"
#include "DialogClasses/header/MaterialManagementDialog.h"


// CWeighManagementDialog dialog

IMPLEMENT_DYNAMIC(CWeighManagementDialog, CDialog)

CWeighManagementDialog::CWeighManagementDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWeighManagementDialog::IDD, pParent)
{

}

CWeighManagementDialog::~CWeighManagementDialog()
{
}

void CWeighManagementDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_MaterialManagement);
	DDX_Control(pDX, IDC_BUTTON2, m_FormulaManagement);
	DDX_Control(pDX, IDC_BUTTON3, m_Query);
	DDX_Control(pDX, IDC_BUTTON4, m_Statistic);
	DDX_Control(pDX, IDCANCEL, m_goBackButton);
}


BEGIN_MESSAGE_MAP(CWeighManagementDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON4, &CWeighManagementDialog::OnBnClickedButton4)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CWeighManagementDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWeighManagementDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CWeighManagementDialog::OnBnClickedButton3)
END_MESSAGE_MAP()


// CWeighManagementDialog message handlers

void CWeighManagementDialog::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CStatisticDialog statisticDialog;
	statisticDialog.DoModal();
}

BOOL CWeighManagementDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_WEIGHTSETTINGS);//‘ÿ»ÎÕº∆¨   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();   

	int left = 200;
	int top = 160;
	int width = 490 - 200;
	int height = 340 - 160;
	int horiSpacer = 535 - 490;
	int vertSpacer = 365 - 340;

	CButton* buttonArray[4] = {&m_MaterialManagement,&m_FormulaManagement,&m_Query,&m_Statistic};
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

	CRect rectBack(382, 578, 643, 640);
	m_goBackButton.MoveWindow(rectBack);

	// TODO:  Add extra initialization here
	//make the dialog fullscreen
	ModifyStyleEx(0, WS_EX_APPWINDOW | WS_EX_CONTROLPARENT, SWP_NOSIZE);   
	ModifyStyle(WS_BORDER | WS_DLGFRAME | WS_THICKFRAME, WS_POPUP, SWP_NOSIZE);  
	CRect   newRect(0,0,::GetSystemMetrics(SM_CXSCREEN),::GetSystemMetrics(SM_CYSCREEN));     
	MoveWindow(&newRect,false);   

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CWeighManagementDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if   (pWnd == this)   
	{   
		return m_brBk;   
	}  
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CWeighManagementDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CMaterialManagementDialog materialManagementDialog;
	materialManagementDialog.DoModal();
}

void CWeighManagementDialog::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CFormulaDialog testDialog;
	testDialog.m_From = 1;
	testDialog.DoModal();
}



void CWeighManagementDialog::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CQueryDialog queryDialog;
	queryDialog.DoModal();
}

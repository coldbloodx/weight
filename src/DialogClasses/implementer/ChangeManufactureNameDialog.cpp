// hangeManufactureNameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "changeManufactureNameDialog.h"


// ChangeManufactureNameDialog dialog

IMPLEMENT_DYNAMIC(ChangeManufactureNameDialog, CDialog)

ChangeManufactureNameDialog::ChangeManufactureNameDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ChangeManufactureNameDialog::IDD, pParent)
{

}

ChangeManufactureNameDialog::~ChangeManufactureNameDialog()
{
}

void ChangeManufactureNameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
}


BEGIN_MESSAGE_MAP(ChangeManufactureNameDialog, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// ChangeManufactureNameDialog message handlers

BOOL ChangeManufactureNameDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_MATERIALINPUTCOUNT);//ÔØÈëÍ¼Æ¬   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();   

	CRect wndRect((1024 - 640) / 2, (768 - 236) / 2, (1024 - 640) / 2 + 640, (768 - 236) / 2 + 250);
	this->MoveWindow(wndRect);

	CRect okRect(404, 190, 503, 224);
	CRect cancelRect(520, 190, 618, 224);

	m_ButtonOK.MoveWindow(okRect);


	m_ButtonCancel.MoveWindow(cancelRect);


	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH ChangeManufactureNameDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if   (pWnd == this)   
	{   
		return m_brBk;   
	}   
	if   (nCtlColor   ==   CTLCOLOR_STATIC)   
	{     
		pDC->SetBkMode(TRANSPARENT);	//Í¸Ã÷   
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	}   
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

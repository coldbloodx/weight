// MaterialCountInputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\MaterialCountInputDialog.h"
#include "..\..\DialogClasses\header\FormulaAddDialog.h"
#include "..\..\OtherClasses\HelperClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaterialCountInputDialog dialog


CMaterialCountInputDialog::CMaterialCountInputDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMaterialCountInputDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMaterialCountInputDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMaterialCountInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterialCountInputDialog)
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_MATERIALCOUNT_EDIT, m_MaterialCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMaterialCountInputDialog, CDialog)
	//{{AFX_MSG_MAP(CMaterialCountInputDialog)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMaterialCountInputDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaterialCountInputDialog message handlers

void CMaterialCountInputDialog::OnOK() 
{
	// TODO: Add extra validation here 
	CString materialCount;
	m_MaterialCount.GetWindowText(materialCount);
	if (materialCount.IsEmpty())
	{
		AfxMessageBox("配方中最少要有一种原料！");
		return;
	}

	int count = atoi(materialCount.GetBuffer(0));
	if (count > 20)
	{
		AfxMessageBox("配方原料种类不能大于10种");
		return;
	}
	CFormulaAddDialog formulaAddDialog;
	formulaAddDialog.materialCount = count;
	this->ShowWindow(0);
	formulaAddDialog.DoModal();
	CDialog::OnOK();
}

BOOL CMaterialCountInputDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_MATERIALINPUTCOUNT);//载入图片   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();   

	CRect wndRect((1024 - 640) / 2, (768 - 236) / 2, (1024 - 640) / 2 + 640, (768 - 236) / 2 + 250);
	this->MoveWindow(wndRect);

	CRect okRect(404, 190, 503, 224);
	CRect cancelRect(520, 190, 618, 224);

	m_ButtonOK.MoveWindow(okRect);
	m_ButtonOK.DrawBorder(FALSE);
	m_ButtonOK.DrawTransparent(TRUE);

	m_ButtonCancel.MoveWindow(cancelRect);
	m_ButtonCancel.DrawBorder(FALSE);
	m_ButtonCancel.DrawTransparent(TRUE);
	// TODO: Add extra initialization here
//	HelperFunctions::setButtonStyle(m_ButtonOK, RGB(55,71,158),SingletonHelper::getInstance()->simSong20)	;
//	HelperFunctions::setButtonStyle(m_ButtonCancel, RGB(55,71,158),SingletonHelper::getInstance()->simSong20);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CMaterialCountInputDialog::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CMaterialCountInputDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

HBRUSH CMaterialCountInputDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if   (pWnd == this)   
	{   
		return m_brBk;   
	}   
	if   (nCtlColor   ==   CTLCOLOR_STATIC)   
	{     
		pDC->SetBkMode(TRANSPARENT);	//透明   
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	}   

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

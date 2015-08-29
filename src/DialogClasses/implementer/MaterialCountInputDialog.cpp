// MaterialCountInputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "MaterialCountInputDialog.h"
#include "FormulaAddDialog.h"
#include "HelperClass.h"
#include "uiFunctions.h"

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
	
	uiFunctions::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);

	return TRUE; 
	             
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

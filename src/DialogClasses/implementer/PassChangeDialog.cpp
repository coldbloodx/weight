// PassChangeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\PassChangeDialog.h"
#include "..\..\OtherClasses\HelperClass.h"
#include "..\..\OtherClasses\DatabaseConnector.h"
#include "..\..\OtherClasses\RecordSetPointer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPassChangeDialog dialog


CPassChangeDialog::CPassChangeDialog(CWnd* pParent /*=NULL*/)
	: CDialog()
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
	DDX_Control(pDX, IDC_BACK, m_Back);
}


BEGIN_MESSAGE_MAP(CPassChangeDialog, CDialog)
	//{{AFX_MSG_MAP(CPassChangeDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CPassChangeDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BACK, &CPassChangeDialog::OnBnClickedBack)
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
	
	CBitmap   bmp;   

	bmp.LoadBitmap(IDB_PASSWORDCHANGE);//载入图片   
	m_brBk.CreatePatternBrush(&bmp);   
	bmp.DeleteObject();   

	CRect wndRect((1024 - 960) / 2, (768 - 583) / 2, (1024 - 960) / 2 + 960, (768 - 583) / 2 + 590);
	this->MoveWindow(wndRect);

	CRect okRect(500, 60, 615, 100);
	CRect cancelRect(645, 60, 760, 100);
	CRect backRect(174, 465, 260, 490);
	
	m_ButtonOK.MoveWindow(okRect);

	m_ButtonCancel.MoveWindow(cancelRect);

	m_Back.MoveWindow(backRect);




	// TODO: Add extra initialization here
	//buttonVector.push_back(&m_ButtonCancel);
	//buttonVector.push_back(&m_ButtonOK);
	//for(size_t i = 0; i < buttonVector.size(); ++i)
	//{
	//	HelperFunctions::setButtonStyle(*buttonVector[i], RGB(55,71,158), SingletonHelper::getInstance()->simSong20);
	//}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPassChangeDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

HBRUSH CPassChangeDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if   (pWnd == this)   
	{   
		return m_brBk;   
	}   
	if   (nCtlColor   ==   CTLCOLOR_STATIC)   
	{     
		pDC->SetBkMode(TRANSPARENT);	//透明   
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	}   

	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

void CPassChangeDialog::OnBnClickedBack()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

// UserManageDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\UserManageDialog.h"
#include <string>
#include <vector>
#include "..\..\DialogClasses\header\UserAddDialog.h"
#include "..\..\OtherClasses\HelperClass.h"
#include "..\..\OtherClasses\DatabaseConnector.h"
#include "..\..\OtherClasses\RecordSetPointer.h"
#include "..\..\OtherClasses\uiFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserManageDialog dialog


CUserManageDialog::CUserManageDialog(CWnd* pParent /*=NULL*/)
	: CCustomColorDialog(CUserManageDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserManageDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUserManageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserManageDialog)
	DDX_Control(pDX, IDC_STATUS_STATIC, m_StatusStatic);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_USERDEL, m_Del);
	DDX_Control(pDX, IDC_USERADD, m_Add);
	DDX_Control(pDX, IDC_USERLIST, m_UserList);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BACK, m_Back);
}


BEGIN_MESSAGE_MAP(CUserManageDialog, CDialog)
	//{{AFX_MSG_MAP(CUserManageDialog)
	ON_BN_CLICKED(IDC_USERADD, OnUseradd)
	ON_BN_CLICKED(IDC_USERDEL, OnUserdel)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BACK, &CUserManageDialog::OnBnClickedBack)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserManageDialog message handlers

CUserManageDialog::~CUserManageDialog()
{

}


BOOL CUserManageDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	HelperFunctions::showStatus(m_StatusStatic);

	// TODO: Add extra initialization here
	initListHeader();
	initList();

	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_USERMANAGEMENT);//载入图片   
	m_brBk.CreatePatternBrush(&bmp);   
	bmp.DeleteObject();   

	CRect wndRect((1024 - 960) / 2, (768 - 566) / 2, (1024 - 960) / 2 + 960, (768 - 566) / 2 + 580);
	this->MoveWindow(wndRect);

	CRect addRect(503, 48, 618, 86);
	CRect delRect(649, 48, 763, 86);
	CRect backRect(175, 460, 260, 480);;
	CRect listRect(260, 100, 918, 503);

	m_Add.MoveWindow(addRect);
	m_Add.DrawBorder(FALSE);
	m_Add.DrawTransparent(TRUE);

	m_Del.MoveWindow(delRect);
	m_Del.DrawBorder(FALSE);
	m_Del.DrawTransparent(TRUE);

	m_Back.MoveWindow(backRect);
	m_Back.DrawBorder(FALSE);
	m_Back.DrawTransparent(TRUE);

	m_UserList.MoveWindow(listRect);
	//CButtonST* buttonArray[3] = {&m_Add,&m_Del,&m_ButtonOK};
	//std::vector<CButtonST*> buttonVector(buttonArray, buttonArray+3);
	//for(size_t i = 0; i < buttonVector.size(); ++i)
	//{
	//	HelperFunctions::setButtonStyle(*buttonVector[i], RGB(55,71,158), SingletonHelper::getInstance()->simSong20);
	//}
	//SetTimer(1000,1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CUserManageDialog::initList()
{
	RecordSetPointer::getInstanceRef().setSqlState(CString("SELECT * FROM USERS"));

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

	CString headerArray[3] = {"ID", "NAME", "RIGHT"};
	std::vector<CString> headerList(headerArray, headerArray+3);

	try
	{
		uiFunctions::updateList(m_pRecordset, m_UserList, headerList);
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
	}

}

void CUserManageDialog::initListHeader()
{
	std::string headerArray[3] = {"人员编号","人员姓名","权限"};
	std::vector<std::string> headerList(headerArray, headerArray+3);
	for (size_t i = 0; i< headerList.size(); ++i)
	{
		m_UserList.InsertColumn(i,headerList[i].c_str(), 0, 160);
	}
}


void CUserManageDialog::OnUseradd() 
{
	// TODO: Add your control notification handler code here
	CUserAddDialog userAddDialog;
	userAddDialog.m_UserManagementWindow = this;
	userAddDialog.DoModal();
}

void CUserManageDialog::OnUserdel() 
{
	// TODO: Add your control notification handler code here
	if (m_UserList.GetFirstSelectedItemPosition() == NULL)
	{
		AfxMessageBox("请在人员表中选中要删除的ID！");
		return;
	}
	
	POSITION pos = m_UserList.GetFirstSelectedItemPosition() -1 ;

	CString ID = m_UserList.GetItemText(((int)pos), 0);

	if (ID == "1001")
	{
		AfxMessageBox("管理员帐户，不可以删除！");
		return;
	}

	CString sqlState("SELECT * FROM USERS");
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

	try
	{
		m_pRecordset->MoveFirst();
		m_pRecordset->Move((int)pos);
		m_pRecordset->Delete(adAffectCurrent);
		m_pRecordset->Update();	
	}
	catch (_com_error  &e)
	{
		AfxMessageBox(e.Description());
		return;
	}
	
	m_UserList.DeleteAllItems();
	initList();
}

void CUserManageDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}

HBRUSH CUserManageDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CUserManageDialog::OnBnClickedBack()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

// LoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\WeightDlg.h"
#include "..\..\DialogClasses\header\LoginDialog.h"
#include "..\..\OtherClasses\HelperClass.h"
#include "..\..\OtherClasses\DatabaseConnector.h"
#include "..\..\OtherClasses\RecordSetPointer.h"
#include "..\..\Splash.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog


CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
: CDialog(CLoginDialog::IDD, pParent),tryTimes(0),m_FocusedID(0)
{
	//{{AFX_DATA_INIT(CLoginDialog)
	//}}AFX_DATA_INIT
}

CLoginDialog::~CLoginDialog()
{

}


void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDialog)
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_BUTTON9, m_Button9);
	DDX_Control(pDX, IDC_BUTTON8, m_Button8);
	DDX_Control(pDX, IDC_BUTTON7, m_Button7);
	DDX_Control(pDX, IDC_BUTTON6, m_Button6);
	DDX_Control(pDX, IDC_BUTTON5, m_Button5);
	DDX_Control(pDX, IDC_BUTTON4, m_Button4);
	DDX_Control(pDX, IDC_BUTTON3, m_Button3);
	DDX_Control(pDX, IDC_BUTTON2, m_Button2);
	DDX_Control(pDX, IDC_BUTTON1, m_Button1);
	DDX_Control(pDX, IDC_BUTTON0, m_Button0);
	DDX_Control(pDX, IDC_BUTTON_COMMA, m_ButtonComma);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_ButonBack);
	DDX_Control(pDX, IDC_PASSWORD_EDIT, m_Password);
	DDX_Control(pDX, IDC_USERNAME_EDIT, m_UserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
//{{AFX_MSG_MAP(CLoginDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON0, OnButton0)
	ON_BN_CLICKED(IDC_BUTTON_COMMA, OnButtonComma)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	ON_WM_TIMER()
//	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog message handlers

void CLoginDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	PostQuitMessage(0);
	CDialog::OnCancel();
}

void CLoginDialog::OnOK() 
{
	// TODO: Add extra validation here
	CString userID;
	CString password;
	
	if (tryTimes >= 2)
	{
		AfxMessageBox("登录错误，程序退出！");
		SendMessage(WM_CLOSE);   
	}
	
	m_UserName.GetWindowText(userID);
	m_Password.GetWindowText(password);
	
	if (userID.IsEmpty() || password.IsEmpty())
	{
		++tryTimes;
		AfxMessageBox("用户编号，密码不能为空，请重新输入！");
		return;
	}
		
	
	CString select("SELECT PASSWORDS, RIGHT,NAME FROM USERS WHERE ID = ");
    CString sqlState = select + userID;
	
	CString tempUserName;
	CString tempPassword;
	CString tempRight;
	
	//init recordset pointer
	RecordSetPointer::getInstanceRef().setDatabaseConnection(DatabaseConnector::getInstanceRef().getDatabaseConnection());
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
		_variant_t vtPassword;
		_variant_t vtRight;
		_variant_t vUserName;
		int i=0;
		int nIndex = 0;
		
		while(!m_pRecordset->adoEOF)
		{
			vtPassword = m_pRecordset->GetCollect("PASSWORDS");
			vtRight = m_pRecordset->GetCollect("RIGHT");
			vUserName = m_pRecordset->GetCollect("NAME");
			
			if (vtPassword.vt != VT_NULL)
			{
				tempPassword = (LPCTSTR)(_bstr_t)vtPassword;
			}
			
			if (vUserName.vt != VT_NULL)
			{
				tempUserName = (LPCTSTR)(_bstr_t)vUserName;
			}
			
			if (vtRight.vt != VT_NULL)
			{
				tempRight =(LPCTSTR)(_bstr_t)vtRight;
			}
			m_pRecordset->MoveNext();
		}
		
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
		return;
	}
	
	SingletonHelper::getInstance()->setUserID(userID);
	SingletonHelper::getInstance()->setUserName(tempUserName);
	SingletonHelper::getInstance()->setUserPass(tempPassword);
	SingletonHelper::getInstance()->setUserRight(tempRight);
	
	//密码正确则进入程序
	if (tempPassword == password)
	{
		if (tempRight == "普通用户")
		{
			CWeightDlg* controlPanel = (CWeightDlg*)(SingletonHelper::getInstance()->getPtrData());
			controlPanel->m_ChangePasswordButton.EnableWindow(FALSE);
			controlPanel->m_MaterialManagementButton.EnableWindow(FALSE);
			controlPanel->m_UserManagementButton.EnableWindow(FALSE);
			controlPanel->m_PowerOffButton.EnableWindow(FALSE);
			controlPanel->m_OtherSettingsButton.EnableWindow(FALSE);
		}
		CDialog::OnOK();
	}
	else
	{
		AfxMessageBox("密码错误，请重新输入！");
		++tryTimes;
	}
}


void CLoginDialog::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD1, 0, 0, 0);
}

void CLoginDialog::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD2, 0, 0, 0);
}

void CLoginDialog::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD3, 0, 0, 0);
}

void CLoginDialog::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD4, 0, 0, 0);
}

void CLoginDialog::OnButton5() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD5, 0, 0, 0);
}

void CLoginDialog::OnButton6() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD6, 0, 0, 0);
}

void CLoginDialog::OnButton7() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD7, 0, 0, 0);
}

void CLoginDialog::OnButton8() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD8, 0, 0, 0);
}

void CLoginDialog::OnButton9() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD9, 0, 0, 0);
}

void CLoginDialog::OnButton0() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD0, 0, 0, 0);
}

void CLoginDialog::OnButtonComma() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(188, 0, 0, 0);
}

void CLoginDialog::OnButtonBack() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_BACK, 0, 0, 0);
}

BOOL CLoginDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CBitmap   bmp;   

	bmp.LoadBitmap(IDB_LOGINDIALOG);//载入图片   

	m_brBk.CreatePatternBrush(&bmp);   

	bmp.DeleteObject();  

	CRect testRect(100,200,900,594);
	this->MoveWindow(&testRect,TRUE);

	// TODO: Add extra initialization here
	buttonVector.push_back(&m_Button1);
	buttonVector.push_back(&m_Button2);
	buttonVector.push_back(&m_Button3);
	buttonVector.push_back(&m_Button4);
	buttonVector.push_back(&m_Button5);	
	buttonVector.push_back(&m_Button6);
	buttonVector.push_back(&m_Button7);	
	buttonVector.push_back(&m_Button8);
	buttonVector.push_back(&m_Button9);
	buttonVector.push_back(&m_Button0);
	buttonVector.push_back(&m_ButtonComma);
	buttonVector.push_back(&m_ButonBack);

	
	CRect rectOK(93, 295, 256, 352);
	CRect rectCancel(313, 295, 477, 352);
	m_ButtonOK.MoveWindow(rectOK, TRUE);
	m_ButtonCancel.MoveWindow(rectCancel, TRUE);

	int left = 557;
	int top = 35;
	int width = 623 - 557;
	int height = 101 - 35;
	int horiSpacer = 635 - 623;
	int vertSpacer = 115 - 101;


		
	for (size_t i = 0; i < buttonVector.size(); ++i)
	{
		CRect startRect(left, top, left + width, top + height);
		buttonVector[i]->MoveWindow(startRect, TRUE);

		if (((i + 1) % 3) == 0)
		{
			left = 557;
			top = startRect.bottom + vertSpacer;
		}
		else
		{
			left = startRect.right + horiSpacer;
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLoginDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	int controlID = LOWORD(wParam);
	if (controlID == IDC_USERNAME_EDIT)
	{
		m_FocusedID = controlID;
	}
	if (controlID == IDC_PASSWORD_EDIT)
	{
		m_FocusedID = controlID;
	}

	return CDialog::OnCommand(wParam, lParam);
}


int CLoginDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

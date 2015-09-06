// LoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "WeightDlg.h"
#include "LoginDialog.h"
#include "HelperClass.h"
#include "DBConnector.h"
#include "DBptr.h"
#include "uiFunctions.h"
#include "Splash.h"

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
	DDX_Control(pDX, IDC_PASSWORD_EDIT, passwordEdit);
	DDX_Control(pDX, IDC_USERNAME_EDIT, useridEdit);
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
	ON_WM_CREATE()
    ON_WM_PAINT()
	ON_WM_ERASEBKGND()
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
	CString userid;
	CString password;
	
	if (tryTimes >= 2)
	{
		AfxMessageBox("��¼���󣬳����˳���");
		SendMessage(WM_CLOSE);   
	}
	
	useridEdit.GetWindowText(userid);
	passwordEdit.GetWindowText(password);
	
	if (userid.IsEmpty() || password.IsEmpty())
	{
		++tryTimes;
		AfxMessageBox("�û���ţ����벻��Ϊ�գ����������룡");
		return;
	}

	CString sql, dbuserid, dbusername, dbpassword, dbpermission;
    sql.Format("select id, password, permission, name from  users where id = %s", userid);

    _RecordsetPtr& m_pRecordset = SQLExecutor::getInstancePtr()->execquery(sql);

	try
	{
        _variant_t vtUserid;
		_variant_t vtPassword;
		_variant_t vtRight;
		_variant_t vUserName;
		int i=0;
		int nIndex = 0;
		
		while(!m_pRecordset->adoEOF)
		{
            vtUserid = m_pRecordset->GetCollect("id");
			vtPassword = m_pRecordset->GetCollect("password");
			vtRight = m_pRecordset->GetCollect("permission");
			vUserName = m_pRecordset->GetCollect("name");
			
            if(vtUserid.vt != VT_NULL)
            {
                dbuserid = (LPCTSTR)(_bstr_t)vtUserid;
            }
			if (vtPassword.vt != VT_NULL)
			{
				dbpassword = (LPCTSTR)(_bstr_t)vtPassword;
			}
			
			if (vUserName.vt != VT_NULL)
			{
				dbusername = (LPCTSTR)(_bstr_t)vUserName;
			}
			
			if (vtRight.vt != VT_NULL)
			{
				dbpermission =(LPCTSTR)(_bstr_t)vtRight;
			}
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
		return;
	}
	
	SingletonHelper::getInstance()->setUserID(dbuserid);
	SingletonHelper::getInstance()->setUserName(dbusername);
	SingletonHelper::getInstance()->setUserPass(dbpassword);
	SingletonHelper::getInstance()->setUserRight(dbpermission);
	
	//������ȷ��������
	if (dbpassword == password)
	{
		if (dbpermission == "��ͨ�û�")
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
		AfxMessageBox("����������������룡");
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
	uiutils::setdlgsize(this);

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

void CLoginDialog::OnPaint()
{
    uiutils::drawDlgBg(this, IDB_MAINPAGE);
}



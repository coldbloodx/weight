// WeightDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Splash.h"
#include "Weight.h"
#include "WeightDlg.h"
#include "FormulaDialog.h"
#include "UserManageDialog.h"
#include "MaterialManagementDialog.h"
#include "OtherSettingsDialog.h"
#include "QueryDialog.h"
#include "LoginDialog.h"
#include "FormulaSelectDialog.h"
#include "FreeWeightDialog.h"
#include "PassChangeDialog.h"
#include "HelperClass.h"

#include "DBConnector.h"
#include "DBptr.h"
#include "PatternLoader.h"

#include "BasicSettingsDialog.h"
#include "WeighManagementDialog.h"
#include "helperclass.h"
#include "uiFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)

END_MESSAGE_MAP()

CWeightDlg::CWeightDlg(CWnd* pParent /*=NULL*/)
: CDialog(CWeightDlg::IDD, pParent),pFormulaDialog(NULL)
{

}

CWeightDlg::~CWeightDlg()
{
	
}

void CWeightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATUS_STATIC, m_StatusStatic);
	DDX_Control(pDX, IDC_FETCHSTUFF_BUTTON, m_FetchStuffButton);
	DDX_Control(pDX, IDC_FORMULAWEIGH_BUTTON, m_FormulaWeighButton);
	DDX_Control(pDX, IDC_WEIGHFREE_BUTTON, m_WeighFreeButton);
	DDX_Control(pDX, IDC_OTHERSETTINGSBUTTON, m_OtherSettingsButton);
	DDX_Control(pDX, IDC_POWEROFF_BUTTON, m_PowerOffButton);
	DDX_Control(pDX, IDC_FORMULAMANAGE_BUTTON, m_FormulaManagementButton);
}

BEGIN_MESSAGE_MAP(CWeightDlg, CDialog)
//{{AFX_MSG_MAP(CWeightDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_POWEROFF_BUTTON, OnPowerOff)
ON_BN_CLICKED(IDC_FORMULAMANAGE_BUTTON, OnFormulaManagement)
ON_BN_CLICKED(IDC_USERMANAGEMENT, OnUsermanagement)
ON_BN_CLICKED(IDC_MATERIALMANAGEMENT_BUTTON, OnMaterialmanagementButton)
ON_BN_CLICKED(IDC_FORMULAWEIGH_BUTTON, OnWightstartButton)
ON_BN_CLICKED(IDC_CHANGEPASSWORD_BUTTON, OnChangepasswordButton)
ON_BN_CLICKED(IDC_WEIGHFREE_BUTTON, OnWeighfreeButton)
ON_BN_CLICKED(IDC_FETCHSTUFF_BUTTON, OnFetchstuffButton)
ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWeightDlg message handlers

BOOL CWeightDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
		
	//set com baud rate
	PatternLoader patternLoader(std::string("config.xml"));
	patternLoader.loadPattern("ConfigPattern");

	SingletonHelper::getInstance()->setCom1BaudRate(patternLoader.pattern.com1.c_str());
	SingletonHelper::getInstance()->setCom2BaudRate(patternLoader.pattern.com2.c_str());
	

	//show login window
	CLoginDialog loginDialog;
	SingletonHelper::getInstance()->setPtrData((void*)this);


	//cancel login
	//点击cancel 直接退出程序
	if (loginDialog.DoModal() == IDCANCEL)
	{
		return TRUE;
	}

	CSplashWnd::ShowSplashScreen(this);

	::Sleep(1500);
	//load background
	CSplashWnd::CloseSplashScreen();
	this->Invalidate();

	//update main window buttons

    CButton* buttonArray[6] = { &m_WeighFreeButton,&m_FormulaWeighButton,&m_FormulaManagementButton,
				 &m_FetchStuffButton,&m_OtherSettingsButton,&m_PowerOffButton };

    uiutils::init2rowbtns(buttonArray, 6);
	this->UpdateData(TRUE);

	uiutils::setdlgsize(this, false);   

	utils::showStatus(m_StatusStatic);
	SetTimer(1000, 1000, NULL);
 
	return TRUE; 
}

void CWeightDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWeightDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
        uiutils::drawDlgBg(this, IDB_MAINPAGE);
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWeightDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWeightDlg::OnPowerOff() 
{
	//关闭计算机
	CString msg("确定要关闭计算机么？");
	CString caption("关机确认");
	//选择cancel则返回
	if (MessageBox(msg, caption, MB_OKCANCEL) != IDOK)
	{
		return;
	}
	//备份数据库
	CString fileName("weight.mdb");
	CString filePath;
	char buffer[512];
	::GetCurrentDirectory(512, buffer);
	filePath = buffer;
	CString oldFileName = filePath + "\\" + fileName;

	CTime currentTime = CTime::GetCurrentTime();
	CString surfix = currentTime.Format("%Y-%m-%d-%H-%M-%S");
	CString newFileName = filePath + "\\bak\\" + surfix + "-" + fileName;
	BOOL nret = CopyFile(oldFileName, newFileName, FALSE);
	if (nret == 1)
	{
		AfxMessageBox("数据库已经备份");
	}
	else
	{
		AfxMessageBox("数据库备份失败，请检查根目录下bak文件夹是否存在");
	}

	//关闭计算机的具体步骤
	HANDLE hToken;   
	TOKEN_PRIVILEGES tkp;   
	OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,
		&hToken);   
	LookupPrivilegeValue(NULL,
		SE_SHUTDOWN_NAME,
		&tkp.Privileges[0].Luid);   
	tkp.PrivilegeCount = 1;	 //   设置一个权限   
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;   
	AdjustTokenPrivileges(hToken,
		FALSE,
		&tkp,
		0,
		(PTOKEN_PRIVILEGES)NULL,
		0);     
	::ExitWindowsEx(EWX_SHUTDOWN ,0);   
}

void CWeightDlg::OnFormulaManagement() 
{
	CMainSettings weighManagementDialog;
	weighManagementDialog.DoModal();
}

void CWeightDlg::OnUsermanagement() 
{
	// TODO: Add your control notification handler code here
	CUserManageDialog userManagementDialog;
	userManagementDialog.DoModal();
}

void CWeightDlg::OnMaterialmanagementButton() 
{
	// TODO: Add your control notification handler code here
	CMaterialManagementDialog materialManagementDialog;
	materialManagementDialog.DoModal();
}


void CWeightDlg::OnQueryButton() 
{
	// TODO: Add your control notification handler code here
	CQueryDialog queryDialog;
	queryDialog.DoModal();
}

void CWeightDlg::OnWightstartButton() 
{
	// TODO: Add your control notification handler code here
	CFormulaSelectDialog formulaSelectDialog;
	formulaSelectDialog.DoModal();
}



void CWeightDlg::OnChangepasswordButton() 
{
	// TODO: Add your control notification handler code here
	CPassChangeDialog passChangeDialog;
	passChangeDialog.DoModal();
}


void CWeightDlg::OnWeighfreeButton() 
{
	// TODO: Add your control notification handler code here
	CFreeWeightDialog freeWeighDialog;
	freeWeighDialog.DoModal();
}

void CWeightDlg::OnFetchstuffButton() 
{
	// TODO: Add your control notification handler code here
	CFormulaDialog formulaDialog;
	formulaDialog.DoModal();
}

void CWeightDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	utils::showStatus(m_StatusStatic); 
	CDialog::OnTimer(nIDEvent);
}

BOOL CWeightDlg::PreTranslateMessage(MSG* pMsg)
{
	if(WM_KEYDOWN == pMsg->message ) 
	{ 
		UINT nKey = (int) pMsg->wParam; 
		if( VK_RETURN == nKey || VK_ESCAPE == nKey ) 
			return TRUE ; 
	}
	return CDialog::PreTranslateMessage(pMsg); 
}


void CWeightDlg::OnCancel()
{
	if (SingletonHelper::getInstance()->getUserRight() != "管理员")
	{
		return;
	}
	else
	{
		CDialog::OnCancel();
	}
	
}


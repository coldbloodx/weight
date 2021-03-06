// Weight.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Weight.h"
#include "WeightDlg.h"
#include "HelperClass.h"

#include "DBConnector.h"
#include "DBptr.h"
#include "Splash.h"
#include "skin/SkinMagicLib.h"
#pragma comment(lib, "skin/SkinMagicTrial.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWeightApp

BEGIN_MESSAGE_MAP(CWeightApp, CWinApp)
	//{{AFX_MSG_MAP(CWeightApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWeightApp construction

CWeightApp::CWeightApp():puser(NULL)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWeightApp object

CWeightApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWeightApp initialization

BOOL CWeightApp::InitInstance()
{
	//this for splash screen
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);      
	CSplashWnd::EnableSplashScreen(TRUE);
	//this line init the ole object for database connection
	AfxOleInit();
	if (!InitATL())
		return FALSE;

	AfxEnableControlContainer();
	_Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);

	//Active initialize the singleton 
	SingletonHelper::getInstance()->initFonts();
	//CNavigatorPanel::getNavigatorPanelPtr();
	try
	{
		DBConnector::getInstanceRef().openDatabaseConnection();
	}
	catch(_com_error)
	{
		AfxMessageBox("数据库连接出错，程序将退出！");
		return TRUE;
	}
	
	// 初始化SkinMagic库
	VERIFY(InitSkinMagicLib(AfxGetInstanceHandle(), "MonitorDir", NULL, NULL));

	// 从资源中加载皮肤文件。也可以用代码“LoadSkinFile("corona.smf")”直接从文件中加载

	//if(LoadSkinFromResource(AfxGetInstanceHandle(), (LPCTSTR)IDR_SKINMAGIC1, "SKINMAGIC"))
    if(LoadSkinFile("skins\\AlphaOS.smf"))
	{
		// 设置对话框默认皮肤
		SetDialogSkin("Dialog");
	}


#ifdef _AFXDLL
#else
	//Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CWeightDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	return FALSE;
}

#include <initguid.h>

	
CWeightModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

LONG CWeightModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CWeightModule::Lock()
{
	AfxOleLockApp();
	return 1;
}


int CWeightApp::ExitInstance()
{

	return CWinApp::ExitInstance();
}

BOOL CWeightApp::InitATL()
{
	m_bATLInited = TRUE;

	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	_Module.dwThreadID = GetCurrentThreadId();

	return TRUE;

}

CWeightApp::~CWeightApp()
{
	//do some cleaning job...
	SingletonHelper::removeInstance();
	try
	{
		SQLExecutor::getInstanceRef().closeRecordSet();
	}
	catch (_com_error& e)
	{
		e;
	}

	//handle exception when close database
	try
	{
		DBConnector::getInstanceRef().closeDatabaseConnection();
	}
	catch (_com_error& e)
	{
		e;
	}

	DBConnector::RemoveInstance();
	SQLExecutor::RemoveInstance();

	if(puser)
	{
		delete puser;
		puser = NULL;
	}

	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
	}
	//===SkinMagic===
	// 释放SkinMagic库申请的内存
	ExitSkinMagicLib();
	//===SkinMagic===
}

BOOL CWeightApp::PreTranslateMessage(MSG* pMsg)
{
	// Route messages to the splash screen while it is visible
	if (CSplashWnd::PreTranslateAppMessage(pMsg)) 
	{
		return TRUE;
	}
	return CWinApp::PreTranslateMessage(pMsg);
}

CWeightApp* CWeightApp::getapp()
{
	return (CWeightApp*)AfxGetApp();
}

CString CWeightApp::getuserid()
{
	return CWeightApp::getapp()->puser->getid();
}

CString CWeightApp::getusername()
{
	return CWeightApp::getapp()->puser->getname();
}

CString CWeightApp::getuserpass()
{
	return CWeightApp::getapp()->puser->getpass();
}

USERPERM CWeightApp::getuserperm()
{
	return CWeightApp::getapp()->puser->getperm();
}
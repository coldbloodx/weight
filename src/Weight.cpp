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

CWeightApp::CWeightApp()
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
	catch(_com_error& e)
	{
		//to do 
		//add the except into log
		e;
		AfxMessageBox("数据库连接出错，程序将退出！");
		return TRUE;
	}
	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

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
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel

	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
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
	//CNavigatorPanel::removeInstance();
	//handle exception when close recordset
	try
	{
		SQLExecutor::getInstanceRef().closeRecordSet();
	}
	catch (_com_error& e)
	{
		//to do 
		//add the except into log
		e;
	}

	//handle exception when close database
	try
	{
		DBConnector::getInstanceRef().closeDatabaseConnection();
	}
	catch (_com_error& e)
	{
		//to do 
		//add the except into log
		e;
	}




	DBConnector::RemoveInstance();
	SQLExecutor::RemoveInstance();
	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
	}

	// TODO: Add your specialized code here and/or call the base class


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
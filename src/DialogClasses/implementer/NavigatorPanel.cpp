// NavigatorPanel.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\NavigatorPanel.h"
#include "..\..\OtherClasses\HelperClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNavigatorPanel dialog

CNavigatorPanel::CNavigatorPanel(CWnd* pParent /*=NULL*/)
	: CCustomColorDialog(CNavigatorPanel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNavigatorPanel)
	//}}AFX_DATA_INIT
}

CNavigatorPanel* CNavigatorPanel::m_Instance = NULL;
const int CNavigatorPanel::TIMERID = 6888;


CNavigatorPanel* CNavigatorPanel::getNavigatorPanelPtr()
{
	if (m_Instance == NULL)
	{
		m_Instance = new CNavigatorPanel;
		return m_Instance;
	}
	return m_Instance;
}

void CNavigatorPanel::removeInstance()
{
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}

void CNavigatorPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNavigatorPanel)
	DDX_Control(pDX, IDC_USER_DYNAMIC, m_User);
	DDX_Control(pDX, IDC_TIME_DYNAMIC, m_Time);
	DDX_Control(pDX, IDC_JOB_DYNAMIC, m_Job);
	DDX_Control(pDX, IDC_DATE_DYNAMIC, m_Date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNavigatorPanel, CDialog)
	//{{AFX_MSG_MAP(CNavigatorPanel)
	ON_WM_CANCELMODE()
	ON_WM_TIMER()
	ON_WM_CAPTURECHANGED()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNavigatorPanel message handlers

void CNavigatorPanel::setJobString(const CString& jobString)
{
	m_Job.SetWindowText(jobString);
	return;
}

void CNavigatorPanel::setUserName(const CString& userName)
{
	m_User.SetWindowText(userName);
	return;
}

BOOL CNavigatorPanel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Date.SetWindowText(HelperFunctions::getCurrentDate());
	m_Time.SetWindowText(HelperFunctions::getCurrentTime());
	SetTimer(TIMERID, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNavigatorPanel::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_Date.SetWindowText(HelperFunctions::getCurrentDate());
	m_Time.SetWindowText(HelperFunctions::getCurrentTime());
	CDialog::OnTimer(nIDEvent);
}

BOOL CNavigatorPanel::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	// block esc and enter key
	if(WM_KEYDOWN == pMsg->message ) 
	{ 
		UINT nKey = (int) pMsg->wParam; 
		if( VK_RETURN == nKey || VK_ESCAPE == nKey ) 
			return TRUE ; 
	}
	if (pMsg->message == WM_SYSKEYDOWN)
	{
		if (pMsg->wParam == VK_F4)
		{
			return TRUE;
		}
    }
	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CNavigatorPanel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CCustomColorDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

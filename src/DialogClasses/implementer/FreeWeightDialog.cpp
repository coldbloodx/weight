// FreeWeightDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\FreeWeightDialog.h"
#include "..\..\OtherClasses\HelperClass.h"
#include "..\..\OtherClasses\uiFunctions.h"
#include <iterator>
#include <vector>
using std::vector;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFreeWeightDialog dialog


CFreeWeightDialog::CFreeWeightDialog(CWnd* pParent /*=NULL*/)
: CDialog(CFreeWeightDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFreeWeightDialog)
	//}}AFX_DATA_INIT
}


void CFreeWeightDialog::DoDataExchange(CDataExchange* pDX)
{

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFreeWeightDialog)
	//DDX_Control(pDX, IDC_STATUS_STATIC, m_StatusStatic);
	DDX_Control(pDX, IDC_COM2DATA_STATIC, m_Com2DataStatic);
	DDX_Control(pDX, IDC_COM1DATA_STATIC, m_Com1DataStatic);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_FWLABEL, fwLabel);
	DDX_Control(pDX, IDC_FWBIG, fwBig);
	DDX_Control(pDX, IDC_FWSMALL, fwSmall);

}


BEGIN_MESSAGE_MAP(CFreeWeightDialog, CDialog)
//{{AFX_MSG_MAP(CFreeWeightDialog)
ON_WM_TIMER()
//}}AFX_MSG_MAP
ON_WM_CTLCOLOR()
ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFreeWeightDialog message handlers

void CFreeWeightDialog::OnOK() 
{
	// TODO: Add extra validation here
	//closeCom(SingletonHelper::getInstance()->com1);

	CDialog::OnOK();
}

BOOL CFreeWeightDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//init comPort;
	int comRate;
	comRate = atoi(SingletonHelper::getInstance()->getCom1BaudRate().GetBuffer(0));
	com1 = HelperFunctions::initCom(SingletonHelper::getInstance()->com1,
		CString("COM1"),
		comRate);
	
	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_FREEWEIGHT);//载入图片   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();   


	uiFunctions::setdlgsize(this);


	m_Com1DataStatic.SetWindowText("请稍等...");
	m_Com2DataStatic.SetWindowText("请稍等...");

	if (com1 < 0)
	{
		AfxMessageBox("com1初始化失败！请将此对话框关闭重试！");
	}
	comRate = atoi(SingletonHelper::getInstance()->getCom2BaudRate().GetBuffer(0));
	com2 = HelperFunctions::initCom(SingletonHelper::getInstance()->com2,
		CString("COM2"),
		comRate);
	
	if (com2 < 0)
	{
		AfxMessageBox("com2初始化失败！请将此对话框关闭重试！");
	}
	SetTimer(1,1000,NULL);
	


	CStatic* sarray[4] = {&m_Com1DataStatic, &m_Com2DataStatic, 
				 &fwBig, &fwSmall};
	
	for (int i = 0; i < 4; ++i)
	{
		sarray[i]->SetFont(SingletonHelper::getInstance()->simhei80, TRUE);
	}
	fwLabel.SetFont(SingletonHelper::getInstance()->simHei40, TRUE);


	return TRUE;  // return TRUE unless you set the focus to a control

}

CFreeWeightDialog::~CFreeWeightDialog()
{
}

void CFreeWeightDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//HelperFunctions::showStatus(m_StatusStatic);
	
	//format time
	CTime time = CTime::GetCurrentTime();
	CString currentTime = time.Format("%Y:%m:%d:%X:   ");
	
	//read data and format data
	CString com1Result,com2Result;
	if (com1 >= 0)
	{
		com1Result = HelperFunctions::readCom(SingletonHelper::getInstance()->com1);
	}
	
	if (com2 >= 0)
	{
		com2Result = HelperFunctions::readCom(SingletonHelper::getInstance()->com2);
	}
	
	
	com1Result = com1Result.IsEmpty() ? "0000.0" : com1Result;
	com2Result = com2Result.IsEmpty() ? "000.00" : com2Result;
	
	RECT rect;	
	m_Com1DataStatic.SetWindowText(com2Result);
	m_Com1DataStatic.GetWindowRect(&rect);   
	m_Com1DataStatic.GetParent()->ScreenToClient(&rect);
	m_Com1DataStatic.GetParent()->InvalidateRect(&rect, TRUE);

	m_Com2DataStatic.SetWindowText(com1Result);
	m_Com2DataStatic.GetWindowRect(&rect);   
	m_Com2DataStatic.GetParent()->ScreenToClient(&rect);
	m_Com2DataStatic.GetParent()->InvalidateRect(&rect, TRUE);
	
	
	CDialog::OnTimer(nIDEvent);
}



void CFreeWeightDialog::OnDestroy()
{
	CDialog::OnDestroy();
	HelperFunctions::closeCom(SingletonHelper::getInstance()->com1);
	HelperFunctions::closeCom(SingletonHelper::getInstance()->com2);
	// TODO: Add your message handler code here
}

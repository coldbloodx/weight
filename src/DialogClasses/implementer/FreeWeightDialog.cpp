// FreeWeightDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "FreeWeightDialog.h"
#include "HelperClass.h"
#include "uiFunctions.h"
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
	DDX_Control(pDX, IDC_COM2DATA_STATIC, m_Com2DataStatic);
	DDX_Control(pDX, IDC_COM1DATA_STATIC, m_Com1DataStatic);
	DDX_Control(pDX, IDOK, m_ButtonOK);
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
	CDialog::OnOK();
}

BOOL CFreeWeightDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int comRate;
	ConfParser parser("config.xml");
	parser.load();

	comRate = atoi(parser.getcom1rate().c_str());
	com1 = utils::initcom(SingletonHelper::getInstance()->com1,
		CString("COM1"),
		comRate);

	uiutils::setdlgsize(this, &m_ButtonOK);

	m_Com1DataStatic.SetWindowText("请稍等...");
	m_Com2DataStatic.SetWindowText("请稍等...");

	if (com1 < 0)
	{
		AfxMessageBox("com1初始化失败！请将此对话框关闭重试！");
	}

	comRate = atoi(parser.getcom2rate().c_str());
	com2 = utils::initcom(SingletonHelper::getInstance()->com2,
		CString("COM2"),
		comRate);
	
	if (com2 < 0)
	{
		AfxMessageBox("com2初始化失败！请将此对话框关闭重试！");
	}
	SetTimer(1,1000,NULL);
	
	CStatic* sarray[4] = {&m_Com1DataStatic, &m_Com2DataStatic, &fwBig, &fwSmall};
	
	for (int i = 0; i < 4; ++i)
	{
		sarray[i]->SetFont(SingletonHelper::getInstance()->simhei80, TRUE);
	}
	fwLabel.SetFont(SingletonHelper::getInstance()->simHei40, TRUE);

	return TRUE;  
}

CFreeWeightDialog::~CFreeWeightDialog()
{
}

void CFreeWeightDialog::OnTimer(UINT nIDEvent) 
{
	//format time
	CTime time = CTime::GetCurrentTime();
	CString currentTime = time.Format("%Y:%m:%d:%X:   ");
	
	CString com1Result,com2Result;
	if (com1 >= 0)
	{
		com1Result = utils::readcom(SingletonHelper::getInstance()->com1);
	}
	
	if (com2 >= 0)
	{
		com2Result = utils::readcom(SingletonHelper::getInstance()->com2);
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
	utils::closecom(SingletonHelper::getInstance()->com1);
	utils::closecom(SingletonHelper::getInstance()->com2);
}

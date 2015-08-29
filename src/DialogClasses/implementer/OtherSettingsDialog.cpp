// OtherSettingsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "OtherSettingsDialog.h"
#include "HelperClass.h"
#include "uifunctions.h"
#include "PatternLoader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COtherSettingsDialog dialog


COtherSettingsDialog::COtherSettingsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COtherSettingsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COtherSettingsDialog)
	//}}AFX_DATA_INIT
}


void COtherSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COtherSettingsDialog)
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_RESTOREDATABASE, m_Restore);
	DDX_Control(pDX, IDC_BACKUPDATABASE, m_Backup);
	DDX_Control(pDX, IDC_COM2RATE_COMBO, m_Com2Rate);
	DDX_Control(pDX, IDC_COM1RATE_COMBO, m_Com1Rate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COtherSettingsDialog, CDialog)
	//{{AFX_MSG_MAP(COtherSettingsDialog)
	ON_BN_CLICKED(IDC_BACKUPDATABASE, OnBackupdatabase)
	ON_BN_CLICKED(IDC_RESTOREDATABASE, OnRestoredatabase)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COtherSettingsDialog message handlers

BOOL COtherSettingsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CBitmap   bmp;   

	bmp.LoadBitmap(IDB_OTHERSETTINGS);//载入图片   
	m_brBk.CreatePatternBrush(&bmp);   
	bmp.DeleteObject();   

	// TODO: Add extra initialization here
	size_t i = m_Com1Rate.FindString(0,SingletonHelper::getInstance()->getCom1BaudRate());
	m_Com1Rate.SetCurSel(i);
	i = m_Com2Rate.FindString(0, SingletonHelper::getInstance()->getCom2BaudRate());
	m_Com2Rate.SetCurSel(i);

	fileName = "weight.mdb";
	char buffer[512];
	::GetCurrentDirectory(512, buffer);
	filePath = buffer;
	oldFileName = filePath + "\\" + fileName;

    uiFunctions::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void COtherSettingsDialog::OnOK() 
{
	// TODO: Add extra validation here
	CString rate1;
	CString rate2;

	m_Com1Rate.GetWindowText(rate1);
	m_Com2Rate.GetWindowText(rate2);

	AfxMessageBox("com1波特率：" + rate1 + "\rcom2波特率：" + rate2);

	SingletonHelper::getInstance()->setCom1BaudRate(rate1);
	SingletonHelper::getInstance()->setCom2BaudRate(rate2);
	
	PatternLoader patternLoader("config.xml");
	patternLoader.loadPattern("ConfigPattern");
	patternLoader.pattern.com1 = rate1.GetBuffer(0);
	patternLoader.pattern.com2 = rate2.GetBuffer(0);
	patternLoader.savePattern();

	CDialog::OnOK();
}

void COtherSettingsDialog::OnBackupdatabase() 
{
	// TODO: Add your control notification handler code here
	CTime currentTime = CTime::GetCurrentTime();
	CString surfix = currentTime.Format("%Y-%m-%d-%H-%M-%S");
	CString newFileName = filePath + "\\bak\\" + surfix + "-"+ fileName;
	BOOL nret = CopyFile(oldFileName, newFileName, FALSE);
	if (nret == 1)
	{
		AfxMessageBox("数据库已经备份");
	}
	else
	{
		AfxMessageBox("数据库备份失败，请检查根目录下bak文件夹是否存在");
	}

}

void COtherSettingsDialog::OnRestoredatabase() 
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDialog(TRUE);
	CString inputFile;
	if (fileDialog.DoModal() == IDOK)
	{
		inputFile = fileDialog.GetPathName();
	}
	BOOL nret = CopyFile(inputFile, oldFileName, FALSE);
}

COtherSettingsDialog::~COtherSettingsDialog()
{

}


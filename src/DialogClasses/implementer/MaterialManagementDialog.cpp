// MaterialManagementDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\MaterialManagementDialog.h"
#include <string>
#include <vector>
#include "..\..\DialogClasses\header\MaterialAddDialog.h"
#include "..\..\OtherClasses\HelperClass.h"
#include "..\..\OtherClasses\DatabaseConnector.h"
#include "..\..\OtherClasses\RecordSetPointer.h"
#include "..\..\OtherClasses\uiFunctions.h"
#include "..\..\BatchNumberChange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaterialManagementDialog dialog


CMaterialManagementDialog::CMaterialManagementDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMaterialManagementDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMaterialManagementDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMaterialManagementDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterialManagementDialog)
	DDX_Control(pDX, IDC_STATUS_STATIC, m_StatusStatic);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_MATERIALDEL, m_Del);
	DDX_Control(pDX, IDC_MATERIALADD, m_Add);
	DDX_Control(pDX, IDC_MATERIALLIST, m_MaterialList);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BATCHNUMBERCHANGE, m_BatchNumberChange);
}

BEGIN_MESSAGE_MAP(CMaterialManagementDialog, CDialog)
	//{{AFX_MSG_MAP(CMaterialManagementDialog)
	ON_BN_CLICKED(IDC_MATERIALADD, OnMaterialadd)
	ON_BN_CLICKED(IDC_MATERIALDEL, OnMaterialdel)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BATCHNUMBERCHANGE, &CMaterialManagementDialog::OnBnClickedBatchnumberchange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaterialManagementDialog message handlers

BOOL CMaterialManagementDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	initListHeader();
	initList();
	// TODO: Add extra initialization here
	CBitmap   bmp;   

	bmp.LoadBitmap(IDB_MATERIALMANAGEMENT);//载入图片   

	m_brBk.CreatePatternBrush(&bmp);   

	bmp.DeleteObject(); 

	CRect wndRect((1024 - 960) / 2, (768 - 551) / 2 , (1024 - 960) / 2 + 960 , (768 - 551) / 2 + 570);
	this->MoveWindow(wndRect);
	
	CRect addRect(505, 42, 620, 80 );
	m_Add.MoveWindow(addRect);
	m_Add.DrawBorder(FALSE);
	m_Add.DrawTransparent(TRUE);

	//去掉删除按钮！
	//CRect delRect(650, 43, 765, 80);
	CRect delRect(0, 0, 0, 0);
	m_Del.MoveWindow(delRect);
	m_Del.DrawBorder(FALSE);
	m_Del.DrawTransparent(TRUE);

	//CRect changeRect(792, 42, 905, 80);
	CRect changeRect(650, 43, 765, 80);
	m_BatchNumberChange.MoveWindow(changeRect);
	m_BatchNumberChange.DrawBorder(FALSE);
	m_BatchNumberChange.DrawTransparent(TRUE);


	CRect backRect(175, 455, 262, 478);
	m_ButtonOK.MoveWindow(backRect);

	m_ButtonOK.DrawBorder(FALSE);
	m_ButtonOK.DrawTransparent(TRUE);

	CRect listRect(264, 96, 918, 494);
	m_MaterialList.MoveWindow(listRect);

	//buttonVector.push_back(&m_Add);
	//buttonVector.push_back(&m_Del);
	//buttonVector.push_back(&m_ButtonOK);

	//for(size_t i = 0; i < buttonVector.size(); ++i)
	//{
	//	HelperFunctions::setButtonStyle(*buttonVector[i], RGB(55,71,158), SingletonHelper::getInstance()->simSong20);
	//}
	
	//HelperFunctions::showStatus(m_StatusStatic);
	//SetTimer(1000,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CMaterialManagementDialog::~CMaterialManagementDialog()
{

}

void CMaterialManagementDialog::initListHeader()
{
	std::vector<std::string> headerList;
	headerList.push_back("材料编号");
	headerList.push_back("材料名称");
	headerList.push_back("材料条码");
	headerList.push_back("制造厂商");
	for (int i = 0; i< (int)headerList.size(); ++i)
	{
		m_MaterialList.InsertColumn(i,headerList[i].c_str(), 0, 160);
	}
}

void CMaterialManagementDialog::initList()
{
	//init recordset pointer
	RecordSetPointer::getInstanceRef().setSqlState(CString("SELECT * FROM MATERIALS"));

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
	
	CString headerArray[4] = {"ID", "NAME","BATCHNUMBER","MANUFACTURE"};
	std::vector<CString> headerList(headerArray, headerArray + 4);

	uiFunctions::updateList(m_pRecordset, m_MaterialList, headerList);
}

void CMaterialManagementDialog::OnMaterialadd() 
{
	// TODO: Add your control notification handler code here
	CMaterialAddDialog materialAddDialog;
	materialAddDialog.m_MaterialManageWindow = this;
	materialAddDialog.DoModal();
}

void CMaterialManagementDialog::OnMaterialdel() 
{
	// TODO: Add your control notification handler code here

	POSITION pos = m_MaterialList.GetFirstSelectedItemPosition() - 1;

	CString ID = m_MaterialList.GetItemText((int)pos, 0);

	if (ID.IsEmpty())
	{
		AfxMessageBox("请在下表中选择要删除的材料!");
		return;
	}
	CString msg("您确定要删除这种材料？");
	CString caption("删除材料");
	//选择cancel则返回
	if (IDCANCEL == MessageBox(msg, caption, MB_OKCANCEL))
	{
		return;
	}

// 	if (ID == "9999")
// 	{
// 		AfxMessageBox("该材料为系统保留，不能删除！");
// 		return;
// 	}

	//init recordset pointer
	RecordSetPointer::getInstanceRef().setSqlState(CString("SELECT * FROM MATERIALS"));

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
	


	m_MaterialList.DeleteAllItems();
	initList();
}

void CMaterialManagementDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}

HBRUSH CMaterialManagementDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if   (pWnd   ==   this)   
	{   
		return   m_brBk;   
	}   
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if   (nCtlColor   ==   CTLCOLOR_STATIC)   
	{     
		pDC->SetBkMode(TRANSPARENT);	//透明   
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	}  
	return hbr;
}


void CMaterialManagementDialog::OnBnClickedBatchnumberchange()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_MaterialList.GetFirstSelectedItemPosition() - 1;

	CString ID = m_MaterialList.GetItemText((int)pos, 0);

	if (ID.IsEmpty())
	{
		AfxMessageBox("请在下表中选择修的材料!");
		return;
	}
	
	SingletonHelper::getInstance()->setFormulaID(ID);
	SingletonHelper::getInstance()->setPtrData((void*)this);
	CBatchNumberChage batchNumberchange;
	batchNumberchange.DoModal();
}

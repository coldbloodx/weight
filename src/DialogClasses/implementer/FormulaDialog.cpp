// FormulaDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\FormulaDialog.h"
#include "..\..\DialogClasses\header\FormulaAddDialog.h"
#include "..\..\DialogClasses\header\MaterialCountInputDialog.h"
#include "..\..\DialogClasses\header\FetchAmountInputDialog.h"
#include "..\..\OtherClasses\HelperClass.h"
#include "..\..\OtherClasses\DatabaseConnector.h"
#include "..\..\OtherClasses\RecordSetPointer.h"
#include "..\..\OtherClasses\uiFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormulaDialog dialog


CFormulaDialog::CFormulaDialog(CWnd* pParent /*=NULL*/)
: CDialog(CFormulaDialog::IDD, pParent),m_FormulaAdd(NULL),m_FormulaDel(NULL), m_FetchButton(NULL), m_From(0)
{
	//{{AFX_DATA_INIT(CFormulaDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT	
}


void CFormulaDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormulaDialog)
	//DDX_Control(pDX, IDC_STATIC6, m_StatusStatic);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	//	DDX_Control(pDX, IDC_FORMULAFETCH_BUTTON, m_FetchButton);
	//	DDX_Control(pDX, IDC_FORMULA_DEL, m_FormulaDel);
	//	DDX_Control(pDX, IDC_FORMULA_ADD, m_FormulaAdd);
	DDX_Control(pDX, IDC_FORMULA_LISTCTRL, m_FormulaListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormulaDialog, CDialog)
	//{{AFX_MSG_MAP(CFormulaDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_FORMULA_ADD, OnFormulaAdd)
	ON_BN_CLICKED(IDC_FORMULA_DEL, OnFormulaDel)
	ON_BN_CLICKED(IDC_FORMULAFETCH_BUTTON, OnFormulaFetch)
	ON_WM_TIMER()

	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormulaDialog message handlers

int CFormulaDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

CFormulaDialog::~CFormulaDialog()
{
	if (m_FormulaAdd)
	{
		delete m_FormulaAdd;
		m_FormulaAdd = NULL;
	}
	if (m_FormulaDel)
	{
		delete m_FormulaDel;
		m_FormulaDel = NULL;
	}
	if (m_FetchButton)
	{
		delete m_FetchButton;
		m_FetchButton = NULL;
	}
}


void CFormulaDialog::OnFormulaAdd() 
{
	SingletonHelper::getInstance()->setPtrData((void*)this);
	// TODO: Add your control notification handler code here
	CMaterialCountInputDialog materialCountInputDialog;
	materialCountInputDialog.DoModal();
	return;
}

void CFormulaDialog::initList()
{
	m_FormulaListCtrl.DeleteAllItems();
	CString sqlState = "SELECT * FROM FORMULAS";

	//init recordset pointer
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

	CString headerArray[4] = {"ID", "NAME", "MATERIAL", "TOTAL"};
	std::vector<CString> headerList(headerArray, headerArray + 4);

	uiFunctions::updateList(m_pRecordset, m_FormulaListCtrl, headerList);
}


BOOL CFormulaDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//HelperFunctions::showStatus(m_StatusStatic);
	SetTimer(1000,1000,NULL);
	// TODO: Add extra initialization here
	if (SingletonHelper::getInstance()->getUserRight() == "普通用户")
	{
		m_FormulaAdd->EnableWindow(FALSE);
		m_FormulaDel->EnableWindow(FALSE);
	}
	initListHeader();
	initList();

	m_FormulaAdd = new CButtonST;

	m_FormulaDel	= new CButtonST;

	m_FetchButton = new CButtonST;
	
	CRect wndRect((1024 - 960) / 2, (768 - 566) / 2, (1024 - 960) / 2 + 960, (768 - 566) / 2 + 580);
	this->MoveWindow(wndRect);

	if (m_From == 1)
	{
		CBitmap   bmp;   
		bmp.LoadBitmap(IDB_FORMULAMANAGEMENT);//载入图片   
		m_brBk.CreatePatternBrush(&bmp); 
		bmp.DeleteObject();   

		m_FormulaAdd->Create("", SW_HIDE, CRect(505,42,620,80), this, 1000);
		m_FormulaDel->Create("", SW_HIDE, CRect(651,42,767,80), this, 2000);
		m_FormulaAdd->DrawBorder(FALSE);
		m_FormulaAdd->DrawTransparent(TRUE);
		m_FormulaDel->DrawBorder(FALSE);
		m_FormulaDel->DrawTransparent(TRUE);

		m_FormulaAdd->SetWindowText("增加配方");
		m_FormulaDel->SetWindowText("删除配方");
		m_FormulaAdd->ShowWindow(SW_SHOW);
		m_FormulaDel->ShowWindow(SW_SHOW);

		CRect listRect(261, 95, 921, 497);
		m_FormulaListCtrl.MoveWindow(listRect);
		//buttonVector.push_back(m_FormulaAdd);
		//buttonVector.push_back(m_FormulaDel);
	}

	if (m_From == 0)
	{
		CBitmap   bmp;   
		bmp.LoadBitmap(IDB_FORMULAFETCH);//载入图片   
		m_brBk.CreatePatternBrush(&bmp); 
		bmp.DeleteObject();   
		this->SetWindowText("");
		m_FetchButton->Create("", SW_HIDE, CRect(505,58,620,88), this,3000);
		m_FetchButton->DrawBorder(FALSE);
		m_FetchButton->DrawTransparent(TRUE);
		m_FetchButton->ShowWindow(SW_SHOW);
		//buttonVector.push_back(m_FetchButton);
		CRect listRect(265, 107, 905, 497);
		m_FormulaListCtrl.MoveWindow(listRect);
	}


	CRect backRect(170,450,260,475);
	m_ButtonOK.MoveWindow(backRect);
	m_ButtonOK.DrawBorder(FALSE);
	m_ButtonOK.DrawTransparent(TRUE);


	//buttonVector.push_back(&m_ButtonOK);

	//for(size_t i = 0; i < buttonVector.size(); ++i)
	//{
	//	HelperFunctions::setButtonStyle(*buttonVector[i], RGB(55,71,158), SingletonHelper::getInstance()->simSong20);
	//}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CFormulaDialog::initListHeader()
{
	std::string headerArray[4] = {"配方编号","配方名称","配方内容","成品总量"};
	std::vector<std::string> headerList(headerArray, headerArray+4);
	for (int i = 0; i< (int)headerList.size(); ++i)
	{
		m_FormulaListCtrl.InsertColumn(i,headerList[i].c_str(), 0, 160);
	}
}

void CFormulaDialog::OnFormulaDel() 
{
	// TODO: Add your control notification handler code here
	CString sqlState = "SELECT * FROM FORMULAS";
	POSITION pos = m_FormulaListCtrl.GetFirstSelectedItemPosition() - 1;

	CString ID = m_FormulaListCtrl.GetItemText((int)pos, 0);

	if (ID.IsEmpty())
	{
		AfxMessageBox("请在下表中选择需要删除的配方！");
		return;
	}

	CString msg("您确定要删除该配方？");
	CString caption("删除配方");
	//选择cancel则返回
	if (IDCANCEL == MessageBox(msg, caption, MB_OKCANCEL))
	{
		return;
	}

	//init recordset pointer
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

	m_FormulaListCtrl.DeleteAllItems();
	initList();
}

void CFormulaDialog::OnFormulaFetch() 
{
	POSITION pos = m_FormulaListCtrl.GetFirstSelectedItemPosition() - 1;
	CString ID = m_FormulaListCtrl.GetItemText((int)pos, 0);
	if (ID.IsEmpty())
	{
		AfxMessageBox("请在在下表中选中领取的配方");
		return;
	}
	SingletonHelper::getInstance()->setFormulaID(ID);
	SingletonHelper::getInstance()->setPtrData((void*)this);
	CFetchAmountInputDialog fetchAmountInputDialog;
	fetchAmountInputDialog.DoModal();
}

void CFormulaDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}

BOOL CFormulaDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	int controlID= LOWORD(wParam);
	if (controlID == 1000)
	{	
		OnFormulaAdd();
	}
	if (controlID == 2000)
	{
		OnFormulaDel();
	}
	if (controlID == 3000)
	{
		OnFormulaFetch();
	}
	return CDialog::OnCommand(wParam, lParam);
}

HBRUSH CFormulaDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if   (pWnd == this)   
	{   
		return m_brBk;   
	}  
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

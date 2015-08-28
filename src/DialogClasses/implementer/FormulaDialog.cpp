// FormulaDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "FormulaDialog.h"
#include "FormulaAddDialog.h"
#include "MaterialCountInputDialog.h"
#include "FetchAmountInputDialog.h"
#include "HelperClass.h"
#include "DatabaseConnector.h"
#include "RecordSetPointer.h"
#include "uiFunctions.h"

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
}


void CFormulaDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_FORMULA_LISTCTRL, m_FormulaListCtrl);
}


BEGIN_MESSAGE_MAP(CFormulaDialog, CDialog)
	//{{AFX_MSG_MAP(CFormulaDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_FORMULA_ADD, OnFormulaAdd)
	ON_BN_CLICKED(IDC_FORMULA_DEL, OnFormulaDel)
	ON_BN_CLICKED(IDC_FORMULAFETCH_BUTTON, OnFormulaFetch)
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
	CMaterialCountInputDialog materialCountInputDialog;
	materialCountInputDialog.DoModal();
	return;
}

void CFormulaDialog::initList()
{

	CString sqlState = "SELECT * FROM FORMULAS";

	//init recordset pointer
	SQLExecutor::getInstanceRef().setSqlState(sqlState);

	//exec SQL state
	try
	{
		SQLExecutor::getInstanceRef().execSQL() ;
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	//get the result data set
	_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().getRecordPtr();

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

	m_FormulaAdd = new CButton;
	m_FormulaDel	= new CButton;
	m_FetchButton = new CButton;
	
    uiFunctions::setdlgsize(this);

	if (m_From == 1)
	{
		m_FormulaAdd->Create("增加配方", SW_HIDE, CRect(574 - 30, 650, 574 - 30 + 200, 650 + 60), this, 1000);
		m_FormulaAdd->ShowWindow(SW_SHOW);
		m_FormulaDel->Create("删除配方", SW_HIDE, CRect(322, 650, 322 + 200, 650 + 60), this, 2000);
		m_FormulaDel->ShowWindow(SW_SHOW);
		
	}

	if (m_From == 0)
	{
		m_FetchButton->Create("成品领取", SW_HIDE, CRect(574 - 30, 650, 574 - 30 + 200, 650 + 60), this, 3000);
		m_FetchButton->ShowWindow(SW_SHOW);
	}

	uiFunctions::setdlgsize(this, &m_ButtonOK);
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
	SQLExecutor::getInstanceRef().setSqlState(sqlState);

	//exec SQL state
	try
	{
		SQLExecutor::getInstanceRef().execSQL() ;
	}
	catch (_com_error& e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	//get the result data set
	_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().getRecordPtr();

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

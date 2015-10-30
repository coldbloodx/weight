// FormulaDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "FormulaDialog.h"
#include "FormulaAddDialog.h"
#include "MaterialCountInputDialog.h"
#include "FetchAmountInputDialog.h"
#include "HelperClass.h"
#include "DBConnector.h"
#include "DBptr.h"
#include "uiFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormulaDialog dialog


CFormulaDialog::CFormulaDialog(CWnd* pParent /*=NULL*/)
: CDialog(CFormulaDialog::IDD, pParent),btnAdd(NULL),btnDel(NULL), btnFetch(NULL), m_From(0)
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
	if (btnAdd)
	{
		delete btnAdd;
		btnAdd = NULL;
	}
	if (btnDel)
	{
		delete btnDel;
		btnDel = NULL;
	}
	if (btnFetch)
	{
		delete btnFetch;
		btnFetch = NULL;
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

	_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().execquery(sqlState);

	CString headerArray[4] = {"ID", "NAME", "MATERIAL", "TOTAL"};
	std::vector<CString> headerList(headerArray, headerArray + 4);

	uiutils::updatelist(m_pRecordset, m_FormulaListCtrl, headerList);
}


BOOL CFormulaDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	initListHeader();
	initList();

	btnAdd = new CButton;
	btnDel	= new CButton;
	btnFetch = new CButton;
	
    uiutils::setdlgsize(this);

	if (m_From == 1)
	{
		btnAdd->Create("增加配方", SW_HIDE, CRect(574 - 30, 650, 574 - 30 + 200, 650 + 60), this, 1000);
		btnAdd->SetFont(SingletonHelper::getInstance()->defaultFont, TRUE);
		btnAdd->ShowWindow(SW_SHOW);
		btnDel->Create("删除配方", SW_HIDE, CRect(322, 650, 322 + 200, 650 + 60), this, 2000);
		btnDel->SetFont(SingletonHelper::getInstance()->defaultFont, TRUE);
		btnDel->ShowWindow(SW_SHOW);
		
	}

	if (m_From == 0)
	{
		btnFetch->Create("成品领取", SW_HIDE, CRect(574 - 30, 650, 574 - 30 + 200, 650 + 60), this, 3000);
		btnFetch->SetFont(SingletonHelper::getInstance()->defaultFont, TRUE);
		btnFetch->ShowWindow(SW_SHOW);
	}

	uiutils::setdlgsize(this, &m_ButtonOK);
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

	CString sql;
	sql.Format("delete from formulas where id = %s", ID);
	SQLExecutor::getInstanceRef().execquery(sql);

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
    m_FormulaListCtrl.DeleteAllItems();
    initList();
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

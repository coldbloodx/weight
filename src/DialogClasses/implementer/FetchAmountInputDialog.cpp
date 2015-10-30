// FetchAmountInputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "FetchAmountInputDialog.h"
#include "HelperClass.h"
#include "FormulaDialog.h"
#include "DBConnector.h"
#include "DBptr.h"
#include "uiFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFetchAmountInputDialog dialog


CFetchAmountInputDialog::CFetchAmountInputDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFetchAmountInputDialog::IDD, pParent)
{
}

CFetchAmountInputDialog::~CFetchAmountInputDialog()
{
}


void CFetchAmountInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRINT_CHECK, m_PrintCheck);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_BUTTON9, m_Button9);
	DDX_Control(pDX, IDC_BUTTON8, m_Button8);
	DDX_Control(pDX, IDC_BUTTON7, m_Button7);
	DDX_Control(pDX, IDC_BUTTON6, m_Button6);
	DDX_Control(pDX, IDC_BUTTON5, m_Button5);
	DDX_Control(pDX, IDC_BUTTON4, m_Button4);
	DDX_Control(pDX, IDC_BUTTON3, m_Button3);
	DDX_Control(pDX, IDC_BUTTON2, m_Button2);
	DDX_Control(pDX, IDC_BUTTON1, m_Button1);
	DDX_Control(pDX, IDC_BUTTON0, m_Button0);
	DDX_Control(pDX, IDC_BUTTON_COMMA, m_ButtonComma);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_ButtonBack);
	DDX_Control(pDX, IDC_FETCHAMOUNT_EDIT, m_FetchAmount);
}


BEGIN_MESSAGE_MAP(CFetchAmountInputDialog, CDialog)
	//{{AFX_MSG_MAP(CFetchAmountInputDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON0, OnButton0)
	ON_BN_CLICKED(IDC_BUTTON_COMMA, OnButtonComma)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	ON_BN_CLICKED(IDOK, &CFetchAmountInputDialog::OnBnClickedOk)
END_MESSAGE_MAP()

void CFetchAmountInputDialog::OnOK() 
{
	if (!utils::isDouble(&m_FetchAmount))
	{
		AfxMessageBox("请确认输入！");
		return;
	}
	CString fetchAmount;
	m_FetchAmount.GetWindowText(fetchAmount);

	CString formulaName, formulaAmount;
	double dFormulaAmount, dFetchAmount;
	
	//查询formula表中成品量的多少
	CString sql;
	sql.Format("select name, total from formulas where id = %s ", SingletonHelper::getInstance()->getFormulaID());

	//get the result data set
	_RecordsetPtr& dbptr = SQLExecutor::getInstanceRef().execquery(sql);


	try
	{
		_variant_t vFormulaName;
		_variant_t vAmount;
		while(!dbptr->adoEOF)
		{
			vFormulaName = dbptr->GetCollect("NAME");
			vAmount = dbptr->GetCollect("TOTAL");
			
			
			if (vFormulaName.vt != VT_NULL)
			{
				formulaName = (LPCTSTR)(_bstr_t)vFormulaName;
			}

			if (vAmount.vt != VT_NULL)
			{
				formulaAmount = (LPCTSTR)(_bstr_t)vAmount;
			}
			
			dbptr->MoveNext();
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
	}
	
	dFormulaAmount = atof(formulaAmount.GetBuffer(0));
	dFetchAmount = atof(fetchAmount.GetBuffer(0));

	if (dFetchAmount > dFormulaAmount)
	{
		AfxMessageBox("成品量不足，请确认有足够的成品");
		return;
	}

	//更新formula表
	CString newAmount(utils::doubleToCString(dFormulaAmount - dFetchAmount));


	sql.Format("update formulas set total = %s  where id = %s", newAmount, SingletonHelper::getInstance()->getFormulaID());
	dbptr = SQLExecutor::getInstanceRef().execquery(sql);

	//首先取得系统时间
	CTime currentTime = CTime::GetCurrentTime();
	CString date = currentTime.Format("%Y-%m-%d");
	CString time = currentTime.Format("%X");
	
	
	CString fetchRectordID = utils::gettimestamp();

	
	sql.Format("insert into fetchrecords(formulaid, formulaname, operatorid, operatorname, amount, odate, otime) values('%s', '%s', '%s', '%s', %s, '%s', '%s') ", 
		SingletonHelper::getInstance()->getFormulaID(), formulaName, 
		SingletonHelper::getInstance()->getUserID(), SingletonHelper::getInstance()->getUsername(), 
		fetchAmount, date, time);

	SQLExecutor::getInstanceRef().execquery(sql);

	CFormulaDialog* pFD = (CFormulaDialog*)SingletonHelper::getInstance()->getPtrData();
	pFD->initList();

	if (m_PrintCheck.GetCheck())
	{
		//为打印做准备
		printVector.push_back(fetchRectordID);
		printVector.push_back(formulaName);
		printVector.push_back(fetchAmount + "Kg");
		printVector.push_back(SingletonHelper::getInstance()->getUsername());
		printVector.push_back(CString(""));
		printVector.push_back(CString(""));
		printVector.push_back(CString(""));
		printVector.push_back(CString(""));

		CString headerArray[8] = {"生产批号","配方名称","领取重量","混料人姓名","称重日期","称重时间","领取人姓名","领料日期"};;
		std::vector<CString> headerList(headerArray, headerArray + 8);
		utils::printVector(CString("成品领取记录"), headerList, printVector);
		printVector.clear();
	}

	CDialog::OnOK();
}

void CFetchAmountInputDialog::OnButton1() 
{
	// TODO: Add your control notification handler code here
	m_FetchAmount.SetFocus();
	keybd_event(VK_NUMPAD1, 0, 0, 0);
}

void CFetchAmountInputDialog::OnButton2() 
{
	// TODO: Add your control notification handler code here
	m_FetchAmount.SetFocus();
	keybd_event(VK_NUMPAD2, 0, 0, 0);
}

void CFetchAmountInputDialog::OnButton3() 
{
	// TODO: Add your control notification handler code here
	m_FetchAmount.SetFocus();
	keybd_event(VK_NUMPAD3, 0, 0, 0);
}

void CFetchAmountInputDialog::OnButton4() 
{
	// TODO: Add your control notification handler code here
	m_FetchAmount.SetFocus();
	keybd_event(VK_NUMPAD4, 0, 0, 0);
}

void CFetchAmountInputDialog::OnButton5() 
{
	// TODO: Add your control notification handler code here
	m_FetchAmount.SetFocus();
	keybd_event(VK_NUMPAD5, 0, 0, 0);
}

void CFetchAmountInputDialog::OnButton6() 
{
	// TODO: Add your control notification handler code here
	m_FetchAmount.SetFocus();
	keybd_event(VK_NUMPAD6, 0, 0, 0);
}

void CFetchAmountInputDialog::OnButton7() 
{
	// TODO: Add your control notification handler code here
	m_FetchAmount.SetFocus();
	keybd_event(VK_NUMPAD7, 0, 0, 0);
}

void CFetchAmountInputDialog::OnButton8() 
{
	// TODO: Add your control notification handler code here
	m_FetchAmount.SetFocus();
	keybd_event(VK_NUMPAD8, 0, 0, 0);
}

void CFetchAmountInputDialog::OnButton9() 
{
	// TODO: Add your control notification handler code here
	m_FetchAmount.SetFocus();
	keybd_event(VK_NUMPAD9, 0, 0, 0);
}

void CFetchAmountInputDialog::OnButton0() 
{
	m_FetchAmount.SetFocus();
	keybd_event(VK_NUMPAD0, 0, 0, 0);
}

void CFetchAmountInputDialog::OnButtonComma() 
{
	// TODO: Add your control notification handler code here
	m_FetchAmount.SetFocus();
	keybd_event(190, 0, 0, 0);
}

void CFetchAmountInputDialog::OnButtonBack() 
{
	// TODO: Add your control notification handler code here
	m_FetchAmount.SetFocus();
	keybd_event(VK_BACK, 0, 0, 0);
}

BOOL CFetchAmountInputDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    uiutils::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFetchAmountInputDialog::OnBnClickedOk()
{
	OnOK();
}

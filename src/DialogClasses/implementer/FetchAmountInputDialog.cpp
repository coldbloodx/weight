// FetchAmountInputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "FetchAmountInputDialog.h"
#include "HelperClass.h"
#include "FormulaDialog.h"
#include "DatabaseConnector.h"
#include "RecordSetPointer.h"
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
	//{{AFX_DATA_INIT(CFetchAmountInputDialog)
	//}}AFX_DATA_INIT
}

CFetchAmountInputDialog::~CFetchAmountInputDialog()
{

}


void CFetchAmountInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFetchAmountInputDialog)
	DDX_Control(pDX, IDC_PRINT_CHECK, m_PrintCheck);
	//DDX_Control(pDX, IDC_STATUS_STATIC2, m_StatusStatic);
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
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_GOBACK, m_GoBack);
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
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CFetchAmountInputDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_GOBACK, &CFetchAmountInputDialog::OnBnClickedGoback)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFetchAmountInputDialog message handlers

void CFetchAmountInputDialog::OnOK() 
{
	// TODO: Add extra validation here
	if (!HelperFunctions::isDouble(&m_FetchAmount))
	{
		AfxMessageBox("请确认输入！");
		return;
	}
	CString fetchAmount;
	m_FetchAmount.GetWindowText(fetchAmount);

	CString formulaName, formulaAmount;
	double dFormulaAmount, dFetchAmount;
	
	//查询formula表中成品量的多少
	CString sqlState("SELECT NAME, TOTAL FROM FORMULAS WHERE ID = ");
	sqlState += SingletonHelper::getInstance()->getFormulaID();

	//init recordset pointer
	SQLExecutor::getInstanceRef().setDatabaseConnection(DBConnector::getInstanceRef().getdbcon());
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
		_variant_t vFormulaName;
		_variant_t vAmount;
		while(!m_pRecordset->adoEOF)
		{
			vFormulaName = m_pRecordset->GetCollect("NAME");
			vAmount = m_pRecordset->GetCollect("TOTAL");
			
			
			if (vFormulaName.vt != VT_NULL)
			{
				formulaName = (LPCTSTR)(_bstr_t)vFormulaName;
			}

			if (vAmount.vt != VT_NULL)
			{
				formulaAmount = (LPCTSTR)(_bstr_t)vAmount;
			}
			
			m_pRecordset->MoveNext();
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
	CString newAmount(HelperFunctions::doubleToCString(dFormulaAmount - dFetchAmount));
	
	
	sqlState = "UPDATE FORMULAS SET TOTAL = " + newAmount + " WHERE ID = " + SingletonHelper::getInstance()->getFormulaID();
	

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
	m_pRecordset = SQLExecutor::getInstanceRef().getRecordPtr();

	//组成新纪录，并且将记录插入fetchrecord表
	sqlState = "SELECT * FROM FETCHRECORDS";
	
	//首先取得系统时间
	CTime currentTime = CTime::GetCurrentTime();
	CString date = currentTime.Format("%Y-%m-%d");
	CString time = currentTime.Format("%X");
	
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
	m_pRecordset = SQLExecutor::getInstanceRef().getRecordPtr();
	
	CString fetchRectordID;

	try
	{
		if (!m_pRecordset->adoEOF)
		{
			m_pRecordset->MoveLast();
		}
		
		m_pRecordset->AddNew();
		//取得流水号！
		_variant_t ID = m_pRecordset->GetCollect(_variant_t("ID"));
		if (ID.vt != VT_NULL)
		{
			fetchRectordID = (LPCTSTR)(_bstr_t)ID;
		}
		m_pRecordset->PutCollect("FORMULAID", _variant_t(SingletonHelper::getInstance()->getFormulaID()));
		m_pRecordset->PutCollect("FORMULANAME", _variant_t(formulaName));
		m_pRecordset->PutCollect("OPERATORID", _variant_t(SingletonHelper::getInstance()->getUserID()));
		m_pRecordset->PutCollect("OPERATORNAME", _variant_t(SingletonHelper::getInstance()->getUsername()));
		m_pRecordset->PutCollect("AMOUNT", _variant_t(fetchAmount));
		m_pRecordset->PutCollect("DATE", _variant_t(date));
		m_pRecordset->PutCollect("TIME", _variant_t(time));
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	try
	{
		m_pRecordset->Update();
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
		return;
	}
	m_pRecordset->Close();
	//m_pRecordset = NULL;

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
		HelperFunctions::printVector(CString("成品领取记录"), headerList, printVector);
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
	
    uiFunctions::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFetchAmountInputDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}


void CFetchAmountInputDialog::OnBnClickedOk()
{
	OnOK();
}

void CFetchAmountInputDialog::OnBnClickedGoback()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

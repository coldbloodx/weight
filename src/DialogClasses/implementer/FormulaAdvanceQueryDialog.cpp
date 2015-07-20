// FormulaAdvanceQueryDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\FormulaAdvanceQueryDialog.h"
#include "..\..\DialogClasses\header\StatisticDialog.h"
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
// CFormulaAdvanceQueryDialog dialog


CFormulaAdvanceQueryDialog::CFormulaAdvanceQueryDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFormulaAdvanceQueryDialog::IDD, pParent),needAnd(FALSE)
{
	//{{AFX_DATA_INIT(CFormulaAdvanceQueryDialog)
	//}}AFX_DATA_INIT
}


void CFormulaAdvanceQueryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormulaAdvanceQueryDialog)
	//DDX_Control(pDX, IDC_STATIC10, m_StatusStatic);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_FORMULA_EDIT, m_FormulaEdit);
	DDX_Control(pDX, IDC_USER_COMBO, m_UserCombo);
	DDX_Control(pDX, IDC_FORMULA_COMBO, m_FormulaCombo);
	DDX_Control(pDX, IDC_DATE_COMBO, m_DateCombo);
	DDX_Control(pDX, IDC_AMOUNT_COMBO, m_AmountCombo);
	DDX_Control(pDX, IDC_USER_EDIT, m_UserEdit);
	DDX_Control(pDX, IDC_SUM_CHECK, m_SumCheck);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SECOND, m_DateSecond);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FIRST, m_DateFirst);
	DDX_Control(pDX, IDC_AMOUNTSECOND_EDIT, m_AmountSecondEdit);
	DDX_Control(pDX, IDC_AMOUNTFIRST_EDIT, m_AmountFirstEdit);
	//}}AFX_DATA_MAP
}

CFormulaAdvanceQueryDialog::~CFormulaAdvanceQueryDialog()
{

}


BEGIN_MESSAGE_MAP(CFormulaAdvanceQueryDialog, CDialog)
	//{{AFX_MSG_MAP(CFormulaAdvanceQueryDialog)
	ON_CBN_SELCHANGE(IDC_USER_COMBO, OnSelchangeUserCombo)
	ON_CBN_SELCHANGE(IDC_FORMULA_COMBO, OnSelchangeFormulaCombo)
	ON_CBN_SELCHANGE(IDC_AMOUNT_COMBO, OnSelchangeAmountCombo)
	ON_CBN_SELCHANGE(IDC_DATE_COMBO, OnSelchangeDateCombo)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CFormulaAdvanceQueryDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormulaAdvanceQueryDialog message handlers

BOOL CFormulaAdvanceQueryDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//HelperFunctions::showStatus(m_StatusStatic);
	//SetTimer(1000,1000,NULL);
	
	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_STATISTICSADVANCEQUERY);//载入图片   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();   

	CRect wndRect((1024 - 960) / 2, (768 - 700) / 2, (1024 - 960) / 2 + 960,(768 - 700) / 2 + 710);
	this->MoveWindow(wndRect);

	CRect okRect(794, 636, 905, 675);
	m_ButtonOK.MoveWindow(okRect);

	

	//HelperFunctions::setButtonStyle(m_ButtonOK, RGB(55,71,158), SingletonHelper::getInstance()->simSong20);

	// TODO: Add extra initialization here
	m_UserCombo.SetCurSel(0);
	m_FormulaCombo.SetCurSel(0);
	m_AmountCombo.SetCurSel(0);
	m_DateCombo.SetCurSel(0);
	m_AmountSecondEdit.EnableWindow(FALSE);
	m_DateSecond.EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CFormulaAdvanceQueryDialog::OnSelchangeUserCombo() 
{
	// TODO: Add your control notification handler code here
	
}

void CFormulaAdvanceQueryDialog::OnSelchangeFormulaCombo() 
{
	// TODO: Add your control notification handler code here
	
}

void CFormulaAdvanceQueryDialog::OnSelchangeAmountCombo() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	CString comboText;
	m_AmountCombo.GetWindowText(comboText);
	if (comboText == "两端" || comboText == "介于")
	{
		m_AmountSecondEdit.EnableWindow(TRUE);
	}
	else
	{
		m_AmountSecondEdit.EnableWindow(FALSE);
	}
}

void CFormulaAdvanceQueryDialog::OnSelchangeDateCombo() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	CString comboText;
	m_DateCombo.GetWindowText(comboText);
	if (comboText == "两端" || comboText == "之间")
	{
		m_DateSecond.EnableWindow(TRUE);
	}
	else
	{
		m_DateSecond.EnableWindow(FALSE);
	}
}

void CFormulaAdvanceQueryDialog::OnOK() 
{
	// TODO: Add extra validation here
		//下面开始格式化sql语句
	CString userIndex, userKeyword, formulaIndex, fourmulaKeyword;
	CString amountIndex, amountKeywordFirst, amountKeywordSecond;
	CString dateIndex, dateKeywordFirst, dateKeywordSecond;
		
	CString sqlHeader = "SELECT * FROM WEIGHT WHERE ";
	CString sumHeader = "SELECT SUM(AMOUNT) AS TOTAL FROM WEIGHT WHERE ";

	m_UserCombo.GetWindowText(userIndex);
	m_UserEdit.GetWindowText(userKeyword);

	m_FormulaCombo.GetWindowText(formulaIndex);
	m_FormulaEdit.GetWindowText(fourmulaKeyword);

	m_AmountCombo.GetWindowText(amountIndex);
	m_AmountFirstEdit.GetWindowText(amountKeywordFirst);
	m_AmountSecondEdit.GetWindowText(amountKeywordSecond);

	m_DateCombo.GetWindowText(dateIndex);
	m_DateFirst.GetWindowText(dateKeywordFirst);
	m_DateSecond.GetWindowText(dateKeywordSecond);

	if (!fourmulaKeyword.IsEmpty())
	{
		needAnd = TRUE;
		if(formulaIndex == "配方编号")
		{
			sqlState += " FORMULAID = " + fourmulaKeyword;
		}
		else
		{
			sqlState += " FORMULANAME = '" + fourmulaKeyword + "'";
		}
	}
	

	if (!userKeyword.IsEmpty())
	{
		if (needAnd)
		{
			sqlState += " AND ";
		}
		else
		{
			needAnd = TRUE;
		}

		if (userIndex == "人员编号")
		{
			sqlState +=  "USERID = " + userKeyword;
		}
		else
		{
			sqlState += "USERNAME = '" + userKeyword + "'";
		}
	}

	if (!amountKeywordFirst.IsEmpty())
	{
		double firstAmount, secondAmount;
		if (HelperFunctions::isDouble(&m_AmountFirstEdit))
		{
			firstAmount = atof(amountKeywordFirst.GetBuffer(0));
		}
		else
		{
			AfxMessageBox("请确认称量数量输入！");
			return;
		}

		if (needAnd)
		{
			sqlState += " AND ";
		}
		else
		{
			needAnd = TRUE;
		}
		if (amountIndex == "大于")
		{
			sqlState += " AMOUNT > " + amountKeywordFirst;
		}
		if (amountIndex == "小于")
		{
			sqlState += " AMOUNT < " + amountKeywordFirst;
		}
		if (amountIndex == "介于")
		{
			if (!amountKeywordSecond.IsEmpty() && HelperFunctions::isDouble(&m_AmountSecondEdit))
			{
				secondAmount = atof(amountKeywordSecond.GetBuffer(0));
			}
			else
			{
				AfxMessageBox("请确认称量数量输入！");
				return;
			}
			
			if (firstAmount > secondAmount)
			{
				AfxMessageBox("请确认称量数量输入！");
				return;
			}

			sqlState += " AMOUNT >= " + amountKeywordFirst + " AND AMOUNT <=" + amountKeywordSecond;
		}
		if (amountIndex == "两端")
		{
			if (!amountKeywordSecond.IsEmpty() && HelperFunctions::isDouble(&m_AmountSecondEdit))
			{
				secondAmount = atof(amountKeywordSecond.GetBuffer(0));
			}
			else
			{
				AfxMessageBox("请确认称量数量输入！");
				return;
			}

			if (firstAmount > secondAmount)
			{
				AfxMessageBox("请确认称量数量输入！");
				return;
			}
			sqlState += " (AMOUNT <= " + amountKeywordFirst + " OR AMOUNT >=" + amountKeywordSecond + ") ";
		}
	}

	if (needAnd)
	{
		sqlState += " AND ";
	}
	else
	{
		needAnd = TRUE;
	}

	if (dateKeywordFirst == dateKeywordSecond)
	{	
		sqlState += " DATE <= \#" + dateKeywordFirst +"\#";
	}
	else
	{
		if (dateIndex == "之前")
		{
			sqlState += " DATE <= \#" + dateKeywordFirst +"\#";
		}
		if (dateIndex == "之后")
		{
			sqlState += " DATE >= \#" + dateKeywordFirst +"\#";
		}
		if (dateIndex == "之间")
		{
			if (dateKeywordFirst >= dateKeywordSecond)
			{
				AfxMessageBox("请检查日期输入的合法性！");
				return;
			}
			sqlState += " DATE > \#" + dateKeywordFirst +"\#" + " AND DATE < \#" + dateKeywordSecond + "\#";
		}
		if (dateIndex == "两端")
		{
			if (dateKeywordFirst >= dateKeywordSecond)
			{
				AfxMessageBox("请检查日期输入的合法性！");
				return;
			}
			sqlState += " (DATE < \#" + dateKeywordFirst + "\#" + " OR DATE >  \#" + dateKeywordSecond + "\#)";
		}
	}
	TRACE("sqlState: %s%s", sqlHeader.GetBuffer(0),sqlState.GetBuffer(0));

	//格式化sql语句完毕

	CStatisticDialog* statisticDialog = (CStatisticDialog*)SingletonHelper::getInstance()->getPtrData();
	statisticDialog->m_StatisticList.DeleteAllItems();

	//init recordset pointer
	RecordSetPointer::getInstanceRef().setSqlState(sqlHeader + sqlState);
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

	CString headerArray[9] = {"ID", "FORMULAID", "FORMULANAME", "USERID", "USERNAME", "AMOUNT","DATE", "TIME","COMMENT" };
	std::vector<CString> headerList(headerArray, headerArray + 9);

	uiFunctions::updateList(m_pRecordset, statisticDialog->m_StatisticList, headerList);

	CString total;
	if (m_SumCheck.GetCheck())
	{
		RecordSetPointer::getInstanceRef().setSqlState(sumHeader + sqlState);
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
			
			_variant_t vTotal;
			
			vTotal = m_pRecordset->GetCollect("TOTAL");
			
			if(vTotal.vt != VT_NULL)
			{
				total = (LPCTSTR)(_bstr_t)vTotal;
			}
			
		}
		catch(_com_error &e)
		{
			AfxMessageBox(e.Description());
			return;
		}
		AfxMessageBox("称量总量为：" + total);
	}

	CDialog::OnOK();
}

void CFormulaAdvanceQueryDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}

void CFormulaAdvanceQueryDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

HBRUSH CFormulaAdvanceQueryDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if   (pWnd == this)   
	{   
		return m_brBk;   
	}   
	if   (nCtlColor   ==   CTLCOLOR_STATIC)   
	{     
		pDC->SetBkMode(TRANSPARENT);	//透明   
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	}   

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

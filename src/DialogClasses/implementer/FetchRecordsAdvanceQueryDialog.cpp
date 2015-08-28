// FetchRecordsAdvanceQueryDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "FetchRecordsAdvanceQueryDialog.h"
#include "FetchRecordDialog.h"
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
// CFetchRecordsAdvanceQueryDialog dialog


CFetchRecordsAdvanceQueryDialog::CFetchRecordsAdvanceQueryDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFetchRecordsAdvanceQueryDialog::IDD, pParent),needAnd(FALSE)
{
	//{{AFX_DATA_INIT(CFetchRecordsAdvanceQueryDialog)
	//}}AFX_DATA_INIT

}


void CFetchRecordsAdvanceQueryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFetchRecordsAdvanceQueryDialog)
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
	DDX_Control(pDX, IDC_BUTTON_COMMA, m_CommaButton);
	DDX_Control(pDX, IDC_BUTTON_BACK, m_BackButton);
//	DDX_Control(pDX, IDC_STATUS_STATIC2, m_StatusStatic);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_USER_EDIT, m_UserEdit);
	DDX_Control(pDX, IDC_FORMULA_EDIT, m_FormulaEdit);
	DDX_Control(pDX, IDC_AMOUNTFIRST_EDIT, m_AmountFirstEdit);
	DDX_Control(pDX, IDC_AMOUNTSECOND_EDIT, m_AmountSecondEdit);
	DDX_Control(pDX, IDC_USER_COMBO, m_UserCombo);
	DDX_Control(pDX, IDC_FORMULA_COMBO, m_FormulaCombo);
	DDX_Control(pDX, IDC_AMOUNT_COMBO, m_AmountCombo);
	DDX_Control(pDX, IDC_DATE_COMBO, m_DateCombo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FIRST, m_DateFirst);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SECOND, m_DateSecond);
	DDX_Control(pDX, IDC_SUM_CHECK, m_SumCheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFetchRecordsAdvanceQueryDialog, CDialog)
	//{{AFX_MSG_MAP(CFetchRecordsAdvanceQueryDialog)
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
	ON_CBN_SELCHANGE(IDC_DATE_COMBO, OnSelchangeDateCombo)
	ON_CBN_SELCHANGE(IDC_AMOUNT_COMBO, OnSelchangeAmountCombo)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CFetchRecordsAdvanceQueryDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFetchRecordsAdvanceQueryDialog message handlers

CFetchRecordsAdvanceQueryDialog::~CFetchRecordsAdvanceQueryDialog()
{

}

BOOL CFetchRecordsAdvanceQueryDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CButton* buttonArray[13] = {&m_Button1,&m_Button2,&m_Button3,&m_Button4,&m_Button5,&m_Button6,
		&m_Button7,&m_Button8,&m_Button9,&m_Button0,&m_CommaButton,&m_BackButton};

	CRect wndRect((1024 - 960) / 2, (768 - 644) / 2, (1024 - 960) / 2 + 960, (768 - 644) / 2 + 660);
	this->MoveWindow(wndRect);

	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_FETCHADVANCEQUERY);//载入图片   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();   

	int left = 43;
	int top = 534;
	int right = 83;
	int buttom = 575;
	int horiSpacer = 91 - 83;
	int width = right - left;

	std::vector<CButton*> numpadButtonVector(buttonArray, buttonArray + 12);
	for (size_t i = 0; i < numpadButtonVector.size(); ++i)
	{
		CRect numpadButtonRect(left, top, right, buttom);
		numpadButtonVector[i]->MoveWindow(numpadButtonRect);

		left += width +horiSpacer;
		right += width + horiSpacer;
	}


	CRect okRect(810, 580, 923, 620);
	m_ButtonOK.MoveWindow(okRect);


	// TODO: Add extra initialization here
	m_UserCombo.SetCurSel(0);
	m_FormulaCombo.SetCurSel(0);
	m_AmountCombo.SetCurSel(0);
	m_DateCombo.SetCurSel(0);
	m_AmountSecondEdit.EnableWindow(FALSE);
	m_DateSecond.EnableWindow(FALSE);

	//HelperFunctions::showStatus(m_StatusStatic);
	//SetTimer(1000,1000,NULL);
    uiFunctions::setdlgsize(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CFetchRecordsAdvanceQueryDialog::OnSelchangeDateCombo() 
{
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

void CFetchRecordsAdvanceQueryDialog::OnSelchangeAmountCombo() 
{
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

void CFetchRecordsAdvanceQueryDialog::OnOK() 
{
	// TODO: Add extra validation here

	//下面开始格式化sql语句
	CString userIndex, userKeyword, formulaIndex, fourmulaKeyword;
	CString amountIndex, amountKeywordFirst, amountKeywordSecond;
	CString dateIndex, dateKeywordFirst, dateKeywordSecond;
		
	CString sqlHeader = "SELECT * FROM FETCHRECORDS WHERE ";
	CString sumHeader = "SELECT SUM(AMOUNT) AS TOTAL FROM FETCHRECORDS WHERE ";

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
			sqlState +=  "OPERATORID = " + userKeyword;
		}
		else
		{
			sqlState += "OPERATORNAME = '" + userKeyword + "'";
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
			sqlState = "";
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
				sqlState = "";
				return;
			}
			
			if (firstAmount > secondAmount)
			{
				AfxMessageBox("请确认称量数量输入！");
				sqlState = "";
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
				sqlState = "";
				return;
			}

			if (firstAmount > secondAmount)
			{
				AfxMessageBox("请确认称量数量输入！");
				sqlState = "";
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
				sqlState = "";
				return;
			}
			sqlState += " DATE > \#" + dateKeywordFirst +"\#" + " AND DATE < \#" + dateKeywordSecond + "\#";
		}
		if (dateIndex == "两端")
		{
			if (dateKeywordFirst >= dateKeywordSecond)
			{
				AfxMessageBox("请检查日期输入的合法性！");
						sqlState = "";
				return;
			}
			sqlState += " (DATE < \#" + dateKeywordFirst + "\#" + " OR DATE >  \#" + dateKeywordSecond + "\#)";
		}
	}
	TRACE("sqlState: %s%s", sqlHeader.GetBuffer(0),sqlState.GetBuffer(0));

	//格式化sql语句完毕

	CFetchRecordDialog* fetchRecordDialog = (CFetchRecordDialog*)SingletonHelper::getInstance()->getPtrData();
	fetchRecordDialog->m_FetchRecordList.DeleteAllItems();

	//init recordset pointer
	SQLExecutor::getInstanceRef().setDatabaseConnection(DBConnector::getInstanceRef().getdbcon());
	SQLExecutor::getInstanceRef().setSqlState(sqlHeader + sqlState);

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

	CString headerArray[9] = {"ID", "FORMULAID", "FORMULANAME", "FORMULANAME", "OPERATORID", "OPERATORNAME","AMOUNT", "DATE", "TIME" };
	std::vector<CString> headerList(headerArray, headerArray + 9);

	uiFunctions::updateList(m_pRecordset, fetchRecordDialog->m_FetchRecordList, headerList);
	
	CString total;
	if (m_SumCheck.GetCheck())
	{
		SQLExecutor::getInstanceRef().setSqlState(sumHeader + sqlState);

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
			_variant_t vTotal;
			
			vTotal = m_pRecordset->GetCollect("TOTAL");
			
			if(vTotal.vt != VT_NULL)
			{
				total = (LPCTSTR)(_bstr_t)vTotal;
			}
		}
		catch(_com_error &e)
		{
			AfxMessageBox("查询出现错误，请检查输入！");
			sqlState = "";
			e;
			return;
		}
		AfxMessageBox("领取成品总量为：" + total);
		sqlState = "";
	}
	CDialog::OnOK();
}

void CFetchRecordsAdvanceQueryDialog::OnTimer(UINT nIDEvent)
{
	//HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}

void CFetchRecordsAdvanceQueryDialog::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD1, 0, 0, 0);
}

void CFetchRecordsAdvanceQueryDialog::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD2, 0, 0, 0);
}

void CFetchRecordsAdvanceQueryDialog::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD3, 0, 0, 0);
}

void CFetchRecordsAdvanceQueryDialog::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD4, 0, 0, 0);
}

void CFetchRecordsAdvanceQueryDialog::OnButton5() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD5, 0, 0, 0);
}

void CFetchRecordsAdvanceQueryDialog::OnButton6() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD6, 0, 0, 0);
}

void CFetchRecordsAdvanceQueryDialog::OnButton7() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD7, 0, 0, 0);
}

void CFetchRecordsAdvanceQueryDialog::OnButton8() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD8, 0, 0, 0);
}

void CFetchRecordsAdvanceQueryDialog::OnButton9() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD9, 0, 0, 0);
}

void CFetchRecordsAdvanceQueryDialog::OnButton0() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD0, 0, 0, 0);
}

void CFetchRecordsAdvanceQueryDialog::OnButtonComma() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(190, 0, 0, 0);
}

void CFetchRecordsAdvanceQueryDialog::OnButtonBack() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_BACK, 0, 0, 0);
}

BOOL CFetchRecordsAdvanceQueryDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	int controlID = LOWORD(wParam);
	if (controlID == IDC_FORMULA_EDIT)
	{
		m_FocusedID = controlID;
	}
	if (controlID == IDC_USER_EDIT)
	{
		m_FocusedID = controlID;
	}
	if (controlID == IDC_AMOUNTFIRST_EDIT)
	{
		m_FocusedID = controlID;
	}
	if (controlID == IDC_AMOUNTSECOND_EDIT)
	{
		m_FocusedID = controlID;
	}
	return CDialog::OnCommand(wParam, lParam);
}

void CFetchRecordsAdvanceQueryDialog::OnBnClickedOk()
{
	OnOK();
	// TODO: Add your control notification handler code here
}

HBRUSH CFetchRecordsAdvanceQueryDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if   (pWnd == this)   
	{   
		return m_brBk;   
	}   
	if   (nCtlColor   ==   CTLCOLOR_STATIC)   
	{     
		pDC->SetBkMode(TRANSPARENT);	//透明   
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	}   
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

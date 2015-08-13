// FormulaSelectDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\FormulaSelectDialog.h"
#include "..\..\OtherClasses\HelperClass.h"
#include "..\..\DialogClasses\header\FormulaWeighDialog.h"
#include "..\..\OtherClasses\DatabaseConnector.h"
#include "..\..\OtherClasses\RecordSetPointer.h"
#include "..\..\OtherClasses\uifunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormulaSelectDialog dialog


CFormulaSelectDialog::CFormulaSelectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFormulaSelectDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFormulaSelectDialog)
	//}}AFX_DATA_INIT
}

CFormulaSelectDialog::~CFormulaSelectDialog()
{

}


void CFormulaSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormulaSelectDialog)
	DDX_Control(pDX, IDC_WEIGH_EDIT, m_Weigh);
	DDX_Control(pDX, IDC_FORMULAID_COMBO, m_FormulaIDCombo);
	DDX_Control(pDX, IDC_FORMULASELECT_COMBO, m_FormulaSelect);
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
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_GOBACK, m_GoBack);
}


BEGIN_MESSAGE_MAP(CFormulaSelectDialog, CDialog)
	//{{AFX_MSG_MAP(CFormulaSelectDialog)
	ON_CBN_SELCHANGE(IDC_FORMULASELECT_COMBO, OnSelchangeFormulaselectCombo)
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
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CFormulaSelectDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_GOBACK, &CFormulaSelectDialog::OnBnClickedGoback)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormulaSelectDialog message handlers

void CFormulaSelectDialog::OnOK() 
{
	// TODO: Add extra validation here
	//查询出配方的ID和所需要的各种材料的用量
	
	CString weight,ID,formulaName,material;
	m_FormulaSelect.GetWindowText(formulaName);
	m_FormulaIDCombo.GetWindowText(ID);
	m_Weigh.GetWindowText(weight);

	//CBitmap   bmp;   
	//bmp.LoadBitmap(IDB_FORMULAINPUT);//载入图片   
	//m_brBk.CreatePatternBrush(&bmp); 
	//bmp.DeleteObject();   


	if (ID.IsEmpty() || formulaName.IsEmpty())
	{
		AfxMessageBox("请确认配方名称和编号！");
		return;
	}

	if (weight.IsEmpty())
	{
		AfxMessageBox("重量输入错误，请重新输入！");
		return;
	}

	if (! HelperFunctions::isDouble(&m_Weigh))
	{
		AfxMessageBox("重量输入错误，请重新输入！");
		return;
	}

	CString sqlState("SELECT MATERIAL FROM FORMULAS WHERE ID = ");
	sqlState += ID ;

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
		_variant_t vMaterial;
		_variant_t vID;
		while(!m_pRecordset->adoEOF)
		{
			vMaterial = m_pRecordset->GetCollect("MATERIAL");
			
		
			if (vMaterial.vt != VT_NULL)
			{
				material =(LPCTSTR)(_bstr_t)vMaterial;
			}
			
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
	}
	//先查出配方的ID，和成分，计算所需用量

	SingletonHelper::getInstance()->setFormulaID(ID);
	SingletonHelper::getInstance()->setMaterials(material);
	SingletonHelper::getInstance()->setFormulaName(formulaName);
	SingletonHelper::getInstance()->setFormulaWeigh(weight);

	CFormulaWeighDialog formulaWeighDialog;
	this->ShowWindow(0);
	formulaWeighDialog.DoModal();
	CDialog::OnOK();
}

BOOL CFormulaSelectDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CButton* buttonArray[14] = {&m_Button1,&m_Button2,&m_Button3,&m_Button4,&m_Button5,&m_Button6,&m_Button7,
		&m_Button8,&m_Button9,&m_Button0,&m_ButtonComma,&m_ButtonBack,&m_ButtonOK,&m_ButtonCancel};


	CString sqlState = "SELECT NAME FROM FORMULAS";
	
	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_FORMULAINPUT);//载入图片   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject(); 

	CRect wndRect((1024 -960) / 2, (768 - 607) / 2, (1024 -960) / 2 + 960, (768 - 607) / 2 + 620);
	this->MoveWindow(wndRect);

	CRect okRect(505, 55, 622, 93);
	m_ButtonOK.MoveWindow(okRect);

	CRect cancelRect(652, 55, 767, 93);
	m_ButtonCancel.MoveWindow(cancelRect);

	CRect goBackRect(171, 464, 261, 487);
	m_GoBack.MoveWindow(goBackRect);


	int left = 650;
	int top = 170;
	int width = 705 - 650;
	int height = 225 - 170;
	int horiSpacer = 716 - 705;
	int vertSpacer = 236 - 224;


	std::vector<CButton*> numpadButtonVector(buttonArray, buttonArray + 12);
	for (size_t i = 0; i < numpadButtonVector.size(); ++i)
	{
		CRect startRect(left, top, left + width, top + height);
		numpadButtonVector[i]->MoveWindow(startRect, TRUE);

		if (((i + 1) % 3) == 0)
		{
			left = 650;
			top = startRect.bottom + vertSpacer;
		}
		else
		{
			left = startRect.right + horiSpacer;
		}
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
		return TRUE;
	}

	//get the result data set
	_RecordsetPtr& m_pRecordset = RecordSetPointer::getInstanceRef().getRecordPtr();
	
	try
	{
		_variant_t vName;
		_variant_t vID;
		while(!m_pRecordset->adoEOF)
		{
			vName = m_pRecordset->GetCollect("NAME");

			CString name;
			if (vName.vt != VT_NULL)
			{
				name =(LPCTSTR)(_bstr_t)vName;
			}
			m_FormulaSelect.AddString(name);

			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
	}


	std::vector<CButton*> buttonVector(buttonArray, buttonArray+14);
	
	uiFunctions::setdlgsize(this);

	
	/////////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFormulaSelectDialog::OnSelchangeFormulaselectCombo() 
{
	// TODO: Add your control notification handler code here
	CString formulaName;
	m_FormulaSelect.GetWindowText(formulaName);
	CString sqlState("SELECT ID FROM FORMULAS WHERE NAME = '");
	sqlState += formulaName + "'";
	CString ID;
	SingletonHelper::getInstance()->setFormulaName(formulaName);

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
		_variant_t vID;
		while(!m_pRecordset->adoEOF)
		{
			vID = m_pRecordset->GetCollect("ID");
			
			if (vID.vt != VT_NULL)
			{
				ID =(LPCTSTR)(_bstr_t)vID;
			}
			m_FormulaIDCombo.AddString(ID);

			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
	}
	m_FormulaIDCombo.SetCurSel(0);
}

void CFormulaSelectDialog::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD1, 0, 0, 0);
}

void CFormulaSelectDialog::OnButton2() 
{
	// TODO: Add your control notification handler code here
	if (m_FocusedID != IDC_WEIGH_EDIT)
	{
		return;
	}
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD2, 0, 0, 0);
}

void CFormulaSelectDialog::OnButton3() 
{
	// TODO: Add your control notification handler code here
	if (m_FocusedID != IDC_WEIGH_EDIT)
	{
		return;
	}
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD3, 0, 0, 0);
}

void CFormulaSelectDialog::OnButton4() 
{
	// TODO: Add your control notification handler code here
	if (m_FocusedID != IDC_WEIGH_EDIT)
	{
		return;
	}
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD4, 0, 0, 0);
}

void CFormulaSelectDialog::OnButton5() 
{
	// TODO: Add your control notification handler code here
	if (m_FocusedID != IDC_WEIGH_EDIT)
	{
		return;
	}
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD5, 0, 0, 0);
}

void CFormulaSelectDialog::OnButton6() 
{
	// TODO: Add your control notification handler code here
	if (m_FocusedID != IDC_WEIGH_EDIT)
	{
		return;
	}
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD6, 0, 0, 0);
}

void CFormulaSelectDialog::OnButton7() 
{
	// TODO: Add your control notification handler code here
	if (m_FocusedID != IDC_WEIGH_EDIT)
	{
		return;
	}
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD7, 0, 0, 0);
}

void CFormulaSelectDialog::OnButton8() 
{
	// TODO: Add your control notification handler code here
	if (m_FocusedID != IDC_WEIGH_EDIT)
	{
		return;
	}
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD8, 0, 0, 0);
}

void CFormulaSelectDialog::OnButton9() 
{
	// TODO: Add your control notification handler code here
	if (m_FocusedID != IDC_WEIGH_EDIT)
	{
		return;
	}
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD9, 0, 0, 0);
}

void CFormulaSelectDialog::OnButton0() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD0, 0, 0, 0);
}

void CFormulaSelectDialog::OnButtonComma() 
{
	// TODO: Add your control notification handler code here
	if (m_FocusedID != IDC_WEIGH_EDIT)
	{
		return;
	}
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(190, 0, 0, 0);
}

void CFormulaSelectDialog::OnButtonBack() 
{
	// TODO: Add your control notification handler code here
	if (m_FocusedID != IDC_WEIGH_EDIT)
	{
		return;
	}
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_BACK, 0, 0, 0);
}

BOOL CFormulaSelectDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	int controlID = LOWORD(wParam);
	if (controlID == IDC_WEIGH_EDIT)
	{
		m_FocusedID = controlID;
	}
	return CDialog::OnCommand(wParam, lParam);
}

void CFormulaSelectDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

HBRUSH CFormulaSelectDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if   (pWnd == this)   
	{   
		return m_brBk;   
	}   
	return hbr;
}

void CFormulaSelectDialog::OnBnClickedGoback()
{
	CDialog::OnCancel();
	// TODO: Add your control notification handler code here
}

// FormulaSelectDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "FormulaSelectDialog.h"
#include "HelperClass.h"
#include "FormulaWeighDialog.h"
#include "DBConnector.h"
#include "DBptr.h"
#include "uifunctions.h"

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

}

CFormulaSelectDialog::~CFormulaSelectDialog()
{

}


void CFormulaSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FORMULASELECT_COMBO, m_FormulaSelect);
	DDX_Control(pDX, IDC_WEIGH_EDIT, m_Weigh);
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
}


BEGIN_MESSAGE_MAP(CFormulaSelectDialog, CDialog)
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
	ON_BN_CLICKED(IDOK, &CFormulaSelectDialog::OnBnClickedOk)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormulaSelectDialog message handlers

void CFormulaSelectDialog::OnOK() 
{
	//查询出配方所需要的各种材料的用量
	
	CString weight,formulaName,material, formulaId;
	m_FormulaSelect.GetWindowText(formulaName);
	m_Weigh.GetWindowText(weight);


	if (formulaName.IsEmpty() )
	{
		AfxMessageBox("请确认配方名称！");
		return;
	}

	if (weight.IsEmpty())
	{
		AfxMessageBox("重量输入错误，请重新输入！");
		return;
	}

	if (! utils::isdouble(&m_Weigh))
	{
		AfxMessageBox("重量输入错误，请重新输入！");
		return;
	}

	CString sql;
	sql.Format("select material, id from formulas where name = '%s'", formulaName);

	_RecordsetPtr& m_pRecordset = SQLExecutor::getInstanceRef().execquery(sql);
	
	try
	{
		_variant_t vMaterial;
		_variant_t vID;
		while(!m_pRecordset->adoEOF)
		{
			vMaterial = m_pRecordset->GetCollect("material");
			
		
			if (vMaterial.vt != VT_NULL)
			{
				material =(LPCTSTR)(_bstr_t)vMaterial;
			}
			
			vID = m_pRecordset->GetCollect("id");
			if (vID.vt != VT_NULL)
			{
				formulaId = (LPCTSTR)(_bstr_t)vID;
			}
	
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
	}

	//先查出配方的ID，和成分，计算所需用量
	SingletonHelper::getInstance()->setFormulaID(formulaId);
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

	CString sql("select name from formulas");
	m_FormulaSelect.SetFont(SingletonHelper::getInstance()->simHei30);
	
	//get the result data set
	_RecordsetPtr& dbptr = SQLExecutor::getInstanceRef().execquery(sql);
	
	try
	{
		_variant_t vName;
		_variant_t vID;
		while(!dbptr->adoEOF)
		{
			vName = dbptr->GetCollect("name");

			CString name;
			if (vName.vt != VT_NULL)
			{
				name =(LPCTSTR)(_bstr_t)vName;
			}
			m_FormulaSelect.AddString(name);

			dbptr->MoveNext();
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
	}
	
	uiutils::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);

	return TRUE;  
}


void CFormulaSelectDialog::OnButtonBack() 
{
	if (m_FocusedID != IDC_WEIGH_EDIT)
	{
		return;
	}
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_BACK, 0, 0, 0);
}



void CFormulaSelectDialog::OnButton1() 
{
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD1, 0, 0, 0);
}

void CFormulaSelectDialog::OnButton2() 
{
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
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD0, 0, 0, 0);
}

void CFormulaSelectDialog::OnButtonComma() 
{
	if (m_FocusedID != IDC_WEIGH_EDIT)
	{
		return;
	}
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(190, 0, 0, 0);
}


BOOL CFormulaSelectDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	int controlID = LOWORD(wParam);
	if (controlID == IDC_WEIGH_EDIT)
	{
		m_FocusedID = controlID;
	}
	return CDialog::OnCommand(wParam, lParam);
}

void CFormulaSelectDialog::OnBnClickedOk()
{
	OnOK();
}


void CFormulaSelectDialog::OnBnClickedGoback()
{
	CDialog::OnCancel();
}

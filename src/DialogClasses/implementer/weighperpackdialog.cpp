// WeighPerPackDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "WeighPerPackDialog.h"
#include "HelperClass.h"
#include "uifunctions.h"
#include "FormulaSepWeighDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWeighPerPackDialog dialog


CWeighPerPackDialog::CWeighPerPackDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWeighPerPackDialog::IDD, pParent)
{
}

CWeighPerPackDialog::~CWeighPerPackDialog()
{

}

void CWeighPerPackDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWeighPerPackDialog)
	//DDX_Control(pDX, IDC_WEIGHPERPACK_STATIC, m_StatusStatic);
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
	DDX_Control(pDX, IDC_WEIGHPERPACK_EDIT, m_WeighPerPack);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_GROSSWEIGHT, m_GrossWeight);
}


BEGIN_MESSAGE_MAP(CWeighPerPackDialog, CDialog)
	//{{AFX_MSG_MAP(CWeighPerPackDialog)
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
	ON_BN_CLICKED(IDOK, &CWeighPerPackDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWeighPerPackDialog message handlers

void CWeighPerPackDialog::OnOK() 
{
	// TODO: Add extra validation here
	CString weighPerPackCString, grossWeight;
	m_GrossWeight.GetWindowText(grossWeight);	
	//处理皮重相关问题
	if (grossWeight.IsEmpty())
	{
		AfxMessageBox("请输入皮重！");
		return;
	}
	if (!utils::isDouble(&m_GrossWeight))
	{
		AfxMessageBox("皮重输入有误，请重新输入！");
		return;
	}

	CFormulaSepWeighDialog* formulaSepWeighDialog = (CFormulaSepWeighDialog*)(SingletonHelper::getInstance()->getSepWieghWindowPtr());
	
	//处理皮重显示
	formulaSepWeighDialog->m_PackWeight.SetWindowText(grossWeight + "Kg");
	formulaSepWeighDialog->dPackWeight = atof(grossWeight.GetBuffer(0));

	//处理分包相关问题
	m_WeighPerPack.GetWindowText(weighPerPackCString);
	if (!utils::isDouble(&m_WeighPerPack))
	{
		AfxMessageBox("包重输入错误，请重新输入");
		return;
	}

	double gross = atof(grossWeight.GetBuffer(0));
	double materialWeigh = formulaSepWeighDialog->dMaterialWeight;
	if (weighPerPackCString.IsEmpty())
	{
		formulaSepWeighDialog->bIsMultiPackFlag = FALSE;
		formulaSepWeighDialog->m_IsMultiPackNeeded.SetWindowText("否");
		formulaSepWeighDialog->m_WeighNeeded.SetWindowText(utils::doubleToCString(
			materialWeigh + atof(grossWeight.GetBuffer(0))));
		formulaSepWeighDialog->dWeightNeeded = materialWeigh /*+ atof(grossWeight.GetBuffer(0))*/;
		formulaSepWeighDialog->updateMultiTimes();
	}
	else
	{

		if (atof(weighPerPackCString.GetBuffer(0)) <=  atof(grossWeight.GetBuffer(0)))
		{
			AfxMessageBox("您的输入有误，请重新输入！");
			return;
		}
		//获得包重
		double weighPerPack = atof(weighPerPackCString.GetBuffer(0)) - gross ;
		formulaSepWeighDialog->dNetWeight = weighPerPack;
		formulaSepWeighDialog->dPackWeight = gross;

		int packCount =static_cast<int>(materialWeigh / weighPerPack);
		formulaSepWeighDialog->m_IsMultiPackNeeded.SetWindowText("是");
		formulaSepWeighDialog->bIsMultiPackFlag = TRUE;
		double packs = materialWeigh / weighPerPack;
		double rest = packs - (double)packCount;
		double neededWeigh = rest * weighPerPack;
		formulaSepWeighDialog->m_WeightPerPack.SetWindowText(weighPerPackCString+"Kg");
		//更新包数
		formulaSepWeighDialog->m_PackNeeded.SetWindowText(utils::intToCString(packCount) +"包");
		formulaSepWeighDialog->iTotalPacks = packCount;

		//更新已经称量过的重量
		formulaSepWeighDialog->m_AlreadyWeighed.SetWindowText(utils::doubleToCString(packCount * weighPerPack));
		formulaSepWeighDialog->dAlreadyWeighed = packCount * weighPerPack;
		formulaSepWeighDialog->dWeightNeeded = formulaSepWeighDialog->dWeightNeeded - packCount * weighPerPack;
		

		//跟新
		formulaSepWeighDialog->m_WeighNeeded.SetWindowText(utils::doubleToCString(neededWeigh  + gross)+"Kg");
		formulaSepWeighDialog->m_RestNeeded.SetWindowText(utils::doubleToCString(neededWeigh) + "Kg");
		formulaSepWeighDialog->dRestWeight = neededWeigh;

	}
	CDialog::OnOK();
}

void CWeighPerPackDialog::OnButton1() 
{
	// TODO: Add your control notification handler code here
		CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD1, 0, 0, 0);
}

void CWeighPerPackDialog::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD2, 0, 0, 0);
}

void CWeighPerPackDialog::OnButton3() 
{
	// TODO: Add your control notification handler code here
		CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD3, 0, 0, 0);
}

void CWeighPerPackDialog::OnButton4() 
{
	// TODO: Add your control notification handler code here
		CWnd * pWnd = GetDlgItem(m_FocusedID);
::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD4, 0, 0, 0);
}

void CWeighPerPackDialog::OnButton5() 
{
	// TODO: Add your control notification handler code here
		CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD5, 0, 0, 0);
}

void CWeighPerPackDialog::OnButton6() 
{
	// TODO: Add your control notification handler code here
		CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD6, 0, 0, 0);
}

void CWeighPerPackDialog::OnButton7() 
{
	// TODO: Add your control notification handler code here
		CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD7, 0, 0, 0);
}

void CWeighPerPackDialog::OnButton8() 
{
	// TODO: Add your control notification handler code here
		CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD8, 0, 0, 0);
}

void CWeighPerPackDialog::OnButton9() 
{
	// TODO: Add your control notification handler code here
		CWnd * pWnd = GetDlgItem(m_FocusedID);
::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD9, 0, 0, 0);
}

void CWeighPerPackDialog::OnButton0() 
{
		CWnd * pWnd = GetDlgItem(m_FocusedID);
::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_NUMPAD0, 0, 0, 0);
}

void CWeighPerPackDialog::OnButtonComma() 
{
	// TODO: Add your control notification handler code here
		CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(190, 0, 0, 0);
}

void CWeighPerPackDialog::OnButtonBack() 
{
	// TODO: Add your control notification handler code here
		CWnd * pWnd = GetDlgItem(m_FocusedID);
	::SetFocus(pWnd->GetSafeHwnd());
	keybd_event(VK_BACK, 0, 0, 0);
}

BOOL CWeighPerPackDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    uiutils::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);
	m_GrossWeight.SetWindowText("1");
	/////////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWeighPerPackDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}


void CWeighPerPackDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

HBRUSH CWeighPerPackDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if   (pWnd   ==   this)   
	{   
		return   m_brBk;   
	}   
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


BOOL CWeighPerPackDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	int constrolID =LOWORD(wParam);

	if (constrolID == IDC_WEIGHPERPACK_EDIT)
	{
		m_FocusedID = IDC_WEIGHPERPACK_EDIT;
	}
	if (constrolID == IDC_GROSSWEIGHT)
	{
		m_FocusedID = IDC_GROSSWEIGHT;
	}
	return CDialog::OnCommand(wParam, lParam);
}

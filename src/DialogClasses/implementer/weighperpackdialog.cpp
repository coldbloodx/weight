// WeighPerPackDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\WeighPerPackDialog.h"
#include "..\..\OtherClasses\HelperClass.h"
#include "..\..\DialogClasses\header\FormulaSepWeighDialog.h"

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
	//{{AFX_DATA_INIT(CWeighPerPackDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
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
	DDX_Control(pDX, IDC_GOBACKBUTTON, m_GoBack);
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
	ON_BN_CLICKED(IDC_GOBACKBUTTON, &CWeighPerPackDialog::OnBnClickedGobackbutton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWeighPerPackDialog message handlers

void CWeighPerPackDialog::OnOK() 
{
	// TODO: Add extra validation here
	CString weighPerPackCString, grossWeight;
	m_GrossWeight.GetWindowText(grossWeight);	
	//����Ƥ���������
	if (grossWeight.IsEmpty())
	{
		AfxMessageBox("������Ƥ�أ�");
		return;
	}
	if (!HelperFunctions::isDouble(&m_GrossWeight))
	{
		AfxMessageBox("Ƥ�������������������룡");
		return;
	}

	CFormulaSepWeighDialog* formulaSepWeighDialog = (CFormulaSepWeighDialog*)(SingletonHelper::getInstance()->getSepWieghWindowPtr());
	
	//����Ƥ����ʾ
	formulaSepWeighDialog->m_PackWeight.SetWindowText(grossWeight + "Kg");
	formulaSepWeighDialog->dPackWeight = atof(grossWeight.GetBuffer(0));

	//����ְ��������
	m_WeighPerPack.GetWindowText(weighPerPackCString);
	if (!HelperFunctions::isDouble(&m_WeighPerPack))
	{
		AfxMessageBox("���������������������");
		return;
	}

	double gross = atof(grossWeight.GetBuffer(0));
	double materialWeigh = formulaSepWeighDialog->dMaterialWeight;
	if (weighPerPackCString.IsEmpty())
	{
		formulaSepWeighDialog->bIsMultiPackFlag = FALSE;
		formulaSepWeighDialog->m_IsMultiPackNeeded.SetWindowText("��");
		formulaSepWeighDialog->m_WeighNeeded.SetWindowText(HelperFunctions::doubleToCString(
			materialWeigh + atof(grossWeight.GetBuffer(0))));
		formulaSepWeighDialog->dWeightNeeded = materialWeigh /*+ atof(grossWeight.GetBuffer(0))*/;
		formulaSepWeighDialog->updateMultiTimes();
	}
	else
	{

		if (atof(weighPerPackCString.GetBuffer(0)) <=  atof(grossWeight.GetBuffer(0)))
		{
			AfxMessageBox("���������������������룡");
			return;
		}
		//��ð���
		double weighPerPack = atof(weighPerPackCString.GetBuffer(0)) - gross ;
		formulaSepWeighDialog->dNetWeight = weighPerPack;
		formulaSepWeighDialog->dPackWeight = gross;

		int packCount =static_cast<int>(materialWeigh / weighPerPack);
		formulaSepWeighDialog->m_IsMultiPackNeeded.SetWindowText("��");
		formulaSepWeighDialog->bIsMultiPackFlag = TRUE;
		double packs = materialWeigh / weighPerPack;
		double rest = packs - (double)packCount;
		double neededWeigh = rest * weighPerPack;
		formulaSepWeighDialog->m_WeightPerPack.SetWindowText(weighPerPackCString+"Kg");
		//���°���
		formulaSepWeighDialog->m_PackNeeded.SetWindowText(HelperFunctions::intToCString(packCount) +"��");
		formulaSepWeighDialog->iTotalPacks = packCount;

		//�����Ѿ�������������
		formulaSepWeighDialog->m_AlreadyWeighed.SetWindowText(HelperFunctions::doubleToCString(packCount * weighPerPack));
		formulaSepWeighDialog->dAlreadyWeighed = packCount * weighPerPack;
		formulaSepWeighDialog->dWeightNeeded = formulaSepWeighDialog->dWeightNeeded - packCount * weighPerPack;
		

		//����
		formulaSepWeighDialog->m_WeighNeeded.SetWindowText(HelperFunctions::doubleToCString(neededWeigh  + gross)+"Kg");
		formulaSepWeighDialog->m_RestNeeded.SetWindowText(HelperFunctions::doubleToCString(neededWeigh) + "Kg");
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
	
	//HelperFunctions::showStatus(m_StatusStatic);
	
	//prepare for ui

	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_DIVIDE);//����ͼƬ   
	m_brBk.CreatePatternBrush(&bmp);   
	bmp.DeleteObject();  
	
	CRect wndRect((1024 - 960) / 2, (768 - 580) / 2, (1024 - 960) / 2 + 960, (768 - 580) / 2 + 595) ;
	this->MoveWindow(wndRect);
	
	CButton* buttonArray[] = {&m_Button1,&m_Button2,&m_Button3,&m_Button4,&m_Button5,&m_Button6,&m_Button7,
		&m_Button8,&m_Button9,&m_Button0,&m_ButtonComma,&m_ButtonBack};
	
	int left = 655;
	int top = 161;
	int width = 714 - 655;
	int height = 220 - 161;
	int horiSpacer = 725 - 714;
	int vertSpacer = 231 - 220;

	std::vector<CButton*> buttonVector(buttonArray, buttonArray + 12);

	for (size_t i = 0; i < buttonVector.size(); ++i)
	{
		CRect startRect(left, top, left + width, top + height);
		buttonVector[i]->MoveWindow(startRect, TRUE);

		if (((i + 1) % 3) == 0)
		{
			left = 655;
			top = startRect.bottom + vertSpacer;
		}
		else
		{
			left = startRect.right + horiSpacer;
		}
	}

	CRect okRect(506, 43, 627, 84);
	m_ButtonOK.MoveWindow(okRect);


	CRect cancelRect(658, 43, 778, 84);
	m_ButtonCancel.MoveWindow(cancelRect);

	
	CRect goBackRect(162, 467, 253, 492);
	m_GoBack.MoveWindow(goBackRect);


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

void CWeighPerPackDialog::OnBnClickedGobackbutton()
{
	CDialog::OnCancel();
	// TODO: Add your control notification handler code here
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

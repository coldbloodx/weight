// FormulaSepWeighDialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\Weight.h"
#include "..\..\DialogClasses\header\FormulaSepWeighDialog.h"
#include "..\..\OtherClasses\HelperClass.h"
#include "..\..\DialogClasses\header\FormulaWeighDialog.h"
#include "..\..\DialogClasses\header\WeighPerPackDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormulaSepWeighDialog dialog

CFormulaSepWeighDialog::CFormulaSepWeighDialog(CWnd* pParent /*=NULL*/)
: CDialog(CFormulaSepWeighDialog::IDD, pParent),
dFormulaWeight(0.0),
dMaterialWeight(0.0),
dWeightNeeded(0.0),
dPackWeight(0.0),
dNetWeight(0.0),
dRestWeight(0.0),
dAlreadyWeighed(0.0),
iTotalPacks(0)
{
	//{{AFX_DATA_INIT(CFormulaSepWeighDialog)
	//}}AFX_DATA_INIT
}

CFormulaSepWeighDialog::~CFormulaSepWeighDialog()
{
	HelperFunctions::closeCom(SingletonHelper::getInstance()->com1);
	HelperFunctions::closeCom(SingletonHelper::getInstance()->com2);
}

void CFormulaSepWeighDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormulaSepWeighDialog)
	DDX_Control(pDX, IDC_DIVIDE_BUTTON, m_ButtonDivide);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_WEIGH2_STATIC, m_Com2Value);
	DDX_Control(pDX, IDC_WEIGH1_STATIC, m_Com1Value);
	DDX_Control(pDX, IDC_MATERIALTOTAL, m_MaterialTotal);
	DDX_Control(pDX, IDC_PACKSNEED, m_PackNeeded);
	DDX_Control(pDX, IDC_WEIGHPERPACK, m_WeightPerPack);
	DDX_Control(pDX, IDC_MATERIALNAME, m_MaterialName);
	DDX_Control(pDX, IDC_FORMULAWEIGH, m_FormulaWeigh);
	DDX_Control(pDX, IDC_FORMULANAME, m_FormulaName);
	DDX_Control(pDX, IDC_COM1DISPLAY_LIST, m_Com1DisplayList);
	DDX_Control(pDX, IDC_COM2DISPLAY_LIST, m_Com2DisplayList);
	DDX_Control(pDX, IDC_PRIBUTTON, m_PriButton);
	DDX_Control(pDX, IDC_SECBUTTON, m_SecButton);
	DDX_Control(pDX, IDC_CANCEL, m_CancalButton);
	DDX_Control(pDX, IDC_MULTITIMES_NEEDED, m_IsMultiTimeNeeded);
	DDX_Control(pDX, IDC_ALREADYWEIGHED, m_AlreadyWeighed);
	DDX_Control(pDX, IDC_WEIGHNEEDED, m_WeighNeeded);
	DDX_Control(pDX, IDC_ISMULTIPACKNEEDED, m_IsMultiPackNeeded);
	DDX_Control(pDX, IDC_PACKWEIGHT, m_PackWeight);
	DDX_Control(pDX, IDC_RESTNEEDED, m_RestNeeded);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormulaSepWeighDialog, CDialog)
	//{{AFX_MSG_MAP(CFormulaSepWeighDialog)
	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_DIVIDE_BUTTON, OnDivideButton)
	ON_BN_CLICKED(IDOK, &CFormulaSepWeighDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_PRIBUTTON, &CFormulaSepWeighDialog::OnBnClickedPributton)
	ON_BN_CLICKED(IDC_SECBUTTON, &CFormulaSepWeighDialog::OnBnClickedSecbutton)
	ON_BN_CLICKED(IDC_CANCEL, &CFormulaSepWeighDialog::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormulaSepWeighDialog message handlers

void CFormulaSepWeighDialog::OnOK() 
{
	CDialog::OnOK();
}

BOOL CFormulaSepWeighDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CBitmap   bmp;   
	bmp.LoadBitmap(IDB_FORMULASEPWEIGHT);//����ͼƬ   
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();   

	CRect wndRect(0, 20, 1024, 768 - 50);
	this->MoveWindow(wndRect);

	CRect backRect(170, 490, 267, 517);
	m_CancalButton.MoveWindow(backRect);
	m_CancalButton.DrawBorder(FALSE);
	m_CancalButton.DrawTransparent(TRUE);

	CRect okRect(322, 569, 468, 612);
	m_ButtonOK.MoveWindow(okRect);
	m_ButtonOK.DrawBorder(FALSE);
	m_ButtonOK.DrawTransparent(TRUE);

	CRect sepRect(312, 126, 470, 167);
	m_ButtonDivide.MoveWindow(sepRect);
	m_ButtonDivide.DrawBorder(FALSE);
	m_ButtonDivide.DrawTransparent(TRUE);

	CRect priButton(550, 582, 707, 622);
	m_PriButton.MoveWindow(priButton);
	m_PriButton.DrawBorder(FALSE);
	m_PriButton.DrawTransparent(TRUE);

	CRect secButton(790, 582, 954, 622);
	m_SecButton.MoveWindow(secButton);
	m_SecButton.DrawBorder(FALSE);
	m_SecButton.DrawTransparent(TRUE);

	//set reader timer;
	SetTimer(1,1000,NULL);

	//�Ծ�̬��ǩ��ʼ��

	//�䷽����
	m_FormulaName.SetWindowText(SingletonHelper::getInstance()->getFormulaName());
	//��Ʒ����
	m_FormulaWeigh.SetWindowText(SingletonHelper::getInstance()->getFormulaWeigh()+ "Kg");
	//��������
	materialName = SingletonHelper::getInstance()->compositions[SingletonHelper::getInstance()->getIntData()]->material.c_str();
	m_MaterialName.SetWindowText(materialName);

	//��������	
	dFormulaWeight = atof(SingletonHelper::getInstance()->getFormulaWeigh().GetBuffer(SingletonHelper::getInstance()->getFormulaWeigh().GetLength()));
	dMaterialWeight = dFormulaWeight * SingletonHelper::getInstance()->compositions[SingletonHelper::getInstance()->getIntData()]->percentage / 100;
	m_MaterialTotal.SetWindowText(HelperFunctions::doubleToCString(dMaterialWeight) + "Kg");
	materialWeigh = HelperFunctions::doubleToCString(dMaterialWeight) + "Kg";

	//�Ѿ��������
	m_AlreadyWeighed.SetWindowText("0");

	//��������
	m_WeighNeeded.SetWindowText(HelperFunctions::doubleToCString(dMaterialWeight) + "Kg");
	dWeightNeeded = dMaterialWeight;
	dRestWeight = dMaterialWeight;

	//�ִγ���
	updateMultiTimes();

	//�ְ�����
	m_IsMultiPackNeeded.SetWindowText("--");

	//ÿ������
	m_WeightPerPack.SetWindowText("--");

	//��Ҫ����
	m_PackNeeded.SetWindowText("--");

	//��Ҫ����
	m_RestNeeded.SetWindowText("--");	

	//Ƥ��
	m_PackWeight.SetWindowText("1");

	//init comPort;
	com1 = HelperFunctions::initCom(SingletonHelper::getInstance()->com1,
		CString("COM1"),
		atoi(SingletonHelper::getInstance()->getCom1BaudRate().GetBuffer(0)));
	if (com1 < 0)
	{
		AfxMessageBox("com1��ʼ��ʧ�ܣ���ȷ�ϳƵ����������Ȼ��رնԻ������ԣ�");
	}

	com2 = HelperFunctions::initCom(SingletonHelper::getInstance()->com2,
		CString("COM2"),
		atoi(SingletonHelper::getInstance()->getCom2BaudRate().GetBuffer(0)));
	if (com2 < 0)
	{
		AfxMessageBox("com2��ʼ��ʧ�ܣ���ȷ�ϳƵ����������Ȼ��رնԻ������ԣ�");
	}

	m_Com1Value.SetFont(SingletonHelper::getInstance()->simHei40, TRUE);
	m_Com2Value.SetFont(SingletonHelper::getInstance()->simHei40, TRUE);

	return TRUE;  
}

void CFormulaSepWeighDialog::OnTimer(UINT nIDEvent) 
{
	//check the item count in display list, reset list every five mins
	if (m_Com1DisplayList.GetCount() > 300  )
	{
		m_Com1DisplayList.ResetContent();
		m_Com2DisplayList.ResetContent();
	}

	//format time
	CTime time = CTime::GetCurrentTime();
	CString currentTime = time.Format("%X: ");

	//read data and format data
	CString com1Result, com2Result;
	if (com1 >= 0)
	{
		com1Result = HelperFunctions::readCom(SingletonHelper::getInstance()->com2);
	}

	if (com2 >= 0)
	{
		com2Result = HelperFunctions::readCom(SingletonHelper::getInstance()->com1);
	}

	com1Result = com1Result.IsEmpty() ? "0000.0" : com1Result;
	com2Result = com2Result.IsEmpty() ? "000.00" : com2Result;

	m_Com1Value.SetWindowText(com1Result);
	m_Com2Value.SetWindowText(com2Result);

	RECT rect;
	m_Com1Value.GetWindowRect(&rect);   
	m_Com1Value.GetParent()->ScreenToClient(&rect);
	m_Com1Value.GetParent()->InvalidateRect(&rect, TRUE);

	m_Com2Value.GetWindowRect(&rect);   
	m_Com2Value.GetParent()->ScreenToClient(&rect);
	m_Com2Value.GetParent()->InvalidateRect(&rect, TRUE);

	m_Com1DisplayList.InsertString(0,currentTime + com2Result + "Kg");
	m_Com2DisplayList.InsertString(0,currentTime + com1Result + "Kg");

	//HelperFunctions::showStatus(m_StatusStatic);
	CDialog::OnTimer(nIDEvent);
}

void CFormulaSepWeighDialog::OnDivideButton() 
{
	// TODO: Add your control notification handler code here
	CWeighPerPackDialog weighPerPackDialog;
	SingletonHelper::getInstance()->setSepWeighWindowPtr((void*)this);
	weighPerPackDialog.DoModal();
}

HBRUSH CFormulaSepWeighDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if   (pWnd == this)   
	{   
		return m_brBk;   
	}   
	if   (nCtlColor   ==   CTLCOLOR_STATIC)   
	{     
		pDC->SetBkMode(TRANSPARENT);	//͸��   
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	}   
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CFormulaSepWeighDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//�ܵĳ���������ƣ�0.5����
	double threshold = 0.5;

	if (dWeightNeeded > threshold || dWeightNeeded < -1.0 * threshold)
	{
		CString msg("û����ɳ�����Ҫ������");
		CString caption("��������");
		//ѡ��cancel�򷵻�
		if (MessageBox(msg, caption, MB_OKCANCEL) != IDOK)
		{
			return;
		}
		else
		{
			CDialog::OnOK();
		}
	}
	else
	{
		CFormulaWeighDialog* pFormulaWeighDialog = (CFormulaWeighDialog*)SingletonHelper::getInstance()->getPtrData();
		SingletonHelper::getInstance()->compositions[SingletonHelper::getInstance()->getIntData()]->isWeigh = TRUE;
		pFormulaWeighDialog->refreshWeighedFlag();
		HelperFunctions::printLabel(materialName, materialWeigh, SingletonHelper::getInstance()->getLineNumber());
		CDialog::OnOK();
	}

}

void CFormulaSepWeighDialog::OnBnClickedPributton()
{
	// TODO: Add your control notification handler code here
	if (dPackWeight <=0.0)
	{
		AfxMessageBox("Ƥ����������������Ƥ��");
		return;
	}

	CString priWeigh = HelperFunctions::readCom(SingletonHelper::getInstance()->com1);
	
	//�����п��ܳ��ִ���
	if (priWeigh.IsEmpty())
	{
		return;
	}

	double dPriIndicatorWeigh = atof(priWeigh.GetBuffer(0));
	
	//������
	double priThreshold = 0.5;
	double priNeededWeigh = (dAlreadyWeighed + dPriIndicatorWeigh - dPackWeight) - dMaterialWeight;
	//��Ƴ������빫��
	if ( priNeededWeigh <= priThreshold || priNeededWeigh <= -1.0 * priThreshold)
	{
		dAlreadyWeighed  += dPriIndicatorWeigh - dPackWeight;
		dWeightNeeded = dWeightNeeded - dPriIndicatorWeigh + dPackWeight;
		dRestWeight = dMaterialWeight - dAlreadyWeighed;
		updateMultiTimes();
	}
	else
	{
		AfxMessageBox("�Ѿ������������������������һЩ����");
		return;
	}
	AfxMessageBox("��ƶ������뽫��ƵĲ�����գ�׼���´γ���");
	return;
}

void CFormulaSepWeighDialog::OnBnClickedSecbutton()
{
	// TODO: Add your control notification handler code here
	if (dPackWeight <=0.0)
	{
		AfxMessageBox("Ƥ����������������Ƥ��");
		return;
	}
	CString secWeigh = HelperFunctions::readCom(SingletonHelper::getInstance()->com2);

	//�����п��ܳ��ִ���
	if (secWeigh.IsEmpty())
	{
		return;
	}

	double dSecIndicatorWeigh = atof(secWeigh.GetBuffer(0));

	//С�Ƴ������
	double secThreshold = 0.05;
	double secNeededWeigh = (dAlreadyWeighed + dSecIndicatorWeigh - dPackWeight) - dMaterialWeight;

	if (secNeededWeigh <= secThreshold || secNeededWeigh <= -1.0 * secThreshold)
	{
		dAlreadyWeighed  += dSecIndicatorWeigh - dPackWeight;
		dWeightNeeded = dWeightNeeded - dSecIndicatorWeigh + dPackWeight;
		dRestWeight = dMaterialWeight - dAlreadyWeighed;
		updateMultiTimes();
	}
	else
	{
		AfxMessageBox("�Ѿ������������������������һЩ����");
		return;
	}

	AfxMessageBox("С�ƶ������뽫С�ƵĲ�����գ�׼���´γ���");
	return;
}

void CFormulaSepWeighDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CFormulaSepWeighDialog::updateMultiTimes()
{
	dWeightNeeded > 1999.0 ? m_IsMultiTimeNeeded.SetWindowText("��"): m_IsMultiTimeNeeded.SetWindowText("����");

	RECT rect;
	//����������ܵĳ���
	m_WeighNeeded.SetWindowText(HelperFunctions::doubleToCString(dWeightNeeded + dPackWeight));
	m_WeighNeeded.GetParent()->GetWindowRect(&rect);   
	m_WeighNeeded.GetParent()->ScreenToClient(&rect);
	m_WeighNeeded.GetParent()->InvalidateRect(&rect, TRUE);

	//�������������
	m_RestNeeded.SetWindowText(HelperFunctions::doubleToCString(dRestWeight));
	m_RestNeeded.GetParent()->GetWindowRect(&rect);   
	m_RestNeeded.GetParent()->ScreenToClient(&rect);
	m_RestNeeded.GetParent()->InvalidateRect(&rect, TRUE);

	m_AlreadyWeighed.SetWindowText(HelperFunctions::doubleToCString(dAlreadyWeighed));
	m_AlreadyWeighed.GetParent()->GetWindowRect(&rect);   
	m_AlreadyWeighed.GetParent()->ScreenToClient(&rect);
	m_AlreadyWeighed.GetParent()->InvalidateRect(&rect, TRUE);

}
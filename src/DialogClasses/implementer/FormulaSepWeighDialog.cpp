// FormulaSepWeighDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "FormulaSepWeighDialog.h"
#include "HelperClass.h"
#include "FormulaWeighDialog.h"
#include "WeighPerPackDialog.h"
#include "uifunctions.h"
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
	utils::closeCom(SingletonHelper::getInstance()->com1);
	utils::closeCom(SingletonHelper::getInstance()->com2);
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

    

	//set reader timer;
	SetTimer(1,1000,NULL);

	//对静态标签初始化

	//配方名称
	m_FormulaName.SetWindowText(SingletonHelper::getInstance()->getFormulaName());
	//成品重量
	m_FormulaWeigh.SetWindowText(SingletonHelper::getInstance()->getFormulaWeigh()+ "Kg");
	//材料名称
	materialName = SingletonHelper::getInstance()->compositions[SingletonHelper::getInstance()->getIntData()]->material.c_str();
	m_MaterialName.SetWindowText(materialName);

	//所需重量	
	dFormulaWeight = atof(SingletonHelper::getInstance()->getFormulaWeigh().GetBuffer(SingletonHelper::getInstance()->getFormulaWeigh().GetLength()));
	dMaterialWeight = dFormulaWeight * SingletonHelper::getInstance()->compositions[SingletonHelper::getInstance()->getIntData()]->percentage / 100;
	m_MaterialTotal.SetWindowText(utils::doubleToCString(dMaterialWeight) + "Kg");
	materialWeigh = utils::doubleToCString(dMaterialWeight) + "Kg";

	//已经完成重量
	m_AlreadyWeighed.SetWindowText("0");

	//待称重量
	m_WeighNeeded.SetWindowText(utils::doubleToCString(dMaterialWeight) + "Kg");
	dWeightNeeded = dMaterialWeight;
	dRestWeight = dMaterialWeight;

	//分次称量
	updateMultiTimes();

	//分包称重
	m_IsMultiPackNeeded.SetWindowText("--");

	//每包重量
	m_WeightPerPack.SetWindowText("--");

	//需要包数
	m_PackNeeded.SetWindowText("--");

	//需要称重
	m_RestNeeded.SetWindowText("--");	

	//皮重
	m_PackWeight.SetWindowText("1");

	//init comPort;
	com1 = utils::initCom(SingletonHelper::getInstance()->com1,
		CString("COM1"),
		atoi(SingletonHelper::getInstance()->getCom1BaudRate().GetBuffer(0)));
	if (com1 < 0)
	{
		AfxMessageBox("com1初始化失败，请确认称的连接情况，然后关闭对话框重试！");
	}

	com2 = utils::initCom(SingletonHelper::getInstance()->com2,
		CString("COM2"),
		atoi(SingletonHelper::getInstance()->getCom2BaudRate().GetBuffer(0)));
	if (com2 < 0)
	{
		AfxMessageBox("com2初始化失败，请确认称的连接情况，然后关闭对话框重试！");
	}

	m_Com1Value.SetFont(SingletonHelper::getInstance()->simHei40, TRUE);
	m_Com2Value.SetFont(SingletonHelper::getInstance()->simHei40, TRUE);
    uiutils::setdlgsize(this, &m_CancalButton, &m_ButtonOK);
    
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
		com1Result = utils::readCom(SingletonHelper::getInstance()->com2);
	}

	if (com2 >= 0)
	{
		com2Result = utils::readCom(SingletonHelper::getInstance()->com1);
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
		pDC->SetBkMode(TRANSPARENT);	//透明   
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);   
	}   
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CFormulaSepWeighDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//总的称重误差限制，0.5公斤
	double threshold = 0.5;

	if (dWeightNeeded > threshold || dWeightNeeded < -1.0 * threshold)
	{
		CString msg("没有完成称量，要放弃吗？");
		CString caption("放弃称重");
		//选择cancel则返回
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
		utils::printLabel(materialName, materialWeigh, SingletonHelper::getInstance()->getLineNumber());
		CDialog::OnOK();
	}

}

void CFormulaSepWeighDialog::OnBnClickedPributton()
{
	// TODO: Add your control notification handler code here
	if (dPackWeight <=0.0)
	{
		AfxMessageBox("皮重输入有误，请输入皮重");
		return;
	}

	CString priWeigh = utils::readCom(SingletonHelper::getInstance()->com1);
	
	//读数有可能出现错误
	if (priWeigh.IsEmpty())
	{
		return;
	}

	double dPriIndicatorWeigh = atof(priWeigh.GetBuffer(0));
	
	//大称误差
	double priThreshold = 0.5;
	double priNeededWeigh = (dAlreadyWeighed + dPriIndicatorWeigh - dPackWeight) - dMaterialWeight;
	//大称称量误差半公斤
	if ( priNeededWeigh <= priThreshold || priNeededWeigh <= -1.0 * priThreshold)
	{
		dAlreadyWeighed  += dPriIndicatorWeigh - dPackWeight;
		dWeightNeeded = dWeightNeeded - dPriIndicatorWeigh + dPackWeight;
		dRestWeight = dMaterialWeight - dAlreadyWeighed;
		updateMultiTimes();
	}
	else
	{
		AfxMessageBox("已经超出所需材料重量！请拿走一些材料");
		return;
	}
	AfxMessageBox("大称读数，请将大称的材料清空，准备下次称量");
	return;
}

void CFormulaSepWeighDialog::OnBnClickedSecbutton()
{
	// TODO: Add your control notification handler code here
	if (dPackWeight <=0.0)
	{
		AfxMessageBox("皮重输入有误，请输入皮重");
		return;
	}
	CString secWeigh = utils::readCom(SingletonHelper::getInstance()->com2);

	//读数有可能出现错误
	if (secWeigh.IsEmpty())
	{
		return;
	}

	double dSecIndicatorWeigh = atof(secWeigh.GetBuffer(0));

	//小称称量误差
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
		AfxMessageBox("已经超出所需材料重量！请拿走一些材料");
		return;
	}

	AfxMessageBox("小称读数，请将小称的材料清空，准备下次称量");
	return;
}

void CFormulaSepWeighDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CFormulaSepWeighDialog::updateMultiTimes()
{
	dWeightNeeded > 1999.0 ? m_IsMultiTimeNeeded.SetWindowText("是"): m_IsMultiTimeNeeded.SetWindowText("待定");

	RECT rect;
	//跟新上面的总的称重
	m_WeighNeeded.SetWindowText(utils::doubleToCString(dWeightNeeded + dPackWeight));
	m_WeighNeeded.GetParent()->GetWindowRect(&rect);   
	m_WeighNeeded.GetParent()->ScreenToClient(&rect);
	m_WeighNeeded.GetParent()->InvalidateRect(&rect, TRUE);

	//更新下面待称重
	m_RestNeeded.SetWindowText(utils::doubleToCString(dRestWeight));
	m_RestNeeded.GetParent()->GetWindowRect(&rect);   
	m_RestNeeded.GetParent()->ScreenToClient(&rect);
	m_RestNeeded.GetParent()->InvalidateRect(&rect, TRUE);

	m_AlreadyWeighed.SetWindowText(utils::doubleToCString(dAlreadyWeighed));
	m_AlreadyWeighed.GetParent()->GetWindowRect(&rect);   
	m_AlreadyWeighed.GetParent()->ScreenToClient(&rect);
	m_AlreadyWeighed.GetParent()->InvalidateRect(&rect, TRUE);

}
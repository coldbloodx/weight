// WeighManagementDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "WeighManagementDialog.h"
#include "formuladialog.h"
#include "StatisticDialog.h"
#include "QueryDialog.h"
#include "MaterialManagementDialog.h"
#include "helperclass.h"
#include "uifunctions.h"
#include "BarcodeManagementDlg.h"
#include "TraceQueryDialog.h"


// CWeighManagementDialog dialog

IMPLEMENT_DYNAMIC(CMainSettings, CDialog)

CMainSettings::CMainSettings(CWnd* pParent /*=NULL*/)
: CDialog(CMainSettings::IDD, pParent)
{

}

CMainSettings::~CMainSettings()
{
}

void CMainSettings::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON1, m_MaterialManagement);
    DDX_Control(pDX, IDC_BUTTON2, m_FormulaManagement);
    DDX_Control(pDX, IDC_BUTTON3, m_Query);
    DDX_Control(pDX, IDC_BUTTON4, m_Statistic);
    DDX_Control(pDX, IDC_BARCODE_UPDATE, m_barcodeManagement);
    DDX_Control(pDX, IDCANCEL, m_goBackButton);
}


BEGIN_MESSAGE_MAP(CMainSettings, CDialog)

    ON_BN_CLICKED(IDC_BUTTON1, &CMainSettings::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CMainSettings::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CMainSettings::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CMainSettings::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BARCODE_UPDATE, &CMainSettings::OnBnClickedBarcodeManagement)
    ON_BN_CLICKED(IDCANCEL, &CMainSettings::OnBnClickedGoBack)

    ON_WM_PAINT()
END_MESSAGE_MAP()


// CWeighManagementDialog message handlers

void CMainSettings::OnBnClickedButton4()
{
    //CStatisticDialog statisticDialog;
    //statisticDialog.DoModal();
    CTraceQueryDialog dlg;
    dlg.DoModal();
}

BOOL CMainSettings::OnInitDialog()
{
    CDialog::OnInitDialog();



    CButton* buttonArray[6] = {&m_MaterialManagement,&m_FormulaManagement,
        &m_Query, &m_Statistic, &m_barcodeManagement, &m_goBackButton};
    std::vector<CButton*> buttonvec(buttonArray, buttonArray + 6);
    uiFunctions::init6Buttons(buttonvec);

    uiFunctions::setdlgsize(this);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void CMainSettings::OnBnClickedButton1()
{
    // TODO: Add your control notification handler code here
    CMaterialManagementDialog materialManagementDialog;
    materialManagementDialog.DoModal();
}

void CMainSettings::OnBnClickedButton2()
{
    // TODO: Add your control notification handler code here
    CFormulaDialog testDialog;
    testDialog.m_From = 1;
    testDialog.DoModal();
}



void CMainSettings::OnBnClickedButton3()
{
    // TODO: Add your control notification handler code here
    CQueryDialog queryDialog;
    queryDialog.DoModal();
}

void CMainSettings::OnPaint()
{
    uiFunctions::drawDlgBg(this, IDB_MAINPAGE);
}

void CMainSettings::OnBnClickedGoBack()
{
    CDialog::OnCancel();
}

void CMainSettings::OnBnClickedBarcodeManagement()
{
    CBarcodeManagementDlg mgrDlg;
    mgrDlg.DoModal();
}
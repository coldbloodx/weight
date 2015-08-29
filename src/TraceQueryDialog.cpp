// TraceQueryDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "TraceQueryDialog.h"
#include "uiFunctions.h"
#include "QueryCondDialog.h"
#include "constants.h"

// CTraceQueryDialog dialog

IMPLEMENT_DYNAMIC(CTraceQueryDialog, CDialog)

CTraceQueryDialog::CTraceQueryDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTraceQueryDialog::IDD, pParent)
{

}

CTraceQueryDialog::~CTraceQueryDialog()
{
}

void CTraceQueryDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON1, btnWorkOut);
    DDX_Control(pDX, IDC_BUTTON2, btnMaterialAmount);
    DDX_Control(pDX, IDC_BUTTON3, btnProductAmount);
    DDX_Control(pDX, IDC_BUTTON4, btnTraceQuery);
    DDX_Control(pDX, IDOK, btnOK);
    DDX_Control(pDX, IDCANCEL, btnCancel);
}


BEGIN_MESSAGE_MAP(CTraceQueryDialog, CDialog)
    ON_BN_CLICKED(IDC_BUTTON1, &CTraceQueryDialog::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CTraceQueryDialog::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CTraceQueryDialog::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CTraceQueryDialog::OnBnClickedButton4)
END_MESSAGE_MAP()

//工作量统计

void CTraceQueryDialog::OnBnClickedButton1()
{
    CQueryCondDialog conddlg;
    conddlg.qtype = QTYPE_USERWORKOUT;
    conddlg.DoModal();
}

//物料使用统计
void CTraceQueryDialog::OnBnClickedButton2()
{
    CQueryCondDialog conddlg;
    conddlg.qtype = QTYPE_MATERIAMOUNT;
    conddlg.DoModal();
}

//成品数量统计
void CTraceQueryDialog::OnBnClickedButton3()
{
    CQueryCondDialog conddlg;
    conddlg.qtype = QTYPE_PRODUCTAMOUNT;
    conddlg.DoModal();
}

//追溯查询
void CTraceQueryDialog::OnBnClickedButton4()
{
    //not done yet
}


BOOL CTraceQueryDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    CButton* btnarray[6] = {&btnWorkOut, &btnMaterialAmount, &btnProductAmount, 
        &btnTraceQuery, &btnCancel, &btnOK};
    uiutils::init2rowbtns(btnarray, 5);
    btnOK.ShowWindow(FALSE);
    uiutils::setdlgsize(this);

    return TRUE;
}

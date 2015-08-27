// BarcodeManagemengDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "BarcodeManagementDlg.h"
#include "BarcodeUpdateDlg.h"
#include "uiFunctions.h"
#include "RecordSetPointer.h"


// CBarcodeManagemengDlg dialog

IMPLEMENT_DYNAMIC(CBarcodeManagemengDlg, CDialog)

CBarcodeManagemengDlg::CBarcodeManagemengDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBarcodeManagemengDlg::IDD, pParent)
{

}

CBarcodeManagemengDlg::~CBarcodeManagemengDlg()
{
}

void CBarcodeManagemengDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST2, resultlist);
}


BEGIN_MESSAGE_MAP(CBarcodeManagemengDlg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON10, &CBarcodeManagemengDlg::OnBnClickedButton10)
    ON_BN_CLICKED(IDC_BUTTON11, &CBarcodeManagemengDlg::OnBnClickedButton11)
    ON_BN_CLICKED(IDC_BUTTON1, &CBarcodeManagemengDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CBarcodeManagemengDlg message handlers
//add barcode
void CBarcodeManagemengDlg::OnBnClickedButton10()
{
	CBarcodeUpdateDlg updatedlg;
	updatedlg.bAddFlag = 1;
	updatedlg.DoModal();
}

//remove barcode
void CBarcodeManagemengDlg::OnBnClickedButton11()
{

}

//update barcode
void CBarcodeManagemengDlg::OnBnClickedButton1()
{
   
    CBarcodeUpdateDlg updatedlg;
    updatedlg.DoModal();
}

BOOL CBarcodeManagemengDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    CString sql = "select * from barcodes;";

    _RecordsetPtr dbptr = RecordSetPointer::getInstancePtr()->execquery(sql);
    

    CString headerarray[3] = {"ID", "barcode", "manufacture"};
    vector<CString>  headervec(headerarray, headerarray + 3);
    uiFunctions::initListHeader(headervec, resultlist);
    uiFunctions::updateList(dbptr, resultlist , headervec);


    uiFunctions::setdlgsize(this);
    return TRUE;
}


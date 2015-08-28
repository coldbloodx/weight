// BarcodeManagemengDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "BarcodeManagementDlg.h"
#include "BarcodeUpdateDlg.h"
#include "uiFunctions.h"
#include "RecordSetPointer.h"
#include "helperclass.h"


// CBarcodeManagemengDlg dialog

IMPLEMENT_DYNAMIC(CBarcodeManagementDlg, CDialog)

CBarcodeManagementDlg::CBarcodeManagementDlg(CWnd* pParent /*=NULL*/)
: CDialog(CBarcodeManagementDlg::IDD, pParent)
{

}

CBarcodeManagementDlg::~CBarcodeManagementDlg()
{
}

void CBarcodeManagementDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST2, resultlist);
}


BEGIN_MESSAGE_MAP(CBarcodeManagementDlg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON10, &CBarcodeManagementDlg::OnBnClickedButton10)
    ON_BN_CLICKED(IDC_BUTTON11, &CBarcodeManagementDlg::OnBnClickedButton11)
    ON_BN_CLICKED(IDC_BUTTON1, &CBarcodeManagementDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CBarcodeManagemengDlg message handlers
//add barcode
void CBarcodeManagementDlg::OnBnClickedButton10()
{
    CBarcodeUpdateDlg updatedlg;
    updatedlg.bAddFlag = 1;
    updatedlg.DoModal();
    resultlist.DeleteAllItems();
    initlistctrl();
}

//remove barcode
void CBarcodeManagementDlg::OnBnClickedButton11()
{
    POSITION pos = resultlist.GetFirstSelectedItemPosition() - 1;
    CString barcodeid = resultlist.GetItemText((int)pos, 0);

    if (barcodeid.IsEmpty())
    {
        AfxMessageBox("请选择要删除的条码");
        return;
    }
    CString sql; 
    sql.Format("delete from barcodes where id = %s", barcodeid);

    _RecordsetPtr dbptr = RecordSetPointer::getInstancePtr()->execquery(sql);
    resultlist.DeleteAllItems();
    initlistctrl();
}

//update barcode
void CBarcodeManagementDlg::OnBnClickedButton1()
{

    POSITION pos = resultlist.GetFirstSelectedItemPosition() - 1;
    CString barcodeid = resultlist.GetItemText((int)pos, 0);

    CString barcode = resultlist.GetItemText((int)pos, 1);
    if (barcodeid.IsEmpty())
    {
        AfxMessageBox("请选择要更新的条码");
        return;
    }

    CBarcodeUpdateDlg updatedlg;
    updatedlg.barcodeid = barcodeid;
    updatedlg.origbarcode = barcode;
    updatedlg.DoModal();

    resultlist.DeleteAllItems();
    initlistctrl();
}

BOOL CBarcodeManagementDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    initlistheader();
    initlistctrl();

    uiFunctions::setdlgsize(this);
    return TRUE;
}

void CBarcodeManagementDlg::initlistctrl()
{
    resultlist.DeleteAllItems();
    CString sql = "select * from barcodes;";

    _RecordsetPtr dbptr = RecordSetPointer::getInstancePtr()->execquery(sql);


    CString headerarray[3] = {"ID", "barcode", "manufacture"};
    vector<CString>  headervec(headerarray, headerarray + 3);
    uiFunctions::updateList(dbptr, resultlist , headervec);
}

void CBarcodeManagementDlg::initlistheader()
{
    CString headerarray[3] = {"编号", "条码", "厂商"};
    vector<CString>  headervec(headerarray, headerarray + 3);
    uiFunctions::initListHeader(headervec, resultlist);
}


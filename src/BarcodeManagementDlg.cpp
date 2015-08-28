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
}

//remove barcode
void CBarcodeManagementDlg::OnBnClickedButton11()
{

}

//update barcode
void CBarcodeManagementDlg::OnBnClickedButton1()
{

	CBarcodeUpdateDlg updatedlg;
	SingletonHelper::getInstance()->setPtrData(this);
	updatedlg.DoModal();
}

BOOL CBarcodeManagementDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	uiFunctions::initListHeader(headervec, resultlist);
	uiFunctions::updateList(dbptr, resultlist , headervec);

}


// BarcodemanagementDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "BarcodeUpdateDlg.h"
#include "uiFunctions.h"
#include "RecordSetPointer.h"
#include "BarcodeManagementDlg.h"
#include "helperclass.h"


// CBarcodemanagementDlg dialog

IMPLEMENT_DYNAMIC(CBarcodeUpdateDlg, CDialog)

CBarcodeUpdateDlg::CBarcodeUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBarcodeUpdateDlg::IDD, pParent), bAddFlag(0)
{

}

CBarcodeUpdateDlg::~CBarcodeUpdateDlg()
{
}

void CBarcodeUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_EDIT1, barcode);
	DDX_Control(pDX, IDC_EDIT2, manufacture);
}


BEGIN_MESSAGE_MAP(CBarcodeUpdateDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CBarcodeUpdateDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBarcodeUpdateDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


BOOL CBarcodeUpdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	if(bAddFlag)
	{
		this->SetWindowText("增加条码");
	}
	else
	{
		barcode.SetWindowText(origBarcode);
		barcode.EnableWindow(FALSE);
		this->SetWindowText("修改厂家");
	}

    return TRUE;
}


void CBarcodeUpdateDlg::OnBnClickedOk()
{
	CString barcodeStr;
	CString manuStr;
	CString sql;
	barcode.GetWindowText(barcodeStr);
	manufacture.GetWindowText(manuStr);

	if(barcodeStr.IsEmpty() || manuStr.IsEmpty())
	{
		AfxMessageBox("条码和生产厂家不能为空.");
		return;
	}

	if(bAddFlag)
	{

		sql.Format("insert into barcodes(barcode, manufacture) values('%s', '%s')", barcodeStr, manuStr);
		
	}
	else
	{
		sql.Format("update barcodes set manufacture = \"%s\" where barcode = \"%s\"", manuStr, barcodeStr);
	}
	_RecordsetPtr dbptr = RecordSetPointer::getInstancePtr()->execquery(sql);

	CBarcodeManagementDlg* dlgptr = (CBarcodeManagementDlg*)SingletonHelper::getInstance()->getPtrData();
	
	dlgptr->resultlist.DeleteAllItems();
	dlgptr->initlistctrl();

	CDialog::OnOK();
}

void CBarcodeUpdateDlg::OnBnClickedCancel()
{
	OnCancel();
}

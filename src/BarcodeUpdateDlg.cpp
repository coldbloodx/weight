// BarcodemanagementDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "BarcodeUpdateDlg.h"
#include "uiFunctions.h"
#include "DBptr.h"
#include "BarcodeManagementDlg.h"
#include "helperclass.h"


// CBarcodemanagementDlg dialog

IMPLEMENT_DYNAMIC(CBarcodeUpdateDlg, CDialog)

CBarcodeUpdateDlg::CBarcodeUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBarcodeUpdateDlg::IDD, pParent), bAddFlag(0), barcodeid("")
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
		barcode.SetWindowText(origbarcode);
		barcode.EnableWindow(FALSE);
		this->SetWindowText("修改厂家");
	}
    
    uiutils::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);
    return TRUE;
}


void CBarcodeUpdateDlg::OnBnClickedOk()
{

	CString manuStr;
	CString sql;

	manufacture.GetWindowText(manuStr);

    CString barcodeStr;
    barcode.GetWindowText(barcodeStr);

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
		sql.Format("update barcodes set manufacture = '%s' where id = %s", manuStr, barcodeid);
	}

	_RecordsetPtr dbptr = SQLExecutor::getInstancePtr()->execquery(sql);

	CDialog::OnOK();
}

void CBarcodeUpdateDlg::OnBnClickedCancel()
{
	OnCancel();
}

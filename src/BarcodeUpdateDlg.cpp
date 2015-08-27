// BarcodemanagementDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "BarcodeUpdateDlg.h"


// CBarcodemanagementDlg dialog

IMPLEMENT_DYNAMIC(CBarcodeUpdateDlg, CDialog)

CBarcodeUpdateDlg::CBarcodeUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBarcodeUpdateDlg::IDD, pParent)
{

}

CBarcodeUpdateDlg::~CBarcodeUpdateDlg()
{
}

void CBarcodeUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBarcodeUpdateDlg, CDialog)
END_MESSAGE_MAP()


BOOL CBarcodeUpdateDlg::OnInitDialog()
{
    CString sql = "select * from barcodes;";


    return TRUE;
}

// CBarcodemanagementDlg message handlers

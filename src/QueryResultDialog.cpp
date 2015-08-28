// QueryResultDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Weight.h"
#include "QueryResultDialog.h"
#include "uiFunctions.h"


// CQueryResultDialog dialog

IMPLEMENT_DYNAMIC(CQueryResultDialog, CDialog)

CQueryResultDialog::CQueryResultDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryResultDialog::IDD, pParent)
{

}

CQueryResultDialog::~CQueryResultDialog()
{
}

void CQueryResultDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, ctlResultList);
    DDX_Control(pDX, IDCANCEL, btnCancel);
}


BEGIN_MESSAGE_MAP(CQueryResultDialog, CDialog)
END_MESSAGE_MAP()

BOOL CQueryResultDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    uiFunctions::setdlgsize(this, &btnCancel);

    switch(qtype)
    {
        case QTYPE_WORKOUT:
        
            break;
        case QTYPE_MATERIAMOUNT:

            break;
        case QTYPE_PRODUCTAMOUNT:

            break;

        default:
            break;
    }


    return TRUE;
}

